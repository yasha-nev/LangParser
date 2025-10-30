#pragma once

#include "AST.hpp"

class ArithmeticExpressionNode: public ASTNode {
public:
    ArithmeticExpressionNode();

    const std::list<std::unique_ptr<ASTNode>>& getNodes() const noexcept override;

    void addNode(std::unique_ptr<ASTNode> node) override;

    void setOperator(int op);

    int getOperator() const noexcept;

private:
    int m_operator;
};
