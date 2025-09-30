# LangParser

## Overview
This project implements simple **lexical** and **syntactic** analyzers for pseudocode.  
It is designed to demonstrate how a custom lexer and parser can work together to process source code, transform it into tokens, and validate it against a defined grammar.

The system consists of:
- **Lexer** – transforms source code into a sequence of tokens.
- **Parser** – validates the sequence of tokens using grammar rules and constructs a parsing table.

The syntactic analysis is based on the **Earley parsing algorithm**, which is capable of parsing any context-free grammar, including ambiguous ones.

## Build
```
cmake -B build
cmake --build build -j
```

## Start
```
./build/LangParse json/grammar.json json/vocabulary.json source.code
```

## P.S.
The project is under active development.
In the future, the following features are planned:
Construction of an AST (Abstract Syntax Tree)
Generation of an IR (Intermediate Representation)
Implementation of a full compiler on top of the current analyzer