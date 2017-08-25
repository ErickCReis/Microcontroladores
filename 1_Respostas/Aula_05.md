Para as questões 2 a 5, considere que as variáveis `f`, `g`, `h`, `i` e `j` são do tipo inteiro (16 bits na arquitetura do MSP430), 
e que o vetor `A[]` é do tipo inteiro. Estas variáveis estão armazenadas nos seguintes registradores:
	f: R4
	g: R5
	h: R6
	i: R7
	j: R8
	A: R9
Utilize os registradores R11, R12, R13, R14 e R15 para armazenar valores temporários.

1. Escreva os trechos de código assembly do MSP430 para:

(a) Somente setar o bit menos significativo de R5.
  
  `bis.w BIT0,R5`
  
(b) Somente setar dois bits de R6: o menos significativo e o segundo menos significativo.
  
  `bis.w BIT0,R6`
  
  `bis.w BIT1,R6`
  
(c) Somente zerar o terceiro bit menos significativo de R7.
  
  `bic.w BIT2,R7`
  
(d) Somente zerar o terceiro e o quarto bits menos significativo de R8.
  
  `bis.w BIT2,R8`
  
  `bis.w BIT3,R8`
  
(e) Somente inverter o bit mais significativo de R9.
  
  `inv.w BITF,R9`
  
(f) Inverter o nibble mais significativo de R10, e setar o nibble menos significativo de R10. 
  
  `inv.w #0xF000,R10`
  
  `bis.w #0xF,R10`

2. "Traduza" o seguinte trecho de código em C para o assembly do MSP430:

```C
if(i>j) f = g+h+10;
else f = g-h-10;
```

```C
cmp R7,R8
jge ELSE

mov.w R6,R11
add.w #10,R11
add.w R5,R11
mov.w R11,R4

jmp EXIT

ELSE:

mov.w R6,R12
sub.w #10,R12
sub.w R5,R12
mov.w R12,R4

EXIT:

```

3. "Traduza" o seguinte trecho de código em C para o assembly do MSP430:

```C
while(save[i]!=k) i++;
```

```C
LOOP: mov.w R7, R12 	; R7 = i, R12 = temporário
rla R12 		; R12 = 2*i
add.w R10, R12 		; R10 = save, R12 = save + 2*i = &save[i]
cmp 0(R12), R9 		; Compara save[i] com k (R9)
jeq EXIT 		; save[ i ] != k ?
inc.w R7 		; i += 1;
jmp LOOP
EXIT:
```

4. "Traduza" o seguinte trecho de código em C para o assembly do MSP430:

```C
for(i=0; i<100; i++) A[i] = i*2;
```

```C
LOOP:
mov.w R7,R12 		; R12 = temp
rla R12 		; R12 = i*2
mov R12,R13 		; R13 = i*2
add.w R9,R12 		; R12 = R12 + &A[]
mov.w R13,0(R12) 	; A[i] = R13 = i*2

inc.w R7
cmp #100,R7
jl LOOP
```

5. "Traduza" o seguinte trecho de código em C para o assembly do MSP430:

```C
for(i=99; i>=0; i--) A[i] = i*2;
```

```C
LOOP:
mov.w R7,R12 		; R12 = temp
rla R12 		; R12 = i*2
mov R12,R13 		; R13 = i*2
add.w R9,R12 		; R12 = R12 + &A[]
mov.w R13,0(R12) 	; A[i] = R13 = i*2

dec.w R7
cmp #0,R7
jge LOOP
```
