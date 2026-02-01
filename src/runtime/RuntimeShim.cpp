#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

extern "C" {

// Basic IO
void println_str(const char* s) {
    printf("%s\n", s);
}

void print_str(const char* s) {
    printf("%s", s);
}

void println_int(int i) {
    printf("%d\n", i);
}

void print_int(int i) {
    printf("%d", i);
}

void println_void() {
    printf("\n");
}

int read_int() {
    int i;
    scanf("%d", &i);
    return i;
}

// String ops
char* string_concat(const char* s1, const char* s2) {
    if (!s1) s1 = "";
    if (!s2) s2 = "";
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    char* result = (char*)malloc(len1 + len2 + 1);
    if (result) {
        strcpy(result, s1);
        strcat(result, s2);
    }
    return result;
}

} // extern "C"
