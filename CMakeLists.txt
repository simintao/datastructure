CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(MyProject)

# Abseil requires C++17
SET (CMAKE_CXX_STANDARD 17)

ADD_SUBDIRECTORY(base)

# add include and lib dirs
INCLUDE_DIRECTORIES("./base/abseil/include")
INCLUDE_DIRECTORIES("./base/include")

SET (CMAKE_BUILD_TYPE "Debug")

IF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    MESSAGE(STATUS "Now is windows")
    IF (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        LINK_DIRECTORIES("./base/abseil/lib/win/debug")
    ELSE ()
        LINK_DIRECTORIES("./base/abseil/lib/win/release")
    ENDIF ()
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    MESSAGE(STATUS "Now is UNIX-like OS's.")
    LINK_DIRECTORIES("./base/abseil/lib/unix")
ENDIF ()


# Abseil lib
SET (AbslLibs
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

ADD_EXECUTABLE(main main.cc)

TARGET_LINK_LIBRARIES(main ${AbslLibs})



