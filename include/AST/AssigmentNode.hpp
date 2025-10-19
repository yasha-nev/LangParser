#pragma once

#include "ArithmeticExpressionNode.hpp"
#include "Ast.hpp"
#include "VariableNode.hpp"

class AssigmentNode: public ASTNode {
public:
    AssigmentNode();

    AssigmentNode(std::unique_ptr<ArithmeticExpressionNode> expression);

    void addVariable(std::unique_ptr<VariableNode> variable);

    const std::list<std::unique_ptr<VariableNode>>& getVariables();

    void setArithmeticExpression(std::unique_ptr<ArithmeticExpressionNode> node);

private:
    std::list<std::unique_ptr<VariableNode>> m_variables;
    std::unique_ptr<ArithmeticExpressionNode> m_expression;
};
