#include "ast/ValueNode.hpp"

ValueNode::ValueNode(DeclaretionType type, const std::string& value):
    ASTNode(),
    m_valueType(type),
    m_value(value) {
    m_nodeType = ASTNodeType::VALUE;
}

const std::list<std::unique_ptr<ASTNode>>& ValueNode::getNodes() {
    return m_nodes;
}

void ValueNode::addNode([[maybe_unused]] std::unique_ptr<ASTNode> node) {
}

void ValueNode::printNode(int deep) {
    std::cout << "|" << std::string(deep, '-') << " Value: " << m_value << " : "
              << declarationTypeToString(m_valueType) << "\n";
}

void ValueNode::setValue(const std::string& value) {
    m_value = value;
}

const std::string& ValueNode::getValue() {
    return m_value;
}

void ValueNode::setValueType(DeclaretionType valueType) {
    m_valueType = valueType;
}

DeclaretionType ValueNode::getValueType() {
    return m_valueType;
}
