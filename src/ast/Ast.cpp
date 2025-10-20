#include "ast/Ast.hpp"

#include "ast/ArithmeticExpressionNode.hpp"
#include "ast/AssigmentNode.hpp"
#include "ast/RootNode.hpp"
#include "ast/ValueNode.hpp"
#include "ast/VariableDeclarationNode.hpp"
#include "ast/VariableNode.hpp"

ASTNode::ASTNode() {
    m_nodeType = ASTNodeType::DEFAULT;
}

ASTNodeType ASTNode::getNodeType() {
    return m_nodeType;
}

void AST::buildTree(std::vector<Lexem>& tokens, std::set<EarleyItem>& eItems) {
    ASTNode* currentNode;

    auto itr = eItems.begin();
    auto end = eItems.end();

    if(itr != end) {
        buildTreeRecursive(currentNode, ++itr, end);
    }

    if(m_root) {
        m_root->printNode(0);
    }
}

void AST::buildTreeRecursive(ASTNode* node, eItemCurrent& it, eItemEnd& end) {
    if(it == end) {
        return;
    }

    if((*it).getVn() == "A") {
        buildTreeRecursive(buildA(node), ++it, end);

    } else if((*it).getVn() == "A0") {
        for(const auto& r: (*it).getRule()) {
            if(r == "A0") {
                buildTreeRecursive(node, ++it, end);
            } else if(r == "B") {
                buildTreeRecursive(buildB(node), ++it, end);
            } else if(r == "C") {
                buildTreeRecursive(node, ++it, end);
            }
        }
    } else if((*it).getVn() == "B") {
        VariableDeclarationNode* variableDeclarationNode = static_cast<VariableDeclarationNode*>(
            node);
        for(const auto& r: (*it).getRule()) {
            if(r == "E") {
                buildTreeRecursive(buildE(variableDeclarationNode), ++it, end);
            } else if(r == "TYPES") {
                variableDeclarationNode->setVariablesType(DeclaretionType::INT);
            }
        }
    } else if((*it).getVn() == "C") {
        for(const auto& rule: (*it).getRule()) {
            if(rule == "D") {
                buildTreeRecursive(buildD(node), ++it, end);
            }
        }
    } else if((*it).getVn() == "D") {
        for(const auto& rule: (*it).getRule()) {
            if(rule == "E") {
                buildTreeRecursive(buildE(node), ++it, end);
            } else if(rule == "G") {
                buildTreeRecursive(buildG(node), ++it, end);
            }
        }
    } else if((*it).getVn() == "E") {
        for(const auto& rule: (*it).getRule()) {
            if(rule == "E") {
                buildTreeRecursive(buildE(node), ++it, end);
            } else if("VARIABLES") {
                buildVariable(node);
            }
        }
    } else if((*it).getVn() == "G") {
        auto gNode = static_cast<ArithmeticExpressionNode*>(node);
        for(const auto& rule: (*it).getRule()) {
            if(rule == "G") {
                buildTreeRecursive(buildG(gNode), ++it, end);
            } else if(rule == "+" || rule == "-" || rule == "*" || rule == "//") {
                gNode->setOperator(rule);
            } else if(rule == "VALUE") {
                buildValue(node);
            } else if(rule == "VARIABLES") {
                buildVariable(node);
            }
        }
    }
}

ASTNode* AST::buildA(ASTNode* node) {
    m_root = std::make_unique<RootNode>();
    return m_root.get();
}

ASTNode* AST::buildB(ASTNode* node) {
    std::unique_ptr<VariableDeclarationNode> ptr = std::make_unique<VariableDeclarationNode>();

    node->addNode(std::move(ptr));
    const auto& list = node->getNodes();

    return list.back().get();
}

ASTNode* AST::buildD(ASTNode* node) {
    std::unique_ptr<AssigmentNode> assigmentNode = std::make_unique<AssigmentNode>();

    node->addNode(std::move(assigmentNode));
    const auto& list = node->getNodes();

    return list.back().get();
}

ASTNode* AST::buildE(ASTNode* node) {
    return node;
}

ASTNode* AST::buildG(ASTNode* node) {
    std::unique_ptr<ArithmeticExpressionNode>
        arithmeticExpressionNode = std::make_unique<ArithmeticExpressionNode>();

    node->addNode(std::move(arithmeticExpressionNode));
    const auto& list = node->getNodes();

    return list.back().get();
}

ASTNode* AST::buildValue(ASTNode* node) {
    std::string var = "10";

    std::unique_ptr<ValueNode> valueNode = std::make_unique<ValueNode>(DeclaretionType::INT, var);
    node->addNode(std::move(valueNode));

    return nullptr;
}

ASTNode* AST::buildVariable(ASTNode* node) {
    std::string var = "aaa";

    std::unique_ptr<VariableNode> variableNode = std::make_unique<VariableNode>(var);
    node->addNode(std::move(variableNode));

    return nullptr;
}
