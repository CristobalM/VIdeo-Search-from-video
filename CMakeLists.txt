cmake_minimum_required(VERSION 3.5)


set(TARGET_NAME "tarea1MIR")

project(tarea1MIR)
find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED COMPONENTS serialization filesystem system)


#include_directories(${Boost_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 11)

#set(CMAKE_CXX_FLAGS "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "-g")

set(BASE_SOURCE src/FrameContainer.cpp src/FrameContainer.h
        src/FrameIndexes.cpp src/FrameIndexes.h
        src/FrameIndexContainer.cpp src/FrameIndexContainer.h
        src/SimilaritySearch.cpp src/SimilaritySearch.h
        src/QueryDistance.cpp src/QueryDistance.h
        src/EuclideanDistance.cpp src/EuclideanDistance.h
        src/InputFileControl.cpp src/InputFileControl.h
        src/VideoContainer.cpp src/VideoContainer.h
        src/ManhattanDistance.cpp src/ManhattanDistance.h
        src/VideoFinder.cpp src/VideoFinder.h
        src/VideoFindResult.cpp src/VideoFindResult.h)

add_library(tarea1MIRLib ${BASE_SOURCE})
#set(SOURCE_FILES main.cpp ${BASE_SOURCE})

add_executable(ExtraccionCaracteristicas extraccion_caracteristicas.cpp )
add_executable(BusquedaPorSimilitud busqueda_similitud.cpp )
add_executable(DeteccionDeApariciones deteccion_apariciones.cpp )

#add_executable(tarea1MIR main.cpp)
target_link_libraries(tarea1MIRLib ${Boost_LIBRARIES} ${OpenCV_LIBS} )

target_link_libraries(ExtraccionCaracteristicas tarea1MIRLib)
target_link_libraries(BusquedaPorSimilitud tarea1MIRLib)
target_link_libraries(DeteccionDeApariciones tarea1MIRLib)
#target_link_libraries(tarea1MIR tarea1MIRLib)

