cmake_minimum_required(VERSION 3.25)
project(helloworld)

set(CMAKE_CXX_STANDARD 20)

add_executable(helloworld main.cpp observer_controller.h observable.h observable_impl.h observable_controller_getter.h)
