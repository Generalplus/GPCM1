;/**************************************************************************************************
; * Copyright(c) 2019 GENERALPLUS Technology Corporation. All rights reserved.
; *-------------------------------------------------------------------------------------------------
; * @File: 
; *   startup_GPCM1F064A.s    
; * @Version: 
; *   V0.9.2
; * @Date: 
; *   October 30, 2019
; * @Abstract: 
; *   Startup File for GPCM1Fx Series Device
; **************************************************************************************************/
; *** <<< Use Configuration Wizard in Context Menu >>> ***


; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000400

                AREA    STACK, NOINIT, READWRITE, ALIGN = 3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000000

                AREA    HEAP, NOINIT, READWRITE, ALIGN = 3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit

                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp              ; Top of Stack                
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler
					
                ; External Interrupts
                DCD     0                         ;  0:
                DCD     0                         ;  1:  
                DCD     DMA_IRQHandler            ;  2: DMA Interrupt
                DCD     MAC_IRQHandler            ;  3: MAC Interrupt
                DCD     QD_IRQHandler             ;  4: QD Interrupt
                DCD     SAR_ADC_IRQHandler        ;  5: SAR ADC Interrupt
                DCD     DS_ADC_IRQHandler	      ;  6: DS ADC Interrupt
                DCD     DAC_CH0_IRQHandler        ;  7: DAC_CH0 Interrupt
                DCD     DAC_CH1_IRQHandler        ;  8: DAC_CH1 Interrupt
                DCD     CCP0_IRQHandler           ;  9: CCP0 Interrupt
                DCD     CCP1_IRQHandler           ; 10: CCP1 Interrupt
                DCD     CTS_TM0_IRQHandler        ; 11: 
                DCD     CTS_TM1_IRQHandler        ; 12: 
                DCD     TIMEBASE_IRQHandler		  ; 13: 
                DCD     I2C_IRQHandler            ; 14: I2C Interrupt
                DCD     0                         ; 15:
                DCD     UART_IRQHandler     	  ; 16: UART Interrupt
                DCD     0                         ; 17:
                DCD     I2S_IRQHandler            ; 18: I2S Interrupt
                DCD     SPI0_IRQHandler           ; 19: SPI0 Interrupt
                DCD     SPI1_IRQHandler           ; 20: SPI1 Interrupt
                DCD     EXTI0_IRQHandler          ; 21: External Input 0 Interrupt
                DCD     EXTI1_IRQHandler          ; 22: External Input 1 Interrupt
                DCD     EXTI2_IRQHandler          ; 23: External Input 2 Interrupt
                DCD     EXTI3_IRQHandler          ; 24: External Input 3 Interrupt
                DCD     DSADC_WAKEUP_IRQHandler   ; 25: 
                DCD     TIMER0_IRQHandler         ; 26: Timer0 Interrupt
                DCD     TIMER1_IRQHandler         ; 27: Timer1 Interrupt
                DCD     TIMER2_IRQHandler         ; 28: Timer2 Interrupt
                DCD     KEYCHG_IRQHandler         ; 29: 
                DCD     0                         ; 30: 
                DCD     0     	                  ; 31: 
__Vectors_End
__Vectors_Size  EQU     __Vectors_End - __Vectors
                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
				EXPORT  _init_
                IMPORT  SystemInit
                IMPORT  __main	
					
	            ;
	            ; Clear watch dog
	            ;					

				LDR		R0,	= 0x400D0000         
				LDR		R1, = 0x000000AA         
				STR		R1,	[R0]
				
	            ;
	            ; Init cache
	            ;						
				LDR		R0,	= 0x50000030				
				LDR		R1, [R0]
				LDR		R2, = ~0x0000001                
				ANDS    R1, R2
				STR		R1,	[R0]                 ; Disable cache	
                NOP                              ; Add 4 NOP after cache disable
                NOP
                NOP
                NOP                              
				LDR		R2, = 0x0000001                
				ORRS    R1, R2
				STR		R1,	[R0]                 ; Enable cache

                ;
				; Waiting for the rising power
				;
				LDR		R2, = 0x60000				
_init_			SUBS	R2, R2, #0x1
				BNE		_init_
				
                LDR     R0, = SystemInit
                BLX     R0
                LDR     R0, = __main
                BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP
Default_Handler PROC
                EXPORT  WDG_IRQHandler             	[WEAK]
                EXPORT  DMA_IRQHandler             	[WEAK]
                EXPORT  MAC_IRQHandler            	[WEAK]
                EXPORT  QD_IRQHandler           	[WEAK]
                EXPORT  SAR_ADC_IRQHandler          [WEAK]
				EXPORT  DS_ADC_IRQHandler           [WEAK]
                EXPORT  DAC_CH0_IRQHandler          [WEAK]
                EXPORT  DAC_CH1_IRQHandler          [WEAK]
                EXPORT  CCP0_IRQHandler           	[WEAK]
                EXPORT  CCP1_IRQHandler           	[WEAK]
                EXPORT  CTS_TM0_IRQHandler        	[WEAK]
                EXPORT  CTS_TM1_IRQHandler         	[WEAK]
				EXPORT  TIMEBASE_IRQHandler        	[WEAK]
                EXPORT  I2C_IRQHandler            	[WEAK]
                EXPORT  UART_IRQHandler           	[WEAK]                
                EXPORT  I2S_IRQHandler           	[WEAK]
                EXPORT  SPI0_IRQHandler            	[WEAK]
                EXPORT  SPI1_IRQHandler            	[WEAK]
                EXPORT  EXTI0_IRQHandler           	[WEAK]
                EXPORT  EXTI1_IRQHandler           	[WEAK]
                EXPORT  EXTI1_IRQHandler           	[WEAK]         
                EXPORT  EXTI2_IRQHandler           	[WEAK]
                EXPORT  EXTI3_IRQHandler           	[WEAK]
				EXPORT  DSADC_WAKEUP_IRQHandler  	[WEAK]				
                EXPORT  TIMER0_IRQHandler          	[WEAK]
                EXPORT  TIMER1_IRQHandler          	[WEAK]
                EXPORT  TIMER2_IRQHandler         	[WEAK]
                EXPORT  KEYCHG_IRQHandler           [WEAK]
				
                ; External Interrupts
WDG_IRQHandler
DMA_IRQHandler
MAC_IRQHandler
QD_IRQHandler
SAR_ADC_IRQHandler
DS_ADC_IRQHandler
DAC_CH0_IRQHandler
DAC_CH1_IRQHandler
CCP0_IRQHandler
CCP1_IRQHandler
CTS_TM0_IRQHandler
CTS_TM1_IRQHandler
TIMEBASE_IRQHandler
I2C_IRQHandler
UART_IRQHandler
I2S_IRQHandler
SPI0_IRQHandler
SPI1_IRQHandler
EXTI0_IRQHandler
EXTI1_IRQHandler
EXTI2_IRQHandler
EXTI3_IRQHandler
DSADC_WAKEUP_IRQHandler
TIMER0_IRQHandler
TIMER1_IRQHandler
TIMER2_IRQHandler
KEYCHG_IRQHandler
                B       .

                ENDP


                ALIGN


; User Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap

__user_initial_stackheap PROC
                LDR     R0, = Heap_Mem
                LDR     R1, = (Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem + Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR
                ENDP

                ALIGN

                ENDIF

                END
					