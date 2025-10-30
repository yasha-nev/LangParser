#include "ast/ValueNode.hpp"

ValueNode::ValueNode(int type, const std::string& value):
    ASTNode(),
    m_valueType(type),
    m_value(value) {
    m_nodeType = ASTNodeType::VALUE;
}

const std::list<std::unique_ptr<ASTNode>>& ValueNode::getNodes() const noexcept {
    return m_nodes;
}

void ValueNode::addNode([[maybe_unused]] std::unique_ptr<ASTNode> node) {
}

void ValueNode::setValue(const std::string& value) {
    m_value = value;
}

const std::string& ValueNode::getValue() const noexcept {
    return m_value;
}

void ValueNode::setValueType(int valueType) {
    m_valueType = valueType;
}

int ValueNode::getValueType() const noexcept {
    return m_valueType;
}
