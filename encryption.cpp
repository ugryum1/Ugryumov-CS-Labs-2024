#include "encryption.hpp"

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

namespace {
const int kColumnWidh = 14;
const int kMaxKeyCode = 128;
const int kFive = 5;

int GetKeysCount() {
    std::ifstream file("keys.txt", std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл keys.txt." << std::endl;
        exit(1);
    }

    int keysCount{};
    char c{};
    bool inWord = false;

    while (file.get(c)) {
        if (std::isalpha(c)) {
            if (!inWord) {
                keysCount++;
                inWord = true;
            }
        } else {
            inWord = false;
        }
    }

    file.close();
    return keysCount;
}

void GetKeys(int* keysArray) {
    std::ifstream newFile("keys.txt", std::ios::binary);

    if (!newFile.is_open()) {
        std::cerr << "Не удалось открыть файл keys.txt." << std::endl;
        exit(1);
    }

    int keysCount{};
    char c{};
    bool inWord = false;
    int key{};

    while (newFile.get(c)) {
        if (std::isalpha(static_cast<unsigned char>(c))) {
            if (!inWord) {
                key = c;
                keysCount++;
                keysArray[keysCount - 1] = key;
                inWord = true;
            } else {
                key += c;
                keysArray[keysCount - 1] = key;
            }
        } else {
            inWord = false;
        }
    }

    if (!std::isalpha(static_cast<unsigned char>(c))) {
        keysArray[keysCount - 1] = key;
    }

    newFile.close();

    for (int i = 0; i < keysCount; ++i) {
        keysArray[i] %= kMaxKeyCode;
    }
}

void StatisticTable(int keysCount) {
    std::ifstream file("text.txt", std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл text.txt." << std::endl;
        return;
    }

    std::string line{};
    std::string text{};

    while (std::getline(file, line)) {
        text += line + "\n";
    }

    std::string symbols{};
    for (char i : text) {
        if (symbols.find(i) == std::string::npos) {
            symbols += i;
        }
    }

    std::cout << std::setw(kColumnWidh) << "symbol" << std::setw(kColumnWidh) << "ASCII code" << std::setw(kColumnWidh) << "symbol count"
              << std::setw(2 * kColumnWidh) << "encryption options number" << std::setw(kColumnWidh) << "keys number" << std::setw(kColumnWidh)
              << "text length" << std::endl;
    for (size_t i = 0; i < symbols.size(); ++i) {
        int* symbolKeysCount = new int[keysCount];
        for (size_t j = 0; j < static_cast<size_t>(keysCount); ++j) {
            symbolKeysCount[j] = 0;
        }

        for (size_t j = 0; j < static_cast<size_t>(text.size()); ++j) {
            if (text[j] == symbols[i]) {
                ++symbolKeysCount[static_cast<int>(j) % keysCount];
            }
        }

        size_t encryptionOptionsNumber{};
        for (size_t j = 0; j < static_cast<size_t>(keysCount); ++j) {
            if (symbolKeysCount[j]) {
                ++encryptionOptionsNumber;
            }
        }
        delete[] symbolKeysCount;

        if (i % kFive == 0 && i != 0) {
            std::cout << "\nвывести ещё 5 строк таблицы? (y/n)" << std::endl;
            char input{};
            std::cin >> input;
            if (input != 'y') {
                break;
            }
        }

        if (symbols[i] == '\n') {
            std::cout << std::setw(kColumnWidh) << "\\n";
        } else {
            std::cout << std::setw(kColumnWidh) << symbols[i];
        }
        std::cout << std::setw(kColumnWidh) << static_cast<int>(symbols[i]) << std::setw(kColumnWidh)
                  << std::count(text.begin(), text.end(), symbols[i]) << std::setw(2 * kColumnWidh) << encryptionOptionsNumber
                  << std::setw(kColumnWidh) << keysCount << std::setw(kColumnWidh) << text.size() << std::endl;
    }
    std::cout << std::endl;
}
}  // namespace

namespace encryption {
void StartEncryption(int* keysArray, int keysCount) {
    std::ifstream file("text.txt", std::ios::binary);
    std::ofstream encriptionFile("encryptedText.txt", std::ios::binary);

    if (!file.is_open() || !encriptionFile.is_open()) {
        std::cerr << "Не удалось открыть файл." << std::endl;
        return;
    }

    std::string line{};
    std::string text{};

    while (std::getline(file, line)) {
        text += line + "\n";
    }

    file.close();

    for (size_t i = 0; i < text.size(); ++i) {
        encriptionFile << static_cast<char>(static_cast<int>(text[i]) + keysArray[i % keysCount]);
    }

    encriptionFile.close();

    std::cout << "Файл успешно закодирован." << std::endl;

    StartDecoding(keysArray, keysCount);
}

void StartDecoding(int* keysArray, int keysCount) {
    std::ifstream file("encryptedText.txt", std::ios::binary);
    std::ofstream decodingFile("decodingText.txt", std::ios::binary);

    if (!file.is_open() || !decodingFile.is_open()) {
        std::cerr << "Не удалось открыть файл." << std::endl;
        return;
    }

    std::string line;
    std::string text;

    while (std::getline(file, line)) {
        text += line + "\n";
    }

    file.close();

    size_t textSymbolCount = text.size();

    for (size_t i = 0; i < textSymbolCount - 1; ++i) {
        decodingFile << static_cast<char>(static_cast<int>(text[i]) - keysArray[i % keysCount]);
    }

    decodingFile.close();

    std::cout << "Файл успешно расшифрован." << std::endl;

    StatisticTable(keysCount);
}

void StartProgram() {
    int keysCount = GetKeysCount();
    if (keysCount <= 0) {
        std::cerr << "Количество ключей должно быть положительным числом." << std::endl;
        return;
    }
    int* keysArray = new int[keysCount];
    GetKeys(keysArray);
    StartEncryption(keysArray, keysCount);
    delete[] keysArray;
}

void ExecuteApp() {
    char continueExecution = 'y';
    while (continueExecution == 'y') {
        StartProgram();

        std::cout << "Продолжить работу? (y/n)" << std::endl;
        std::cin >> continueExecution;
        if (continueExecution == 'y') {
            std::cout << std::endl;
        }
    }
}
}  // namespace encryption
