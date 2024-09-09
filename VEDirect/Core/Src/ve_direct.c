#include "parser.h"
#include <string.h>
#include <stdio.h>

// Helper function to convert a string to ve_direct_data_base_type_t (uint32_t)
ve_direct_data_base_type_t convert_to_uint32(const char *str) {
    return (ve_direct_data_base_type_t)strtoul(str, NULL, 0);
}

#define MAP_FIELD(field, struct_ptr, value)                        \
    if (strcmp(ve_data->fields[i].label, #field) == 0) {           \
        struct_ptr->label.field = convert_to_uint32(value);        \
    }

#define PARSE_FIELD(field, struct_ptr, ve_data, value)             \
    MAP_FIELD(field, struct_ptr, value)


// Function to map fields into the structure using macros
void map_fields_to_structure(ve_data_t *ve_data, ve_direct_data_t *ve_direct_data) {
    for (int i = 0; i < ve_data->field_count; i++) {
        PARSE_FIELD(PID, ve_direct_data, ve_data, ve_data->fields[i].value);
        PARSE_FIELD(V, ve_direct_data, ve_data, ve_data->fields[i].value);
        PARSE_FIELD(VS, ve_direct_data, ve_data, ve_data->fields[i].value);
        PARSE_FIELD(I, ve_direct_data, ve_data, ve_data->fields[i].value);
        PARSE_FIELD(P, ve_direct_data, ve_data, ve_data->fields[i].value);
        PARSE_FIELD(CE, ve_direct_data, ve_data, ve_data->fields[i].value);
        PARSE_FIELD(SOC, ve_direct_data, ve_data, ve_data->fields[i].value);
        PARSE_FIELD(TTG, ve_direct_data, ve_data, ve_data->fields[i].value);
        PARSE_FIELD(H1, ve_direct_data, ve_data, ve_data->fields[i].value);
        PARSE_FIELD(H2, ve_direct_data, ve_data, ve_data->fields[i].value);
        PARSE_FIELD(H3, ve_direct_data, ve_data, ve_data->fields[i].value);
        PARSE_FIELD(H4, ve_direct_data, ve_data, ve_data->fields[i].value);
        PARSE_FIELD(H5, ve_direct_data, ve_data, ve_data->fields[i].value);
        PARSE_FIELD(H6, ve_direct_data, ve_data, ve_data->fields[i].value);
        PARSE_FIELD(H7, ve_direct_data, ve_data, ve_data->fields[i].value);
        PARSE_FIELD(H8, ve_direct_data, ve_data, ve_data->fields[i].value);
        PARSE_FIELD(H9, ve_direct_data, ve_data, ve_data->fields[i].value);
        PARSE_FIELD(H10, ve_direct_data, ve_data, ve_data->fields[i].value);
        PARSE_FIELD(H11, ve_direct_data, ve_data, ve_data->fields[i].value);
        PARSE_FIELD(H12, ve_direct_data, ve_data, ve_data->fields[i].value);
        PARSE_FIELD(H13, ve_direct_data, ve_data, ve_data->fields[i].value);
        PARSE_FIELD(H14, ve_direct_data, ve_data, ve_data->fields[i].value);
        PARSE_FIELD(H15, ve_direct_data, ve_data, ve_data->fields[i].value);
        PARSE_FIELD(H16, ve_direct_data, ve_data, ve_data->fields[i].value);
        PARSE_FIELD(H17, ve_direct_data, ve_data, ve_data->fields[i].value);
        PARSE_FIELD(H18, ve_direct_data, ve_data, ve_data->fields[i].value);
        PARSE_FIELD(H19, ve_direct_data, ve_data, ve_data->fields[i].value);
        PARSE_FIELD(H20, ve_direct_data, ve_data, ve_data->fields[i].value);
        PARSE_FIELD(H21, ve_direct_data, ve_data, ve_data->fields[i].value);
        PARSE_FIELD(H22, ve_direct_data, ve_data, ve_data->fields[i].value);
        PARSE_FIELD(H23, ve_direct_data, ve_data, ve_data->fields[i].value);
        PARSE_FIELD(ERR, ve_direct_data, ve_data, ve_data->fields[i].value);
        PARSE_FIELD(CS, ve_direct_data, ve_data, ve_data->fields[i].value);
        PARSE_FIELD(FW, ve_direct_data, ve_data, ve_data->fields[i].value);
        PARSE_FIELD(FWE, ve_direct_data, ve_data, ve_data->fields[i].value);
        PARSE_FIELD(SER, ve_direct_data, ve_data, ve_data->fields[i].value);
        PARSE_FIELD(HSDS, ve_direct_data, ve_data, ve_data->fields[i].value);
        PARSE_FIELD(MODE, ve_direct_data, ve_data, ve_data->fields[i].value);
        PARSE_FIELD(AC_OUT_V, ve_direct_data, ve_data, ve_data->fields[i].value);
        PARSE_FIELD(AC_OUT_I, ve_direct_data, ve_data, ve_data->fields[i].value);
        PARSE_FIELD(AC_OUT_S, ve_direct_data, ve_data, ve_data->fields[i].value);
        PARSE_FIELD(MPPT, ve_direct_data, ve_data, ve_data->fields[i].value);
        PARSE_FIELD(MON, ve_direct_data, ve_data, ve_data->fields[i].value);
        PARSE_FIELD(DC_IN_V, ve_direct_data, ve_data, ve_data->fields[i].value);
        PARSE_FIELD(DC_IN_I, ve_direct_data, ve_data, ve_data->fields[i].value);
        PARSE_FIELD(DC_IN_P, ve_direct_data, ve_data, ve_data->fields[i].value);
    }
}
