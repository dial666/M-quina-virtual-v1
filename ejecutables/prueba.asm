texto equ "hola\n soy\n valentina"
hola equ "salto?"

MOV EDX, KS
ADD EDX, TEXTO
SYS 0x04

mov EDX, KS
add edx, hola
sys 0x04
sys 0x07