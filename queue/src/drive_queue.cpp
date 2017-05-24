#include <iostream>
#include "queue.hpp"

int main(){

    ls::Queue<int> queue(3);

    queue.enqueue(5);
    assert(queue.front() == 5);
    assert(queue.size() == 1);

    queue.enqueue(4);
    queue.enqueue(3);

    //retirar 2 elementos
    queue.dequeue();
    queue.dequeue();
    assert( queue.size() == 1);

    //Insere mais um
    queue.enqueue(2);
    assert( queue.size() == 3);

    return 0;
}