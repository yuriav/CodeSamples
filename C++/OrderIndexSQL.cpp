/********************************************************************
	Rhapsody	: 7.6.1 
	Login		: Administrator
	Component	: cmsv2lxImage 
	Configuration 	: linux_static
	Model Element	: OrderIndexSQL
//!	Generated Date	: Tue, 15, Nov 2016  
	File Path	: cmsv2lxImage/linux_static/Default/OrderIndexSQL.cpp
*********************************************************************/

//## auto_generated
#include "Default/OrderIndexSQL.h"
//## auto_generated
#include "Default/FileLog.h"
//## auto_generated
#include "Default/ObjectP.h"
//## dependency QueryXml
#include "Default/QueryXml.h"
//## package Default

//## class OrderIndexSQL
OrderIndexSQL::OrderIndexSQL() : version(0), versionNew(0) {
    //#[ operation OrderIndexSQL()
    initFlag=false;
    pDb=NULL;
    //prefixDB=NULL;
    //#]
}

OrderIndexSQL::~OrderIndexSQL() {
    //#[ operation ~OrderIndexSQL()
    if(pDb!=NULL) close();
    //#]
}

void OrderIndexSQL::addReference(ObjectP * rObject) {
    //#[ operation addReference(ObjectP *)
    int rc, i, ncols, id, cid;
    //sqlite3 *db=pDb;
    sqlite3_stmt *stmt;
    char *sql;
    
    log->getOfs()<<"SQL : addReferer: "<<rObject->getName()<<endl<<flush;
    
    if(pDb==NULL) return;
    
    sql = sqlite3_mprintf("INSERT INTO referer VALUES('%q','%q','%q')\0",(rObject->getId()).c_str(),(rObject->generatePath2()).c_str(),(rObject->getName()).c_str());
    
    sqlite3_prepare(pDb, sql, strlen(sql), &stmt, NULL);
    
    //while(rc == SQLITE_ROW) {
    	//id = sqlite3_column_int(stmt, 0);
    	//cid = sqlite3_column_int(stmt, 1);
    	//name = sqlite3_column_text(stmt, 2);
    	//if(name != NULL){
    	//	fprintf(stderr, "Row: id=%i, cid=%i, name='%s'\n", id,cid,name);
    	//} else {
    		/* Field is NULL */
    	//	fprintf(stderr, "Row: id=%i, cid=%i, name=NULL\n", id,cid);
    	//}
    	rc = sqlite3_step(stmt);
    //} 
    //indexer->getLog()<<"rc "<<rc;
    //indexer->getLog()<<endl<<flush;
    
    sqlite3_finalize(stmt);
    sqlite3_free(sql);
    
    //#]
}

void OrderIndexSQL::append(char* name, char* value) {
    //#[ operation append(char*,char*)
    string ordhex=getLastOrdinal();
    string _curE="";
    string _newS;
    string _posHex;
    string ordbin;
                
                log->getOfs()<<"SQL : last Ordinal: "<<ordhex<<endl<<flush;
                
                //if(ordhex.empty()) return;
                
                //hex2bin(ordhex,ordbin);
                
                log->getOfs()<<"SQL : last Ordinal bin: "<<ordbin<<endl<<flush;
                
                makeNewBitString(ordhex,_curE,_newS);
                
                //bin2hex(_newS.c_str(),_posHex,NULL);
                
                this->i_ordhex=_newS;
    			this->i_tag=name;
    			this->i_value=value;
    
    insert();
    //#]
}

void OrderIndexSQL::append(ObjectP * obj) {
    //#[ operation append(ObjectP *)
    string ordhex=getLastOrdinal();
    string _curE="";
    string _newS;
    string _posHex;
    string ordbin;
                
                log->getOfs()<<"SQL : last Ordinal: "<<ordhex<<endl<<flush;
                
                //if(ordhex.empty()) return;
                
                //hex2bin(ordhex,ordbin);
                
                //log->getOfs()<<"SQL : last Ordinal bin: "<<ordbin<<endl<<flush;
                
                //bin2hex(_newS.c_str(),_posHex,NULL);
                
                //if((obj->getOrdhex()).empty()) {
                	makeNewBitString(ordhex,_curE,_newS);
                	this->i_ordhex=_newS;
                	obj->setOrdhex(_newS);
                //} else {
                //	this->i_ordhex=obj->getOrdhex();
                //}
    			//this->i_tag=(char*)((obj->getObjectNode())->name);
    			this->i_tag=obj->getContentType();
    			this->i_value=obj->getName();
    
    insert();
    //#]
}

void OrderIndexSQL::bin2hex(const char * bs, string & out1, char* out2) {
    //#[ operation bin2hex(char *,string &,char*)
    /*
    int _len=strlen(bs);
    out1.clear();
    bitset<8> _byte;
    
    _byte=string(bs);
    
    char _buf[3];
    sprintf(_buf,"%x",_byte.to_ulong());
    */
    
    if(1){
    int bc=0;
    unsigned int _hbyte=0;
    int _len=strlen(bs);
    int _flen=0;
    
    out1.clear();
    
    
    if(_len%4) {
    	_flen=_len+(4-(_len%4));
    } else {
    	_flen=_len;
    }
    
    //_flen=_len;
    
    //log->getOfs()<<"bin2hex:"<<_len<<" "<<_flen<<endl<<flush;
    
    for(int i=0;i<_flen;i++) {
    	if(i<_len) {
    		if(bs[i]=='1') {
    			_hbyte=_hbyte | 1;
    		} else {
    			//_hbyte=_hbyte & 0;
    		}
    	} else {
    		//_hbyte=_hbyte<<1;
    		//getLog()<<" *"<<_hbyte;
    	}
    	//getLog()<<" "<<_hbyte;
    	if((i+1)%4==0) {
    		//getLog()<<endl;
    		char _buf[3];
    		sprintf(_buf,"%x",_hbyte);
    		//log->getOfs()<<"bin2hex:"<<_buf<<endl<<flush;
    		out1=out1+_buf;
    		_hbyte=0;
    	} else {
    		_hbyte=_hbyte<<1;
    	}
    }
    }
    //#]
}

