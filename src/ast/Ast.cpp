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

AST::AST(Vocabulary& vocabulary):
    m_vocabulary(vocabulary) {
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

    static std::map<int, std::function<void(ASTNode * node, eItemCurrent & it, eItemEnd & end)>> test = {
        { m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "A"),
          [=](ASTNode* n, eItemCurrent& it, eItemEnd& end) {
              return buildTreeRecursive(buildA(n), ++it, end);
          } },
        { m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "A0"),
          [=](ASTNode* n, eItemCurrent& it, eItemEnd& end) {
              return buildTreeRecursive(n, ++it, end);
          } },
        { m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "B"),
          [=](ASTNode* n, eItemCurrent& it, eItemEnd& end) {
              return buildTreeRecursive(buildB(n), ++it, end);
          } },
        { m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "C"),
          [=](ASTNode* n, eItemCurrent& it, eItemEnd& end) {
              return buildTreeRecursive(n, ++it, end);
          } },
        { m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "D"),
          [=](ASTNode* n, eItemCurrent& it, eItemEnd& end) {
              return buildTreeRecursive(buildD(n), ++it, end);
          } },
        { m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "E"),
          [=](ASTNode* n, eItemCurrent& it, eItemEnd& end) {
              return buildTreeRecursive(buildE(n), ++it, end);
          } },
        { m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "G"),
          [=](ASTNode* n, eItemCurrent& it, eItemEnd& end) {
              return buildTreeRecursive(buildG(n), ++it, end);
          } },
        { m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "TYPES"),
          [=](ASTNode* n, eItemCurrent& it, eItemEnd& end) { return; } },
        { m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "VALUE"),
          [=](ASTNode* n, eItemCurrent& it, eItemEnd& end) { return buildValue(n); } },
        { m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "VARIABLES"),
          [=](ASTNode* n, eItemCurrent& it, eItemEnd& end) { return buildVariable(n); } }
    };

    if((*it).getVn() == m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "A")) {
        buildTreeRecursive(buildA(node), ++it, end);
    }

    for(const auto& rule: (*it).getRule()) {
        std::cout << "rule: "<< m_vocabulary.getWord(rule).second << "\n";
        if(m_vocabulary.getWord(rule).first == LexemCategory::NOTERMINAL) {
            test[rule](node, it, end);
        }
    }

    /*if((*it).getVn() == m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "A")) {
        buildTreeRecursive(buildA(node), ++it, end);
    } else if((*it).getVn() == m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "A0")) {
        for(const auto& rule: (*it).getRule()) {
            if(rule == m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "A0")) {
                buildTreeRecursive(node, ++it, end);
            } else if(rule == m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "B")) {
                buildTreeRecursive(buildB(node), ++it, end);
            } else if(rule == m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "C")) {
                buildTreeRecursive(node, ++it, end);
            }
        }
    } else if((*it).getVn() == m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "B")) {
        VariableDeclarationNode* variableDeclarationNode = static_cast<VariableDeclarationNode*>(
            node);
        for(const auto& rule: (*it).getRule()) {
            if(rule == m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "E")) {
                buildTreeRecursive(buildE(variableDeclarationNode), ++it, end);
            } else if(rule == m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "TYPES")) {
                variableDeclarationNode->setVariablesType(DeclaretionType::INT);
            }
        }
    } else if((*it).getVn() == m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "C")) {
        for(const auto& rule: (*it).getRule()) {
            if(rule == m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "D")) {
                buildTreeRecursive(buildD(node), ++it, end);
            }
        }
    } else if((*it).getVn() == m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "D")) {
        for(const auto& rule: (*it).getRule()) {
            if(rule == m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "E")) {
                buildTreeRecursive(buildE(node), ++it, end);
            } else if(rule == m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "G")) {
                buildTreeRecursive(buildG(node), ++it, end);
            }
        }
    } else if((*it).getVn() == m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "E")) {
        for(const auto& rule: (*it).getRule()) {
            if(rule == m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "E")) {
                buildTreeRecursive(buildE(node), ++it, end);
            } else if(rule == m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "VARIABLES")) {
                buildVariable(node);
            }
        }
    } else if((*it).getVn() == m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "G")) {
        auto gNode = static_cast<ArithmeticExpressionNode*>(node);
        for(const auto& rule: (*it).getRule()) {
            if(rule == m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "G")) {
                buildTreeRecursive(buildG(gNode), ++it, end);
            } else if(
                rule == m_vocabulary.getWordId(LexemCategory::OPERATOR, "+") ||
                rule == m_vocabulary.getWordId(LexemCategory::OPERATOR, "-") ||
                rule == m_vocabulary.getWordId(LexemCategory::OPERATOR, "*") ||
                rule == m_vocabulary.getWordId(LexemCategory::OPERATOR, "//")) {
                gNode->setOperator(m_vocabulary.getWord(rule).second);
            } else if(rule == m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "VALUE")) {
                buildValue(node);
            } else if(rule == m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "VARIABLES")) {
                buildVariable(node);
            }
        }
    }*/
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
