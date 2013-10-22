/*
AUTHORS: Tuan Anh Nguyen

DESCRIPTION: parallel object description data and interface

UPDATES : 
Authors		Date			Comment
clementval	2010/05/06	All code added for the semester project begin with this comment //Added by clementval
clementval 	2010/05/06	Add object description for search parameter
 */


#ifndef _POPC_OD_H
#define _POPC_OD_H
#include <paroc_string.h>
#include <paroc_base.h>
#include <paroc_list.h>

typedef paroc_list<paroc_string> paroc_list_string;
/**
 * @class paroc_od
 * @brief Object description class, used by POP-C++ runtime.
 *
 * The od specifies how and where the parallel object is to be created at runtime
 *
 * @author Tuan Anh Nguyen
 */
class paroc_od: public paroc_base
{
public:
	paroc_od();
	~paroc_od();

	/**
	 * @brief Specifies the minimal power requirement for the target machine (JobMgr)
	 * @param require Required power (MFlops)
	 * @param min minimal power (MFlops)
	 */
	void power(float require, float min=-1.0f);

	/**
	 * @brief Specifies the minimal memory requirement for the target machine (JobMgr)
	 * @param require Required memory (MB)
	 * @param min minimal memory (MB)
	 */
	void memory(float require, float min=-1.0f);

	/**
	 * @brief Specifies the minimal bandwidth requirement for the target machine (JobMgr)
	 * @param require Required bandwidth
	 * @param min minimal bandwidth
	 */
	void bandwidth(float require, float min=-1.0f);

	void walltime(float time);

	/**
	 * @brief Specifies the working directory of the object
	 * @param h dir
	 */
	void directory(const char *h);
	/**
	 * @brief Set remote working directory to the current directory on interface side
	 */
	void sameDirectory(bool a);

	/**
	 * @brief Specifies the address requirement for the target machine (no JobMgr used)
	 * Syntaxe : user@ip{core}:port
	 * @param h machine ip or name
	 */
	void url(const char *h);
	/**
	* @brief Specifies the address requirement for the target machine (no JobMgr used)
	* Syntaxe : user@ip{core}:port
	* @param h machine ip or name
	* @param arch machine architecture
	*/
	void url(const char *h, const char *arch);
	//void url(const std::string h);

	//void url(const std::string h, std::string arch);
	void joburl(const char *jobcontact);
	void executable(const char *codefile);

	void protocol(const char *myproto);
	void encoding(const char *myencode);

	/**
	 * @brief Specifies that the command to launch the object is to be printed instead, (no JobMgr used)
	 * @param a on/off
	 */
	void manual(bool a);

	//Added by clementval
	/**
	 * @brief Specifies the parameter for the resource discovery
	 * @param maxdepth 	maximum number of hop for a request
	 * @param maxsize 	maximum size of the request message
	 * @param waittime 	time to wait for the resource discovery
	 */
	void search(int maxdepth, int maxsize, int waittime);
	int getSearchMaxDepth() const;	
	int getSearchMaxReqSize() const;
	int getSearchWaitTime() const;
	bool isSearchSet() const;
	//End of add

   bool isSecureSet() const;
   void secure(int foo);
   bool isServiceSet() const;
	void service(bool serv);

	void getPower(float &require, float &min) const;
	void getMemory(float &require, float &min) const;
	void getBandwidth(float &require, float &min) const;
	float getWallTime() const;
	void getDirectory(paroc_string & cwd) const;
	void getURL(paroc_string & url) const;
	void getUser(paroc_string & s) const;
	void getCore(paroc_string & s) const;
	void getArch(paroc_string & s) const;
	void getJobURL(paroc_string &joburl) const;
	void getExecutable(paroc_string &exec) const;

	void getProtocol(paroc_string &proto) const;
	void getEncoding(paroc_string &encode) const;
	bool getIsManual() const;
#ifdef OD_DISCONNECT
	void checkConnection(int time_alive, int time_control);
	void checkConnection(bool doCheck);
	bool getCheckConnection() const;
	void getCheckConnection(int &time_alive, int &time_control) const;
#endif
	void getBatch(paroc_string& batch) const;

	paroc_od &operator =(const paroc_od &od);

	bool IsEmpty() const;
	bool IsLocal() const;

	void setPlatforms(const char *objplatforms);
	void getPlatforms(paroc_string &objplatforms) const;

	void setValue(const paroc_string &key, const paroc_string &val);
	void getValue(const paroc_string &key, paroc_string &val);


	virtual void Serialize(paroc_buffer &buf, bool pack);
	void runLocal(bool isLocal);



public:
	static bool defaultLocalJob;

protected:
	bool isLocalJob;
	float mflops, min_mflops;
	float ram, min_ram;
	float net, min_net;
	float time;
	bool isManual;
	paroc_string cwd;

	paroc_string hostname; /*only for use with od.url*/
	paroc_string hostuser; /*only for use with od.url*/
	paroc_string hostcore; /*only for use with od.url*/
	paroc_string hostarch; /*only for use with od.url*/
	paroc_string batchSystem;

	paroc_string jobcontact;
	paroc_string codefile;

	paroc_string platforms;

	paroc_string proto; //space-separate protocol lists
	paroc_string encode; //space-separate encoding lists

	paroc_list_string keys, values;

	//Added by clementval
	int max_depth;	//Maximum depth for the request propagation
	int max_size;	//Maximum size of the request message
	int wait_time;	//Wait time for the resource discovery
	bool searchSet;
	//End of add

   bool secureSet;
   bool serviceSet;

#ifdef OD_DISCONNECT	
	int time_alive, time_control; /*od.checkConnection ms*/
	static const int TIME_ALIVE=1000;     /*od.checkConnection ms*/
	static const int TIME_CONTROL=1000;   /*od.checkConnection ms*/
#endif
};

#endif
