//freertos任务的创建与删除 
//xTaskCreate(函数名,“任务名”,堆栈大小,参数,优先级,任务句柄) 
#include <stdio.h>
#include "freertos/Freertos.h"
#include "freertos/task.h"
#include "esp_log.h"
 
void myTask(void *pvParam){
	for(;;){
		printf("hello world\n");
		vTaskDelay(1000/portTICK_PERIOD_MS);
		ESP_LOGI("myTask","run");
		ESP_LOGE("myTask","run");
		ESP_LOGD("myTask","run");
	}

}

 
void app_main(void)
{
	xTaskCreate(myTask,"myTask",1024,NULL,1,NULL);
	ESP_LOGI("freertos","ok");
	vTaskDelay(1000);
}
