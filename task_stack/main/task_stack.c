//设置任务堆栈大小
//uxTaskGetStackHighWaterMark(任务句柄) 
//返回最小剩余堆栈数量，越接近0则表示越接近堆栈溢出 
#include <stdio.h>
#include "freertos/Freertos.h"
#include "freertos/task.h"
#include "esp_log.h"


void task_0(void *pvParam){
	for(;;){
//		ESP_LOGI("task0","runing:%d",i);
		printf("task0: running\n");
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
}

void task_1(void *pvParam){
	for(;;){
		ESP_LOGE("task1","runing");
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
} 

//printf 比ESP_LOG占用的资源少 
void app_main(void)
{
	TaskHandle_t task0_handle = NULL;
	TaskHandle_t task1_handle = NULL;
	xTaskCreate(task_0,"task_0",4096,NULL,2,&task0_handle);
	xTaskCreate(task_1,"task_1",4096,NULL,3,&task1_handle);
	while(true){	
		UBaseType_t task0_stack = uxTaskGetStackHighWaterMark(task0_handle);
		UBaseType_t task1_stack = uxTaskGetStackHighWaterMark(task1_handle);
		ESP_LOGI("task0","stack = %d",task0_stack);
		ESP_LOGI("task1","stack = %d",task1_stack);
		vTaskDelay(2000/portTICK_PERIOD_MS);
    }
}
