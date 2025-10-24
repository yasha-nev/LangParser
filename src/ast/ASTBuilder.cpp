#include "ast/ASTBuilder.hpp"

ASTBuilder::ASTBuilder(
    Vocabulary& vocabulary,
    std::vector<Lexem>& tokens,
    std::set<EarleyItem>& eItems):
    m_vocabulary(vocabulary),
    m_tokens(tokens),
    m_eItems(eItems) {
}

std::unique_ptr<AST> ASTBuilder::buildTree() {
    m_eIemIt = m_eItems.begin();
    m_lexemIt = m_tokens.begin();

    auto end = m_eItems.end();

    std::unique_ptr<ASTNode> m_root = std::make_unique<RootNode>();

    if(m_eIemIt != end) {
        buildTreeRecursive(m_root.get(), m_eIemIt, end);
    }

    return std::make_unique<AST>(std::move(m_root));
}

void ASTBuilder::buildTreeRecursive(ASTNode* node, eItemCurrent& it, eItemEnd& end) {
    if(it == end || node == nullptr) {
        return;
    }

    std::map<int, std::function<void(ASTNode * node, eItemCurrent & it, eItemEnd & end)>> test = {
        { m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "<stmt-list>"),
          [&](ASTNode* n, eItemCurrent& it, eItemEnd& end) {
              buildTreeRecursive(buildA(n), ++it, end);
          } },
        { m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "<stmt-seq>"),
          [&](ASTNode* n, eItemCurrent& it, eItemEnd& end) { buildTreeRecursive(n, ++it, end); } },
        { m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "<decl-stmt>"),
          [&](ASTNode* n, eItemCurrent& it, eItemEnd& end) {
              buildTreeRecursive(buildB(n), ++it, end);
          } },
        { m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "<control-flow-stmt>"),
          [&](ASTNode* n, eItemCurrent& it, eItemEnd& end) { buildTreeRecursive(n, ++it, end); } },
        { m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "<assignment>"),
          [&](ASTNode* n, eItemCurrent& it, eItemEnd& end) {
              buildTreeRecursive(buildD(n), ++it, end);
          } },
        { m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "<var-name>"),
          [&](ASTNode* n, eItemCurrent& it, eItemEnd& end) {
              buildTreeRecursive(buildE(n), ++it, end);
          } },
        { m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "<arithm-expr>"),
          [&](ASTNode* n, eItemCurrent& it, eItemEnd& end) {
              buildTreeRecursive(buildG(n), ++it, end);
          } },
        { m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "<type-decl>"),
          [&](ASTNode* n, eItemCurrent& it, eItemEnd& end) {} },
        { m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "<value>"),
          [&](ASTNode* n, eItemCurrent& it, eItemEnd& end) { return buildValue(n); } },
        { m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "<variables>"),
          [&](ASTNode* n, eItemCurrent& it, eItemEnd& end) { return buildVariable(n); } }
    };

    for(const auto& rule: (*it).getRule()) {
        if(m_vocabulary.getWord(rule).first == LexemCategory::NOTERMINAL) {
            test[rule](node, it, end);
        }
    }
}

ASTNode* ASTBuilder::buildA(ASTNode* node) {
    return node;
}

ASTNode* ASTBuilder::buildB(ASTNode* node) {
    std::unique_ptr<VariableDeclarationNode> ptr = std::make_unique<VariableDeclarationNode>();

    node->addNode(std::move(ptr));
    const auto& list = node->getNodes();

    return list.back().get();
}

ASTNode* ASTBuilder::buildD(ASTNode* node) {
    std::unique_ptr<AssigmentNode> assigmentNode = std::make_unique<AssigmentNode>();

    node->addNode(std::move(assigmentNode));
    const auto& list = node->getNodes();

    return list.back().get();
}

ASTNode* ASTBuilder::buildE(ASTNode* node) {
    return node;
}

ASTNode* ASTBuilder::buildG(ASTNode* node) {
    std::unique_ptr<ArithmeticExpressionNode>
        arithmeticExpressionNode = std::make_unique<ArithmeticExpressionNode>();

    node->addNode(std::move(arithmeticExpressionNode));
    const auto& list = node->getNodes();

    return list.back().get();
}

ASTNode* ASTBuilder::buildValue(ASTNode* node) {
    std::string value = getNextValue();

    std::unique_ptr<ValueNode> valueNode = std::make_unique<ValueNode>(DeclaretionType::INT, value);
    node->addNode(std::move(valueNode));

    return nullptr;
}

ASTNode* ASTBuilder::buildVariable(ASTNode* node) {
    std::string var = getNextValue();

    std::unique_ptr<VariableNode> variableNode = std::make_unique<VariableNode>(var);
    node->addNode(std::move(variableNode));

    return nullptr;
}

std::string ASTBuilder::getNextValue() {
    std::string res = "";
    for(m_lexemIt; m_lexemIt != m_tokens.end(); m_lexemIt++) {
        if((*m_lexemIt).getType() == LexemCategory::VALUE ||
           (*m_lexemIt).getType() == LexemCategory::VARIABLES) {
            res = m_vocabulary.getWord((*m_lexemIt).getWordId()).second;
            m_lexemIt++;
            break;
        }
    }

    return res;
}
