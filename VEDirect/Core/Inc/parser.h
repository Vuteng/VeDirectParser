#ifndef PARSER_H
#define PARSER_H

#include <stdint.h>

#define MAX_FIELDS 22       // Maximum number of fields in a block
#define LABEL_SIZE 9        // Buffer size for field label (8 characters + null terminator)
#define VALUE_SIZE 33       // Buffer size for field value (32 characters + null terminator)

typedef struct {
    char label[LABEL_SIZE]; // Field label
    char value[VALUE_SIZE]; // Field value
} vedirect_field_t;

typedef struct {
    vedirect_field_t fields[MAX_FIELDS];
    uint8_t field_count;    // Number of fields currently stored
} vedirect_data_t;

// Declare ve_data as extern so it can be accessed globally
extern vedirect_data_t ve_data;

void parse_frame();

#endif // PARSER_H
