#include <Arduino.h>

#include <nvs_flash.h>
#include <esp_partition.h>

#include "WebServerApp.h"
#include "WebsocketServerApp.h"

char static constexpr TAG[]{ "\tMAIN.CPP" };

void setup()
{
    // Disable default WiFi logging messages
    esp_log_level_set( "wifi",      ESP_LOG_NONE );
    esp_log_level_set( "wifi_init", ESP_LOG_NONE );


    // Initialize NVS (Non-volatile storage)
    ESP_LOGI( TAG, "Initializing NVS storage" );

    esp_err_t status{ nvs_flash_init() };

    if ( ESP_ERR_NVS_NO_FREE_PAGES == status || ESP_ERR_NVS_NEW_VERSION_FOUND == status )
    {
        ESP_ERROR_CHECK( nvs_flash_erase() );
        
        status = nvs_flash_init();
    }

    ESP_ERROR_CHECK( status );

    WebServerAppStart();

    WebSocketAppStart();

}

void loop()
{
    delay( 30 ); 
}
