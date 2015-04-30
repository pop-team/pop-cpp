#include "pop_xmp_object.ph"
#include <stdio.h>

POPXMPObject::POPXMPObject() {
    printf("REMOTE OBJECT: Created successfully (rank=%d)\n", get_rank());
}

POPXMPObject::~POPXMPObject() {
}

void POPXMPObject::execute_xmp_1() {
    printf("REMOTE OBJECT: Execute XMP 1\n");

#pragma xmp

#ifdef _XCALABLEMP
    _XMP_init(NULL, NULL);
    _XMP_init_nodes_DYNAMIC_GLOBAL(&(_XMP_DESC_p), 1, (int*)(&(_XMP_NODES_SIZE_p)), (int*)(&(_XMP_NODES_RANK_p_0)));
    _XMP_init_template_FIXED(&(_XMP_DESC_t), 1, (long long)(0), (long long)(9));
    _XMP_init_template_chunk(_XMP_DESC_t, _XMP_DESC_p);
    _XMP_dist_template_BLOCK(_XMP_DESC_t, 0, 0);
    _XMP_init_array_desc(&(_XMP_DESC_a), _XMP_DESC_t, 1, 507, sizeof(int), (int)(0x00000000all));
    _XMP_align_array_BLOCK(_XMP_DESC_a, 0, 0, 0, &(_XMP_GTOL_temp0_a_0));
    _XMP_init_array_comm(_XMP_DESC_a, 0);
    _XMP_init_array_nodes(_XMP_DESC_a);
    _XMP_alloc_array((void**)(&(_XMP_ADDR_a)), _XMP_DESC_a, (unsigned long long*)(&(_XMP_GTOL_acc_a_0)));

    {
        int i;
        {
            int _XMP_loop_init_i;
            int _XMP_loop_cond_i;
            int _XMP_loop_step_i;
            _XMP_sched_loop_template_BLOCK(0, 10, 1, &(_XMP_loop_init_i), &(_XMP_loop_cond_i), &(_XMP_loop_step_i),
                                           _XMP_DESC_t, 0);

            for (i = _XMP_loop_init_i; i < _XMP_loop_cond_i; i += _XMP_loop_step_i) {
                (*(_XMP_M_GET_ADDR_E_1(_XMP_ADDR_a, i))) =
                    (_XMP_M_LTOG_TEMPLATE_BLOCK(i, 0, 10, _XMP_NODES_SIZE_p, _XMP_NODES_RANK_p_0));
            }
        }
        {
            int _XMP_loop_init_i;
            int _XMP_loop_cond_i;
            int _XMP_loop_step_i;
            _XMP_sched_loop_template_BLOCK(0, 10, 1, &(_XMP_loop_init_i), &(_XMP_loop_cond_i), &(_XMP_loop_step_i),
                                           _XMP_DESC_t, 0);
            for (i = _XMP_loop_init_i; i < _XMP_loop_cond_i; i += _XMP_loop_step_i) {
                printf("%d %d\n", *(_XMP_M_GET_ADDR_E_1(_XMP_ADDR_a, i)), xmp_node_num());
            }
        }
    }
#endif
}

void POPXMPObject::set_value(int val) {
    printf("REMOTE OBJECT(%d): Set Value %d\n", get_rank(), val);
}

void POPXMPObject::propagate_value(int val) {
    printf("REMOTE OBJECT(%d): Propagate Value %d\n", get_rank(), val);
}
