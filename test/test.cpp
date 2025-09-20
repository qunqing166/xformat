#include "xformat.h"
#include <iostream>

int main()
{
    std::string format = "0 is {0}, 1 is {1}, 2 {{nmsl}}is {2}, 3 is {3}";
    auto str = x::Format(format, "a", true, 123, 3.33);
    std::cout << format << "\n";
    std::cout << str << "\n";

    return 0;
}
