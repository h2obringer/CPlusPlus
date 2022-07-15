;**********************************************************
;*   Laboratory #3
;*	Program uses the four 7-segment displays to count 
;*	from 00.00 to 99.99, then rolls over to start the count again.
;**********************************************************

	list p=16f877	; Assembler directive to turn list on
			; and give 16F877 listing codes
;
; Define some 8-bit file register labels
; See PIC16F877 datasheet for location of the Special Function Registers 
;

Z		equ 0x02	;Z=2
PCL		equ 0x02	;PCL = 0x02
PORTB	equ	0x06	; in BANK 0
TRISB	equ	0x06	; in BANK 1
PORTD	equ	0x08	; in BANK 0
TRISD	equ	0x08	; in BANK 1
STATUS	equ	0x03	; in all BANKS
INTCON		equ 0x0B	; in all BANKS
K 		equ 0x20
J		equ 0x21
TEMP_W		equ 0x22
T_STAT		equ 0x23
D1		equ 0x24
D2		equ 0x25
D3		equ 0x26
D4		equ 0x27
TMR0		equ 0x01
OPTION_REG 	equ 0x01

W		equ	d'0'	; destination=W  ('working' register)
F		equ	d'1'	; destination=f
RP1		equ	d'6'	; bank select high bit in status reg.
RP0		equ	d'5'	; bank select low bit in status reg.

;end of equ statements, begin program code:

		org	0x000	; program starts at Program Memory location 0x0000
		nop		; nop required by older MPLAB ICD system
		goto INIT
		org 0x004
		goto TMR0_ISR
	
INIT:		clrf STATUS
		bsf STATUS, RP0 		;move to BANK1 to access TRISB and D
		movlw b'00000000'
		movwf TRISD 		;set all pins of PORTD as outputs
		movlw b'11100001'
		movwf TRISB 		;set bits 1-4 of TRISB to outputs
			     		;and all other bits to inputs
		movlw b'11010111'		;Use clock for timer0 and use prescaler of 256
		movwf OPTION_REG
		
		bcf STATUS, RP0		;return to BANK0
		
		movlw b'00100000'		;turn on timer0 interrupt
		movwf INTCON		;
		movlw d'216'		;initialize start value of the timer0
		movwf TMR0			;
		bsf INTCON,7		;enable global interrupt
		movlw 0x00
		movwf D1
		movwf D2
		movwf D3
		movwf D4
		
MAIN:		movf D1,W		;move value of the display to w
       		call NUMBER_124
		movwf PORTD		;
		movlw b'00010000' 		;7seg display right-most
        		movwf PORTB
        		call DELAY
        
       		 movf D2,W		;move value of the display to w
        		call NUMBER_124
		movwf PORTD		;
		movlw b'00001000'		;7seg display right-mid
        		movwf PORTB
      		 call DELAY
        
        		movf D3,W		;move value of the display to w
      		call NUMBER_3
		movwf PORTD		;
		movlw b'00000100' 		;7seg display left-mid
        		movwf PORTB
       		call DELAY
        
      		movf D4,W		;move value of the display to w
        		call NUMBER_124
		movwf PORTD		;
		movlw b'00000010'		;7seg display left-most
       		 movwf PORTB
       		call DELAY
        		goto MAIN
		

DELAY:		movlw d'6'			;outer loop iterations
		movwf K			
INNER:		movlw d'221'		;inner loop iterations
		movwf J			;
NXT:		decfsz J,F			;decrement inner loop and store in J
		goto NXT			;go back to decrementing inner loop if not yet 0
		decfsz K,F			;decrement outer loop and store in K
		goto INNER		;go back and do inner loop again if outer loop isn't 0
		return
		
TMR0_ISR:	movwf TEMP_W 		;save context
		swapf STATUS,W		;save context
		movwf T_STAT		;save context
			
		call INC_VALUE
		bcf INTCON,2		;clear the timer interrupt flag so that 
					;we don't call this ISR again.
			
		movlw d'216'
		movwf TMR0
			
			
		swapf T_STAT,W		;load context
		movwf STATUS		;load context
		swapf TEMP_W,F		;load context
		swapf TEMP_W,W		;load context
		retfie
		

;computed goto for the 7-seg displays WITHOUT the decimal point
NUMBER_124:	addwf	PCL,F
		retlw	b'00111111' ;0
		retlw	b'00000110' ;1
		retlw	b'01011011' ;2
		retlw	b'01001111' ;3
		retlw	b'01100110' ;4
		retlw	b'01101101' ;5
		retlw	b'01111100' ;6
		retlw	b'00000111' ;7
		retlw	b'01111111' ;8
		retlw	b'01100111' ;9
		

			
INC_VALUE:	incf D1,F		
		movlw d'10'
		subwf D1,W
		btfss STATUS,Z
		return	

		;if roll-over then reset D1 to 0 and increment D2
		movlw 0x00	
		movwf D1
		incf D2,F
		movlw d'10'
		subwf D2,W
		btfss STATUS,Z
		return

		;if roll-over then reset D2 to 0 and increment D3
		movlw 0x00
		movwf D2
		incf D3,F
		movlw d'10'
		subwf D3,W
		btfss STATUS,Z
		return

		;if roll-over then reset D3 to 0 and increment D4
		movlw 0x00
		movwf D3
		incf D4,F
		movlw d'10'
		subwf D4,W
		btfss STATUS,Z
		return
		;if roll-over, reset D4 to 0
		movlw 0x00
		movwf D4
		return			
		
end