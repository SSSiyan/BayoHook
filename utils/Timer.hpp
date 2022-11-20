#pragma once
#include <chrono>
#include <functional>
#include <deque>

// chrono for humans
using fmilliseconds = std::chrono::duration<float, std::milli>;
using fseconds = std::chrono::duration<float>;
using fminutes = std::chrono::duration<float, std::ratio<60>>;
using fhours = std::chrono::duration<float, std::ratio<3600>>;
using fdays = std::chrono::duration<float, std::ratio<86400>>;
using fweeks = std::chrono::duration<float, std::ratio<604800>>;
using fmonths = std::chrono::duration<float, std::ratio<2629746>>;
using fyears = std::chrono::duration<float, std::ratio<31556952>>;

namespace utils {
	// TODO(): this is probably horrible by bideogame standards
	// replace std::function with c function pointers or something
	struct Timer {

		Timer(float seconds, std::function<void()> callback)
			: m_duration(seconds), m_callback(callback) {
		}
		Timer(Timer&& other) = delete;

		bool     m_active{ false };
		float    m_duration;
		fseconds m_time { 0 };

		std::function<void()> m_callback;

		void start();

		void tick(fmilliseconds& dt);
	};
};