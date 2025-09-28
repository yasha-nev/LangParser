#include "Application.hpp"

int main(int argc, char* argv[]) {
    if(argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <grammar.json> <vocab.json> <source.code>\n";
        return 1;
    }

    try {
        Application app(argv[1], argv[2]);
        app.run(argv[3]);
    } catch(const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
        return 1;
    }

    return 0;
}
