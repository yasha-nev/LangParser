cmake_minimum_required(VERSION 3.10)

project(LangParse)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

include(FetchContent)

FetchContent_Declare(
  nlohmann_json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.3
)

FetchContent_MakeAvailable(nlohmann_json)

set(HEADERS
    include/EarleyItem.hpp
    include/Lexer.hpp
    include/Lexem.hpp
    include/LexemCategory.hpp
    include/Parser.hpp
    include/Vocabulary.hpp
    include/Grammar.hpp
)

set(SOURCES
    main.cpp
    src/EarleyItem.cpp
    src/Lexer.cpp
    src/Lexem.cpp
    src/Parser.cpp
    src/Vocabulary.cpp
    src/Grammar.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)