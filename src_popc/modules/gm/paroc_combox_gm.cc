#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "gm.h"
#include "paroc_combox_gm.h"

paroc_combox_gm::paroc_combox_gm(paroc_protocol_gm_factory *fact): paroc_combox(fact){}

paroc_combox_gm::~paroc_combox_gm(){

  /* Exit GM API */
  gm_finalize();
}
		
/*
bool paroc_combox_gm::Create(){
	
  Create(DEFAULT_GM_PORT);
	
}
*/

bool paroc_combox_gm::Create(int portNum){
	
  int i=0,maxi=0;
  gm_status_t status;
  
  /* Init GM API */
  status = gm_init();
  if (status != GM_SUCCESS) 
    {
      fprintf(stdout,"GM init failed");
      return false;
    }

  if(portNum != 0)
    {
      //Try to open the GM specified port...
      printf("Trying to open the specified port: %i\n", portNum);
      status = gm_open (&gm_port, KERNEL_GM_BOARD, portNum, "ParoC++ GM",  (enum gm_api_version) GM_API_VERSION_1_0);
      if (status != GM_SUCCESS){
	printf("Cannot open the specified port: %i\n", portNum);
	return false;
      }
    }
  else
    {
      
      int gm_num_port = gm_num_ports(gm_port);
      int port=DEFAULT_GM_PORT;

      for(int i=0; i<gm_num_port; i++)
	{
	  if(port==GM_INTERNAL_USE_NUMBER || port==GM_MAPPER_PORT_NUMBER || port==GM_ETHERNET_EMULATION_PORT_NUMBER) continue;

	  printf("Try to open the port: %i\n", port);
	  status = gm_open (&gm_port, KERNEL_GM_BOARD, port, "ParoC++ GM",  (enum gm_api_version) GM_API_VERSION_1_0);
	  if (status == GM_SUCCESS) break;
	  else
	    { 
	      if(status==GM_BUSY)
		{
		  
		  printf("The port %i is busy...\n", port);
		}
	      else
		{
		  gm_perror("Gm Failed to open port",status);
		  return false;	
		}
	    }
	  port=(port+1)%gm_num_port;
	}
    }

  if(status!=GM_SUCCESS)
    {
      gm_perror("GM Failed to open port: No more available port\n", status);
      return false;
    }

  status = gm_get_node_id(gm_port, &localNodeID);
  
  if (status!=GM_SUCCESS)
    {
      gm_perror("Unable to get Local Node Id\n",status);
      return false;
    }
  
  nSendTokens=gm_num_receive_tokens(gm_port);
  nRecvTokens=gm_num_send_tokens(gm_port);
  
  printf("#Recv Tokens %d Send Tokens %d\n",nRecvTokens,nSendTokens);
  
  /* provide recv buffer space */
  maxi=(nRecvTokens <= MAX_RECV_BUFFERS)? nRecvTokens:MAX_RECV_BUFFERS; 
  nRecvTokens=maxi;
  for (i=0; i < maxi; i++) 
    {
      gm_recv_buffer[i] = gm_dma_calloc (gm_port, 1,MSG_SIZE);
      if (!gm_recv_buffer[i])
	{
	  gm_perror ("Could not allocate recv buffer.", GM_OUT_OF_MEMORY);
	  return false;
	}
      gm_provide_receive_buffer_with_tag(gm_port, gm_recv_buffer[i],gm_log2_roundup(MSG_SIZE), GM_LOW_PRIORITY,0);
    }	
  
  maxi=(nSendTokens <= MAX_SEND_BUFFERS)?nSendTokens:MAX_SEND_BUFFERS; 
  nSendTokens=maxi;
  for (i=0; i < maxi; i++)
    {
      gm_send_buffer[i].data=NULL;
      gm_send_buffer[i].data = gm_dma_calloc(gm_port, 1,MSG_SIZE);
      gm_send_buffer[i].state=BUFFER_FREE;
      
      if (!gm_send_buffer[i].data)
	{
	  gm_perror ("Could not allocate send buffers.",GM_OUT_OF_MEMORY);
	  return false;
	}
    }
  
  nNextSendBuffer = 0;
  nLastFreedSendBuffer = -1;
  return true;

}

