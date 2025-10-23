#pragma once

#include "AST.hpp"

#include <iostream>
#include <string>

class VariableNode: public ASTNode {
public:
    VariableNode();

    VariableNode(const std::string& variable);

    const std::list<std::unique_ptr<ASTNode>>& getNodes() override;

    void addNode(std::unique_ptr<ASTNode> node) override;

    void printNode(int deep) override;

    void setVariable(const std::string& value);

    const std::string& getVariable();

private:
    std::string m_variable;
};
