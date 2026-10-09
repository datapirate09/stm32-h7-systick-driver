#include <stdint.h>

typedef enum {
	EXTERNAL_CLK = 0,
	PROCESSOR_CLK = 1,
} clock_source;

typedef enum {
	COUNTER_DISABLE = 0,
	COUNTER_ENABLE = 1 ,
} counter_status;

typedef enum {
	INTERRUPT_DISABLE = 0,
	INTERRUPT_ENABLE = 1,
} exception_enable_status;

struct counter_config {
	clock_source src;
	exception_enable_status is_int_enabled;
	counter_status is_counter_enabled;
};

typedef void (*systick_callback)(void);

void systick_config(struct counter_config* config);
void systick_register_callback(systick_callback callback);
void load_systick_value(uint32_t val);
uint32_t check_timer_expire(void);
uint32_t read_current_value(void);

