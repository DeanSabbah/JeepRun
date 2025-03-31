#include <GLFW/glfw3.h>
#include <iostream>

#include "timer.h"

namespace game {
	Timer::Timer(){
		start_time_ = 0;
		end_time_ = 0;
		checked = false;
		running = false;
	}

	void Timer::Start(float end_time){
		end_time_ = end_time;
		start_time_ = glfwGetTime();
		end_time_ = end_time;
		checked = false;
		running = true;
	}

	bool Timer::Finished(){
		// Check if the timer has finished, only return true once
		if (glfwGetTime() - start_time_ > end_time_ && !checked) {
			checked = true;
			return true;
			running = false;
		}
		else {
			return false;
		}
	}

	bool Timer::Running() const {
		return running;
	}

	double Timer::get_run_time() const {
		return glfwGetTime() - start_time_;
	}

	double Timer::get_target() const {
		return end_time_;
	}

} // namespace game