int OrderIndexSQL::callback1(void * NotUsed, int argc, char ** argv, char ** azColName) {
    //#[ operation callback1(void *,int,char **,char **)
      int i;
      for(i=0; i<argc; i++){
        //cerr<<azColName[i]<<" = "<< argv[i];
      }
      //cerr<<endl<<flush;
      return 0;
    //#]
}

void OrderIndexSQL::close() {
    //#[ operation close()
    if(pDb!=NULL) {
    	//log->getOfs()<<"SQL : close: "<<endl<<flush;
    	sqlite3_close(pDb);pDb=NULL;
    }
    //#]
}

string OrderIndexSQL::createFileName() {
    //#[ operation createFileName()
    if(object->getIsPermanent()) {
      string tmpPath=object->getObjInstallDir()+object->getPath()+object->getName();
      //log->getOfs()<<"object dir: "<<tmpPath<<endl<<flush;
      
      return tmpPath+string("/")+string(".index.order");
    } else {
    	return string(":memory:");
    }
    //#]
}

void OrderIndexSQL::createTables() {
    //#[ operation createTables()
    char *zErrMsg = 0;
    
    int _ret = 0;
    
    if(pDb==NULL) return;
    
    log->getOfs()<<"SQL Create Tables: "<<endl<<flush;
    
    _ret = sqlite3_exec(pDb, "CREATE TABLE nodes (ordhex TEXT UNIQUE,ordpath TEXT,tag TEXT,value TEXT UNIQUE,prefix TEXT,namid TEXT)", callback1, 0, &zErrMsg);
    if( _ret!=SQLITE_OK ){
        log->getOfs()<<"SQL error: "<<zErrMsg<<endl<<flush;
        sqlite3_free(zErrMsg);
    }
    
    _ret = sqlite3_exec(pDb, "CREATE TABLE referer (uuid TEXT UNIQUE,path TEXT,name TEXT)", callback1, 0, &zErrMsg);
    if( _ret!=SQLITE_OK ){
        log->getOfs()<<"SQL error: "<<zErrMsg<<endl<<flush;
        sqlite3_free(zErrMsg);
    }
    
    _ret = sqlite3_exec(pDb, "CREATE TABLE stats (childrens INTEGER)", callback1, 0, &zErrMsg);
    if( _ret!=SQLITE_OK ){
        log->getOfs()<<"SQL error: "<<zErrMsg<<endl<<flush;
        sqlite3_free(zErrMsg);
    }
    
    _ret = sqlite3_exec(pDb, "CREATE TABLE registry (name TEXT UNIQUE ON CONFLICT REPLACE,value TEXT,valuei INTEGER)", callback1, 0, &zErrMsg);
    if( _ret!=SQLITE_OK ){
        log->getOfs()<<"SQL error: "<<zErrMsg<<endl<<flush;
        sqlite3_free(zErrMsg);
    }
    
    _ret = sqlite3_exec(pDb, "CREATE TABLE version (num INTEGER)", callback1, 0, &zErrMsg);
    if( _ret!=SQLITE_OK ){
        log->getOfs()<<"SQL error: "<<zErrMsg<<endl<<flush;
        sqlite3_free(zErrMsg);
    }
    
    /*
    _ret = sqlite3_exec(pDb, "CREATE TABLE meta ?????? (ordhex TEXT UNIQUE,ordpath TEXT,tag TEXT,value TEXT UNIQUE,prefix TEXT,namid TEXT)", callback1, 0, &zErrMsg);
    if( _ret!=SQLITE_OK ){
        log->getOfs()<<"SQL error: "<<zErrMsg<<endl<<flush;
        sqlite3_free(zErrMsg);
    }
    _ret = sqlite3_exec(pDb, "CREATE TABLE xml ???????(ordhex TEXT UNIQUE,ordpath TEXT,tag TEXT,value TEXT UNIQUE,prefix TEXT,namid TEXT)", callback1, 0, &zErrMsg);
    if( _ret!=SQLITE_OK ){
        log->getOfs()<<"SQL error: "<<zErrMsg<<endl<<flush;
        sqlite3_free(zErrMsg);
    }
    
    */
    //#]
}

int OrderIndexSQL::decodeOrdpathNum(string & str) {
    //#[ operation decodeOrdpathNum(string &)
    bitset<8> _char;
    
    string _prefix;
    _prefix.clear();
    
    char _ch[3];
    _ch[2]='\0';
    
    int _bit=0;
    bool isBitstring=true;
    
    int ci,i;
    
    for(ci=0;ci<str.size();ci+=2) {
    	errno=0; 
    	_ch[0]=str[ci];
    	_ch[1]=str[ci+1];
    	unsigned long n=strtoul(_ch,NULL,16);
    	_char=n;
    	log->getOfs()<<"n="<<n<<" ch="<<_ch<<endl<<flush;
    	for(i=7;i>=0;i--) {
    		log->getOfs()<<""<<_char.test(i)<<flush;
    	}
    	log->getOfs()<<endl<<flush;
    }
    
    return 0;
    //#]
}

void OrderIndexSQL::decrement() {
    //#[ operation decrement()
    //#]
}

