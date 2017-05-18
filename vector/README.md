# Vector

## Sobre a classe

A classe Vector consiste na implementação do tipo abstrato de dado (TAD) lista.

## Como executar

| #       | Descrição           | Comando  |
| :------------- |:-------------| :-----|
| 1      | Compilar | ```$ make``` |
| 2      | Executar   | ```$ ./build/drive_vector``` |

## Como fazer utilizar em outros programas

1º Copie os arquivos .hpp e .inl da pasta ```include/```<br/>
2º Inclua o arquivo .hpp no seu programa.<br/>
3º Instancie a classe com o namespace ```ls```  o tipo dos elementos entre ```<>```

#### Exemplo de utilização
```cpp
#include <iostream>
#include "../include/vector.hpp"

int main(){
    ls::Vector<int> v = {1, 2, 3, 4, 5};

    v.push_back(10);

    for( auto i(v.begin()); i != v.end(); ++i)
        std::cout << *i << " ";
    std::cout << std::endl;

    return 0;
}
```

**Importante!:** Lembrar de incluir o arquivo .hpp e .inl na hora de compilar.

## Possíveis erros

```Arquivo inválido! Por favor, tente novamente.```

Arquivos inválidos não serão lidos pelo jogo. Um arquivo é considerado ilegível se possuir número de linhas diferente de 3.


```A aposta não é um valor válido! Por favor, aposte entre R$ 1,00 - 10.000,00.``` 

O valor da aposta, ou seja, a primeira linha do arquivo lido, deve estar entre 1 e 10000 reais para ser considerado uma aposta válida.



```O número de rodadas não é válido! Por favor, aposte entre 1 - 10 rodadas.``` 

A segunda linha do arquivo, que representa o número de rodadas, deve conter um número que está entre 1 e 10 reais para ser considerada como uma aposta válida.



```O número de números apostados é inválido! Por favor, aposte ente 1 - 15 números.``` 

Para ser considerada como uma aposta válida, a terceira linha do arquivo deve conter de 1 a 15 números, sendo estes os números que o jogador quer apostar.

## Autoria

Desenvolvido pMayra Dantas de Azevedo (<mayradazevedo@gmail.com >)

2017.1

&copy; IMD/UFRN 2017.
