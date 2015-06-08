cmake_minimum_required(VERSION 2.6)

project(swipl_cpp_lp)

add_subdirectory("ext/swipl-cpp-bindings")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PLBINDINGS_SRC_DIR}/cmake/modules/")

include(CTest)
include(SPCFindCPP11)
include(SPCFindSWIProlog)

include_directories("${CMAKE_SOURCE_DIR}/include" "${SPC_SWIPL_INCLUDE_DIRS}" "${PLBINDINGS_SRC_DIR}/include")

add_definitions("${SPC_SWIPL_DEFS}")
link_directories("${SPC_SWIPL_LINK_DIR}" "${PLBINDINGS_LIBS_DIR}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SPC_CPP11_FLAGS} ${SPC_SWIPL_CXX_FLAGS} -Wall")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
add_library(swiplcpplp SHARED src/Properties.cpp)
target_link_libraries(swiplcpplp swiplcpp)
add_dependencies(swiplcpplp ${PLBINDINGS_PROJECT_NAME})

install(TARGETS swiplcpplp DESTINATION lib)
install(FILES
  include/Properties.h include/PropertyBag.h
  include/PropertyGenerator.h include/PropertyMap.h
  include/PropertyVault.h
  DESTINATION include)

add_subdirectory("ext/gtest")
add_subdirectory("tests")