int OrderIndexSQL::encodeOrdpathNum(int n, string & out) {
    //#[ operation encodeOrdpathNum(int,string &)
    int rc, i, ncols, id, cid;
    //sqlite3 *db=pDb;
    //sqlite3_stmt *stmt;
    char *sql;
    
    //const unsigned char *prefix;
    //unsigned char prefix[20];
    string prefix;
    int Li,Omin,Omax;
    
    /*
    sql = sqlite3_mprintf("select prefix,Li,Omin FROM prefixMapping WHERE Omin <= %d AND Omax >= %d\0",n,n);
    
    rc = sqlite3_prepare(pDb, sql, strlen(sql), &stmt, NULL);
    
    rc = sqlite3_step(stmt);
    while(rc == SQLITE_ROW) {
    	Li = sqlite3_column_int(stmt, 1);
    	Omin = sqlite3_column_int(stmt, 2);
    	prefix = sqlite3_column_text(stmt, 0);
    	rc = sqlite3_step(stmt);
    }
    */
    
    Omin= -1118485;Omax= -69910;if(n>=Omin && n<=Omax) {Li= 20;prefix="000000001";}
    Omin= -69909;Omax= -4374;if(n>=Omin && n<=Omax) {Li= 16;prefix="00000001";}
    Omin= -4373;Omax= -278;if(n>=Omin && n<=Omax) {Li= 12;prefix="0000001";}
    Omin= -277;Omax= -22;if(n>=Omin && n<=Omax) {Li= 8;prefix="000001";}
    Omin= -21;Omax= -6;if(n>=Omin && n<=Omax) {Li= 4;prefix="00001";}
    Omin= -5;Omax= -2;if(n>=Omin && n<=Omax) {Li= 2;prefix="0001";}
    Omin= -1;Omax= 0;if(n>=Omin && n<=Omax) {Li= 1;prefix="001";}
    Omin= 1;Omax= 1;if(n>=Omin && n<=Omax) {Li= 0;prefix="01";}
    Omin= 2;Omax= 3;if(n>=Omin && n<=Omax) {Li= 1;prefix="10";}
    Omin= 4;Omax= 7;if(n>=Omin && n<=Omax) {Li= 2;prefix="110";}
    Omin= 8;Omax= 23;if(n>=Omin && n<=Omax) {Li= 4;prefix="1110";}
    Omin= 24;Omax= 279;if(n>=Omin && n<=Omax) {Li= 8;prefix="11110";}
    Omin= 280;Omax= 4375;if(n>=Omin && n<=Omax) {Li= 12;prefix="111110";}
    Omin= 4376;Omax= 69911;if(n>=Omin && n<=Omax) {Li= 16;prefix="1111110";}
    Omin= 69912;Omax= 1118487;if(n>=Omin && n<=Omax) {Li= 20;prefix="11111110";}
    
    
    /* 
    getLog()<<"============"<<endl;
    getLog()<<"prefix "<<prefix;
    getLog()<<" Li "<<Li;
    getLog()<<" Omin "<<Omin;
    getLog()<<endl<<flush;
    */
    
    char _buf[30];
    int c;
    
    int On=n-Omin;
    
    //getLog()<<" On "<<On<<" "<<n<<endl;
    
    for (c = 0; c<Li; c++)
    {
    	if(On & 1){
    		//getLog()<<"1";
    		_buf[Li-c-1]='1';
    	} else {
    		//getLog()<<"0";
    		_buf[Li-c-1]='0';
    	}
      On>>=1;
    }
    _buf[Li]='\0';
    
    //  getLog()<<endl<<c<<endl;
    
    out=out+(char*)prefix.c_str();
    out=out+_buf;
    
    //sqlite3_finalize(stmt);
    //sqlite3_free(sql);
    
    //getLog()<<"============"<<endl<<flush;
    
    return 0;
    //#]
}

unsigned int OrderIndexSQL::getChildrenCount() {
    //#[ operation getChildrenCount()
    int rc, i, ncols, id, cid;
    
    int value=0;
    sqlite3 *db=pDb;
    sqlite3_stmt *stmt;
    char *sql;
    
    sql = sqlite3_mprintf("select count(*) FROM nodes\0");
    
    rc = sqlite3_prepare(pDb, sql, strlen(sql), &stmt, NULL);
    //log->getOfs()<<"SQL:"<<sql<<":"<<rc<<" :"<<sqlite3_errmsg(pDb)<<endl<<flush;
    rc = sqlite3_step(stmt);
    //log->getOfs()<<"SQL:"<<sql<<":"<<rc<<" :"<<sqlite3_errmsg(pDb)<<endl<<flush;
    while(rc == SQLITE_ROW) {
    	value = sqlite3_column_int(stmt, 0);
    	rc = sqlite3_step(stmt);
    }
    
    sqlite3_finalize(stmt);
    sqlite3_free(sql);
    
    return value;
    //#]
}

string OrderIndexSQL::getLastOrdinal() {
    //#[ operation getLastOrdinal()
    int rc, i, ncols, id, cid;
    //sqlite3 *db=pDb;
    sqlite3_stmt *stmt;
    //char *sql;
    string rval;
    
    string sql = "SELECT ordhex FROM nodes ORDER BY ordhex DESC LIMIT 1\0";
    
    rc=sqlite3_prepare(pDb, sql.c_str(), sql.size(), &stmt, NULL);
    
    if(rc==SQLITE_OK) {
    
    	rc = sqlite3_step(stmt);
    	const unsigned char *ordinal = sqlite3_column_text(stmt, 0);
    
    	//sqlite3_free(sql);
    
    	if(ordinal!=NULL) {
    		rval=string((const char *)ordinal);
    	} else {
    		rval=string("");
    	}
    }else{
    	log->getOfs()<<"SQL : : error:"<<rc<<endl<<flush;
    	rval=string("");
    }
    
    sqlite3_finalize(stmt);
    
    return rval;
    //#]
}

void OrderIndexSQL::getOrdhex(string & tag, string & value, list<string> & _list) {
    //#[ operation getOrdhex(string &,string &,list<string> &)
    int rc, i, ncols, id, cid;
    //sqlite3 *db=pDb;
    sqlite3_stmt *stmt;
    //char *sql;
    string rval;
    
    string sql = string("SELECT ordhex FROM nodes WHERE value=='")+value+string("'");
    
    if(!tag.empty()) {
    	string _str("");
    	_str=string(" AND tag=='")+tag+string("'");
    	sql.append(_str);
    }
    
    //string("' LIMIT 1\0")
    sql.append("\0");
    
    //log->getOfs()<<"SQL : cmd: "<<sql<<endl<<flush;
    
    rc=sqlite3_prepare(pDb, sql.c_str(), sql.size(), &stmt, NULL);
    
    //log->getOfs()<<"SQL : cmd: rc: "<<rc<<endl<<flush;
    
    rc = sqlite3_step(stmt);
    if(rc==SQLITE_ROW) {
    
    	const unsigned char *ordinal = sqlite3_column_text(stmt, 0);
    
    	//sqlite3_free(sql);
    
    	if(ordinal!=NULL) {
    		rval=string((const char *)ordinal);
    		_list.push_back(rval);
    	} else {
    		rval=string("");
    	}
    	rc = sqlite3_step(stmt);
    }
    /*else{
    	log->getOfs()<<"SQL : get last Ordinal: error:"<<rc<<endl<<flush;
    	rval=string("");
    }*/
    
    sqlite3_finalize(stmt);
    
    //value=rval;
    //#]
}

