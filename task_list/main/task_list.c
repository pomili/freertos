//任务列表 
/*
vTaskList(char *data); 
*/ 

#include <stdio.h>
#include "freertos/Freertos.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/gpio.h"

#define GPIO_OUTPUT_PIN_0 10
#define GPIO_OUTPUT_PIN_1 11
#define GPIO_OUTPUT_PIN_SEL (1ULL<<GPIO_OUTPUT_PIN_0) | (1ULL<<GPIO_OUTPUT_PIN_1)

void task_0(void *pvParam){
	int i = 0;
	for(;;){
		ESP_LOGI("task0","runing:%d",i);
		i++;
		vTaskDelay(1000/portTICK_PERIOD_MS);
		if (i == 3)
		vTaskSuspend(NULL);
	}
}

void task_1(void *pvParam){
	for(;;){
		gpio_set_level(GPIO_OUTPUT_PIN_0, 0);            // 把这个GPIO输出低电平
		vTaskDelay(1000/portTICK_PERIOD_MS);
		gpio_set_level(GPIO_OUTPUT_PIN_0, 1);            // 把这个GPIO输出高电平
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
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


void app_main(void)
{
	gpio_init();
	TaskHandle_t task0_handle = NULL;
	TaskHandle_t task1_handle = NULL;
	xTaskCreate(task_0,"task_0",4096,NULL,2,&task0_handle);
	xTaskCreate(task_1,"task_1",4096,NULL,3,&task1_handle);
	vTaskDelay(5000/portTICK_PERIOD_MS);
	vTaskSuspend(task1_handle);
	vTaskDelay(5000/portTICK_PERIOD_MS);
	while(true){
		static char list_tab[512] = {0};
		vTaskList(list_tab);
		printf("------------------------------------------\n");
		printf("name          state  priority   stack  num\n");
		printf("------------------------------------------\n");
		printf("%s\n",list_tab);
		printf("------------------------------------------\n");
		vTaskDelay(2000/portTICK_PERIOD_MS); 
	}
}
