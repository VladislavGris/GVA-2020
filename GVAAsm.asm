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
l53 byte 'c'
l63 dword 6
l73 byte 'ѕривет', 0
l83 dword 7
l93 byte 'привет', 0
l103 dword 1
l113 dword 57
l123 byte 'd'
l133 dword 5
l143 byte 'a равно 5', 0
l153 byte 'a не равно 5', 0
l163 dword 3
l173 byte 'a не равно 3', 0
l183 dword 0
.data
result byte 40 dup(0)
consolehandle dword 0h
a3 dword ?
b3 dword ?
c3 byte ?
num3 dword ?
d3 byte ?
stra3 dword ?
strb3 dword ?
h3 byte ?
len3 dword ?
prio3 dword ?
g3 dword ?
e3 dword ?
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

mov al, [l53]
mov c3, al

push b3
push a3
call Equal
mov num3, eax

push offset l73
pop stra3

push offset l93
pop strb3

push offset ConsoleTitle
push stra3
call printconsole
mov eax, 10
mov result, al
push offset ConsoleTitle
push offset result
call printconsole

mov edx, stra3
lea edx, [edx + 1]
mov eax, [edx]
mov h3, al

push stra3
call strle
mov len3, eax

push strb3
push stra3
call compa
mov prio3, eax

push l113
pop b3

lea edx, [l123]
mov eax, [edx]
mov d3, al

push b3
push a3
call GorL
mov g3, eax

push b3
push a3
call GorL

mov eax,a3
mov ebx,b3
cmp eax,ebx
jle f7
jge f8
f8:

push a3
pop e3

push b3
pop a3

push e3
pop b3

jmp f9
f7:
f9:
mov eax,a3
mov ebx,l133
cmp eax,ebx
jne f10
je f11
f11:

push offset ConsoleTitle
push offset l143
call printconsole
mov eax, 10
mov result, al
push offset ConsoleTitle
push offset result
call printconsole

jmp f12
f10:
push offset ConsoleTitle
push offset l153
call printconsole
mov eax, 10
mov result, al
push offset ConsoleTitle
push offset result
call printconsole

f12:
mov eax,a3
mov ebx,l163
cmp eax,ebx
je f13
jne f14
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
push 0
call ExitProcess
main endp
end main