.586
.model flat, stdcall
includelib kernel32.lib
includelib libucrt.lib
includelib Debug/GVALib.lib
ExitProcess proto : dword
strle proto: dword
compa proto: dword,:dword
cpr proto: dword
ipr proto: dword
.stack 4096
.const
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
a3 dword ?
b3 dword ?
c3 dword ?
d3 dword ?
hello3 dword ?
Hello3 dword ?
h3 dword ?
len3 dword ?
prio3 dword ?
g3 dword ?
e3 dword ?
.code
Compa proc a1:dword, b1:dword
Compa endp
Equal proc a2:dword, b2:dword
Equal endp
main proc
lea edx, [l33]
mov eax, [edx]
mov a3, eax

lea edx, [l43]
mov eax, [edx]
mov b3, eax

lea edx, [l53]
mov eax, [edx]
mov c3, al

push offset l73
pop hello3

push offset l93
pop Hello3

lea edx, [hello3+1]
mov eax, [edx]
mov h3, al

push offset hello3
call strle
mov len3, eax

push offset Hello3
push offset hello3
call compa
mov prio3, eax

lea edx, [l113]
mov eax, [edx]
mov b3, eax

lea edx, [l123]
mov eax, [edx]
mov d3, al

push b3
push a3
call Compa
mov g3, eax

lea edx, [a3]
mov eax, [edx]
mov e3, eax

lea edx, [b3]
mov eax, [edx]
mov a3, eax

lea edx, [e3]
mov eax, [edx]
mov b3, eax

push l143
call cpr

push l153
call cpr

push l173
call cpr

push 0
call ExitProcess
main endp
