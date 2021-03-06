#include <Rish/Utils/String.h>

namespace rl {
namespace String {

std::string &replaceFirst(std::string &str, const std::string &from, const std::string &to)
{
    size_t start_pos = str.find(from);
    if (start_pos == std::string::npos)
        return str;
    str.replace(start_pos, from.length(), to);
    return str;
}

std::string &replaceAll(std::string &str, const std::string &from, const std::string &to)
{
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
    return str;
}

bool isSubString(std::string target, std::string filter)
{
    if(filter.size() > target.size())
        return false;
    //
    std::transform(target.begin(), target.end(), target.begin(), tolower);
    std::transform(filter.begin(), filter.end(), filter.begin(), tolower);
    //
    for(int i = 0; i <= target.size()-filter.size(); i++ )
    {
        if(target.substr(i,filter.size()) == filter)
            return true;
    }
    return false;
}

}
}