
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
finalize proc
call end_program
finalize endp

pare proc
in al, 9
cmp al, 1
jne fim_pare
mov al,0
out 9,al
fim_pare:
call espera_robopronto
pare endp
;===================================
; CONDICOES

roboocupado proc
in al,11
test al, 00000010b
jz false_roboocupado
mov bx,1
jmp fim_roboocupado
false_roboocupado:
mov bx,0
fim_roboocupado:
ret
roboocupado endp

roboparado proc
in al,11
test al, 00000010b
jz true_roboparado
in al, 9
cmp al, 1
jne true_roboparado
mov bx,0
jmp fim_roboparado
true_roboparado:
mov bx,1
fim_roboparado:
ret
roboparado endp

robomovimentando proc
call roboparado
cmp bx,0
je true_robomovimentando
jmp fim_robomovimentando
true_robomovimentando:
mov bx,1
fim_robomovimentando:
ret
robomovimentando endp

frenterobobloqueada proc
call examine
in al, 10
cmp al,0
jne robo_bloqueado
mov bx,0
jmp fim_robobloqueado
robo_bloqueado:
mov bx,1
fim_robobloqueado:
ret
frenterobobloqueada endp

direitarobobloqueada proc
call espera_robopronto
call turn_right
call espera_robopronto
call frenterobobloqueada
call turn_left
call espera_robopronto
ret
direitarobobloqueada endp

esquerdarobobloqueada proc
call espera_robopronto
call turn_left
call espera_robopronto
call frenterobobloqueada
call turn_right
call espera_robopronto
ret
esquerdarobobloqueada endp

lampadaapagadaafrente proc
call examine
in al, 10
cmp al, 8
je true_lampadaapagadaafrente
mov bx,0
jmp fim_lampadaapagadaafrente
true_lampadaapagadaafrente:
mov bx,1
fim_lampadaapagadaafrente:
ret
lampadaapagadaafrente endp


lampadaacesaafrente proc
call examine
in al, 10
cmp al, 7
je true_lampadaacesaafrente
mov bx,0
jmp fim_lampadaacesaafrente
true_lampadaacesaafrente:
mov bx,1
fim_lampadaacesaafrente:
ret
lampadaacesaafrente endp

lampadaacesaadireita proc
call espera_robopronto
call turn_right
call espera_robopronto
call lampadaacesaafrente
call turn_left
call espera_robopronto
ret
lampadaacesaadireita endp

lampadaacesaaesquerda proc
call espera_robopronto
call turn_left
call espera_robopronto
call lampadaacesaafrente
call turn_right
call espera_robopronto
ret
lampadaacesaaesquerda endp

lampadaapagadaadireita proc
call espera_robopronto
call turn_right
call espera_robopronto
call lampadaapagadaafrente
call turn_left
call espera_robopronto
ret
lampadaapagadaadireita endp

lampadaapagadaaesquerda proc
call espera_robopronto
call turn_left
call espera_robopronto
call lampadaapagadaafrente
call turn_right
call espera_robopronto
ret
lampadaapagadaaesquerda endp

;===================================
end_program proc
termino:
jmp termino
end_program endp

;===================================
