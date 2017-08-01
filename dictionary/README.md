# Dictionary

## About

A classe ```DAL``` (Dictionary with Array List ) implementa o tipo abstrato de dado (TAD) dicionário utilizando um vetor não-ordenado, isto é, os elementos armazenados não seguem uma sequência linear, então as operações são baseadas no valor de suas chaves e não nas posições do conteúdo.

A classe ```DSAL``` (Dictionary with Sorted-Array List ) é semelhanta à classe anterior, com a diferença de fazer uso de uma lista sequencial ordenada.

#### Performance

| Operations  | DAL           | DSAL  |
| :------------- |:-------------| :-----|
| Search(key, info) | O( n ) | O( 1 ) |
| Remove(key, info) | O( 1 ) | O( n ) |
| Insert(key, info) | O( 1 ) | O( n ) |
| Max( ) | O( n )   | O( 1 ) |
| Min( ) | O( n ) | O( 1 ) |
| Sucessor(key, info) | O( n )   | O( 1 ) |
| Predecessor(key, info) | O( n ) | O( 1 ) |


## How to run

| #       | Description          | Command  |
| :------------- |:-------------| :-----|
| 1      | Compile | ```$ make``` |
| 2      | Run   | ```$ ./dict.out``` |

## How to use

1º Copy files .hpp e .inl from directory ```include/```<br/>
2º Include file .hpp in your code.<br/>
3º Instance the class with the namespace ```ls``` and the type of the elements between ```<>```

### Example
```cpp
#include <iostream>
#include "dsal.h"
#include "dal.h"
#include <vector>

struct Fruit{
    int calories;
    float weight;
    std::string name;

    using FrKey = std::pair < std::string , int >;

    Fruit( int c=50, float w=10.0, std::string n="None")
    :calories(c), weight(w), name(n)
    {/*empty*/}

    FrKey get_key()
    {
        std::pair<std::string, int> p(name, calories);
        return p; 
    }

    float get_weight()
    {
        return weight;
    }
};

struct FruitCompare{
    bool operator()( const Fruit::FrKey &lhs, const Fruit::FrKey &rhs) const{
        return (lhs.second < rhs.second);
    }
};

int main() {
    
    DAL < int , std::string , MyKeyComparator > myList ( 50 );
    myList.insert( 2015065190 , "Poison Ivy" );
    myList.insert( 2014065191 , "Supergirl" );
    myList.insert( 2014065192 , "Harley Quinn" );
    myList.insert( 2017065190 , "Wonder Woman" );
    myList.insert( 2017065191 , "Bumblebee" );

    std::string name;
    myList.search( 2015065190 , name );
    std::cout << name << std::endl;

    myList.remove( 2017065190, name);
    std::cout << name << " was removed. \n";

    int id = 2014065192;
    myList.sucessor( 2014065192, id);
    std::cout << "Sucessor( 2014065192 ): " << id << std::endl;


    std::vector<Fruit> fruits = {
        Fruit( 20, 2.50, "Abacaxi"),
        Fruit( 85, 15.25, "Kiwi"),
        Fruit( 75, 10.0, "Blueberry"),
        Fruit( 50, 11.75, "Tomate"),
        Fruit( 10, 2.00, "Banana")
    };


    DSAL < Fruit::FrKey , float , FruitCompare > myDict ( 50 );

    myDict.insert( fruits[0].get_key(), fruits[0].get_weight() ));
    myDict.insert( fruits[1].get_key(), fruits[1].get_weight() );
    myDict.insert( fruits[2].get_key(), fruits[2].get_weight() );
    myDict.insert( fruits[3].get_key(), fruits[3].get_weight() );

    auto min = myDict.min();
    std::cout << "Fruta menos calórica eh: " << min.first <<std::endl ;

    auto max = myDict.max();
    std::cout << "Fruta mais calórica eh: " << max.first <<std::endl ;

    std::pair<std::string, int> p;
    myDict.predecessor(fruits[1].get_key(), p);
    std::cout<<"Predecessor("<<fruits[1].get_key().first << ","<<fruits[1].get_key().second <<"): "<< p.first<<","<<p.second<<std::endl;
    

    return 0;
}
```

The output would be:
```
PoisonIvy
WonderWoman was removed
Sucessor( 2014065192 ): 2015065190
Fruta menos calorica eh: Abacaxi
Fruta mais calórica eh: Kiwi
Predecessor(Kiwi,85): Blueberry,75
```


## Autorship

Developed by Mayra Dantas de Azevedo (<mayradazevedo@ufrn.edu.br >), 2017.1

&copy; IMD/UFRN 2017.
