#include "main.h"
#include <iostream>
#include <filesystem>
#define FMT_HEADER_ONLY
#include <fmt/core.h>
#include "main.h"

namespace fs = std::filesystem;

void printdir(const fs::path& path) {
    std::string fullPath;
    std::string spaces;
    int slashes = 0;
    int diff;
    int path_slashes;
    for (char e : path.generic_string()) {
        if (e != '/') continue;
        path_slashes++;
    }
    for(const auto& file : fs::recursive_directory_iterator(path)){
        std::string fileName = file.path().filename();
        if (file.is_directory())
            fileName = fmt::format("┬─ \e[0;34m🗁 {}\e[0m", fileName);
        for (char e : file.path().generic_string()) {
            if (e != '/') continue;
            slashes++;
        }
        slashes -= 1;
        diff = slashes - path_slashes;

        for (int i{0}; i <= diff; i++) spaces += "  ";

        fullPath += fmt::format("{}├─{}\n", spaces, fileName);
        spaces = "";
        slashes = 0;
    }
    std::cout << fullPath;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printdir(".");
        return 0;
    }
    if (std::strcmp(argv[1], "--help") == 0) {
        printf("\e[0;34m%s\e[0m\n", ART);
        printf("lt <dir>\n");
        printf("lt : displays tree of the current directory\n");
        printf("lt --help : displays this menu\n");
        return 0;
    }
    printdir(argv[1]);
    return 0;
}
