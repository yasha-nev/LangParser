#pragma once

#include "Ast.hpp"

class AssigmentNode: public ASTNode {
public:
    AssigmentNode(int deep);

    ASTNode *process(ASTNode *parent, const EarleyItem &eItem, int deep) override;

    void addNode(std::unique_ptr<ASTNode> node) override;

    void printNode() override;

    const std::list<std::unique_ptr<ASTNode>>& getVariables();

    const std::unique_ptr<ASTNode> &getExpression();

    

private:
    std::list<std::unique_ptr<ASTNode>> m_variables;
    std::unique_ptr<ASTNode> m_expression;
};
