#include "POPObject.ph"
#include <unistd.h>

int main(int argc, char** argv) {
    try {
        printf("UDS test\n");

        POPObject o1;
        POPObject o2;

        o1.firstMethod();
        o2.secondMethod();
        o1.secondMethod();
        o2.firstMethod();
    } catch(POPException& e) {
        printf("UDS: test failed, error no.%d, destroying objects:\n", e.Code());
        return 1;
    } catch(std::exception& e) {
        cout << "UDS: test failed" << e.what() << popcendl;
        return 1;
    }

    return 0;
}
