
#start=robot.exe#

name "robot"

#make_bin#
#cs = 500#
#ds = 500#
#ss = 500#    ; stack
#sp = ffff#
#ip = 0#

; this is an example of contoling the robot.

; this code randomly moves the robot,
; and makes it to switch the lamps on and off.

; robot is a mechanical creature and it takes 
; some time for it to complete a task.
; status register is used to see if robot is busy or not.

; c:\emu8086\devices\robot.exe uses ports 9, 10 and 11
; source code of the robot and other devices is in:
; c:\emu8086\devices\developer\sources\
; robot is programmed in visual basic 6.0


; robot base i/o port:
r_port equ 9
mov al,0
out 9,al
out 10,al
out 11,al
; MAIN:
;===================================





call end_program
;===================================

; this procedure does not
; return until robot is ready
; to receive next command:
robopronto proc
; check if robot busy:
	  in al, r_port+2
      test al, 00000010b
      jnz busy ; busy, so wait.
      mov bx,1
      jmp nbusy
busy:
	  mov bx,0
nbusy:
ret    
robopronto endp

espera_robopronto proc
busay: in al, r_port+2
      test al, 00000010b
      jnz busay ; busy, so wait.	
ret
espera_robopronto endp
;===================================

examine proc
call espera_robopronto
mov al, 4
out r_port, al
call wait_exam
ret
examine endp
; this procedure does not
; return until robot completes
; the examination:
wait_exam proc
; check if has new data:
busy2: in al, r_port+2
       test al, 00000001b
       jz busy2 ; no new data, so wait.
ret    
wait_exam endp

;===================================

; switch off the lamp:
apaguelampada proc
call espera_robopronto
mov al, 6
out r_port, al

ret
apaguelampada endp

;===================================

; switch on the lamp:
acendalampada proc
call espera_robopronto
mov al, 5
out r_port, al

ret
acendalampada endp

;===================================

;siga em frente
move_forward proc
call espera_robopronto
call examine
; get result from
; data register:
in al, r_port + 1
; nothing found?
cmp al, 0
jne fim_move  ; - yes, so continue.
mov al, 1
out r_port, al
call espera_robopronto
fim_move: nop
ret
move_forward endp

;===================================

;olhe para o lado
turn_right proc
call espera_robopronto
mov al, 3
out r_port, al
call espera_robopronto
ret
turn_right endp

turn_left proc
call espera_robopronto
mov al, 2
out r_port, al
call espera_robopronto
ret
turn_left endp
;===================================
; INSTRUCOES:


;===================================
end_program proc
termino:
jmp termino
end_program endp

;===================================
