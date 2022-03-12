#include <iostream>
#include <sstream>
#include <string>

void cin (int x)
{
    std:: cin >> x;
}

int main()
{
    std::cout << "Kecske";
    int x;
    cin(x);
    std::cout << "Ok";
    std::cin.ignore(256, '\n');
    // std::cin.get();

}