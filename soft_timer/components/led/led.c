#include <stdio.h>
#include "led.h"
#include "freertos/Freertos.h"
#include "freertos/task.h"
void blinker(){
	printf("components registor successed\n"); 
	gpio_set_level(GPIO_OUTPUT_PIN_1, 0);            // 把这个GPIO输出低电平
	vTaskDelay(500/portTICK_PERIOD_MS);
	gpio_set_level(GPIO_OUTPUT_PIN_1, 1);            // 把这个GPIO输出高电平
	vTaskDelay(500/portTICK_PERIOD_MS);	
}

void gpio_init(){
	gpio_config_t io_conf = {};
	io_conf.intr_type = GPIO_INTR_DISABLE;
	io_conf.mode = GPIO_MODE_OUTPUT;
	io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
	io_conf.pull_up_en = 0;
	io_conf.pull_down_en = 0;
	gpio_config(&io_conf);
}
