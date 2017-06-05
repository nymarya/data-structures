# List

## Sobre a classe

A classe List consiste na implementação do tipo abstrato de dado (TAD) lista por meio do uso de lista duplamente encadeada, 
com as propriedades estruturais e operações referentes à TAD. Sua característica mais marcante é possuir operações de inserção
e remoção com complexidade constante.

## Como executar

| #       | Descrição           | Comando  |
| :------------- |:-------------| :-----|
| 1      | Compilar | ```$ make``` |
| 2      | Executar   | ```$ ./build/drive_list``` |

## Como utilizar em outros programas

1º Copie os arquivos .h e .inl da pasta ```include/```<br/>
2º Inclua o arquivo .h no seu programa.<br/>
3º Instancie a classe com o namespace ```ls```  o tipo dos elementos entre ```<>```

### Exemplo de utilização
```cpp
#include <iostream>
#include "list.h"

int main(){
    //Cria a lista com os valores de 1 a 5
    ls::List<int> list = {1, 2, 3, 4, 5};

    //Insere 10 no final da lista
    list.push_back(10);

    //Imprime conteúdo da lista
    for( auto i(list.begin()); i != list.end(); ++i)
        std::cout << *i << " ";
    std::cout << std::endl;
    
    //Insere [-3, -2, -1, 0] no início da lista
    lis.insert(list.begin(), {-3, -2, -1, 0};
    
    //Remove todos os elementos da lista
    list.remove( list.begin(), list.end() );

    return 0;
}
```

## Possíveis erros
A exceção ```std::out_of_range``` pode ser lançada ao chamar os métodos ```pop_back()```, ```pop_front()```, ```back()``` e ```front()```numa lista vazia.

## Autoria

Desenvolvido por Mayra Dantas de Azevedo (<mayradazevedo@gmail.com >), 2017.1

&copy; IMD/UFRN 2017.
