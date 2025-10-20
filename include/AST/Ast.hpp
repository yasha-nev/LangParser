#pragma once

#include "EarleyItem.hpp"

#include <algorithm>
#include <list>
#include <vector>
#include <memory>
#include <set>

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
    ASTNode(int deep);

    virtual ~ASTNode() = default;

    virtual void addNode(std::unique_ptr<ASTNode> node) = 0;

    virtual ASTNode *process(ASTNode *parent, const EarleyItem &eItem, int deep) = 0;

    virtual void printNode() = 0;

    ASTNodeType getNodeType();

protected:
    int m_deep;
    ASTNodeType m_nodeType;
};

class RootNode;

class AST {
public:
    void buildTree(std::vector<Lexem>& tokens, std::set<EarleyItem>& items);

private:
    void buildTreeRecursive(ASTNode* node, std::set<EarleyItem>::iterator &it, std::set<EarleyItem>::iterator &end, int deep);
    std::unique_ptr<ASTNode> m_root;
};
