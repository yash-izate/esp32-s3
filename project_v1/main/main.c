#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "PROJECT_V1";

void app_main(void)
{
    while (1)
    {
        ESP_LOGI(TAG, "Hello from ESP32-S3!");

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}