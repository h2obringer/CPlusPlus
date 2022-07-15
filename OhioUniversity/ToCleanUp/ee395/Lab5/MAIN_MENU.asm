;       TEMPLATE FOR STUDENTS - EE395A Winter 2009
;	
;  Executable part of program starts here...  
;  Start at the reset vector
;

;equ statements copied from previous lab, may have some unneeded statements
Z		equ 0x02	;Z=2
PCL		equ 0x02	;PCL = 0x02
PORTC	equ 0x07	;bank 0 for RX(7) and TX(6)
TRISC	equ 0x87	;bank 1
STATUS	equ	0x03	;in all BANKS
SPBRG	equ 0x99	;bank 1
TXSTA	equ 0x98	;bank 1
RCSTA	equ 0x18	;bank 0
TXREG	equ 0x19	;bank 0
RCREG 	equ 0x1A	;bank 0
PIR1	equ 0x0C	;bank 0
RCIF	equ d'5'	;USART receive interrupt flag bit in PIR1
TXIF	equ d'4'	;USART transmit interrupt flag bit in PIR1
OERR	equ d'1'	;overrun error
FERR	equ d'2'	;frame error
CREN	equ d'4'	;continuous recieve enable bit


TEMP	equ 0x21	;general purpose register
TEMP2	equ 0x22

W		equ	d'0'	; destination=W  ('working' register)
F		equ	d'1'	; destination=f
RP1		equ	d'6'	; bank select high bit in status reg.
RP0		equ	d'5'	; bank select low bit in status reg.
	org	0x0000	; program starts at Program Memory location 0x0000
	nop		; put here so we can breakpoint at 0x0000
	movlw 0x01
	movwf TEMP2
	goto	INIT	; Jump over Tables so they can be in first 255 loc.

;    Set Configuration bits in code:
;	__CONFIG	0x3F31	; WDT disable, XT osc, PWRT enable, LVProg disable, CP off
;
; Data to send to Terminal is located in first 255 locations
; so no PCL overflow occurs when using computed goto's
;
; TABLE of messages to send to Computer Terminal.
; Each Message ends with '0x00' to indicate 'end of message'
;  ( My Editor - TABS spacing set to '8' )
;			
; 

		
		
		
		

