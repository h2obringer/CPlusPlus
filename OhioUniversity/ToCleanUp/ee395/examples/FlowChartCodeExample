;					Code Example

	list	P=16F877		; Compiler directive
	
;---------Register Equates------------------------------
PORTC equ	0x07	; Bank 0
TRISC equ	0x87	; Bank 1
STATUS equ	0x03	; Mirrored across all banks

;---------Bit Equates-----------------------------------
RP0 equ	5	; Register Bank select bit(STATUS)
W equ	0	; Working Register
F equ	1	; File Register

;---------PAUSE ROUTINE EQUATES-------------------------
inloop	equ 0x30	; For delay routine
outloop	equ	0x31

;---------MISC. VARIABLE EQUATES------------------------
count equ	0x32
;
;	PROGRAM STARTS HERE

	org		0x0000		; Compiler directive
	nop					; (1) No Operation, desired by MPLAB
	goto Main			; (2) Starting Place for entire App
	
;//*********************************************************
;//* Main Routine
;//*********************************************************
Main
	clrf	STATUS		; (1) Ensure that Bank 0 is seleted
	clrf	PORTC		; (1) Brink all of PORTC's pins low
	
	bsf		STATUS,RP0	; (1) Select Bank 1, needed for TRISC
	clrf	TRISC		; (1) Make all of PORTC's pins outputs
	
	bcf		STATUS,RP0	; (1) Select Bank 0
	
	clrf	count		; (1) Initialize count variable
	
Main_High
	call	Blink_High	; (2) Call the Blink_High subroutine
	
	incfsz	count,F		; (1),(2) if zero.
	goto	Main_High	; (2) Continue until count is zero
	
	clrf	PORTC		; (1) Ensure all LED's are off
	
Main_Low
	call	Blink_Low	; (2) Call the Blink_Low subroutine
	
	decfsz	count,F		; (1),(2) if zero
	goto	Main_Low	; (2) Continue until count is zero
	
	clrf	PORTC		; (1) Ensure that all LED's are off
	
	goto	Main_High	; (2) Continue this entire routine
						;	indefinitely
						
;//********************************************************
;//* Blink_High Subroutine
;//*
;//* This routine is used to toggle the high nibble of 
;//* PORTC on and off.
;//********************************************************
Blink_High
	movlw	0xF0		; (1) Use the bit mask 1111 0000
						;	to toggle the high nibble
	
	xorwf	PORTC,F		; (1) Toggle the high nibble
	
	call	Delay		; (2) This is a small delay
	
	return				; (2) Return from subroutine
	
;//********************************************************
;//* Blink_Low Subroutine
;//*
;//* This routine is used to create a small delay in between
;//* successive toggles of the LEDs attached to PORTC.
;//********************************************************
Blink_Low
	movlw	0x0F		; (1) Use the bit mask 0000 1111
						; 	to toggle the low nibble
	
	xorwf	PORTC,F		; (1) Toggle the low nibble
	
	call	Delay		; (2) This is a small delay
	
	return				; (2) Return from subroutine
	
;//********************************************************
;//* Delay Subroutine
;//*
;//* This routine is used to create a small delay in between
;//* successive toggles of the LEDs attached to PORTC.
;//********************************************************
Delay
	clrf	outloop		; (1) Initialize outloop variable to 0x00
	clrf	inloop		; (1) Initialize inloop variable to 0x00
	
Delay_in
	decfsz	inloop,F	; (1),(2) if zero
	goto Delay_in		; (2), Continue decrementing until zero
	
	decfsz	outloop,F	; (1),(2) if zero
	goto Delay_in		; (2), Count inloop again. This all
						;	happens until outloop reaches zero.
						
	return				; (2) Return from subroutine
	
	end					; Compiler directive