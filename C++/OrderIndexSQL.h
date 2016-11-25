/*********************************************************************
	Rhapsody	: 7.6.1 
	Login		: Administrator
	Component	: cmsv2lxImage 
	Configuration 	: linux_static
	Model Element	: OrderIndexSQL
//!	Generated Date	: Tue, 15, Nov 2016  
	File Path	: cmsv2lxImage/linux_static/Default/OrderIndexSQL.h
*********************************************************************/

#ifndef Default_OrderIndexSQL_H
#define Default_OrderIndexSQL_H

//## auto_generated
#include <oxf/oxf.h>
//## auto_generated
#include "Default/Default.h"
//## class OrderIndexSQL
#include "Default/OrderIndex.h"
//## auto_generated
class FileLog;

//## auto_generated
class ObjectP;

//## dependency QueryXml
class QueryXml;

//## package Default

//## class OrderIndexSQL
class OrderIndexSQL : public OrderIndex {
    ////    Constructors and destructors    ////
    
public :

    //## operation OrderIndexSQL()
    OrderIndexSQL();
    
    //## operation ~OrderIndexSQL()
    ~OrderIndexSQL();
    
    ////    Operations    ////
    
    //## operation addReference(ObjectP *)
    void addReference(ObjectP * rObject);
    
    //## operation append(char*,char*)
    void append(char* name, char* value);
    
    //## operation append(ObjectP *)
    void append(ObjectP * obj);
    
    //## operation bin2hex(char *,string &,char*)
    void bin2hex(const char * bs, string & out1, char* out2);
    
    //## operation callback1(void *,int,char **,char **)
    static int callback1(void * NotUsed, int argc, char ** argv, char ** azColName);
    
    //## operation close()
    void close();
    
    //## operation createFileName()
    virtual string createFileName();
    
    //## operation createTables()
    void createTables();
    
    //## operation decodeOrdpathNum(string &)
    int decodeOrdpathNum(string & str);
    
    //## operation decrement()
    void decrement();
    
    //## operation encodeOrdpathNum(int,string &)
    int encodeOrdpathNum(int n, string & out);
    
    //## operation getChildrenCount()
    virtual unsigned int getChildrenCount();
    
    //## operation getLastOrdinal()
    string getLastOrdinal();
    
    //## operation getOrdhex(string &,string &,list<string> &)
    virtual void getOrdhex(string & tag, string & value, list<string> & _list);
    
    //## operation getOrdhex(ObjectP *,list<string> &)
    virtual void getOrdhex(ObjectP * obj, list<string> & _list);
    
    //## operation getRegistry(char *)
    virtual string getRegistry(const char * name);
    
    //## operation getValue(string &,string &,string &,list<string> &)
    virtual void getValue(string & tag, string & tagc, string & value, list<string> & _list);
    
    //## operation getVersion()
    int getVersion();
    
    //## operation hex2bin(string,string &)
    void hex2bin(string in, string & out);
    
    //## operation increment()
    void increment();
    
    //## operation init()
    int init();
    
    //## operation initFill()
    void initFill();
    
    //## operation initPrefixMapping()
    void initPrefixMapping();
    
    //## operation insert()
    void insert();
    
    //## operation makeNewBitString(string &,string &,string &)
    void makeNewBitString(string & leftB, string & rightB, string & out);
    
    //## operation open()
    void open();
    
    //## operation remove(char*)
    virtual void remove(char* linkName);
    
    //## operation setOrdhexFor(ObjectP *)
    void setOrdhexFor(ObjectP * obj);
    
    //## operation setRegistry(char*,char *)
    virtual void setRegistry(char* name, const char * value);
    
    //## operation setVersion(int)
    void setVersion(int num);
    
    //## operation update()
    void update();
    
    //## operation upgrade()
    void upgrade();
    
    //## operation upgradeFill()
    void upgradeFill();
    
    //## operation upgradeFinish()
    void upgradeFinish();
    
    //## operation upgradePrepare()
    void upgradePrepare();
    
    ////    Additional operations    ////
    
    //## auto_generated
    string getI_namid() const;
    
    //## auto_generated
    void setI_namid(string p_i_namid);
    
    //## auto_generated
    string getI_ordhex() const;
    
    //## auto_generated
    void setI_ordhex(string p_i_ordhex);
    
    //## auto_generated
    string getI_tag() const;
    
    //## auto_generated
    void setI_tag(string p_i_tag);
    
    //## auto_generated
    string getI_tagc() const;
    
    //## auto_generated
    void setI_tagc(string p_i_tagc);
    
    //## auto_generated
    string getI_value() const;
    
    //## auto_generated
    void setI_value(string p_i_value);
    
    //## auto_generated
    sqlite3 * getPDb() const;
    
    //## auto_generated
    void setPDb(sqlite3 * p_pDb);
    
    //## auto_generated
    int getVersionNew() const;
    
    //## auto_generated
    void setVersionNew(int p_versionNew);
    
    ////    Attributes    ////

protected :

    string i_namid;		//## attribute i_namid
    
    string i_ordhex;		//## attribute i_ordhex
    
    string i_tag;		//## attribute i_tag
    
    string i_tagc;		//## attribute i_tagc
    
    string i_value;		//## attribute i_value
    
    sqlite3 * pDb;		//## attribute pDb
    
    int version;		//## attribute version
    
    int versionNew;		//## attribute versionNew
};

#endif
/*********************************************************************
	File Path	: cmsv2lxImage/linux_static/Default/OrderIndexSQL.h
*********************************************************************/
