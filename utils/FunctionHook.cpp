#include "minhook/include/MinHook.h"

#include "FunctionHook.hpp"

using namespace std;

bool g_is_min_hook_initialized{ false };

FunctionHook::FunctionHook(Address target, Address destination)
    : m_target{ 0 },
    m_destination{ 0 },
    m_original{ 0 }
{
    // Initialize MinHook if it hasn't been already.
    if (!g_is_min_hook_initialized && MH_Initialize() == MH_OK) {
        g_is_min_hook_initialized = true;
    }

    // Create the hook. Call create afterwards to prevent race conditions accessing FunctionHook before it leaves its constructor.
    if (MH_CreateHook(target.as<LPVOID>(), destination.as<LPVOID>(), (LPVOID*)&m_original) == MH_OK) {
        m_target = target;
        m_destination = destination;
    }
}

FunctionHook::~FunctionHook() {
    remove();
}

bool FunctionHook::create() {
    if (m_target == 0 || m_destination == 0 || m_original == 0) {
        return false;
    }

    if (MH_EnableHook((LPVOID)m_target) != MH_OK) {
        m_original = 0;
        m_destination = 0;
        m_target = 0;
        return false;
    }
    return true;
}

bool FunctionHook::disable() {
	if (!m_original) {
		return true;
	}
	if (MH_DisableHook((LPVOID)m_target) != MH_OK) {
		return false;
	}
	return true;
}

bool FunctionHook::remove() {
    // Don't try to remove invalid hooks.
    if (m_original == 0) {
        return true;
    }

    // Disable then remove the hook.
    if (MH_DisableHook((LPVOID)m_target) != MH_OK ||
        MH_RemoveHook((LPVOID)m_target) != MH_OK) {
        return false;
    }

    // Invalidate the members.
    m_target = 0;
    m_destination = 0;
    m_original = 0;

    return true;
}