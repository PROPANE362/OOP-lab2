#include <iostream>
#include "Three.h"
using namespace std;

int main() {
    Three a("210");
    Three b("12");
    
    cout << "Chislo a: " << a.toString() << endl;
    cout << "Chislo b: " << b.toString() << endl;
    cout << endl;

    Three sum = a.add(b);
    cout << "a + b = " << sum.toString() << endl;

    Three diff = a.subtract(b);
    cout << "a - b = " << diff.toString() << endl;
    cout << endl;

    cout << "a > b: " << (a.isGreater(b) ? "y" : "n") << endl;
    cout << "a < b: " << (a.isLess(b) ? "y" : "n") << endl;
    cout << "a == b: " << (a.isEqual(b) ? "y" : "n") << endl;
    cout << endl;

    Three c = a.copy();
    cout << "Kopiya a: " << c.toString() << endl;
    cout << "c == a: " << (c.isEqual(a) ? "y" : "n") << endl;
    cout << endl;

    Three d{1, 2, 0};
    cout << "Chislo iz spiske {1, 2, 0}: " << d.toString() << endl;

    Three e(5, 2);
    cout << "Chislo iz 5 dvoek: " << e.toString() << endl;

    cout << endl;
    cout << "Thats it!!!!" << endl;

    return 0;
}
