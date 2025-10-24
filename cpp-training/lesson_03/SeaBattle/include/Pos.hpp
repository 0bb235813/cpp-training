#pragma once

class Pos
{
public:
    Pos();
    Pos(int n, int m);
    bool operator==(const Pos& other) const;

    char x;
    int y;
    bool horizontal;
};
