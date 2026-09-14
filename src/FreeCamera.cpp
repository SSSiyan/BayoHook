#include "FreeCamera.h"
#include "../SafeHook/SafeHook.h"
#include <WorldVisualizer.hpp>

static const char* FreeCamera_CfgKeys[FreeCamera::CTRL_MAX] = {
	"FreeCamera.Toggle", "FreeCamera.CutscenePause",
	"FreeCamera.Forward", "FreeCamera.Backward", "FreeCamera.Left", "FreeCamera.Right",
	"FreeCamera.LookLeft", "FreeCamera.LookRight", "FreeCamera.LookUp", "FreeCamera.LookDown",
	"FreeCamera.FovUp", "FreeCamera.FovDown",
	"FreeCamera.TurboMove",
	"FreeCamera.MoveUp", "FreeCamera.MoveDown"
};

struct Vector3
{
	float x, y, z;

	Vector3() : x(0), y(0), z(0) {}
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

	Vector3& operator+=(const Vector3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;

		return *this;
	}

	Vector3& operator-=(const Vector3& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;

		return *this;
	}

	Vector3 operator+(const Vector3& v)
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	Vector3 operator-(const Vector3& v)
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	Vector3 operator*(const Vector3& v)
	{
		return Vector3(x * v.x, y * v.y, z * v.z);
	}

	Vector3 operator*(float scalar)
	{
		return Vector3(x * scalar, y * scalar, z * scalar);
	}

	Vector3 operator/(const Vector3& v)
	{
		return Vector3(x / v.x, y / v.y, z / v.z);
	}

	Vector3& operator*=(const Vector3& v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;

		return *this;
	}

	Vector3& operator/=(const Vector3& v)
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;

		return *this;
	}
};

#define DEG_TO_RAD(x) (x * (M_PI / 180.0))
#define RAD_TO_DEG(x) (x * (180.0 / M_PI))

void FreeCamera::Load(const utils::Config& cfg)
{
	m_bEnabled = cfg.get<bool>("FreeCamera.Enabled").value_or(false);
	m_bUseMouseForLook = cfg.get<bool>("FreeCamera.UseMouse").value_or(false);

	m_fSpeed = cfg.get<float>("FreeCamera.Speed").value_or(0.2f);
	m_fTurboSpeed = cfg.get<float>("FreeCamera.TurboSpeed").value_or(1.0f);
	m_fLookPitchSpeed = cfg.get<float>("FreeCamera.LookPitchSpeed").value_or(0.03f);
	m_fLookSpeed = cfg.get<float>("FreeCamera.LookSpeed").value_or(0.05f);

	for (int i = 0; i < CTRL_MAX; i++)
		m_Controls[i] = cfg.get<int>(FreeCamera_CfgKeys[i]).value_or(m_Controls[i]);
}

void FreeCamera::Save(utils::Config& cfg)
{
	cfg.set<bool>("FreeCamera.Enabled", m_bEnabled);
	cfg.set<bool>("FreeCamera.UseMouse", m_bUseMouseForLook);
	cfg.set<float>("FreeCamera.Speed", m_fSpeed);

	cfg.set<float>("FreeCamera.TurboSpeed", m_fTurboSpeed);
	cfg.set<float>("FreeCamera.LookPitchSpeed", m_fLookPitchSpeed);
	cfg.set<float>("FreeCamera.LookSpeed", m_fLookSpeed);

	for (int i = 0; i < CTRL_MAX; i++)
		cfg.set<int>(FreeCamera_CfgKeys[i], m_Controls[i]);
}

