#pragma once

#include "EarleyItem.hpp"

#include <algorithm>
#include <list>
#include <memory>
#include <set>
#include <vector>

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

using eItemCurrent = std::set<EarleyItem>::iterator;
using eItemEnd = std::set<EarleyItem>::iterator;

class RootNode;

class AST {
public:
    void buildTree(std::vector<Lexem>& tokens, std::set<EarleyItem>& items);

private:
    void buildTreeRecursive(ASTNode* node, eItemCurrent& it, eItemEnd& end);

    ASTNode* buildA(ASTNode* node);

    ASTNode* buildB(ASTNode* node);

    ASTNode* buildD(ASTNode* node);

    ASTNode* buildE(ASTNode* node);

    ASTNode* buildG(ASTNode* node);

    ASTNode* buildValue(ASTNode* node);

    ASTNode* buildVariable(ASTNode* node);

    std::unique_ptr<ASTNode> m_root;
};
