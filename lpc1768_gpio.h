/*
 * lpc1768_gpio.h
 *
 * Low-level GPIO driver for LPC1768 microcontroller
 * Direct register access without HAL dependencies
 */

#ifndef LPC1768_GPIO_H_
#define LPC1768_GPIO_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * LPC1768 Memory Map - GPIO Registers
 */
#define LPC_APB0_BASE         (0x40000000UL)
#define LPC_APB1_BASE         (0x40080000UL)
#define LPC_AHB_BASE          (0x20080000UL)

/* GPIO Base Addresses */
#define LPC_GPIO0_BASE        (0x2009C000UL)
#define LPC_GPIO1_BASE        (0x2009C020UL)
#define LPC_GPIO2_BASE        (0x2009C040UL)
#define LPC_GPIO3_BASE        (0x2009C060UL)
#define LPC_GPIO4_BASE        (0x2009C080UL)

/* Pin Connect Block Base Address */
#define LPC_PINCON_BASE       (0x4002C000UL)

/* System Control Block Base Address */
#define LPC_SC_BASE           (0x400FC000UL)

/*
 * GPIO Register Structure
 */
typedef struct {
    volatile uint32_t FIODIR;       /* 0x00: Fast GPIO Port Direction register */
    uint32_t RESERVED0[3];
    volatile uint32_t FIOMASK;      /* 0x10: Fast Mask register */
    volatile uint32_t FIOPIN;       /* 0x14: Fast Port Pin value register */
    volatile uint32_t FIOSET;       /* 0x18: Fast Port Output Set register */
    volatile uint32_t FIOCLR;       /* 0x1C: Fast Port Output Clear register */
} LPC_GPIO_TypeDef;

/*
 * Pin Connect Block Register Structure
 */
typedef struct {
    volatile uint32_t PINSEL[11];   /* Pin Function Select Registers */
    uint32_t RESERVED0[5];
    volatile uint32_t PINMODE[10];  /* Pin Mode Select Registers */
    volatile uint32_t PINMODE_OD[5]; /* Open Drain Mode Registers */
    volatile uint32_t I2CPADCFG;    /* I2C Pin Configuration */
} LPC_PINCON_TypeDef;

/*
 * System Control Register Structure (partial)
 */
typedef struct {
    uint32_t RESERVED0[4];
    volatile uint32_t FLASHCFG;     /* Flash Configuration */
    uint32_t RESERVED1[15];
    volatile uint32_t PLL0CON;      /* PLL0 Control Register */
    volatile uint32_t PLL0CFG;      /* PLL0 Configuration Register */
    volatile uint32_t PLL0STAT;     /* PLL0 Status Register */
    volatile uint32_t PLL0FEED;     /* PLL0 Feed Register */
    uint32_t RESERVED2[4];
    volatile uint32_t PLL1CON;      /* PLL1 Control Register */
    volatile uint32_t PLL1CFG;      /* PLL1 Configuration Register */
    volatile uint32_t PLL1STAT;     /* PLL1 Status Register */
    volatile uint32_t PLL1FEED;     /* PLL1 Feed Register */
    uint32_t RESERVED3[4];
    volatile uint32_t PCON;         /* Power Control Register */
    volatile uint32_t PCONP;        /* Power Control for Peripherals */
    uint32_t RESERVED4[15];
    volatile uint32_t CCLKCFG;      /* CPU Clock Configuration */
    volatile uint32_t USBCLKCFG;    /* USB Clock Configuration */
    volatile uint32_t CLKSRCSEL;    /* Clock Source Select */
    uint32_t RESERVED5[12];
    volatile uint32_t EXTINT;       /* External Interrupt Flag */
    uint32_t RESERVED6;
    volatile uint32_t EXTMODE;      /* External Interrupt Mode */
    volatile uint32_t EXTPOLAR;     /* External Interrupt Polarity */
    uint32_t RESERVED7[12];
    volatile uint32_t RSID;         /* Reset Source Identification */
    uint32_t RESERVED8[7];
    volatile uint32_t SCS;          /* System Control and Status */
    volatile uint32_t IRCTRIM;      /* IRC Trim */
    volatile uint32_t PCLKSEL0;     /* Peripheral Clock Select 0 */
    volatile uint32_t PCLKSEL1;     /* Peripheral Clock Select 1 */
} LPC_SC_TypeDef;

/*
 * SysTick Register Structure
 */
typedef struct {
    volatile uint32_t CTRL;         /* SysTick Control and Status Register */
    volatile uint32_t LOAD;         /* SysTick Reload Value Register */
    volatile uint32_t VAL;          /* SysTick Current Value Register */
    volatile uint32_t CALIB;        /* SysTick Calibration Register */
} SysTick_TypeDef;