paroc_combox * paroc_combox_gm::Accept(int timeout)
{

  gm_connect_msg msg;
  int readResult = Recv((char *)&msg, sizeof(msg));
  if(readResult != sizeof(msg))
    {
      printf("in Accept() : Cannot read !!!\n");
      return NULL;
    }
  printf("in Accept() : Connection received\n");
  printf("in Accept() : Client Node ID: %i - Port ID: %i\n", msg.nodeID, msg.portID);
 
  paroc_combox_gm * gm_combox=(theFactory==NULL)? new paroc_combox_gm(NULL) : (paroc_combox_gm *)theFactory->CreateCombox();
  gm_combox->Create(0);
  gm_combox->setDestNodeID(msg.nodeID);
  gm_combox->setDestPortID(msg.portID);
  int newPort = gm_combox->GetPort();

  printf("In Accept - Port server side : %i\n", newPort);  
  int writeResult = gm_combox->Send((char *)&newPort, sizeof(newPort));
  if(writeResult!=sizeof(newPort))
    {
      printf("In Accept() : Cannot write !!!\n");
      return NULL;
    }
  return gm_combox;

}

bool paroc_combox_gm::Listen(int queueLength){} 

bool paroc_combox_gm::Connect(const char* accesspoint, int timeout){

  gm_connect_msg msg;
  msg.nodeID=localNodeID;
  msg.portID=localPortID;
  GetNodeAndPort(accesspoint, &destNodeID, &destPortID);
  int writeResult=Send((char *)&msg, sizeof(msg));
  if(writeResult!=sizeof(msg))
    {
      printf("In Connect() : Cannot write !!!\n");
      return false;
    }

  int readResult=Recv((char *)&destPortID, sizeof(int));
  if(readResult != sizeof(msg))
    {
      printf("in Connect() : Cannot read !!!\n");
      return false;
    }
  return true;
}

int paroc_combox_gm::Recv(char * msg, int msgLength){
  
  gm_recv_event_t *event;
  void *buffer;
  unsigned int size;
  int messages_expected = 1;
  unsigned int len;
  void * message;
  
  while(messages_expected > 0){
    
    event = gm_receive (gm_port);
    
    //	    fprintf(stdout,"Received an Event \n");
    switch (GM_RECV_EVENT_TYPE(event)){
    case GM_RECV_EVENT:
    case GM_PEER_RECV_EVENT:
    case GM_FAST_PEER_RECV_EVENT:
      len=gm_ntoh_u32(event->recv.length);
      memcpy(msg, gm_ntohp(event->recv.message), len);
      
      messages_expected--;
      /* Return the buffer for reuse */
      buffer = gm_ntohp (event->recv.buffer);
      size = (unsigned int)gm_ntoh_u8 (event->recv.size);
      gm_provide_receive_buffer (gm_port, buffer, gm_log2_roundup(MSG_SIZE),
				 GM_LOW_PRIORITY);
      break;
      
    case GM_NO_RECV_EVENT:
      break;
      
    default:
      gm_unknown (gm_port, event);	/* gm_unknown calls the callback */
    }
  }
}


