/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief parallel object description data and interface
 *
 * UPDATES :
 * Authors      Date              Comment
 * clementval   2010/05/06  All code added for the semester project begin with this comment //Added by clementval
 * clementval 2010/05/06    Add object description for search parameter
 *
 */



#ifndef _POPC_OD_H
#define _POPC_OD_H
#include <paroc_base.h>

/**
 * @class paroc_od
 * @brief Object description class, used by POP-C++ runtime.
 *
 * The od specifies how and where the parallel object is to be created at runtime
 *
 * @author Tuan Anh Nguyen
 */
class paroc_od: public paroc_base {
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
    inline void directory(const std::string& str){cwd = str;}
    /**
     * @brief Set remote working directory to the current directory on interface side
     */
    void sameDirectory(bool a);

    /**
     * @brief Specifies the address requirement for the target machine (no JobMgr used)
     * Syntaxe : user@ip{core}:port
     * @param h machine ip or name
     */
    void url(const std::string& h);
    
    void node(int value);
    void core(int value);




    /**
    * @brief Specifies the address requirement for the target machine (no JobMgr used)
    * Syntaxe : user@ip{core}:port
    * @param h machine ip or name
    * @param arch machine architecture
    */
    void url(const std::string& h, const std::string& arch);
    //void url(const std::string h);

    //void url(const std::string h, std::string arch);
    inline void joburl(const std::string& str) {jobcontact = str;}
    inline void executable(const std::string& str) {codefile = str;}

    inline void protocol(const std::string& myproto){proto = myproto;}
    inline void encoding(const std::string& myencode) {encode = myencode;}

    /**
     * @brief Specifies that the command to launch the object is to be printed instead, (no JobMgr used)
     * @param a on/off
     */
    void manual(bool a);

    //Added by clementval
    /**
     * @brief Specifies the parameter for the resource discovery
     * @param maxdepth  maximum number of hop for a request
     * @param maxsize   maximum size of the request message
     * @param waittime  time to wait for the resource discovery
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
    inline const std::string& getCwd() const {return cwd;}           // Formerly getDirectory
    inline const std::string& getURL() const {return hostname;}
    inline const std::string& getUser() const {return hostuser;}
    inline const std::string& getCore() const {return hostcore;}
    inline const std::string& getArch() const {return hostarch;}
    inline const std::string& getJobURL() const {return jobcontact;}
    inline const std::string& getExecutable() const {return codefile;}

    int get_node() const;
    int get_core() const;

    inline const std::string& getProtocol() const {return proto;}
    inline const std::string& getEncoding() const {return encode;}
    bool getIsManual() const;
#ifdef OD_DISCONNECT
    void checkConnection(int time_alive, int time_control);
    void checkConnection(bool doCheck);
    bool getCheckConnection() const;
    void getCheckConnection(int &time_alive, int &time_control) const;
#endif
    inline const std::string&  getBatch() const {return batchSystem;}

    paroc_od &operator =(const paroc_od &od);

    bool IsEmpty() const;
    bool IsLocal() const;

    inline void setPlatforms(const std::string& str) {platforms = str;}
    inline const std::string& getPlatforms() const {return platforms;}

    void setValue(const std::string &key, const std::string &val);
    void getValue(const std::string &key, std::string &val);


    virtual void Serialize(pop_buffer &buf, bool pack);
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

    int node_value;
    int core_value;

    std::string cwd;

    std::string hostname; /*only for use with od.url*/
    std::string hostuser; /*only for use with od.url*/
    std::string hostcore; /*only for use with od.url*/
    std::string hostarch; /*only for use with od.url*/
    std::string batchSystem;

    std::string jobcontact;
    std::string codefile;

    std::string platforms;

    std::string proto; //space-separate protocol lists
    std::string encode; //space-separate encoding lists

    std::vector<std::string> keys;
    std::vector<std::string> values;

    //Added by clementval
    int max_depth;  //Maximum depth for the request propagation
    int max_size;   //Maximum size of the request message
    int wait_time;  //Wait time for the resource discovery
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
