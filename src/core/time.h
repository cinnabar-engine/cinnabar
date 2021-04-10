#pragma once

namespace ce {
	class Time {
	 private:
		unsigned long m_now, m_last;
		double m_dt, m_fps;

	 public:
		Time();
		~Time();

		void recalculate(bool dt = true, bool fps = true);
		void update(bool dt = true, bool fps = true);
		void waitUntilDelta(double dt);

		double getDeltaTime() { return m_dt; }
		double getFPS() { return m_fps; };
	};
}
