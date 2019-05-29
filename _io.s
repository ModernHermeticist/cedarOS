global outb

section .text:                    ; start of text section
align 4                           ; must be 4 byte aligned
; outb - send a byte to an I/O port
; stack: [esp + 8] the data byte
;        [esp + 4] the I/O port
;        [esp    ] the return address

outb:
    mov al, [esp + 8]             ; move the data to be sent to the al register
    mov dx, [esp + 4]             ; move the address of the I/O port into the dx register
    out dx, al                    ; send the data to the I/O port
    ret                           ; return to the calling function
