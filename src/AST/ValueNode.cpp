#include "AST/ValueNode.hpp"

ValueNode::ValueNode(DeclaretionType type, const std::string& value):
    ASTNode(),
    m_valueType(type),
    m_value(value) {
    m_nodeType = ASTNodeType::VALUE;
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
