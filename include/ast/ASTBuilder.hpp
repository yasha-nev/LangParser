#pragma once

#include "AST.hpp"
#include "ArithmeticExpressionNode.hpp"
#include "AssigmentNode.hpp"
#include "BranchNode.hpp"
#include "ConditionExpressionNode.hpp"
#include "EarleyItem.hpp"
#include "LoopStatementNode.hpp"
#include "RootNode.hpp"
#include "ValueNode.hpp"
#include "VariableDeclarationNode.hpp"
#include "VariableNode.hpp"
#include "Vocabulary.hpp"

#include <algorithm>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <vector>

using eItemCurrent = std::set<EarleyItem>::iterator;
using eItemEnd = std::set<EarleyItem>::iterator;

class ASTBuilder {
public:
    ASTBuilder(Vocabulary& vocabulary, std::vector<Lexem>& tokens, std::set<EarleyItem>& items);

    std::unique_ptr<AST> buildTree();

private:
    void buildTreeRecursive(ASTNode* node, eItemCurrent& it, eItemEnd& end);

    template<typename NodeT>
    ASTNode* addChild(ASTNode* parent) {
        auto ptr = std::make_unique<NodeT>();
        ASTNode* child = ptr.get();
        parent->addNode(std::move(ptr));
        return child;
    }

    // NONERMINAL handlers

    ASTNode* buildStmtList(ASTNode* node);

    ASTNode* buildDeclStmt(ASTNode* node);

    ASTNode* buildAssignment(ASTNode* node);

    ASTNode* buildVarName(ASTNode* node);

    ASTNode* buildArithmExpr(ASTNode* node);

    ASTNode* buildConditionExptr(ASTNode* node);

    ASTNode* buildLoopStmt(ASTNode* node);

    ASTNode* buildBranchStmt(ASTNode* node);

    ASTNode* buildValue(ASTNode* node);

    ASTNode* buildVariable(ASTNode* node);

    // OPERATOR HANDLERS

    void buildOperator(ASTNode* node, int op);

    // Loop Handlers

    void buildLoopType(ASTNode* node, int loopType);

    // Condition Handles

    void buildConditionType(ASTNode* node, int conditionType);

    std::optional<std::string> nextTokenValue(std::initializer_list<LexemCategory> categories);

    Vocabulary& m_vocabulary;

    std::vector<Lexem>& m_tokens;

    std::set<EarleyItem>& m_eItems;

    std::vector<Lexem>::iterator m_lexemIt;

    std::set<EarleyItem>::iterator m_eIemIt;

    inline int wordId(const std::string& nonterm) const;

    using buildNodeHandler = std::function<ASTNode*(ASTBuilder&, ASTNode*)>;

    std::unordered_map<int, buildNodeHandler> m_buildNodeFactory;
};
