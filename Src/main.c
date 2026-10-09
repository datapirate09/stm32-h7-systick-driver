#include "systick_driver.h"
#include "logger.h"
#include <stdio.h>

#define COUNTER_INITIAL_VALUE 64000

static void systick_timer_callback(void);

uint8_t is_timer_elapsed = 0;

struct counter_config config = {
	.src = PROCESSOR_CLK,
	.is_int_enabled = INTERRUPT_ENABLE,
	.is_counter_enabled = COUNTER_ENABLE
};

int main() {
	logger_init();
	printf("In main\n");
	load_systick_value(COUNTER_INITIAL_VALUE);
	systick_register_callback(systick_timer_callback);
	systick_config(&config);
	printf("Systick configuration set\n");

	while(1) {
		if (is_timer_elapsed) {
			is_timer_elapsed = 0;
			printf("Timer Elapsed\n");
		}
	}

//	// uncomment for polling
//	while(1) {
//		// wait until counter expires so arm sets count flag
//		if (check_timer_expire()) {
//			printf("Ticks Elapsed\n");
//			printf("%lu\n", read_current_value());
//		}
//	}
}

static void systick_timer_callback(void) {
	is_timer_elapsed = 1;
}
