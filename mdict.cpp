#include "mdict.hpp"

#include <iostream>
#include <cstring>
#include <fstream>

int menu() {
    std::cout << "Что сделать?" << std::endl;
    std::cout << "\t1. Добавить слово в словарь." << std::endl;
    std::cout << "\t2. Удалить слово из словаря." << std::endl;
    std::cout << "\t3. Перевести слово с английского на русский." << std::endl;
    std::cout << "\t4. Перевести слово с русского на английский." << std::endl;
    std::cout << "\t5. Вывести словарь на экран." << std::endl;
    std::cout << "\t6. Вывести словарь в файл." << std::endl;
    std::cout << "\t7. Завершить программу." << std::endl;

    int choice;
    std::cin >> choice;
    return choice;
}

void create_dict(Dictionary*& dict) {
    dict[0].engl = new char[6];
    std::strcpy(dict[0].engl, "apple");
    dict[0].rus = new char[8];
    std::strcpy(dict[0].rus, "yabloko");

    dict[1].engl = new char[5];
    std::strcpy(dict[1].engl, "book");
    dict[1].rus = new char[6];
    std::strcpy(dict[1].rus, "kniga");

    dict[2].engl = new char[4];
    std::strcpy(dict[2].engl, "car");
    dict[2].rus = new char[8];
    std::strcpy(dict[2].rus, "mashina");

    dict[3].engl = new char[5];
    std::strcpy(dict[3].engl, "door");
    dict[3].rus = new char[5];
    std::strcpy(dict[3].rus, "dver");

    dict[4].engl = new char[11];
    std::strcpy(dict[4].engl, "helicopter");
    dict[4].rus = new char[9];
    std::strcpy(dict[4].rus, "vertolet");

    dict[5].engl = new char[6];
    std::strcpy(dict[5].engl, "human");
    dict[5].rus = new char[9];
    std::strcpy(dict[5].rus, "chelovek");

    dict[6].engl = new char[4];
    std::strcpy(dict[6].engl, "pen");
    dict[6].rus = new char[7];
    std::strcpy(dict[6].rus, "ruchka");

    dict[7].engl = new char[6];
    std::strcpy(dict[7].engl, "table");
    dict[7].rus = new char[5];
    std::strcpy(dict[7].rus, "stol");

    dict[8].engl = new char[4];
    std::strcpy(dict[8].engl, "tree");
    dict[8].rus = new char[7];
    std::strcpy(dict[8].rus, "derevo");

    dict[9].engl = new char[6];
    std::strcpy(dict[9].engl, "world");
    dict[9].rus = new char[4];
    std::strcpy(dict[9].rus, "mir");
}

void delete_dict(Dictionary*& dict, int *n) {
    for (int i = 0; i < *n; ++i) {
        delete[] dict[i].engl;
        delete[] dict[i].rus;
    }

    delete[] dict;
    dict = nullptr;
}

int compare(const char *a, const char *b) {
    while (*a && *b && *a == *b) {
        a++;
        b++;
    }
    return *(const unsigned char *)a - *(const unsigned char *)b;
}

int binarySearch(Dictionary *dict, int n, const char *word) {
    int left = 0;
    int right = n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (compare(dict[mid].engl, word) == 0)
            return mid; // Найдено совпадение

        if (compare(dict[mid].engl, word) > 0)
            right = mid - 1;
        else
            left = mid + 1;
    }

    return -1; // Элемент не найден
}

void add_w(Dictionary*& dict, int *n, char* temp_engl, char* temp_rus) {
    // Выделение памяти для новых слов
    char *new_engl_word = new char[std::strlen(temp_engl) + 1];
    char *new_rus_word = new char[std::strlen(temp_rus) + 1];
    std::strcpy(new_engl_word, temp_engl);
    std::strcpy(new_rus_word, temp_rus);

    int pos = 0;
    while (pos < *n && compare(dict[pos].engl, new_engl_word) <= 0) {
        ++pos;
    }

    const int new_size = *n + 1;
    Dictionary *new_dict = new Dictionary[new_size];

    // Копирование старых элементов до позиции вставки
    for (int i = 0; i < pos; ++i) {
        new_dict[i].engl = new char[std::strlen(dict[i].engl) + 1];
        std::strcpy(new_dict[i].engl, dict[i].engl);
        new_dict[i].rus = new char[std::strlen(dict[i].rus) + 1];
        std::strcpy(new_dict[i].rus, dict[i].rus);
    }

    // Вставка нового элемента
    new_dict[pos].engl = new_engl_word;
    new_dict[pos].rus = new_rus_word;

    // Копирование оставшихся элементов
    for (int i = pos; i < *n; ++i) {
        new_dict[i + 1].engl = new char[std::strlen(dict[i].engl) + 1];
        std::strcpy(new_dict[i + 1].engl, dict[i].engl);
        new_dict[i + 1].rus = new char[std::strlen(dict[i].rus) + 1];
        std::strcpy(new_dict[i + 1].rus, dict[i].rus);
    }

    // Удаление старого массива
    delete_dict(dict, n);

    // Замена старого массива на новый
    dict = new_dict;
    ++(*n);

    std::cout << "Слово добавлено в словарь.\n" << std::endl;
}

