#include <string.h>
#include <stdio.h>
#include <ve_direct.h>
#include <stdbool.h>

ve_direct_data_t g_ve_direct_channels[VE_DIRECT_CH_MAX];

// Helper function to convert a string to ve_direct_data_base_type_t (uint32_t)
ve_direct_data_base_type_t convert_to_uint32(const char *str) {
    return (ve_direct_data_base_type_t)strtoul(str, NULL, 0);
}
// Define a macro to map a field string to its corresponding structure member and break on match
#define MAP_FIELD(field, struct_ptr, value)           \
    if (strcmp(label, #field) == 0) {                 \
        struct_ptr.field = convert_to_uint32(value); \
        break;                                        \
    }

// Define a macro to parse fields using the MAP_FIELD macro inside a do-while loop
#define PARSE_FIELD(struct_ptr, label, value)          \
    do {                                               \
        MAP_FIELD(V, struct_ptr, value)                \
        MAP_FIELD(VS, struct_ptr, value)               \
        MAP_FIELD(I, struct_ptr, value)                \
        MAP_FIELD(P, struct_ptr, value)                \
        MAP_FIELD(CE, struct_ptr, value)               \
        MAP_FIELD(SOC, struct_ptr, value)              \
        MAP_FIELD(TTG, struct_ptr, value)              \
        MAP_FIELD(H1, struct_ptr, value)               \
        MAP_FIELD(H2, struct_ptr, value)               \
        MAP_FIELD(H3, struct_ptr, value)               \
        MAP_FIELD(H4, struct_ptr, value)               \
        MAP_FIELD(H5, struct_ptr, value)               \
        MAP_FIELD(H6, struct_ptr, value)               \
        MAP_FIELD(H7, struct_ptr, value)               \
        MAP_FIELD(H8, struct_ptr, value)               \
        MAP_FIELD(H9, struct_ptr, value)               \
        MAP_FIELD(H10, struct_ptr, value)              \
        MAP_FIELD(H11, struct_ptr, value)              \
        MAP_FIELD(H12, struct_ptr, value)              \
        MAP_FIELD(H13, struct_ptr, value)              \
        MAP_FIELD(H14, struct_ptr, value)              \
        MAP_FIELD(H15, struct_ptr, value)              \
        MAP_FIELD(H16, struct_ptr, value)              \
        MAP_FIELD(H17, struct_ptr, value)              \
        MAP_FIELD(H18, struct_ptr, value)              \
        MAP_FIELD(H19, struct_ptr, value)              \
        MAP_FIELD(H20, struct_ptr, value)              \
        MAP_FIELD(H21, struct_ptr, value)              \
        MAP_FIELD(H22, struct_ptr, value)              \
        MAP_FIELD(H23, struct_ptr, value)              \
		MAP_FIELD(ERR, struct_ptr, value)              \
		MAP_FIELD(PID, struct_ptr, value)              \
        MAP_FIELD(CS, struct_ptr, value)               \
        MAP_FIELD(FW, struct_ptr, value)               \
        MAP_FIELD(FWE, struct_ptr, value)              \
        MAP_FIELD(SER, struct_ptr, value)              \
        MAP_FIELD(HSDS, struct_ptr, value)             \
        MAP_FIELD(MODE, struct_ptr, value)             \
        MAP_FIELD(AC_OUT_V, struct_ptr, value)         \
        MAP_FIELD(AC_OUT_I, struct_ptr, value)         \
        MAP_FIELD(AC_OUT_S, struct_ptr, value)         \
        MAP_FIELD(MPPT, struct_ptr, value)             \
        MAP_FIELD(MON, struct_ptr, value)              \
        MAP_FIELD(DC_IN_V, struct_ptr, value)          \
        MAP_FIELD(DC_IN_I, struct_ptr, value)          \
        MAP_FIELD(DC_IN_P, struct_ptr, value)          \
        /* Add other fields as needed */               \
    } while (0)

int32_t convertToInt(char* value){
    return atoi(value);
}

bool compareLabel(const char *fieldLabel, const char *targetLabel) {
    return (strcmp(fieldLabel, targetLabel) == 0);
}

void parse_vedirect_data(data_t *src, ve_direct_data_t *dest) {
    for (int i = 0; i < src->field_count; i++) {
        field_t *field = &src->fields[i];
        
        if (compareLabel(field->label, "V")) {
            dest->label.V = convertToInt(field->value);  // mV Main or channel 1 (battery) voltage
        } else if (compareLabel(field->label, "V2")) {
            dest->label.V2 = convertToInt(field->value); // mV Channel 2 (battery) voltage
        } else if (compareLabel(field->label, "V3")) {
            dest->label.V3 = convertToInt(field->value); // mV Channel 3 (battery) voltage
        } else if (compareLabel(field->label, "VS")) {
            dest->label.VS = convertToInt(field->value); // mV Auxiliary (starter) voltage
        } else if (compareLabel(field->label, "VM")) {
            dest->label.VM = convertToInt(field->value); // mV Mid-point voltage of the battery bank
        } else if (compareLabel(field->label, "VPV")) {
            dest->label.VPV = convertToInt(field->value); // mV Panel voltage
        } else if (compareLabel(field->label, "AC_OUT_V")) {
            dest->label.AC_OUT_V = convertToInt(field->value); // 0.01 V AC output voltage
        } else if (compareLabel(field->label, "I")) {
            dest->label.I = convertToInt(field->value);  // mA Main or channel 1 battery current
        } else if (compareLabel(field->label, "I2")) {
            dest->label.I2 = convertToInt(field->value); // mA Channel 2 battery current
        } else if (compareLabel(field->label, "I3")) {
            dest->label.I3 = convertToInt(field->value); // mA Channel 3 battery current
        } else if (compareLabel(field->label, "IL")) {
            dest->label.IL = convertToInt(field->value); // mA Load current
        } else if (compareLabel(field->label, "DC_IN_I")) {
            dest->label.DC_IN_I = convertToInt(field->value);  // 0.1 A DC input current
        } else if (compareLabel(field->label, "P")) {
            dest->label.P = convertToInt(field->value);  // W Instantaneous power
        } else if (compareLabel(field->label, "SOC")) {
            dest->label.SOC = convertToInt(field->value); // ‰ State-of-charge
        } else if (compareLabel(field->label, "TTG")) {
            dest->label.TTG = convertToInt(field->value); // Minutes Time-to-go
        } else if (compareLabel(field->label, "H1")) {
            dest->label.H1 = convertToInt(field->value);  // mAh Depth of the deepest discharge
        } else if (compareLabel(field->label, "H2")) {
            dest->label.H2 = convertToInt(field->value);  // mAh Depth of the last discharge
        } else if (compareLabel(field->label, "H7")) {
            dest->label.H7 = convertToInt(field->value);  // mV Minimum main (battery) voltage
        } else if (compareLabel(field->label, "H8")) {
            dest->label.H8 = convertToInt(field->value);  // mV Maximum main (battery) voltage
        } else if (compareLabel(field->label, "ERR")) {
            dest->label.ERR = convertToInt(field->value);  // Error code
        } else if (compareLabel(field->label, "CS")) {
            dest->label.CS = convertToInt(field->value);   // State of operation
        } else if (compareLabel(field->label, "PID")) {
            dest->label.PID = (ve_direct_pid_t)strtol(field->value, NULL, 0);  // Product ID
        } else if (compareLabel(field->label, "SER")) {
            dest->label.SER = convertToInt(field->value);  // Serial number
        } else if (compareLabel(field->label, "HSDS")) {
            dest->label.HSDS = convertToInt(field->value); // Day sequence number (0..364)
        } else if (compareLabel(field->label, "MODE")) {
            dest->label.MODE = convertToInt(field->value); // Device mode
        } else if (compareLabel(field->label, "AC_OUT_I")) {
            dest->label.AC_OUT_I = convertToInt(field->value); // 0.1 A AC output current
        } else if (compareLabel(field->label, "AC_OUT_S")) {
            dest->label.AC_OUT_S = convertToInt(field->value); // VA AC output apparent power
        } else if (compareLabel(field->label, "MPPT")) {
            dest->label.MPPT = convertToInt(field->value); // Tracker operation mode
        } else if (compareLabel(field->label, "MON")) {
            dest->label.MON = convertToInt(field->value);  // DC monitor mode
        } else if (compareLabel(field->label, "DC_IN_V")) {
            dest->label.DC_IN_V = convertToInt(field->value);  // 0.01 V DC input voltage
        } else if (compareLabel(field->label, "DC_IN_P")) {
            dest->label.DC_IN_P = convertToInt(field->value);  // 1 W DC input power
        } else if (compareLabel(field->label, "WARN")) {
            strncpy(dest->label.WARN, field->value, sizeof(dest->label.WARN)); // Warning reason (string)
        }else if (compareLabel(field->label, "AR")) {
            strncpy(dest->label.AR, field->value, sizeof(dest->label.AR)); // Warning reason (string)
        }else if (compareLabel(field->label, "OR")) {
            strncpy(dest->label.OR, field->value, sizeof(dest->label.OR)); // Warning reason (string)
        }
    }
}

data_t ve_data;

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
		char *value = tab_pos + 1; //+1 to skip tab

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
