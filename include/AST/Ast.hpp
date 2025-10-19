#pragma once

#include "EarleyItem.hpp"

#include <algorithm>
#include <list>
#include <memory>
#include <set>

enum class ASTNodeType {
    DEFAULT,
    ROOT,
    VARIABLE_DECLARATION,
    ASSIGMENTS,
    CONTROL,
    ARITHMETIC_EXPRESSION,
    VARIABLE,
    VALUE
};

class ASTNode {
public:
    ASTNode();

    virtual ~ASTNode() = default;

    ASTNodeType getNodeType();

protected:
    ASTNodeType m_nodeType;
};

class AST {
public:
    void buildTree(const std::set<Lexem>& tokens, const std::set<EarleyItem>& items);

private:
    std::unique_ptr<ASTNode> root;
};
