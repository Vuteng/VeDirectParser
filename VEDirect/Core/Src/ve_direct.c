#include <parser.h>
#include <string.h>
#include <stdio.h>
#include <ve_direct.h>

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


// Function to map fields into the structure using macros
void map_fields_to_structure(vedirect_data_t ve_data, ve_direct_data_t ve_direct_data) {
    for (int i = 0; i < ve_data.field_count; i++) {
        const char *label = ve_data.fields[i].label;
        const char *value = ve_data.fields[i].value;
        PARSE_FIELD(ve_direct_data.label, label, value);
    }
}
