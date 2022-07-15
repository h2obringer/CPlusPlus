;**********************************************************
;*  Laboratory #4
;*	Program uses the microcontroller's ADC to output
;*	the a digital voltage measurement from RA0 to the
;*	7-segment displays 
;**********************************************************

	list p=16f877	; Assembler directive to turn list on
			; and give 16F877 listing codes
;
; Define some 8-bit file register labels
; See PIC16F877 datasheet for location of the Special Function Registers 
;

;equ statements copied from previous lab, may have some unneeded statements
Z		equ 0x02	;Z=2
PCL		equ 0x02	;PCL = 0x02
PORTA	equ 0x05	; in BANK 0
TRISA	equ 0x05	; in BANK 1
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
TMR0		equ 0x01
OPTION_REG 	equ 0x01
ADCON0	equ 0x1F	;in BANK 0
ADCON1	equ 0x94	;in BANK 1
ADRESH equ 0x1E

W		equ	d'0'	; destination=W  ('working' register)
F		equ	d'1'	; destination=f
RP1		equ	d'6'	; bank select high bit in status reg.
RP0		equ	d'5'	; bank select low bit in status reg.

;end of equ statements, begin program code:



		org	0x000	; program starts at Program Memory location 0x0000
		nop		; nop required by older MPLAB ICD system
		goto INIT

INIT:	clrf STATUS
		bsf STATUS, RP0 		;move to BANK1 to access TRISA, B and D
		movlw b'00000000'
		movwf TRISD 		;set all pins of PORTD as outputs
		movlw b'11100001'
		movwf TRISB 		;set bits 1-4 of TRISB to outputs
			     		;and all other bits to inputs
		bsf TRISA, 0 	;PORTA bit 0 is now an input
		
		movlw b'00000000'
		movwf ADCON1		;configure ADC via ADCON1
		
		bcf STATUS, RP0		;return to BANK0
		
		movlw 0x00
		movwf D1
		movwf D2
		
		movlw b'01000001'	;Fosc/4 and turn ADON
		movwf ADCON0
		
		

MAIN:	;measure voltage
	bsf ADCON0,2

MAIN2:
		movf D1,W		;move value of the display to w
       	;call FIRST_VOL
		movwf PORTD		;
		movlw b'00000010' 		;7seg display left-most
        movwf PORTB
        call DELAY
        movf D2,W		;move value of the display to w
        ;call SEC_VOL
		movwf PORTD		;
		movlw b'00000100'		;7seg display left-mid
        movwf PORTB
      	call DELAY
      	;goto main was here
      	
        btfsc ADCON0,2 ;check if done, if done move it to be displayed, if not display old value
        goto MAIN2
        rrf ADRESH,F
        rrf ADRESH,F
        rrf ADRESH,F
        rrf ADRESH,F
        rrf ADRESH,F
        movlw b'00000111';mask the bits
        andwf ADRESH,W
        call FIRST_VOL
        movwf D1
        movlw b'00000111';mask the bits
        andwf ADRESH,W
        call SEC_VOL
        movwf D2
        goto MAIN
        
        
		;shift the bits
		
		;left justify the adresh then rright shift




;0.004 second delay to display two voltage digits 
DELAY:	movlw d'6'			;outer loop iterations
		movwf K			
INNER:	movlw d'221'		;inner loop iterations
		movwf J				;
NXT:	decfsz J,F			;decrement inner loop and store in J
		goto NXT			;go back to decrementing inner loop if not yet 0
		decfsz K,F			;decrement outer loop and store in K
		goto INNER			;go back and do inner loop again if outer loop isn't 0
		return
		

		
;computed goto for the 7-seg display WITH the decimal point
FIRST_VOL:	addwf	PCL,F		
		retlw	b'10111111' ;0.	
		retlw	b'10111111' ;0. 
		retlw	b'10000110' ;1.
		retlw	b'11011011' ;2.
		retlw	b'11011011' ;2.
		retlw	b'11001111' ;3.
		retlw	b'11100110' ;4.	
		retlw	b'11100110' ;4.	
		
SEC_VOL:	addwf	PCL,F
		retlw	b'01001111' ;3
		retlw	b'01100111' ;9
		retlw	b'01111100' ;6
		retlw	b'01011011' ;2
		retlw	b'01111111' ;8
		retlw	b'01100110' ;4
		retlw	b'00000110' ;1
		retlw	b'00000111' ;7
		
		end

