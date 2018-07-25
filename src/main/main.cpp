
// The basic input output
#include <iostream>
#include <string>

int main()
{
    std::cout << "Please enter your name: ";

    std::string Name;
    std::cin >> Name;

    std::cout << "Hello " << Name << std::endl;

    return 0;
}
