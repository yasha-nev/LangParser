#include "Render.hpp"

Render::Render(Vocabulary& vocabulary):
    m_vocabulary(vocabulary) {
}

void Render::renderLexem(const Lexem& lexem) {
    std::cout << formatLexem(lexem);
}

void Render::renderEarleyItem(const EarleyItem& eItem) {
    std::cout << formatEarlyItem(eItem);
}

void Render::renderAST(const std::unique_ptr<AST>& ast) {
    std::cout << formatTreeNode(ast);
}

static std::string category2String(LexemCategory lexemCategory) {
    switch(lexemCategory) {
        case LexemCategory::OPERATOR:
            return "OPERATOR";
        case LexemCategory::CONDITION:
            return "CONDITION";
        case LexemCategory::LOGIC:
            return "LOGIC";
        case LexemCategory::TYPES:
            return "TYPES";
        case LexemCategory::KEYWORD:
            return "KEYWORD";
        case LexemCategory::END:
            return "END";
        case LexemCategory::END_WORDS:
            return "END_WORDS";
        case LexemCategory::VALUE:
            return "VALUE";
        case LexemCategory::SPACE:
            return "SPACE";
        case LexemCategory::VARIABLES:
            return "VARIABLES";
        default:
            return "";
    }
}

std::string Render::formatLexem(const Lexem& lexem) const {
    std::stringstream ss;

    ss << "----Token-----\n";
    ss << "name: " << m_vocabulary.getWord(lexem.getWordId()).second << "\n";
    ss << "type: " << category2String(lexem.getType()) << "\n";
    ss << "id: " << lexem.getPosition() << "\n";
    ss << "--------------\n";

    return ss.str();
}

std::string Render::formatEarlyItem(const EarleyItem& eItem) const {
    std::stringstream ss;

    const std::string& vn = m_vocabulary.getWord(eItem.getVn()).second;
    const auto& rule = eItem.getRule();

    size_t n = vn.size();

    ss << vn << " -> ";

    for(const auto& part: rule) {
        const std::string& word = m_vocabulary.getWord(part).second;
        n += word.size() + 1;
        ss << word << " ";
    }

    ss << std::string(100 - n, ' ') << " | " << eItem.getNumber() << "\n";

    return ss.str();
}

std::string Render::formatTreeNode(const std::unique_ptr<AST>& ast) const {
    std::stringstream ss;
    ss << "AST\n";

    const ASTNode* ptr = ast->getRootNode().get();

    if(ptr != nullptr) {
        formatAstNode(ptr, 0, ss);
    }
    return ss.str();
}

void Render::formatAstNode(const ASTNode* node, int deep, std::stringstream& ss) const {
    if(node == nullptr) {
        return;
    }

    switch(node->getNodeType()) {
        case ASTNodeType::ARITHMETIC_EXPRESSION:
            formatArithmeticExpressionNode(
                static_cast<const ArithmeticExpressionNode*>(node), deep, ss);
            break;
        case ASTNodeType::ASSIGMENTS:
            formatAssigmentNode(static_cast<const AssigmentNode*>(node), deep, ss);
            break;
        case ASTNodeType::BRANCH:
            formatBranchNode(static_cast<const BranchStatementNode*>(node), deep, ss);
            break;
        case ASTNodeType::CONDITION_EXPRESSION:
            formatConditionExpressionNode(
                static_cast<const ConditionExpressionNode*>(node), deep, ss);
            break;
        case ASTNodeType::LOOP:
            formatLoopStatementNode(static_cast<const LoopStatementNode*>(node), deep, ss);
            break;
        case ASTNodeType::ROOT:
            formatRootNode(static_cast<const RootNode*>(node), deep, ss);
            break;
        case ASTNodeType::VALUE:
            formatValueNode(static_cast<const ValueNode*>(node), deep, ss);
            break;
        case ASTNodeType::VARIABLE:
            formatVariableNode(static_cast<const VariableNode*>(node), deep, ss);
            break;
        case ASTNodeType::VARIABLE_DECLARATION:
            formatVariableDeclarationNode(
                static_cast<const VariableDeclarationNode*>(node), deep, ss);
            break;
        default:
            break;
    }
}

void Render::formatRootNode(const RootNode* node, int deep, std::stringstream& ss) const {
    for(const auto& node: node->getNodes()) {
        formatAstNode(node.get(), deep + 1, ss);
    }
}

