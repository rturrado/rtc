set(test_sources
    "${CMAKE_CURRENT_SOURCE_DIR}/console_read.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/filesystem.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/pretty_print.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/print.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/random.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/stream.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/string.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/timer.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/typeinfo.cpp"
)

include(FetchContent)
FetchContent_Declare(fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG "7ffe87c0bc8e69cd38941b92c0b33ab2e5cf3c57"
)
FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG "af29db7ec28d6df1c7f0f745186884091e602e07"
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(fmt googletest)

add_executable(${PROJECT_NAME}_test ${test_sources})
target_compile_features(${PROJECT_NAME}_test PRIVATE cxx_std_23)
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME} fmt gmock gtest_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_test)
