#include "Timer.h"

Timer::Timer(time_unit units) {
	running = false;
	iters = 0;
	sum = 0.0;
	this->units = units;
	track_average = true;
}

/*Units are used for the timeout value. All other units are specified by the user*/
void Timer::set_units(time_unit units) { this->units = units; }

/*Start the timer*/
void Timer::start() {
	running = true;
	start_time = std::chrono::high_resolution_clock::now();
}

/*Stop the timer. If track_avarege is set to true, add the elapsed time to the average*/
void Timer::stop() {
	running = false;
	stop_time = std::chrono::high_resolution_clock::now();
	iters++;
	sum += get_elapsed_time();
}

/*Return whether or not the timer is currently running*/
bool Timer::is_running() { return running; }

/*If timer running:
	return elapsed time since timer was started
  else (timer not running):
	return elaposed time between start and stop times*/
timer_val Timer::get_elapsed_time() {
	if (running) return timer_val{ std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - start_time).count() };
	else return timer_val{ std::chrono::duration_cast<std::chrono::duration<double>>(stop_time - start_time).count() };
}

/*Set the timeout value. This allows the 'expired()' method to be called.
If the elapse time of the timer is greater than 'timeout', 'expired()' will
return TRUE, otherwise FALSE*/
/*Need to convert the timeout value to SECONDS as that is what the high_resolution_clock is in*/
void Timer::set_timeout(const double timeout) {	
	switch (this->units) {
	case seconds:
		this->timeout = timeout;
		break;
	case milliseconds:
		this->timeout = timeout / 1000.0;
		break;
	case microseconds:
		this->timeout = timeout / 1000000.0;
		break;
	case nanoseconds:
		this->timeout = timeout / 1000000000.0;
		break;
	}
}

/*Return the timeout value*/
timer_val Timer::get_timeout() { return timer_val{ this->timeout }; }

/*Check if the current elapsed time is greater than the timeout specified.
If no timeout specified, return FALSE
If elapsed time is less than timeout, return FALSE
If elapsed time is greater than timeout, return TRUE*/
bool Timer::expired() {
	if (timeout == -1) return false;
	else {
		if (get_elapsed_time() > timeout) return true;
		else return false;
	}
}

/*Start averaging elapsed time
If averaging was already true (default), no change
Otherwise, start average elapsed times beginning with the next time stop() is called*/
void Timer::start_average() { track_average = true; }

/*Stop calculating average elapsed time*/
void Timer::stop_average() { track_average = false; }

/*Reset average to 0*/
void Timer::reset_average() { sum = 0; iters = 0; }

/*Return whether or not the average is being calculated*/
bool Timer::is_averaging() { return track_average; }

/*Add currently elapsed time to average without stopping timer. If track_average is false, nothing happens*/
void Timer::add_time_to_average() { if(track_average) sum += get_elapsed_time(); }

/*Returns the average elapsed time
If iters is 0 (timer hasn't been stopped with track_average == true OR add_time_to_average() has not been called), method returns 0*/
timer_val Timer::average() {
	if (iters > 0) return timer_val{ sum / iters };
	else return timer_val{ 0.0 };
}
