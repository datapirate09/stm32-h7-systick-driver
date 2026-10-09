#include "stm32h7a3xxq.h"
#include <stdio.h>
#include "systick_driver.h"
#include <stddef.h>


static systick_callback application_callback = NULL;

void systick_config(struct counter_config* config) {
	SysTick->CTRL &= ~(1U << 2);
	SysTick->CTRL |= ((uint32_t)config->src << 2);
	SysTick->CTRL &= ~(1U << 1);
	SysTick->CTRL |= ((uint32_t)config->is_int_enabled << 1);
	SysTick->CTRL &= ~(1U << 0);
	SysTick->CTRL |= ((uint32_t)config->is_counter_enabled << 0);
}

void systick_register_callback(systick_callback callback) {
	application_callback = callback;
}

void load_systick_value(uint32_t val) {
	SysTick->LOAD = val;
	// now also clear the current value as hw wont do that
	SysTick->VAL = 0xFFFFFF;
}

uint32_t check_timer_expire(void) {
	return (uint32_t)(SysTick->CTRL & (1U << 16));
}

uint32_t read_current_value(void) {
	return (uint32_t)SysTick->VAL;
}

void SysTick_Handler(void) {
	if (application_callback != NULL) {
		application_callback();
	}
}
