#ifndef TIMER_H_
#define TIMER_H_

namespace game {

    // A class implementing a simple timer
    class Timer {

        public:
            // Constructor and destructor
            Timer();

            // Start the timer now: end time given in seconds
            void Start(float end_time); 

            // Check if timer has finished
            bool Finished();
			// Get runnning status
            bool Running() const;
            // Get amount of time running
			double get_run_time() const;
			// Get target time
			double get_target() const;

        private:
			// Time when the timer started
			double start_time_;
			// Time when the timer should end
			double end_time_;
			// Bool to check if the timer has been checked
			bool checked;
			// Bool to check if the timer is running
			bool running;

    }; // class Timer

} // namespace game

#endif // TIMER_H_
