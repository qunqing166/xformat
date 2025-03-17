#include <string>
#include <variant>
#include <vector>
#include <iostream>

namespace x
{

using var = std::variant<bool, char, short, int, long, long long, float, double, std::string>;

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
    int pos = format.find('}');
    if(pos == std::string::npos)
    {
        itemSize = format.length();
        return -1;
    }

    std::string braceStr = format.substr(0, pos + 1);

    if(braceStr[0] != '{' || braceStr[braceStr.length() - 1] != '}')
    {
        return -1;
    }

    std::string numStr = braceStr.substr(1, braceStr.length() - 2);

    itemSize = pos + 1;

    int num = 0;
    if (IsNumLegal(numStr))
        num = std::stoi(numStr);

    return num;
}

static std::string VarToString(const var& arg)
{
    std::string ret;
    switch (arg.index())
    {
    case 0: // bool
        ret = std::get<bool>(arg) ? "true" : "false";
        break;
    case 1: // char
        ret = std::get<char>(arg);
        break;
    case 2: // short
        ret = std::to_string(std::get<short>(arg));
        break;
    case 3: // int 
        ret = std::to_string(std::get<int>(arg));
        break;
    case 4: // long
        ret = std::to_string(std::get<long>(arg));
        break;
    case 5: // long long
        ret = std::to_string(std::get<long long>(arg));
        break;
    case 6: // float
        ret = std::to_string(std::get<float>(arg));
        break;
    case 7: // double
        ret = std::to_string(std::get<double>(arg));
        break;
    case 8: //std::string
        ret = std::get<std::string>(arg);
        break;

    default:
        break;
    }

    return ret;
}

/**
 * @brief 格式化字符串
 */
template <typename... Args>
std::string Format(const std::string &str, Args...args)
{
    std::vector<var> vargs = {(args)...};

    int pos = 0;

    std::string format = str;

    for (int i = 0; i < format.length(); ++i)
    {
        if(format[i] == '{')
        {
            pos = i;
            if(i + 1 < format.length() && format[i + 1] == '{')
            {
                format.erase(i, 1);
                // pos += 1;
            }
            else
            {
                int a;
                int num = GetFormatItemNum(format.substr(i), a);
                if(num >= vargs.size())
                {
                    num = vargs.size() - 1;
                }

                std::string repStr = VarToString(vargs[num]);

                format.replace(pos, a, repStr);
                pos += repStr.length() - a + 1;
            }
        }
        else if(format[i] == '}')
        {
            if(i + 1 < format.length() && format[i + 1] == '}')
            {
                format.erase(i, 1);
            }
        }
    }

    return format;
}

}