# Dictionary

## Sobre a classe

A classe ```DAL``` (Dictionary with Array List ) implementa o tipo abstrato de dado (TAD) dicionário utilizando um vetor não-ordenado, isto é, os elementos armazenados não seguem uma sequência linear, então as operações são baseadas no valor de suas chaves e não nas posições do conteúdo.

A classe ```DSAL``` (Dictionary with Sorted-Array List ) é semelhanta à classe anterior, com a diferença de fazer uso de uma lista sequencial ordenada,.

#### Perfomance

| Operações  | DAL           | DSAL  |
| :------------- |:-------------| :-----|
| Search(key, info) | O(n) | O(1) |
| Remove(key, info) | O(1)   | O(n) |
| Insert(key, info) | O(1)| O(n) |
| Max() | O(n)   | O(1) |
| Min() | O(n) | O(1) |
| Sucessor(key, info) | O(n)   | O(1) |
| Predecessor(key, info) | O(n) | O(1) |


## Como executar

| #       | Descrição           | Comando  |
| :------------- |:-------------| :-----|
| 1      | Compilar | ```$ make``` |
| 2      | Executar   | ```$ .dict.out``` |

## Como utilizar em outros programas

1º Copie os arquivos .h e .inl da pasta ```include/```<br/>
2º Inclua o arquivo .h no seu programa.<br/>
3º Instancie a classe com o tipo dos elementos entre ```<>```

### Exemplo de uso
```cpp
#include <iostream>
#include "dsal.h"

    return 0;
}
```

A saída do programa seria:
```
Temos 5 clientes ativos
Temos 4 clientes ativos
O cliente Ringo Starr possui R$2500.25
```


## Autoria

Desenvolvido por Mayra Dantas de Azevedo (<mayradazevedo@gmail.com >), 2017.1

&copy; IMD/UFRN 2017.
