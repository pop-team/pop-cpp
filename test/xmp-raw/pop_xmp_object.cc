#include "pop_xmp_object.h"
#include "POPString.h"

#include <stdio.h>

POPXMPObject::POPXMPObject()
{
  od.executable("./pop_xmp_object.obj"); 
}

POPXMPObject::~POPXMPObject()
{
  printf("POPXMP object terminated\n"); 
}


void POPXMPObject::_popc_constructor()
{
//pop_mutex_locker __paroc_lock(_pop_imutex);
printf("_popc_construct\n");
  pop_connection* _popc_connection = _popc_combox->get_connection();
  _popc_buffer->Reset();
  pop_message_header _popc_message_header(CLASSUID_POPXMPObject, 10, 21, "POPXMPObject");
  _popc_buffer->SetHeader(_popc_message_header); 

  popc_send_request(_popc_buffer, _popc_connection); 
  popc_recv_response(_popc_buffer, _popc_connection);
  
  _popc_buffer->Reset();
  _popc_connection->reset();   
}

void POPXMPObject::construct_remote_object()
{
  _popc_constructor();
}

// Collective method
void POPXMPObject::execute_xmp_1()
{
  printf("Will call the execute_xmp_1() method\n"); 
  pop_connection* _popc_connection = _popc_combox->get_connection(); 
  _popc_buffer->Reset();
  pop_message_header _popc_message_header(CLASSUID_POPXMPObject, 13, 0, "execute_xmp_1"); 
  _popc_buffer->SetHeader(_popc_message_header); 
  popc_send_request(_popc_buffer, _popc_connection); 
  popc_recv_response(_popc_buffer, _popc_connection);
  _popc_buffer->Reset();
  _popc_connection->reset(); 
}


// Non-collective method call
void POPXMPObject::set_value(int val)
{
  pop_connection* _popc_connection = _popc_combox->get_connection(); 
  _popc_buffer->Reset();
  pop_message_header _popc_message_header(CLASSUID_POPXMPObject, 9, 0, "set_non_collective_rank"); 
  _popc_buffer->SetHeader(_popc_message_header);
  _popc_buffer->Push("rank", "int", 1); 
  _popc_buffer->Pack(&_popc_default_rank_for_single_call, 1); 
  _popc_buffer->Pop(); 
  popc_send_request(_popc_buffer, _popc_connection); 
  _popc_buffer->Reset();
  
  pop_message_header _popc_message_header_call(CLASSUID_POPXMPObject, 14, 0, "set_value"); 
  _popc_buffer->SetHeader(_popc_message_header_call);
  _popc_buffer->Push("val", "int", 1); 
  _popc_buffer->Pack(&val, 1); 
  _popc_buffer->Pop(); 
  popc_send_request(_popc_buffer, _popc_connection); 
  popc_recv_response(_popc_buffer, _popc_connection);  
  _popc_buffer->Reset();
  
  _popc_connection->reset(); 


}


POPXMPObject& POPXMPObject::operator[] (const int index)
{
  set_default_rank(index);
  return (*this); 
}	  