void OrderIndexSQL::getOrdhex(ObjectP * obj, list<string> & _list) {
    //#[ operation getOrdhex(ObjectP *,list<string> &)
    int rc, i, ncols, id, cid;
    //sqlite3 *db=pDb;
    sqlite3_stmt *stmt;
    //char *sql;
    string rval;
    
    string value=obj->getName();
    string tag=obj->getContentType();
    
    
    if((obj->getStatus()).compare("updateOrderIndex") == 0) {
    	i_tag=tag;
    	i_value=value;
    	update();
    	obj->setStatus("");
    }
    
    getOrdhex(tag,value,_list);
    
    /*
    if(_list.empty()) {
    	update();
    	getOrdhex(tag,value,_list);
    }*/
    
    /*
    string sql = string("SELECT ordhex FROM nodes WHERE value=='")+value+string("'");
    
    if(!tag.empty()) {
    	string _str("");
    	_str=string(" AND tag=='")+tag+string("'");
    	sql.append(_str);
    }
    
    sql.append("\0");
    
    rc=sqlite3_prepare(pDb, sql.c_str(), sql.size(), &stmt, NULL);
    
    rc = sqlite3_step(stmt);
    if(rc==SQLITE_ROW) {
    
    	const unsigned char *ordinal = sqlite3_column_text(stmt, 0);
    
    	if(ordinal!=NULL) {
    		rval=string((const char *)ordinal);
    		_list.push_back(rval);
    	} else {
    		rval=string("");
    	}
    	rc = sqlite3_step(stmt);
    }
    
    sqlite3_finalize(stmt);
    */
    //#]
}

string OrderIndexSQL::getRegistry(const char * name) {
    //#[ operation getRegistry(char *)
    int rc, i, ncols, id, cid;
    //sqlite3 *db=pDb;
    sqlite3_stmt *stmt;
    char *sql;
    string rval;
    
    //log->getOfs()<<"SQL : get Registry: "<<name<<endl<<flush;
    
    sql = sqlite3_mprintf("select value FROM registry WHERE name='%q' LIMIT 1\0",name);
    
    rc=sqlite3_prepare(pDb, sql, strlen(sql), &stmt, NULL);
    
    if(rc==SQLITE_OK) {
    
    	rc = sqlite3_step(stmt);
    	const unsigned char *ordinal = sqlite3_column_text(stmt, 0);
    
    	//sqlite3_free(sql);
    
    	//log->getOfs()<<"SQL : get value end. ";
    	if(ordinal!=NULL) {
    		//log->getOfs()<<ordinal<<endl<<flush;
    	} else {
    		//log->getOfs()<<endl<<flush;
    	}
    
    	if(ordinal!=NULL) {
    		rval=string((const char *)ordinal);
    	} else {
    		rval=string("");
    	}
    }else{
    	log->getOfs()<<"SQL : get registry: error:"<<rc<<endl<<flush;
    	rval=string("");
    }
    
    sqlite3_finalize(stmt);
    sqlite3_free(sql);
    
    return rval;
    //#]
}

void OrderIndexSQL::getValue(string & tag, string & tagc, string & value, list<string> & _list) {
    //#[ operation getValue(string &,string &,string &,list<string> &)
    int rc, i, ncols, id, cid;
    //sqlite3 *db=pDb;
    sqlite3_stmt *stmt;
    //char *sql;
    string rval;
    
    string sql;
    
    unsigned int range=0;
    unsigned int rangeCount=0;
    
    range=object->getRange();
    rangeCount=object->getRangeCount();
    
    if(tag.empty()){
    	sql = string("SELECT value FROM nodes");
    } else {
    	sql = string("SELECT value FROM nodes WHERE tag ")+tag;
    }
    
    if(0) {
    	string _str("");
    	_str=string(" AND tagc like '")+tagc+string("'");
    	sql.append(_str);
    }
    
    if(!value.empty()) {
    	string _str("");
    	_str=string(" AND value like '")+value+string("'");
    	sql.append(_str);
    }
    
    if(rangeCount>0) {
    	string _str("");
    	char _buf[50];
    	unsigned int _limit=0;
    	unsigned int _offset=0;
    	_limit=rangeCount;
    	sprintf(_buf,"%d\0",_limit);
    	_str=string(" LIMIT ")+string(_buf);
    	sql.append(_str);
    	_offset=range*rangeCount;
    	sprintf(_buf,"%d\0",_offset);
    	_str=string(" OFFSET ")+string(_buf);
    	sql.append(_str);
    }
    
    //string("' LIMIT 1\0")
    sql.append("\0");
    
    rc=sqlite3_prepare(pDb, sql.c_str(), sql.size(), &stmt, NULL);
    
    rc = sqlite3_step(stmt);
    while(rc == SQLITE_ROW) {
    //if(rc==SQLITE_ROW) {
    
    	const unsigned char *ordinal = sqlite3_column_text(stmt, 0);
    
    	//sqlite3_free(sql);
    
    	if(ordinal!=NULL) {
    		rval=string((const char *)ordinal);
    		_list.push_back(rval);
    	} else {
    		rval=string("");
    	}
    	rc = sqlite3_step(stmt);
    }
    /*else{
    	log->getOfs()<<"SQL : get last Ordinal: error:"<<rc<<endl<<flush;
    	rval=string("");
    }*/
    
    sqlite3_finalize(stmt);
    
    //value=rval;
    //#]
}

