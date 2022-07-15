	list p=16f877
	

PORTB	equ	0x06	; in BANK 0
TRISB	equ	0x06	; in BANK 1
PORTD	equ	0x08	; in BANK 0
TRISD	equ	0x08	; in BANK 1
SEL		equ	0x20	; in BANK 0
TOGGLE	equ	0x21	; in BANK 0
STATUS	equ	0x03	; in all BANKS
FSR 	equ 0x04 	;use to store address we are refering to for indirect adressing
INDF	equ 0x00	;indirect addressing

W		equ	d'0'	; destination=W  ('working' register)
F		equ	d'1'	; destination=f
RP1		equ	d'6'	; bank select high bit in status reg.
RP0		equ	d'5'	; bank select low bit in status reg.
Z		equ 0x02

		org	0x000	; program starts at Program Memory location 0x0000
		nop			; nop required by older MPLAB ICD system

		bcf STATUS,7 	;select bank 0 and 1
		movlw 0x20 		;set the first address
		movwf FSR 		;   of the set to write to
NXT0:	movlw 0xA1 		; value to write to registers is 0xA1
		movwf INDF		; write 0xA1 to the indirect address
						; that we set above (starting at 0x20)
		incf FSR,1 		;change to the next location and store the new value in the FSR
		movf FSR,0 		;move value of address to working register
		sublw 0x70 		;compare address to 0x70
		btfss STATUS,Z 	; if address is 0x70 (outside of our range)then proceed to bank 1.
		goto NXT0		;    else continue writing to this bank.
		goto BANK1
		
BANK1: 	movlw 0xA0 		;set first address of bank1 to write to.
		movwf FSR 		;store this address in the FSR for indirect addressing later. 
NXT1:	movlw 0xA1		;store the value we wish to write to registers inside the w register.
		movwf INDF		;store our value (0xA1) inside the address in FSR
		incf FSR,1		;change to the next location and store the new value in the FSR	
		movf FSR,0		;move value of new address to the working register
		sublw 0xF0		;compare address to 0xF0 (next undesired address)
		btfss STATUS,Z	;if the next address is 0xF0 move on to the next bank
		goto NXT1		;else continue writing to this bank
		goto BANK2
		
BANK2:	bsf STATUS,7 	;select banks 2 and 3 to work with
		movlw 0x110		;select start address to write into while in bank2.
		movwf FSR		;store our start address in the FSR to allow indirect addressing.
NXT2:	movlw 0xA1		;store the value we wish to write to registers inside the w register. 
		movwf INDF		;store our value (0xA1) inside the address in FSR
		incf FSR,1		;change to the next location and store the new value in the FSR
		movf FSR,0		;move value of new address to the working register
		sublw 0x170		;compare address to 0x170 (next undesired address)
		btfss STATUS,Z	;if the next address is 0x170 move onto the next bank
		goto NXT2		;else continue writing to this bank
		goto BANK3
		
BANK3:	movlw 0x190		;select start address to write into while in bank3.
		movwf FSR		;store our start address in the FSR to allow indirect addressing.
NXT3:	movlw 0xA1		;store the value we wish to write to registers inside the w register.
		movwf INDF		;store our value (0xA1) inside the address in FSR
		incf FSR,1		;change to the next location and store the new value in the FSR
		movf FSR,0		;move value of new address to the working register
		sublw 0x1E5		;compare address to 0x1E5 (next undesired address)
		btfss STATUS,Z	;if the next address is 0x1E5 finish the program
		goto NXT3		;else continue writing to the bank
		end
	