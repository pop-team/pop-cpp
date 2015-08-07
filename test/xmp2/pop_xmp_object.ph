/**
 * Test Case for XMP support in POP-C++
 * Include test about Parallel Object Group (POG)
 */


parclass POPXMPObject {
public:
    classuid(2000);
    POPXMPObject() @{ od.executable("./pop_xmp_object.obj"); };
    ~POPXMPObject();

    sync broadcast void execute_xmp_1();
    sync seq void set_value(int val);
    async broadcast void propagate_value(int val);
};
