#pragma once

#include <list>
#include <memory>

enum class ASTNodeType {
    DEFAULT = 0,
    ROOT,
    VARIABLE_DECLARATION,
    ASSIGMENTS,
    LOOP,
    BRANCH,
    CONTROL,
    CONDITION_EXPRESSION,
    ARITHMETIC_EXPRESSION,
    VARIABLE,
    VALUE
};

class ASTNode {
public:
    ASTNode();

    virtual ~ASTNode() = default;

    virtual const std::list<std::unique_ptr<ASTNode>>& getNodes() const noexcept = 0;

    virtual void addNode(std::unique_ptr<ASTNode> node) = 0;

    ASTNodeType getNodeType() const noexcept;

protected:
    ASTNodeType m_nodeType;

    std::list<std::unique_ptr<ASTNode>> m_nodes;
};

class AST {
public:
    AST(std::unique_ptr<ASTNode> root);

    const std::unique_ptr<ASTNode>& getRootNode() const noexcept;

private:
    std::unique_ptr<ASTNode> m_root;
};
