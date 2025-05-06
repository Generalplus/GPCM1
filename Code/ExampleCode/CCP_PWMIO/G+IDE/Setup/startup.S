/************************************************************************************
 * File:    startup.S
 * Purpose: Startup file for GPCM1xxx devices.
 *          Should use with GCC for ARM Embedded Processors
 * Version: V1.0
 * Date:    8 March 2017
 * Notice:  Changed for use with ARM IDE project wizard
 * Date:    8 March 2017
 *
 ************************************************************************************/
  .syntax unified
  .arch	armv6-m
  /* .fpu softvfp */


/************************************************************************************
 *
 *  The minimal vector table for GPCM1xxx.
 *  Device specific external interrupts can be added below.
 ************************************************************************************/
    .section .isr_vector
    .align 2
    .globl __isr_vector
__isr_vector:
    .long    __stack_end__         /* Top of Stack */
    .long    Reset_Handler         /* Reset Handler */
    .long    NMI_Handler           /* NMI Handler */
    .long    HardFault_Handler     /* Hard Fault Handler */
    .long    0                      /* Reserved */
    .long    0                      /* Reserved */
    .long    0                      /* Reserved */
    .long    0                     /* Reserved */
    .long    0                     /* Reserved */
    .long    0                     /* Reserved */
    .long    0                     /* Reserved */
    .long    SVC_Handler           /* SVCall Handler */
    .long    0                    /* Debug Monitor Handler */
    .long    0                     /* Reserved */
    .long    PendSV_Handler        /* PendSV Handler */
    .long    SysTick_Handler       /* SysTick Handler */


    /* External interrupts */
    .long     0                         //  0:
    .long     0                         //  1:
    .long     DMA_IRQHandler            //  2: DMA Interrupt
    .long     MAC_IRQHandler            //  3: MAC Interrupt
    .long     QD_IRQHandler             //  4: QD Interrupt
    .long     SAR_ADC_IRQHandler        //  5: SAR ADC Interrupt
    .long     DS_ADC_IRQHandler	        //  6: DS ADC Interrupt
    .long     DAC_CH0_IRQHandler        //  7: DAC_CH0 Interrupt
    .long     DAC_CH1_IRQHandler        //  8: DAC_CH1 Interrupt
    .long     CCP0_IRQHandler           //  9: CCP0 Interrupt
    .long     CCP1_IRQHandler           // 10: CCP1 Interrupt
    .long     CTS_TM0_IRQHandler        // 11:
    .long     CTS_TM1_IRQHandler        // 12:
    .long     TIMEBASE_IRQHandler		// 13:
    .long     I2C_IRQHandler            // 14: I2C Interrupt
    .long     0                         // 15:
    .long     UART_IRQHandler     	    // 16: UART Interrupt
    .long     0                         // 17:
    .long     I2S_IRQHandler            // 18: I2S Interrupt
    .long     SPI0_IRQHandler           // 19: SPI0 Interrupt
    .long     SPI1_IRQHandler           // 20: SPI1 Interrupt
    .long     EXTI0_IRQHandler          // 21: External Input 0 Interrupt
    .long     EXTI1_IRQHandler          // 22: External Input 1 Interrupt
    .long     EXTI2_IRQHandler          // 23: External Input 2 Interrupt
    .long     EXTI3_IRQHandler          // 24: External Input 3 Interrupt
    .long     DSADC_WAKEUP_IRQHandler   // 25:
    .long     TIMER0_IRQHandler         // 26: Timer0 Interrupt
    .long     TIMER1_IRQHandler         // 27: Timer1 Interrupt
    .long     TIMER2_IRQHandler         // 28: Timer2 Interrupt
    .long     KEYCHG_IRQHandler         // 29:
    .long     0                         // 30:
    .long     0     	                // 31:

    .size    __isr_vector, . - __isr_vector

/************************************************************************************
 *
 *  Reset_Handler()
 *  This function gets called at start of execution after a reset event.
 *  Copies data from ROM to RAM, clears BSS if defined,
 *  calls SystemInit() if defined, finally calls main()
 ************************************************************************************/
    .text
    .thumb
    .global __stack_end__
    .thumb_func
    .align 1
    .globl    Reset_Handler
    .type    Reset_Handler, %function
