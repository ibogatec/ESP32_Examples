#include <WebSocketsServer.h>
#include <WiFi.h>

#include "WebsocketServerApp.h"

char static constexpr TAG[]{ "\tWebsocketServerApp.cpp" };


// Web socket server
uint16_t         static constexpr wsPort{ 1337 };
WebSocketsServer static           wsServer{ wsPort };


// Messages that ESP32 websocket server can process
char static constexpr msgToggleLed[]  { "toggleLED" };
char static constexpr msgGetLedState[]{ "getLEDState" };


// Event handler for the websocket events
void OnWebSocketEvent( uint8_t clientNo, WStype_t type, uint8_t * payload, size_t length )
{
    bool    static           ledState{ false };
    uint8_t static constexpr ledPin  { 2 };

    switch ( type )
    {
        case WStype_DISCONNECTED:
        {
            ESP_LOGI( TAG, "WStype_DISCONNECTED: %u", clientNo );
            break;
        }

        case WStype_CONNECTED:
        {
            IPAddress ip{ wsServer.remoteIP( clientNo ) };

            ESP_LOGI( TAG, "WStype_CONNECTED: Connection from: %u, IP: %s", clientNo, ip.toString().c_str() );
            break;
        }

        case WStype_TEXT:
        {
            ESP_LOGI( TAG, "WStype_TEXT: %u", clientNo );

            char const * received = reinterpret_cast< char const * >( payload );

            if ( 0 == strcmp( received, msgToggleLed ) )
            {
                ledState = !ledState;
                digitalWrite( ledPin, ledState );

                wsServer.broadcastTXT( ledState ? "ON" : "OFF" );
            }
            else if ( 0 == strcmp( received, msgGetLedState ) )
            {
                wsServer.sendTXT( clientNo, ( ledState ? "ON" : "OFF" ) );
            }

            break;
        }

        case WStype_PING:
        case WStype_PONG:
        case WStype_BIN:
        case WStype_ERROR:
        case WStype_FRAGMENT:
        case WStype_FRAGMENT_TEXT_START:
        case WStype_FRAGMENT_BIN_START:
        case WStype_FRAGMENT_FIN:
            break;

    }
}


// Websocket application Task
static void WebSocketAppTask( void *pvParameters )
{
    while( true )
    {
        wsServer.loop();
        delay( 10 );
    }
}


/**
 * Web Socket App entry point - configures websocket server and starts websocket app task
*/
void WebSocketAppStart()
{
        ESP_LOGI( TAG, "WebSocketAppStart(): Starting WebSocket Server..." );

        // Configure GPIO pin
        uint8_t constexpr ledPin{ 2 };

        pinMode( ledPin, OUTPUT );
        
        digitalWrite( ledPin, LOW );


        // Start websocket server and assign callback
        wsServer.begin();

        wsServer.onEvent( OnWebSocketEvent );


        // Start the WiFi application task
        xTaskCreatePinnedToCore( &WebSocketAppTask, "WebSocketAppTask", WEBSOCKET_TASK_STACK_SIZE, NULL, WEBSOCKET_TASK_PRIORITY, NULL, WEBSOCKET_TASK_CORE_ID );
}
