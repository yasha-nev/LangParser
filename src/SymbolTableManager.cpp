#include "SymbolTableManager.hpp"

SymbolTable::SymbolTable(int level) {
    m_scopeLevel = level;
}

void SymbolTable::insert(const std::string& name, const Symbol& symbol) {
    m_symbols.insert({ name, symbol });
}

Symbol SymbolTable::find(const std::string& name) {
    auto it = m_symbols.find(name);

    if(it != m_symbols.end()) {
        return (*it).second;
    }

    return Symbol();
}

SymbolTableManager::SymbolTableManager() {
    // make global table
    m_tables.push_back(std::make_unique<SymbolTable>(0));
}

void SymbolTableManager::enterTable() {
    m_tables.emplace_back(std::make_unique<SymbolTable>(m_tables.size()));
}

void SymbolTableManager::exitTable() {
    if(!m_tables.empty()) {
        m_tables.pop_back();
    }
}

void SymbolTableManager::addSymbol(const std::string& name, const Symbol& symbol) {
    currentTable()->insert(name, symbol);
}

Symbol SymbolTableManager::lookup(const std::string& name) {
    for(auto rit = m_tables.rbegin(); rit != m_tables.rend(); ++rit) {
        return (*rit)->find(name);
    }
    return Symbol();
}

const std::unique_ptr<SymbolTable>& SymbolTableManager::currentTable() {
    return m_tables.back();
}
