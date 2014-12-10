#ifdef _XCALABLEMP
typedef int _Bool;
extern "C" {
    //
#include <xmp.h>
#include "xmp_comm_macro.h"
#include "xmp_index_macro.h"
#include "xmp_func_decl.h"
}
static void * _XMP_DESC_p;
static int _XMP_NODES_SIZE_p;
static int _XMP_NODES_RANK_p_0;
static void * _XMP_DESC_t;

static void * _XMP_DESC_b;
static unsigned long long _XMP_GTOL_acc_b_0;
static unsigned long long _XMP_GTOL_acc_b_1;
static int _XMP_GTOL_temp0_b_0;

static void * _XMP_DESC_c;
static unsigned long long _XMP_GTOL_acc_c_0;
static unsigned long long _XMP_GTOL_acc_c_1;
static int _XMP_GTOL_temp0_c_0;


#endif

parclass XMPWorker {
public:
    classuid(2500);

    XMPWorker() @{ od.executable("./xmpworker.obj"); };
    ~XMPWorker();



    sync broadcast void init_xmp();
    sync broadcast void compute();


//  sync broadcast void distribute_a(int row, int length,[in, size=length] double* tmpa);
    sync seq void get_row_c(int row, int length, [out, size=length] double* tmpc);
private:
    double a[12][12];
    double * _XMP_ADDR_c;
    double * _XMP_ADDR_b;


};
