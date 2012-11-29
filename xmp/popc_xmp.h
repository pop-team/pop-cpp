/**
 * @author Valentin Clement
 * @date 2012/11/29
 * @brief Template class to integrate support for parallel class using XMP 
 * 
 *
 */


#ifndef POPC_XMP_H_
#define POPC_XMP_H_

#include <mpi.h>
#include <string.h>

#include "popc_combox_uds.h"
#include "paroc_system.h"



template<class T> class POPXMP
{
public:
  POPXMP();
  POPXMP(int nb_node);
  ~POPXMP();
  
  // XMP control methods
  bool initialize(int nb_node); 
  bool finalize();
  
  // Utility method to access useful information
  int get_nb_node(); 
  bool is_initialized();
  bool is_finalized();  
  

private: 
  // Internal variable to manage the group of XMP parallel objects
  bool _popc_xmp_is_initialized;
  bool _popc_xmp_is_finalized;

  // Reference to the parallel object belonging to this group
  T* _popc_xmp_parallel_object;
  // Number of parallel object belonging to this group
  int _popc_xmp_nb_parallel_object;

  // Internal method controlling the live of XMP parallel object
  bool _popc_xmp_allocate_parallel_object(T *&objectgroup, int nb_node);
  bool _popc_xmp_terminate_parallel_object(T *&objectgroup, int nb_node);
  
};


template<class T>
POPXMP<T>::POPXMP() : _popc_xmp_nb_parallel_object(0), _popc_xmp_parallel_object(NULL), _popc_xmp_is_initialized(false), _popc_xmp_is_finalized(false)
{
}


template<class T>
POPXMP<T>::POPXMP(int nb_node) : _popc_xmp_nb_parallel_object(0), _popc_xmp_parallel_object(NULL), _popc_xmp_is_initialized(false), _popc_xmp_is_finalized(false)
{
  if(initialize(nb_node)) {
    printf("POPXMP: initialization done with success\n"); 
  } else {
    printf("POPXMP: initialzation failed\n"); 
  }

}

template<class T>
POPXMP<T>::~POPXMP()
{
  if(!is_finalized()) {
    finalize();
  }
}

/**
 * Initialized a group of nb_node parallel object supporting XMP
 * @return TRUE if the parallel objects were allocated successfully. FALSE in any other cases. 
 */
template<class T>
bool POPXMP<T>::initialize(int nb_node)
{
  if(is_initialized()) {
    return false;
  }

  if(nb_node <= 0) {
    return false;
  }

  T tmp_object;
  const char* class_name = tmp_object.ClassName();

  printf("POPXMP: initialize\n"); 

  POPString codefile;
  tmp_object.od.getExecutable(codefile); 

  if(codefile.Length() <= 0) {
    printf("POP-C++ Error: Cannot allocate group of objects because executbale is not specified\n"); 
    return false;
  }


  _popc_xmp_parallel_object = NULL;
  

  // Contact the local POP-C++ MPI Interconnector to create XMP process
  printf("POPXMP: Will initialized %d XMP process of type %s\n", nb_node, class_name);   

  int rank = paroc_system::popc_local_mpi_communicator_rank;
  printf("POPXMP: Contact POP-C++ MPI Interconnector %d to create the process\n", rank); 


  char* local_interconnector_address = new char[15];
  snprintf(local_interconnector_address, 15, "uds_%d.0", rank);  

  paroc_combox_factory* combox_factory = paroc_combox_factory::GetInstance();
  if(combox_factory == NULL) {
    paroc_exception::paroc_throw(POPC_NO_PROTOCOL, "ComboxFactory NULL"); 
  }

  paroc_combox* allocating_combox = combox_factory->Create("uds"); 
  if(allocating_combox == NULL) {
    paroc_exception::paroc_throw(POPC_NO_PROTOCOL, "Combox NULL"); 
  }

  paroc_buffer* allocating_buffer = allocating_combox->GetBufferFactory()->CreateBuffer();
  
  if(!allocating_combox->Create(local_interconnector_address, false)) {
    paroc_exception::paroc_throw(POPC_NO_PROTOCOL, "Can't connect to local interconnector"); 
  }

  if(!allocating_combox->Connect(local_interconnector_address)) {
    paroc_exception::paroc_throw(POPC_NO_PROTOCOL, "Can't connect to local interconnector"); 
  }

  delete local_interconnector_address; 

  paroc_message_header header(0, 210000, INVOKE_SYNC, "_allocation"); 
  allocating_buffer->Reset();
  allocating_buffer->SetHeader(header); 

  // Prepare information for the allocation
  POPString objectname(class_name); 
  allocating_buffer->Push("objectname", "POPString", 1);
  allocating_buffer->Pack(&objectname, 1); 
  allocating_buffer->Pop();

  allocating_buffer->Push("codefile", "POPString", 1);
  allocating_buffer->Pack(&codefile, 1); 
  allocating_buffer->Pop();

  allocating_buffer->Push("objectnb", "int", 1);
  allocating_buffer->Pack(&nb_node, 1); 
  allocating_buffer->Pop();


  paroc_connection* connection = allocating_combox->get_connection();
  
  if(!allocating_buffer->Send((*allocating_combox), connection)) {
    paroc_exception::paroc_throw_errno();
  }



  // Getting information for the allocation process
  if(!allocating_buffer->Recv((*allocating_combox), connection)) {
    paroc_exception::paroc_throw_errno();
  }
  paroc_buffer::CheckAndThrow(*allocating_buffer); 

  POPString objectaddress;
  allocating_buffer->Push("objectaddress", "POPString", 1);
  allocating_buffer->UnPack(&objectaddress, 1); 
  allocating_buffer->Pop();

  printf("POPXMP: allocation return %s\n", objectaddress.GetString()); 
 
  allocating_buffer->Destroy();
  allocating_combox->Close();

  _popc_xmp_is_initialized = true;
  return true; 
}

/**
 * Terminate all the parallel objects belonging to this group
 * @return TRUE if the termination is done successfully. FALSE if the termination encountered a 
 * problem or the parallel objects were already finalized. 
 */
template<class T>
bool POPXMP<T>::finalize()
{
  if(is_finalized()) {
    return false;
  }
 

  _popc_xmp_is_finalized = true; 
}

/**
 * Get the number of node to run XMP parallel object
 * @return The number of node to run XMP parallel object
 */
template<class T> 
int POPXMP<T>::get_nb_node()
{
  return _popc_xmp_nb_parallel_object;
}


/**
 * Check if the XMP parallel objects are already initialized
 * @return TRUE is the XMP parallel objects have been initialized. FALSE in any other cases. 
 */
template<class T> 
bool POPXMP<T>::is_initialized()
{
  return _popc_xmp_is_initialized;  
}

/**
 * Check if the XMP parallel objects are already initialized
 * @return TRUE is the XMP parallel objects have been initialized. FALSE in any other cases. 
 */
template<class T> 
bool POPXMP<T>::is_finalized()
{
  return _popc_xmp_is_finalized; 
}

#endif /* POPC_XMP_H_ */
