#ifndef PARSER_H
#define PARSER_H

#include <stdint.h>

#define MAX_FIELDS 22       // Maximum number of fields in a block
#define LABEL_SIZE 9        // Buffer size for field label (8 characters + null terminator)
#define VALUE_SIZE 33       // Buffer size for field value (32 characters + null terminator)

typedef enum {
    CHECKSUM_OK,
	CHECKSUM_FAIL,
} DATA_STATE;

typedef enum {
    VOLTAGE, //values in voltage, mV
    CURRENT, //values in amperes, mA
    POWER, //values in watts, W
    TEMPERATURE, //degree Celsius
    CURRENT_ENERGY, //mAh
    PERCENTAGE, 
    TIME,
    POWER_ENERGY //kWh
} DATA_TYPE;


typedef struct {
    char *label;
    char *value;
} vedirect_field_t;

typedef struct {
    vedirect_field_t fields[MAX_FIELDS];
    uint8_t field_count;    // Number of fields currently stored
} vedirect_data_t;


extern vedirect_data_t ve_data;
extern DATA_STATE data_state;
extern DATA_TYPE data_type;

extern char *LATEST_PID;

void parse_frame();
void data_set_state(DATA_STATE new_state);
void data_upd_timestamp(void);
DATA_STATE data_get_state(void);

uint8_t calculate_checksum(char *frame, uint16_t size);

#endif // PARSER_H
