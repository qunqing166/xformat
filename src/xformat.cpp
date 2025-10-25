#include "xformat.h"

namespace x
{

bool IsNumLegal(const std::string& numStr)
{
    for (int i = 0; i < numStr.length(); i++)
    {
        if(numStr[i] <= '0' || numStr[i] > '9')
            return false;
    }
    return true;
}

int GetFormatItemNum(const std::string& format, int& itemSize, int& curIndex)
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

    int num = curIndex;
    if (!numStr.empty() && IsNumLegal(numStr))
        num = std::stoi(numStr);
    else{
        ++curIndex;
    }

    return num;
}

std::string VarToString(const var& arg)
{
    std::string ret = "[unkonwn type]";
    switch (arg.index())
    {
    case 0: ret =std::get<bool>(arg) ? "true" : "false";break;
    case 1:ret = std::get<char>(arg);break;
    case 2:ret = std::to_string(std::get<int64_t>(arg));break;
    case 3:ret = std::to_string(std::get<uint64_t>(arg));break;
    case 4:ret = std::to_string(std::get<double>(arg));break;
    case 5:ret = std::get<std::string>(arg);break;
    default:
        break;
    }

    return ret;
}

std::string FormatDetail(std::string& format, const std::vector<var>& vargs)
{
    int index = 0;
    int pos = 0;
    for (int i = 0; i < format.length(); ++i)
    {
        if(format[i] == '{')
        {
            pos = i;
            if(i + 1 < format.length() && format[i + 1] == '{')
            {
                format.erase(i, 1);
            }
            else
            {
                int a;
                int num = GetFormatItemNum(format.substr(i), a, index);
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
