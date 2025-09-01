
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "led_strip.h"
#include "sdkconfig.h"

/* Use project configuration menu (idf.py menuconfig) to choose the GPIO to blink,
   or you can edit the following line and set a number here.
*/
#define BLINK_GPIO CONFIG_BLINK_GPIO

void blink_task(void *pvParameter)
{
    gpio_pad_select_gpio(BLINK_GPIO);
    // set the GPIO as a push/pull output

    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
    while (1)
    {
        gpio_set_level(BLINK_GPIO, 0); // blink off(output low)
        vTaskDelay(pdMS_TO_TICKS(1000));

        gpio_set_level(BLINK_GPIO, 1); // blink on(output low)
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
void app_main(void) { 
    xTaskCreate(&blink_task,"Blink Task",configMINIMAL_STACK_SIZE,NULL,5,NULL); 
}