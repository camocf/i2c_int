/*************************************************************************/
/*  i2c_int.h for i2c_int Library                                        */
/*************************************************************************/
/* Copyright (c) Cameron Fielden                                         */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#ifndef I2C_INT_H
#define I2C_INT_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

typedef struct i2c_address_t
{
    uint8_t address : 7; // I2C address of the slave device
    uint8_t operation : 1;   // Read/Write bit (0 = WRITE, 1 = READ)
} i2c_address_t;

typedef struct i2c_communication_t
{
    i2c_address_t address; // I2C address of the slave device
    uint8_t *data;    // Data to be transmitted or received
    uint8_t length; // Length of the data
} i2c_communication_t;

#define TRANSMIT 0
#define RECEIVE 1
#define WRITE 0
#define READ 1

//Status Codes in the TWSR register reside in the upper 5 bits
#define I2C_STATUS_CODE_MASK 0xF8
//Prescaler bits in TWSR register reside in the lower 2 bits
#define I2C_PRESCALER_MASK 0x03
//Master Transmit Status Codes
#define I2C_START_TRANSMITTED 0x08
#define I2C_REPEATED_START_TRANSMITTED 0x10
#define I2C_WRITE_ADDRESS_ACK_RECEIVED 0x18
#define I2C_WRITE_ADDRESS_NACK_RECEIVED 0x20
#define I2C_WRITE_DATA_ACK_RECEIVED 0x28
#define I2C_WRITE_DATA_NACK_RECEIVED 0x30
#define I2C_ARBITRATION_LOST 0x38
#define I2C_READ_ADDRESS_ACK_RECEIVED 0x40
#define I2C_READ_ADDRESS_NACK_RECIEVED 0x48
#define I2C_READ_DATA_ACK_RECEIVED 0x50
#define I2C_READ_DATA_NACK_RECEIVED 0x58

#define TRANSMISSION_IDLE     100
#define TRANSMISSION_IN_PROG  101
#define TRANSMISSION_COMPLETE 102 
#define TRANSMISSION_FAILED   103

void i2c_uninit(void);
void i2c_master_init(i2c_communication_t *i2c_comm);
void i2c_master_start_transmission(void);
uint8_t i2c_get_transmission_status(void);


#endif // I2C_INT_H