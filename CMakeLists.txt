cmake_minimum_required(VERSION 3.10)

project(LangParse)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

set(HEADERS
    include/EarleyItem.hpp
    include/Lexer.hpp
    include/Lexem.hpp
    include/LexemCategory.hpp
    include/Parser.hpp
    include/Vocabulary.hpp
)

set(SOURCES
    main.cpp
    src/EarleyItem.cpp
    src/Lexer.cpp
    src/Lexem.cpp
    src/Parser.cpp
    src/Vocabulary.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})