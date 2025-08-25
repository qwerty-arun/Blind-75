#include <iostream>
#include <unordered_map>

int main() {
    std::unordered_map<std::string, int> umap;
    umap["apple"] = 3;
    umap["banana"] = 2;
    umap["orange"] = 5;

    for (const auto& pair : umap) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    return 0;
}