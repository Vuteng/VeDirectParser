#include <stdint.h>

#define VE_DIRECT_DATA_ARR_MAX_SIZE 33U
#define MAX_FIELDS 22       // Maximum number of fields in a block
#define LABEL_SIZE 9        // Buffer size for field label (8 characters + null terminator)
#define VALUE_SIZE 33       // Buffer size for field value (32 characters + null terminator)

typedef uint8_t ve_direct_data_string_t[VE_DIRECT_DATA_ARR_MAX_SIZE];





typedef enum {
    CHECKSUM_OK,
	CHECKSUM_FAIL,
} DATA_STATE;

typedef struct {
	 char label[LABEL_SIZE];
	 char value[VALUE_SIZE];
} field_t;

typedef struct {
    field_t fields[MAX_FIELDS];
    uint8_t field_count;    // Number of fields currently stored
} data_t;


typedef enum {
    VE_DIRECT_ERR_NO_ERROR                          = 0,
    VE_DIRECT_ERR_BATTERY_VOLTAGE_TOO_HIGH          = 2,
    VE_DIRECT_ERR_CHARGER_TEMPERATURE_TOO_HIGH      = 17,
    VE_DIRECT_ERR_CHARGER_OVER_CURRENT              = 18,
    VE_DIRECT_ERR_CHARGER_CURRENT_REVERSED          = 19,
    VE_DIRECT_ERR_BULK_TIME_LIMIT_EXCEEDED          = 20,
    VE_DIRECT_ERR_CURRENT_SENSOR_ISSUE              = 21,
    VE_DIRECT_ERR_TERMINALS_OVERHEATED              = 26,
    VE_DIRECT_ERR_CONVERTER_ISSUE                   = 28,
    VE_DIRECT_ERR_INPUT_VOLTAGE_TOO_HIGH            = 33,
    VE_DIRECT_ERR_INPUT_CURRENT_TOO_HIGH            = 34,
    VE_DIRECT_ERR_INPUT_SHUTDOWN_BATTERY_VOLTAGE    = 38,
    VE_DIRECT_ERR_INPUT_SHUTDOWN_CURRENT_FLOW       = 39,
    VE_DIRECT_ERR_LOST_COMMUNICATION                = 65,
    VE_DIRECT_ERR_SYNC_CHARGING_DEVICE_CONFIG       = 66,
    VE_DIRECT_ERR_BMS_CONNECTION_LOST               = 67,
    VE_DIRECT_ERR_NETWORK_MISCONFIGURED             = 68,
    VE_DIRECT_ERR_FACTORY_CALIBRATION_DATA_LOST     = 116,
    VE_DIRECT_ERR_INVALID_INCOMPATIBLE_FIRMWARE     = 117,
    VE_DIRECT_ERR_USER_SETTINGS_INVALID             = 119
} ve_direct_err_t;

typedef enum {
    VE_DIRECT_CS_OFF                = 0,
    VE_DIRECT_CS_LOW_POWER          = 1,
    VE_DIRECT_CS_FAULT              = 2,
    VE_DIRECT_CS_BULK               = 3,
    VE_DIRECT_CS_ABSORPTION         = 4,
    VE_DIRECT_CS_FLOAT              = 5,
    VE_DIRECT_CS_STORAGE            = 6,
    VE_DIRECT_CS_EQUALIZE_MANUAL    = 7,
    VE_DIRECT_CS_INVERTING          = 9,
    VE_DIRECT_CS_POWER_SUPPLY       = 11,
    VE_DIRECT_CS_STARTING_UP        = 245,
    VE_DIRECT_CS_REPEATED_ABSORPTION= 246,
    VE_DIRECT_CS_AUTO_EQUALIZE      = 247,
    VE_DIRECT_CS_BATTERYSAVE        = 248,
    VE_DIRECT_CS_EXTERNAL_CONTROL   = 252
} ve_direct_cs_t;

typedef enum {
    VE_DIRECT_MODE_CHARGER          = 1,
    VE_DIRECT_MODE_INVERTER         = 2,
    VE_DIRECT_MODE_OFF              = 4,
    VE_DIRECT_MODE_ECO              = 5,
    VE_DIRECT_MODE_HIBERNATE        = 253
} ve_direct_mode_t;

