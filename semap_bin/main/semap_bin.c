//关键点
//创建信号量
//xSemaphoreCreateBinary(void)
//xSemaphorTake(信号量句柄，等待时间)
//xSemaphorGive(信号量句柄)

#include "freertos/Freertos.h"
#include "freertos/projdefs.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "freertos/semphr.h"
#include <stdio.h>

SemaphoreHandle_t semaphor_handle;
int count = 0;


void task1(void *pvParam){
    for(;;){
        xSemaphoreTake(semaphor_handle,portMAX_DELAY);
        for (int i = 0;i < 10;i++){
            count++;
            printf("task1 count:%d\n",count);
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
        xSemaphoreGive(semaphor_handle);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void task2(void *pvParam){
    for(;;){
        xSemaphoreTake(semaphor_handle,portMAX_DELAY);
        for (int i = 0;i < 10;i++){
            count++;
            printf("task2 count:%d\n",count);
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
    }
}

void app_main(void)
{
    xTaskCreate(task1,"task1",4096*2,NULL,1,NULL);
    xTaskCreate(task2,"task2",4096*2,NULL,1,NULL);
    semaphor_handle = xSemaphoreCreateBinary();
    xSemaphoreGive(semaphor_handle);
    vTaskDelay(pdMS_TO_TICKS(1000));
}
