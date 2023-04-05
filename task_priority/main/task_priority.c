/*
优先级的定义： 
优先级从0到(configMAX_PRIORITIES-1) 越大优先级别越高， 

相同优先级运行顺序： 
以时间片的方式顺序运行 

不同优先级运行顺序：
 
修改优先级
vTaskprioritySet(任务句柄，新的优先级) 
*/

//tip:freertos函数前面的v,u,x代表的是不同的数据类型 

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
	ESP_LOGI("priority","%d",priority); //有点问题，学完再说 
}
