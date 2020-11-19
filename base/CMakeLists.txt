CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

SET (CMAKE_BUILD_TYPE "Debug")
SET (CMAKE_CXX_STANDARD 17)
# add include and lib dirs
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/abseil/include")
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/include")
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/log")
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/tcl")
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}")

find_package(TCL 8.6 QUIET)

IF(TCL_FOUND)

    INCLUDE_DIRECTORIES(${TCL_INCLUDE_PATH})
    LINK_DIRECTORIES(${TCL_LIBRARY})    

ELSE(TCL_FOUND)

    MESSAGE(STATUS "not found tcl")
    INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/third_party/tcl/include)
    LINK_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/third_party/tcl/lib)

ENDIF(TCL_FOUND)

ADD_SUBDIRECTORY(log)
ADD_SUBDIRECTORY(tcl)

IF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    MESSAGE(STATUS "Now is windows")
    IF (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        LINK_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/abseil/lib/win/debug")
    ELSE ()
        LINK_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/abseil/lib/win/release")
    ENDIF ()
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    MESSAGE(STATUS "Now is UNIX-like OS's.")
    LINK_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/abseil/lib/unix")    
ENDIF ()

# Abseil lib
SET (AbslLibs
        absl_base
        absl_int128
        absl_city        
        absl_hash
        absl_hashtablez_sampler
        absl_random_seed_gen_exception
        absl_random_seed_sequences
        absl_raw_hash_set
        absl_malloc_internal
        absl_spinlock_wait
        absl_synchronization
        absl_throw_delegate
        absl_raw_logging_internal
        absl_time
        absl_time_zone
        )

OPTION (BASE_RUN_TESTS "If ON, the tests will be run." ON)

IF (BASE_RUN_TESTS)
    MESSAGE(STATUS "RUN BASE TESTS")
    # declare googletest
    IF (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        IF (CMAKE_SYSTEM_NAME MATCHES "Windows")
            INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../third_party/googletest/win/debug")
            LINK_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../third_party/googletest/win/debug")
        ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Linux")
            INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../third_party/googletest/unix")
            LINK_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../third_party/googletest/unix")
        ENDIF ()
        
    ELSE ()
        IF (CMAKE_SYSTEM_NAME MATCHES "Windows")
            INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../third_party/googletest/win/release")
            LINK_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../third_party/googletest/win/release")
        ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Linux")
            INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../third_party/googletest/unix")
            LINK_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../third_party/googletest/unix")
        ENDIF ()
        
    ENDIF()

    # build test
    AUX_SOURCE_DIRECTORY(./test SourceFiles)
    ADD_EXECUTABLE(base_test ${SourceFiles})

    SET(MyLibs base_log base_tcl)

    FILE(GLOB SO_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/abseil/lib/unix/*.so 
    )

    IF (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        IF (CMAKE_SYSTEM_NAME MATCHES "Windows")
        TARGET_LINK_LIBRARIES(base_test gmock_maind gtestd gmockd ${AbslLibs} ${MyLibs})
        ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Linux")
        TARGET_LINK_LIBRARIES(base_test gmock_main gtest gmock pthread ${AbslLibs} ${MyLibs})
        ADD_CUSTOM_COMMAND(TARGET base_test
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SO_FILES} ${CMAKE_CURRENT_BINARY_DIR}/
    )
        endif()
    ELSE ()
        IF (CMAKE_SYSTEM_NAME MATCHES "Windows")
        TARGET_LINK_LIBRARIES(base_test gmock_main gtest gmock ${AbslLibs})
        ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Linux")
        TARGET_LINK_LIBRARIES(base_test gmock_main gtest gmock pthread ${AbslLibs} ${MyLibs})
        ADD_CUSTOM_COMMAND(TARGET base_test
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SO_FILES} ${CMAKE_CURRENT_BINARY_DIR}/
    )
        endif()
    ENDIF ()

ENDIF (BASE_RUN_TESTS)



