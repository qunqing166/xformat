#include <string>
#include <variant>
#include <vector>
#include <iostream>

namespace x
{

using var = std::variant<bool, int, std::string>;

static std::vector<var> tmp;

// {a}
// {{} {}}


static bool IsNumLegal(const std::string& numStr)
{
    for (int i = 0; i < numStr.length(); i++)
    {
        if(numStr[i] <= '0' || numStr[i] > '9')
            return false;
    }
    return true;
}

/**
 * @brief 获取需要'{}'中的编号
 */
static int GetFormatItemNum(const std::string& format, int& itemSize)
{
    // {...

    int pos = format.find('}');
    if(pos == std::string::npos)
    {
        std::cout << "format str is error!\n";
        itemSize = format.length();
        return -1;
    }

    // if(pos + 1 < format.length() && format[pos + 1] == '}')
    // {

    // }

    std::string braceStr = format.substr(0, pos + 1);

    if(braceStr[0] != '{' || braceStr[braceStr.length() - 1] != '}')
    {
        std::cout << "截取占位符错误\n";
        return -1;
    }

    std::string numStr = braceStr.substr(1, braceStr.length() - 2);

    std::cout << "substr: " << braceStr << "\n";
    itemSize = pos + 1;

    int num = 0;
    if (IsNumLegal(numStr))
        num = std::stoi(numStr);

    return num;
}



template <typename... Args>
std::string Format(const std::string &str, Args...args)
{
    // "url is {0}, this link is {1}, we should use '{' and '}' to get the value of var"
    std::vector<var> vargs = {(args)...};
    std::string res;

    int status = 0;
    int pos = 0;

    std::string format = str;

    while(true)
    {
        int ll = format.find('{', pos);
        if(ll == std::string::npos)break;

        pos = ll;

        if(ll + 1 < format.length() && format[ll + 1] == '{')
        {
            format.erase(ll, 1);
            pos += 1;
        }
        else
        {
            int a;
            int num = GetFormatItemNum(format.substr(ll), a);
            
            if(num >= vargs.size())
            {
                num = vargs.size() - 1;
                std::cout << "error: 序号大于参数列表长度\n";
            }

            format.replace(pos, a, std::get<std::string>(vargs[num]));
            pos += std::get<std::string>(vargs[num]).length() - a;
        }
    }

    return format;
}

}