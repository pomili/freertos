// 互斥量与二进制信号量类似，但是会继承优先级

#include "freertos/Freertos.h"
#include "freertos/portmacro.h"
#include "freertos/projdefs.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include <stdio.h>

SemaphoreHandle_t mutexHandle;
void task1(void *pvParam) {
  BaseType_t iRet;
  for (;;) {
    printf("task1 run!\n");
    iRet = xSemaphoreTake(mutexHandle, 1000);
    if (iRet == pdPASS) {
      printf("task1 take!\n");
      for (int i = 0; i < 50; i++) {
        printf("task1 i = %d\n", i);
        vTaskDelay(pdMS_TO_TICKS(1000));
      }
      xSemaphoreGive(mutexHandle);
      printf("task1 give!\n");
      vTaskDelay(pdMS_TO_TICKS(5000));
    } else {
      printf("task1 didn't take!\n");
      vTaskDelay(pdMS_TO_TICKS(1000));
    }
  }
}

void task2(void *pvParam) {
  printf("task2 run!\n");
  vTaskDelay(pdMS_TO_TICKS(1000));
  for (;;) {
    ;
  }
}

void task3(void *pvParam) {
  BaseType_t iRet;
  printf("task3 run!\n");
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  for (;;) {
    iRet = xSemaphoreTake(mutexHandle, 1000);
    if (iRet == pdPASS) {
      printf("task3 take!\n");
      for (int i = 0; i < 10; i++) {
        printf("task3 i = %d\n", i);
        vTaskDelay(pdMS_TO_TICKS(1000));
      }
      xSemaphoreGive(mutexHandle);
      printf("task3 give!\n");
      vTaskDelay(pdMS_TO_TICKS(5000));
    } else {
      printf("task3 didn't take!\n");
      vTaskDelay(pdMS_TO_TICKS(1000));
    }
  }
}

void app_main(void) {
  mutexHandle = xSemaphoreCreateMutex();
  vTaskSuspendAll();
  xTaskCreate(task1, "task1", 1024 * 5, NULL, 1, NULL);
  xTaskCreate(task2, "task2", 1024 * 5, NULL, 2, NULL);
  xTaskCreate(task3, "task3", 1024 * 5, NULL, 3, NULL);
  xTaskResumeAll();
}
