//freertos任务的创建与删除 
//xTaskCreate(函数名,“任务名”,堆栈大小,参数,优先级,任务句柄) 
#include <stdio.h>
#include "freertos/Freertos.h"
#include "freertos/task.h"
#include "esp_log.h"
int num0 = 0;
int num1 = 0; 
void myTask1(void *pvParam){
	for(;;){
		num1++;
		vTaskDelay(1000/portTICK_PERIOD_MS);
		ESP_LOGE("myTask1","%d",num1);
		if(num1 == 50)
		vTaskDelete(NULL);
	}

}
void myTask0(void *pvParam){
	for(;;){
		num0++;
		ESP_LOGI("myTask0","%d",num0);
		vTaskDelay(500/portTICK_PERIOD_MS);
	}
}
 
void app_main(void)
{	
	TaskHandle_t myHandle1 = NULL;
	TaskHandle_t myHandle0 = NULL;
	xTaskCreate(myTask1,"myTask1",4096,NULL,1,&myHandle1);
	xTaskCreate(myTask0,"myTask0",4096,NULL,2,&myHandle0);
	vTaskDelay(8000/portTICK_PERIOD_MS);
	if(myHandle0 != NULL){
		vTaskDelete(myHandle0);
		printf("my task1 deleted\n");
	}
	
}
