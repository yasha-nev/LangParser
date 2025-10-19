#pragma once

#include "Ast.hpp"

class VariableNode: public ASTNode {
    VariableNode(const std::string& variable);

    void setVariable(const std::string& value);

    const std::string& getVariable();

private:
    std::string m_variable;
};
