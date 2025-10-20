#pragma once

#include "Ast.hpp"

class ArithmeticExpressionNode: public ASTNode {
public:
    ArithmeticExpressionNode(int deep);

    ASTNode *process(ASTNode *parent, const EarleyItem &eItem, int deep) override;

    void addNode(std::unique_ptr<ASTNode> node) override;

    void printNode() override;

    void setOperator(const std::string &op);

    const std::unique_ptr<ASTNode>& getParam();

    const std::unique_ptr<ASTNode>& getExpression();

    

private:
    std::unique_ptr<ASTNode> m_param;
    std::string m_operator; // + - * /
    std::unique_ptr<ASTNode> m_expression;
};
