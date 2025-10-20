#pragma once

#include "Ast.hpp"

class VariableNode: public ASTNode {
public:
    VariableNode(int deep);

    VariableNode(int deep, const std::string& variable);

    ASTNode *process(ASTNode *parent, const EarleyItem &eItem, int deep) override;

    void addNode(std::unique_ptr<ASTNode> node) override;

    void printNode() override;

    void setVariable(const std::string& value);

    const std::string& getVariable();

private:
    std::string m_variable;
};
