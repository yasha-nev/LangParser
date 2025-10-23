#pragma once

#include "AST.hpp"
#include "ArithmeticExpressionNode.hpp"
#include "AssigmentNode.hpp"
#include "EarleyItem.hpp"
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

    ASTNode* buildA(ASTNode* node);

    ASTNode* buildB(ASTNode* node);

    ASTNode* buildD(ASTNode* node);

    ASTNode* buildE(ASTNode* node);

    ASTNode* buildG(ASTNode* node);

    ASTNode* buildValue(ASTNode* node);

    ASTNode* buildVariable(ASTNode* node);

    std::string getNextValue();

    Vocabulary& m_vocabulary;

    std::vector<Lexem>& m_tokens;

    std::set<EarleyItem>& m_eItems;

    std::vector<Lexem>::iterator m_lexemIt;

    std::set<EarleyItem>::iterator m_eIemIt;
};
