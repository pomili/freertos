//����Ĺ�����ָ�
/*
����״̬�� 
running
ready
blocked 
susuended

���񴴽�֮��ͻ�������̬�������������ȣ�������̬�л�
���������к󣬽������״̬������̬������̬������̬�����Խ������̬
��������
vTaskSuspend(������) 
���������ΪNULL����ô���������� 
*/ 

#include <stdio.h>
#include "freertos/Freertos.h"
#include "freertos/task.h"
#include "esp_log.h"


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
	vTaskDelay(5000/portTICK_PERIOD_MS);
	vTaskSuspend(task1_handle);
	vTaskDelay(5000/portTICK_PERIOD_MS);
	vTaskResume(task1_handle);
}