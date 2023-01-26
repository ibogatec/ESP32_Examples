idf_component_register(
    SRCS
    WebServerApp.cpp

    INCLUDE_DIRS
    .

    REQUIRES
    ESPAsyncWebServer
)

spiffs_create_partition_image( storage webpage FLASH_IN_PROJECT )