MENU:	addwf	PCL,F	; do computed goto's to get characters
	retlw	0x0c	;  'new page'
	retlw	0x0a	;  'new line'
	retlw	0x09	;  'tab'
	retlw	A'M'	; M
	retlw	0x09	;  'tab'
	retlw	A'M'	; M
	retlw	A'a'	; a
	retlw	A'i'	; i
	retlw	A'n'	; n
	retlw	A' '	;  'space'
	retlw	A'M'	; M
	retlw	A'e'	; e
	retlw	A'n'	; n
	retlw	A'u'	; u
	retlw	0x0d	;  'carriage return'
	retlw	0x0a	;  'new line'
	retlw	0x0a	;  'new line'
	retlw	0x0a	;  'new line'
	retlw	0x09	;  'tab'
	retlw	A'f'	; f
	retlw	0x09	;  'tab'
	retlw	A'F'	; F
	retlw	A'i'	; i
	retlw	A'r'	; r
	retlw	A's'	; s
	retlw	A't'	; t
	retlw	A' '	; space
	retlw	A'N'	; N
	retlw	A'a'	; a
	retlw	A'm'	; m
	retlw	A'e'	; e
	retlw	0x0d	;  'carriage return'
	retlw	A'\n'	;  'new line'
	retlw	A'\n'	;  'new line'
	retlw	0x09	;  'tab'
	retlw	A'l'	; l - this is lowercase "L"
	retlw	0x09	;  'tab'
	retlw	A'L'	; L
	retlw	A'a'	; a
	retlw	A's'	; s
	retlw	A't'	; t
	retlw	A' '	;  'space'
	retlw	A'N'	; N
	retlw	A'a'	; a
	retlw	A'm'	; m
	retlw	A'e'	; e
	retlw	0x0d	;  'carriage return'
	retlw	0x0a	;  'new line'
	retlw	0x0a	;  'new line'
	retlw	0x09	;  'tab'
	retlw	A'p'	; p
	retlw	0x09	;  'tab'
	retlw	A'P'	; P
	retlw	A'I'	; I
	retlw	A'D'	; D
	retlw	A' '	;  'space'
	retlw	A'#'	; #
	retlw	0x0d	;  'carriage return'
	retlw	0x0a	;  'new line'
	retlw	0x0a	;  'new line'
	retlw	0x09	;  'tab'
	retlw	A'2'	; 2
	retlw	0x09	;  'tab'
	retlw	A'T'	; T
	retlw	A'o'	; o
	retlw	A'g'	; g
	retlw	A'g'	; g
	retlw	A'l'	; l
	retlw	A'e'	; e
	retlw	A' '	;  'space'
	retlw	A'R'	; R
	retlw	A'C'	; C
	retlw	A'2'	; 2
	retlw	0x0d	;  'carriage return'
	retlw	0x0a	;  'new line'
	retlw	0x0a	;  'new line'
	retlw	0x09	;  'tab'
	retlw	A'3'	; 3
	retlw	0x09	;  'tab'
	retlw	A'T'	; T
	retlw	A'o'	; o
	retlw	A'g'	; g
	retlw	A'g'	; g
	retlw	A'l'	; l
	retlw	A'e'	; e
	retlw	A' '	;  'space'
	retlw	A'R'	; R
	retlw	A'C'	; C
	retlw	A'3'	; 3
	retlw	0x0d	;  'carriage return'
	retlw	0x0a	;  'new line'
	retlw	0x0a	;  'new line'
	retlw	0x0a	;  'new line'
	retlw	0x00	; end of table - character
;
;
;	PUT THE REST OF YOUR DATA TABLES HERE -
;		LIST OF DATA	for First Name
;				for Last Name
;				for 'PID #'
;	End Each list with the "end of table" character = 0x00

;*****************************************************************************
;
;  Put all Initiliazation Instructions here:
;		Initialize UART, PORTC LEDs, etc.
;
INIT:	clrf STATUS

		bsf STATUS,RP0	;move to BANK 1
		movlw b'10000011'	;set the transmit line and receive line and set led's to output
		movwf TRISC
		
		movlw d'12'	;x value in equation
		movwf SPBRG	;set the baud rate 
		
		movlw	b'00100110'
		movwf	TXSTA ;send 8 data bits, set up the equation for the baud rate to
						;Fosc/(16*(x+1))
		
		bcf STATUS,RP0	;move to BANK 0
		
		movlw b'10010000'	;enables serial port 8 bit reception and continuous receive. 
		movwf RCSTA	
	
		goto SEND_MENU	
MAIN:	call RCV
		bcf STATUS,RP0
		movlw A'f'
		subwf TEMP,W
		btfsc STATUS,Z
		goto SEND_FIRST
		movlw A'l'
		subwf TEMP,W
		btfsc STATUS,Z
		goto SEND_LAST
		movlw A'2'
		subwf TEMP,W
		btfsc STATUS,Z
		goto LED_2
		movlw A'3'
		subwf TEMP,W
		btfsc STATUS,Z
		goto LED_3
		movlw A'p'
		subwf TEMP,W
		btfsc STATUS,Z
		goto SEND_PID
		movlw A'M'
		subwf TEMP,W
		btfsc STATUS,Z
		goto SEND_MENU
		goto MAIN
		
		
		
		

;*****************************************************************************
;
; Put your MAIN Program here:
;		Send the MAIN MENU to the PC terminal
;		Read the UART to get Received Character from Hyperterminal (PC)
;		test for what character was received from PC
;		Do what ever function should be perfomed
;			( send first name )
;			( send last name )
; 			( send 'PID #' )
;			( Toggle RC2 )
;			( Toggle RC3 )
;			( resend Main Menu )
;
;***************************************************************************** 
;  Subroutines:   Use subroutines to TRANSMIT and RECEIVE Characters via the PIC's USART.
;

