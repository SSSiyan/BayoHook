#pragma once
#include <Windows.h>
#include "../utils/config.hpp"

class FreeCamera
{
public:
	bool m_bEnabled;
	bool m_bToggle;
	bool m_bCutscenePaused;
	bool m_bUseMouseForLook;

	enum eCtrlId
	{
		CTRL_TOGGLE,
		CTRL_CUTSCENE_PAUSE,

		CTRL_FORWARD,
		CTRL_BACKWARD,
		CTRL_LEFT,
		CTRL_RIGHT,

		CTRL_LOOK_LEFT,
		CTRL_LOOK_RIGHT,
		CTRL_LOOK_UP,
		CTRL_LOOK_DOWN,

		CTRL_FOV_UP,
		CTRL_FOV_DOWN,

		CTRL_TURBO_MOVE,

		CTRL_MOVE_UP,
		CTRL_MOVE_DOWN,

		CTRL_MAX
	};

	float m_fSpeed = 0.2f;
	float m_fTurboSpeed = 1.0f;
	
	float m_fLookSpeed = 0.05f;
	float m_fLookPitchSpeed = 0.03f;

	int m_Controls[CTRL_MAX] = { VK_BACK, 'P', 'I', 'K', 'J', 'L', VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN, 'Y', 'H', VK_RSHIFT, VK_OEM_2, VK_RCONTROL };

	FreeCamera()
	{
		m_bEnabled = m_bToggle = m_bUseMouseForLook = m_bCutscenePaused = false;
	}

	void Save(utils::Config& cfg);
	void Load(const utils::Config& cfg);

	void Update(void *pCamera);

	// On config load or on enable
	void Init();

	static inline FreeCamera& get()
	{
		static FreeCamera c;

		return c;
	}
};