#include "Parser.hpp"

#include <ctime>

Parser::Parser(std::vector<Lexem>* tokens) {
    m_grammar["A"] = { "{ A0 } end" };
    m_grammar["A0"] = { "B", "D", "B A0", "D A0" };
    m_grammar["B"] = { "C : TYPES ;", "B B" };
    m_grammar["C"] = { "VARIABLES", "C , C" };
    m_grammar["D"] = { "while F do { D }",
                       "for E to G do { D }",
                       "if F then { D }",
                       "if F then { D } else { D }",
                       "E",
                       "D D" };
    m_grammar["E"] = { "C ass G ;" };
    m_grammar["F"] = { "F",      "( F )", "F or F", "F and F", "G = G", "G < G",
                       "G <> G", "G > G", "G <= G", "G >= G",  "G" };
    m_grammar["G"] = { "H", "( G )", "G + G", "G - G", "G * G", "G \\ G" };
    m_grammar["H"] = { "VARIABLES", "VALUE", "not F" };

    m_tokens = tokens;
}

void Parser::parsing() {
    m_tokens->push_back(
        Lexem((*m_tokens)[m_tokens->size() - 1].getPosInRow(), "", LexemType("END", "")));
    std::vector<std::set<EarleyItem>> D(m_tokens->size() + 1);
    D[0].insert(EarleyItem("1A", { "A" }, 0, 0));
    try {
        for(size_t i = 0; i < m_tokens->size() + 1; i++) {

            if(i > 0) {
                scan(D[i - 1], D[i], i);
            }

            int k = -1;
            while(D[i].size() != k) {
                k = D[i].size();
                complite(D, i);
                predict(D[i], i);
            }

            std::cout << std::string(50, '-') << "\n";
            if(i < (*m_tokens).size()) {
                std::cout << i << " " << (*m_tokens)[i].getName() << "\n";
            }
            for(const auto d: D[i]) {
                std::cout << d << "\n";
            }
            std::cout << "\n";
        }
    } catch(std::invalid_argument& ex) {
        std::cout << "----- ERROR: " << ex.what() << "-----" << "\n";
        return;
    }

    std::cout << "----NO ERROR FOUND PROGRAM IS TRUE----" << "\n";
    std::cout << "-------------Parse Tree---------------" << "\n";
    for(const auto d: m_parseTree) {
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
    EarleyItem EndEvent("A", { "{", "A0", "}", "end" }, 4, 0);
    for(const auto d: P_D) {
        if(d.getQueueRule() == (*m_tokens)[pos - 1].getName() ||
           d.getQueueRule() == "TYPES" && (*m_tokens)[pos - 1].getType() == "TYPES" ||
           d.getQueueRule() == "VALUE" && (*m_tokens)[pos - 1].getType() == "VALUE") {
            EarleyItem _Event = d;
            _Event.movePoint();
            C_D.insert(_Event);
        } else if(
            d.getQueueRule() == "VARIABLES" && (*m_tokens)[pos - 1].getType() == "VARIABLES") {
            bool a = 0;
            for(const auto d_sup: P_D) {
                if(d_sup.getVn() == "B") {
                    a = 1;
                    break;
                }
            }
            if(a == 1) {
                (*m_tokens)[pos - 1].addNewKey();
            } else if((*m_tokens)[pos - 1].getPos() == -1) {
                throw std::invalid_argument(
                    "Variable: " + (*m_tokens)[pos - 1].getName() + " not exist");
            }
            EarleyItem _Event = d;
            _Event.movePoint();
            C_D.insert(_Event);
        }

        if(EndEvent.compire(d) == 1 && (*m_tokens)[pos - 1].getName() != "") {
            throw std::invalid_argument(
                "Row " + std::to_string((*m_tokens)[pos - 1].getPosInRow()) + " symbols " +
                (*m_tokens)[pos - 1].getName() + " is not expected");
        }
    }
    if(C_D.size() == 0) {
        std::string str;
        for(const auto d: P_D) {
            if(m_grammar.count(d.getQueueRule()) == 0 && d.getQueueRule().size() != 0) {
                str = str + "," + d.getQueueRule();
            }
        }
        if(str.size() != 0) {
            throw std::invalid_argument(
                "Row " + std::to_string((*m_tokens)[pos - 1].getPosInRow()) + " " + str +
                " is expected");
        }
        throw std::invalid_argument(
            "Row " + std::to_string((*m_tokens)[pos - 1].getPosInRow()) +
            " No symbols is expected");
    }
}

void Parser::predict(std::set<EarleyItem>& D, int pos) {
    std::set<EarleyItem> D_sup;
    for(const auto d: D) {
        if(m_grammar.count(d.getQueueRule()) == 1) {
            std::string sup = d.getQueueRule();

            for(int i = 0; i < m_grammar[sup].size(); i++) {
                EarleyItem _Event(sup, stringSplit(m_grammar[sup][i]), 0, pos);
                D_sup.insert(_Event);
            }
        }
    }
    for(const auto d: D_sup) {
        D.insert(d);
    }
}

void Parser::complite(std::vector<std::set<EarleyItem>>& D, int pos) {
    std::set<EarleyItem> D_Sup;
    for(const auto d: D[pos]) {
        if(d.checkEnd() == 0) {
            continue;
        }
        m_parseTree.insert(d);
        int number = d.getNumber();

        for(const auto s: D[number]) {
            if(s.getQueueRule() == d.getVn()) {
                EarleyItem _Event(s);
                _Event.movePoint();
                D_Sup.insert(_Event);
            }
        }
    }
    for(const auto d: D_Sup) {
        D[pos].insert(d);
    }
}

std::vector<std::string> Parser::stringSplit(std::string str) {
    std::vector<std::string> sup;
    while(str.size() > 0) {
        int i = str.find(" ");
        if(i >= 0) {
            sup.push_back(str.substr(0, i));
            str = str.substr(i + 1);
        } else {
            sup.push_back(str);
            str = "";
        }
    }
    return sup;
}
