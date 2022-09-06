project(binarycoder)

include_directories(include)
include_directories(ThirdParty/std2/include)

add_executable(binarycoder src/BinaryCoder.cc src/NativeTypes.cc)
