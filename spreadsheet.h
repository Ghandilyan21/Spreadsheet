#ifndef SPREADSHEET_H
#define SPREADSHEET_H
#include "cell.h"
class Spreadsheet
{
    friend std::ostream& operator<<(std::ostream& out, const Spreadsheet& rhs);
public:
    Spreadsheet();
    Spreadsheet(const size_t height, const size_t width);
    Spreadsheet(const Spreadsheet& oth); 
    Spreadsheet(Spreadsheet&& oth); 
    ~Spreadsheet();

    const Spreadsheet& operator=(const Spreadsheet& rhs);
    const Spreadsheet& operator=(Spreadsheet&& rhs);
    Cell& operator[](std::pair<size_t, size_t> indexes) const;
    bool operator==(const Spreadsheet& rhs) const;
    bool operator!=(const Spreadsheet& rhs) const;

    void resize_row(size_t row);
    void resize_col(size_t col);
    void resize(size_t row, size_t col);
private:
    mutable size_t cell_size = 5;
    size_t m_height;
    size_t m_width;
    mutable Cell** sheet;
    void clear();
    size_t calc_cell_max_size(size_t ix) const;
};

#endif