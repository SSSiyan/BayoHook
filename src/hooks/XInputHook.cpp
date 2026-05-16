#include "XInputHook.hpp"
#include "XInput.h"
#include "Windows.h"
#include <assert.h>

XInputHook* g_xinput_hook { nullptr };

XInputHook::~XInputHook() {
    //assert(m_get_state_hook);
    unhook();
}

bool XInputHook::hook() {
    //spdlog::info("Hooking XInput");

    g_xinput_hook = this;

    // get address of XInputGetState
    // game uses this specific version
    HMODULE h_xinput = GetModuleHandleA("XINPUT1_3");
    assert(h_xinput != NULL);

    FARPROC ptr_xinput_get_state = GetProcAddress(h_xinput, "XInputGetState");
    //assert(ptr_xinput_get_state != NULL);

    m_get_state_hook = std::make_unique<FunctionHook>( ptr_xinput_get_state, xinput_get_state );
    m_hooked = m_get_state_hook->create();

    return m_hooked;
}

bool XInputHook::unhook() {
    if (!m_hooked) {
        //spdlog::info("[XInputHook] trying to unhook while not hooked!");
        return true;
    }
    if (m_get_state_hook->remove()) {
        m_hooked = false;
        return true;
    }
    return false;
}

void XInputHook::add_on_get_state_fptr(on_get_state ogs) {
    m_ogs_pointers.push_back(ogs);
}

DWORD WINAPI XInputHook::xinput_get_state(DWORD dw_user_index, void* p_state) {
    if (!g_xinput_hook) { return ERROR_SUCCESS; }

    // call original
    auto get_state_fn = g_xinput_hook->m_get_state_hook->get_original<decltype(XInputHook::xinput_get_state)>();
    DWORD retval      = get_state_fn(dw_user_index, p_state);
    if (retval != ERROR_SUCCESS) {
        return retval;
    }
    // call into our function pointers
    for (auto ogs_pointer : g_xinput_hook->m_ogs_pointers) {
        ogs_pointer(dw_user_index, p_state);
    }
    return retval;
}
