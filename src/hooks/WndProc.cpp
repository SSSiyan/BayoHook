#include <pch.h>
#include <base.h>
#include "gamehook.hpp"
#include <windows.h>
#include <XInput.h>

const char* GameHook::previousWeaponName = "Scarborough Fair";
const char* GameHook::previousWeaponName2 = "Scarborough Fair";

int& weaponA1Value = *(int*)GameHook::WeaponA1Address;
int& weaponA2Value = *(int*)GameHook::WeaponA2Address;
int& weaponB1Value = *(int*)GameHook::WeaponB1Address;
int& weaponB2Value = *(int*)GameHook::WeaponB2Address;
int& weaponSetActive = *(int*)GameHook::WeaponActiveSet;
int& weaponSetPicked = *(int*)GameHook::WeaponPickedSet;

int GameHook::weaponA1 = weaponA1Value;
int GameHook::weaponA2 = weaponA2Value;
int GameHook::weaponB1 = weaponB1Value;
int GameHook::weaponB2 = weaponB2Value;

int GameHook::currentSet = -1;


bool GameHook::leftPressed = false;
bool GameHook::rightPressed = false;
bool GameHook::upPressed = false;
bool GameHook::downPressed = false;

int GameHook::messageTimer = 200;
int GameHook::switchLimit = 0;



int GameHook::previousMoveWrite = -1;

int maxLimit = 90;


float GameHook::animFrame = 0;


extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Base::Hooks::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if(uMsg == WM_KEYDOWN || uMsg == WM_KEYUP)
		Data::WmKeys[wParam] = uMsg;

	if (uMsg == WM_KEYDOWN)
	{
		switch (wParam)
		{
		case VK_DELETE:
			Data::ShowMenu = !Data::ShowMenu;
			if (Data::ShowMenu) {
				ImGui::GetIO().MouseDrawCursor = true;
				GameHook::disableClicking_toggle = true; // bayo
				GameHook::DisableClicking(GameHook::disableClicking_toggle); // bayo
			}
			else {
				ImGui::GetIO().MouseDrawCursor = false;
				GameHook::disableClicking_toggle = false; // bayo
				GameHook::DisableClicking(GameHook::disableClicking_toggle); // bayo
			}
			break;
		case VK_F1:
			GameHook::enemyHP_no_damage_toggle = !GameHook::enemyHP_no_damage_toggle;
			GameHook::DisableKilling(GameHook::enemyHP_no_damage_toggle);
			if (GameHook::enemyHP_no_damage_toggle)
				GameHook::enemyHP_one_hit_kill_toggle = false;
			GameHook::showMessageTimerF1 = GameHook::messageTimer;
			break;
		case VK_F2:
			GameHook::takeNoDamage_toggle = !GameHook::takeNoDamage_toggle;
			GameHook::TakeNoDamage(GameHook::takeNoDamage_toggle);
			GameHook::showMessageTimerF2 = GameHook::messageTimer;
			break;
		case VK_F3:
			GameHook::enemyHP_one_hit_kill_toggle = !GameHook::enemyHP_one_hit_kill_toggle;
			if (GameHook::enemyHP_one_hit_kill_toggle) {
				GameHook::enemyHP_no_damage_toggle = false;
				GameHook::DisableKilling(GameHook::enemyHP_no_damage_toggle);
			}
			GameHook::showMessageTimerF3 = GameHook::messageTimer;
			break;
		case VK_F4:
			GameHook::infJumps_toggle = !GameHook::infJumps_toggle;
			GameHook::InfJumps(GameHook::infJumps_toggle);
			GameHook::showMessageTimerF4 = GameHook::messageTimer;
			break;
		case VK_F5:
			GameHook::noClip_toggle = !GameHook::noClip_toggle;
			GameHook::NoClip(GameHook::noClip_toggle);
			GameHook::showMessageTimerF5 = GameHook::messageTimer;
			break;
		case VK_HOME:
			GameHook::SaveStates_SaveState();
			break;
		case VK_END:
			GameHook::SaveStates_LoadState();
			break;
		}
	}
	ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);


	if (GameHook::weaponswap_toggle)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));
		
		if (GameHook::moveIDSwap_toggle == true)
		{
			uintptr_t actorPlayable = *(uintptr_t*)GameHook::playerPointerAddress;
			if (actorPlayable)
			{
				float& playerAnimFrame = *(float*)(actorPlayable + 0x3E4);
				if (playerAnimFrame > 10)
				{
					GameHook::moveIDSwap_toggle = false;
					GameHook::testMoveSwap = -1;
					GameHook::animFrame = 0;
				}
				else if (playerAnimFrame == 1)
				{
					playerAnimFrame = GameHook::animFrame + 1;
				}
				else
				{
					GameHook::animFrame = playerAnimFrame;
				}
			}
		}

		if (GameHook::switchLimit > 0) GameHook::switchLimit--;

		if (XInputGetState(0, &state) == ERROR_SUCCESS)
		{
			if (weaponSetPicked == 0)
			{
				GameHook::switchHandsLeft(&GameHook::weaponB1, state, 1);
				GameHook::switchHandsRight(&GameHook::weaponB1, state, 1);
				GameHook::switchLegsUp(&GameHook::weaponB2, state, 1);
				GameHook::switchLegsDown(&GameHook::weaponB2, state, 1);
			}
			else if (weaponSetPicked == 1)
			{
				GameHook::switchHandsLeft(&GameHook::weaponA1, state, 0);
				GameHook::switchHandsRight(&GameHook::weaponA1, state, 0);
				GameHook::switchLegsUp(&GameHook::weaponA2, state, 0);
				GameHook::switchLegsDown(&GameHook::weaponA2, state, 0);
			}
		}


		if (weaponSetPicked == GameHook::currentSet)
		{
			uintptr_t actorPlayable = *(uintptr_t*)GameHook::playerPointerAddress;
			if (actorPlayable)
			{
				int& playerMoveID = *(int*)(actorPlayable + 0x34C);
				int& playerMovePart = *(int*)(actorPlayable + 0x350);
				int& playerMoveSomething = *(int*)(actorPlayable + 0x354);
				float& playerAnimFrame = *(float*)(actorPlayable + 0x3E4);

				int moveId = playerMoveID;
				//int desiredMove = 116;
				bool ismovezero = playerMoveID == 0;
				int movePart = playerMovePart;
				int moveSomething = playerMoveSomething;
				float animFrame = playerAnimFrame;
				int tempPicked = -1;
				if (GameHook::currentSet == 1)
				{
					tempPicked = 0;
					weaponB1Value = GameHook::currentPair[0];
					weaponB2Value = GameHook::currentPair[1];
				}
				else if (GameHook::currentSet == 0)
				{
					tempPicked = 1;
					weaponA1Value = GameHook::currentPair[0];
					weaponA2Value = GameHook::currentPair[1];

				}

				if (GameHook::currentSet == weaponSetActive)
				{
					//GameHook::_nop((char*)(0x6EDB52F6), 6); // nop move id reset
					if (playerMoveID != 0
						&& playerMoveID != 1
						&& playerMoveID != 6)
					{
						GameHook::moveIDSwap_toggle = true;
						GameHook::testMoveZero = 0;
						GameHook::testMoveSwap = playerMoveID;
						if (playerAnimFrame > 0)
						{
							GameHook::animFrame = playerAnimFrame;
						}
					}
					GameHook::WeaponSwapCaller();

					if (playerMoveID != 0
						&& playerMoveID != 1
						&& playerMoveID != 6)
					{
						GameHook::testMoveSwap = playerMoveID;
						if (playerAnimFrame > 0)
						{
							GameHook::animFrame = playerAnimFrame;
						}
					}
					GameHook::currentSet = -1;
					//playerMoveID = 13;
				}

			}
		}
	}

	return CallWindowProc(Data::oWndProc, hWnd, uMsg, wParam, lParam);
}

