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

// String ops (minimal implementation if needed by generated code)
// string_concat is already defined in StringOps.cpp

// AI stubs (to allow linking if AI features are disabled/missing)
// Ideally these are provided by OllamaClient.cpp, but if that fails linking...
// For now, let's assume OllamaClient handles its symbols.

} // extern "C"
