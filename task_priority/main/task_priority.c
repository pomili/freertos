/*
���ȼ��Ķ��壺 
���ȼ���0��(configMAX_PRIORITIES-1) Խ�����ȼ���Խ�ߣ� 

��ͬ���ȼ�����˳�� 
��ʱ��Ƭ�ķ�ʽ˳������ 

��ͬ���ȼ�����˳��
 
�޸����ȼ�
vTaskprioritySet(���������µ����ȼ�) 
*/

//tip:freertos����ǰ���v,u,x�������ǲ�ͬ���������� 

#include <stdio.h>
#include "freertos/Freertos.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *prt_char = "hello world!";

void myTask0(void *pvParam){
	char *task_char;
	task_char = (char *)pvParam;
	ESP_LOGI("myTask0","task_char:%s",task_char);
	vTaskDelete(NULL); 
}

void myTask1(void *pvParam){
	ESP_LOGI("myTask1","priority:%d",uxTaskPriorityGet(NULL));
	vTaskPrioritySet(NULL,8);
	ESP_LOGI("myTask1","priority:%d",uxTaskPriorityGet(NULL));
	vTaskDelete(NULL); 
}

void app_main(void)
{
	TaskHandle_t myTask_handle0 = NULL;
	TaskHandle_t myTask_handle1 = NULL;
	xTaskCreate(myTask0,"myTask0",4096,(void *)prt_char,5,&myTask_handle0);
	xTaskCreate(myTask1,"myTask1",4096,NULL,2,&myTask_handle1);
	UBaseType_t priority = 0;
	priority =  uxTaskPriorityGet(myTask_handle1);
	ESP_LOGI("priority","%d",priority); //�е����⣬ѧ����˵ 
}