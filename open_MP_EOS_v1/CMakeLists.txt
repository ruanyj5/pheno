cmake_minimum_required(VERSION 3.15)
project(open_MP_EOS_v1)

set(CMAKE_CXX_STANDARD 20)

# set multi .cpp
aux_source_directory(. DIRSRCS)
add_executable(open_MP_EOS_v1 ${DIRSRCS})


target_link_libraries(open_MP_EOS_v1 gdal)

set(CMAKE_C_FLAGS "-fopenmp")
set(CMAKE_CXX_FLAGS "-fopenmp")


