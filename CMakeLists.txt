cmake_minimum_required(VERSION 3.5)


set(TARGET_NAME "tarea1MIR")

project($(TARGET_NAME))
find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED COMPONENTS serialization filesystem system)


#include_directories(${Boost_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 11)

#set(CMAKE_CXX_FLAGS "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "-g")


set(SOURCE_FILES main.cpp src/FrameContainer.cpp src/FrameContainer.h src/FrameIndexes.cpp src/FrameIndexes.h src/FrameIndexContainer.cpp src/FrameIndexContainer.h src/SimilaritySearch.cpp src/SimilaritySearch.h src/QueryDistance.h src/EuclideanDistance.cpp src/EuclideanDistance.h src/InputFileControl.cpp src/InputFileControl.h)

add_executable(tarea1MIR ${SOURCE_FILES})
add_executable(weaculia testwea.cpp)
target_link_libraries(tarea1MIR ${Boost_LIBRARIES} ${OpenCV_LIBS} )
target_link_libraries(weaculia ${Boost_LIBRARIES} ${OpenCV_LIBS} )

