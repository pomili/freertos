//分为中断看门狗和任务看门狗 
//避免task watchdog 触发有两种方法
//1.在task的循环里面添加延时函数，低优先级的函数就会执行 
//2.将task的优先级改为0,这样task与idle task(空闲任务)的优先级一样，这样就会执行idle task 
//
//添加自己人任务的看门狗
//esp_task_wtd_add(任务句柄) 添加任务看门狗
//esp_task_wtd_reset(任务句柄) 喂狗 

 
#include <stdio.h>
#include "freertos/Freertos.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_task_wdt.h"

void task_0(void *pvParam){
	esp_task_wdt_add(NULL); 
	for(;;){
		ESP_LOGI("task0","runing");
		vTaskDelay(1000/portTICK_PERIOD_MS);
		esp_task_wdt_reset(); 
	}
}

void task_1(void *pvParam){
	for(;;){
		ESP_LOGE("task1","runing");
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
} 


void app_main(void)
{
	TaskHandle_t task0_handle = NULL;
	TaskHandle_t task1_handle = NULL;
	xTaskCreate(task_0,"task_0",4096,NULL,2,&task0_handle);
	xTaskCreate(task_1,"task_1",4096,NULL,3,&task1_handle);
}
