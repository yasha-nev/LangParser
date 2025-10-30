#include "ast/ASTBuilder.hpp"

ASTBuilder::ASTBuilder(
    Vocabulary& vocabulary,
    std::vector<Lexem>& tokens,
    std::set<EarleyItem>& eItems):
    m_vocabulary(vocabulary),
    m_tokens(tokens),
    m_eItems(eItems) {

    m_buildNodeFactory = {
        { wordId("<stmt-list>"), &ASTBuilder::buildStmtList },
        { wordId("<stmt-seq>"), [](ASTBuilder&, ASTNode* node) { return node; } },
        { wordId("<decl-stmt>"), &ASTBuilder::buildDeclStmt },
        { wordId("<stmt>"), [](ASTBuilder&, ASTNode* node) { return node; } },
        { wordId("<loop-stmt>"), &ASTBuilder::buildLoopStmt },
        { wordId("<branch-stmt>"), &ASTBuilder::buildBranchStmt },
        { wordId("<assignment-stmt>"), &ASTBuilder::buildAssignment },
        { wordId("<var-name>"), &ASTBuilder::buildVarName },
        { wordId("<arithm-expr>"), &ASTBuilder::buildArithmExpr },
        { wordId("<cond-expr>"), &ASTBuilder::buildConditionExptr },
        { wordId("<value>"), &ASTBuilder::buildValue },
        { wordId("<variables>"), &ASTBuilder::buildVariable },
        { wordId("<type-decl>"), &ASTBuilder::buildDeclaration },

    };
}

inline int ASTBuilder::wordId(const std::string& nonterm) const {
    return m_vocabulary.getWordId(LexemCategory::NONTERMINAL, nonterm);
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

    for(const auto& rule: (*it).getRule()) {
        auto [category, name] = m_vocabulary.getWord(rule);

        switch(category) {
            case LexemCategory::NONTERMINAL: {
                auto found = m_buildNodeFactory.find(rule);
                if(found != m_buildNodeFactory.end()) {
                    ASTNode* ptr = found->second(*this, node);
                    if(ptr) {
                        buildTreeRecursive(ptr, ++it, end);
                    }
                }
                break;
            }
            case LexemCategory::OPERATOR: {
                buildOperator(node, rule);
                break;
            }
            case LexemCategory::LOOP: {
                buildLoopType(node, rule);
                break;
            }
            case LexemCategory::LOGIC:
            case LexemCategory::CONDITION: {
                buildConditionType(node, rule);
                break;
            }

            case LexemCategory::TYPES:
            case LexemCategory::BRANCHING:
            case LexemCategory::KEYWORD:
            default: {
                break;
            }
        }
    }
}

ASTNode* ASTBuilder::buildStmtList(ASTNode* node) {
    return node;
}

ASTNode* ASTBuilder::buildDeclStmt(ASTNode* node) {
    return addChild<VariableDeclarationNode>(node);
}

ASTNode* ASTBuilder::buildAssignment(ASTNode* node) {
    return addChild<AssigmentNode>(node);
}

ASTNode* ASTBuilder::buildVarName(ASTNode* node) {
    return node;
}

ASTNode* ASTBuilder::buildArithmExpr(ASTNode* node) {
    return addChild<ArithmeticExpressionNode>(node);
}

ASTNode* ASTBuilder::buildConditionExptr(ASTNode* node) {
    return addChild<ConditionExpressionNode>(node);
}

ASTNode* ASTBuilder::buildLoopStmt(ASTNode* node) {
    return addChild<LoopStatementNode>(node);
}

ASTNode* ASTBuilder::buildBranchStmt(ASTNode* node) {
    return addChild<BranchStatementNode>(node);
}

ASTNode* ASTBuilder::buildValue(ASTNode* node) {
    if(auto val = nextTokenValue({ LexemCategory::VALUE })) {
        auto ptr = std::make_unique<ValueNode>(-1, *val);
        node->addNode(std::move(ptr));
    }
    return nullptr;
}

ASTNode* ASTBuilder::buildVariable(ASTNode* node) {
    if(auto val = nextTokenValue({ LexemCategory::VARIABLES })) {
        auto ptr = std::make_unique<VariableNode>(*val);
        node->addNode(std::move(ptr));
    }
    return nullptr;
}

ASTNode* ASTBuilder::buildDeclaration(ASTNode* node) {
    auto val = nextTokenValue({ LexemCategory::TYPES });
    if(val && node->getNodeType() == ASTNodeType::VARIABLE_DECLARATION) {
        VariableDeclarationNode* vnode = static_cast<VariableDeclarationNode*>(node);
        vnode->setVariablesType(m_vocabulary.getWordId(LexemCategory::TYPES, (*val)));
    }

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

void ASTBuilder::buildConditionType(ASTNode* node, int conditionType) {
    if(node->getNodeType() == ASTNodeType::CONDITION_EXPRESSION) {
        ConditionExpressionNode* cnode = static_cast<ConditionExpressionNode*>(node);

        cnode->setConditionType(conditionType);
    }
}

std::optional<std::string> ASTBuilder::nextTokenValue(
    std::initializer_list<LexemCategory> categories) {
    while(m_lexemIt != m_tokens.end()) {
        auto type = m_lexemIt->getType();
        if(std::find(categories.begin(), categories.end(), type) != categories.end()) {
            std::string val = m_vocabulary.getWord(m_lexemIt->getWordId()).second;
            ++m_lexemIt;
            return val;
        }
        ++m_lexemIt;
    }
    return std::nullopt;
}
