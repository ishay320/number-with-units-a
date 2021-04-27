#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include "NumberWithUnits.hpp"
#include <algorithm>

using namespace std;
namespace ariel
{
    NumberWithUnits::NumberWithUnits(double num, string name)
    {
        _num = num;
        _name = name;
    }
    NumberWithUnits::NumberWithUnits(const NumberWithUnits &num)
    {
        _num = num._num;
        _name = num._name;
    }
    void NumberWithUnits::read_units(std::ifstream &units_file)
    {
        
    } ////////////////////////////////

    NumberWithUnits NumberWithUnits::operator-() const
    {
        NumberWithUnits tmp{-_num, _name};
        return tmp;
    }
    NumberWithUnits NumberWithUnits::operator+() const
    {
        NumberWithUnits tmp{+_num, _name};
        return tmp;
    }
    NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits &num) const
    {
        NumberWithUnits tmp{_num + convert(num._num, num._name, _name), _name};
        return tmp;
    }
    NumberWithUnits NumberWithUnits::operator+(double &num) const
    {
        NumberWithUnits tmp{_num + num, _name};
        return tmp;
    }

    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits &num) const
    {
        NumberWithUnits tmp{_num - convert(num._num, num._name, _name), _name};
        return tmp;
    }
    NumberWithUnits operator*(const NumberWithUnits &num, double x)
    {
        NumberWithUnits tmp(num);
        tmp.setNumber(tmp.getNumber() * x);
        return tmp;
    }
    NumberWithUnits operator*(double x, const NumberWithUnits &num)
    {
        NumberWithUnits tmp(num);
        tmp.setNumber(tmp.getNumber() * x);
        return tmp;
    }

    NumberWithUnits operator/(const double x, const NumberWithUnits &num)
    {
        NumberWithUnits tmp(num);
        tmp.setNumber(tmp.getNumber() / x);
        return tmp;
    }

    NumberWithUnits NumberWithUnits::operator--(int)
    {
        NumberWithUnits tmp(*this);
        setNumber(getNumber() - 1);
        return tmp;
    }
    NumberWithUnits NumberWithUnits::operator++(int)
    {
        NumberWithUnits tmp(*this);
        setNumber(getNumber() + 1);
        return tmp;
    }
    NumberWithUnits &NumberWithUnits::operator--()
    {
        this->_num -= 1;
        return *this;
    }
    NumberWithUnits &NumberWithUnits::operator++()
    {
        this->_num += 1;
        return *this;
    }

    ostream &operator<<(ostream &out, const NumberWithUnits &num)
    {
        out << num.getNumber() << "[" << num.getName() << "]";
        return out;
    }
    istream &operator>>(istream &in, NumberWithUnits &num)
    {
        double tmpNum = 0;
        in >> tmpNum;
        num.setNumber(tmpNum);
        string tmpStr;
        in >> tmpStr;
        tmpStr.erase(std::remove(tmpStr.begin(), tmpStr.end(), '['), tmpStr.end());
        tmpStr.erase(std::remove(tmpStr.begin(), tmpStr.end(), ']'), tmpStr.end());
        if (tmpStr.empty())
        {
            in >> tmpStr;
        }

        if (!num.leagalName(tmpStr))
        {
            throw "name exception";
        }
        num.setName(tmpStr);
        return in;
    }
    NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &num)
    {
        setNumber(getNumber() + convert(num.getNumber(), num.getName(), getName()));
        return *this;
    }
    NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &num)
    {
        setNumber(getNumber() - convert(num.getNumber(), num.getName(), getName()));
        return *this;
    }
    NumberWithUnits &NumberWithUnits::operator/=(const NumberWithUnits &num)
    {
        setNumber(getNumber() / convert(num.getNumber(), num.getName(), getName()));
        return *this;
    }
    NumberWithUnits &NumberWithUnits::operator*=(const NumberWithUnits &num)
    {
        setNumber(getNumber() * convert(num.getNumber(), num.getName(), getName()));
        return *this;
    }
    NumberWithUnits &NumberWithUnits::operator=(const NumberWithUnits &num)
    {
        setNumber(convert(num.getNumber(), num.getName(), getName()));
        return *this;
    }
    bool NumberWithUnits::operator<(const NumberWithUnits &num) const
    {
        // if (0 < _num - convert(num.getNumber(), num.getName(), getName()))
        // {
        //     return true;
        // }

        if (getName().compare(num.getName()) == 0)
        {
            if (_num < num._num)
            {
                return true;
            }
        }
        return false;
    }
    bool NumberWithUnits::operator<=(const NumberWithUnits &num) const
    {
        if (getName().compare(num.getName()) == 0)
        {
            if (_num <= num._num)
            {
                return true;
            }
        }
        return false;
    }
    bool NumberWithUnits::operator>(const NumberWithUnits &num) const
    {
        if (getName().compare(num.getName()) == 0)
        {
            if (_num > num._num)
            {
                return true;
            }
        }
        return false;
    }
    bool NumberWithUnits::operator>=(const NumberWithUnits &num) const
    {
        if (getName().compare(num.getName()) == 0)
        {
            if (_num >= num._num)
            {
                return true;
            }
        }
        return false;
    }
    bool NumberWithUnits::operator==(const NumberWithUnits &num) const
    {
        if (getName().compare(num.getName()) == 0)
        {
            if (num._num == _num)
            {
                return true;
            }
        }
        return false;
    }
    bool NumberWithUnits::operator!=(const NumberWithUnits &num) const
    {
        if (getName().compare(num.getName()) == 0)
        {
            if (num._num == _num)
            {
                return false;
            }
        }
        return true;
    }

    double NumberWithUnits::convert(double num, std::string from, std::string to)
    {
        return num; ////////////////////////
    }
    std::string NumberWithUnits::getName() const
    {
        return this->_name;
    }
    double NumberWithUnits::getNumber() const
    {
        return this->_num;
    }
    bool NumberWithUnits::leagalName(const std::string &name) const
    {
        return true;
    }

};