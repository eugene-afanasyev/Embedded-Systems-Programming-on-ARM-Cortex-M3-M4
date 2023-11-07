#define TASK_STACK_SIZE 1024u
#define SCHEDULER_STACK_SIZE 1024u
#define SRAM_START 0x20000000u
#define SRAM_SIZE ((40u) * (1024u))
#define SRAM_END ((SRAM_START) + (SRAM_SIZE))

#define T1_STACK_START SRAM_END
#define T2_STACK_START ((T1_STACK_START) - (TASK_STACK_SIZE))
#define T3_STACK_START ((T2_STACK_START) - (TASK_STACK_SIZE))
#define T4_STACK_START ((T3_STACK_START) - (TASK_STACK_SIZE))
#define IDLE_STACK_START ((T4_STACK_START) - (TASK_STACK_SIZE))
#define SCHEDULER_STACK_START ((IDLE_STACK_START) - (TASK_STACK_SIZE))

#define INTERRUPT_DISABLE() do { __asm volatile("MOV R0,#0x1"); __asm volatile("MSR PRIMASK,R0"); } while(0)
#define INTERRUPT_ENABLE() do { __asm volatile("MOV R0,#0x0"); __asm volatile("MSR PRIMASK,R0"); } while(0)

#define TICK_PER_SECOND 1000u
#define HSI_FREQUENCY 8000000u
#define SYSTICK_TIMER_CLK HSI_FREQUENCY

#define DUMMY_XPSR 0x01000000U

#define PERIPH_BASE (0x40000000UL)

#define AHB1_PERIPH_OFFSET (0x00020000UL)
#define AHB2_PERIPH_OFFSET (0x08000000UL)

#define AHB1_PERIPH_BASE (PERIPH_BASE + AHB1_PERIPH_OFFSET)
#define AHB2_PERIPH_BASE (PERIPH_BASE + AHB2_PERIPH_OFFSET)

#define GPIOE_OFFSET (0x1000UL)
#define GPIOE_BASE (AHB2_PERIPH_BASE + GPIOE_OFFSET)

#define GPIOE_MODE_R_OFFSET (0x0)
#define GPIOE_MODE_R (*(volatile unsigned int *)(GPIOE_BASE + GPIOE_MODE_R_OFFSET))

#define OD_R_OFFSET (0x14)
#define GPIOE_OD_R (*(volatile unsigned int *)(GPIOE_BASE + OD_R_OFFSET))

#define RCC_BASE (0x40021000UL)

#define AHBEN_R_OFFSET (0x14UL)
#define RCC_AHBEN_R (*(volatile unsigned int *)(RCC_BASE + AHBEN_R_OFFSET))

#define IOPEEN (1U << 21)

#define PINE9 (1U << 9)
#define PINE13 (1U << 13)
#define PINE15 (1U << 15)
#define PINE11 (1U << 11)
#define LED_PIN PINE9

#define TASK1_LED PINE9
#define TASK2_LED PINE11
#define TASK3_LED PINE13
#define TASK4_LED PINE15

#define __IO volatile

typedef struct
{
    volatile uint32_t MODER;
    volatile uint32_t DUMMY[4];
    volatile uint32_t ODR;
} GPIO_TypeDef;

typedef struct {
    uint32_t psp;
    uint32_t block_count;
    uint8_t state;
    void (*task_handler)(void);
} sTCB;

enum eTaskState {
    READY = 0x00,
    BLOCKED
};
