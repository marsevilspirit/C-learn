#ifndef SALESITEM_H
#define SALESITEM_H
#include <cmath>
#include <iostream>
#include <string>
using namespace std;

class Sales_item
{
public:
    string isbn;
    unsigned units_sold;
    double revenue;
public:
    Sales_item() : units_sold(0), revenue(0.0){}
    Sales_item(const string& book) : isbn(book), units_sold(0), revenue(0.0){}
    double avg_price() const;
    string risbn() { return isbn; }
    bool same_isbn(const Sales_item& rhs) const { return isbn == rhs.isbn;}
    Sales_item& operator+=(const Sales_item&);
    friend std::istream& operator>>(istream&, Sales_item&);
    friend ostream& operator<<(ostream&,const Sales_item&);
    friend Sales_item operator+(const Sales_item& lhs, const Sales_item& rhs);
};

inline double Sales_item::avg_price() const
{
    if(units_sold)    
        return revenue / units_sold;
    else
        return 0;
}

inline Sales_item& Sales_item::operator+=(const Sales_item& rhs)
{
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

inline istream& operator>>(istream& is, Sales_item& s)
{
    double price;
    is >> s.isbn >> s.units_sold >> price;
    if(is)
        s.revenue = s.units_sold * price;
    else
        s = Sales_item();

    return is;
}

inline ostream& operator<<(ostream& os, const Sales_item& s)
{
    os << s.isbn << "\t" << s.units_sold << "\t" << s.revenue << "\t" << s.avg_price();
    return os;
}

inline Sales_item operator+(const Sales_item& lhs, const Sales_item& rhs)
{
    Sales_item ret(lhs);
    ret += rhs;
    return ret;
}

#endif