int OrderIndexSQL::getVersion() {
    //#[ operation getVersion()
    int rc, i, ncols, id, cid;
    
    int verN=0;
    sqlite3 *db=pDb;
    sqlite3_stmt *stmt;
    char *sql;
    
    sql = sqlite3_mprintf("select num FROM version LIMIT 1\0");
    
    rc = sqlite3_prepare(pDb, sql, strlen(sql), &stmt, NULL);
    //log->getOfs()<<"SQL:"<<sql<<":"<<rc<<" :"<<sqlite3_errmsg(pDb)<<endl<<flush;
    rc = sqlite3_step(stmt);
    //log->getOfs()<<"SQL:"<<sql<<":"<<rc<<" :"<<sqlite3_errmsg(pDb)<<endl<<flush;
    while(rc == SQLITE_ROW) {
    	verN = sqlite3_column_int(stmt, 0);
    	rc = sqlite3_step(stmt);
    }
    
    sqlite3_finalize(stmt);
    sqlite3_free(sql);
    
    return verN;
    //#]
}

void OrderIndexSQL::hex2bin(string in, string & out) {
    //#[ operation hex2bin(string,string &)
    
    map<char,string> hexl;
    
    hexl['0']="0000";
    hexl['1']="0001";
    hexl['2']="0010";
    hexl['3']="0011";
    
    hexl['4']="0100";
    hexl['5']="0101";
    hexl['6']="0110";
    hexl['7']="0111";
    
    hexl['8']="1000";
    hexl['9']="1001";
    hexl['a']="1010";
    hexl['b']="1011";
    
    hexl['c']="1100";
    hexl['d']="1101";
    hexl['e']="1110";
    hexl['f']="1111";
    
    for(int i=0;i<in.size();i++) {
    	out.append(hexl[in[i]]);
    }
    //#]
}

void OrderIndexSQL::increment() {
    //#[ operation increment()
    //#]
}

int OrderIndexSQL::init() {
    //#[ operation init()
    char *zErrMsg = 0;
    
    #define CURRENT_VER 14
    
    //OrderIndex::init();
    
    struct stat st1;
    		int er;
    		if(object->getIsPermanent()) {
        		fileName=createFileName();
        		er=stat(fileName.c_str(),&st1);
        	} else {
        		fileName=":memory:";
        		log->getOfs()<<"SQL : open :memory: "<<endl<<flush;
        		int _ret = sqlite3_open(fileName.c_str(),&pDb);
        		return _ret;
        	}
        	if(er<0){
        		//Index does't exist.Create index file
        		int _ret = sqlite3_open(fileName.c_str(),&pDb);
        		versionNew=CURRENT_VER;
        		createTables();
        		initFill();
        		/*if(object->isPermanent)*/ close();
        	} else {
        		//Index exist
        		int _ret = sqlite3_open(fileName.c_str(),&pDb);
        		int versionN = getVersion();
        		bool _updateByTimestamp=false;
        		{
        			time_t mtime=0;
        			mtime=st1.st_mtime;
        			typedef struct tm tstamp;
        			tstamp *tsXml=NULL;
        			tsXml=object->getTstamp();
        			//log->getOfs()<<"SQL : time compare : "<<mtime<<" ? "<<mktime(tsXml)<<endl<<flush;
        			if(mktime(tsXml)>mtime) {
        				_updateByTimestamp=true;
        			}
        		}
        		version=versionN;
        		//log->getOfs()<<"SQL : dataset version "<<versionN<<endl<<flush;
        		if(versionN<CURRENT_VER) {
        			log->getOfs()<<"SQL : upgrade "<<endl<<flush;
        			versionNew=CURRENT_VER;
        			upgrade();
        		} /*else if(_updateByTimestamp && !(object->getUninstalled())) { if updateFlag
        			upgrade();
        			object->serialize();
        		}*/
        		if(object->getVersion()<1) {
        			log->getOfs()<<"Upgrade : : "<<object->getName()<<endl<<flush;
        			upgrade();
        			object->setVersion(1);
        			//object->clearLinks();
        			object->serialize();
        		}
        		initFlag=true;
        		//insertLinks();
        		close();
        	}
    
    //Test
    /*
    log->getOfs()<<"********************* indexOrder:TEST ************************"<<endl<<flush;
    string testOut="";
    string hex="";
    encodeOrdpathNum(21157,testOut);
    log->getOfs()<<testOut<<endl<<flush;
    bin2hex(testOut.c_str(),hex,NULL);
    log->getOfs()<<hex<<endl<<flush;
    int num=0;
    num=decodeOrdpathNum(hex);
    log->getOfs()<<num<<endl<<flush;
    
    testOut.clear();
    encodeOrdpathNum(21156,testOut);
    log->getOfs()<<testOut<<endl<<flush;
    bin2hex(testOut.c_str(),hex,NULL);
    log->getOfs()<<hex<<endl<<flush;
    num=decodeOrdpathNum(hex);
    log->getOfs()<<num<<endl<<flush;
    hex="fc8319";
    num=decodeOrdpathNum(hex);
    log->getOfs()<<num<<endl<<flush;
    
    log->getOfs()<<"===================== indexOrder:TEST ========================"<<endl<<flush;
    */
    //#]
}

void OrderIndexSQL::initFill() {
    //#[ operation initFill()
    	{
    		string _str;
    		xmlNodePtr _xmlLink=NULL;
    		QueryXml q(object->getObjectNode());
            //q.setUnlink(true);
    
    /*
    	Link Source is:
    	1. xml document links
    	2. in memory parent->child releation database
    */
            
    		_str=string("/*[self::pages or self::objects or self::lobjs]/*");
    		log->getOfs()<<"initFill:q:"<<_str<<endl<<flush;
    		q.run((char*)(_str.c_str()));
    		q.result(_xmlLink);
    		int _pos=-1;
    		vector<int> _ordVec;
    		string _pS="a";
    		string _pE="";
    		string _curS=_pS;
    		string _curE=_pE;
    		string _newS;
    		string _next;
    		
    		_ordVec.push_back(_pos);
    		int _lasti=0;
    		string _numHex,_posHex,_prefixHex;
    		string _numBin;
    		while(_xmlLink){
    			char *zErrMsg = 0;
    
    			int _ret = 0;
    			
    			if(0){
    			_lasti=_ordVec.size()-1;
    			_ordVec[_lasti]=_ordVec[_lasti]+2;
    			if(_ordVec[_lasti]>3) {
    				_ordVec[_lasti]=1;
    				_ordVec.push_back(1);
    			}
    			_numBin.clear();
    			_posHex.clear();
    			log->getOfs()<<"initFill:n:"<<flush;
    			vector<int>::iterator it;
    			for ( it=_ordVec.begin() ; it < _ordVec.end(); it++ ){
    				_numBin.clear();
                	encodeOrdpathNum(*it,_numBin);
                	bin2hex(_numBin.c_str(),_numHex,NULL);
                	_posHex.append(_numHex);
                	//log->getOfs()<<*it<<"("<<_numBin<<")"<<","<<flush;
    			}
    			log->getOfs()<<endl<<flush;
    			log->getOfs()<<"initFill:hex:"<<_numBin<<endl<<flush;
                //bin2hex(_numBin.c_str(),_posHex,NULL);
                }//disable
    
    
    			_numBin.clear();
    			_next=_pE;
               	makeNewBitString(_curS,_curE,_newS);
               	_curS=_newS;
               	log->getOfs()<<"("<<_newS<<")"<<","<<flush;
                
                _posHex=_newS;
                //bin2hex(_newS.c_str(),_posHex,NULL);
                //log->getOfs()<<"("<<_posHex<<")"<<","<<flush;
                
                this->i_ordhex=_posHex;
    			this->i_tag=(char*)_xmlLink->name;
    			this->i_value=(char*)xmlNodeGetContent(_xmlLink);
    			insert();			
    			q.result(_xmlLink);
    		}   
    		setVersion(1);
    	}
    //#]
}

