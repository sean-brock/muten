# Testing library
FetchContent_Declare(
  catch
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v2.13.6)
FetchContent_MakeAvailable(catch)

add_executable(hipcpu test_hipcpu.cpp)
target_compile_features(hipcpu PRIVATE cxx_std_20)
target_link_libraries(hipcpu PRIVATE hip_cpu_rt::hip_cpu_rt Catch2::Catch2)
add_test(NAME test_hipcpu COMMAND hipcpu)

add_executable(tensor test_tensor.cpp)
target_compile_features(tensor PRIVATE cxx_std_20)
target_link_libraries(tensor PRIVATE muten_library Catch2::Catch2)
add_test(NAME test_tensor COMMAND tensor)
