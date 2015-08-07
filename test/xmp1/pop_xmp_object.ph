/**
 * Test Case for XMP support in POP-C++
 * Include test about Parallel Object Group (POG)
 */

static void * _XMP_DESC_p;
static int _XMP_NODES_SIZE_p;
static int _XMP_NODES_RANK_p_0;
static void * _XMP_DESC_t;
static void * _XMP_DESC_a;
static unsigned long long _XMP_GTOL_acc_a_0;
static int _XMP_GTOL_temp0_a_0;

parclass POPXMPObject {
public:
    classuid(2000);
    POPXMPObject() @{ od.executable("./pop_xmp_object.obj"); };
    ~POPXMPObject();

    sync broadcast void execute_xmp_1();
    sync seq void set_value(int val);
    async broadcast void propagate_value(int val);

private:
    int * _XMP_ADDR_a;
};
