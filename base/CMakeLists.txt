CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

# Abseil requires C++11
SET(CMAKE_CXX_STANDARD 11)

# Process Abseil's CMake build system
ADD_SUBDIRECTORY(abseil-cpp)

AUX_SOURCE_DIRECTORY(./ SourceFiles)

ADD_EXECUTABLE(test ${SourceFiles})

# Declare dependency on the absl::strings library
TARGET_LINK_LIBRARIES(test gtest_main gtest pthread absl_city absl_hash absl_hashtablez_sampler absl_raw_hash_set absl_random_seed_gen_exception absl_random_seed_sequences)
