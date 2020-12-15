.586
.model flat, stdcall
includelib libucrt.lib

SetConsoleTitleA proto:dword
GetStdHandle proto:dword
WriteConsoleA proto:dword,: dword,: dword,: dword,: dword
int_to_char PROTO, pstr:dword, intfield:sdword
printconsole proto:dword,:dword
cleararray proto, arr:dword
.stack 4096

.code
cleararray proc arr:dword
mov edi, arr
mov ebx, 0
mov ecx, 39
mark:
mov [edi + ecx], bl
loop mark
ret
cleararray endp
int_to_char proc uses eax ebx ecx edi esi,
					pstr:dword,
					intfield:sdword
	mov edi,pstr
	mov esi, 0
	mov eax, intfield
	cdq
	mov ebx, 10
	idiv ebx
	test eax, 80000000h
	jz plus
	neg eax
	neg edx
	mov cl, '-'
	mov[edi], cl
	inc edi
plus:
	push dx
	inc esi
	test eax, eax
	jz fin
	cdq
	idiv ebx
	jmp plus
fin:
	mov ecx, esi
write:
	pop bx
	add bl, '0'
	mov[edi], bl
	inc edi
	loop write
	ret
int_to_char endp
printconsole proc uses eax ebx ecx edi esi, pstr:dword, ptitle:dword
push ptitle
call SetConsoleTitleA
push -11
call GetStdHandle
mov esi, pstr
mov edi, -1
count:
inc edi
cmp byte ptr [esi + edi],0
jne count
push 0
push 0
push edi
push pstr
push eax
call WriteConsoleA
ret
printconsole endp
end