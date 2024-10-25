#include <iostream>
#include <fstream>
#include <random>
#include <unordered_map>
#include <json/json.h>

void encryptFile(const std::string& inputFile, const std::string& outputFile, const std::string& explanationFile) {
    std::ifstream inFile(inputFile);
    std::ofstream outFile(outputFile);
    std::ofstream explFile(explanationFile);
    
    if (!inFile.is_open()  !outFile.is_open()  !explFile.is_open()) {
        std::cerr << "Помилка при відкритті файлів!" << std::endl;
        return;
    }

    std::unordered_map<char, char> charMap;
    Json::Value jsonRoot;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(32, 126);

    char ch;
    while (inFile.get(ch)) {
        if (charMap.find(ch) == charMap.end()) {
            char randomChar = static_cast<char>(dis(gen));
            charMap[ch] = randomChar;
            jsonRoot[std::string(1, ch)] = std::string(1, randomChar);
        }
        outFile.put(charMap[ch]);
    }

    explFile << jsonRoot.toStyledString();

    inFile.close();
    outFile.close();
    explFile.close();
}

int main() {
    encryptFile("input.txt", "C:\\Windows\\system32\\output.txt", "C:\\Windows\\system32\\Werhoun.json");
    std::cout << "Шифрування завершено!" << std::endl;
    return 0;
}
