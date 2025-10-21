#include "Parser.hpp"

#include <ctime>

Parser::Parser(std::vector<Lexem>& tokens, Vocabulary &vocabulary, Grammar& grammar):
    m_tokens(tokens),
    m_vocabulary(vocabulary),
    m_grammar(grammar) {
}

void Parser::parsing() {
    m_tokens.push_back(
        Lexem(LexemCategory::END, 900, -1, m_tokens[m_tokens.size() - 1].getLineNumber()));

    std::vector<std::set<EarleyItem>> D(m_tokens.size() + 1);
    D[0].insert(EarleyItem(m_vocabulary.getWordId("1A"), { m_vocabulary.getWordId("A") }, 0, 0));

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
        }
    } catch(std::invalid_argument& ex) {
        std::cout << "----- ERROR: " << ex.what() << "-----"
                  << "\n";
        return;
    }
}

void Parser::printLineScan(int line, const Lexem& token, std::set<EarleyItem>& D) {
    std::cout << std::string(50, '-') << "\n";
    std::cout << "line number: " << std::to_string(line) + " symbol: " << m_vocabulary.getWord(token.getType(), token.getWordId()) << "\n\n";

    for(const auto& d: D) {
        std::cout << d << "\n";
    }
}

void Parser::scan(
    std::set<EarleyItem>& P_D,
    std::set<EarleyItem>& C_D,
    int pos) { // P = past, C - Current
    if(pos == 0) {
        return;
    }
    EarleyItem endItem(
        m_vocabulary.getWordId("A"), 
        { m_vocabulary.getWordId("{"), 
            m_vocabulary.getWordId("A0"), 
            m_vocabulary.getWordId("}")}, 
            4, 0);
    Lexem& preToken = m_tokens[pos - 1];

    for(const auto& d: P_D) {
        if(d.getQueueRule() == preToken.getWordId() ||
           d.getQueueRule() == m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "TYPES") && preToken.getType() == LexemCategory::TYPES ||
           d.getQueueRule() == m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "VALUE") && preToken.getType() == LexemCategory::VALUE ||
           d.getQueueRule() == m_vocabulary.getWordId(LexemCategory::NOTERMINAL, "VARIABLES") && preToken.getType() == LexemCategory::VARIABLES) {
            EarleyItem item = d;
            item.movePoint();
            C_D.insert(item);
        }

        if(endItem == d && preToken.getWordId() != 900) {
            throw std::invalid_argument(
                "Row " + std::to_string(preToken.getLineNumber()) + " symbols " +
                m_vocabulary.getWord(preToken.getType(), preToken.getWordId()) + " is not expected");
        }
    }
    if(C_D.empty()) {
        throwUnexpectedToken(preToken, P_D);
    }
}

void Parser::throwUnexpectedToken(const Lexem& preToken, const std::set<EarleyItem>& P_D) const {
    std::set<std::string> missingRulesSet;
    for(const auto& d: P_D) {
        int rule = d.getQueueRule();
        if(m_grammar.getCountElementsInRule(rule) == 0 && rule != -1) {
            missingRulesSet.insert(m_vocabulary.getWord(rule));
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
            m_vocabulary.getWord(preToken.getType(), preToken.getWordId()) + "': unexpected token; expected one of " + missingRules + "");
    }

    throw std::invalid_argument(
        "Error: row " + std::to_string(preToken.getLineNumber()) + ", symbol '" +
        m_vocabulary.getWord(preToken.getType(), preToken.getWordId()) + "': unexpected token; no symbols expected");
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

static void printEarlyItem(const EarleyItem &eItem, const Vocabulary &vocabulary) {
    std::string vn = vocabulary.getWord(LexemCategory::NOTERMINAL, eItem.getVn());
    std::cout << std::string(2 - vn.size(), ' ')  << vn << " -> ";

    int n = 0;

    for (const auto &rule : eItem.getRule()) {
        std::string ruleWorld = vocabulary.getWord(rule);
        std::cout << ruleWorld << " ";
        n += ruleWorld.size() + 1;
    }

    std::cout << std::string(30 - n, ' ') << " | "  << eItem.getNumber() << "\n";
}

void Parser::printTree() {
    std::cout << "GRAMMATICAL SEQUENCE"
              << "\n";
    for(const auto& d: m_parseTree) {
        //std::cout << d;
        printEarlyItem(d, m_vocabulary);
    }
}

std::set<EarleyItem>& Parser::getParserOutput() {
    return m_parseTree;
}