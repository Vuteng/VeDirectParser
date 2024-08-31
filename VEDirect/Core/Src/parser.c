#include "parser.h"
#include <string.h>
#include <stdio.h>

vedirect_data_t ve_data;

void parse_frame(char *frame)
{
    // Initialize field count
    ve_data.field_count = 0;

    char *line_start = frame;
    char *line_end;

    // Loop over each line, separated by \r\n
    while ((line_end = strstr(line_start, "\r\n")) != NULL && ve_data.field_count < MAX_FIELDS)
    {
        // Temporarily terminate the line
        *line_end = '\0';

        // Split the line into label and value based on the tab character
        char *label = line_start;
        char *value = strchr(line_start, '\t');

        if (value)
        {
            // Move the pointer past the tab character
            *value = '\0';
            value++;

            // Copy label and value to the ve_data structure
            strncpy(ve_data.fields[ve_data.field_count].label, label, LABEL_SIZE - 1);
            ve_data.fields[ve_data.field_count].label[LABEL_SIZE - 1] = '\0'; // Ensure null termination

            strncpy(ve_data.fields[ve_data.field_count].value, value, VALUE_SIZE - 1);
            ve_data.fields[ve_data.field_count].value[VALUE_SIZE - 1] = '\0'; // Ensure null termination

            ve_data.field_count++;
        }

        // Restore the '\r\n' characters and move to the next line
        *line_end = '\r';
        line_start = line_end + 2; // Move to the character after the '\r\n'
    }

    // Handle the last line if there's no trailing \r\n
    if (*line_start != '\0' && ve_data.field_count < MAX_FIELDS)
    {
        char *label = line_start;
        char *value = strchr(line_start, '\t');

        if (value)
        {
            *value = '\0';
            value++;

            strncpy(ve_data.fields[ve_data.field_count].label, label, LABEL_SIZE - 1);
            ve_data.fields[ve_data.field_count].label[LABEL_SIZE - 1] = '\0'; // Ensure null termination

            strncpy(ve_data.fields[ve_data.field_count].value, value, VALUE_SIZE - 1);
            ve_data.fields[ve_data.field_count].value[VALUE_SIZE - 1] = '\0'; // Ensure null termination

            ve_data.field_count++;
        }
    }
}