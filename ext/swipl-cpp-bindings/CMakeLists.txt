cmake_minimum_required(VERSION 2.6)

include(ExternalProject)

ExternalProject_Add(plbindings
  URL "${CMAKE_CURRENT_SOURCE_DIR}/src"
  CMAKE_ARGS -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
    -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
  PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
)

ExternalProject_Get_Property(plbindings source_dir)
ExternalProject_Get_Property(plbindings binary_dir)

set(PLBINDINGS_PROJECT_NAME "plbindings" PARENT_SCOPE)
set(PLBINDINGS_INCLUDE_DIRS ${source_dir}/include PARENT_SCOPE)
set(PLBINDINGS_LIBS_DIR ${binary_dir}/lib PARENT_SCOPE)
set(PLBINDINGS_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src" PARENT_SCOPE)

