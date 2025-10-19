
#include "Ast.hpp"
#include "ValueNode.hpp"

class ArithmeticExpressionNode: public ASTNode {
public:
    ArithmeticExpressionNode();

    ArithmeticExpressionNode(const std::string& op);

    ArithmeticExpressionNode(
        const std::string& op,
        std::unique_ptr<ValueNode> param,
        std::unique_ptr<ArithmeticExpressionNode> m_expression);

    void setParam(std::unique_ptr<ValueNode> param);

    const std::unique_ptr<ValueNode>& getParam();

    void setExpression(std::unique_ptr<ArithmeticExpressionNode> expression);

    const std::unique_ptr<ArithmeticExpressionNode>& getExpression();

private:
    std::unique_ptr<ValueNode> m_param;
    std::string m_operator; // + - * /
    std::unique_ptr<ArithmeticExpressionNode> m_expression;
};
