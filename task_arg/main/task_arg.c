//task参数输入 
//myTask0接受数组类型
//myTask1接受整数类型
//所有的任务必须是无限循环 
#include <stdio.h>
#include "freertos/Freertos.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/gpio.h"

#define GPIO_OUTPUT_PIN_0 10
#define GPIO_OUTPUT_PIN_1 11
#define GPIO_OUTPUT_PIN_SEL (1ULL<<GPIO_OUTPUT_PIN_0) | (1ULL<<GPIO_OUTPUT_PIN_1)   //引脚位掩码，用来设置引脚号，1ULL表示unsigned long long 

int task_arg = 2023; 
int task_arry[] = {5,2,0};
typedef struct TASK_STR{
	int num1;
	int num2;	
} task_str; 
task_str str_test = {4,1};
static const char *prt_char = "hello world!"; 

void gpio_init(){
	gpio_config_t io_conf = {};
	io_conf.intr_type = GPIO_INTR_DISABLE;
	io_conf.mode = GPIO_MODE_OUTPUT;
	io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
	io_conf.pull_up_en = 0;
	io_conf.pull_down_en = 0;
	gpio_config(&io_conf);
}

void myTask0(void *pvParam){
	int *ptr;
	ptr = (int *)pvParam;
	ESP_LOGI("myTask0","task_arg:%d",*ptr);
	for(;;){
		gpio_set_level(GPIO_OUTPUT_PIN_0, 0);            // 把这个GPIO输出低电平
		vTaskDelay(1000/portTICK_PERIOD_MS);
		gpio_set_level(GPIO_OUTPUT_PIN_0, 1);            // 把这个GPIO输出高电平
		vTaskDelay(1000/portTICK_PERIOD_MS);

	}
}

void myTask1(void *pvParam){
	int *ptr_arry;
	ptr_arry = (int *)pvParam;
	for (int i = 0;i < 3;i++){
		ESP_LOGE("myTask1","task_arry[%d]:%d",i,*(ptr_arry+i));
	}
	for(;;){
		gpio_set_level(GPIO_OUTPUT_PIN_1, 0);            // 把这个GPIO输出低电平
		vTaskDelay(500/portTICK_PERIOD_MS);
		gpio_set_level(GPIO_OUTPUT_PIN_1, 1);            // 把这个GPIO输出高电平
		vTaskDelay(500/portTICK_PERIOD_MS);

	}
}

void myTask2(void *pvParam){
	task_str *ptr_str;
	ptr_str = (task_str *)pvParam;
	ESP_LOGW("myTask2","ptr_str->num1:%d",ptr_str->num1);
	ESP_LOGW("myTask2","ptr_str->num2:%d",ptr_str->num2);
	vTaskDelete(NULL);
}

void myTask3(void *pvParam){
	char *task_char;
	task_char = (char *)pvParam;
	ESP_LOGI("myTask3","task_char:%s",task_char);
	vTaskDelete(NULL); 
}

void app_main(void)
{	
	gpio_init();
	TaskHandle_t myTask_handle0 = NULL;
	TaskHandle_t myTask_handle1 = NULL;
	TaskHandle_t myTask_handle2 = NULL;
	TaskHandle_t myTask_handle3 = NULL;
	xTaskCreate(myTask0,"myTask0",4096,(void *)&task_arg,1,&myTask_handle0);
	xTaskCreate(myTask1,"myTask1",4096,(void *)task_arry,2,&myTask_handle1);
	xTaskCreate(myTask2,"myTask2",4096,(void *)&str_test,3,&myTask_handle2);
	xTaskCreate(myTask3,"myTask3",4096,(void *)prt_char,4,&myTask_handle3);
	vTaskDelay(1000/portTICK_PERIOD_MS);
}
