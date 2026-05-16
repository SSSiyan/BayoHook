#pragma once

#include <array>
#include <vector>
#include <cstdint>
#include <memory>
#include <string>
#include "../utils/config.hpp"

constexpr auto _XUSER_MAX_COUNT = 4;

namespace utility {
    class Config;
}

enum XIBtn : uint32_t {
    DPAD_UP,
    DPAD_DOWN,
    DPAD_LEFT,
    DPAD_RIGHT,
    START,
    BACK,
    LEFT_THUMB,
    RIGHT_THUMB,
    LEFT_SHOULDER,
    RIGHT_SHOULDER,
    A,
    B,
    X,
    Y,
    LEFT_TRIGGER,
    RIGHT_TRIGGER,
    XIBTN_MAX
};

namespace utility
{
    namespace gamepads {
        void set_gamepad_callbacks();
    } // gamepads


    class Input
    {
    public:


        void update();

        bool is_down(int vkey, bool is_gamepad) const;
        bool went_down(int vkey, bool is_gamepad) const;
        bool went_up(int vkey, bool is_gamepad) const;

        auto get_keys_size() const { return m_status.size(); };
        auto get_btns_size() const { return m_gpad_status.size(); };


    private:

        enum class InputState
        {
            IDLE,
            WENT_DOWN,
            WENT_UP
        };

        struct InputStatus
        {
            bool is_down = false;
            InputState state = InputState::IDLE;
        };

        std::array<InputStatus, 256> m_status = { 0 };
        std::array<InputStatus, XIBtn::XIBTN_MAX> m_gpad_status = { 0 };

        void update_gamepads();
        void get_state(bool keydown, InputStatus& current_status);
    };

    struct Hotkey {

        enum HkType {
            Keyboard,
            Gamepad
        };

        Hotkey() = delete;
        Hotkey(const Hotkey& other) = delete;
        Hotkey(Hotkey&& other) = delete;

#if 0
        // single overload so you dont have to pass an std::vector<uint32_t> verbose shit for a 1 button
        Hotkey(Input::Binds default_key, const char* description, const char* config_entry, HkType type) :
            m_default_keys(std::vector<uint32_t>{default_key}),
            m_description(description),
            m_config_entry(config_entry),
            m_is_gamepad(type == HkType::Gamepad) {
        }
#endif
        // key combo 
        Hotkey(std::vector<uint32_t> default_keys, const char* description, const char* config_entry, HkType type) :
            m_default_keys(std::move(default_keys)),
            m_description(description),
            m_config_entry(config_entry),
            m_is_gamepad(type == HkType::Gamepad) {
        }


        std::vector<uint32_t> m_default_keys;

        std::string m_description;
        std::string m_config_entry;

        bool m_setting = false;
        bool m_is_gamepad = false;

        char m_tmp_buf[2]{ 0 };

        // this could have been a fixed array but someone will complain
        // they cant bind adagio for strings and organ in G minor
        std::vector<uint32_t> m_binds;

        const char* hotkey_name(int hotkey);
        void draw(utility::Input& input);
        bool check(utility::Input& input);


        void on_config_load(const utils::Config& cfg);
        void on_config_save(utils::Config& cfg);
    };

    void create_keyboard_hotkey(std::vector<std::unique_ptr<utility::Hotkey>>& mod_hotkeys, std::vector<uint32_t>&& default_keys, const char* desc, const char* cfg_entry);
    void create_gamepad_hotkey(std::vector<std::unique_ptr<utility::Hotkey>>& mod_hotkeys, std::vector<uint32_t>&& default_keys, const char* desc, const char* cfg_entry);

    std::unique_ptr<utility::Hotkey> create_keyboard_hotkey(std::vector<uint32_t>&& default_keys, const char* desc, const char* cfg_entry);
    std::unique_ptr<utility::Hotkey> create_gamepad_hotkey(std::vector<uint32_t>&& default_keys, const char* desc, const char* cfg_entry);
} // utility
