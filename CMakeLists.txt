cmake_minimum_required(VERSION 4.1 FATAL_ERROR)

set(CMAKE_CXX_MODULE_STD ON)
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD 451f2fe2-a8a2-47c3-bc32-94786d8fc91b)

project(cpplabs LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR
   CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Weffc++ -Wextra -Wpedantic")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  endif()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8 /W4")
endif()

add_library(UValue STATIC)
target_sources(UValue
  PUBLIC
  FILE_SET CXX_MODULES
  FILES
  src/utils/UValue.cppm
)

add_library(api STATIC)
target_sources(api
  PUBLIC
  FILE_SET CXX_MODULES
  FILES
  src/api/api.ixx
  src/api/Serializable.cppm
  src/api/Serializer.cppm
)
target_link_libraries(api PUBLIC UValue)

add_library(serializers STATIC)
target_sources(serializers
  PUBLIC
  FILE_SET CXX_MODULES
  FILES
  src/serializers/serializers.ixx
  src/serializers/BinarySerializer.cppm
  src/serializers/JsonSerializer.cppm
  src/serializers/User.cppm
  src/serializers/XmlSerializer.cppm
)
target_link_libraries(serializers PUBLIC
  api
  UValue
)

add_executable(main)

target_compile_features(main PRIVATE cxx_std_23)
target_sources(main PRIVATE src/main.cpp)
target_link_libraries(main PRIVATE serializers)