void OrderIndexSQL::initPrefixMapping() {
    //#[ operation initPrefixMapping()
    if(0){
    	//Init Prefix Mapping and set prefixDB
       		char *zErrMsg = 0;
       		int _ret = sqlite3_open(fileName.c_str(),&pDb);
    
    _ret = sqlite3_exec(pDb, "CREATE TABLE prefixMapping (prefix TEXT PRIMARY KEY,Li INTEGER,Omin INTEGER,Omax INTEGER)", 0, 0, &zErrMsg);
    if( _ret!=SQLITE_OK ){
        log->getOfs()<<"SQL error: "<<zErrMsg<<endl<<flush;
        sqlite3_free(zErrMsg);
    }
    
    		_ret = sqlite3_exec(pDb, "INSERT INTO prefixMapping VALUES( '000000001', 20, -1118485, -69910 )", 0, 0, &zErrMsg);
    		_ret = sqlite3_exec(pDb, "INSERT INTO prefixMapping VALUES( '00000001', 16, -69909, -4374 )", 0, 0, &zErrMsg);
    		_ret = sqlite3_exec(pDb, "INSERT INTO prefixMapping VALUES( '0000001', 12, -4373, -278 )", 0, 0, &zErrMsg);
    		_ret = sqlite3_exec(pDb, "INSERT INTO prefixMapping VALUES( '000001', 8, -277, -22 )", 0, 0, &zErrMsg);
    		_ret = sqlite3_exec(pDb, "INSERT INTO prefixMapping VALUES( '00001', 4, -21, -6 )", 0, 0, &zErrMsg);
    		_ret = sqlite3_exec(pDb, "INSERT INTO prefixMapping VALUES( '0001', 2, -5, -2 )", 0, 0, &zErrMsg);
    		_ret = sqlite3_exec(pDb, "INSERT INTO prefixMapping VALUES( '001', 1, -1, 0 )", 0, 0, &zErrMsg);
    		_ret = sqlite3_exec(pDb, "INSERT INTO prefixMapping VALUES( '01', 0, 1, 1 )", 0, 0, &zErrMsg);
    		_ret = sqlite3_exec(pDb, "INSERT INTO prefixMapping VALUES( '10', 1, 2, 3 )", 0, 0, &zErrMsg);
    		_ret = sqlite3_exec(pDb, "INSERT INTO prefixMapping VALUES( '110', 2, 4, 7 )", 0, 0, &zErrMsg);
    		_ret = sqlite3_exec(pDb, "INSERT INTO prefixMapping VALUES( '1110', 4, 8, 23 )", 0, 0, &zErrMsg);
    		_ret = sqlite3_exec(pDb, "INSERT INTO prefixMapping VALUES( '11110', 8, 24, 279 )", 0, 0, &zErrMsg);
    		_ret = sqlite3_exec(pDb, "INSERT INTO prefixMapping VALUES( '111110', 12, 280, 4375 )", 0, 0, &zErrMsg);
    		_ret = sqlite3_exec(pDb, "INSERT INTO prefixMapping VALUES( '1111110', 16, 4376, 69911 )", 0, 0, &zErrMsg);
    		_ret = sqlite3_exec(pDb, "INSERT INTO prefixMapping VALUES( '11111110', 20, 69912, 1118487 )", 0, 0, &zErrMsg);
       		if(pDb!=NULL) sqlite3_close(pDb);
    }
    //#]
}

void OrderIndexSQL::insert() {
    //#[ operation insert()
    int rc, i, ncols, id, cid;
    //sqlite3 *db=pDb;
    sqlite3_stmt *stmt;
    char *sql;
    
    if(pDb==NULL) return;
    
    sql = sqlite3_mprintf("INSERT INTO nodes VALUES('%q','%q','%q','%q','','%q')\0",i_ordhex.c_str(),"",(this->i_tag).c_str(),(this->i_value).c_str(),(this->i_namid).c_str());
    
    //log->getOfs()<<"SQL : cmd: "<<sql<<endl<<flush;
    
    sqlite3_prepare(pDb, sql, strlen(sql), &stmt, NULL);
    
    //while(rc == SQLITE_ROW) {
    	//id = sqlite3_column_int(stmt, 0);
    	//cid = sqlite3_column_int(stmt, 1);
    	//name = sqlite3_column_text(stmt, 2);
    	//if(name != NULL){
    	//	fprintf(stderr, "Row: id=%i, cid=%i, name='%s'\n", id,cid,name);
    	//} else {
    		/* Field is NULL */
    	//	fprintf(stderr, "Row: id=%i, cid=%i, name=NULL\n", id,cid);
    	//}
    	rc = sqlite3_step(stmt);
    //} 
    //indexer->getLog()<<"rc "<<rc;
    //indexer->getLog()<<endl<<flush;
    
    sqlite3_finalize(stmt);
    sqlite3_free(sql);
    //#]
}