int paroc_combox_gm::Send(const char *msg, int len){
  
  printf("Send\n");
  gm_recv_event_t *event;
  void *sendBuffer=NULL;
  int expected_callbacks=0;
  gm_status_t status;
  
  /* Buffers are preallocated to CACTUS_MSG_SIZE other buffers need to be handled */
  nNextSendBuffer = (nNextSendBuffer + 1) % nSendTokens;
  
  printf("Send2\n");
  
  
  if(gm_send_buffer[nNextSendBuffer].state != BUFFER_FREE){
    
    while(nNextSendBuffer < nSendTokens){
      nNextSendBuffer=(nNextSendBuffer+1) % nSendTokens;
      if(gm_send_buffer[nNextSendBuffer].state == BUFFER_FREE)
	break;
    }
    
    if(nNextSendBuffer==nSendTokens && gm_send_buffer[nNextSendBuffer].state==BUFFER_IN_USE){
      fprintf(stdout,"Not enough Tokens for send \n");
      return -1;
    }
  }
  
  printf("Send3\n");
  
  sendBuffer=gm_send_buffer[nNextSendBuffer].data;
  
  printf("Send4\n");
  printf("Msg: %s\n", (char *) msg);
  printf("Len: %i\n", strlen((char *) msg)+1);
  
  
  memcpy(gm_send_buffer[nNextSendBuffer].data,msg,len);
  
  printf("Send5\n");
  
  gm_printf("DESTINATION : Node=%i ;Port=%i", destNodeID, destPortID);
  
  gm_send_with_callback(gm_port,sendBuffer,gm_log2_roundup(MSG_SIZE),len,GM_LOW_PRIORITY,destNodeID,destPortID,send_callback,&gm_send_buffer[nNextSendBuffer]);
  
  fprintf(stdout,"Send-Msg Sent Message successfully\n");
  while (1){
    event = gm_receive (gm_port);
    
    switch (GM_RECV_EVENT_TYPE(event))
      {
      case GM_RECV_EVENT:
      case GM_PEER_RECV_EVENT:
      case GM_FAST_PEER_RECV_EVENT:
	gm_printf ("[send] Receive Event (UNEXPECTED)\n");
	status = GM_FAILURE; /* Unexpected incoming message */
	return -1;
	
      case GM_NO_RECV_EVENT:
	break;
	
      default:
	gm_unknown (gm_port, event);	/* gm_unknown calls the callback */
	return 0;
      }
  }
  
  return (GM_SUCCESS);
}

bool paroc_combox_gm::IsMsgReceived(){
  
  gm_recv_event_t *event;
  event = gm_receive (gm_port);
  switch (GM_RECV_EVENT_TYPE(event))
    {
    case GM_RECV_EVENT:
    case GM_PEER_RECV_EVENT:
    case GM_FAST_PEER_RECV_EVENT:
      return true;
      
    case GM_NO_RECV_EVENT:
      return false;
      
    default:
      return false;
    }
}

/* This function is called inside gm_unknown() when there is a callback
   ready to be processed.  It tells us that a send has completed, either
   successfully or with error. */
static void send_callback (struct gm_port *port, void *the_context,
		  gm_status_t the_status)
{
  /* One pending callback has been received */
  struct _gm_send_buffer *sbuffer =(struct _gm_send_buffer*) the_context;

  sbuffer->state=BUFFER_FREE;

  //fprintf(stdout,"Sent Message successfully\n");
  switch (the_status)
    {
    case GM_SUCCESS:
      break;

    case GM_SEND_DROPPED:
      gm_printf ("**** Send dropped!\n");
      break;

    default:
      gm_perror ("Send completed with error", the_status);
    }
   return ;
}

void paroc_combox_gm::Close(){

}

void paroc_combox_gm::Shutdown(int dir){}

bool paroc_combox_gm::GetSrcAccesspoint(paroc_string & accesspoint){

  char s[256];
  sprintf(s, "%u:%u", localNodeID, localPortID);
  accesspoint=s;
  return true;
}

/*
const char* paroc_combox_gm::GetDestAccesspoint(){
  
  char * s = (char*) malloc(50);
  sprintf(s, "%u:%u", destNodeID, destPortID);
  return s;
}
*/


bool paroc_combox_gm::GetProtocolName(paroc_string & protocolName){
  
  protocolName="gm";
  return true;
  
}

int paroc_combox_gm::GetDefaultPort(){
  return 0; //NOT USED WITH GM
}

int paroc_combox_gm::GetPort(){
  return localPortID;
}

void paroc_combox_gm::setDestNodeID(unsigned int nodeID)
{
  destNodeID=nodeID;
}

unsigned int paroc_combox_gm::getDestNodeID()
{
  return destNodeID;
}

void paroc_combox_gm::setDestPortID(unsigned int portID)
{
  destPortID = portID;
}
unsigned int paroc_combox_gm::getDestportID()
{
  return destPortID;
}


void paroc_combox_gm::GetNodeAndPort(const char* accesspoint, unsigned int* node, unsigned int* port){
  
  char * tempAccesspoint;
  char * nodeStr;
  char * portStr;
  int len = strlen(accesspoint);
  
  tempAccesspoint = (char *) malloc(len);
  memcpy(tempAccesspoint, accesspoint, len);
  
  nodeStr=strtok(tempAccesspoint, ":");
  *node=atoi(nodeStr);
  
  portStr=strtok(NULL, ":");
  *port=atoi(portStr);	
}

