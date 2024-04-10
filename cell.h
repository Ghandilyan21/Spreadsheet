#ifndef CELL_H
#define CELL_H
#include <iostream>
#include <string>
#include <iomanip>
class Cell
{
public:
    Cell() = default;
    Cell(int val);
    Cell(double val);
    Cell(const std::string& val); 
    Cell(const Cell& oth);
    Cell(Cell&& oth);
    ~Cell();

    const Cell& operator=(int rhs);
    const Cell& operator=(double rhs);
    const Cell& operator=(std::string rhs);
    const Cell& operator=(Cell&& rhs);
    const Cell& operator=(const Cell& rhs);
    const Cell& operator=(const char* rhs);
    operator int();
    operator double();
    operator std::string();
    bool operator==(const Cell& rhs) const;
    bool operator!=(const Cell& rhs) const;

    size_t get_size() const;
private:
    std::string info;
};
#endif