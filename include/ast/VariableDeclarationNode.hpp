#pragma once

#include "AST.hpp"

class VariableDeclarationNode: public ASTNode {
public:
    VariableDeclarationNode();

    VariableDeclarationNode(int variableType);

    const std::list<std::unique_ptr<ASTNode>>& getNodes() const noexcept override;

    void addNode(std::unique_ptr<ASTNode> node) override;

    void setVariablesType(int type);

    int getVariablesType() const noexcept;

private:
    int m_variableType;
};
