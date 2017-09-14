1. Escreva uma função em C que faz o debounce de botões ligados à porta P1.

```C
int debounce (int Bit){           //executa o debounce na porta P1."Bit"
  x = P1IN & Bit;                 //x = valor lido na porta P1."Bit"
  for(i=0;i<1000;i++){            
    if(P1IN & Bit != x){          //o valor deve se manter constante durante a contagem
      x = P1IN & Bit;             //caso contrario x é redefinido 
      i=0;                        //e se reinicia a contagem
    }
  }
  return x;
}
```

2. Escreva um código em C que lê 9 botões multiplexados por 6 pinos, e pisca os LEDs da placa Launchpad de acordo com os botões. 
Por exemplo, se o primeiro botão é pressionado, os LEDs piscam uma vez; se o segundo botão é pressionado, os LEDs piscam duas vezes;
e assim por diante. Se mais de um botão é pressionado, os LEDs não piscam.






