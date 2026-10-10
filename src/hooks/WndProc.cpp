#include <pch.h>
#include <base.h>
#include "GameHook.hpp"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Base::Hooks::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
/*
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

		case VK_F1:
			if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl)) {
				GameHook::EasySpawnEntityFromHotkey(0x20000, 1, 0); // affinity, spear
			}
			else if (ImGui::IsKeyDown(ImGuiKey_LeftShift)) {
				GameHook::EasySpawnEntityFromHotkey(0x20080, 0, 0); // joy
			}
			else {
				GameHook::enemyHPNoDamage_toggle = !GameHook::enemyHPNoDamage_toggle;
				GameHook::DisableKilling(GameHook::enemyHPNoDamage_toggle);
				if (GameHook::enemyHPNoDamage_toggle && GameHook::enemyHPOneHitKill_toggle) {
					GameHook::enemyHPOneHitKill_toggle = false;
					GameHook::DisplayMessageText("Enemy One Hit Kill", GameHook::enemyHPOneHitKill_toggle);
				}
				GameHook::DisplayMessageText("Enemy Takes No Damage", GameHook::enemyHPNoDamage_toggle);
			}
			break;
		case VK_F2:
			if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl)) {
				GameHook::EasySpawnEntityFromHotkey(0x20000, 2, 0); // affinity, trumpet
			}
			else if (ImGui::IsKeyDown(ImGuiKey_LeftShift)) {
				GameHook::EasySpawnEntityFromHotkey(0x20040, 0, 0); // grace
			}
			else {
				GameHook::damageReceivedMultiplierNoDamage_toggle = !GameHook::damageReceivedMultiplierNoDamage_toggle;
				GameHook::DisplayMessageText("Player Takes No Damage", GameHook::damageReceivedMultiplierNoDamage_toggle);
			}
			break;
		case VK_F3:
			if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl)) {
				GameHook::EasySpawnEntityFromHotkey(0x20000, 4, 0); // applaud, spear
			}
			else if (ImGui::IsKeyDown(ImGuiKey_LeftShift)) {
				GameHook::EasySpawnEntityFromHotkey(0x20041, 0, 0); // glory
			}
			else {
				GameHook::enemyHPOneHitKill_toggle = !GameHook::enemyHPOneHitKill_toggle;
				if (GameHook::enemyHPOneHitKill_toggle && GameHook::enemyHPNoDamage_toggle) {
					GameHook::enemyHPNoDamage_toggle = false;
					GameHook::DisableKilling(GameHook::enemyHPNoDamage_toggle);
					GameHook::DisplayMessageText("Enemy Takes No Damage", GameHook::enemyHPNoDamage_toggle);
				}
				GameHook::DisplayMessageText("Enemy One Hit Kill", GameHook::enemyHPOneHitKill_toggle);
			}
			break;
		case VK_F4:
			if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl)) {
				GameHook::EasySpawnEntityFromHotkey(0x20000, 5, 0); // applaud, greatsword
			}
			else if (ImGui::IsKeyDown(ImGuiKey_LeftShift)) {
				GameHook::EasySpawnEntityFromHotkey(0x20042, 0, 0); // gracious
			}
			else {
				GameHook::infJumps_toggle = !GameHook::infJumps_toggle;
				GameHook::InfJumps(GameHook::infJumps_toggle);
				GameHook::DisplayMessageText("Infinite Jumps", GameHook::infJumps_toggle);
			}
			break;
		case VK_F5:
			if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl)) {
				GameHook::EasySpawnEntityFromHotkey(0x20030, 0, 0); // enchant
			}
			else if (ImGui::IsKeyDown(ImGuiKey_LeftShift)) {
				GameHook::EasySpawnEntityFromHotkey(0x20043, 0, 0); // glorious
			}
			break;
		case VK_F6:
			if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl)) {
				GameHook::EasySpawnEntityFromHotkey(0x20004, 0, 0); // ardor, greatsword
			}
			else if (ImGui::IsKeyDown(ImGuiKey_LeftShift)) {
				GameHook::EasySpawnEntityFromHotkey(0x200A0, 0, 0); // kinship
			}
			break;
		case VK_F7:
			if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl)) {
				GameHook::EasySpawnEntityFromHotkey(0x20004, 1, 0); // ardor, axe
			}
			else if (ImGui::IsKeyDown(ImGuiKey_LeftShift)) {
				GameHook::EasySpawnEntityFromHotkey(0x20074, 0, 0); // beloved (silver)
			}
			break;
		case VK_F8:
			if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl)) {
				GameHook::EasySpawnEntityFromHotkey(0x20002, 0, 0); // affinity, laser
			}
			else if (ImGui::IsKeyDown(ImGuiKey_LeftShift)) {
				GameHook::EasySpawnEntityFromHotkey(0x20090, 0, 0); // golem
			}
			break;
		case VK_F9:
			if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl)) {
				GameHook::EasySpawnEntityFromHotkey(0x20050, 0, 0); // fearless
			}
			else if (ImGui::IsKeyDown(ImGuiKey_LeftShift)) {
				GameHook::EasySpawnEntityFromHotkey(0x200B0, 0, 0); // fortitudo (green)
			}
			break;
		case VK_F10:
			if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl)) {
				GameHook::EasySpawnEntityFromHotkey(0x20051, 0, 0); // fairness
			}
			else if (ImGui::IsKeyDown(ImGuiKey_LeftShift)) {
				GameHook::EasySpawnEntityFromHotkey(0x20500, 0, 0); // balder
			}
			break;
		case VK_F11:
			if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl)) {
				GameHook::EasySpawnEntityFromHotkey(0x20060, 0, 0); // harmony
			}
			else if (ImGui::IsKeyDown(ImGuiKey_LeftShift)) {
				GameHook::EasySpawnEntityFromHotkey(0x21002, 0, 0); // jeanne formal A
			}
			break;
		case VK_F12:
			if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl)) {
				GameHook::EasySpawnEntityFromHotkey(0x20073, 0, 0); // brave
			}
			else if (ImGui::IsKeyDown(ImGuiKey_LeftShift)) {
				GameHook::EasySpawnEntityFromHotkey(0x21003, 0, 0); // bayonetta default
			}
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
		}
	}
*/
	ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
	return CallWindowProc(Data::oWndProc, hWnd, uMsg, wParam, lParam);
}
