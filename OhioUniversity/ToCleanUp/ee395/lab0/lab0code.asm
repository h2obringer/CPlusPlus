;**********************************************************
;*   Laboratory # 0
;*	Program reads the state of RB0 pushbutton (normal=1)
;*	On each succesive press, rotates segment on left-most
;*	7 segment display. (portD if simulating)
;**********************************************************

	list p=16f877	; Assembler directive to turn list on
			; and give 16F877 listing codes
;
; Define some 8-bit file register labels
; See PIC16F877 datasheet for location of the Special Function Registers 
;
PORTB	equ	0x06	; in BANK 0
TRISB	equ	0x06	; in BANK 1
PORTD	equ	0x08	; in BANK 0
TRISD	equ	0x08	; in BANK 1
SEL	equ	0x20	; in BANK 0
TOGGLE	equ	0x21	; in BANK 0
STATUS	equ	0x03	; in all BANKS
;
;  Now define some BIT labels...
;
W	equ	d'0'	; destination=W  ('working' register)
F	equ	d'1'	; destination=f
RP1	equ	d'6'	; bank select high bit in status reg.
RP0	equ	d'5'	; bank select low bit in status reg.
;
;  Executable part of program starts here...  
;  Start at the reset vector
;
	org	0x000	; program starts at Program Memory location 0x0000
	nop		; nop required by older MPLAB ICD system
;
;  First allow program to initialize registers
;
Init:	clrf 	STATUS		; clear status reg, to select BANK0
	bsf	STATUS,RP0	; select bank 1 so we can access the TRISD register
	clrf	TRISD		; set all direction bits of PORTD to '0': all outputs
	movlw	B'00000001'	; set up I/O data for configuring PortB
	movwf	TRISB		; set bit 0 of PORTB to 1:input; all other bits to 0:outputs
	bcf	STATUS,RP0	; select bank 0 so we can access the PORTD register
	clrf	PORTD		; set all bits to '0' - turns off all segments.
	movlw	B'00000001'	; move the binary number B'00000001' into W
	movwf	SEL		; and store in memory location SEL (= address 0x20 in memory)
	movwf	PORTD		; store it also to PORTD, turn on top segment.
	movlw	B'00000010'	; move the binary number B'00000010' to PORTB,
	movwf	PORTB		; this will turn on the left-most 7-segment display
	clrf	TOGGLE		; set RAM location TOGGLE (=0x21) to all zeros: B'00000000'

TST:	btfsc	PORTB,0		; port B bit 0 is tested (RB0 button normally '1')
	goto	LED_NXT		; if button not pressed, then go to line labeled LED_NXT	
LED_CHG:
	btfsc	TOGGLE,0	; button pressed(='0'), test bit 0 of TOGGLE register
	goto	TST		; if TOGGLE bit 0 is set, then go to line labeled TST	
	rlf	SEL,F		; if TOGGLE bit 0 is clear, left-shift contents of SEL
	bsf	TOGGLE,0	; and, set bit 0 of TOGGLE
	goto	TST		; return to RB0 switch testing statement
LED_NXT:
	movf	SEL,W		; get display data (contents of SEL to W)
	movwf	PORTD		; put display data in W to PORTD (outputs the bit pattern in W)
	clrf	TOGGLE		; set all bits of TOGGLE back to 0 including bit 0
	goto	TST		; return to bit testing statement
	end			; Assembler directive = quit assembling.
