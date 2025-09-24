#include <cassert>
#include <cstddef>
#include <iostream>
#include <string>
#include <string_view>

class split_iterator
{
public:
    split_iterator() : finaly(true) {}
    split_iterator (std::string_view& s, char c) : str{s}, ch{c} {
        nextp();
    }

    split_iterator& operator++()
    {
        if (next == std::string_view::npos) {
            finaly = true;
            return *this;
        }
        nextp();
        return *this;
    }

    std::string_view& operator*()
    {
        return curr;
    }

    bool operator==(const split_iterator& other) const {
        return this->finaly == other.finaly;
    }

    bool operator!=(const split_iterator& other) const {
        return !(*this == other);
    }

private:
    void nextp()
    {
        next = str.find(ch, pos);
        if (next == std::string_view::npos) {
            curr = (pos < str.size() ? str.substr(pos, str.size()-pos) : "");
            return;
        }
        curr = (next-pos > 0 ? str.substr(pos, next-pos) : "");
        pos = next + 1;
    }
    size_t pos{};
    size_t next{};
    std::string_view str;
    std::string_view curr;
    char ch{};
    bool finaly = false;
};

std::string prnt (std::string_view s, char ch)
{
    std::string str;
    split_iterator g (s, ch);
    split_iterator end{};

    for (; g != end; ++g)
        str += std::string("[") + std::string(*g) + std::string("],");

    str.pop_back();
    return str;
}

int main()
{
    assert(prnt("", ',') == std::string(R"([])"));
    assert(prnt("a,,b,", ',') == std::string(R"([a],[],[b],[])"));
    assert(prnt("abc", ',') == std::string(R"([abc])"));
    assert(prnt("a,b,c,", ',') == std::string(R"([a],[b],[c],[])"));
    assert(prnt("a,b123,c,", ',') == std::string(R"([a],[b123],[c],[])"));
    assert(prnt("a,b,c123", ',') == std::string(R"([a],[b],[c123])"));
    assert(prnt("a123,b,c", ',') == std::string(R"([a123],[b],[c])"));
    assert(prnt("a,b,c", ',') == std::string(R"([a],[b],[c])"));
    assert(prnt("a,,b,,c,", ',') == std::string(R"([a],[],[b],[],[c],[])"));
}