Reset_Handler:
    //
    // Clear watch dog
    //
    LDR		R0,	= 0x400D0000
    LDR		R1, = 0x000000AA
    STR		R1,	[R0]

    //
    // Init cache
    //
    LDR		R0,	= 0x50000030
    LDR		R1, [R0]
    LDR		R2, = ~0x0000001
    ANDS    R1, R2
    STR		R1,	[R0]                 // Disable cache
    NOP                              // Add 4 NOP after cache disable
    NOP
    NOP
    NOP
    LDR		R2, = 0x0000001
    ORRS    R1, R2
    STR		R1,	[R0]                 // Enable cache

    //
    // Waiting for the rising power
    //
    LDR		R2, = 0x60000
_init_:
    SUBS	R2, R2, #0x1
    BNE		_init_

/*  Setup stack pointer. Helpful for targets running in RAM without script file */
    ldr   r0, =__stack_end__
    mov   sp, r0

/*  Loop to copy data from read only memory to RAM. The ranges
 *   of copy from/to are specified by following symbols evaluated in
 *   linker script.
 *   __etext: End of code section, i.e., begin of data sections to copy from.
 *   __data_start__/__data_end__: RAM address range that data should be
 *   copied to. Both must be aligned to 4 bytes boundary.  */

     /* Place your code here */
	ldr	r1, =__etext
	ldr	r2, =__data_start__
	ldr	r3, =__data_end__

	subs	r3, r2
	ble	.LC1

.LC0:
	subs	r3, #1
	ldrb	r0, [r1,r3]
	strb	r0, [r2,r3]
	bgt	.LC0

.LC1:

/*  Loop to zero out BSS section, which uses following symbols
 *  in linker script:
 *   __bss_start__: start of BSS section. Must align to 4
 *   __bss_end__: end of BSS section. Must align to 4
 */
    /* Place your code here */
	ldr	r1, =__bss_start__
	ldr	r2, =__bss_end__

	movs	r0, 0

	subs	r2, r1
	ble	.LC3

.LC2:
	subs	r2, #1
	strb	r0, [r1, r2]
	bgt	.LC2
.LC3:

#ifndef __NO_SYSTEM_INIT
    bl    SystemInit
#endif

    @bl    __libc_init_array    /* C++ static variable initialization, dummy for C */
    bl    main
    .pool
    .size Reset_Handler, . - Reset_Handler

/************************************************************************************
 *
 *  Weak definition for exceptions.
 *  Any function with the same name will override the weak definition.
 ************************************************************************************/
/*  Macro to define default handlers. Default handler
 *  will be weak symbol and just dead loops. They can be
 *  overwritten by other handlers */
    .macro    def_default_handler    handler_name
    .align 1
    .thumb_func
    .weak    \handler_name
    .type    \handler_name, %function
\handler_name :
    b    .
    .size    \handler_name, . - \handler_name
    .endm

    def_default_handler     NMI_Handler
    def_default_handler     HardFault_Handler
    def_default_handler     SVC_Handler
    def_default_handler     PendSV_Handler
    def_default_handler     SysTick_Handler


    def_default_handler     Default_Handler
    def_default_handler     WDG_IRQHandler
    //def_default_handler   LVD_IRQHandler
    def_default_handler     DMA_IRQHandler
    def_default_handler     MAC_IRQHandler
    def_default_handler     QD_IRQHandler
    def_default_handler     SAR_ADC_IRQHandler
    def_default_handler     DS_ADC_IRQHandler
    def_default_handler     DAC_CH0_IRQHandler
    def_default_handler     DAC_CH1_IRQHandler
    def_default_handler     CCP0_IRQHandler
    def_default_handler     CCP1_IRQHandler
    def_default_handler     CTS_TM0_IRQHandler
    def_default_handler     CTS_TM1_IRQHandler
    def_default_handler     TIMEBASE_IRQHandler
    def_default_handler     I2C_IRQHandler
    //def_default_handler     I2C1_IRQHandler
    def_default_handler     UART_IRQHandler
    //def_default_handler     UART1_IRQHandler
    def_default_handler     I2S_IRQHandler
    def_default_handler     SPI0_IRQHandler
    def_default_handler     SPI1_IRQHandler
    def_default_handler     EXTI0_IRQHandler
    def_default_handler     EXTI1_IRQHandler
    def_default_handler     EXTI2_IRQHandler
    def_default_handler     EXTI3_IRQHandler
    //def_default_handler     EXTI4_15IRQHandler
    def_default_handler     DSADC_WAKEUP_IRQHandler
    def_default_handler     TIMER0_IRQHandler
    def_default_handler     TIMER1_IRQHandler
    def_default_handler     TIMER2_IRQHandler
    def_default_handler     KEYCHG_IRQHandler
    //def_default_handler DSADC_WAKEUP_IRQHandler



    .end
