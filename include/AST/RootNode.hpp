#pragma once

#include "Ast.hpp"

class RootNode: public ASTNode {
public:
    RootNode();

    void addNode(std::unique_ptr<ASTNode>&& node);

private:
    std::list<std::unique_ptr<ASTNode>> m_nodes;
};
