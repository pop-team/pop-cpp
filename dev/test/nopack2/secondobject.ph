#ifndef SECONDOBJECT_PH_
#define SECONDOBJECT_PH_

/**
 * @author clementval
 * @date 2012.07.11
 * This program tests compilation without the @pack directive. Compilation should work and print a warning message.
 */

parclass SecondObject {
    classuid(1501);

public:
    SecondObject() @{ od.url("localhost"); };
    ~SecondObject();

    sync seq int getValue();

private:
    int value;

};


#endif /* SECONDOBJECT_PH_ */
