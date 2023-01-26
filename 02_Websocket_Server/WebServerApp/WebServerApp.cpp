#include <WiFi.h>
#include <SPIFFS.h>

#include <ESPAsyncWebServer.h>

#include "WebServerApp.h"

char static constexpr TAG[]{ "\tWebServerApp.cpp" };


// Credentials that client will use to connect to ESP32 Access Point
char static constexpr ssid[]    { "ESP32-AP" };
char static constexpr password[]{ "Password1" };


// WebServer
uint16_t       static constexpr httpPort  { 80 };
AsyncWebServer static           httpServer{ httpPort };


// Handler for serving index.html page
static void OnIndexRequest( AsyncWebServerRequest *req )
{
    ESP_LOGI( TAG, "index.html requested" );

    req->send( SPIFFS, "/index.html", "text/html" );
}

// Handler for serving style.css
static void OnStyleCssRequest( AsyncWebServerRequest *req )
{
    ESP_LOGI( TAG, "app.css requested" );

    req->send( SPIFFS, "/style.css", "text/css" );
}

// Handler for serving app.js
static void OnAppJsRequest( AsyncWebServerRequest *req )
{
    ESP_LOGI( TAG, "app.js requested" );

    req->send( SPIFFS, "/app.js", "text/javascript" );
}

// Handler for serving jquery-3.6.3.min.js
static void OnjQueryRequest( AsyncWebServerRequest *req )
{
    ESP_LOGI( TAG, "jquery-3.6.3.min.js requested" );

    req->send( SPIFFS, "/jquery-3.6.3.min.js", "text/javascript" );
}

// Handler for serving favicon.ico
static void OnFaviconRequest( AsyncWebServerRequest *req )
{
    ESP_LOGI( TAG, "favicon.ico requested" );

    req->send( SPIFFS, "/favicon.ico", "image/x-icon" );
}


void WebServerAppStart()
{

    ESP_LOGI( TAG, "WebServerAppStart(): Starting an Access Point..." );

    // Start SPIFFS file system (Spy Flash File System) - make sure we can read from this file system
    if ( !SPIFFS.begin( true ) )
    {
        ESP_LOGE( TAG, "WebServerAppStart(): Error mounting SPIFFS" );
        return;
    }


    // Configure WiFi Access Point and start it
    WiFi.softAP( ssid, password );

    ESP_LOGI( TAG, "WebSocketAppStart(): AP Running, IP Address of this AP is: '%s'", WiFi.softAPIP().toString().c_str() );


    // Configure and Start HTTP Server
    httpServer.on( "/",                    HTTP_GET, OnIndexRequest    );
    httpServer.on( "/style.css",           HTTP_GET, OnStyleCssRequest );
    httpServer.on( "/app.js",              HTTP_GET, OnAppJsRequest    );
    httpServer.on( "/jquery-3.6.3.min.js", HTTP_GET, OnjQueryRequest   );
    httpServer.on( "/favicon.ico",         HTTP_GET, OnFaviconRequest  );

    httpServer.begin();

}
