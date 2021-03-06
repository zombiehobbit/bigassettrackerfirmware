/* 
 * File:   sparkfun_lte.h
 * Author: dmanhall@gmail.com
 *
 * Created on 3/8/2019 1:30:10 AM UTC
 * "Created in MPLAB Xpress"
 *
 *  Header file for the sparkfun LTE board
 *  Anytime line numbers referd to are in the git retpo
 *  See: https://github.com/sparkfun/SparkFun_LTE_Shield_Arduino_Library/blob/master/src/SparkFun_LTE_Shield_Arduino_Library.h
 *
 */

#ifndef SPARKFUN_LTE_H
#define	SPARKFUN_LTE_H

#include <string.h>
#include <stdbool.h>
#include <stdint.h> // some of the structs need this.  Don't remove
#include <xc.h> // special functions for the pic16f
//#include <stdio.h> // for sprintf
#include "usartserial.h"
//#include "app.h"

#define LTE_SHIELD_POWER_PIN 5
#define LTE_SHIELD_RESET_PIN 6

// states for the LTE start function
#define LTE_RESET 1
#define LTE_AUTOBAUD 2
#define LTE_CONFIGURE 3

// moble network operators from line 57
// pretty sure these are used to set things
#define MNO_INVALID -1
#define MNO_SW_DEFAULT 0
#define MNO_SIM_ICCD 1
#define MNO_ATT 2
#define MNO_VERIZON 3
#define MNO_TELSTRA 4
#define MNO_TMO 5
#define MNO_CT 6

// LTE error codes, see line 68 
typedef char LTE_Shield_error_t;
#define LTE_SHIELD_ERROR_INVALID -1
#define LTE_SHIELD_ERROR_SUCCESS 0
#define LTE_SHIELD_ERROR_OUT_OF_MEMORY 1
#define LTE_SHIELD_ERROR_TIMEOUT 2
#define LTE_SHIELD_ERROR_UNEXPECTED_PARAM 3
#define LTE_SHIELD_ERROR_UNEXPECTED_RESPONSE 4
#define LTE_SHIELD_ERROR_NO_RESPONSE 5
#define LTE_SHIELD_ERROR_DEREGISTERED 6

// LTE sheild registration status, see line 92
typedef char LTE_Shield_registration_status_t;
#define LTE_SHIELD_REGISTRATION_INVALID -1
#define LTE_SHIELD_REGISTRATION_NOT_REGISTERED 0
#define LTE_SHIELD_REGISTRATION_HOME 1
#define LTE_SHIELD_REGISTRATION_SEARCHING 2
#define LTE_SHIELD_REGISTRATION_DENIED 3
#define LTE_SHIELD_REGISTRATION_UNKNOWN 4
#define LTE_SHIELD_REGISTRATION_ROAMING 5
#define LTE_SHIELD_REGISTRATION_HOME_SMS_ONLY 6
#define LTE_SHIELD_REGISTRATION_ROAMING_SMS_ONLY 7
#define LTE_SHIELD_REGISTRATION_HOME_CSFB_NOT_PREFERRED 8
#define LTE_SHIELD_REGISTRATION_ROAMING_CSFB_NOT_PREFERRED 9

// LTE sheild codes 
//typedef char LTE_Shield_error_t;
#define LTE_SHIELD_STANDARD_RESPONSE_TIMEOUT 1000
#define LTE_SHIELD_SET_BAUD_TIMEOUT 500
#define LTE_SHIELD_POWER_PULSE_PERIOD 3200
#define LTE_RESET_PULSE_PERIOD 10000
#define LTE_SHIELD_IP_CONNECT_TIMEOUT 60000
#define LTE_SHIELD_POLL_DELAY 1
#define LTE_SHIELD_SOCKET_WRITE_TIMEOUT 10000
#define LTE_SHIELD_INIT_TIMEOUT 60000

// macros for selecting the TCP/UDP network protocol
typedef char lte_shield_socket_protocol_t;
#define LTE_SHIELD_TCP 6
#define LTE_SHEILD_UDP 17

// LTE sheild message format
typedef char lte_shield_message_format_t;
#define LTE_SHIELD_MESSAGE_FORMAT_PDU 0
#define LTE_SHIELD_MESSAGE_FORMAT_TEXT 1

// LTE sheild type for GPIO 
typedef unsigned char LTE_Shield_gpio_t;
#define GPIO1 16
#define GPIO2 23
#define GPIO3 24
#define GPIO4 25
#define GPIO5 42
#define GPIO6 19

