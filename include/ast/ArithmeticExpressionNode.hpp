#pragma once

#include "Ast.hpp"

class ArithmeticExpressionNode: public ASTNode {
public:
    ArithmeticExpressionNode();

    const std::list<std::unique_ptr<ASTNode>>& getNodes() override;

    void addNode(std::unique_ptr<ASTNode> node) override;

    void printNode(int deep) override;

    void setOperator(const std::string& op);

private:
    std::string m_operator; // + - * /
};
