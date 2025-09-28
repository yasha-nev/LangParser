#include "Parser.hpp"

#include <ctime>

Parser::Parser(std::vector<Lexem>& tokens, Grammar& grammar):
    m_tokens(tokens),
    m_grammar(grammar) {
}

void Parser::parsing() {
    m_tokens.push_back(
        Lexem(-1, m_tokens[m_tokens.size() - 1].getPositionInRow(), "", LexemCategory::END));

    std::vector<std::set<EarleyItem>> D(m_tokens.size() + 1);
    D[0].insert(EarleyItem("1A", { "A" }, 0, 0));

    try {
        for(size_t i = 0; i < m_tokens.size() + 1; i++) {

            if(i > 0) {
                scan(D[i - 1], D[i], i);
            }

            size_t prevSize = 0;
            do {
                prevSize = D[i].size();
                complite(D, i);
                predict(D[i], i);
            } while(D[i].size() != prevSize);

            printLineScan(i, m_tokens[i], D[i]);
        }
    } catch(std::invalid_argument& ex) {
        std::cout << "----- ERROR: " << ex.what() << "-----" << "\n";
        return;
    }

    std::cout << "----NO ERROR FOUND PROGRAM IS TRUE----" << "\n";
}

void Parser::printLineScan(int line, const Lexem& token, std::set<EarleyItem>& D) {
    std::cout << std::string(50, '-') << "\n";
    std::cout << "line number: " << std::to_string(line) + " symbol: " << token.getName() << "\n\n";

    for(const auto& d: D) {
        std::cout << d << "\n";
    }
    std::cout << "\n";
}

void Parser::scan(
    std::set<EarleyItem>& P_D,
    std::set<EarleyItem>& C_D,
    int pos) { // P = past, C - Current
    if(pos == 0) {
        return;
    }
    EarleyItem endItem("A", { "{", "A0", "}", "end" }, 4, 0);
    Lexem& preToken = m_tokens[pos - 1];

    for(const auto& d: P_D) {
        if(d.getQueueRule() == preToken.getName() ||
           d.getQueueRule() == "TYPES" && preToken.getType() == LexemCategory::TYPES ||
           d.getQueueRule() == "VALUE" && preToken.getType() == LexemCategory::VALUE ||
           d.getQueueRule() == "VARIABLES" && preToken.getType() == LexemCategory::VARIABLES) {
            EarleyItem item = d;
            item.movePoint();
            C_D.insert(item);
        }

        if(endItem == d && preToken.getName() != "") {
            throw std::invalid_argument(
                "Row " + std::to_string(preToken.getPositionInRow()) + " symbols " +
                preToken.getName() + " is not expected");
        }
    }
    if(C_D.empty()) {
        throwUnexpectedToken(preToken, P_D);
    }
}

void Parser::throwUnexpectedToken(const Lexem& preToken, const std::set<EarleyItem>& P_D) const {
    std::set<std::string> missingRulesSet;
    for(const auto& d: P_D) {
        const std::string& rule = d.getQueueRule();
        if(m_grammar.getCountElementsInRule(rule) == 0 && !rule.empty()) {
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
            "Error: row " + std::to_string(preToken.getPositionInRow()) + ", symbol '" +
            preToken.getName() + "': unexpected token; expected one of {" + missingRules + "}");
    }

    throw std::invalid_argument(
        "Error: row " + std::to_string(preToken.getPositionInRow()) + ", symbol '" +
        preToken.getName() + "': unexpected token; no symbols expected");
}

static std::vector<std::string> stringSplit(const std::string& str) {
    std::vector<std::string> result;
    size_t start = 0;
    while(start < str.size()) {
        size_t pos = str.find(' ', start);
        if(pos == std::string::npos) {
            pos = str.size();
        }
        if(pos > start) {
            result.push_back(str.substr(start, pos - start));
        }
        start = pos + 1;
    }
    return result;
}

void Parser::predict(std::set<EarleyItem>& D, int pos) {
    std::set<EarleyItem> D_sup;
    for(const auto& d: D) {
        if(m_grammar.getCountElementsInRule(d.getQueueRule()) == 1) {
            std::string sup = d.getQueueRule();

            for(auto& rule: m_grammar.getRule(sup)) {
                EarleyItem item(sup, stringSplit(rule), 0, pos);
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
    std::cout << "-------------Parse Tree---------------" << "\n";
    for(const auto& d: m_parseTree) {
        std::cout << d << "\n";
    }
}
