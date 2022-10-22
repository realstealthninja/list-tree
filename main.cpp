#include <iostream>
#include <filesystem>
#define FMT_HEADER_ONLY
#include <fmt/core.h>
namespace fs = std::filesystem;

void printdir(fs::path path) {
    int depth = 0;
    std::string spaces = "";
    std::string fullPath = "";
    for(const auto& file : fs::recursive_directory_iterator(path)){
        std::string fileName = file.path().filename();
        std::string parent_path = file.path().parent_path().concat("/");
        if(file.is_directory()){
            fileName = fmt::format("┬─ \e[0;34m🗁 {}\e[0m", fileName);
            depth++;
        }
        if (parent_path == path) { depth=0; }
        for(int i; i<depth; i++) { spaces += "  ";}
        fullPath += fmt::format("{}├─{}\n", spaces, fileName);
    }
    std::cout << fullPath;
}

int main(int argc, char *argv[]) {
    printdir(argv[1]);
    if (argc != 2) {
        return 0;
    }
}
