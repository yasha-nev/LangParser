#include "Lexem.hpp"

Lexem::Lexem(LexemCategory type, int wordId, int position, int lineNumber):
    m_type(type),
    m_wordId(wordId),
    m_position(position),
    m_lineNumber(lineNumber) {
}

LexemCategory Lexem::getType() const noexcept {
    return m_type;
}

int Lexem::getWordId() const noexcept {
    return m_wordId;
}

int Lexem::getPosition() const noexcept {
    return m_position;
}

int Lexem::getLineNumber() const noexcept {
    return m_lineNumber;
}
