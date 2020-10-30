CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(MyProject)

# Abseil requires C++17
SET (CMAKE_CXX_STANDARD 17)

ADD_SUBDIRECTORY(base)

# add include and lib dirs
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/base/abseil/include")
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/base/include")

SET (CMAKE_BUILD_TYPE "Debug")

IF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    MESSAGE(STATUS "Now is windows")
    IF (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        LINK_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/base/abseil/lib/win/debug")
    ELSE ()
        LINK_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/base/abseil/lib/win/release")
    ENDIF ()
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    MESSAGE(STATUS "Now is UNIX-like OS's.")
    LINK_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/base/abseil/lib/unix")
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

ADD_EXECUTABLE(main main.cc)

TARGET_LINK_LIBRARIES(main ${AbslLibs})