void GameHook::switchHandsLeft(int* weapon, XINPUT_STATE state, int cSet)
{
	if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) == 0)
	{
		GameHook::leftPressed = false;
	}

	if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0
		&& GameHook::leftPressed == false)

	{

		GameHook::isCallerCalled = true;
		GameHook::leftPressed = true;
		GameHook::currentPair[0] = GameHook::pairLeft[0];
		GameHook::currentPair[1] = GameHook::pairLeft[1];
		GameHook::currentSet = cSet;
	}
}

void GameHook::switchHandsRight(int* weapon, XINPUT_STATE state, int cSet)
{
	if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) == 0)
	{
		GameHook::rightPressed = false;
	}

	if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0
		&& GameHook::rightPressed == false)

	{

		GameHook::isCallerCalled = true;
		GameHook::rightPressed = true;
		GameHook::currentPair[0] = GameHook::pairRight[0];
		GameHook::currentPair[1] = GameHook::pairRight[1];
		GameHook::currentSet = cSet;
	}
}

void GameHook::switchLegsUp(int* weapon, XINPUT_STATE state, int cSet)
{
	if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) == 0)
	{
		GameHook::upPressed = false;
	}

	if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0
		&& GameHook::upPressed == false)
	{
		GameHook::upPressed = true;
		GameHook::isCallerCalled = true;

		GameHook::currentPair[0] = GameHook::pairUp[0];
		GameHook::currentPair[1] = GameHook::pairUp[1];
		GameHook::currentSet = cSet;
	}

}

void GameHook::switchLegsDown(int* weapon, XINPUT_STATE state, int cSet)
{
	if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) == 0)
	{
		GameHook::downPressed = false;
	}

	if ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0
		&& GameHook::downPressed == false)
	{
		GameHook::isCallerCalled = true;
		GameHook::downPressed = true;
	
		GameHook::currentPair[0] = GameHook::pairDown[0];
		GameHook::currentPair[1] = GameHook::pairDown[1];
		GameHook::currentSet = cSet;
	}

}
