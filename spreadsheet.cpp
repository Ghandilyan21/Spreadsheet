#include "spreadsheet.h"
#include <iostream>
Spreadsheet::Spreadsheet()
    : m_height{3},
      m_width{3},
      sheet{new Cell*[m_height]}
{
    for (size_t i = 0; i < m_height; ++i)
    {
        sheet[i] = new Cell[m_width];
    }
}
Spreadsheet::Spreadsheet(const size_t height, const size_t width)
    : m_height{height},
      m_width{width},
      sheet{new Cell*[m_height]}
{
    for (size_t i = 0; i < m_height; ++i)
    {
        sheet[i] = new Cell[m_width];
    }
}
Spreadsheet::Spreadsheet(const Spreadsheet& oth)
    : Spreadsheet(oth.m_height, oth.m_width)
{
    for (size_t i = 0; i < m_height; ++i)
    {
        for (size_t j = 0; j < m_width; ++j)
        {
            sheet[i][j] = oth.sheet[i][j];
        }   
    }
}    
void Spreadsheet::clear()
{
    if (sheet != nullptr)
    {
        for (size_t i = 0; i < m_height; ++i)
        {
            delete [] sheet[i];
        }
        delete [] sheet;
        m_height = 0;
        m_width = 0;
    }
}
Spreadsheet::Spreadsheet(Spreadsheet&& oth)
    : m_height{oth.m_height},
      m_width{oth.m_width},
      sheet{oth.sheet}
{
    oth.sheet = nullptr;
    oth.m_height = 0;
    oth.m_width = 0;
}
Spreadsheet::~Spreadsheet()
{
    clear();
}
const Spreadsheet& Spreadsheet::operator=(Spreadsheet&& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    clear();
    m_height = rhs.m_height;
    m_width = rhs.m_width;
    sheet = rhs.sheet;
    rhs.sheet = nullptr;
    return *this;
}
const Spreadsheet& Spreadsheet::operator=(const Spreadsheet& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    clear();
    m_height = rhs.m_height;
    m_width = rhs.m_width;
    sheet = new Cell*[m_height];
    for (size_t i = 0; i < m_height; ++i)
    {
        sheet[i] = new Cell[m_width];
    }
    for (size_t i = 0; i < m_height; ++i)
    {
        for (size_t j = 0; j < m_width; ++j)
        {
            sheet[i][j] = rhs.sheet[i][j];
        }
    }
    return *this;
}
void Spreadsheet::resize_row(size_t row)
{
    size_t min_row_size = m_height < row? m_height : row;
    Cell** tmp = new Cell*[row];
    for (size_t i = 0; i < m_width; ++i)
    {
        tmp[i] = new Cell[m_width];
    }
    for (size_t i = 0; i < min_row_size; ++i)
    {
        tmp[i] = sheet[i]; 
    }
    if (row > m_height)
    {
        for (size_t i = m_height; i < row; ++i)
        {   
            tmp[i] = new Cell[m_width];
        }
    }
    delete[] sheet;
    sheet = tmp;
    m_height = row;
}
void Spreadsheet::resize_col(size_t col)
{
    size_t min_col_size = m_width < col? m_width : col;
    size_t save_height = m_height;
    Cell** tmp = new Cell*[m_height];
    for (size_t i = 0; i < m_height; ++i)
    {
        tmp[i] = new Cell[col];
    }
    for (size_t i = 0; i < m_height; ++i)
    {
        for (size_t j = 0; j < min_col_size; ++j)
        {
            tmp[i][j] = sheet[i][j];
        }
    }
    clear();
    m_height = save_height;
    m_width = col;
    sheet = tmp;
}
void Spreadsheet::resize(size_t height, size_t width)
{
    resize_row(height);
    resize_col(width);
}
Cell& Spreadsheet::operator[](std::pair<size_t, size_t> cord) const
{
    return sheet[cord.first][cord.second];
}
bool Spreadsheet::operator==(const Spreadsheet& rhs) const
{
    for (size_t i = 0; i < m_height; ++i)
    {
        for (size_t j = 0; j < m_width; ++j)
        {
            if (sheet[i][j] != rhs.sheet[i][j])
            {
                return false;
            } 
        }
    }
    return true;
}
bool Spreadsheet::operator!=(const Spreadsheet& rhs) const
{
    for (size_t i = 0; i < m_height; ++i)
    {
        for (size_t j = 0; j < m_width; ++j)
        {
            if (sheet[i][j] != rhs.sheet[i][j])
            {
                return true;
            } 
        }
    }
    return false;
}
size_t Spreadsheet::calc_cell_max_size(size_t ix) const
{
    size_t max = 5;
    for (size_t i = 0; i < m_width; ++i)
    {
        if (sheet[ix][i].get_size() > max)
        {
            max = sheet[ix][i].get_size();
        }
    }
    return max;
}
std::ostream& operator<<(std::ostream& out, const Spreadsheet& rhs)
{
    size_t cell_length = rhs.calc_cell_max_size(0);
    std::cout << "\033[0;40;101m" << std::setw(5) << std::left << "  N" << "\033[0m" << ' ';
    for (size_t i = 0; i < rhs.m_width; ++i)
    {
        std::cout << "\033[0;40;47m" << std::setw(cell_length + 1) << std::left << i + 1 << "\033[0m"  << ' ';
    }
    std::cout << std::endl << std::endl;
    for (size_t i = 0; i < rhs.m_height; ++i)
    {
        size_t cell_len = rhs.calc_cell_max_size(i);
        std::cout << "\033[0;40;47m" << std::setw(5) << std::left << i + 1 << "\033[0m" << ' '; 
        for (size_t j = 0; j < rhs.m_width; ++j)
        {
            out << "\033[0;40;100m" << std::setw(cell_len + 1) << std::left << (std::string)rhs.sheet[i][j] << "\033[0m" << ' ';
        }
        out << std::endl << std::endl;
    }
    return out;
}