void OrderIndexSQL::makeNewBitString(string & leftB, string & rightB, string & out) {
    //#[ operation makeNewBitString(string &,string &,string &)
    /*
    if(leftB.size()>rightB.size()) {
    	out=leftB+'1';
    } else {
    	out=rightB;
    	out[out.size()-1]='0';
    	out=out+'1';
    }
    */
    
    int maxLen=30;
    
    if(rightB.empty()){
    	//increment
    	if(leftB.size()<maxLen) {
    		out=leftB;
    		out.push_back('a');
    	} else {
    		out=leftB;
    		string::reverse_iterator rit;
    		for ( rit=out.rbegin() ; rit < out.rend(); rit++ ){
    			if(*rit>='z') *rit='a'; 
    			else {(*rit)++;break;}
    			rit++;
    		}
    		
    	}
    } else {
    	//create string
    }
    /*
    char nc[] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
    map<char,int> ord0;
    
    lenL=leftB.size();
    lenR=rightB.size();
    
    string _prefix="";
    
    for(int i=0;i<16;i++) {
    	map[nc[i]]=i;
    }
    */
    
    //if(lenL<maxLen) _prefix=leftB;
    //if(leftB[lenL-1]>='z')   
    //if(leftB.size()>rightB.size()) {
    	//get left
    	//check if last in range
    //} else {
    	//get right
    	//decrement last 
    	//append first in range
    
    //#]
}

void OrderIndexSQL::open() {
    //#[ operation open()
    char *zErrMsg = 0;
    
    struct stat st1;
    
    if(pDb==NULL) {
        	fileName=createFileName();
    //    	log->getOfs()<<"SQL : open: "<<fileName<<endl<<flush;
        	int er=stat(fileName.c_str(),&st1);
        	if(er>=0){
        		//Index exist.Open it
        		int _ret = sqlite3_open(fileName.c_str(),&pDb);
            }
    } else {
    	//Database still opened
    	//Possible in memory db
    }
    //#]
}

void OrderIndexSQL::remove(char* linkName) {
    //#[ operation remove(char*)
    int rc, i, ncols, id, cid;
    //sqlite3 *db=pDb;
    sqlite3_stmt *stmt=NULL;
    char *sql;
    
    if(pDb==NULL) return;
    
    sql = sqlite3_mprintf("DELETE FROM nodes WHERE value='%q'\0",linkName);
    
    log->getOfs()<<"SQL : remove: "<<sql<<endl<<flush;
    
    sqlite3_prepare(pDb, sql, strlen(sql), &stmt, NULL);
    rc = sqlite3_step(stmt);
    while(rc == SQLITE_ROW) {
    	rc = sqlite3_step(stmt);
    }
    
    sqlite3_finalize(stmt);
    sqlite3_free(sql);
    
    //#]
}

void OrderIndexSQL::setOrdhexFor(ObjectP * obj) {
    //#[ operation setOrdhexFor(ObjectP *)
    string ordhex=getLastOrdinal();
    string _curE="";
    string _newS;
    string _posHex;
    string ordbin;
                
                log->getOfs()<<"setOrdHex : last Ordinal: "<<ordhex<<endl<<flush;
                
                //if(ordhex.empty()) return;
                
                //hex2bin(ordhex,ordbin);
                
                //log->getOfs()<<"SQL : last Ordinal bin: "<<ordbin<<endl<<flush;
                map<string,ObjectP *> *ordMap=NULL;
                if(obj->getParent()) ordMap=obj->getParent()->getChildrenMapOrd();
                map<string,ObjectP *>::reverse_iterator rit;
    
                if(ordMap)
                if(!(ordMap->empty())) {
                	rit=ordMap->rbegin();
    				log->getOfs()<<"setOrdHex : last Ordinal compare: "<<rit->first<<" ? "<<ordhex<<endl<<flush;            
    
                	if(!lexicographical_compare((rit->first).begin(),(rit->first).end(),ordhex.begin(),ordhex.end())) {
                		ordhex=rit->first;
                	}
                }
                
                log->getOfs()<<"setOrdHex : last Ordinal: "<<ordhex<<endl<<flush;            
                makeNewBitString(ordhex,_curE,_newS);
                
                //bin2hex(_newS.c_str(),_posHex,NULL);
                
                obj->setOrdhex(_newS);
    
    //#]
}

void OrderIndexSQL::setRegistry(char* name, const char * value) {
    //#[ operation setRegistry(char*,char *)
    int rc, i, ncols, id, cid;
    //sqlite3 *db=pDb;
    sqlite3_stmt *stmt;
    char *sql;
    
    if(strlen(value)>0) {
    
    	sql = sqlite3_mprintf("INSERT INTO registry(name,value) VALUES('%q','%q')\0",name,value);
    
    	sqlite3_prepare(pDb, sql, strlen(sql), &stmt, NULL);
    
    	rc = sqlite3_step(stmt);
    	log->getOfs()<<"SQL:"<<sql<<" :"<<sqlite3_errmsg(pDb)<<endl<<flush;
    
    	sqlite3_finalize(stmt);
    	sqlite3_free(sql);
    
    } else {
    
    	sql = sqlite3_mprintf("DELETE FROM registry WHERE name='%q'\0",name);
    
    	sqlite3_prepare(pDb, sql, strlen(sql), &stmt, NULL);
    
    	rc = sqlite3_step(stmt);
    	log->getOfs()<<"SQL:"<<sql<<" :"<<sqlite3_errmsg(pDb)<<endl<<flush;
    
    	sqlite3_finalize(stmt);
    	sqlite3_free(sql);
    
    }
    //#]
}

void OrderIndexSQL::setVersion(int num) {
    //#[ operation setVersion(int)
    int rc, i, ncols, id, cid;
    //sqlite3 *db=pDb;
    sqlite3_stmt *stmt;
    char *sql;
    
    //if(version==0) {
    	sql = sqlite3_mprintf("INSERT INTO version VALUES(%d)\0",this->versionNew);
    //} else {
    //	sql = sqlite3_mprintf("UPDATE version SET num=%d\0",this->versionNew);
    //}
    
    //log->getOfs()<<"SQL : setVersion: "<<sql<<endl<<flush;
    
    sqlite3_prepare(pDb, sql, strlen(sql), &stmt, NULL);
    
    rc = sqlite3_step(stmt);
    
    sqlite3_finalize(stmt);
    sqlite3_free(sql);
    //#]
}