;
RCV:	;write a subroutine to Recieve a character via the PIC'S USART.
		bcf STATUS,RP0	;bank0
RXWAIT:	btfsc RCSTA,OERR	;did overrun error occur?
		goto CLROR		;if so clear the over run error
		btfss PIR1,RCIF		;have we recieved a word?
		goto RXWAIT			;no data keep waiting		btfsc RCSTA,FERR	;did frame error occur?
		movf RCREG,W		;move recieved data word to a temp register
		movwf TEMP			;
		return
		
CLROR:	bcf RCSTA,CREN	;clear the cont.receive bit	
		bsf RCSTA,CREN	;set the cont.receive bit
		goto RXWAIT
		
;CLRFE:	movf RCREG,W	;this clears the frame error
;		goto ENDit

;	( don't forget to check for an Overrun Error, and clear it if it occurred)\

SEND_MENU:	movlw 0x00
			movwf TEMP2
WHY3:		movf TEMP2,W
			call MENU
			bcf STATUS,RP0
			movwf TXREG
			call TXMIT
			bcf STATUS,RP0
			incf TEMP2,F
			movlw d'94'
			subwf TEMP2,W
			btfss STATUS,Z
			goto WHY3
			goto MAIN

FIRST:	addwf PCL,F
		retlw A'R'
		retlw A'a'
		retlw A'n'
		retlw A'd'
		retlw A'y'
		retlw	0x0d	;  'carriage return'
		retlw	0x0a	;  'new line'
		
LAST:	addwf PCL,F
		retlw A'O'
		retlw A'b'
		retlw A'r'
		retlw A'i'
		retlw A'n'
		retlw A'g'
		retlw A'e'
		retlw A'r'
		retlw	0x0d	;  'carriage return'
		retlw	0x0a	;  'new line'	
			
PID:	addwf PCL,F
		retlw A'P'
		retlw A'0'
		retlw A'0'
		retlw A'1'
		retlw A'1'
		retlw A'9'
		retlw A'2'
		retlw A'0'
		retlw A'0'
		retlw A'9'
		retlw	0x0d	;  'carriage return'
		retlw	0x0a	;  'new line'
		
TXMIT:	;write a subroutine to Transmit a character via the PIC's USART.
		bsf STATUS,RP0
LOOP:	btfss TXSTA,1 
		goto LOOP
		bcf STATUS,RP0
		return
		
SEND_FIRST:	movlw 0x00
			movwf TEMP2
WHY:		movf TEMP2,W
			call FIRST
			bcf STATUS,RP0
			movwf TXREG
			call TXMIT
			incf TEMP2,F
			movlw d'7'
			subwf TEMP2,W
			btfss STATUS,Z
			goto WHY
			goto MAIN
			

SEND_LAST:	movlw 0x00
			movwf TEMP2
WHY2:		movf TEMP2,W
			call LAST
			bcf STATUS,RP0
			movwf TXREG
			call TXMIT
			incf TEMP2,F
			movlw d'10'
			subwf TEMP2,W
			btfss STATUS,Z
			goto WHY2
			goto MAIN
			
SEND_PID:	movlw 0x00
			movwf TEMP2
WHY4:		movf TEMP2,W
			call PID
			bcf STATUS,RP0
			movwf TXREG
			call TXMIT
			incf TEMP2,F
			movlw d'12'
			subwf TEMP2,W
			btfss STATUS,Z
			goto WHY4
			goto MAIN

LED_2:	btfss PORTC,2
		goto LED2_ON
		goto LED2_OFF
		
LED_3:	btfss PORTC,3	;toggle
		goto LED3_ON
		goto LED3_OFF
		
LED2_ON:	bsf PORTC,2
			goto MAIN
LED2_OFF:	bcf PORTC,2
			goto MAIN

LED3_ON:	bsf PORTC,3
			goto MAIN
LED3_OFF:	bcf PORTC,3
			goto MAIN
		
		end