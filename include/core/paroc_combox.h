/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief POP-C++ communication abstraction
 *
 */

#ifndef POPC_COMBOX_H_
#define POPC_COMBOX_H_

#include "paroc_buffer_factory_finder.h"

class paroc_combox;
class paroc_buffer_factory;
/**
 * @class paroc_connection
 * @brief POP-C++ communication abstraction, used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 *
 */
class paroc_connection {
public:
    paroc_connection(paroc_combox *com);
    paroc_connection(paroc_combox *com, bool init);
    paroc_connection(paroc_combox *com, paroc_buffer_factory *f);
    virtual ~paroc_connection();

    virtual bool is_initial_connection();

    virtual void SetBufferFactory(paroc_buffer_factory *fact);
    virtual paroc_buffer_factory *GetBufferFactory();

    paroc_combox *GetCombox();

    virtual paroc_connection *Clone()=0;
    virtual void reset()=0;



protected:
    paroc_buffer_factory * fact;
    paroc_combox *combox;
    bool _is_initial_connection;
};


enum COMBOX_EVENTS {COMBOX_NEW=0, COMBOX_CLOSE=1};
typedef bool (*COMBOX_CALLBACK)(void *, paroc_connection *);


/**
 * @class paroc_combox
 * @brief POP-C++ combox, used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 *
 */
class paroc_combox {
public:
    paroc_combox();
protected:
    virtual ~paroc_combox();

public:
    virtual bool Create(int port, bool server)=0;
    virtual bool Create(const char *address, bool server)=0;

    virtual bool need_address(){ return false; }

    virtual bool Connect(const char *url)=0;

    // Note: these 2 methods exist only for compatibility between dynamic and pseudodynamic versions of popc
    // they must never be used in dynamic version
    virtual bool connect_and_die(std::string &url){(void)url; return true;}
    virtual bool is_server(){return false;}

    virtual int Send(const char *s,int len)=0;
    virtual int Send(const char *s,int len, paroc_connection *connection)=0;
    virtual bool SendAck(paroc_connection *conn);

    virtual int Recv(char *s,int len)=0;
    virtual int Recv(char *s,int len, paroc_connection *connection)=0;
    virtual bool RecvAck(paroc_connection *conn=0);

    virtual paroc_connection *Wait()=0;

    virtual paroc_connection* get_connection()=0;

    virtual void Close()=0;

    void SetTimeout(int millisec);
    int  GetTimeout();

    virtual std::string GetUrl()=0;
    virtual std::string GetProtocol()=0;

    virtual void Destroy();

    bool SetCallback(COMBOX_EVENTS ev, COMBOX_CALLBACK cb, void *arg);

    void SetBufferFactory(paroc_buffer_factory *fact);
    paroc_buffer_factory *GetBufferFactory();

    static const char* PROTOCOL_SEPARATOR;

protected:
    virtual bool OnNewConnection(paroc_connection *conn);
    virtual bool OnCloseConnection(paroc_connection *conn);

protected:
    int timeout;
    COMBOX_CALLBACK cblist[2];
    void *cbdata[2];

    paroc_buffer_factory *defaultFact;

};



#endif // POPC_COMBOX_H_







