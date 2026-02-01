// Generic I/O Runtime with function overloading

#include <stdio.h>
#include <stdbool.h>

// ============= PRINT (no newline) =============

void print_int(int value) {
    printf("%d", value);
}

void print_str(const char* str) {
    printf("%s", str);
}

void print_bool(int value) {
    printf("%s", value ? "true" : "false");
}

void print_char(char c) {
    printf("%c", c);
}

// ============= PRINTLN (with newline) =============

void println_int(int value) {
   printf("%d\n", value);
}

void println_str(const char* str) {
    printf("%s\n", str);
}

void println_bool(int value) {
    printf("%s\n", value ? "true" : "false");
}

void println_char(char c) {
    printf("%c\n", c);
}

void println_void() {
    printf("\n");
}

// ============= READ =============

int read_int() {
    int value;
    if (scanf("%d", &value) == 1) {
        return value;
    }
    return 0;
}

// Note: returning pointer to static buffer
// ============= DATA STRUCTURES =============

#include <stdlib.h>
#include <string.h>

// --- VECTOR (Dynamic Array) ---
// Simple vector holding integers (can be cast to ptrs)

typedef struct {
    int* data;
    int size;
    int capacity;
} Vector;

void* vector_new() {
    Vector* v = (Vector*)malloc(sizeof(Vector));
    v->size = 0;
    v->capacity = 10;
    v->data = (int*)malloc(sizeof(int) * v->capacity);
    return v;
}

void vector_push(void* v_ptr, int val) {
    if (!v_ptr) return;
    Vector* v = (Vector*)v_ptr;
    if (v->size >= v->capacity) {
        v->capacity *= 2;
        v->data = (int*)realloc(v->data, sizeof(int) * v->capacity);
    }
    v->data[v->size++] = val;
}

int vector_get(void* v_ptr, int idx) {
    if (!v_ptr) return 0;
    Vector* v = (Vector*)v_ptr;
    if (idx < 0 || idx >= v->size) return 0; // Boundary check
    return v->data[idx];
}

int vector_size(void* v_ptr) {
    if (!v_ptr) return 0;
    Vector* v = (Vector*)v_ptr;
    return v->size;
}

// --- MAP (String -> Int) ---
// Simple Linear Probe Hash Map for simplicity

typedef struct {
    char* key;
    int value;
    bool occupied;
} Entry;

typedef struct {
    Entry* entries;
    int capacity;
    int size;
} Map;

void* map_new() {
    Map* m = (Map*)malloc(sizeof(Map));
    m->size = 0;
    m->capacity = 16;
    m->entries = (Entry*)calloc(m->capacity, sizeof(Entry));
    return m;
}

unsigned long hash_str(const char* str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}

void map_put(void* m_ptr, const char* key, int val) {
    if (!m_ptr || !key) return;
    Map* m = (Map*)m_ptr;
    
    // Resize if load factor > 0.7
    if (m->size > m->capacity * 0.7) {
        // ... resizing logic omitted for MVP brevity ...
        // Realloc is complex for hash maps (rehash needed).
        // For MVP, fix size or implementing full rehash later.
        // Let's implement basic doubling rehash.
        int old_cap = m->capacity;
        Entry* old_entries = m->entries;
        
        m->capacity *= 2;
        m->entries = (Entry*)calloc(m->capacity, sizeof(Entry));
        m->size = 0;
        
        for (int i=0; i<old_cap; i++) {
            if (old_entries[i].occupied) {
                map_put(m, old_entries[i].key, old_entries[i].value);
                free(old_entries[i].key); // map_put dups key
            }
        }
        free(old_entries);
    }
    
    unsigned long h = hash_str(key);
    int idx = h % m->capacity;
    
    while (m->entries[idx].occupied) {
        if (strcmp(m->entries[idx].key, key) == 0) {
            // Update
            m->entries[idx].value = val;
            return;
        }
        idx = (idx + 1) % m->capacity;
    }
    
    m->entries[idx].key = strdup(key);
    m->entries[idx].value = val;
    m->entries[idx].occupied = true;
    m->size++;
}

int map_get(void* m_ptr, const char* key) {
    if (!m_ptr || !key) return 0;
    Map* m = (Map*)m_ptr;
    
    unsigned long h = hash_str(key);
    int idx = h % m->capacity;
    int start_idx = idx;
    
    while (m->entries[idx].occupied) {
        if (strcmp(m->entries[idx].key, key) == 0) {
            return m->entries[idx].value;
        }
        idx = (idx + 1) % m->capacity;
        if (idx == start_idx) break;
    }
    return 0; // Not found
}

// ============= FILE I/O =============

#include <sys/stat.h>
#include <unistd.h>

// File open - returns FILE* as void*
void* file_open(const char* path, const char* mode) {
    if (!path || !mode) return NULL;
    FILE* fp = fopen(path, mode);
    return (void*)fp;
}

// File close
void file_close(void* file) {
    if (!file) return;
    fclose((FILE*)file);
}

