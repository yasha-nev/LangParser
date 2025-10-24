#include "Application.hpp"

#include "GrammarLoader.hpp"
#include "VocabularyLoader.hpp"

Application::Application(const std::string& grammarFile, const std::string& vocabFile):
    m_vocabulary(VocabularyLoader::loadFromJson(vocabFile)),
    m_grammar(GrammarLoader::loadFromJson(grammarFile, m_vocabulary)) {
}

void Application::run(const std::string& sourceFile) {

    LexicalAnalyzer lexicalAnalyzer(m_vocabulary);
    lexicalAnalyzer.performLexicalAnalisis(sourceFile);

    Parser parser(m_vocabulary, m_grammar);
    parser.performSyntaxAnalysis(lexicalAnalyzer.getTokens());
    parser.printTree();

    ASTBuilder astBuilder(m_vocabulary, lexicalAnalyzer.getTokens(), parser.getParserOutput());
    auto ast = astBuilder.buildTree();
    ast->printTree();
}
