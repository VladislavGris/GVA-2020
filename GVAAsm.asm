.586
.model flat, stdcall
includelib kernel32.lib
includelib libucrt.lib
includelib Debug/GVALib.lib
includelib Debug/GVAAsmLib.lib
ExitProcess proto : dword
SetConsoleTitleA proto:dword
GetStdHandle proto:dword
WriteConsoleA proto:dword,: dword,: dword,: dword,: dword
SetConsoleOutputCP proto:dword
SetConsoleCP proto:dword
int_to_char PROTO, pstr:dword, intfield:sdword
printconsole proto:dword,:dword
cleararray proto, arr:dword
strle proto: dword
compa proto: dword,:dword
.stack 4096
.const
ConsoleTitle byte 'GVA-2020',0
l12 dword 1
l22 dword 0
l33 dword 0
l44 dword 11
l54 dword -13
l64 byte 'a больше или равно b', 0
l74 byte 'a меньше b', 0
l84 dword 1
l94 byte 'a равно b', 0
l104 byte 'a не равно b', 0
l114 byte 'a'
l124 byte 'b'
l134 byte 'd'
l144 dword 6
l154 byte 'привет', 0
l164 dword 6
l174 byte 'Привет', 0
l184 dword 2
l194 byte 'Строка stra лексикографически меньше строки strb', 0
l204 dword 1
l214 byte 'Строка stra лексикографически больше строки strb', 0
l224 dword 0
l234 byte 'Строки лексикографически равны', 0
l244 dword 6
l254 dword 3
l264 dword 0
.data
result byte 40 dup(0)
consolehandle dword 0h
e3 byte 0,0
a4 dword ?
b4 dword ?
c4 dword ?
d4 dword ?
e4 byte 0,0
u4 byte 0,0
stra4 dword ?
strb4 dword ?
len4 dword ?
cmp4 dword ?
g4 byte 0,0
.code
gorl proc a1:dword, b1:dword
mov eax,a1
mov ebx,b1
cmp eax,ebx
jl f1
jg f2
f2:

mov eax, a1
ret 

jmp f3
f1:
mov eax, b1
ret 

f3:
gorl endp
equal proc a2:dword, b2:dword
mov eax,a2
mov ebx,b2
cmp eax,ebx
jne f4
je f5
f5:

mov eax, l12
ret 

jmp f6
f4:
mov eax, l22
ret 

f6:
equal endp
pr proc a3:byte, b3:byte
mov al, [a3]
mov e3, al

lea edx, [b3]
mov eax, [edx]
mov a3, al

lea edx, [e3]
mov eax, [edx]
mov b3, al

push offset ConsoleTitle
lea eax, a3
push eax
call printconsole
mov eax, 10
mov result, al
push offset ConsoleTitle
push offset result
call printconsole

mov eax, l33
ret 

pr endp
main proc
push 1251d
call SetConsoleOutputCP
push 1251d
call SetConsoleCP
push l44
pop a4

push l54
pop b4

push b4
push offset result
call int_to_char
push offset ConsoleTitle
push offset result
call printconsole
push offset result
call cleararray
mov eax, 10
mov result, al
push offset ConsoleTitle
push offset result
call printconsole

push b4
push a4
call gorl
mov c4, eax

push c4
push offset result
call int_to_char
push offset ConsoleTitle
push offset result
call printconsole
push offset result
call cleararray
mov eax, 10
mov result, al
push offset ConsoleTitle
push offset result
call printconsole

mov eax,a4
mov ebx,b4
cmp eax,ebx
jle f7
jge f8
f8:

push offset ConsoleTitle
push offset l64
call printconsole
mov eax, 10
mov result, al
push offset ConsoleTitle
push offset result
call printconsole

jmp f9
f7:
push offset ConsoleTitle
push offset l74
call printconsole
mov eax, 10
mov result, al
push offset ConsoleTitle
push offset result
call printconsole

f9:
push b4
pop a4

push b4
push a4
call equal
mov d4, eax

mov eax,d4
mov ebx,l84
cmp eax,ebx
jne f10
je f11
f11:

push offset ConsoleTitle
push offset l94
call printconsole
mov eax, 10
mov result, al
push offset ConsoleTitle
push offset result
call printconsole

jmp f12
f10:
push offset ConsoleTitle
push offset l104
call printconsole
mov eax, 10
mov result, al
push offset ConsoleTitle
push offset result
call printconsole

f12:
mov al, [l114]
mov e4, al

mov al, [l124]
mov u4, al

mov al, u4
push eax
mov al, e4
push eax
call pr

push offset ConsoleTitle
lea eax, e4
push eax
call printconsole
mov eax, 10
mov result, al
push offset ConsoleTitle
push offset result
call printconsole

lea edx, [l134]
mov eax, [edx]
mov e4, al

push offset ConsoleTitle
lea eax, e4
push eax
call printconsole
mov eax, 10
mov result, al
push offset ConsoleTitle
push offset result
call printconsole

push offset l154
pop stra4

push offset l174
pop strb4

push stra4
call strle
mov len4, eax

push offset ConsoleTitle
push stra4
call printconsole
mov eax, 10
mov result, al
push offset ConsoleTitle
push offset result
call printconsole

push offset ConsoleTitle
push strb4
call printconsole
mov eax, 10
mov result, al
push offset ConsoleTitle
push offset result
call printconsole

push len4
push offset result
call int_to_char
push offset ConsoleTitle
push offset result
call printconsole
push offset result
call cleararray
mov eax, 10
mov result, al
push offset ConsoleTitle
push offset result
call printconsole

push strb4
push stra4
call compa
mov cmp4, eax

mov eax,cmp4
mov ebx,l184
cmp eax,ebx
jne f13
je f14
f14:

push offset ConsoleTitle
push offset l194
call printconsole
mov eax, 10
mov result, al
push offset ConsoleTitle
push offset result
call printconsole

jmp f15
f13:
f15:
mov eax,cmp4
mov ebx,l204
cmp eax,ebx
jne f16
je f17
f17:

push offset ConsoleTitle
push offset l214
call printconsole
mov eax, 10
mov result, al
push offset ConsoleTitle
push offset result
call printconsole

jmp f18
f16:
f18:
mov eax,cmp4
mov ebx,l224
cmp eax,ebx
jne f19
je f20
f20:

push offset ConsoleTitle
push offset l234
call printconsole
mov eax, 10
mov result, al
push offset ConsoleTitle
push offset result
call printconsole

jmp f21
f19:
f21:
mov eax, strb4
mov stra4, eax

push offset ConsoleTitle
push stra4
call printconsole
mov eax, 10
mov result, al
push offset ConsoleTitle
push offset result
call printconsole

mov edx, stra4
lea edx, [edx + 3]
mov eax, [edx]
mov g4, al

push offset ConsoleTitle
lea eax, g4
push eax
call printconsole
mov eax, 10
mov result, al
push offset ConsoleTitle
push offset result
call printconsole

push a4
push offset result
call int_to_char
push offset ConsoleTitle
push offset result
call printconsole
push offset result
call cleararray
mov eax, 10
mov result, al
push offset ConsoleTitle
push offset result
call printconsole

push offset ConsoleTitle
lea eax, e4
push eax
call printconsole
mov eax, 10
mov result, al
push offset ConsoleTitle
push offset result
call printconsole

push offset ConsoleTitle
push stra4
call printconsole
mov eax, 10
mov result, al
push offset ConsoleTitle
push offset result
call printconsole

push 0
call ExitProcess
main endp
end main