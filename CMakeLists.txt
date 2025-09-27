cmake_minimum_required(VERSION 3.10)

project(LangParse)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

set(HEADERS
    include/EarleyItem.hpp
    include/LexemAnalizator.hpp
    include/Lexem.hpp
    include/LexemType.hpp
    include/Parser.hpp
)

set(SOURCES
    main.cpp
    src/EarleyItem.cpp
    src/LexemAnalizator.cpp
    src/Lexem.cpp
    src/LexemType.cpp
    src/Parser.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})