CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

SET (CMAKE_CXX_STANDARD 17)

AUX_SOURCE_DIRECTORY(./ SRC)

IF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    MESSAGE(STATUS "Now is windows")
    IF (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        LINK_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../abseil/lib/win/debug")
    ELSE ()
        LINK_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../abseil/lib/win/release")
    ENDIF ()
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    MESSAGE(STATUS "Now is UNIX-like OS's.")
    LINK_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../abseil/lib/unix")
ENDIF ()

ADD_LIBRARY(base_log STATIC ${SRC})

FIND_PACKAGE(Boost 1.54.0 QUIET COMPONENTS log_setup log thread filesystem)

IF(Boost_FOUND)

    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
    LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

    TARGET_LINK_LIBRARIES(base_log ${Boost_LIBRARIES})

ELSE(Boost_FOUND)

    INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../boost/log/include)
    LINK_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../boost/log/lib)

    TARGET_LINK_LIBRARIES(base_log libboost_log_setup.a libboost_log.a libboost_thread.a libboost_filesystem.a)

ENDIF(Boost_FOUND)