typedef enum {
    VE_DIRECT_MPPT_OFF              = 0,
    VE_DIRECT_MPPT_VOLTAGE_LIMITED  = 1,
    VE_DIRECT_MPPT_TRACKER_ACTIVE   = 2
} ve_direct_mppt_t;

typedef enum {
    VE_DIRECT_MON_SOLAR_CHARGER     = -9,
    VE_DIRECT_MON_WIND_TURBINE      = -8,
    VE_DIRECT_MON_SHAFT_GENERATOR   = -7,
    VE_DIRECT_MON_ALTERNATOR        = -6,
    VE_DIRECT_MON_FUEL_CELL         = -5,
    VE_DIRECT_MON_WATER_GENERATOR   = -4,
    VE_DIRECT_MON_DC_DC_CHARGER     = -3,
    VE_DIRECT_MON_AC_CHARGER        = -2,
    VE_DIRECT_MON_GENERIC_SOURCE    = -1,
    VE_DIRECT_MON_BATTERY_MONITOR   = 0,  // BMV
    VE_DIRECT_MON_GENERIC_LOAD      = 1,
    VE_DIRECT_MON_ELECTRIC_DRIVE    = 2,
    VE_DIRECT_MON_FRIDGE            = 3,
    VE_DIRECT_MON_WATER_PUMP        = 4,
    VE_DIRECT_MON_BILGE_PUMP        = 5,
    VE_DIRECT_MON_DC_SYSTEM         = 6,
    VE_DIRECT_MON_INVERTER          = 7,
    VE_DIRECT_MON_WATER_HEATER      = 8
} ve_direct_mon_t;
typedef enum
{
    VE_DIRECT_STATUS_ACTIVE     = 0,
    VE_DIRECT_STATUS_NOT_ACTIVE = 1,
} ve_direct_status_t;

typedef enum
{
    VE_DIRECT_CH_1   = 0,
    VE_DIRECT_CH_2   = 1,
    VE_DIRECT_CH_3   = 2,
    VE_DIRECT_CH_MAX = 3,
} ve_direct_channels_t;

typedef int32_t ve_direct_data_base_type_t;

