#include <iostream>
#include "Management.h"

using namespace std;

int main() {
    Management management;
    while (management.menu() != 0)
        cout << endl;
    return 0;
}
