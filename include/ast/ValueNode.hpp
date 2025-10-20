#pragma once

#include "Ast.hpp"
#include "VariableDeclarationNode.hpp"

class ValueNode: public ASTNode {
public:
    ValueNode(DeclaretionType type, const std::string& value);

    const std::list<std::unique_ptr<ASTNode>>& getNodes() override;

    void addNode(std::unique_ptr<ASTNode> node) override;

    void printNode(int deep) override;

    void setValue(const std::string& value);

    void setValueType(DeclaretionType valueType);

    const std::string& getValue();

    DeclaretionType getValueType();

private:
    DeclaretionType m_valueType;
    std::string m_value;
};
