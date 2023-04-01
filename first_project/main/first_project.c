//freertos����Ĵ�����ɾ�� 
//xTaskCreate(������,����������,��ջ��С,����,���ȼ�,������) 
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