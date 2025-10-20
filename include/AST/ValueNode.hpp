#pragma once

#include "Ast.hpp"
#include "VariableDeclarationNode.hpp"

class ValueNode: public ASTNode {
public:
    ValueNode(int deep, DeclaretionType type, const std::string& value);

    ASTNode *process(ASTNode *parent, const EarleyItem &eItem, int deep) override;

    void addNode(std::unique_ptr<ASTNode> node) override;

    void printNode() override;

    void setValue(const std::string& value);

    void setValueType(DeclaretionType valueType);

    const std::string& getValue();

    DeclaretionType getValueType();

private:
    DeclaretionType m_valueType;
    std::string m_value;
};
