#include "driver/gpio.h"
#include "stdio.h"
#define GPIO_OUTPUT_PIN_0 10
#define GPIO_OUTPUT_PIN_1 11
#define GPIO_OUTPUT_PIN_SEL (1ULL<<GPIO_OUTPUT_PIN_0) | (1ULL<<GPIO_OUTPUT_PIN_1)


void blinker(void);
void gpio_init(void);
