#pragma once

#include "AST.hpp"
#include "VariableDeclarationNode.hpp"

#include <iostream>
#include <string>

class ValueNode: public ASTNode {
public:
    ValueNode(int type, const std::string& value);

    const std::list<std::unique_ptr<ASTNode>>& getNodes() const noexcept override;

    void addNode(std::unique_ptr<ASTNode> node) override;

    void setValue(const std::string& value);

    void setValueType(int valueType);

    const std::string& getValue() const noexcept;

    int getValueType() const noexcept;

private:
    int m_valueType;
    std::string m_value;
};
