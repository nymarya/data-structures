# Vector

## Sobre a classe

A classe Vector consiste na implementação do tipo abstrato de dado (TAD) lista, com as propriedades estruturais e operações referentes à TAD.

## Como executar

| #       | Descrição           | Comando  |
| :------------- |:-------------| :-----|
| 1      | Compilar | ```$ make``` |
| 2      | Executar   | ```$ ./build/drive_vector``` |

## Como utilizar em outros programas

1º Copie os arquivos .hpp e .inl da pasta ```include/```<br/>
2º Inclua o arquivo .hpp no seu programa.<br/>
3º Instancie a classe com o namespace ```ls```  o tipo dos elementos entre ```<>```

### Exemplo de utilização
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

**Importante!** Lembrar de incluir os arquivos ```.hpp``` e ```.inl``` ao compilar.

## Possíveis erros
A exceção ```std::out_of_range``` pode ser lançada ao chamar os métodos ```pop_back()```, ```pop_front()```, ```back()``` e ```front()```numa lista vazia. A mesma exceção pode ser acionada ao usar o método ```at()``` utilizando uma posição inválida.

## Autoria

Desenvolvido por Mayra Dantas de Azevedo (<mayradazevedo@gmail.com >), 2017.1

&copy; IMD/UFRN 2017.