// LTE GPIO pin modes
typedef char LTE_Shield_gpio_mode_t;
#define GPIO_MODE_INVALID -1
#define GPIO_OUTPUT 0
#define GPIO_INPUT 1 
#define NETWORK_STATUS 2
#define GNSS_SUPPLY_ENABLE 3
#define GNSS_DATA_READY 4
#define GNSS_RTC_SHARING 5
#define SIM_CARD_DETECTION 6
#define HEADSET_DETECTION 7
#define GSM_TX_BURST_INDICATION 8
#define MODULE_OPERATING_STATUS_INDICATION 9
#define MODULE_FUNCTIONALITY_STATUS_INDICATION 10
#define I2S_DIGITAL_AUDIO_INTERFACE 11
#define SPI_SERIAL_INTERFACE 12
#define MASTER_CLOCK_GENRATION 13
#define UART_INTERFACE 14
#define WIFI_ENABLE 15
#define RING_INDICATION 16
#define LAST_GASP_ENABLE 17
#define PAD_DISABLED 255

// macros for commands
#define LTE_SHIELD_STANDARD_RESPONSE_TIMEOUT 1000
#define LTE_SHIELD_SET_BAUD_TIMEOUT 500
#define LTE_SHIELD_POWER_PULSE_PERIOD 3200
#define LTE_RESET_PULSE_PERIOD 10000
#define LTE_SHIELD_IP_CONNECT_TIMEOUT 60000
#define LTE_SHIELD_POLL_DELAY 1
#define LTE_SHIELD_SOCKET_WRITE_TIMEOUT 10000

// ## Suported AT Commands
// ### General
//const char LTE_SHIELD_COMMAND_AT[] = "AT";         // AT "Test"
//const char LTE_SHIELD_COMMAND_ECHO[] = "E";        // Local Echo
//const char LTE_SHIELD_COMMAND_IMEI[] = "+CGSN";    // IMEI identification
//const char LTE_SHIELD_COMMAND_IMSI[] = "+CIMI";    // IMSI identification
//const char LTE_SHIELD_COMMAND_CCID[] = "+CCID";    // SIM CCID
#define LTE_SHIELD_COMMAND_AT "AT"
#define LTE_SHIELD_COMMAND_ECHO "E"
#define LTE_SHIELD_COMMAND_IMEI "+CGSN"
#define LTE_SHIELD_COMMAND_IMSI "+CIMI"
#define LTE_SHIELD_COMMAND_CCID "+CCID"
// ### Control and status
//const char LTE_SHIELD_COMMAND_FUNC[] = "+CFUN";    // Functionality (reset, etc.)
//const char LTE_SHIELD_COMMAND_CLOCK[] = "+CCLK";   // Clock
//const char LTE_SHIELD_COMMAND_AUTO_TZ[] = "+CTZU"; // Automatic time zone update
#define LTE_SHIELD_COMMAND_FUNC "+CFUN"
#define LTE_SHIELD_COMMAND_CLOCK "+CCLK"
#define LTE_SHIELD_COMMAND_AUTO_TZ "+CTZU"
// ### Network service
//const char LTE_SHIELD_COMMAND_MNO[] = "+UMNOPROF"; // MNO (mobile network operator) Profile
//const char LTE_SHIELD_SIGNAL_QUALITY[] = "+CSQ";
//const char LTE_SHIELD_REGISTRATION_STATUS[] = "+CREG";
//const char LTE_SHIELD_MESSAGE_PDP_DEF[] = "+CGDCONT";
//const char LTE_SHIELD_MESSAGE_ENTER_PPP[] = "D";
//const char LTE_SHIELD_OPERATOR_SELECTION[] = "+COPS";
#define LTE_SHIELD_COMMAND_MNO "+UMNOPROF"
#define LTE_SHIELD_SIGNAL_QUALITY "+CSQ"
#define LTE_SHIELD_REGISTRATION_STATUS "+CGDCONT"
#define LTE_SHIELD_MESSAGE_ENTER_PPP "D"
#define LTE_SHIELD_OPERATOR_SELECTION "+COPS"
// V24 control and V25ter (UART interface)
//const char LTE_SHIELD_COMMAND_BAUD[] = "+IPR";     // Baud rate
#define LTE_SHIELD_COMMAND_BAUD "+IPR"
// ### GPIO
//const char LTE_SHIELD_COMMAND_GPIO[] = "+UGPIOC";  // GPIO Configuration
#define LTE_SHIELD_COMMAND_GPIO "+UGPIOC"
// ### IP
//const char LTE_SHIELD_CREATE_SOCKET[] = "+USOCR";  // Create a new socket
//const char LTE_SHIELD_CLOSE_SOCKET[] = "+USOCL";   // Close a socket
//const char LTE_SHIELD_CONNECT_SOCKET[] = "+USOCO"; // Connect to server on socket
//const char LTE_SHIELD_WRITE_SOCKET[] = "+USOWR";   // Write data to a socket
//const char LTE_SHIELD_READ_SOCKET[] = "+USORD";    // Read from a socket
//const char LTE_SHIELD_LISTEN_SOCKET[] = "+USOLI";  // Listen for connection on socket
#define LTE_SHIELD_CREATE_SOCKET "+USOCR"
#define LTE_SHIELD_CLOSE_SOCKET "+USOCL"
#define LTE_SHIELD_CONNECT_SOCKET "+USOCO"
#define LTE_SHIELD_WRITE_SOCKET "+USOWR"
#define LTE_SHIELD_READ_SOCKET "+USORD"
#define LTE_SHIELD_LISTEN_SOCKET "+USOLI"
// ### SMS
//const char LTE_SHIELD_MESSAGE_FORMAT[] = "+CMGF";  // Set SMS message format
//const char LTE_SHIELD_SEND_TEXT[] = "+CMGS";       // Send SMS message
#define LTE_SHIELD_MESSAGE_FORMAT "+CMGF"
#define LTE_SHIELD_SEND_TEXT "+CMGS"
// ### GPS
//const char LTE_SHIELD_GPS_POWER[] = "+UGPS";
//const char LTE_SHIELD_GPS_REQUEST_LOCATION[] = "+ULOC";
//const char LTE_SHIELD_GPS_GPRMC[] = "+UGRMC";
#define LTE_SHIELD_GPS_POWER "+UGPS"
#define LTE_SHIELD_GPS_REQUEST_LOCATION "+ULOC"
#define LTE_SHIELD_GPS_GPRMC "+UGRMC"

