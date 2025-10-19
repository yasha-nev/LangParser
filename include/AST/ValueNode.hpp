#pragma once

#include "Ast.hpp"
#include "VariableDeclarationNode.hpp"

class ValueNode: public ASTNode {
    ValueNode(DeclaretionType type, const std::string& value);

    void setValue(const std::string& value);

    const std::string& getValue();

    void setValueType(DeclaretionType valueType);

    DeclaretionType getValueType();

private:
    DeclaretionType m_valueType;
    std::string m_value;
};
