#pragma once

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <map>

namespace ariel
{
    static std::map<std::string, std::map<std::string, double>> unitMap; //global
    class NumberWithUnits
    {
    private:
        double _num;
        std::string _name;

    public:
        NumberWithUnits(double num, std::string const &name);
        NumberWithUnits(const NumberWithUnits &num);
        static void read_units(std::ifstream &units_file);

        NumberWithUnits operator-() const;
        NumberWithUnits operator+() const;
        NumberWithUnits operator+(const NumberWithUnits &num) const;
        NumberWithUnits operator+(double num) const;
        NumberWithUnits operator-(const NumberWithUnits &num) const;
        friend NumberWithUnits operator*(const NumberWithUnits &num, double x);
        friend NumberWithUnits operator*(double x, const NumberWithUnits &num);
        friend NumberWithUnits operator/(const double x, const NumberWithUnits &num);

        NumberWithUnits operator--(int);
        NumberWithUnits operator++(int);
        NumberWithUnits &operator--();
        NumberWithUnits &operator++();

        friend std::ostream &operator<<(std::ostream &out, const NumberWithUnits &num);
        friend std::istream &operator>>(std::istream &in, NumberWithUnits &num);

        NumberWithUnits &operator+=(const NumberWithUnits &num);
        NumberWithUnits &operator-=(const NumberWithUnits &num);
        NumberWithUnits &operator/=(const NumberWithUnits &num);
        NumberWithUnits &operator*=(const NumberWithUnits &num);
        NumberWithUnits &operator=(const NumberWithUnits &num);

        bool operator<(const NumberWithUnits &num) const;
        bool operator<=(const NumberWithUnits &num) const;
        bool operator>(const NumberWithUnits &num) const;
        bool operator>=(const NumberWithUnits &num) const;
        bool operator==(const NumberWithUnits &num) const;
        bool operator!=(const NumberWithUnits &num) const;

        static double convert(double num, std::string const &from, std::string const &to);
        void setNumber(const double x) { _num = x; }
        void setName(const std::string name)
        {
            _name = name;
        }
        std::string getName() const;
        double getNumber() const;
        static bool leagalName(const std::string &name);
    };
};