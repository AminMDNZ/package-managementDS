#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <functional>

#include "DS.h"
#include "package.h"
#include "pgManage.h"

using namespace std;

int main() {
    srand(time(0));
    pgmanage p;
    p.man();
    return 0;
}
