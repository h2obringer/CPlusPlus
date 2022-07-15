list p = 16f877

Z		equ 0x02	;Z=2
PCL		equ 0x02	;PCL = 0x02
PORTB	equ	0x06	;in BANK0
TRISB	equ 0x06	;in BANK1
PORTD	equ 0x08	;in BANK0
TRISD	equ 0x08	;in BANK1
STATUS	equ 0x03	;in all banks
TEMP	equ 0x20	;used to keep the current display #
RP1	equ d'6'
RP0	equ d'5'	
J	equ 0x30 	;storage value for inner counter value
K	equ 0x31	;storage for middle
L	equ 0x32	;storage for outer

W		equ d'0'	;W=0 for destinations
F		equ d'1'	;F=1 for destinations

		org 0x000	;program starts at Prog Mem loc. 0x00
		nop		;required by older MPLAB ICD system
		
		bsf STATUS, RP0 	;move to BANK1 to access TRISB and D
		movlw b'00000000'
		movwf TRISD 		;set all pins of PORTD as outputs
		movlw b'11100001'
		movwf TRISB 		;set bits 1-4 of TRISB to outputs
			     		    ;and all other bits to inputs
		bcf STATUS, RP0		;return to BANK0
		bsf PORTB, 1
INIT:	movlw 0x00			;move 0 to W
		movwf TEMP			;move 0 to TEMP in order to start displaying 0
		
		call COMP_GOTO		;move into computed goto
		
DISPLAY: movf TEMP, W		;move TEMP to W
		 call COMP_GOTO		;go and change TEMP to 0 instead of 10
		 movwf PORTD		;move TEMP value to PORTD to be displayed
		 call DELAY			;start the delay loop
		 incf TEMP			;increment TEMP value
		 movlw d'10'		;start the test to determine if at 10
		 subwf TEMP, W
		 btfsc STATUS,Z		;if Z is clear, skip and continue on program
		 goto INIT			;Z was not clear -> must reinitialize
		 goto DISPLAY		;value is not 10, continue as usual
		;computed goto
		
COMP_GOTO:		addwf	PCL,F
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
		
		
		;Delay loop for ~500000 microseconds
DELAY:	movlw	d'5'
		movwf	L
mid_agn:movlw	d'130'
		movwf  K
in_agn:	movlw  d'255'
		movwf  J
in_nxt:	decfsz J,F
		goto in_nxt
		decfsz K,F
		goto in_agn
		decfsz L,F
		goto mid_agn
		return
		
end