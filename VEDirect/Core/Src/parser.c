#include "parser.h"
#include <string.h>
#include <stdio.h>

vedirect_data_t ve_data;

// Function to set the state
void data_set_state(DATA_STATE new_state)
{
    data_state = new_state;
}

// Function to get the current state
DATA_STATE data_get_state(void)
{
    return data_state;
}


uint8_t calculate_checksum(char *frame, uint16_t size)
{
	volatile int checksum_calculated = 0;

	for(int i = 0; i < size; i++) {
        checksum_calculated = (checksum_calculated + (int)frame[i]) % 256;
    }

    //printf("Calculated checksum: %c", checksum_calculated );

    return checksum_calculated;
}

//parses the whole string frame to array of structs
void parse_frame(const char *input, vedirect_field_t fields[]) {
    const char *start = input;  // Pointer to start of the string
    const char *end = input + strlen(input);  // Pointer to the end of the string
    int count = 0;  // Counter for fields

    while (start < end) {
        // Find the position of the next \r\n (end of label-value pair)
        const char *line_end = strstr(start, "\r\n");
        if (!line_end) {
            break;  // No more lines
        }

        // Find the position of the \t (delimiter between label and value)
        const char *tab = strchr(start, '\t');
        if (tab && tab < line_end) {
            fields[count].label = (char *)start;       // Point to the start of the label
            fields[count].value = (char *)(tab + 1);   // Point to the start of the value

            // Null terminate the label and value temporarily for printing or further processing
            *((char *)tab) = '\0';            // Null terminate the label
            *((char *)line_end) = '\0';       // Null terminate the value

            count++;
        }

        // Move the start pointer to the next line
        start = line_end + 2;  // Skip \r\n
    }

    // Add a sentinel NULL at the end to mark the end of the array
    fields[count].label = NULL;
    fields[count].value = NULL;
}

void ve_data_data_type(){
	
}