typedef enum
{
    VE_DIRECT_PID_BMV_700                              = 0X203,
    VE_DIRECT_PID_BMV_702                              = 0X204,
    VE_DIRECT_PID_BMV_700H                             = 0X205,
    VE_DIRECT_PID_BLUESOLAR_MPPT_70_15                 = 0X0300,
    VE_DIRECT_PID_BLUESOLAR_MPPT_75_50                 = 0XA040,
    VE_DIRECT_PID_BLUESOLAR_MPPT_150_35                = 0XA041,
    VE_DIRECT_PID_BLUESOLAR_MPPT_75_15                 = 0XA042,
    VE_DIRECT_PID_BLUESOLAR_MPPT_100_15                = 0XA043,
    VE_DIRECT_PID_BLUESOLAR_MPPT_100_30                = 0XA044,
    VE_DIRECT_PID_BLUESOLAR_MPPT_100_50                = 0XA045,
    VE_DIRECT_PID_BLUESOLAR_MPPT_150_70                = 0XA046,
    VE_DIRECT_PID_BLUESOLAR_MPPT_150_100               = 0XA047,
    VE_DIRECT_PID_BLUESOLAR_MPPT_100_50_REV2           = 0XA049,
    VE_DIRECT_PID_BLUESOLAR_MPPT_100_30_REV2           = 0XA04A,
    VE_DIRECT_PID_BLUESOLAR_MPPT_150_35_REV2           = 0XA04B,
    VE_DIRECT_PID_BLUESOLAR_MPPT_75_10                 = 0XA04C,
    VE_DIRECT_PID_BLUESOLAR_MPPT_150_45                = 0XA04D,
    VE_DIRECT_PID_BLUESOLAR_MPPT_150_60                = 0XA04E,
    VE_DIRECT_PID_BLUESOLAR_MPPT_150_85                = 0XA04F,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_250_100              = 0XA050,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_150_100              = 0XA051,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_150_85               = 0XA052,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_75_15                = 0XA053,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_75_10                = 0XA054,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_100_15               = 0XA055,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_100_30               = 0XA056,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_100_50               = 0XA057,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_150_35               = 0XA058,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_150_100_REV2         = 0XA059,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_150_85_REV2          = 0XA05A,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_250_70               = 0XA05B,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_250_85               = 0XA05C,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_250_60               = 0XA05D,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_250_45               = 0XA05E,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_100_20               = 0XA05F,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_100_20_48V           = 0XA060,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_150_45               = 0XA061,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_150_60               = 0XA062,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_150_70               = 0XA063,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_250_85_REV2          = 0XA064,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_250_100_REV2         = 0XA065,
    VE_DIRECT_PID_BLUESOLAR_MPPT_100_20                = 0XA066,
    VE_DIRECT_PID_BLUESOLAR_MPPT_100_20_48V            = 0XA067,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_250_60_REV2          = 0XA068,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_250_70_REV2          = 0XA069,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_150_45_REV2          = 0XA06A,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_150_60_REV2          = 0XA06B,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_150_70_REV2          = 0XA06C,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_150_85_REV3          = 0XA06D,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_150_100_REV3         = 0XA06E,
    VE_DIRECT_PID_BLUESOLAR_MPPT_150_45_REV2           = 0XA06F,
    VE_DIRECT_PID_BLUESOLAR_MPPT_150_60_REV2           = 0XA070,
    VE_DIRECT_PID_BLUESOLAR_MPPT_150_70_REV2           = 0XA071,
    VE_DIRECT_PID_BLUESOLAR_MPPT_150_45_REV3           = 0XA072,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_150_45_REV3          = 0XA073,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_75_10_REV2           = 0XA074,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_75_15_REV2           = 0XA075,
    VE_DIRECT_PID_BLUESOLAR_MPPT_100_30_REV3           = 0XA076,
    VE_DIRECT_PID_BLUESOLAR_MPPT_100_50_REV3           = 0XA077,
    VE_DIRECT_PID_BLUESOLAR_MPPT_150_35_REV3           = 0XA078,
    VE_DIRECT_PID_BLUESOLAR_MPPT_75_10_REV2            = 0XA079,
    VE_DIRECT_PID_BLUESOLAR_MPPT_75_15_REV2            = 0XA07A,
    VE_DIRECT_PID_BLUESOLAR_MPPT_100_15_REV2           = 0XA07B,
    VE_DIRECT_PID_BLUESOLAR_MPPT_75_10_REV3            = 0XA07C,
    VE_DIRECT_PID_BLUESOLAR_MPPT_75_15_REV3            = 0XA07D,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_100_30_12V           = 0XA07E,
    VE_DIRECT_PID_ALL_IN_1_SMARTSOLAR_MPPT_75_15_12V   = 0XA07F,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_VE_CAN_150_70        = 0XA102,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_VE_CAN_150_45        = 0XA103,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_VE_CAN_150_60        = 0XA104,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_VE_CAN_150_85        = 0XA105,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_VE_CAN_150_100       = 0XA106,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_VE_CAN_250_45        = 0XA107,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_VE_CAN_250_60        = 0XA108,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_VE_CAN_250_70        = 0XA109,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_VE_CAN_250_85        = 0XA10A,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_VE_CAN_250_100       = 0XA10B,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_VE_CAN_150_70_REV2   = 0XA10C,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_VE_CAN_150_85_REV2   = 0XA10D,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_VE_CAN_150_100_REV2  = 0XA10E,
    VE_DIRECT_PID_BLUESOLAR_MPPT_VE_CAN_150_100        = 0XA10F,
    VE_DIRECT_PID_BLUESOLAR_MPPT_VE_CAN_250_70         = 0XA112,
    VE_DIRECT_PID_BLUESOLAR_MPPT_VE_CAN_250_100        = 0XA113,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_VE_CAN_250_70_REV2   = 0XA114,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_VE_CAN_250_100_REV2  = 0XA115,
    VE_DIRECT_PID_SMARTSOLAR_MPPT_VE_CAN_250_85_REV2   = 0XA116,
    VE_DIRECT_PID_BLUESOLAR_MPPT_VE_CAN_150_100_REV2   = 0XA117,
    VE_DIRECT_PID_PHOENIX_INVERTER_12V_250VA_230V      = 0XA201,
    VE_DIRECT_PID_PHOENIX_INVERTER_24V_250VA_230V      = 0XA202,
    VE_DIRECT_PID_PHOENIX_INVERTER_48V_250VA_230V      = 0XA204,
    VE_DIRECT_PID_PHOENIX_INVERTER_12V_375VA_230V      = 0XA211,
    VE_DIRECT_PID_PHOENIX_INVERTER_24V_375VA_230V      = 0XA212,
    VE_DIRECT_PID_PHOENIX_INVERTER_48V_375VA_230V      = 0XA214,
    VE_DIRECT_PID_PHOENIX_INVERTER_12V_500VA_230V      = 0XA221,
    VE_DIRECT_PID_PHOENIX_INVERTER_24V_500VA_230V      = 0XA222,
    VE_DIRECT_PID_PHOENIX_INVERTER_48V_500VA_230V      = 0XA224,
    VE_DIRECT_PID_PHOENIX_INVERTER_12V_250VA_230V_2    = 0XA231,
    VE_DIRECT_PID_PHOENIX_INVERTER_24V_250VA_230V_2    = 0XA232,
    VE_DIRECT_PID_PHOENIX_INVERTER_48V_250VA_230V_2    = 0XA234,
    VE_DIRECT_PID_PHOENIX_INVERTER_12V_250VA_120V      = 0XA239,
    VE_DIRECT_PID_PHOENIX_INVERTER_24V_250VA_120V      = 0XA23A,
    VE_DIRECT_PID_PHOENIX_INVERTER_48V_250VA_120V      = 0XA23C,
    VE_DIRECT_PID_PHOENIX_INVERTER_12V_375VA_230V_2    = 0XA241,
    VE_DIRECT_PID_PHOENIX_INVERTER_24V_375VA_230V_2    = 0XA242,
    VE_DIRECT_PID_PHOENIX_INVERTER_48V_375VA_230V_2    = 0XA244,
    VE_DIRECT_PID_PHOENIX_INVERTER_12V_375VA_120V      = 0XA249,
    VE_DIRECT_PID_PHOENIX_INVERTER_24V_375VA_120V      = 0XA24A,
    VE_DIRECT_PID_PHOENIX_INVERTER_48V_375VA_120V      = 0XA24C,
    VE_DIRECT_PID_PHOENIX_INVERTER_12V_500VA_230V_2    = 0XA251,
    VE_DIRECT_PID_PHOENIX_INVERTER_24V_500VA_230V_2    = 0XA252,
    VE_DIRECT_PID_PHOENIX_INVERTER_48V_500VA_230V_2    = 0XA254,
    VE_DIRECT_PID_PHOENIX_INVERTER_12V_500VA_120V      = 0XA259,
    VE_DIRECT_PID_PHOENIX_INVERTER_24V_500VA_120V      = 0XA25A,
    VE_DIRECT_PID_PHOENIX_INVERTER_48V_500VA_120V      = 0XA25C,
    VE_DIRECT_PID_PHOENIX_INVERTER_12V_800VA_230V      = 0XA261,
    VE_DIRECT_PID_PHOENIX_INVERTER_24V_800VA_230V      = 0XA262,
    VE_DIRECT_PID_PHOENIX_INVERTER_48V_800VA_230V      = 0XA264,
    VE_DIRECT_PID_PHOENIX_INVERTER_12V_800VA_120V      = 0XA269,
    VE_DIRECT_PID_PHOENIX_INVERTER_24V_800VA_120V      = 0XA26A,
    VE_DIRECT_PID_PHOENIX_INVERTER_48V_800VA_120V      = 0XA26C,
    VE_DIRECT_PID_PHOENIX_INVERTER_12V_1200VA_230V     = 0XA271,
    VE_DIRECT_PID_PHOENIX_INVERTER_24V_1200VA_230V     = 0XA272,
    VE_DIRECT_PID_PHOENIX_INVERTER_48V_1200VA_230V     = 0XA274,
    VE_DIRECT_PID_PHOENIX_INVERTER_12V_1200VA_120V     = 0XA279,
    VE_DIRECT_PID_PHOENIX_INVERTER_24V_1200VA_120V     = 0XA27A,
    VE_DIRECT_PID_PHOENIX_INVERTER_48V_1200VA_120V     = 0XA27C,
    VE_DIRECT_PID_PHOENIX_INVERTER_12V_1600VA_230V     = 0XA281,
    VE_DIRECT_PID_PHOENIX_INVERTER_24V_1600VA_230V     = 0XA282,
    VE_DIRECT_PID_PHOENIX_INVERTER_48V_1600VA_230V     = 0XA284,
    VE_DIRECT_PID_PHOENIX_INVERTER_12V_2000VA_230V     = 0XA291,
    VE_DIRECT_PID_PHOENIX_INVERTER_24V_2000VA_230V     = 0XA292,
    VE_DIRECT_PID_PHOENIX_INVERTER_48V_2000VA_230V     = 0XA294,
    VE_DIRECT_PID_PHOENIX_INVERTER_12V_3000VA_230V     = 0XA2A1,
    VE_DIRECT_PID_PHOENIX_INVERTER_24V_3000VA_230V     = 0XA2A2,
    VE_DIRECT_PID_PHOENIX_INVERTER_48V_3000VA_230V     = 0XA2A4,
    VE_DIRECT_PID_PHOENIX_SMART_IP43_CHARGER_12_50_1_1 = 0XA340,
    VE_DIRECT_PID_PHOENIX_SMART_IP43_CHARGER_12_50_3   = 0XA341,
    VE_DIRECT_PID_PHOENIX_SMART_IP43_CHARGER_24_25_1_1 = 0XA342,
    VE_DIRECT_PID_PHOENIX_SMART_IP43_CHARGER_24_25_3   = 0XA343,
    VE_DIRECT_PID_PHOENIX_SMART_IP43_CHARGER_12_30_1_1 = 0XA344,
    VE_DIRECT_PID_PHOENIX_SMART_IP43_CHARGER_12_30_3   = 0XA345,
    VE_DIRECT_PID_PHOENIX_SMART_IP43_CHARGER_24_16_1_1 = 0XA346,
    VE_DIRECT_PID_PHOENIX_SMART_IP43_CHARGER_24_16_3   = 0XA347,
    VE_DIRECT_PID_BMV_712_SMART                        = 0XA381,
    VE_DIRECT_PID_BMV_710H_SMART                       = 0XA382,
    VE_DIRECT_PID_BMV_712_SMART_REV2                   = 0XA383,
    VE_DIRECT_PID_SMARTSHUNT_500A_50MV                 = 0XA389,
    VE_DIRECT_PID_SMARTSHUNT_1000A_50MV                = 0XA38A,
    VE_DIRECT_PID_SMARTSHUNT_2000A_50MV                = 0XA38B,
    VE_DIRECT_PID_SMART_BUCKBOOST_12V_12V_50A          = 0XA3F0

} ve_direct_pid_t;