//const char LTE_SHIELD_RESPONSE_OK[] = "OK\r\n";
#define LTE_SHIELD_RESPONSE_OK "OK\r\n"

// array of supported baud rates for the LTE system
#define NUM_SUPPORTED_BAUD 6
const unsigned long LTE_SHIELD_SUPPORTED_BAUD[NUM_SUPPORTED_BAUD] =
{
    115200,
    9600,
    19200,
    38400,
    57600,
    230400
};



//void bDelay_ms(unsigned int delayms); // moved...

struct DateData {
    uint8_t day;
    uint8_t month;
    unsigned int year;
};

struct TimeData {
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    unsigned int ms;
    uint8_t tzh;
    uint8_t tzm;
};

struct ClockData {
    struct DateData date;
    struct TimeData time;
};

struct PositionData {
    float utc;
    float lat;
    char latDir;
    float lon;
    char lonDir;
    float alt;
    char mode;
    char status;
};

struct SpeedData {
    float speed;
    float track;
    float magVar;
    char magVarDir;
};

struct operator_stats {
    uint8_t stat;
    char *shortOp;
    char *longOp;
    unsigned long numOp;
    uint8_t act;
};

// constents for terminating connections
// CTRL+Z and ESC ASCII codes for SMS message sends
const char ASCII_CTRL_Z = 0x1A;
const char ASCII_ESC = 0x1B;

// headers for LTE functions 

typedef struct
{
    unsigned short baud; // baud rate
    unsigned char powerPin; //...
    unsigned char resetPin;
} LTE_sheild;

// sets the LTE sheild to reseive commands
// returns true if worked, false if it dosnt
bool begin(unsigned short baud_rate); 

// functions defined in line 160 of the gitrepo
// loop polling and polling setup
bool poll();
//LTE_Shield_error_t AT(); // send an AT test command 
//LTE_Shield_error_t sendCommandWithResponse(const char * command, const char * expectedResponse, char * responseDest, unsigned int commandTimeout, bool at);
//LTE_Shield_error_t set_lte_baud(unsigned int baud); // set the desired baud rate on the lte board
void send_command(char *cmd,bool at); // send a command, maybe with an AT
char read_responce(char *data,unsigned int timeout); // read a responce and return the number of bytes returned
// functions for starting up the LTE board
void powerOn(); // run the power function, power on button is RC2, which is physical pin 8
char sendATcmd(char *cmd, char *buffres, bool AT, unsigned int timeout); // option to send an AT command to the LTE board
char set_lte_baud(unsigned long baud);
char set_gpio_mode(LTE_Shield_gpio_t gpio, LTE_Shield_gpio_mode_t mode); // set the GPIO mode
char lte_start(unsigned long desired_baud); 
char autobaud(unsigned long baud); // not implmented yet
char enable_echo(bool echon); // enable/disable the echo functionality.
bool testAT(); // send an AT command to set the baud rate

#endif	/* SPARKFUN_LTE_H */
