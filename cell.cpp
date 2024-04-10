#include "cell.h"
#include "spreadsheet.h"
#include <iostream>
Cell::Cell(int val)
    : info{std::to_string(val)}
{
}
Cell::Cell(double val)
    : info{std::to_string(val)}
{
}
Cell::Cell(const std::string& val)
    : info{val}
{
}
Cell::Cell(const Cell& oth)
    : info{oth.info}
{
}
Cell::Cell(Cell&& oth)
    : info{std::move(oth.info)}
{
}
Cell::~Cell()
{
    info.clear();
}
const Cell& Cell::operator=(int rhs)
{
    info = std::to_string(rhs);
    return *this;
}
const Cell& Cell::operator=(double rhs)
{
    info = std::to_string(rhs);
    return *this;
}
const Cell& Cell::operator=(std::string rhs)
{
    info = std::move(rhs);
    return *this;
}
const Cell& Cell::operator=(const char* rhs)
{
    info = rhs;
    return *this;
}
const Cell& Cell::operator=(const Cell& rhs)
{
    info = rhs.info;
    return *this;
}

const Cell& Cell::operator=(Cell&& rhs)
{
    info = rhs.info;
    return *this;
}
Cell::operator int()
{
    try
    {
        return std::stoi(info);
    }
    catch(const std::invalid_argument& c)
    {
        std::cerr << c.what() << '\n';
        return 0;
    }
}
Cell::operator double()
{
    try
    {
        return std::stod(info);
    }
    catch(const std::invalid_argument& c)
    {
        std::cerr << c.what() << '\n';
        return 0;
    }
}
Cell::operator std::string()
{
    return info;
}
bool Cell::operator==(const Cell& rhs) const
{
    return info == rhs.info;
}
bool Cell::operator!=(const Cell& rhs) const 
{
    return info != rhs.info;
}
size_t Cell::get_size() const
{
    return info.size();
}
std::ostream& operator<<(std::ostream& out, Cell& rhs)
{
    out << (std::string)rhs;
    return out;
}