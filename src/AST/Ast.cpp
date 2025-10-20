#include "ast/Ast.hpp"
#include "ast/RootNode.hpp"
#include "ast/VariableDeclarationNode.hpp"
#include "ast/VariableNode.hpp"
#include "ast/ValueNode.hpp"
#include "ast/AssigmentNode.hpp"
#include "ast/ArithmeticExpressionNode.hpp"

ASTNode::ASTNode(int deep) {
    m_deep = deep;
    m_nodeType = ASTNodeType::DEFAULT;
}

ASTNodeType ASTNode::getNodeType() {
    return m_nodeType;
}

void AST::buildTree(std::vector<Lexem>& tokens, std::set<EarleyItem>& eItems) {
    ASTNode *currentNode;

    auto itr =  eItems.begin();
    auto end = eItems.end();

    buildTreeRecursive(currentNode, itr, end, 0);

    if (m_root) {
        m_root->printNode();
    }
}

void AST::buildTreeRecursive(ASTNode* node, std::set<EarleyItem>::iterator &it, std::set<EarleyItem>::iterator &end, int deep) {
    if (it == end) {
        return;
    }

    deep++;

    if ((*it).getVn() == "1A") {
        
        buildTreeRecursive(node, ++it, end, deep);

    } else if ((*it).getVn() == "A") {
        m_root =  std::make_unique<RootNode>(--deep);

        buildTreeRecursive(m_root.get(), ++it, end, deep);

    } else if ((*it).getVn() == "A0") {
        RootNode * rootNode = static_cast<RootNode *> (node);
        for (const auto &r : (*it).getRule()) {
            if (r == "A0") {
                
                buildTreeRecursive(node, ++it, end, --deep);

            } else if (r == "B") {
                std::unique_ptr<VariableDeclarationNode> ptr = std::make_unique<VariableDeclarationNode>(--deep);
                
                rootNode->addNode(std::move(ptr));
                const auto &list = rootNode->getNodes();

                buildTreeRecursive(list.back().get(), ++it, end, deep);
            } else if (r == "C"){
                buildTreeRecursive(rootNode, ++it, end, deep);
            }
        }
    } else if ((*it).getVn() == "B") {
        VariableDeclarationNode* variableDeclarationNode = static_cast<VariableDeclarationNode *> (node);

        for (const auto &r : (*it).getRule()) {
            if (r == "E") {
                std::unique_ptr<VariableNode> variableNode = std::make_unique<VariableNode>(deep);
                
                variableDeclarationNode->addNode(std::move(variableNode));
                const auto &list = variableDeclarationNode->getVariables();

                buildTreeRecursive(list.back().get(), ++it, end, deep);
                ++it;
            } else if (r == "TYPES"){
                variableDeclarationNode->setVariablesType(DeclaretionType::INT);
            }
        }
    } else if ((*it).getVn() == "C") {
        RootNode * rootNode = static_cast<RootNode *> (node);
        for (const auto &rule : (*it).getRule() ) {
            if (rule == "D") {
                std::unique_ptr<AssigmentNode> assigmentNode = std::make_unique<AssigmentNode>(deep);
                
                rootNode->addNode(std::move(assigmentNode));
                const auto &list = rootNode->getNodes();

                buildTreeRecursive(list.back().get(), ++it, end, deep);
            }
        }
    } else if ((*it).getVn() == "D") {
        AssigmentNode * assigmentNode = static_cast<AssigmentNode *> (node);
        for (const auto &rule : (*it).getRule() ) {
            if (rule == "E") {
                std::unique_ptr<VariableNode> variableNode = std::make_unique<VariableNode>(deep);
                
                assigmentNode->addNode(std::move(variableNode));
                const auto &list = assigmentNode->getVariables();

                buildTreeRecursive(list.back().get(), ++it, end, deep);
            } else if (rule == "G") {
                std::unique_ptr<ArithmeticExpressionNode> arithmeticExpressionNode = std::make_unique<ArithmeticExpressionNode>(deep);
                
                assigmentNode->addNode(std::move(arithmeticExpressionNode));
                const auto &expression = assigmentNode->getExpression();

                buildTreeRecursive(expression.get(), ++it, end, deep);
            }
        }
    } else if ((*it).getVn() == "E") {
        VariableNode* variableNode = static_cast<VariableNode *> (node);
        std::string var = "aaa";
        variableNode->setVariable(var);
    
    } else if ((*it).getVn() == "G") {
        ArithmeticExpressionNode * arithmeticExpressionNode = static_cast<ArithmeticExpressionNode *> (node);
        for (const auto &rule : (*it).getRule() ) {
            if (rule == "H") {
                buildTreeRecursive(arithmeticExpressionNode, ++it, end, deep);
                ++it;
            }
        }
    } else if ((*it).getVn() == "H") {
        for (const auto &rule : (*it).getRule() ) {
            ArithmeticExpressionNode * arithmeticExpressionNode = static_cast<ArithmeticExpressionNode *> (node);
            if (rule == "VALUE") {
                std::string var = "10";
                std::unique_ptr<ValueNode> valueNode = std::make_unique<ValueNode>(deep, DeclaretionType::INT, var);
                
                arithmeticExpressionNode->addNode(std::move(valueNode));
            } else if (rule == "VARIABLE") {
                std::string var = "aaa";
                std::unique_ptr<VariableNode> variableNode = std::make_unique<VariableNode>(deep, var);
                
                arithmeticExpressionNode->addNode(std::move(variableNode));
            }
        }
    }
}
