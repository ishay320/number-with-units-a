#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include "NumberWithUnits.hpp"
#include <algorithm>
#include <map>
using namespace std;
#define EPS 0.00001
namespace ariel
{
    NumberWithUnits::NumberWithUnits(double num, string name)
    {
        if (!leagalName(name))
        {
            throw invalid_argument(name + " is not leagal name");
        }

        _num = num;
        _name = name;
    }
    NumberWithUnits::NumberWithUnits(const NumberWithUnits &num)
    {
        _num = num._num;
        _name = num._name;
    }

    void update_map(const string &src, const string &dest)
    {
        for (auto &unit : unitMap[dest])
        {
            if (unit.first != src)
            {
                double new_size = unitMap[src][dest] * unit.second;
                unitMap[src][unit.first] = new_size;
                unitMap[unit.first][src] = 1 / new_size;
            }
        }
    }
    void NumberWithUnits::read_units(std::ifstream &units_file)
    {
        string dump, strA, strB;
        double size1 = 0, size2 = 0;
        while (units_file >> size1 >> strA >> dump >> size2 >> strB)
        {
            unitMap[strA][strB] = size2;
            unitMap[strB][strA] = 1 / size2;
            update_map(strA, strB);
            update_map(strB, strA);
        }
    }

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
    NumberWithUnits NumberWithUnits::operator+(double num) const
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
            throw invalid_argument(tmpStr + " is not leagal name");
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

        if (0 > _num - convert(num.getNumber(), num.getName(), getName()))
        {
            return true;
        }

        return false;
    }
    bool NumberWithUnits::operator<=(const NumberWithUnits &num) const
    {

        if (0 >= (_num - convert(num.getNumber(), num.getName(), getName())))
        {
            return true;
        }

        return false;
    }
    bool NumberWithUnits::operator>(const NumberWithUnits &num) const
    {
        if (0 < _num - convert(num.getNumber(), num.getName(), getName()))
        {
            return true;
        }
        return false;
    }
    bool NumberWithUnits::operator>=(const NumberWithUnits &num) const
    {
        if (0 <= _num - convert(num.getNumber(), num.getName(), getName()))
        {
            return true;
        }
        return false;
    }
    bool NumberWithUnits::operator==(const NumberWithUnits &num) const
    {

        if (EPS > _num - convert(num.getNumber(), num.getName(), getName()) &&
            -EPS < _num - convert(num.getNumber(), num.getName(), getName()))
        {
            return true;
        }

        return false;
    }
    bool NumberWithUnits::operator!=(const NumberWithUnits &num) const
    {
        return !((*this) == num);
    }

    double NumberWithUnits::convert(double num, std::string from, std::string to)
    {
        if (from != to && unitMap[from].find(to) == unitMap[from].end())
        {
            throw invalid_argument(from + " ->" + to + " dont exist in data ");
        }
        if (from == to)
        {
            return num;
        }
        return num * unitMap[from][to];
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

        return (unitMap.find(name) != unitMap.end());
    }

};