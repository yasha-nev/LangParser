#include "Application.hpp"

#include "GrammarLoader.hpp"
#include "VocabularyLoader.hpp"

Application::Application(const std::string& grammarFile, const std::string& vocabFile):
    m_vocabulary(VocabularyLoader::loadFromJson(vocabFile)),
    m_grammar(GrammarLoader::loadFromJson(grammarFile, m_vocabulary)),
    m_lexer(m_vocabulary),
    m_parser(m_lexer.getTokens(), m_vocabulary, m_grammar) {
}

void Application::run(const std::string& sourceFile) {
    m_lexer.fileCodeAnalysis(sourceFile);
    m_parser.parsing();
    m_parser.printTree();

    ASTBuilder astBuilder(m_vocabulary, m_lexer.getTokens(), m_parser.getParserOutput());
    std::unique_ptr<AST> ast = astBuilder.buildTree();

    ast->printTree();
}
