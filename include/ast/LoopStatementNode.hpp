#pragma once

#include "AST.hpp"

class LoopStatementNode: public ASTNode {
public:
    LoopStatementNode();

    const std::list<std::unique_ptr<ASTNode>>& getNodes() const noexcept override;

    void addNode(std::unique_ptr<ASTNode> node) override;

    int getLoopType() const noexcept;

    void setLoopType(int loopType);

private:
    int m_loopType;
};
