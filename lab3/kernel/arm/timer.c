#include <arm/timer.h>
#include <arm/reg.h>

volatile uint32_t timer;


void initializeTimer() {
	timer = 0;
}


void addTimer(int time) {
	timer += time;
}

unsigned int get_clock() {
	return timer;
}

volatile unsigned int* get_vclock() {
	return &timer;
}


