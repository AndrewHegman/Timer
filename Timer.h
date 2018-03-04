#ifndef TIMER_H_
#define TIMER_H_

#include <chrono>

enum time_unit {
	seconds,
	milliseconds,
	microseconds,
	nanoseconds
};

struct timer_val {
	double val;
	operator double() const { return val; }
	double scale(time_unit units) {
		switch (units) {
		case seconds:
			return val;
			break;
		case milliseconds:
			return val * 1000.0f;
			break;
		case microseconds:
			return val * 1000000.0f;
			break;
		case nanoseconds:
			return val * 1000000000.0f;
			break;
		}
	}
};

class Timer {
private:
	std::chrono::high_resolution_clock::time_point start_time;
	std::chrono::high_resolution_clock::time_point stop_time;

	double sum;
	double iters;
	double elapsed_time;
	double timeout;

	bool running;
	bool track_average;
	time_unit units;

public:
	Timer(time_unit units=milliseconds);

	void start();
	void stop();

	void set_units(time_unit units);

	bool is_running();

	timer_val get_elapsed_time();

	void set_timeout(const double timeout);
	timer_val get_timeout();

	bool expired();

	void start_average();
	void stop_average();
	void reset_average();
	bool is_averaging();
	timer_val average();
	void add_time_to_average();
};

#endif