void FreeCamera::Update(void *pCamera)
{
	if (!m_bEnabled)
		return;

	if (pCamera != (void*)0xF2DAE0)
		return; // not main camera

	static Vector3 nowTrans, nowTarget, nowUp;
	static float nowFov;

	Vector3* trans = (Vector3*)((unsigned long)pCamera + 0xB0 + 0x100);
	Vector3* target = (Vector3*)((unsigned long)pCamera + 0xB0 + 0x110);
	Vector3* up = (Vector3*)((unsigned long)pCamera + 0xB0 + 0x120);
	float* fov = (float*)((unsigned long)pCamera + 0x94);

	{
		static bool guard = false;
		if (GetAsyncKeyState(m_Controls[CTRL_TOGGLE]) & 0x8000)
		{
			if (!guard)
			{
				m_bToggle ^= true;

				SafeHook::WriteMemory<unsigned char>(0xA95E2E, m_bToggle ? 0xEB : 0x75);

				up->x = 0.0;
				up->y = 1.0;
				up->z = 0.0;

				if (m_bCutscenePaused)
				{
					((void(__thiscall*)(void*))0xC31E40)((void*)0x5BB5BA0);
					((void(__cdecl*)())0x514890)();
					((void(__cdecl*)(int))0x450B80)(0);
					((void(__thiscall*)(void*, int))0x433AC0)((void*)0x50A4FC4, 0);

					SafeHook::WriteMemory<unsigned char>(0x433D00, 0x56);
					*(unsigned int*)0x51ADE34 &= ~((1 << 31) | (1 << 27));
				}

				if (m_bToggle)
				{
					nowTrans = *trans;
					nowTarget = *target;
					nowUp = *up;
					nowFov = *fov;

					SafeHook::MakeNOP(0xA95E1F, 5, true);
				}
				else
				{
					SafeHook::WriteMemoryRaw(0xA95E1F, (const void*)"\xE8\x1C\x59\x01\x00", 5);
				}

				m_bCutscenePaused = false;
			}
			guard = true;
		}
		else
		{
			guard = false;
		}
	}

	if (!m_bToggle)
		return;

	{
		static bool guard = false;
		if (SHORT down = GetAsyncKeyState(m_Controls[CTRL_CUTSCENE_PAUSE]) & 0x8000; down && !guard)
		{
			m_bCutscenePaused ^= true;
			SafeHook::WriteMemory<unsigned char>(0x433D00, m_bCutscenePaused ? 0xC3 : 0x56);

			((void(__cdecl*)(int))0x450B80)(m_bCutscenePaused); // movie pause, although has no sense to be here
			((void(__thiscall*)(void*, int))0x433AC0)((void*)0x50A4FC4, m_bCutscenePaused); // Pause events

			if (m_bCutscenePaused)
			{
				*(unsigned int*)0x51ADE34 |= (1 << 31) | (1 << 27); // STP_OBJ | STP_ESP, stop objects and effects
				((void(__cdecl*)())0x514880)(); // Pause sound, bgm and se
				((void(__thiscall*)(void*))0xC31E30)((void*)0x5BB5BA0); // Pause messages(or just subtitles)
			}
			else
			{
				*(unsigned int*)0x51ADE34 &= ~((1 << 31) | (1 << 27)); // removal of STP_OBJ and STP_ESP
				((void(__thiscall*)(void*))0xC31E40)((void*)0x5BB5BA0); // Resume messages(or just subtitles)
				((void(__cdecl*)())0x514890)(); // Resume sound, bgm and se
			}

			guard = true;
		}
		else if (!down)
		{
			guard = false;
		}
	}

	Vector3 d = nowTarget - nowTrans;

	float yaw = atan2f(d.x, d.z);
	float pitch = atan2f(d.y, sqrtf(d.x * d.x + d.z * d.z));

	Vector3 m;

	float speed = m_fSpeed;
	if (GetAsyncKeyState(m_Controls[CTRL_TURBO_MOVE]) & 0x8000)
		speed = m_fTurboSpeed;

	if (GetAsyncKeyState(m_Controls[CTRL_FORWARD]) & 0x8000)
	{
		m.x += cosf(pitch) * sinf(yaw);
		m.y += sinf(pitch);
		m.z += cosf(pitch) * cosf(yaw);
	}
	else if (GetAsyncKeyState(m_Controls[CTRL_BACKWARD]) & 0x8000)
	{
		m.x -= cosf(pitch) * sinf(yaw);
		m.y -= sinf(pitch);
		m.z -= cosf(pitch) * cosf(yaw);
	}

	if (GetAsyncKeyState(m_Controls[CTRL_LEFT]) & 0x8000)
	{
		m.x -= sinf(yaw - float(M_PI / 2.0));
		m.z -= cosf(yaw - float(M_PI / 2.0));
	}
	else if (GetAsyncKeyState(m_Controls[CTRL_RIGHT]) & 0x8000)
	{
		m.x += sinf(yaw - float(M_PI / 2.0));
		m.z += cosf(yaw - float(M_PI / 2.0));
	}

	if (GetAsyncKeyState(m_Controls[CTRL_MOVE_UP]) & 0x8000)
		m.y += speed;
	else if (GetAsyncKeyState(m_Controls[CTRL_MOVE_DOWN]) & 0x8000)
		m.y -= speed;

	float fovStep = 0.5f * (nowFov / 90.0f);
	if (fovStep < 0.01f) fovStep = 0.01f;

	if (GetAsyncKeyState(m_Controls[CTRL_FOV_UP]))
		nowFov += fovStep;
	else if (GetAsyncKeyState(m_Controls[CTRL_FOV_DOWN]))
		nowFov -= fovStep;

	nowTrans += m * speed;

	// clamping to >= 10.0f and <= 150.0f degrees
	nowFov = float(nowFov < DEG_TO_RAD(150.0f) ? (nowFov > DEG_TO_RAD(10.0f) ? nowFov : DEG_TO_RAD(10.0f)) : DEG_TO_RAD(150.0f));

	if (!m_bUseMouseForLook)
	{
		if (GetAsyncKeyState(m_Controls[CTRL_LOOK_LEFT]) & 0x8000)
			yaw += m_fLookSpeed * float(nowFov < DEG_TO_RAD(90.f) ? sinf(nowFov) : nowFov / DEG_TO_RAD(90.0f));
		else if (GetAsyncKeyState(m_Controls[CTRL_LOOK_RIGHT]) & 0x8000)
			yaw -= m_fLookSpeed * float(nowFov < DEG_TO_RAD(90.f) ? sinf(nowFov) : nowFov / DEG_TO_RAD(90.0f));

		if (GetAsyncKeyState(m_Controls[CTRL_LOOK_UP]) & 0x8000)
			pitch += m_fLookPitchSpeed * float(nowFov < DEG_TO_RAD(90.f) ? sinf(nowFov) : nowFov / DEG_TO_RAD(90.0f));
		else if (GetAsyncKeyState(m_Controls[CTRL_LOOK_DOWN]) & 0x8000)
			pitch -= m_fLookPitchSpeed * float(nowFov < DEG_TO_RAD(90.f) ? sinf(nowFov) : nowFov / DEG_TO_RAD(90.0f));
	}
	else
	{
		float (&deltas)[2] = *(float(*)[2])0x5ACBF50; // mouse deltas

		if (deltas[0] != 0.0f)
			yaw -= (deltas[0] / 1000.f) * m_fLookSpeed * float(nowFov < DEG_TO_RAD(90.f) ? sinf(nowFov) : nowFov / DEG_TO_RAD(90.0f));

		if (deltas[1] != 0.0f)
			pitch -= (deltas[1] / 1000.f) * m_fLookPitchSpeed * float(nowFov < DEG_TO_RAD(90.f) ? sinf(nowFov) : nowFov / DEG_TO_RAD(90.0f));
	}

	if (yaw > M_PI)
		yaw -= (float)(M_PI * 2.0f);
	else if (yaw < -M_PI)
		yaw += (float)(M_PI * 2.0f);

	if (pitch > DEG_TO_RAD(89.0f))
		pitch = (float)DEG_TO_RAD(89.0f);
	else if (pitch < -DEG_TO_RAD(89.0f))
		pitch = -(float)DEG_TO_RAD(89.0f);

	nowTarget.x = nowTrans.x + cosf(pitch) * sinf(yaw);
	nowTarget.y = nowTrans.y + sinf(pitch);
	nowTarget.z = nowTrans.z + cosf(pitch) * cosf(yaw);

	*target = nowTarget;
	*trans = nowTrans;
	*up = nowUp;
	*fov = nowFov;
}

