// ������ʱ����ƽ̨�޹�
//

#include "freertos/Freertos.h"
#include "freertos/projdefs.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "led.h"
#include <stdio.h>

/*
TimerHandle_t xTimerCreate( const char *pcTimerName,
                                                        const TickType
xTimerPeriod, const UBaseType_t uxAutoReload, void * const pvTimerID,
                                                        TimerCallbackFunction
pvCallbackFunction);


*/

void Timer_1_callback(TimerHandle_t xTimer) {
  const char *strName;
  strName = pcTimerGetName(xTimer);

  printf("Timer Name = %s\n", strName);
}

void app_main(void) {
  TimerHandle_t xTimer1;
  TimerHandle_t xTimer2;
  xTimer1 = xTimerCreate("Timer1", pdMS_TO_TICKS(1000), pdTRUE, (void *)0,
                         Timer_1_callback);
  xTimer2 = xTimerCreate("Timer2", pdMS_TO_TICKS(1000), pdTRUE, (void *)1,
                         Timer_1_callback);

  xTimerStart(xTimer1, 0);
  xTimerStart(xTimer2, 0);
  gpio_init();
  vTaskDelay(pdMS_TO_TICKS(5000));
  xTimerStop(xTimer1, 0);

  while (1) {
    blinker();
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
