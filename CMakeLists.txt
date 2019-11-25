cmake_minimum_required(VERSION 3.2)

project(matrix VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

add_subdirectory(src)
//add_subdirectory(tests)

//enable_testing()
