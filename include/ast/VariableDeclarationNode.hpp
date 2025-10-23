#pragma once

#include "AST.hpp"

#include <iostream>

enum class DeclaretionType {
    INT,
    FLOAT,
    BOOL,
};

std::string declarationTypeToString(DeclaretionType type);

class VariableDeclarationNode: public ASTNode {
public:
    VariableDeclarationNode();

    VariableDeclarationNode(DeclaretionType variable_type);

    const std::list<std::unique_ptr<ASTNode>>& getNodes() override;

    void addNode(std::unique_ptr<ASTNode> node) override;

    void printNode(int deep) override;

    void setVariablesType(DeclaretionType type);

    DeclaretionType getVariablesType();

private:
    DeclaretionType m_variableType;
};
