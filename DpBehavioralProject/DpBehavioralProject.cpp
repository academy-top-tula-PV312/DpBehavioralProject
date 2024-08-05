#include <iostream>
#include "Strategy.h"

int main()
{
    srand(time(nullptr));

    Vector myv(10);
    for (int i{}; i < myv.V().size(); i++)
        myv.V()[i] = rand() % 100;

    for (int i{}; i < myv.V().size(); i++)
        std::cout << myv.V()[i] << " ";
    std::cout << "\n";

    myv.SetStrategy(new SelectSortStrategy());
    myv.Sort();

    for (int i{}; i < myv.V().size(); i++)
        std::cout << myv.V()[i] << " ";
    std::cout << "\n";
}
