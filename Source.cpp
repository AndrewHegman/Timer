#include <stdio.h>
#include "Timer.h"

int main() {
	Timer my_timer(milliseconds);
	double time = my_timer.average().scale(milliseconds);
	return(0);
}