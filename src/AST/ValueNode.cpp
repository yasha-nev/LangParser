#include "ast/ValueNode.hpp"

ValueNode::ValueNode(int deep, DeclaretionType type, const std::string& value):
    ASTNode(deep),
    m_valueType(type),
    m_value(value) {
    m_nodeType = ASTNodeType::VALUE;
}

ASTNode *ValueNode::process(ASTNode *parent, const EarleyItem &eItem, int deep) {

}

void ValueNode::addNode(std::unique_ptr<ASTNode> node) {

}

void ValueNode::printNode() {
    std::cout << "|" << std::string(m_deep, '-') << "- Value:" << m_value << " : " << declarationTypeToString(m_valueType) << "\n";
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

