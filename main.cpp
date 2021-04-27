#include "NumberWithUnits.hpp"
#include <iostream>
using namespace ariel;
using namespace std;

int main(int argc, char const *argv[])
{

    NumberWithUnits x{1, "km"};
    NumberWithUnits y{999, "m"};
    NumberWithUnits z{100, "ton"};
    ifstream units_file{"filename1.txt"};
    x.read_units(units_file);
    cout << x.getName() << endl;
    cout<<"test: " << (y!=x ) << endl;
    //x.leagalName("");
    cout << x.getNumber() << endl;
    cout << y << endl;
    cout << "" << endl;
    cout << "" << endl;
    return 0;
}