void rm_w(Dictionary*& dict, int *n, char* word) {
    int pos = 0;
    bool flag = false;
    for (int i = 0; i < *n; ++i) {
        if (compare(dict[i].engl, word) == 0 || compare(dict[i].rus, word) == 0) {
            pos = i;
            flag = true;
            break;
        }
    }

    if (!flag) {
        std::cout << "Такого слова нет в словаре.\n" << std::endl;
        return;
    }

    const int new_size = *n - 1;
    Dictionary *new_dict = new Dictionary[new_size];

    // Копирование старых элементов до позиции вставки
    for (int i = 0; i < pos; ++i) {
        new_dict[i].engl = new char[std::strlen(dict[i].engl) + 1];
        std::strcpy(new_dict[i].engl, dict[i].engl);
        new_dict[i].rus = new char[std::strlen(dict[i].rus) + 1];
        std::strcpy(new_dict[i].rus, dict[i].rus);
    }

    // Копирование оставшихся элементов
    for (int i = pos; i < *n - 1; ++i) {
        new_dict[i].engl = new char[std::strlen(dict[i + 1].engl) + 1];
        std::strcpy(new_dict[i].engl, dict[i + 1].engl);
        new_dict[i].rus = new char[std::strlen(dict[i + 1].rus) + 1];
        std::strcpy(new_dict[i].rus, dict[i + 1].rus);
    }

    // Удаление старого массива
    delete_dict(dict, n);

    // Замена старого массива на новый
    dict = new_dict;
    --(*n);

    std::cout << "Слово удалено из словаря.\n" << std::endl;
}

void translate_to_rus(Dictionary*& dict, int *n, char* word) {
    int pos = binarySearch(dict, *n, word);

    if (pos == -1) {
        std::cout << "Такого слова нет в словаре.\n" << std::endl;
        return;
    }

    std::cout << "Перевод слова " << word << " на русский: " << dict[pos].rus << std::endl << std::endl;
}

void translate_to_engl(Dictionary*& dict, int *n, char* word) {
    for (int i = 0; i < *n; ++i) {
        if (compare(dict[i].rus, word) == 0) {
            std::cout << "Перевод слова " << word << " на английский: " << dict[i].engl << std::endl << std::endl;
            return;
        }
    }

    std::cout << "Такого слова нет в словаре.\n" << std::endl;
}

void print_dict(Dictionary*& dict, int *n) {
    for (int i = 0; i < *n; ++i) {
        std::cout << dict[i].engl << " - " << dict[i].rus << std::endl;
    }
    std::cout << std::endl;
}

void add_dict_to_file(Dictionary*& dict, int *n) {
    std::ofstream file("dict.txt");

    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл для записи." << std::endl;
        return;
    }

    for (int i = 0; i < *n; ++i) {
        file << dict[i].engl << '\n';
        file << dict[i].rus << '\n';
        file << '\n';
    }

    file.close();
    std::cout << "Словарь добавлен в файл dict.txt.\n" << std::endl;
}

int interactive() {
    int n = 10;
    Dictionary* dict = new Dictionary[n];

    create_dict(dict);

    std::cout << "interactive" << std::endl;

    char word[100];

    while (true) {
        switch (menu()) {
            case 1:
                std::cout << "Введите через пробел новое слово на английском языке и его перевод на русский язык.\n";
                char temp_engl[100], temp_rus[100];
                std::cin >> temp_engl >> temp_rus;
                add_w(dict, &n, temp_engl, temp_rus);
                break;
            case 2:
                std::cout << "Введите слово, которое нужно удалить.\n";
                std::cin >> word;
                rm_w(dict, &n, word);
                break;
            case 3:
                std::cout << "Введите английское слово." << std::endl;
                std::cin >> word;
                translate_to_rus(dict, &n, word);
                break;
            case 4:
                std::cout << "Введите русское слово." << std::endl;
                std::cin >> word;
                translate_to_engl(dict, &n, word);
                break;
            case 5:
                print_dict(dict, &n);
                break;
            case 6:
                add_dict_to_file(dict, &n);
                break;
            case 7:
                delete_dict(dict, &n);
                return 0;
            default:
                std::cout << " Надо вводить число от 1 до 7" << std::endl;
                break;
        }
    }

    delete_dict(dict, &n);

    return 0;
}


int demo() {
    int n = 10;
    Dictionary* dict = new Dictionary[n];

    create_dict(dict);

    //5
    std::cout << "Исходный словарь:" << std::endl;
    print_dict(dict, &n);

    // 1
    std::cout << "Вывод словаря после добавления слова 'dog' с переводом 'sobaka':" << std::endl;
    char temp_engl[4] = "dog", temp_rus[7] = "sobaka";
    add_w(dict, &n, temp_engl, temp_rus);
    print_dict(dict, &n);

    // 2
    std::cout << "Вывод словаря после удаления слова 'door':" << std::endl;
    char word_door[5] = "door";
    rm_w(dict, &n, word_door);
    print_dict(dict, &n);

    //3
    char word_book[5] = "book";
    translate_to_rus(dict, &n, word_book);

    //4
    char word_ruchka[7] = "ruchka";
    translate_to_engl(dict, &n, word_ruchka);

    //6
    add_dict_to_file(dict, &n);

    return 0;
}

int main(int argc, char *argv[]) {
    bool isInteractive = false; // по умолчанию демо-режим.

    // Если i передается в качестве аргумента, то программу
    // необходимо запустить в интерактивном режиме
    if ((argc == 2) && strcmp(argv[1], "i") == 0) {
        isInteractive = true;
    }

    if (isInteractive) {
        return interactive();

    } else {
        return demo();
    }
}
