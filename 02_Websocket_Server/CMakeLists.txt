cmake_minimum_required( VERSION 3.20.0 )

set( CMAKE_CXX_STANDARD          20    )
set( CMAKE_CXX_STANDARD_REQUIRED ON    )
set( CMAKE_BUILD_TYPE            Debug )

set(
    EXTRA_COMPONENT_DIRS
    Main
    WebServerApp
    WebsocketServerApp
)

include( $ENV{IDF_PATH}/tools/cmake/project.cmake )

project( WebSocketServer VERSION 1.0.0 )
