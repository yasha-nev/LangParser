#include "Parser.hpp"

#include <ctime>

Parser::Parser(Vocabulary& m_vocabulary, Grammar& grammar):
    m_vocabulary(m_vocabulary),
    m_grammar(grammar) {
}

void Parser::performSyntaxAnalysis(std::vector<Lexem>& tokens) {
    tokens.push_back(Lexem(
        LexemCategory::END,
        m_vocabulary.getWordId(""),
        -1,
        tokens[tokens.size() - 1].getLineNumber()));

    std::vector<std::set<EarleyItem>> D(tokens.size() + 1);
    D[0].insert(EarleyItem(
        m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "1A"),
        { m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "A") },
        0,
        0));

    try {
        for(size_t i = 0; i < tokens.size() + 1; i++) {

            if(i > 0) {
                scan(D[i - 1], D[i], tokens[i - 1], i);
            }

            size_t prevSize = 0;
            do {
                prevSize = D[i].size();
                complite(D, i);
                predict(D[i], i);
            } while(D[i].size() != prevSize);
        }
    } catch(std::invalid_argument& ex) {
        std::cout << "----- ERROR: " << ex.what() << "-----"
                  << "\n";
        return;
    }
}

void Parser::scan(
    std::set<EarleyItem>& P_D,
    std::set<EarleyItem>& C_D,
    const Lexem& preToken,
    int pos) { // P = past, C - Current
    if(pos == 0) {
        return;
    }
    EarleyItem endItem(
        m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "A"),
        { m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "{"),
          m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "A0"),
          m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "}") },
        4,
        0);

    for(const auto& d: P_D) {
        if(d.getQueueRule() == preToken.getWordId() ||
           d.getQueueRule() == m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "TYPES") &&
               preToken.getType() == LexemCategory::TYPES ||
           d.getQueueRule() == m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "VALUE") &&
               preToken.getType() == LexemCategory::VALUE ||
           d.getQueueRule() == m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "VARIABLES") &&
               preToken.getType() == LexemCategory::VARIABLES) {
            EarleyItem item = d;
            item.movePoint();
            C_D.insert(item);
        }

        if(endItem == d && m_vocabulary.getWord(preToken.getWordId()).second != "") {
            throw std::invalid_argument(
                "Row " + std::to_string(preToken.getLineNumber()) + " symbols " +
                m_vocabulary.getWord(preToken.getWordId()).second + " is not expected");
        }
    }
    if(C_D.empty()) {
        throwUnexpectedToken(preToken, P_D);
    }
}

void Parser::throwUnexpectedToken(const Lexem& preToken, const std::set<EarleyItem>& P_D) const {
    std::set<int> missingRulesSet;
    for(const auto& d: P_D) {
        int rule = d.getQueueRule();
        if(m_grammar.getCountElementsInRule(rule) == 0 && rule != -1) {
            missingRulesSet.insert(rule);
        }
    }

    if(!missingRulesSet.empty()) {
        std::string missingRules;
        for(const auto& rule: missingRulesSet) {
            if(!missingRules.empty()) {
                missingRules += ", ";
            }
            missingRules += rule;
        }

        throw std::invalid_argument(
            "Error: row " + std::to_string(preToken.getLineNumber()) + ", symbol '" +
            m_vocabulary.getWord(preToken.getWordId()).second +
            "': unexpected token; expected one of " + missingRules + "");
    }

    throw std::invalid_argument(
        "Error: row " + std::to_string(preToken.getLineNumber()) + ", symbol '" +
        m_vocabulary.getWord(preToken.getWordId()).second +
        "': unexpected token; no symbols expected");
}

void Parser::predict(std::set<EarleyItem>& D, int pos) {
    std::set<EarleyItem> D_sup;

    for(const auto& d: D) {
        if(m_grammar.getCountElementsInRule(d.getQueueRule()) == 1) {
            int sup = d.getQueueRule();

            for(auto& rule: m_grammar.getRule(sup)) {
                EarleyItem item(sup, rule, 0, pos);
                D_sup.insert(item);
            }
        }
    }

    for(const auto& d: D_sup) {
        D.insert(d);
    }
}

void Parser::complite(std::vector<std::set<EarleyItem>>& D, int pos) {
    std::set<EarleyItem> D_Sup;

    for(const auto& d: D[pos]) {
        if(d.checkEnd() == 0) {
            continue;
        }
        m_parseTree.insert(d);

        for(const auto& s: D[d.getNumber()]) {
            if(s.getQueueRule() == d.getVn()) {
                EarleyItem item(s);
                item.movePoint();
                D_Sup.insert(item);
            }
        }
    }

    for(const auto& d: D_Sup) {
        D[pos].insert(d);
    }
}

void Parser::printTree() {
    Render render(m_vocabulary);
    std::cout << "GRAMMATICAL SEQUENCE"
              << "\n";
    for(const auto& d: m_parseTree) {
        render.renderEarleyItem(d);
    }
}

std::set<EarleyItem>& Parser::getParserOutput() {
    return m_parseTree;
}
