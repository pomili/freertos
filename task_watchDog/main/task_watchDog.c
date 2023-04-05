//��Ϊ�жϿ��Ź��������Ź� 
//����task watchdog ���������ַ���
//1.��task��ѭ������������ʱ�����������ȼ��ĺ����ͻ�ִ�� 
//2.��task�����ȼ���Ϊ0,����task��idle task(��������)�����ȼ�һ���������ͻ�ִ��idle task 
//
//�����Լ�������Ŀ��Ź�
//esp_task_wtd_add(������) ���������Ź�
//esp_task_wtd_reset(������) ι�� 

 
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