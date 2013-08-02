#include "xmpworker.ph"
#include <iostream>

XMPWorker::XMPWorker() 
{
  
}

XMPWorker::~XMPWorker()
{
#ifdef _XCALABLEMP
  _XMP_finalize();
#endif
}

void XMPWorker::init_xmp()
{
  std::cout << "Init XMP" << get_rank() << std::endl; 
#ifdef _XCALABLEMP
  _XMP_init(NULL, NULL);
  _XMP_init_nodes_DYNAMIC_GLOBAL(&(_XMP_DESC_p), 1, (int * )(&(_XMP_NODES_SIZE_p)), (int * )(&(_XMP_NODES_RANK_p_0)));
  _XMP_init_template_FIXED(&(_XMP_DESC_t), 1, (long long)(0), (long long)(11));
  _XMP_init_template_chunk(_XMP_DESC_t, _XMP_DESC_p);
  _XMP_dist_template_BLOCK(_XMP_DESC_t, 0, 0);
  _XMP_init_array_desc(&(_XMP_DESC_b), _XMP_DESC_t, 2, 514, sizeof(double), (int)(0x00000000cll), (int)(0x00000000cll));
  _XMP_align_array_BLOCK(_XMP_DESC_b, 0, 0, 0, &(_XMP_GTOL_temp0_b_0));
  _XMP_align_array_NOT_ALIGNED(_XMP_DESC_b, 1);
  _XMP_init_array_comm(_XMP_DESC_b, 0);
  _XMP_init_array_nodes(_XMP_DESC_b);
  _XMP_init_array_desc(&(_XMP_DESC_c), _XMP_DESC_t, 2, 514, sizeof(double), (int)(0x00000000cll), (int)(0x00000000cll));
  _XMP_align_array_BLOCK(_XMP_DESC_c, 0, 0, 0, &(_XMP_GTOL_temp0_c_0));
  _XMP_align_array_NOT_ALIGNED(_XMP_DESC_c, 1);
  _XMP_init_array_comm(_XMP_DESC_c, 0);
  _XMP_init_array_nodes(_XMP_DESC_c);

  _XMP_alloc_array((void * * )(&(_XMP_ADDR_b)), _XMP_DESC_b, (unsigned long long * )(&(_XMP_GTOL_acc_b_1)), (unsigned long long * )(&(_XMP_GTOL_acc_b_0)));
  std::cout << _XMP_GTOL_acc_b_1  << "/" << _XMP_GTOL_acc_b_0 << std::endl; 

  _XMP_alloc_array((void * * )(&(_XMP_ADDR_c)), _XMP_DESC_c, (unsigned long long * )(&(_XMP_GTOL_acc_c_1)), (unsigned long long * )(&(_XMP_GTOL_acc_c_0)));
  std::cout << _XMP_GTOL_acc_c_1  << "/" << _XMP_GTOL_acc_c_0 << std::endl; 
#endif
}


void XMPWorker::compute()
{

  std::cout << "compute" << get_rank() << std::endl; 
#ifdef _XCALABLEMP
  int i;
  { 
    int i = 0;
    for(; i < (12); i++) {
      {
        int j = 0;
        for(; j < (12); j++) {
          (a[i][j]) = (i + j);
        }
      }
    }
  } 
  {
    int _XMP_loop_init_i;
    int _XMP_loop_cond_i;
    int _XMP_loop_step_i;

    int i;
    _XMP_sched_loop_template_BLOCK(0, 12, 1, &(_XMP_loop_init_i), &(_XMP_loop_cond_i), &(_XMP_loop_step_i), _XMP_DESC_t, 0);
    for(i = _XMP_loop_init_i; i < _XMP_loop_cond_i; i += _XMP_loop_step_i) {
      {
        int j = 0;
        for(; j < (12); j++) {
          (*(_XMP_M_GET_ADDR_E_2(_XMP_ADDR_b, i, j, _XMP_GTOL_acc_b_0))) = ((_XMP_M_LTOG_TEMPLATE_BLOCK(i, 0, 12, _XMP_NODES_SIZE_p, _XMP_NODES_RANK_p_0)) * j);
        }
      }
    }
  }
  {
    int _XMP_loop_init_j;
    int _XMP_loop_cond_j;
    int _XMP_loop_step_j;
    int j;
    _XMP_sched_loop_template_BLOCK(0, 12, 1, &(_XMP_loop_init_j), &(_XMP_loop_cond_j), &(_XMP_loop_step_j), _XMP_DESC_t, 0);
    for(j = _XMP_loop_init_j; j < _XMP_loop_cond_j; j += _XMP_loop_step_j) {
      {
        int i = 0;
        for(; i < (12); i++) {
          {
            int k = 0;
            for(; k < (12); k++) {
              (*(_XMP_M_GET_ADDR_E_2(_XMP_ADDR_c, j, i, _XMP_GTOL_acc_c_0))) = ((*(_XMP_M_GET_ADDR_E_2(_XMP_ADDR_c, j, i, _XMP_GTOL_acc_c_0))) + ((a[k][i]) * (*(_XMP_M_GET_ADDR_E_2(_XMP_ADDR_b, j, k, _XMP_GTOL_acc_b_0)))));
            }
          }
        }
      }
    }
  }
  /*{
    int _XMP_loop_init_j;
    int _XMP_loop_cond_j;
    int _XMP_loop_step_j;

    int j;
    _XMP_sched_loop_template_BLOCK(0, 12, 1, &(_XMP_loop_init_j), &(_XMP_loop_cond_j), &(_XMP_loop_step_j), _XMP_DESC_t, 0);

    for(j = _XMP_loop_init_j; j < _XMP_loop_cond_j; j += _XMP_loop_step_j) {
      printf("\n");
      {
        int i = 0;
        for(; i < (12); i++) {
          printf("%8.2f  ", *(_XMP_M_GET_ADDR_E_2(_XMP_ADDR_c, j, i, _XMP_GTOL_acc_c_0)));
        }
      }
    }
  }*/
#endif
}

void XMPWorker::get_row_c(int row, int length, double* tmpc) {
#ifdef _XCALABLEMP
  for (int i = 0; i < 12; i++) {
    tmpc[i] = *(_XMP_M_GET_ADDR_E_2(_XMP_ADDR_c, row, i, _XMP_GTOL_acc_c_0));
  }
  /*memcpy((_XMP_M_GET_ADDR_E_2(_XMP_ADDR_c, row, 0, _XMP_GTOL_acc_c_0)), tmpc, sizeof(double) * length); 
  for (int i = 0; i < 12; i++) {
    printf("%8.2f  ", tmpc[i]);
  }
  printf("\n"); */
  

//  memcpy((_XMP_ADDR_c + row * sizeof(double)*length), tmpc, sizeof(double) * length); 
#endif
}

@pack(XMPWorker); 
