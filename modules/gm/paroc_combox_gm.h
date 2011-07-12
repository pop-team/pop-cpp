#ifndef _PAROC_COMBOX_GM_H
#define _PAROC_COMBOX_GM_H

#include <stdio.h>
#include "paroc_combox.h"
#include "paroc_protocol_gm_factory.h"
#include "paroc_string.h"
#include "gm.h"

/*! \def KERNEL_GM_BOARD
 *  
 * 	This macro define the GM board to use
 */
#define KERNEL_GM_BOARD 0 

#define KERNEL_GM_PORT 2

/*! \def DEFAULT_GM_PORT
 *  
 * 	This macro define the default GM port 
 */
#define DEFAULT_GM_PORT 2

/*! \def GM_INTERNAL_USE_NUMBER
 *  
 * 	This macro define the GM port used by the GM system. This port cannot be used by the user!
 */
#define GM_INTERNAL_USE_NUMBER 0

/*! \def GM_MAPPER_PORT_NUMBER
 *  
 * 	This macro define the GM port used by the GM mapper. This port cannot be used by the user!
 */
#define GM_MAPPER_PORT_NUMBER 1

/*! \def GM_ETHERNET_EMULATION_PORT_NUMBER
 *  
 * 	This macro define the GM port used by the GM ethernet emulation. This port cannot be used by the user!
 */
#define GM_ETHERNET_EMULATION_PORT_NUMBER 3

/*! \def MAX_RECV_BUFFERS
 *  
 * 	This macro define the number of receive buffers to use.
 */
#define MAX_RECV_BUFFERS 3

/*! \def MAX_SEND_BUFFERS
 *  
 * 	This macro define the number of send buffers to use.
 */
#define MAX_SEND_BUFFERS 3

/*! \def MSG_SIZE
 *  
 * 	This macro define the maximum size of messages
 */
#define MSG_SIZE  16384 //2^14

/*! \def BUFFER_IN_USE
 *  
 * 	This macro define that the buffer is actually in use
 */
#define BUFFER_IN_USE 1

/*! \def BUFFER_FREE
 *  
 * 	This macro define that the buffer is free
 */
#define BUFFER_FREE 0

struct _gm_send_buffer{
	void *data;
	int state;
};

typedef struct{
	unsigned int nodeID;
	unsigned int portID;	
}gm_connect_msg;



static void send_callback (struct gm_port *port, void *the_context,gm_status_t the_status);

/**
 * Class implementing the GM protocol
 */
class paroc_combox_gm:public paroc_combox{
public:

	/**
	 * Class constructor
	 */
	paroc_combox_gm(paroc_protocol_gm_factory * fact);
	/**
	 * Class destructor
	 */
	~paroc_combox_gm();
	
	/**
	 * Opens a GM port and allocate send and receive buffers.
	 * This method try to open a port with the default port number 
	 */
	//bool Create();
	
	/**
	 * Allows to create a new instance on the specified port number
	 * 
	 * @param int Port number
	 */
	virtual bool Create(int port=0);
	
	/**
	 * Allows to accept a new connection on the combox in argument
	 * 
	 * @param &combox A paroc_combox implementation
	 */
	virtual paroc_combox* Accept(int timeout=0);
	
	/**
	 * Allows to define the max number of connexion at same time.
	 * Not used with GM
	 */
	virtual bool Listen(int queueLength=0);
	
	/**
	 * Allows to connect to a accesspoint(url:port)
	 * 
	 * @param accesspoint Accesspoint to a resource
	 */
	virtual bool Connect(const char* url, int timeout=0);
	
	/**
	 * Allows to receive data
	 * 
	 * @param s A pointer to an allocate place
	 * @param length The length of the data to receive
	 */
	virtual int Recv(char *s, int length);
	
	/**
	 * Allows to send data
	 * 
	 * @param s A pointer to data
	 * @param lenght The length of data to send
	 */
	virtual int Send(const char *s, int length);

	/**
	 * Allows to close the connection
	 */
	virtual void Close();

	virtual void Shutdown(int dir=1);
	
	/**
	 * Allows to know the url:port
	 */ 
	virtual bool GetSrcAccesspoint(paroc_string & accesspoint);
	
	/**
	 * Allows to know the url:port destination
	 */
	//virtual const char* GetDestAccesspoint();
	
	/**
	 * Return the name of this protocol
	 */
	virtual bool GetProtocolName(paroc_string & protocolName);
	
	/**
	 * Return the port number
	 */
	int GetPort();
	
	void setDestNodeID(unsigned int nodeID);
	unsigned int getDestNodeID();
	
	void setDestPortID(unsigned int portID);
	unsigned int getDestportID();
	bool IsMsgReceived();


 protected:	

	/**
	 * Return the default port
	 */
	int GetDefaultPort();
	
	void GetNodeAndPort(const char* accesspoint, unsigned int* node, unsigned int* port);
	
	struct gm_port *gm_port;
	struct _gm_send_buffer  gm_send_buffer[MAX_SEND_BUFFERS];
	void *gm_recv_buffer[MAX_RECV_BUFFERS];
	
	int nNextSendBuffer;
	int nLastFreedSendBuffer;
	int nRecvTokens,nSendTokens;

	unsigned int localNodeID;
	unsigned int localPortID;	
	unsigned int destNodeID;
	unsigned int destPortID;
	
};

#endif
