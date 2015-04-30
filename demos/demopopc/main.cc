#include "demopopc.ph"
#include <unistd.h>
int main(int argc, char** argv) {
    if (argc < 2 || atoi(argv[1]) == 0) {
        printf("Usage: popcrun obj.map %s NbObjects machine1, machine2, .... \n", argv[0]);
        return 0;
    } else {
        int nbObjects = atoi(argv[1]);
        POPCobject** objects = new POPCobject* [nbObjects];

        printf("\nSTART of %s program with %d objects\n", argv[0], nbObjects);

        for (int i = 0; i < argc - 2 && i < nbObjects; i++) {
            if (argv[i + 2][0] == '-') {
                objects[i] = new POPCobject(i + 1, 60, 40);
            } else {
                int node = atoi(argv[i + 2]);
                objects[i] = new POPCobject(i + 1, node);
            }
        }

        // The rest is created using node 0
        for (int i = argc - 2; i < nbObjects; i++) {
            objects[i] = new POPCobject(i + 1, 0);
        }

        // Send IDs to each other
        for (int i = 0; i < (nbObjects - 1); i++) {
            objects[i]->sendIDto(*(objects[i + 1]));
        }
        objects[nbObjects - 1]->sendIDto(*(objects[0]));
        //      objects[nbObjects-1]->wait(2);

        sleep(2);
        for (int i = 0; i < nbObjects; i++) {
            delete objects[i];
        }
        delete objects;
    }
    printf("\nEND of %s program\n", argv[0]);
    return 0;
}
