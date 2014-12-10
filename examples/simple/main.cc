


#include "integer.ph"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    try {
        Integer o1;
    } catch(POPException *e) {
        cout << "Exception occurs in application :" << endl;
        e->Print();
        delete e;
        return -1;
    }
    return 0;
}
