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
  include/Application.hpp
  include/EarleyItem.hpp
  include/Grammar.hpp
  include/GrammarLoader.hpp
  include/Lexer.hpp
  include/Lexem.hpp
  include/LexemCategory.hpp
  include/Parser.hpp
  include/Vocabulary.hpp
  include/VocabularyLoader.hpp
  include/AST/Ast.hpp
  include/AST/RootNode.hpp
  include/AST/ValueNode.hpp
  include/AST/VariableNode.hpp
  include/AST/VariableDeclarationNode.hpp
  include/AST/AssigmentNode.hpp
  include/AST/ArithmeticExpressionNode.hpp
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
  src/Vocabulary.cpp
  src/VocabularyLoader.cpp
  src/AST/Ast.cpp
  src/AST/RootNode.cpp
  src/AST/ValueNode.cpp
  src/AST/VariableNode.cpp
  src/AST/VariableDeclarationNode.cpp
  src/AST/AssigmentNode.cpp
  #src/AST/ArithmeticExpressionNode.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)