void FreeCamera::Init()
{
	// lazy init, only when enabled, to avoid unnecessary hooks and memory writes

	if (!m_bEnabled)
	{
		SafeHook::WriteMemory<unsigned char>(0xA95E2E, 0x75);
		SafeHook::WriteMemoryRaw(0xA95E1F, (const void*)"\xE8\x1C\x59\x01\x00", 5);
		SafeHook::WriteMemoryRaw(0x4AD510, (const void*)"\x51\x56\x8B\xF1\x83\x7E", 6);

		if (m_bToggle && m_bCutscenePaused)
		{
			((void(__thiscall*)(void*))0xC31E40)((void*)0x5BB5BA0);
			((void(__cdecl*)())0x514890)();
			((void(__cdecl*)(int))0x450B80)(0);
			((void(__thiscall*)(void*, int))0x433AC0)((void*)0x50A4FC4, 0);

			SafeHook::WriteMemory<unsigned char>(0x433D00, 0x56);
			*(unsigned int*)0x51ADE34 &= ~((1 << 31) | (1 << 27));
		}

		m_bToggle = false;
		m_bCutscenePaused = false;
	}
	else
	{
		static SafeHook::MidAsmHook hook(0xA95E55, [](SafeHook::CTX& ctx)
		{
			void* pCamera = (void*)ctx.esi.i32;

			FreeCamera::get().Update(pCamera);
		});
	}
}