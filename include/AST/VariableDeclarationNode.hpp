#pragma once

#include "Ast.hpp"

enum class DeclaretionType {
    INT,
    FLOAT,
    BOOL,
};

std::string declarationTypeToString(DeclaretionType type);

class VariableDeclarationNode: public ASTNode {
public:
    VariableDeclarationNode(int deep);

    VariableDeclarationNode(int deep, DeclaretionType variable_type);

    ASTNode *process(ASTNode *parent, const EarleyItem &eItem, int deep) override;

    void addNode(std::unique_ptr<ASTNode> node) override;

    void printNode() override;

    void setVariablesType(DeclaretionType type);

    const std::list<std::unique_ptr<ASTNode>>& getVariables();

    DeclaretionType getVariablesType();

private:
    std::list<std::unique_ptr<ASTNode>> m_variables;
    DeclaretionType m_variableType;
};
