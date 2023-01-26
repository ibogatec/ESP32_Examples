cmake_minimum_required( VERSION 3.20.0 )

set( CMAKE_CXX_STANDARD          20    )
set( CMAKE_CXX_STANDARD_REQUIRED ON    )
set( CMAKE_BUILD_TYPE            Debug )

include( $ENV{IDF_PATH}/tools/cmake/project.cmake )

project( Blink VERSION 1.0.0 )
