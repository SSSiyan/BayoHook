#pragma once
#include <Windows.h>
#include <functional>
#include <vector>
#include <memory>
#include "../../utils/FunctionHook.hpp"

class XInputHook {
public:
    typedef void (WINAPI *on_get_state)(DWORD, void* p_state);

    XInputHook() = default;
    virtual ~XInputHook();

    // no copies 
    XInputHook(const XInputHook&) = delete;
    // no copy assigment
    XInputHook& operator=(const XInputHook&) = delete;
    // no moves
    XInputHook(XInputHook&&) noexcept = delete;
    // no move assigment
    XInputHook& operator=(XInputHook&&) noexcept = delete;

    bool hook();
    bool unhook();

    void add_on_get_state_fptr(on_get_state);

protected:

    bool m_hooked = false;

    std::vector<on_get_state> m_ogs_pointers{};

    std::unique_ptr<FunctionHook> m_get_state_hook;
    static DWORD WINAPI xinput_get_state(DWORD dw_user_index, void* p_state);
};

extern XInputHook* g_xinput_hook;
