set(test_sources
    "${CMAKE_CURRENT_SOURCE_DIR}/chrono.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/console.cpp"
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
FetchContent_Declare(date
    GIT_REPOSITORY https://github.com/HowardHinnant/date.git
    GIT_TAG "22ceabf205d8d678710a43154da5a06b701c5830"
)
FetchContent_Declare(fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG "c4ee726532178e556d923372f29163bd206d7732"
)
FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG "61720589cbef9707b3c5247d02141a7c31e2876f"
)
FetchContent_Declare(range-v3
    GIT_REPOSITORY https://github.com/ericniebler/range-v3.git
    GIT_TAG "0fa54d7de5dc00655e38a08e87cda61f7aa6d5b9"
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(date fmt googletest range-v3)

add_executable(${PROJECT_NAME}_test ${test_sources})
if(MSVC)
    target_compile_features(${PROJECT_NAME}_test PRIVATE cxx_std_23)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    target_compile_features(${PROJECT_NAME}_test PRIVATE cxx_std_20)
endif()
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME} date fmt gmock gtest_main range-v3)
if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    target_compile_options(${PROJECT_NAME}_test PRIVATE -DLIBCXX_ENABLE_INCOMPLETE_FEATURES=ON)
endif()

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_test)