typedef struct
{
    ve_direct_status_t status;

    struct
    {
        ve_direct_data_base_type_t V;     // mV Main or channel 1 (battery) voltage
        ve_direct_data_base_type_t V2;    // mV Channel 2 (battery) voltage
        ve_direct_data_base_type_t V3;    // mV Channel 3 (battery) voltage
        ve_direct_data_base_type_t VS;    // mV Auxiliary (starter) voltage
        ve_direct_data_base_type_t VM;    // mV Mid-point voltage of the battery bank
        ve_direct_data_base_type_t DM;    // ‰ Mid-point deviation of the battery bank
        ve_direct_data_base_type_t VPV;   // mV Panel voltage
        ve_direct_data_base_type_t PPV;   // W Panel power
        ve_direct_data_base_type_t I;     // mA Main or channel 1 battery current
        ve_direct_data_base_type_t I2;    // mA Channel 2 battery current
        ve_direct_data_base_type_t I3;    // mA Channel 3 battery current
        ve_direct_data_base_type_t IL;    // mA Load current
        ve_direct_data_base_type_t LOAD;  // Load output state (ON/OFF)
        ve_direct_data_base_type_t T;     // °C Battery temperature
        ve_direct_data_base_type_t P;     // W Instantaneous power
        ve_direct_data_base_type_t CE;    // mAh Consumed Amp Hours
        ve_direct_data_base_type_t SOC;   // ‰ State-of-charge
        ve_direct_data_base_type_t TTG;   // Minutes Time-to-go
        ve_direct_data_base_type_t Alarm; // Alarm condition active
        ve_direct_data_base_type_t Relay; // Relay state
        ve_direct_data_string_t    AR;    // Alarm reason
        ve_direct_data_string_t    OR;    // Off reason
        ve_direct_data_base_type_t H1;    // mAh Depth of the deepest discharge
        ve_direct_data_base_type_t H2;    // mAh Depth of the last discharge
        ve_direct_data_base_type_t H3;    // mAh Depth of the average discharge
        ve_direct_data_base_type_t H4;    // Number of charge cycles
        ve_direct_data_base_type_t H5;    // Number of full discharges
        ve_direct_data_base_type_t H6;    // mAh Cumulative Amp Hours drawn
        ve_direct_data_base_type_t H7;    // mV Minimum main (battery) voltage
        ve_direct_data_base_type_t H8;    // mV Maximum main (battery) voltage
        ve_direct_data_base_type_t H9;    // Seconds Number of seconds since last full charge
        ve_direct_data_base_type_t H10;   // Number of automatic synchronizations
        ve_direct_data_base_type_t H11;   // Number of low main voltage alarms
        ve_direct_data_base_type_t H12;   // Number of high main voltage alarms
        ve_direct_data_base_type_t H13;   // Number of low auxiliary voltage alarms
        ve_direct_data_base_type_t H14;   // Number of high auxiliary voltage alarms
        ve_direct_data_base_type_t H15;   // mV Minimum auxiliary (battery) voltage
        ve_direct_data_base_type_t H16;   // mV Maximum auxiliary (battery) voltage
        ve_direct_data_base_type_t
            H17; // 0.01 kWh Amount of discharged energy (BMV) / Amount of produced energy (DC monitor)
        ve_direct_data_base_type_t
            H18; // 0.01 kWh Amount of charged energy (BMV) / Amount of consumed energy (DC monitor)
        ve_direct_data_base_type_t H19;      // 0.01 kWh Yield total (user resettable counter)
        ve_direct_data_base_type_t H20;      // 0.01 kWh Yield today
        ve_direct_data_base_type_t H21;      // W Maximum power today
        ve_direct_data_base_type_t H22;      // 0.01 kWh Yield yesterday
        ve_direct_data_base_type_t H23;      // W Maximum power yesterday
        ve_direct_err_t ERR;      // Error code
        ve_direct_cs_t CS;       // State of operation
        ve_direct_data_base_type_t BMV;      // Model description (deprecated)
        ve_direct_data_base_type_t FW;       // Firmware version (16 bit)
        ve_direct_data_base_type_t FWE;      // Firmware version (24 bit)
        ve_direct_pid_t            PID;      // Product ID
        ve_direct_data_base_type_t SER;      // Serial number
        ve_direct_data_base_type_t HSDS;     // Day sequence number (0..364)
        ve_direct_mon_t MODE;     // Device mode
        ve_direct_data_base_type_t AC_OUT_V; // 0.01 V AC output voltage
        ve_direct_data_base_type_t AC_OUT_I; // 0.1 A AC output current
        ve_direct_data_base_type_t AC_OUT_S; // VA AC output apparent power
        ve_direct_data_string_t    WARN;     // Warning reason
        ve_direct_data_base_type_t MPPT;     // Tracker operation mode
        ve_direct_data_base_type_t MON;      // DC monitor mode
        ve_direct_data_base_type_t DC_IN_V;  // 0.01 V DC input voltage
        ve_direct_data_base_type_t DC_IN_I;  // 0.1 A DC input current
        ve_direct_data_base_type_t DC_IN_P;  // 1 W DC input power

    } label;
} ve_direct_data_t;

extern data_t ve_data;
extern DATA_STATE data_state;

extern char *LATEST_PID;

void parse_frame();
void data_set_state(DATA_STATE new_state);
DATA_STATE data_get_state(void);

uint8_t calculate_checksum(char *frame, uint16_t size);
