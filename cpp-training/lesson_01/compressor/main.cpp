#include <cstdint>
#include <iostream>
#include <optional>
#include <string_view>

unsigned helper (std::string_view n)
{
    if (n.size() == 2)
    {
        int first = n[0]-48;
        int second = n[1]-48;
        //std::cout << first*10+second << std::endl;
        return first*10+second;
    }
    //std::cout << n[0]-48 << std::endl;
    return n[0]-48;
}

std::optional<unsigned> isInt (std::string_view n)
{
    int first{}, second{};
    if (n.size() == 2)
    {
        first = n[0]-48;
        second = n[1]-48;
    }
    if (n.front() < 48 || n.front() > 57 || n.back() < 48 || n.back() > 57 || 
            n.size() > 2 || n.empty() || (first*10+second) > 63) return std::nullopt;
    return true;
}

int main()
{
    std::string_view nums {"1,3,60"};
    uint64_t result{};
    if (nums.empty()) return 0;

    int start{};
    for (int i{}; i < nums.size(); ++i)
    {
        uint64_t temp{};
        int end{};
        if (nums[i] == ',' || i == nums.size()-1) {
            if (i == nums.size()-1) end = nums.size()-1;
            else end = i-start;
            std::string_view sstr = nums.substr(start, end);
            if (!isInt(sstr)) {
                std::cout << "Incorrect data" << std::endl;
                return 0;
                }
            unsigned n = helper(sstr);
            temp = 1ULL << n-1;
            result = result | temp;
            start = i+1;
        }
    }
    std::cout << result << std::endl;
}
