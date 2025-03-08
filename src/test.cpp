#include "../include/XForamt.h"
#include <iostream>

int main()
{
    // auto a = x::GetArgs(1, 2, 3, 4, 5);

    // for(auto x : a)
    // {
    //     std::cout << std::get<int>(x) << "\n";
    // }
    std::string format = "url is {0}, this link is {5}, we should use '{' and '}' {{} to get the value of var";
    auto str = x::Format(format, "a", "b", "c", "d");
    std::cout << format << "\n";
    std::cout << str << "\n";
    std::cout << "nmsl\n";
    return 0;
}