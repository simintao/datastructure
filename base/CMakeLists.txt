CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

# Abseil requires C++17
SET(CMAKE_CXX_STANDARD 17)

# Abseil lib
SET(AbslLibs
        absl_bad_any_cast_impl
        absl_bad_optional_access
        absl_bad_variant_access
        absl_base
        absl_city
        absl_civil_time
        absl_cord
        absl_debugging_internal
        absl_demangle_internal
        absl_examine_stack
        absl_exponential_biased
        absl_failure_signal_handler
        absl_flags
        absl_flags_commandlineflag
        absl_flags_commandlineflag_internal
        absl_flags_config
        absl_flags_internal
        absl_flags_marshalling
        absl_flags_parse
        absl_flags_private_handle_accessor
        absl_flags_program_name
        absl_flags_reflection
        absl_flags_usage
        absl_flags_usage_internal
        absl_graphcycles_internal
        absl_hash
        absl_hashtablez_sampler
        absl_hash_generator_testing
        absl_int128
        absl_leak_check
        absl_leak_check_disable
        absl_log_severity
        absl_malloc_internal
        absl_periodic_sampler
        absl_random_distributions
        absl_random_internal_distribution_test_util
        absl_random_internal_platform
        absl_random_internal_pool_urbg
        absl_random_internal_randen
        absl_random_internal_randen_hwaes
        absl_random_internal_randen_hwaes_impl
        absl_random_internal_randen_slow
        absl_random_internal_seed_material
        absl_random_seed_gen_exception
        absl_random_seed_sequences
        absl_raw_hash_set
        absl_raw_logging_internal
        absl_scoped_set_env
        absl_spinlock_wait
        absl_stacktrace
        absl_status
        absl_statusor
        absl_str_format_internal
        absl_strerror
        absl_strings
        absl_strings_internal
        absl_symbolize
        absl_synchronization
        absl_throw_delegate
        absl_time
        absl_time_zone
        )

#message("libs ${AbslLibs}")

# add include and lib dirs
INCLUDE_DIRECTORIES("./abseil/include")
INCLUDE_DIRECTORIES("./include")

IF (WIN32)
    MESSAGE(STATUS "Now is windows")
    LINK_DIRECTORIES("./abseil/lib/win")
ELSEIF (APPLE)
    MESSAGE(STATUS "Now is Apple systems.")
ELSEIF (UNIX)
    MESSAGE(STATUS "Now is UNIX-like OS's.")
    LINK_DIRECTORIES("./abseil/lib/unix")
ENDIF ()

OPTION(BASE_RUN_TESTS "If ON, the tests will be run." ON)

IF(${BASE_RUN_TESTS})

# declare googletest
IF (WIN32)
    INCLUDE_DIRECTORIES("../third_party/googletest/win")
    LINK_DIRECTORIES("../third_party/googletest/win")
ELSEIF (APPLE)
    MESSAGE(STATUS "Now is Apple systems.")
ELSEIF (UNIX)
    INCLUDE_DIRECTORIES("../third_party/googletest/unix")
    LINK_DIRECTORIES("../third_party/googletest/unix")
ENDIF ()
ENDIF (${BASE_RUN_TESTS})


# build test
AUX_SOURCE_DIRECTORY(./test SourceFiles)
ADD_EXECUTABLE(base_test ${SourceFiles})

IF (WIN32)
TARGET_LINK_LIBRARIES(base_test gmock_main gtest gmock ${AbslLibs})
ELSEIF (UNIX)
TARGET_LINK_LIBRARIES(base_test gmock_main gtest gmock pthread ${AbslLibs})
endif()




