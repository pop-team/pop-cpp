/**
 * @author  clementval
 * @date    2012.09.04
 * This program tests marshalling and un-masrhalling of big amount of data
 */

#include "POPObject.ph"
#include <assert.h>

namespace {

//60 MiB
const int Size = 60 * 1024 * 1024;

char array[Size];

} //end of anonymous namespace

int main(int argc, char** argv) {
    try {
        cout << "Big data: Starting test..." << popcendl;

        for(int i = 0; i < Size; i++) {
            array[i] = 'a';
        }

        POPObject o;
        o.displayArray(Size, array);

        assert(array[2] == 'b');
        assert(array[5] == 'c');
        assert(array[10495910] == 'z');
        assert(array[60495998] == 'w');

        cout << "big data succeed !" << popcendl;
    } catch(POPException e) {
        printf("big data test failed: error no.%d, destroying objects:\n", e.Code());
        return 1;
    }
    printf("big data: test succeeded, destroying objects:\n");
    return 0;
}
