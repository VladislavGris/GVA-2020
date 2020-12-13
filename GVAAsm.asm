.586
.model flat, stdcall
includelib kernel32.lib
includelib libucrt.lib
includelib Debug/GVALib.lib
ExitProcess proto : dword
strle proto: byte
compa proto: byte,:byte
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
l103 dword 57
l113 byte 'd'
l123 dword 5
l133 byte 'a равно 5', 0
l143 byte 'a не равно 5', 0
l153 dword 3
l163 byte 'a не равно 3', 0
l173 dword 0
.data
a3 dword ?
b3 dword ?
c3 byte ?
d3 byte ?
hello3 byte 6 dup (?)
Hello3 byte 7 dup (?)
len3 dword ?
prio3 dword ?
g3 dword ?
e3 dword ?
