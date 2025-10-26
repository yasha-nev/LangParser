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

    static std::map<int, std::function<void(ASTNode * node, eItemCurrent & it, eItemEnd & end)>>
        nonterminalHandler = {
            { m_vocabulary.getWordId(LexemCategory::NONTERMINAL, "<stmt-list>"),
              [&](ASTNode* n, eItemCurrent& it, eItemEnd& end) {
                  buildTreeRecursive(buildStmtList(n), ++it, end);
              } },
            { m_vocabulary.getWordId(LexemCategory::NONTERMINAL, "<stmt-seq>"),
              [&](ASTNode* n, eItemCurrent& it, eItemEnd& end) {
                  buildTreeRecursive(n, ++it, end);
              } },
            { m_vocabulary.getWordId(LexemCategory::NONTERMINAL, "<decl-stmt>"),
              [&](ASTNode* n, eItemCurrent& it, eItemEnd& end) {
                  buildTreeRecursive(buildStmtSeq(n), ++it, end);
              } },
            { m_vocabulary.getWordId(LexemCategory::NONTERMINAL, "<control-flow-stmt>"),
              [&](ASTNode* n, eItemCurrent& it, eItemEnd& end) {
                  buildTreeRecursive(n, ++it, end);
              } },
            { m_vocabulary.getWordId(LexemCategory::NONTERMINAL, "<loop>"),
              [&](ASTNode* n, eItemCurrent& it, eItemEnd& end) {
                  buildTreeRecursive(buildLoopStmt(n), ++it, end);
              } },
            { m_vocabulary.getWordId(LexemCategory::NONTERMINAL, "<assignment>"),
              [&](ASTNode* n, eItemCurrent& it, eItemEnd& end) {
                  buildTreeRecursive(buildAssignment(n), ++it, end);
              } },
            { m_vocabulary.getWordId(LexemCategory::NONTERMINAL, "<var-name>"),
              [&](ASTNode* n, eItemCurrent& it, eItemEnd& end) {
                  buildTreeRecursive(buildVarName(n), ++it, end);
              } },
            { m_vocabulary.getWordId(LexemCategory::NONTERMINAL, "<arithm-expr>"),
              [&](ASTNode* n, eItemCurrent& it, eItemEnd& end) {
                  buildTreeRecursive(buildArithmExpr(n), ++it, end);
              } },
            { m_vocabulary.getWordId(LexemCategory::NONTERMINAL, "<cond-expr>"),
              [&](ASTNode* n, eItemCurrent& it, eItemEnd& end) {
                  buildTreeRecursive(buildConditionExptr(n), ++it, end);
              } },
            { m_vocabulary.getWordId(LexemCategory::NONTERMINAL, "<type-decl>"),
              [&](ASTNode* n, eItemCurrent& it, eItemEnd& end) {} },
            { m_vocabulary.getWordId(LexemCategory::NONTERMINAL, "<value>"),
              [&](ASTNode* n, eItemCurrent& it, eItemEnd& end) { return buildValue(n); } },
            { m_vocabulary.getWordId(LexemCategory::NONTERMINAL, "<variables>"),
              [&](ASTNode* n, eItemCurrent& it, eItemEnd& end) { return buildVariable(n); } }
        };

    for(const auto& rule: (*it).getRule()) {
        if(m_vocabulary.getWord(rule).first == LexemCategory::NONTERMINAL) {
            nonterminalHandler[rule](node, it, end);
        } else if(m_vocabulary.getWord(rule).first == LexemCategory::OPERATOR) {
            buildOperator(node, rule);
        } else if(m_vocabulary.getWord(rule).first == LexemCategory::LOOP) {
            buildLoopType(node, rule);
        } else if(m_vocabulary.getWord(rule).first == LexemCategory::LOGIC) {
            buildLogic(node, rule);
        }
    }
}

ASTNode* ASTBuilder::buildStmtList(ASTNode* node) {
    return node;
}

ASTNode* ASTBuilder::buildStmtSeq(ASTNode* node) {
    std::unique_ptr<VariableDeclarationNode> ptr = std::make_unique<VariableDeclarationNode>();

    node->addNode(std::move(ptr));
    const auto& list = node->getNodes();

    return list.back().get();
}

ASTNode* ASTBuilder::buildAssignment(ASTNode* node) {
    std::unique_ptr<AssigmentNode> assigmentNode = std::make_unique<AssigmentNode>();

    node->addNode(std::move(assigmentNode));
    const auto& list = node->getNodes();

    return list.back().get();
}

ASTNode* ASTBuilder::buildVarName(ASTNode* node) {
    return node;
}

ASTNode* ASTBuilder::buildArithmExpr(ASTNode* node) {
    std::unique_ptr<ArithmeticExpressionNode>
        arithmeticExpressionNode = std::make_unique<ArithmeticExpressionNode>();

    node->addNode(std::move(arithmeticExpressionNode));
    const auto& list = node->getNodes();

    return list.back().get();
}

ASTNode* ASTBuilder::buildConditionExptr(ASTNode* node) {
    std::unique_ptr<ConditionExpressionNode>
        conditionExpressionNode = std::make_unique<ConditionExpressionNode>();

    node->addNode(std::move(conditionExpressionNode));
    const auto& list = node->getNodes();

    return list.back().get();
}

ASTNode* ASTBuilder::buildLoopStmt(ASTNode* node) {
    std::unique_ptr<LoopStatementNode> loopStatementNode = std::make_unique<LoopStatementNode>();

    node->addNode(std::move(loopStatementNode));
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

void ASTBuilder::buildOperator(ASTNode* node, int op) {
    if(node->getNodeType() == ASTNodeType::ARITHMETIC_EXPRESSION) {
        ArithmeticExpressionNode* anode = static_cast<ArithmeticExpressionNode*>(node);

        anode->setOperator(op);
    }
}

void ASTBuilder::buildLoopType(ASTNode* node, int loopType) {
    if(node->getNodeType() == ASTNodeType::LOOP) {
        LoopStatementNode* lnode = static_cast<LoopStatementNode*>(node);

        lnode->setLoopType(loopType);
    }
}

void ASTBuilder::buildLogic(ASTNode* node, int logic) {
    if(node->getNodeType() == ASTNodeType::CONDITION_EXPRESSION) {
        ConditionExpressionNode* cnode = static_cast<ConditionExpressionNode*>(node);

        cnode->setConditionType(logic);
    }
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
