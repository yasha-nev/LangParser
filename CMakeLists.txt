cmake_minimum_required(VERSION 3.10)

project(LangParse)

set(CMAKE_CXX_STANDARD 17)
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
  include/Application.hpp
  include/EarleyItem.hpp
  include/Grammar.hpp
  include/GrammarLoader.hpp
  include/Lexer.hpp
  include/Lexem.hpp
  include/LexemCategory.hpp
  include/Parser.hpp
  include/Render.hpp
  include/Vocabulary.hpp
  include/VocabularyLoader.hpp
  include/ast/Ast.hpp
  include/ast/RootNode.hpp
  include/ast/ValueNode.hpp
  include/ast/VariableNode.hpp
  include/ast/VariableDeclarationNode.hpp
  include/ast/AssigmentNode.hpp
  include/ast/ArithmeticExpressionNode.hpp
)

set(SOURCES
  main.cpp
  src/Application.cpp
  src/EarleyItem.cpp
  src/Grammar.cpp
  src/GrammarLoader.cpp
  src/Lexer.cpp
  src/Lexem.cpp
  src/Parser.cpp
  src/Render.cpp
  src/Vocabulary.cpp
  src/VocabularyLoader.cpp
  src/ast/Ast.cpp
  src/ast/RootNode.cpp
  src/ast/ValueNode.cpp
  src/ast/VariableNode.cpp
  src/ast/VariableDeclarationNode.cpp
  src/ast/AssigmentNode.cpp
  src/ast/ArithmeticExpressionNode.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)