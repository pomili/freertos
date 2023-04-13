#include "freertos/Freertos.h"
#include "freertos/projdefs.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "freertos/semphr.h"
#include <stdio.h>


SemaphoreHandle_t sempherHandle;

void carInTask(void *pvParam){
    int emptySpace = 0;
    BaseType_t iResult;
    for(;;){
        emptySpace = uxSemaphoreGetCount(sempherHandle);
        printf("emptySpace = %d!\n",emptySpace);
        iResult = xSemaphoreTake(sempherHandle,0);
        if (iResult == pdPASS){
            printf("One car in!\n");
        }else {
            printf("no space!\n");
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void carOutTask(void *pvParam){
    for(;;){
        vTaskDelay(pdMS_TO_TICKS(6000));
        xSemaphoreGive(sempherHandle);
        printf("One car out!\n");
    }
}

void app_main(void)
{
    sempherHandle = xSemaphoreCreateCounting(5,5); 
    xTaskCreate(carInTask, "carInTask", 1024*6,NULL, 1, NULL);
    xTaskCreate(carOutTask, "carOutTask", 1024*6,NULL, 1, NULL);
}

