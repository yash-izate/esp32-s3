#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"
#include "esp_err.h"

#include "esp_adc/adc_oneshot.h"

#define FSR_GPIO        5

static const char *TAG = "FSR";

void app_main(void)
{
    ESP_LOGI(TAG, "FSR pressure sensor test started");
    ESP_LOGI(TAG, "FSR connected to GPIO %d", FSR_GPIO);

    /*
     * GPIO 5 = ADC1 Channel 4 on ESP32-S3
     */
    adc_oneshot_unit_handle_t adc_handle;

    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = ADC_UNIT_1,
    };

    ESP_ERROR_CHECK(
        adc_oneshot_new_unit(&init_config, &adc_handle)
    );

    /*
     * Configure ADC1 Channel 4 = GPIO5
     */
    adc_oneshot_chan_cfg_t config = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,
        .atten = ADC_ATTEN_DB_12,
    };

    ESP_ERROR_CHECK(
        adc_oneshot_config_channel(
            adc_handle,
            ADC_CHANNEL_4,
            &config
        )
    );

    ESP_LOGI(TAG, "ADC initialized successfully");

    while (1)
    {
        int raw_value = 0;

        /*
         * Read ADC
         */
        ESP_ERROR_CHECK(
            adc_oneshot_read(
                adc_handle,
                ADC_CHANNEL_4,
                &raw_value
            )
        );

        /*
         * Print live reading
         */
        printf("FSR ADC = %d\n", raw_value);

        vTaskDelay(pdMS_TO_TICKS(200));
    }
}