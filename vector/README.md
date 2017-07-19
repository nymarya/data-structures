# Vector

## Class Vector

The class Vector consists of implementing the abstract data type (ADT) list, using structural properties and operations. 

## How to run

| #       | Description           | Command  |
| :------------- |:-------------| :-----|
| 1      | Compile | ```$ make``` |
| 2      | Run   | ```$ ./build/drive_vector``` |

## How to use

1º Copy files .hpp e .inl from directory ```include/```<br/>
2º Include file .hpp in your code.<br/>
3º Instance the class with the namespace ```ls``` and the type of the elements between ```<>```

### Example
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

## Exceptions
The exception ```std::out_of_range``` is thrown if the methods ```pop_back()```, ```pop_front()```, ```back()``` e ```front()``` are called in a empty container. The function ```at()``` throws ```std::out_of_range``` if n is out of bounds.

## Authorship

Developed by Mayra Dantas de Azevedo (<mayradazevedo@ufrn.edu.br >), 2017.1

&copy; IMD/UFRN 2017.
