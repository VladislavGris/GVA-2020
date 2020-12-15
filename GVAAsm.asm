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
cpr proto: dword
ipr proto: dword
.stack 4096
.const
ConsoleTitle byte 'GVA-2020',0
l12 dword 1
l22 dword 0
l33 dword 11
l43 dword 13
l53 byte 'a больше или равно b', 0
l63 byte 'a меньше b', 0
l73 dword 1
l83 byte 'a равно b', 0
l93 byte 'a не равно b', 0
l103 byte 'a'
l113 byte 'd'
l123 dword 6
l133 byte 'привет', 0
l143 dword 6
l153 byte 'Привет', 0
l163 dword 2
l173 byte 'Строка stra лексикографически меньше строки strb', 0
l183 dword 1
l193 byte 'Строка stra лексикографически больше строки strb', 0
l203 dword 0
l213 byte 'Строки лексикографически равны', 0
l223 dword 6
l233 dword 0
.data
result byte 40 dup(0)
consolehandle dword 0h
a3 dword ?
b3 dword ?
c3 dword ?
d3 dword ?
e3 byte ?
stra3 dword ?
strb3 dword ?
len3 dword ?
cmp3 dword ?
.code
GorL proc a1:dword, b1:dword
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
GorL endp
Equal proc a2:dword, b2:dword
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
Equal endp
main proc
push 1251d
call SetConsoleOutputCP
push 1251d
call SetConsoleCP
push l33
pop a3

push l43
pop b3

push b3
push a3
call GorL
mov c3, eax

push c3
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

mov eax,a3
mov ebx,b3
cmp eax,ebx
jle f7
jge f8
f8:

push offset ConsoleTitle
push offset l53
call printconsole
mov eax, 10
mov result, al
push offset ConsoleTitle
push offset result
call printconsole

jmp f9
f7:
push offset ConsoleTitle
push offset l63
call printconsole
mov eax, 10
mov result, al
push offset ConsoleTitle
push offset result
call printconsole

f9:
push b3
pop a3

push b3
push a3
call Equal
mov d3, eax

mov eax,d3
mov ebx,l73
cmp eax,ebx
jne f10
je f11
f11:

push offset ConsoleTitle
push offset l83
call printconsole
mov eax, 10
mov result, al
push offset ConsoleTitle
push offset result
call printconsole

jmp f12
f10:
push offset ConsoleTitle
push offset l93
call printconsole
mov eax, 10
mov result, al
push offset ConsoleTitle
push offset result
call printconsole

f12:
mov al, [l103]
mov e3, al

push offset ConsoleTitle
push offset e3
call printconsole
mov eax, 10
mov result, al
push offset ConsoleTitle
push offset result
call printconsole

lea edx, [l113]
mov eax, [edx]
mov e3, al

push offset ConsoleTitle
push offset e3
call printconsole
mov eax, 10
mov result, al
push offset ConsoleTitle
push offset result
call printconsole

push offset l133
pop stra3

push offset l153
pop strb3

push stra3
call strle
mov len3, eax

push offset ConsoleTitle
push stra3
call printconsole
mov eax, 10
mov result, al
push offset ConsoleTitle
push offset result
call printconsole

push offset ConsoleTitle
push strb3
call printconsole
mov eax, 10
mov result, al
push offset ConsoleTitle
push offset result
call printconsole

push len3
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

push strb3
push stra3
call compa
mov cmp3, eax

mov eax,cmp3
mov ebx,l163
cmp eax,ebx
jne f13
je f14
f14:

push offset ConsoleTitle
push offset l173
call printconsole
mov eax, 10
mov result, al
push offset ConsoleTitle
push offset result
call printconsole

jmp f15
f13:
f15:
mov eax,cmp3
mov ebx,l183
cmp eax,ebx
jne f16
je f17
f17:

push offset ConsoleTitle
push offset l193
call printconsole
mov eax, 10
mov result, al
push offset ConsoleTitle
push offset result
call printconsole

jmp f18
f16:
f18:
mov eax,cmp3
mov ebx,l203
cmp eax,ebx
jne f19
je f20
f20:

push offset ConsoleTitle
push offset l213
call printconsole
mov eax, 10
mov result, al
push offset ConsoleTitle
push offset result
call printconsole

jmp f21
f19:
f21:
mov eax, strb3
mov stra3, eax

push offset ConsoleTitle
push stra3
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