void Render::formatValueNode(const ValueNode* node, int deep, std::stringstream& ss) const {
    ss << "|" << std::string(deep, '-') << " Value: " << node->getValue() << " : "
       << node->getValueType() << "\n";
}

void Render::formatVariableNode(const VariableNode* node, int deep, std::stringstream& ss) const {
    ss << "|" << std::string(deep, '-') << " Identifier: " << node->getVariable() << "\n";
}

void Render::formatVariableDeclarationNode(
    const VariableDeclarationNode* node,
    int deep,
    std::stringstream& ss) const {
    ss << "|" << std::string(deep, '-') << " Declaration: \n";
    ss << "|" << std::string(deep + 1, '-')
       << " Type: " << m_vocabulary.getWord(node->getVariablesType()).second << "\n";
    for(const auto& var: node->getNodes()) {
        formatAstNode(var.get(), deep + 2, ss);
    }
}

void Render::formatLoopStatementNode(const LoopStatementNode* node, int deep, std::stringstream& ss)
    const {
    ss << "|" << std::string(deep, '-')
       << " LOOP: " << m_vocabulary.getWord(node->getLoopType()).second << "\n";

    for(const auto& var: node->getNodes()) {
        if(var->getNodeType() == ASTNodeType::ASSIGMENTS) {
            ss << "|" << std::string(deep + 1, '-') << " Assigments:\n";
        } else if(var->getNodeType() == ASTNodeType::CONDITION_EXPRESSION) {
            ss << "|" << std::string(deep + 1, '-') << " condition:\n";
        } else {
            ss << "|" << std::string(deep + 1, '-') << " Loop field:\n";
        }

        formatAstNode(var.get(), deep + 2, ss);
    }
}

void Render::formatBranchNode(const BranchStatementNode* node, int deep, std::stringstream& ss)
    const {
    ss << "|" << std::string(deep, '-') << " If:\n";

    for(const auto& var: node->getNodes()) {
        if(var->getNodeType() == ASTNodeType::CONDITION_EXPRESSION) {
            ss << "|" << std::string(deep + 1, '-') << " Condition\n";
        } else {
            ss << "|" << std::string(deep + 1, '-') << " Field\n";
        }

        formatAstNode(var.get(), deep + 2, ss);
    }
}

void Render::formatConditionExpressionNode(
    const ConditionExpressionNode* node,
    int deep,
    std::stringstream& ss) const {
    if(node->getNodes().size() == 1) {
        formatAstNode(node->getNodes().front().get(), deep + 1, ss);
    }

    else {
        ss << "|" << std::string(deep, '-')
           << " Condition: " << m_vocabulary.getWord(node->getConditionType()).second << "\n";

        int i = 0;
        for(const auto& child: node->getNodes()) {
            if(i == 0) {
                ss << "|" << std::string(deep + 1, '-') << " Left operand:\n";
            } else {
                ss << "|" << std::string(deep + 1, '-') << " Right operand: \n";
            }

            formatAstNode(child.get(), deep + 2, ss);

            i++;
        }
    }
}

void Render::formatArithmeticExpressionNode(
    const ArithmeticExpressionNode* node,
    int deep,
    std::stringstream& ss) const {
    if(node->getNodes().size() == 1) {
        formatAstNode(node->getNodes().front().get(), deep + 1, ss);
    }

    else {
        ss << "|" << std::string(deep, '-')
           << " Operator: " << m_vocabulary.getWord(node->getOperator()).second << "\n";
        int i = 0;
        for(const auto& child: node->getNodes()) {
            if(i == 0) {
                ss << "|" << std::string(deep + 1, '-') << " Left operand:\n";
            } else {
                ss << "|" << std::string(deep + 1, '-') << " Right operand: \n";
            }
            formatAstNode(child.get(), deep + 2, ss);
            i++;
        }
    }
}

void Render::formatAssigmentNode(const AssigmentNode* node, int deep, std::stringstream& ss) const {
    ss << "|" << std::string(deep, '-') << " Operator: =\n";
    ss << "|" << std::string(deep + 1, '-') << " Left operand:\n";

    for(const auto& var: node->getNodes()) {
        if(var->getNodeType() == ASTNodeType::VARIABLE) {
            formatAstNode(var.get(), deep + 2, ss);
        }
    }

    ss << "|" << std::string(deep + 1, '-') << " Right operand:\n";

    for(const auto& exp: node->getNodes()) {
        if(exp->getNodeType() == ASTNodeType::ARITHMETIC_EXPRESSION) {
            formatAstNode(exp.get(), deep + 2, ss);
        }
    }
}
