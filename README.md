# i2cbitbang

I2C bit-banging library for embedded microcontrollers. Originally developed for STM32F4, now ported to **LPC1768** with direct register access (no HAL dependencies).

This is a bit-banging implementation of I2C master protocol with support for:
- Multiple I2C port instances (limited by available GPIO pins)
- Clock stretching with configurable timeout
- Multiple bus speeds: 10kHz, 50kHz, 100kHz, 400kHz
- SCCB protocol mode (for cameras like OV7670)
- Open-drain GPIO configuration for proper I2C bus operation

Based on the I2C bit-banging template from [Wikipedia I2C article](https://en.wikipedia.org/wiki/I%C2%B2C).

## Features

- **No HAL dependency**: Uses direct register access for maximum portability
- **LPC1768 support**: Full support for NXP LPC1768 ARM Cortex-M3 microcontroller
- **SysTick-based timing**: Accurate microsecond delays using SysTick timer
- **Open-drain GPIO**: Proper I2C bus configuration with internal pull-ups
- **Multiple instances**: Support for multiple I2C buses on different GPIO pins

## Hardware Requirements

- NXP LPC1768 microcontroller (or compatible LPC17xx series)
- External pull-up resistors recommended (2.2kΩ - 10kΩ) for reliable operation
- GPIO pins configured for open-drain mode

## Compilation

### Using ARM GCC Toolchain

```bash
arm-none-eabi-g++ -mcpu=cortex-m3 -mthumb -c -I. Delay.cpp i2cbitbang.cpp i2cbitbang_driver.cpp -o i2cbitbang.o
```

### Using Keil MDK / ARM Compiler

Add all source files to your project and include the header directory in your include paths.

### Using MBED

This library is compatible with MBED OS. Add the files to your MBED project.

## Configuration

### 1. Edit `i2cbitbang_board.h`

Configure your I2C port instances:

```cpp
// Define I2C instance names
#define I2CBB_OLED   0
#define I2CBB_SENSOR 1

// Set total number of I2C instances
#define NUMBER_OF_I2CBB_INSTANCES 2

// Configure GPIO pins for each instance
#define I2CBB_DECLARE_STRUCTURE() \
    const i2cbbConfig_t i2cbbConfigTable[NUMBER_OF_I2CBB_INSTANCES] = \
    { \
        {LPC_GPIO0, GPIO_PIN_4,     /* SCL for OLED */ \
         LPC_GPIO0, GPIO_PIN_5},    /* SDA for OLED */ \
\
        {LPC_GPIO1, GPIO_PIN_10,    /* SCL for SENSOR */ \
         LPC_GPIO1, GPIO_PIN_11},   /* SDA for SENSOR */ \
    }
```

### 2. Available GPIO Ports

LPC1768 GPIO ports:
- `LPC_GPIO0` - Port 0 (32 pins: P0.0 - P0.31)
- `LPC_GPIO1` - Port 1 (32 pins: P1.0 - P1.31)
- `LPC_GPIO2` - Port 2 (14 pins: P2.0 - P2.13)
- `LPC_GPIO3` - Port 3 (2 pins: P3.25 - P3.26)
- `LPC_GPIO4` - Port 4 (2 pins: P4.28 - P4.29)

GPIO pin masks:
- `GPIO_PIN_0` through `GPIO_PIN_31`

## Usage Example

```cpp
#include "i2cbitbang.h"

// Create I2C instance for OLED display at address 0x3C
i2cbitbang oled(I2CBB_OLED, 0x3C);

// Configure speed (optional, default is 400kHz)
oled.setSpeed(SPEED_100k);

// Write to a register
oled.writeReg(0x00, 0xAE);  // Display OFF command

// Read from a register
uint8_t val = oled.readReg(0x00);

// Write multiple bytes
uint8_t data[] = {0x00, 0x10, 0x40};
oled.writeData(0x00, data, 3);

// Read multiple bytes
uint8_t buffer[8];
oled.readData(0x00, buffer, 8);

// Check for errors
if (oled.getError() != I2CBB_ERROR_NONE) {
    // Handle error
}
```

## Speed Settings

Available speed options:
- `SPEED_10k`  - 10 kHz (for long cables or noisy environments)
- `SPEED_50k`  - 50 kHz
- `SPEED_100k` - 100 kHz (Standard mode)
- `SPEED_400k` - 400 kHz (Fast mode, default)

```cpp
i2cbitbang i2c(I2CBB_OLED, 0x3C);
i2c.setSpeed(SPEED_100k);
```

## SCCB Mode (Camera Interface)

For SCCB protocol (used by OV7670 and similar cameras):

```cpp
i2cbitbang cam(I2CBB_SCCB, 0x42);
cam.setI2CMode(MODE_SCCB);
cam.setAckMode(ACK_IGNORE);  // SCCB doesn't check ACK
```

## Error Handling

After each I2C operation, check for errors:

```cpp
uint32_t err = i2c.getError();

if (err & I2CBB_ERROR_NACK) {
    // No acknowledge received
}
if (err & I2CBB_ERROR_STRETCH_TOUT) {
    // Clock stretching timeout
}
if (err & I2CBB_ERROR_ARBITRATION) {
    // Bus arbitration lost (not implemented)
}
```

## File Structure

- `lpc1768_gpio.h` - LPC1768 GPIO register definitions and macros
- `Delay.h/cpp` - SysTick-based delay functions
- `i2cbitbang_board.h` - Board-specific I2C pin configuration
- `i2cbitbang.h/cpp` - I2C protocol implementation
- `i2cbitbang_driver.cpp` - Hardware abstraction layer for GPIO

## Timing Considerations

The library uses SysTick timer for accurate timing. Ensure that:
- System clock is correctly configured (default: 100 MHz)
- SysTick is not being used by other critical timing functions
- Interrupts don't cause excessive delays during I2C operations

## Notes

- This library does NOT support multi-master arbitration (yet)
- Clock stretching is supported with configurable timeout (default: 1ms)
- For critical applications, add external pull-up resistors (2.2kΩ - 4.7kΩ)
- The `SystemCoreClock` value should be updated to match your actual clock configuration

## License

MIT License - See LICENSE file for details.

## Author

TB (Tata)

Enjoy!
