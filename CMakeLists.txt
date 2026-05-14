
cmake_minimum_required(VERSION 3.31)
project(system_design)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ------------------- Core Library -------------------
add_library(rs_core STATIC
        # Source files
        src/Galios\ Field\ operations/GF2mAlpha.cpp
        src/Codeword/Codeword.cpp
        src/Codeword/Message.cpp
        src/Codeword/Encodedmessage.cpp
        src/Codeword/Generatorpolynomial.cpp
        src/Encoding/RSencoder.cpp
        src/Encoding/RSencoderInterface.cpp
        src/Decoding/RSFECdecoder.cpp
        src/Decoding/Syndrome.cpp
        src/Decoding/KeyequationEEA.cpp
        src/Decoding/Chiensearch.cpp
        src/Decoding/Forneyalgorithm.cpp
        src/Decoding/RSdecoder.cpp
        src/Decoding/RSFEDdecoder.cpp
        src/DecoderInterface/RSFECdecoderInterface.cpp
        src/DecoderInterface/RSFEDdecoderInterface.cpp
        src/DecoderInterface/RSdecoderInterface.cpp
        src/Channel\ Interface/ChannelInterfaceTransmitter.cpp
        src/Channel\ Interface/ChannelInterfaceReceiver.cpp

        # Header files
        include/Galios\ Field\ operations/GF2mAlpha.h
        include/Codeword/Codeword.h
        include/Codeword/Message.h
        include/Codeword/Encodedmessage.h
        include/Codeword/Generatorpolynomial.h
        include/Encoding/RSencoder.h
        include/Encoding/RSencoderInterface.h
        include/Decoding/RSFECdecoder.h
        include/Decoding/Syndrome.h
        include/Decoding/KeyequationEEA.h
        include/Decoding/Chiensearch.h
        include/Decoding/Forneyalgorithm.h
        include/Decoding/RSdecoder.h
        include/Decoding/RSFEDdecoder.h
        include/DecoderInterface/RSFECdecoderInterface.h
        include/DecoderInterface/RSFEDdecoderInterface.h
        include/DecoderInterface/RSdecoderInterface.h
        include/Channel\ Interface/ChannelInterfaceTransmitter.h
        include/Channel\ Interface/ChannelInterfaceReceiver.h
)

target_include_directories(rs_core PUBLIC include)

# ------------------- Main Executable -------------------
add_executable(system_design main.cpp)
target_link_libraries(system_design PRIVATE rs_core)

# ------------------- GoogleTest Setup -------------------
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# ------------------- Unit Test Executable -------------------
add_executable(UnitTests
        test/main.cpp
        test/test_RSencoderInterface.cpp
        test/test_GF2mAlpha.cpp
        test/test_Codeword.cpp
        test/test_Generatorpolynomial.cpp
        test/test_Syndrome.cpp
        test/test_KeyEquation.cpp
        test/test_Chiensearch.cpp
        test/test_RSFECdecoder.cpp
        test/test_RSFEDdecoder.cpp
        test/test_RSdecoder.cpp
        test/test_RSencoder1.cpp
)

target_link_libraries(UnitTests
        gtest_main
        gmock
        rs_core
)

include(GoogleTest)
gtest_discover_tests(UnitTests)
