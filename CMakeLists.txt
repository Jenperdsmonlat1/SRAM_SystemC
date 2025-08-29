cmake_minimum_required(VERSION 3.0)

project(fundamental_of_computer_architecture_and_design)

set(SYSTEMC_HOME /home/rayane/systemc/install)
set(SYSTEMC_INCLUDE_DIR ${SYSTEMC_HOME}/include)
set(SYSTEMC_LIBRARY_DIR ${SYSTEMC_HOME}/lib)

add_executable(sram main.cpp)
target_include_directories(sram PRIVATE ${SYSTEMC_INCLUDE_DIR})
target_link_libraries(sram ${SYSTEMC_LIBRARY_DIR}/libsystemc.so)