void OrderIndexSQL::update() {
    //#[ operation update()
    int rc, i, ncols, id, cid;
    //sqlite3 *db=pDb;
    sqlite3_stmt *stmt;
    char *sql;
    
    if(pDb==NULL) return;
    
    //update nodes set tag='pageIC112' where value = 'test'
    sql = sqlite3_mprintf("update nodes set tag='%q' where value = '%q'\0",(this->i_tag).c_str(),(this->i_value).c_str());
    
    log->getOfs()<<"SQL : cmd: "<<sql<<endl<<flush;
    
    sqlite3_prepare(pDb, sql, strlen(sql), &stmt, NULL);
    
    //while(rc == SQLITE_ROW) {
    	//id = sqlite3_column_int(stmt, 0);
    	//cid = sqlite3_column_int(stmt, 1);
    	//name = sqlite3_column_text(stmt, 2);
    	//if(name != NULL){
    	//	fprintf(stderr, "Row: id=%i, cid=%i, name='%s'\n", id,cid,name);
    	//} else {
    		/* Field is NULL */
    	//	fprintf(stderr, "Row: id=%i, cid=%i, name=NULL\n", id,cid);
    	//}
    	rc = sqlite3_step(stmt);
    //} 
    //indexer->getLog()<<"rc "<<rc;
    //indexer->getLog()<<endl<<flush;
    
    sqlite3_finalize(stmt);
    sqlite3_free(sql);
    //#]
}

void OrderIndexSQL::upgrade() {
    //#[ operation upgrade()
    /*
    */
    
    char *zErrMsg = 0;
    
    int _ret = 0;
    
    upgradePrepare();
    createTables();
    upgradeFill();
    upgradeFinish();
    
    //#]
}

void OrderIndexSQL::upgradeFill() {
    //#[ operation upgradeFill()
    initFill();
    //#]
}

void OrderIndexSQL::upgradeFinish() {
    //#[ operation upgradeFinish()
    char *zErrMsg = 0;
    
    int _ret = 0;
    
    _ret = sqlite3_exec(pDb, "DROP TABLE nodes_bak", callback1, 0, &zErrMsg);
    if( _ret!=SQLITE_OK ){
        log->getOfs()<<"SQL error: "<<zErrMsg<<endl<<flush;
        sqlite3_free(zErrMsg);
    }
    
    _ret = sqlite3_exec(pDb, "DROP TABLE referer_bak", callback1, 0, &zErrMsg);
    if( _ret!=SQLITE_OK ){
        log->getOfs()<<"SQL error: "<<zErrMsg<<endl<<flush;
        sqlite3_free(zErrMsg);
    }
    
    setVersion(1);
    
    //#]
}

void OrderIndexSQL::upgradePrepare() {
    //#[ operation upgradePrepare()
    
    char *zErrMsg = 0;
    
    int _ret = 0;
    
    _ret = sqlite3_exec(pDb, "ALTER TABLE nodes RENAME TO nodes_bak", callback1, 0, &zErrMsg);
    if( _ret!=SQLITE_OK ){
        log->getOfs()<<"SQL error: "<<zErrMsg<<endl<<flush;
        sqlite3_free(zErrMsg);
    }
    
    _ret = sqlite3_exec(pDb, "ALTER TABLE referer RENAME TO referer_bak", callback1, 0, &zErrMsg);
    if( _ret!=SQLITE_OK ){
        log->getOfs()<<"SQL error: "<<zErrMsg<<endl<<flush;
        sqlite3_free(zErrMsg);
    }
    
    _ret = sqlite3_exec(pDb, "DROP TABLE reference", callback1, 0, &zErrMsg);
    if( _ret!=SQLITE_OK ){
        log->getOfs()<<"SQL error: "<<zErrMsg<<endl<<flush;
        sqlite3_free(zErrMsg);
    }
    
    _ret = sqlite3_exec(pDb, "DROP TABLE reference_bak", callback1, 0, &zErrMsg);
    if( _ret!=SQLITE_OK ){
        log->getOfs()<<"SQL error: "<<zErrMsg<<endl<<flush;
        sqlite3_free(zErrMsg);
    }
    
    _ret = sqlite3_exec(pDb, "DROP TABLE version", callback1, 0, &zErrMsg);
    if( _ret!=SQLITE_OK ){
        log->getOfs()<<"SQL error: "<<zErrMsg<<endl<<flush;
        sqlite3_free(zErrMsg);
    }
    
    //#]
}

string OrderIndexSQL::getI_namid() const {
    return i_namid;
}

void OrderIndexSQL::setI_namid(string p_i_namid) {
    i_namid = p_i_namid;
}

string OrderIndexSQL::getI_ordhex() const {
    return i_ordhex;
}

void OrderIndexSQL::setI_ordhex(string p_i_ordhex) {
    i_ordhex = p_i_ordhex;
}

string OrderIndexSQL::getI_tag() const {
    return i_tag;
}

void OrderIndexSQL::setI_tag(string p_i_tag) {
    i_tag = p_i_tag;
}

string OrderIndexSQL::getI_tagc() const {
    return i_tagc;
}

void OrderIndexSQL::setI_tagc(string p_i_tagc) {
    i_tagc = p_i_tagc;
}

string OrderIndexSQL::getI_value() const {
    return i_value;
}

void OrderIndexSQL::setI_value(string p_i_value) {
    i_value = p_i_value;
}

sqlite3 * OrderIndexSQL::getPDb() const {
    return pDb;
}

void OrderIndexSQL::setPDb(sqlite3 * p_pDb) {
    pDb = p_pDb;
}

int OrderIndexSQL::getVersionNew() const {
    return versionNew;
}

void OrderIndexSQL::setVersionNew(int p_versionNew) {
    versionNew = p_versionNew;
}

/*********************************************************************
	File Path	: cmsv2lxImage/linux_static/Default/OrderIndexSQL.cpp
*********************************************************************/
