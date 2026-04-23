#include <pch.h>
#include <base.h>
#include "gamehook.hpp"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Base::Hooks::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
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
				GameHook::disableClicking_toggle = true;
				GameHook::DisableClicking(GameHook::disableClicking_toggle);
			}
			else {
				ImGui::GetIO().MouseDrawCursor = false;
				GameHook::disableClicking_toggle = false;
				GameHook::DisableClicking(GameHook::disableClicking_toggle);
			}
			break;

#ifndef SPEEDRUN_BUILD
		case VK_F1:
			GameHook::enemyHPNoDamage_toggle = !GameHook::enemyHPNoDamage_toggle;
			GameHook::DisableKilling(GameHook::enemyHPNoDamage_toggle);
			if (GameHook::enemyHPNoDamage_toggle)
				GameHook::enemyHPOneHitKill_toggle = false;
			GameHook::DisplayMessageText("Enemy Takes No Damage ", GameHook::enemyHPNoDamage_toggle);
			break;
		case VK_F2:
			GameHook::damageReceivedMultiplierNoDamage_toggle = !GameHook::damageReceivedMultiplierNoDamage_toggle;
			GameHook::DisplayMessageText("Player Takes No Damage ", GameHook::damageReceivedMultiplierNoDamage_toggle);
			break;
		case VK_F3:
			GameHook::enemyHPOneHitKill_toggle = !GameHook::enemyHPOneHitKill_toggle;
			if (GameHook::enemyHPOneHitKill_toggle) {
				GameHook::enemyHPNoDamage_toggle = false;
				GameHook::DisableKilling(GameHook::enemyHPNoDamage_toggle);
			}
			GameHook::DisplayMessageText("Enemy One Hit Kill ", GameHook::enemyHPOneHitKill_toggle);
			break;
		case VK_F4:
			GameHook::infJumps_toggle = !GameHook::infJumps_toggle;
			GameHook::InfJumps(GameHook::infJumps_toggle);
			GameHook::DisplayMessageText("Infinite Jumps ", GameHook::infJumps_toggle);
			break;
		case VK_F5:
			GameHook::noClip_toggle = !GameHook::noClip_toggle;
			GameHook::NoClip(GameHook::noClip_toggle);
			GameHook::DisplayMessageText("No Clip ", GameHook::noClip_toggle);
			break;
		case VK_F6:
			GameHook::lessClothes_toggle = !GameHook::lessClothes_toggle;
			GameHook::LessClothes(GameHook::lessClothes_toggle);
			GameHook::DisplayMessageText("Less Clothes ", GameHook::lessClothes_toggle);
			break;
		case VK_HOME:
			if (GameHook::saveStatesHotkeys_toggle) {
				GameHook::SaveStates_SaveState();
			}
			break;
		case VK_END:
			if (GameHook::saveStatesHotkeys_toggle) {
				GameHook::SaveStates_LoadState();
			}
			break;
#endif
		}
	}
	ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
	return CallWindowProc(Data::oWndProc, hWnd, uMsg, wParam, lParam);
}
