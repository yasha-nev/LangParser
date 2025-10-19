#pragma once

#include "Ast.hpp"
#include "VariableNode.hpp"

enum class DeclaretionType {
    INT,
    FLOAT,
    BOOL,
};

class VariableDeclarationNode: public ASTNode {
public:
    VariableDeclarationNode();

    VariableDeclarationNode(DeclaretionType variable_type);

    DeclaretionType getVariablesType();

    void setVariablesType(DeclaretionType type);

    const std::list<std::unique_ptr<VariableNode>>& getVariables();

    void addVariable(std::unique_ptr<VariableNode> variable);

private:
    std::list<std::unique_ptr<VariableNode>> m_variables;
    DeclaretionType m_variableType;
};
