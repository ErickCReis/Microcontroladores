# Questões Aula 02
- 1 . Quais as diferenças entre os barramentos de dados e de endereços?

O barramento de endereço é utilizado para indicar a origem ou destinos dos dados já o barramento de dados é onde se transmite dados entre as unidades

- 2 . Quais são as diferenças entre as memórias RAM e ROM?

RAM é uma memória volátil, ou seja, perde o conteúdo quando acaba a energia.
ROM é uma memória não-volátil, ou seja, mantém o conteúdo quando fica sem energia, a escrita nesse tipo de memória é bem mais lenta do que para a memória RAM.

- 3 . Considere o código abaixo:

```C
#include <stdio.h>
int main(void)
{
	int i;
	printf("Insira um número inteiro: ");
	scanf("%d", &i);
	if(i%2)
		printf("%d eh impar.\n");
	else
		printf("%d eh par.\n");
	return 0;
}
```

Para este código, responda: (a) A variável `i` é armazenada na memória RAM ou ROM? Por quê? (b) O programa compilado a partir deste código é armazenado na memória RAM ou ROM? Por quê?

(a) Na memoria RAM, porque se trata de uma variável auxilar e descartável.

(b) Na memoria ROM, pois o programa deve ser mantido caso o sistema reinicie ou fique sem energia.

- 4 . Quais são as diferenças, vantagens e desvantagens das arquiteturas Harvard e Von Neumann?

Arquitetura tipo Harvard: Caminhos de dados e de instrução distintos, dessa forma, seus componentes internos também estão dispostos em lugares distintos, o que a torna mais rápida porem mais complexa.

Von Neumann: é processada uma única informação por vez, visto que nessa tecnologia, execução e dados percorrem o mesmo barramento, o que torna a arquitetura mais simples porém torna o processo lento em relação à arquitetura Harvard.

- 5 . Considere a variável inteira `i`, armazenando o valor `0x8051ABCD`. Se `i` é armazenada na memória a partir do endereço `0x0200`, como ficam este byte e os seguintes, considerando que a memória é: (a) Little-endian; (b) Big-endian.

(a)  Little-endian:

`bytes` => `end. memória`

- 6 . Sabendo que o processador do MSP430 tem registradores de 16 bits, como ele soma duas variáveis de 32 bits?
