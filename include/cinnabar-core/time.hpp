#pragma once

namespace ce {
	class Time {
	 public:
		/**
	  * @brief Construct a new Time object
	  * 
	  */
		Time();
		~Time();
		/**
		 * @brief Calculates the FPS and DeltaTime
		 * 
		 * @param dt weather to calculate the DeltaTime
		 * @param fps weather to calculate the FPS
		 */
		void recalculate(bool dt = true, bool fps = true);

		/**
		 * @brief Updates the FPS and DeltaTime and makes a GameTick
		 * 
		 * @param dt weather to calculate the DeltaTime
		 * @param fps weather to calculate the FPS
		 */
		void update(bool dt = true, bool fps = true);

		/**
		 * @brief Wait until delta reches a certain values
		 * 
		 * @param dt value to wait for
		 */
		void waitUntilDelta(double dt);

		/**
		 * @brief Get the Delta Time
		 * 
		 * @return double 
		 */
		double getDeltaTime() { return m_dt; }

		/**
		 * @brief Get the FPS
		 * 
		 * @return double 
		 */
		double getFPS() { return m_fps; };

	 private:
		unsigned long m_now, m_last;
		double m_dt, m_fps;
	};
}
