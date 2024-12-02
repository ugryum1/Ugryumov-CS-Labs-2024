#ifndef MDICT_HPP
#define MDICT_HPP

struct Dictionary {
    char *engl;    // слово по-английски
    char *rus;     // слово по-русски
};

int menu();

int interactive();
int demo();

void add_w(Dictionary*& dict, int *n, char* temp_engl, char* temp_rus);
void rm_w(Dictionary*& dict, int *n, char* word);
void translate_to_rus(Dictionary*& dict, int *n, char* word);
void translate_to_engl(Dictionary*& dict, int *n, char* word);
void print_dict(Dictionary*& dict, int *n);
void add_dict_to_file(Dictionary*& dict, int *n);


#endif  // MDICT_HPP
