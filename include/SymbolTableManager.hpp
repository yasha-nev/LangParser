#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class Symbol {
public:
    std::string name;
    int type;
    bool is_constant;
};

class SymbolTable {
public:
    explicit SymbolTable(int level);

    void insert(const std::string& name, const Symbol& symbol);

    Symbol find(const std::string& name);

private:
    std::unordered_map<std::string, Symbol> m_symbols;
    int m_scopeLevel;
};

class SymbolTableManager {
public:
    SymbolTableManager();

    void enterTable();

    void exitTable();

    void addSymbol(const std::string& name, const Symbol& symbol);

    Symbol lookup(const std::string& name);

private:
    const std::unique_ptr<SymbolTable>& currentTable();

    std::vector<std::unique_ptr<SymbolTable>> m_tables;
};
