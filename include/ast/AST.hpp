#pragma once

#include <list>
#include <memory>

enum class ASTNodeType {
    DEFAULT = 0,
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

    virtual const std::list<std::unique_ptr<ASTNode>>& getNodes() = 0;

    virtual void addNode(std::unique_ptr<ASTNode> node) = 0;

    virtual void printNode(int deep) = 0;

    ASTNodeType getNodeType();

protected:
    ASTNodeType m_nodeType;

    std::list<std::unique_ptr<ASTNode>> m_nodes;
};

class ASTBuilder;

class AST {
public:
    AST(std::unique_ptr<ASTNode> root);

    void printTree();

private:
    std::unique_ptr<ASTNode> m_root;

    friend ASTBuilder;
};
