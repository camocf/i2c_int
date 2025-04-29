/*************************************************************************/
/*  i2c_int.c for i2c_int Library                                        */
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

#include "i2c_int.h"

static uint8_t i2c_master_address;
static uint8_t *i2c_master_data;
static uint8_t i2c_master_length;
static uint8_t i2c_master_operation;
static uint8_t transmission_status = TRANSMISSION_IDLE;

static void i2c_start()
{
    // Set the TWINT bit to start the I2C communication
    transmission_status = TRANSMISSION_IN_PROG;
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
}

static void i2c_stop()
{
    // Set the TWINT bit to stop the I2C communication
    TWCR = (1 << TWINT) | (1 << TWSTO);
}

static void i2c_set_address()
{
    TWDR = (i2c_master_address | i2c_master_operation); // Set the address and operation (read,write)
    TWCR = (1 << TWINT) | (1 << TWEN);
}

static void i2c_write_data()
{
    static uint8_t data_index = 0;

    if(data_index < i2c_master_length)
    {
        TWDR = *(i2c_master_data + data_index); // Load the data to be transmitted
        data_index++;

        TWCR = (1 << TWINT) | (1 << TWEN);
    }
    else
    {
        transmission_status = TRANSMISSION_COMPLETE;
        i2c_stop();
    }
    
}

static void i2c_read_data()
{
    static uint8_t data_index = 0;

    if(data_index < i2c_master_length)
    {
        *(i2c_master_data + data_index) = TWDR;
        data_index++;
    
        TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    }
    else
    {
        transmission_status = TRANSMISSION_COMPLETE;
        i2c_stop();
    }
}

static void i2c_isr(void)
{
    switch (TWSR & I2C_STATUS_CODE_MASK)
    {
        case I2C_START_TRANSMITTED:
        case I2C_REPEATED_START_TRANSMITTED:
            i2c_set_address();
            break;
        case I2C_WRITE_ADDRESS_ACK_RECEIVED:
        case I2C_WRITE_DATA_ACK_RECEIVED:
            i2c_write_data();
            break;
        case I2C_READ_ADDRESS_ACK_RECEIVED:
        case I2C_READ_DATA_ACK_RECEIVED:
            i2c_read_data();
            break;
        case I2C_WRITE_ADDRESS_NACK_RECEIVED:
        case I2C_WRITE_DATA_NACK_RECEIVED:
        case I2C_ARBITRATION_LOST:
        case I2C_READ_ADDRESS_NACK_RECIEVED:
        case I2C_READ_DATA_NACK_RECEIVED:
            transmission_status = TRANSMISSION_FAILED;
            i2c_stop();
            break;
        default:
            break;
    }
}

void i2c_uninit(void)
{
    // Disable the I2C interface
    TWCR &= ~(1 << TWEN);
    transmission_status = TRANSMISSION_IDLE;
}

void i2c_master_init(i2c_communication_t *i2c_comm)
{
    // Set the I2C clock frequency
    TWSR = 0x00; // Prescaler set to 1
    TWBR = ((F_CPU / 100000) - 16) / (2 * (1 << (TWSR & I2C_PRESCALER_MASK)));

    // Set the I2C address and data
    i2c_master_address = i2c_comm->address.address;
    i2c_master_data = i2c_comm->data;
    i2c_master_length = i2c_comm->length;
    i2c_master_operation = i2c_comm->address.operation;



    // Enable the I2C interface
    TWCR = (1 << TWEN);
}

void i2c_master_start_transmission()
{
    i2c_start();
}

uint8_t i2c_get_transmission_status()
{
    return transmission_status;
}

ISR(TWI_vect)
{
    i2c_isr();
}