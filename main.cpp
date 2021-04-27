#include "NumberWithUnits.hpp"
#include <iostream>
using namespace ariel;
using namespace std;

int main(int argc, char const *argv[])
{

    NumberWithUnits x{1, "km"};
    ifstream units_file{"filename.txt"};
    x.read_units(units_file);
    cout << x.getName() << endl;
    cout << x.getNumber() << endl;
    //x.leagalName("");
    cout << (unitMap.begin() == unitMap.end()) << endl;
    cout << x.convert(1,"km","ce") << endl;
    cout << "" << endl;
    cout << "" << endl;
    cout << "" << endl;
    cout << "" << endl;
    return 0;
}
