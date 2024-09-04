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
void parse_frame(char *frame)
{
	ve_data.field_count = 0; // Reset field count

	char *line_start = frame;
	char *line_end;

	//seperates string into new lines based on \r\n
	while ((line_end = strstr(line_start, "\r\n")) != NULL) {
		*line_end = '\0'; // to know where it ends

		// process data line by line
		char *tab_pos = strstr(line_start, "\t");
		if (tab_pos != NULL) {
			*tab_pos = '\0'; // to know where it ends

		char *label = line_start;
		char *value = tab_pos + 1; //+1 to skip tab;

		if (ve_data.field_count < MAX_FIELDS) {
			strncpy(ve_data.fields[ve_data.field_count].label, label, LABEL_SIZE - 1);
			ve_data.fields[ve_data.field_count].label[LABEL_SIZE - 1] = '\0';

			strncpy(ve_data.fields[ve_data.field_count].value, value, VALUE_SIZE - 1);
			ve_data.fields[ve_data.field_count].value[VALUE_SIZE - 1] = '\0';

			ve_data.field_count++;
			}
		}

		line_start = line_end + 2;
	}
}
