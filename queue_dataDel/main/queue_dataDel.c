//通过队列传递整形，结构体，指针类型的数据
//QueueHandle_t xQueueCreate(长度,宽度); 
//发送函数
/*
BaseType_t xQueueSend(QueueHandle_t xQueue,
					  const void * pvItemToQueue,	
					  TickType_t xTicksToWait);
					  
BaseType_t xQueueSendToFront(QueueHandle_t xQueue,
					  const void * pvItemToQueue,	
					  TickType_t xTicksToWait);
					  
BaseType_t xQueueSendtoBack(QueueHandle_t xQueue,
					  const void * pvItemToQueue,	
					  TickType_t xTicksToWait);					  
*/ 
//接受函数
/*
BaseType_t xQueueReceive(QueueHandle_t xQueue,
						void *pvBuffer 
						TickType_t xTickToWait);
*/ 
#include <stdio.h>
#include "freertos/Freertos.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "freertos/queue.h"


typedef struct  QUE_STRUCT{
	char id;
	char data;
}que_struct; 

 
void task_0(void *pvParam){ 
	QueueHandle_t queue_handle;
	queue_handle = (QueueHandle_t)pvParam;
	BaseType_t xStatus;
	int i = 0;
	for(;;){
		xStatus = xQueueSend(queue_handle,&i,0);
		if (xStatus != pdPASS)
			ESP_LOGI("int_send","send fail!\n");
		else
			ESP_LOGI("int_send","send done.\n");
		i++;
		if (i == 6)
			i = 0;		
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
}

void task_1(void *pvParam){
	QueueHandle_t queue_handle;
	queue_handle = (QueueHandle_t)pvParam;
	BaseType_t xStatus;
	int j = 0;	
	for(;;){
		if(uxQueueMessagesWaiting(queue_handle) != 0){
			xStatus = xQueueReceive(queue_handle,&j,0);
			if (xStatus != pdPASS)
				ESP_LOGI("int_rec","receive fail!\n");
			else
				ESP_LOGI("int_rec","receive done. \nreceived data : %d\n",j);			
		}
		else
			ESP_LOGI("int_rec","no data!\n");
		
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
} 

void task_2(void *pvParam){ 
	QueueHandle_t queue_handle;
	queue_handle = (QueueHandle_t)pvParam;
	BaseType_t xStatus;
	que_struct que_Struct = {0,198};
	for(;;){
		xStatus = xQueueSend(queue_handle,&que_Struct,0);
		if (xStatus != pdPASS)
			ESP_LOGI("str_send","send fail!\n");
		else
			ESP_LOGI("str_send","send done.\n");
		que_Struct.id++;
		que_Struct.data--; 
		if (que_Struct.id == 6)
			que_Struct.id = 0;		
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
}

void task_3(void *pvParam){
	QueueHandle_t queue_handle;
	queue_handle = (QueueHandle_t)pvParam;
	BaseType_t xStatus;
	que_struct que_Struct = {0,0};	
	for(;;){
		if(uxQueueMessagesWaiting(queue_handle) != 0){
			xStatus = xQueueReceive(queue_handle,&que_Struct,0);
			if (xStatus != pdPASS)
				ESP_LOGI("str_rec","receive fail!\n");
			else
				ESP_LOGI("str_rec","receive done. \nreceived id : %d, data : %d\n",que_Struct.id,que_Struct.data);			
		}
		else
			ESP_LOGI("str_rec","no data!\n");
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
}

void task_4(void *pvParam){ 
	QueueHandle_t queue_handle;
	queue_handle = (QueueHandle_t)pvParam;
	BaseType_t xStatus;
	char *p_send;
	int i = 0;
	for(;;){
		p_send = (char *)malloc(50);
		snprintf(p_send,50,"You are a good man,%d",i);
		i++;
		xStatus = xQueueSend(queue_handle,&p_send,0);
		if (xStatus != pdPASS)
			ESP_LOGI("p_send","send fail!\n");
		else
			ESP_LOGI("p_send","send done.\n");	
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
}

void task_5(void *pvParam){
	QueueHandle_t queue_handle;
	queue_handle = (QueueHandle_t)pvParam;
	BaseType_t xStatus;
	char *p_rec;	
	for(;;){
		if(uxQueueMessagesWaiting(queue_handle) != 0){
			xStatus = xQueueReceive(queue_handle,&p_rec,0);
			if (xStatus != pdPASS)
				ESP_LOGI("p_rec","receive fail!\n");
			else{
				ESP_LOGI("p_rec","receive done. \nreceived data: %s\n",p_rec);
				free(p_rec);	
		}
		}
		else
			ESP_LOGI("p_rec","no data!\n");
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
}

void app_main(void)
{
	QueueHandle_t queue_handle;
	QueueHandle_t queue_handle_str;
	QueueHandle_t queue_handle_p;
	queue_handle = xQueueCreate(5,sizeof(int));
	queue_handle_str = xQueueCreate(5,sizeof(que_struct));
	queue_handle_p = xQueueCreate(5,sizeof(char *));
	
	if (queue_handle != NULL){
		printf("Create queue successfully!\n");
		xTaskCreate(task_0,"task_0",4096,(void *)queue_handle,3,NULL);
		xTaskCreate(task_1,"task_1",4096,(void *)queue_handle,3,NULL);
		xTaskCreate(task_2,"task_2",4096,(void *)queue_handle_str,3,NULL);
		xTaskCreate(task_3,"task_3",4096,(void *)queue_handle_str,3,NULL);
		xTaskCreate(task_4,"task_4",4096,(void *)queue_handle_p,3,NULL);
		xTaskCreate(task_5,"task_5",4096,(void *)queue_handle_p,3,NULL);					
	}else{
		printf("Create queue failed!\n");
	}
}
