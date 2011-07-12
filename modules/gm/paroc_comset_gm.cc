
#include <time.h>
#include "paroc_comset_gm.h"
#include "paroc_combox_gm.h"

paroc_comset_gm::paroc_comset_gm():paroc_comset()
{}
paroc_comset_gm::~paroc_comset_gm()
{}
//Allows to define the next protocol instance to treat
paroc_combox* paroc_comset_gm::Wait(int timeout){

  int n = comboxArray.GetSize();
  
  clock_t endTime;
  endTime = clock () + (long int) (timeout * 0.1 * CLOCKS_PER_SEC);
  
  while((timeout==-1) || clock() < endTime){
    
    for(int i=0; i<n; i++){

      paroc_combox_gm *gm=(paroc_combox_gm *) comboxArray[i];

      if(gm->IsMsgReceived()){
	ready.AddTail((paroc_combox * &)gm);
      }
    }
  } 
  
  POSITION headPos = ready.GetHeadPosition();
  return ready.GetAt(headPos);
}
		
//Allows to add a protocol instance given in argument into the set
bool paroc_comset_gm::Add(paroc_combox *combox){
	
  int n=comboxArray.GetSize();
  for (int i=0;i<n;i++) if (combox==comboxArray[i]) return false;
  comboxArray.InsertAt(-1,combox);
  return true;
  	
}
		
//Allows to remove a protocol instance given in argument into the set
bool paroc_comset_gm::Remove(paroc_combox *combox){
	
  int i=0;
  while (i<comboxArray.GetSize()){
    if (comboxArray[i]==combox) {
      comboxArray.RemoveAt(i);
      break;
    } 
    else i++;
  }
  return true;
}
		
//Allows to know the size of the set
int paroc_comset_gm::GetSize(){
  return comboxArray.GetSize();
}

paroc_combox* paroc_comset_gm::RemoveAt(int i){
  
  paroc_combox * ptr = comboxArray[i];
  comboxArray.RemoveAt(i);
  return ptr;
  
}

paroc_combox* paroc_comset_gm::GetAt(int i){
  
  return comboxArray[i];

}
