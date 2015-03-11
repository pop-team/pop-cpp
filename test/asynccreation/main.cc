#include "POPObject.ph"
#include <unistd.h>

/**
 * @author  clementval
 * @date    2012.08.22
 * This program tests asynchronous parallel object allocation
 */
int main(int argc, char** argv) {
    try {
        printf("Asynchronous allocation of parallel object\n");
        printf("Before creating POPObject o1\n");
        POPObject o1;
        printf("Before creating POPObject o2\n");
        POPObject o2;
        printf("Before creating POPObject o3\n");
        POPObject o3;
        printf("Before creating POPObject o4\n");
        POPObject o4;
        printf("Before creating array of POPObject\n");
        //Create useless objects to make sure destructor is
        //synchronized
        POPObject oo[10];
        printf("Before calling method 1 on POPObject o1\n");
        o1.firstMethod();
        printf("Before calling method 1 on POPObject o2\n");
        o2.firstMethod();
        printf("Before calling method 1 on POPObject o3\n");
        o3.firstMethod();
        printf("Before calling method 2 on POPObject o1\n");
        o1.secondMethod();
        printf("Before calling method 2 on POPObject o2\n");
        o2.secondMethod();
        printf("Before calling method 2 on POPObject o3\n");
        o3.secondMethod();
        printf("Before calling method 2 on POPObject o4\n");
        o4.secondMethod();
        printf("Method with void parameter: test succeeded, destroying objects ...\n");
    } catch(POPException& e) {
        printf("Method with void parameter: test failed, error no.%d, destroying objects:\n", e.Code());
        return 1;
    } catch(std::exception& e) {
        cout << e.what() << popcendl;
        return 1;
    }
    return 0;
}