/* SysTick Base Address */
#define SysTick_BASE          (0xE000E010UL)
#define SysTick               ((SysTick_TypeDef *)SysTick_BASE)

/* SysTick Control Register Bits */
#define SysTick_CTRL_ENABLE_Msk     (1UL << 0)
#define SysTick_CTRL_TICKINT_Msk    (1UL << 1)
#define SysTick_CTRL_CLKSOURCE_Msk  (1UL << 2)
#define SysTick_CTRL_COUNTFLAG_Msk  (1UL << 16)

/* SysTick Reload Value Mask */
#define SysTick_LOAD_RELOAD_Msk     (0x00FFFFFFUL)

/*
 * GPIO Port Pointers
 */
#define LPC_GPIO0             ((LPC_GPIO_TypeDef *)LPC_GPIO0_BASE)
#define LPC_GPIO1             ((LPC_GPIO_TypeDef *)LPC_GPIO1_BASE)
#define LPC_GPIO2             ((LPC_GPIO_TypeDef *)LPC_GPIO2_BASE)
#define LPC_GPIO3             ((LPC_GPIO_TypeDef *)LPC_GPIO3_BASE)
#define LPC_GPIO4             ((LPC_GPIO_TypeDef *)LPC_GPIO4_BASE)

#define LPC_PINCON            ((LPC_PINCON_TypeDef *)LPC_PINCON_BASE)
#define LPC_SC                ((LPC_SC_TypeDef *)LPC_SC_BASE)

/*
 * System Core Clock (default for LPC1768)
 * This should be updated based on actual system configuration
 */
#ifndef SystemCoreClock
#define SystemCoreClock       (100000000UL)  /* 100 MHz default */
#endif

/*
 * GPIO Direction Macros
 */
#define GPIO_DIR_INPUT        0
#define GPIO_DIR_OUTPUT       1

/*
 * GPIO Pin Macros
 */
#define GPIO_PIN_0            (1UL << 0)
#define GPIO_PIN_1            (1UL << 1)
#define GPIO_PIN_2            (1UL << 2)
#define GPIO_PIN_3            (1UL << 3)
#define GPIO_PIN_4            (1UL << 4)
#define GPIO_PIN_5            (1UL << 5)
#define GPIO_PIN_6            (1UL << 6)
#define GPIO_PIN_7            (1UL << 7)
#define GPIO_PIN_8            (1UL << 8)
#define GPIO_PIN_9            (1UL << 9)
#define GPIO_PIN_10           (1UL << 10)
#define GPIO_PIN_11           (1UL << 11)
#define GPIO_PIN_12           (1UL << 12)
#define GPIO_PIN_13           (1UL << 13)
#define GPIO_PIN_14           (1UL << 14)
#define GPIO_PIN_15           (1UL << 15)
#define GPIO_PIN_16           (1UL << 16)
#define GPIO_PIN_17           (1UL << 17)
#define GPIO_PIN_18           (1UL << 18)
#define GPIO_PIN_19           (1UL << 19)
#define GPIO_PIN_20           (1UL << 20)
#define GPIO_PIN_21           (1UL << 21)
#define GPIO_PIN_22           (1UL << 22)
#define GPIO_PIN_23           (1UL << 23)
#define GPIO_PIN_24           (1UL << 24)
#define GPIO_PIN_25           (1UL << 25)
#define GPIO_PIN_26           (1UL << 26)
#define GPIO_PIN_27           (1UL << 27)
#define GPIO_PIN_28           (1UL << 28)
#define GPIO_PIN_29           (1UL << 29)
#define GPIO_PIN_30           (1UL << 30)
#define GPIO_PIN_31           (1UL << 31)

/*
 * Power Control for Peripherals bits
 */
#define PCONP_PCGPIO          (1UL << 15)  /* GPIO power/clock control */

/*
 * Pin Mode definitions
 */
#define PINMODE_PULLUP        0  /* Pull-up resistor enabled */
#define PINMODE_REPEATER      1  /* Repeater mode */
#define PINMODE_NONE          2  /* Neither pull-up nor pull-down */
#define PINMODE_PULLDOWN      3  /* Pull-down resistor enabled */

/*
 * GPIO Helper Macros
 */

/* Set pin as output */
#define GPIO_SET_OUTPUT(port, pin)     ((port)->FIODIR |= (pin))

/* Set pin as input */
#define GPIO_SET_INPUT(port, pin)      ((port)->FIODIR &= ~(pin))