// File read - reads entire file content
// Returns static buffer (simplified - in production use dynamic allocation)
char* file_read(void* file) {
    if (!file) return "";
    
    FILE* fp = (FILE*)file;
    static char buffer[65536]; // 64KB buffer
    
    // Save current position
    long pos = ftell(fp);
    
    // Read from start
    fseek(fp, 0, SEEK_SET);
    size_t bytes_read = fread(buffer, 1, sizeof(buffer) - 1, fp);
    buffer[bytes_read] = '\0';
    
    // Restore position
    fseek(fp, pos, SEEK_SET);
    
    return buffer;
}

// File write
void file_write(void* file, const char* data) {
    if (!file || !data) return;
    FILE* fp = (FILE*)file;
    fputs(data, fp);
}

// File read line - reads one line
char* file_read_line(void* file) {
    if (!file) return "";
    
    FILE* fp = (FILE*)file;
    static char line_buffer[4096];
    
    if (fgets(line_buffer, sizeof(line_buffer), fp)) {
        // Remove trailing newline
        size_t len = strlen(line_buffer);
        if (len > 0 && line_buffer[len-1] == '\n') {
            line_buffer[len-1] = '\0';
        }
        return line_buffer;
    }
    
    return ""; // EOF or error
}

// File exists - checks if file exists
int file_exists(const char* path) {
    if (!path) return 0;
    return access(path, F_OK) == 0 ? 1 : 0;
}

// File size - returns file size in bytes
int file_size(const char* path) {
    if (!path) return 0;
    
    struct stat st;
    if (stat(path, &st) == 0) {
        return (int)st.st_size;
    }
    return 0;
}

// File delete - deletes a file
int file_delete(const char* path) {
    if (!path) return 0;
    return remove(path) == 0 ? 1 : 0;
}

// ============= SEMANTIC SIMILARITY =============

#include <ctype.h>
#include <math.h>

// Helper: Convert string to lowercase
static void to_lowercase(char* dest, const char* src) {
    while (*src) {
        *dest++ = tolower(*src++);
    }
    *dest = '\0';
}

// Helper: Jaccard similarity between two strings (set of words)
static float jaccard_similarity(const char* s1, const char* s2) {
    if (!s1 || !s2) return 0.0f;
    
    // Simple tokenization and comparison
    char buf1[4096], buf2[4096];
    to_lowercase(buf1, s1);
    to_lowercase(buf2, s2);
    
    // Count common characters (simplified)
    int common = 0;
    int total = 0;
    int freq1[256] = {0};
    int freq2[256] = {0};
    
    for (const char* p = buf1; *p; p++) {
        if (isalpha(*p)) freq1[(unsigned char)*p]++;
    }
    for (const char* p = buf2; *p; p++) {
        if (isalpha(*p)) freq2[(unsigned char)*p]++;
    }
    
    for (int i = 0; i < 256; i++) {
        if (freq1[i] && freq2[i]) {
            common += (freq1[i] < freq2[i]) ? freq1[i] : freq2[i];
        }
        total += (freq1[i] > freq2[i]) ? freq1[i] : freq2[i];
    }
    
    return total > 0 ? (float)common / total : 0.0f;
}

// Helper: Levenshtein distance normalized
static float levenshtein_similarity(const char* s1, const char* s2) {
    if (!s1 || !s2) return 0.0f;
    
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    
    if (len1 == 0) return len2 == 0 ? 1.0f : 0.0f;
    if (len2 == 0) return 0.0f;
    
    // Simple character-based distance (simplified for demo)
    int distance = abs(len1 - len2);
    int min_len = len1 < len2 ? len1 : len2;
    
    for (int i = 0; i < min_len; i++) {
        if (tolower(s1[i]) != tolower(s2[i])) {
            distance++;
        }
    }
    
    int max_len = len1 > len2 ? len1 : len2;
    return max_len > 0 ? 1.0f - (float)distance / max_len : 0.0f;
}

// Semantic similarity - combines multiple metrics
float semantic_similarity(const char* str1, const char* str2) {
    if (!str1 || !str2) return 0.0f;
    
    // Exact match
    if (strcmp(str1, str2) == 0) return 1.0f;
    
    // Case-insensitive match
    char buf1[4096], buf2[4096];
    to_lowercase(buf1, str1);
    to_lowercase(buf2, str2);
    if (strcmp(buf1, buf2) == 0) return 0.95f;
    
    // Combine Jaccard and Levenshtein
    float jaccard = jaccard_similarity(str1, str2);
    float levenshtein = levenshtein_similarity(str1, str2);
    
    // Weighted average
    return 0.6f * jaccard + 0.4f * levenshtein;
}

// Semantic equality with threshold
int semantic_equals(const char* str1, const char* str2, float threshold) {
    float similarity = semantic_similarity(str1, str2);
    return similarity >= threshold ? 1 : 0;
}

// ============= STRING OPERATIONS =============

char* string_concat(const char* s1, const char* s2) {
    if (!s1) s1 = "";
    if (!s2) s2 = "";
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    char* result = (char*)malloc(len1 + len2 + 1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}
