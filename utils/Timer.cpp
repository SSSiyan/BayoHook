#include "Timer.hpp"

namespace utils {

	void Timer::start() {
		m_active = true;
		m_time = fseconds{ 0 };
	}

	void Timer::tick(fmilliseconds& dt) {
		if (!m_active) { return; }
		if (m_time.count() >= m_duration) {
			m_callback();
			m_active = false;
		}
		m_time += dt;
	}
};