/* Set pin high (output) */
#define GPIO_SET_PIN(port, pin)        ((port)->FIOSET = (pin))

/* Set pin low (output) */
#define GPIO_CLEAR_PIN(port, pin)      ((port)->FIOCLR = (pin))

/* Read pin value */
#define GPIO_READ_PIN(port, pin)       (((port)->FIOPIN & (pin)) ? 1 : 0)

/* Toggle pin */
#define GPIO_TOGGLE_PIN(port, pin)     ((port)->FIOPIN ^= (pin))

/*
 * Open-Drain Configuration Macros
 */

/* Enable open-drain mode for a pin on a port (port 0-4) */
#define GPIO_ENABLE_OPEN_DRAIN(port_num, pin_num)  \
    (LPC_PINCON->PINMODE_OD[port_num] |= (1UL << (pin_num)))

/* Disable open-drain mode (normal push-pull) */
#define GPIO_DISABLE_OPEN_DRAIN(port_num, pin_num) \
    (LPC_PINCON->PINMODE_OD[port_num] &= ~(1UL << (pin_num)))

/*
 * Pin Function Selection
 * Each pin has 2 bits in PINSEL registers for function selection
 * PINSEL0 covers P0.0-P0.15
 * PINSEL1 covers P0.16-P0.31
 * PINSEL2 covers P1.0-P1.15
 * etc.
 */

/* Set pin function (func: 0-3) */
#define GPIO_SET_FUNCTION(pinsel_idx, bit_pos, func) \
    do { \
        LPC_PINCON->PINSEL[pinsel_idx] &= ~(3UL << (bit_pos)); \
        LPC_PINCON->PINSEL[pinsel_idx] |= ((func) << (bit_pos)); \
    } while(0)

/* Set pin mode (pull-up/pull-down/none) */
#define GPIO_SET_MODE(pinmode_idx, bit_pos, mode) \
    do { \
        LPC_PINCON->PINMODE[pinmode_idx] &= ~(3UL << (bit_pos)); \
        LPC_PINCON->PINMODE[pinmode_idx] |= ((mode) << (bit_pos)); \
    } while(0)

/*
 * Helper function to get port number from GPIO pointer
 */
static inline uint32_t LPC_GPIO_GetPortNum(LPC_GPIO_TypeDef* port)
{
    if (port == LPC_GPIO0) return 0;
    if (port == LPC_GPIO1) return 1;
    if (port == LPC_GPIO2) return 2;
    if (port == LPC_GPIO3) return 3;
    if (port == LPC_GPIO4) return 4;
    return 0; /* Default to port 0 */
}

/*
 * Helper function to get pin number from pin mask
 */
static inline uint32_t LPC_GPIO_GetPinNum(uint32_t pinMask)
{
    uint32_t pinNum = 0;
    while (pinMask > 1) {
        pinMask >>= 1;
        pinNum++;
    }
    return pinNum;
}

/*
 * Enable GPIO power (should be called during system initialization)
 */
static inline void LPC_GPIO_PowerEnable(void)
{
    LPC_SC->PCONP |= PCONP_PCGPIO;
}

/*
 * Configure a GPIO pin for I2C bit-banging (open-drain output with pull-up)
 */
static inline void LPC_GPIO_ConfigI2CPin(LPC_GPIO_TypeDef* port, uint32_t pinMask)
{
    uint32_t portNum = LPC_GPIO_GetPortNum(port);
    uint32_t pinNum = LPC_GPIO_GetPinNum(pinMask);
    
    /* Determine PINSEL and PINMODE register index and bit position */
    uint32_t pinsel_idx = (portNum * 2) + (pinNum / 16);
    uint32_t pinmode_idx = (portNum * 2) + (pinNum / 16);
    uint32_t bit_pos = (pinNum % 16) * 2;
    
    /* Set pin function to GPIO (function 0) */
    GPIO_SET_FUNCTION(pinsel_idx, bit_pos, 0);
    
    /* Set pin mode to pull-up */
    GPIO_SET_MODE(pinmode_idx, bit_pos, PINMODE_PULLUP);
    
    /* Enable open-drain mode */
    GPIO_ENABLE_OPEN_DRAIN(portNum, pinNum);
    
    /* Set as output (open-drain will handle high-Z when set high) */
    GPIO_SET_OUTPUT(port, pinMask);
    
    /* Set pin high (release bus) */
    GPIO_SET_PIN(port, pinMask);
}

#ifdef __cplusplus
}
#endif

#endif /* LPC1768_GPIO_H_ */
