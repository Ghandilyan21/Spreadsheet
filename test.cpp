#include "spreadsheet.h"
int main(int argc, char const *argv[])
{
    //Spreadsheet* a = new Spreadsheet(6,6);
    
    Spreadsheet a(5,5);
    std::string s = "barev";
    for (size_t i = 0; i < 5; ++i)
    {
        for (size_t j = 0; j < 5; ++j)
        {
            a[{i,j}] = "Testversion";
        }
    }
    //a[{1,1}] = "a";
    //std::cout << a << std::endl;
    //a.resize_col(6);
    //a[{0,6}] = "hay";
    //Spreadsheet b(2,3);
    //b = (Spreadsheet(3,3));
    
    Spreadsheet b(3,3);
    b = a;
    b[{0,0}] = 7;
    // a.resize(1,7);
    //std::cout << "esa : " << std::endl;
    //a.test_size();
    
    //a[{1,1}] = s;
    // a[{0,0}] = "bas";
    // a[{0,2}] = "jan";
    // a[{2,1}] = 3;
    // a[{2,2}] = 4;
    // a[{1,1}] = 5;
    std::cout << a << std::endl << b << std::endl; 
    //std::cout << "esa : "  << std::endl;

    return 0;
}
