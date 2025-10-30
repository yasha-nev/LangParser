#pragma once

#include "EarleyItem.hpp"
#include "Lexem.hpp"
#include "Vocabulary.hpp"
#include "ast/AST.hpp"
#include "ast/ArithmeticExpressionNode.hpp"
#include "ast/AssigmentNode.hpp"
#include "ast/BranchStatementNode.hpp"
#include "ast/ConditionExpressionNode.hpp"
#include "ast/LoopStatementNode.hpp"
#include "ast/RootNode.hpp"
#include "ast/ValueNode.hpp"
#include "ast/VariableDeclarationNode.hpp"
#include "ast/VariableNode.hpp"

#include <iostream>
#include <sstream>

class Render {
public:
    Render(Vocabulary& vocabulary);

    void renderLexem(const Lexem& lexem);

    void renderEarleyItem(const EarleyItem& eItem);

    void renderAST(const std::unique_ptr<AST>& ast);

protected:
    virtual std::string formatLexem(const Lexem&) const;

    virtual std::string formatEarlyItem(const EarleyItem&) const;

    virtual std::string formatTreeNode(const std::unique_ptr<AST>& ast) const;

private:
    void formatAstNode(const ASTNode* node, int deep, std::stringstream& ss) const;

    void formatRootNode(const RootNode* node, int deep, std::stringstream& ss) const;

    void formatValueNode(const ValueNode* node, int deep, std::stringstream& ss) const;

    void formatVariableNode(const VariableNode* node, int deep, std::stringstream& ss) const;

    void formatVariableDeclarationNode(
        const VariableDeclarationNode* node,
        int deep,
        std::stringstream& ss) const;

    void formatLoopStatementNode(const LoopStatementNode* node, int deep, std::stringstream& ss)
        const;

    void formatBranchNode(const BranchStatementNode* node, int deep, std::stringstream& ss) const;

    void formatConditionExpressionNode(
        const ConditionExpressionNode* node,
        int deep,
        std::stringstream& ss) const;

    void formatArithmeticExpressionNode(
        const ArithmeticExpressionNode* node,
        int deep,
        std::stringstream& ss) const;

    void formatAssigmentNode(const AssigmentNode* node, int deep, std::stringstream& ss) const;

private:
    Vocabulary& m_vocabulary;
};
