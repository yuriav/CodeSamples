/*********************************************************************
	Rhapsody	: 7.6.1 
	Login		: Administrator
	Component	: cmsv2lxImage 
	Configuration 	: linux_static
	Model Element	: multipartPost
//!	Generated Date	: Tue, 22, Nov 2016  
	File Path	: cmsv2lxImage/linux_static/StateMachines/multipartPost.rl
*********************************************************************/

#ifndef StateMachines_multipartPost_H
#define StateMachines_multipartPost_H

//Machine Definition
%%{

machine multipartPost;

action start_bn {
	//site->getFileLog()->getOfs()<<"start\n";
	site->getFileLog()->getOfs()<<""<<fc<<flush;
}

action write_bn {
	site->getFileLog()->getOfs()<<""<<fc<<flush;
}

action start_bc {
	//site->getFileLog()->getOfs()<<"start\n";
	site->getFileLog()->getOfs()<<""<<fc<<flush;
}

action write_bc {
	site->getFileLog()->getOfs()<<""<<fc<<flush;
}
action start_fn {
	//site->getFileLog()->getOfs()<<"start\n";
	site->getFileLog()->getOfs()<<""<<fc<<flush;
}

action write_field {
	site->getFileLog()->getOfs()<<"*"<<fc<<flush;
	post_field.push_back(fc);
}
action start_fv {
	//site->getFileLog()->getOfs()<<"start\n";
	site->getFileLog()->getOfs()<<""<<fc<<flush;
}

action write_param {
	//site->getFileLog()->getOfs()<<""<<fc<<flush;
	post_param.push_back(fc);
}

action next_param {
	site->getFileLog()->getOfs()<<"next Param"<<endl<<flush;
	site->getFileLog()->getOfs()<<"f:"<<post_field<<endl<<flush;
	site->getFileLog()->getOfs()<<"p:"<<post_param<<endl<<flush;
	site->getFileLog()->getOfs()<<"v:"<<post_value<<endl<<flush;
	if(strcmp(post_field.c_str(),"Content-Disposition")==0)
	if(strcmp(post_param.c_str(),"filename")==0)
	{
		n_tmp=xmlNewDocNode(doc,NULL,(xmlChar*)"arg3",NULL);
		xmlAddChild(n_stdin,n_tmp);
		xmlNodePtr n_text=xmlNewDocText(doc,(xmlChar*)(post_value.c_str()));
		xmlAddChild(n_tmp,n_text);
		n_tmp=NULL;
		binaryFile=post_value;
	} 
	if(strcmp(post_field.c_str(),"Content-Disposition")==0)
	if(strcmp(post_param.c_str(),"name")==0)
	if(strncmp(post_value.c_str(),"arg1",4)==0)
	{
		n_tmp=xmlNewDocNode(doc,NULL,(xmlChar*)"arg1",NULL);
		xmlAddChild(n_stdin,n_tmp);
	} 
	if(n_tmp==NULL && strcmp(post_param.c_str(),"name")==0) {
		postStr.append(post_value);
		postStr.append("=");
	}
	post_param.clear();
	post_value.clear();
}

action next_boundary {
	site->getFileLog()->getOfs()<<"next boundary"<<endl<<flush;
	isBinary=false;
}

action next_field {
	site->getFileLog()->getOfs()<<"next Field"<<endl<<flush;
	site->getFileLog()->getOfs()<<"f:"<<post_field<<endl<<flush;
	site->getFileLog()->getOfs()<<"p:"<<post_param<<endl<<flush;
	site->getFileLog()->getOfs()<<"v:"<<post_value<<endl<<flush;

	if(strcmp(post_field.c_str(),"Content-Type")==0) {
		isBinary=true;
		contentType=post_param;
	}

	if(strcmp(post_field.c_str(),"Content-Disposition")==0)
	if(strcmp(post_param.c_str(),"filename")==0)
	{
		n_tmp=xmlNewDocNode(doc,NULL,(xmlChar*)"arg3",NULL);
		xmlAddChild(n_stdin,n_tmp);
		size_t found=string::npos;
		string key ("\\");
		found=post_value.rfind(key);
		if (found!=string::npos) {
			post_value.erase(0,found+1);
		}
		key="/";
		found=post_value.rfind(key);
		if (found!=string::npos) {
			post_value.erase(0,found+1);
		}
        
		key=".";
		found=post_value.rfind(key);
		if (found!=string::npos) {
			//SegFault possible
			file_ext=post_value.substr(found+1);
			post_value.erase(found);
		}

		xmlNodePtr n_text=xmlNewDocText(doc,(xmlChar*)(post_value.c_str()));
		xmlAddChild(n_tmp,n_text);
		n_tmp=NULL;
		binaryFile=post_value;
	} 
	if(strcmp(post_field.c_str(),"Content-Disposition")==0)
	if(strcmp(post_param.c_str(),"name")==0)
	if(strncmp(post_value.c_str(),"arg1",4)==0)
	{
		n_tmp=xmlNewDocNode(doc,NULL,(xmlChar*)"arg1",NULL);
		xmlAddChild(n_stdin,n_tmp);
	} 
	if(n_tmp==NULL && strcmp(post_param.c_str(),"name")==0) {
		postStr.append(post_value);
		postStr.append("=");
	}
	post_field.clear();
	post_param.clear();
	post_value.clear();
}

action write_value {
	site->getFileLog()->getOfs()<<fc<<flush;
	post_value.push_back(fc);
}

action data_begin {
    site->getFileLog()->getOfs()<<"data begin"<<fc<<endl<<flush;
	site->getFileLog()->getOfs()<<"f:"<<post_field<<endl<<flush;
	site->getFileLog()->getOfs()<<"p:"<<post_param<<endl<<flush;
	site->getFileLog()->getOfs()<<"v:"<<post_value<<endl<<flush;

	if(strcmp(post_field.c_str(),"Content-Type")==0) {
		isBinary=true;
		contentType=post_param;
	}
	
	if(!contentType.empty()) {
		binarySize=0;
		string _objectDir=/*site->getObjInstallDir()+string("/")+site->getName()*/string("/root")+objectPath;
		site->getFileLog()->getOfs()<<"objectDir:"<<_objectDir<<endl<<flush;
		_Obj=site->loadObject(_objectDir);
		//site->getFileTypeByExt(fileExt);
		//site->getFileTypeByMime();
		
		_binaryObj=_Obj->addNewChild((char*)binaryFile.c_str(),(char*)binaryFile.c_str(),"file");

		xmlNodePtr n_1=_binaryObj->getContentDocRoot();
		xmlAddChild(n_1,xmlNewDocNode(_binaryObj->getContentDoc(),NULL,(xmlChar*)"mime",(xmlChar*)contentType.c_str()));
		xmlAddChild(n_1,xmlNewDocNode(_binaryObj->getContentDoc(),NULL,(xmlChar*)"extension",(xmlChar*)file_ext.c_str()));
			_ContentLength=getenv("CONTENT_LENGTH");
			if(_ContentLength){
				site->getFileLog()->getOfs()<<"Content Length:"<<_ContentLength<<endl<<flush;
			}
        xmlAddChild(n_1,xmlNewDocNode(_binaryObj->getContentDoc(),NULL,(xmlChar*)"length",(xmlChar*)_ContentLength));
        
		_binaryObj->serialize();

		site->getFileLog()->getOfs()<<"objectDir:"<<_binaryObj->getPath()<<endl<<flush;
		string _filePath=site->getObjInstallDir()+_binaryObj->getPath()+_binaryObj->getName()+string("/file.orig");
		site->getFileLog()->getOfs()<<"objectDir:"<<_filePath<<endl<<flush;
		binaryFD=open(_filePath.c_str(),O_CREAT | O_TRUNC | O_WRONLY,S_IRUSR | S_IWUSR);
		_bufOffset=fpc+1;//skip NL
		if(_bufOffset>&str[B1SIZE-1]) _bufOffset=str; //Rololback offset
	}
	if(strcmp(post_field.c_str(),"Content-Disposition")==0)
	if(strcmp(post_param.c_str(),"name")==0)
	if(strncmp(post_value.c_str(),"arg1",4)==0)
	{                                                                     
		n_tmp=xmlNewDocNode(doc,NULL,(xmlChar*)"arg1",NULL);
		xmlAddChild(n_stdin,n_tmp);
	} 
	if(n_tmp==NULL && strcmp(post_param.c_str(),"name")==0) {
		postStr.append(post_value);
		postStr.append("=");
	}
}

action write_data {
        site->getFileLog()->getOfs()<<fc<<flush;
        
        if(!doCopyAhead) {
        	bytes2=read(STDIN_FILENO,&str[bytes],B2SIZE-1);
        	if(bytes2>0){
        		doCopyAhead=true;
        		//memcpy((void*)(&str[B1SIZE]),(void*)ahead,bytes);
        	}
        }
        //if(copyAhead) site->getFileLog()->getOfs()<<"!!!Buffers ["<<fpc<<"]"<<endl<<flush;
        if(strncmp(fpc,boundaryStr.c_str(),boundaryStr.size())==0) {
            site->getFileLog()->getOfs()<<"jump_b:"<<post_data<<" "<<isBinary<<flush;
            
            if(!isBinary) {
            	post_data.erase(post_data.size()-2);
				if(n_tmp) {
					xmlNodePtr n_text=xmlNewDocText(doc,(xmlChar*)(post_data.c_str()));
					xmlAddChild(n_tmp,n_text);
					objectPath=post_data;
					n_tmp=NULL;
				} else {
					site->getFileLog()->getOfs()<<"data:"<<post_data<<endl<<flush;
					postStr.append(post_data);
				}
            } else {
				site->getFileLog()->getOfs()<<"bs:"<<_size<<endl<<flush;
				_size=_size-2;
            }
            
            if(strncmp(fpc+boundaryStr.size(),"--",2)==0) {
            	site->getFileLog()->getOfs()<<"end post"<<flush;
            	//fpc=fpc+boundaryStr.size()+1;
            	done=true;
            	fpc=pe-1;
            } else {
            	if(n_tmp==NULL && !isBinary) postStr.append("&");
            }
            
            post_data.clear();
			post_field.clear();
			post_param.clear();
			post_value.clear();
			contentType.clear();
           	fnext boundary;
        } else {
        	if(!isBinary) {
				post_data.push_back(fc);
			} else {
				_size=fpc-_bufOffset+1;
			}
		}
}

action next_b {
        site->getFileLog()->getOfs()<<"next b"<<fc<<flush;
}

action go_fname {
        site->getFileLog()->getOfs()<<"go(fname)"<<fc<<flush;
}
action go_param {
        site->getFileLog()->getOfs()<<"go(param)"<<fc<<flush;
}
action go_value {
        site->getFileLog()->getOfs()<<"go(value)"<<fc<<flush;
}
action go_ {
        site->getFileLog()->getOfs()<<"go()"<<fc<<flush;
}

# line endings
  CRLF = "\r\n";

# character types
  CTL = (cntrl | 127);
  safe = ("$" | "-" | "_" | ".");
  extra = ("!" | "*" | "'" | "(" | ")" | ",");
  reserved = (";" | "/" | "?" | ":" | "@" | "&" | "=" | "+");
  unsafe = (CTL | " " | "\"" | "#" | "%" | "<" | ">");
  national = any -- (alpha | digit | reserved | extra | safe | unsafe);
  unreserved = (alpha | digit | safe | extra | national);
  escape = ("%" xdigit xdigit);
  uchar = (unreserved | escape | "/");
  pchar = (uchar | ":" | "@" | "&" | "=" | "+");
  tspecials = ("(" | ")" | "<" | ">" | "@" | "," | ";" | ":" | "\\" | "\"" | "/" | "[" | "]" | "?" | "=" | "{" | "}" | " " | "\t");

  token = (ascii -- (CTL | tspecials));

  #field_value = any* >start_fv %write_fv;
  
  #params = ( field_value ( ";" " "* field_value )* ) ;

  #field_name = ( token -- ":" )+ >start_fn %write_fn;

  #message_header = field_name ":" " "* params :> CRLF;
  
  #boundaryNumber = uchar* >start_bc %write_bc;
  #boundary = "-"* boundaryNumber CRLF >start_bn %write_bn;

main :=
start:
#boundary: (
#  "-" @write_bn -> boundary |
#  (alpha | digit) @write_bn -> boundary |
#  CRLF @go_fname -> fname
#  ),
boundary: (
  loop:("-" @write_bn -> boundary::loop |
  (alpha | digit) @write_bn -> boundary::loop |
  CRLF @go_fname -> fname)) >next_boundary,
fname: (
#  uchar @ 3 @write_field -> fname |
#  " " @ 3 -> fname |
#  ":" @ 1 @go_param -> param) >next_field,
  loop:(uchar @ 3 @write_field -> fname::loop |
  " " @ 3 -> fname::loop |
  ":" @ 1 @go_param -> param)) >next_field,
param: (
  uchar @write_param -> param |
  " " -> param |
  "=" @go_value -> value |
  ";" @next_param -> param |
  CRLF -> fname |
  CRLF CRLF @data_begin -> data
),
value: (
  pchar @write_value -> value |
  ("\"" | " ") -> value |
  ";" @next_param -> param |
  CRLF -> fname |
  CRLF CRLF @data_begin -> data),
data: (
#  "-------" @next_b -> boundary |
  any @write_data -> data
);
}%%

//Implementation
%% write data;

#define BSIZE 2000
#define B1SIZE 990
#define B2SIZE 990
int cs;
int res=0;
int bytes=0;
int bytes2=0;
char *p, *pe;
char str[BSIZE]="\0";
char ahead[B2SIZE];
char *eof=0;

bool done=false;
bool doCopyAhead;
doCopyAhead=false;

str[0]='\0';
str[BSIZE-1]='\0';

string buffer;
buffer.clear();

string post_field("");
string post_param("");
string post_value("");
string post_data("");
string post_data_crlf("");
string postStr("");
string objectPath("");
string binaryFile("");
string contentType("");
string file_ext("");
ObjectP *_binaryObj=NULL;
char *_bufOffset=str;
long _size=0;
bool isBinary=false;

int binaryFD=0;
long binarySize=0;

int _progress=0;
string buffer1("");
ObjectP *_Obj=NULL;

char *_ContentLength=NULL;

site->getFileLog()->getOfs()<<"Start Parse Post\n"<<flush;

%% write init;

bytes=read(STDIN_FILENO,str,B1SIZE);
site->getFileLog()->getOfs()<<"Start Parse Post\n"<<str<<flush;
_progress=0;
int _progressValOld=0;
curl_global_init(CURL_GLOBAL_ALL);
if(strncmp(str,"<?xml",5)!=0){
	while(bytes>0){
		p = str;
		pe = p + bytes;
		_bufOffset=str;
		_size=0;
		
		while(p!=pe) {

			%% write exec;

		}
		site->getFileLog()->getOfs()<<"end buffer\n"<<flush;
        if(isBinary) {
		site->getFileLog()->getOfs()<<"Message Server:"<<(string("http://")+site->getDomain()+string(":6969"))<<endl<<flush;
		_progress++;
/*
MessageSystem ms=...;
MessagePipe mp
Message msg  (xml->json);
msg.send(mp);
*/
		CURL *curl=NULL;
		CURLcode _res;
		
		curl=curl_easy_init();
		if(curl){
            
            FILE *curlErr=NULL;
/*
			json_tokener *tok;
			json_object *my_string, *my_int, *params, *my_object, *my_array;
			json_object *new_obj;

			my_array = json_object_new_array();
			my_object = json_object_new_object();
			json_object_array_add(my_array,my_object);
			params = json_object_new_object();
			json_object_object_add(my_object,"cmd",json_object_new_string("inlinepush"));
			json_object_object_add(my_object,"params",params);
			json_object_object_add(params,"password",json_object_new_string("testpasswd"));
			json_object_object_add(params,"raw",json_object_new_string("postmsg"));
			json_object_object_add(params,"channel",json_object_new_string("testchannel"));

			json_object *data1 = json_object_new_object();
			json_object_object_add(params,"data",data1);
			json_object_object_add(data1,"message",json_object_new_string("aaaaaaaaaaaaaaaaa"));
			json_object_object_add(data1,"percent",json_object_new_int(_progress));
			
			site->getFileLog()->getOfs()<<"my_array.to_string()="<<json_object_to_json_string(my_array)<<endl<<flush;
*/			

json_t *array=NULL;

array=json_array();
json_t *root=json_object();
json_array_append(array,root);
json_object_set_new(root,"cmd",json_string("inlinepush"));
json_t *params=json_object();
json_object_set(root,"params",params);
json_object_set_new(params,"password",json_string("testpasswd"));
json_object_set_new(params,"raw",json_string("postmsg"));
json_object_set_new(params,"channel",json_string((string("channel(uuid(")+_Obj->getId()+string("))")).c_str()));
json_t *data=json_object();
json_object_set(params,"data",data);
json_object_set_new(data,"message",json_string("Test message"));
int _progressVal=(int)round((_progress*100)/(atoi(_ContentLength)/B2SIZE));
json_object_set_new(data,"percent",json_integer(_progressVal));
char *jsonDump=json_dumps(array,JSON_COMPACT | JSON_PRESERVE_ORDER);
site->getFileLog()->getOfs()<<"my_array.to_string()="<<jsonDump<<endl<<flush;
free(jsonDump);

//printf("my_array.to_string()=%s\n", json_dumps(array,JSON_COMPACT | JSON_PRESERVE_ORDER));

/*
	if(_progressVal>_progressValOld) {
			curl_easy_setopt(curl, CURLOPT_URL, (string("http://")+site->getDomain()+string(":6969")).c_str());
			curl_easy_setopt(curl, CURLOPT_POST, true);
			char *jsonDump=json_dumps(array,JSON_COMPACT | JSON_PRESERVE_ORDER);
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS,jsonDump);
			curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
			curlErr=fopen("curl.err","w");
			curl_easy_setopt(curl, CURLOPT_STDERR, curlErr);
			curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &WebInterface::WriteMemoryCallback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer1);
			curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

			_res = curl_easy_perform(curl);
			free(jsonDump);
			fclose(curlErr);
			if (_res != CURLE_OK) {
				site->getFileLog()->getOfs()<<"Curl perform failed: " << curl_easy_strerror(_res)<<endl<<flush;
			}
			site->getFileLog()->getOfs()<<"out:"<<buffer1<<endl<<flush;
            buffer1.clear();
            _progressValOld=_progressVal;
	}
*/
//json_array_clear(array);
json_decref(array);
//json_object_clear(data);
//json_object_del(params,"data");
//json_object_del(root,"params");
json_decref(data);
json_decref(params);
json_decref(root);

/*
json_object_del(params,"data");
json_object_del(root,"params");
json_decref(data);
json_decref(params);
json_decref(root);
*/
		}
		curl_easy_cleanup(curl);
		}
		
		if(isBinary && _size>0) {
			if(binaryFD) {
				site->getFileLog()->getOfs()<<"write buffer:"<<(void*)str<<" "<<(void*)_bufOffset<<" "<<_size<<endl<<flush;
				site->getFileLog()->getOfs()<<"offset:"<<(long)(_bufOffset-str)<<endl<<flush;
				long _c=write(binaryFD,_bufOffset,_size);
				site->getFileLog()->getOfs()<<"write "<<_c<<" bytes."<<endl<<flush;
				binarySize+=_c;
			} else {
				site->getFileLog()->getOfs()<<"Error open binary File\n"<<flush;
			}
		}
		if(done) {
			site->getFileLog()->getOfs()<<"file size "<<binarySize<<" bytes."<<" ext:"<<file_ext<<endl<<flush;
			site->getFileLog()->getOfs()<<"post str:"<<postStr<<endl<<flush;
			close(binaryFD);
			if(_binaryObj) {
				xmlNodePtr n_1=_binaryObj->getContentDocRoot();
				char sizeStr[200];
				sprintf(sizeStr,"%d",binarySize);
				xmlAddChild(n_1,xmlNewDocNode(_binaryObj->getContentDoc(),NULL,(xmlChar*)"size",(xmlChar*)sizeStr));
				bool isImage=false;
				if(strcmp(file_ext.c_str(),"jpg")==0) isImage=true;
				if(strcmp(file_ext.c_str(),"jpeg")==0) isImage=true;
				if(strcmp(file_ext.c_str(),"gif")==0) isImage=true;
				if(strcmp(file_ext.c_str(),"bmp")==0) isImage=true;
				if(strcmp(file_ext.c_str(),"JPG")==0) isImage=true;
				if(strcmp(file_ext.c_str(),"JPEG")==0) isImage=true;
				if(strcmp(file_ext.c_str(),"GIF")==0) isImage=true;
				if(strcmp(file_ext.c_str(),"BMP")==0) isImage=true;
				if(isImage) {
					ObjectP *ci=_binaryObj->convert();
					ci->getParent()->serialize();
					ci->serialize();
				} else {
					_binaryObj->serialize();
				}
			}
			break;
		}
		if(doCopyAhead) {
			site->getFileLog()->getOfs()<<"copy ahead buffer "<<bytes2<<endl<<flush;
			memcpy((void*)str,(void*)&str[bytes],bytes2);
			bytes=bytes2;
			doCopyAhead=false;
		} else {
			bytes=read(STDIN_FILENO,str,B1SIZE);
		}
	}

	n_tmp=xmlNewDocNode(doc,NULL,(xmlChar*)"post",NULL);
	xmlAddChild(n_stdin,n_tmp);
	//xmlNodePtr n_text=xmlNewDocText(doc,(xmlChar*)(postStr.c_str()));
	xmlNodePtr n_text=xmlNewCDataBlock(doc,(xmlChar*)(postStr.c_str()),postStr.size());
	xmlAddChild(n_tmp,n_text);
	n_tmp=NULL;
    
    curl_global_cleanup();

	site->getFileLog()->getOfs()<<"end scan\n"<<"post:"<<postStr<<flush;
} else {
	isMultipart=false;
	isXml=true;
	str[bytes]='\0';
	buf.append(str);
}  
#endif
/*********************************************************************
	File Path	: cmsv2lxImage/linux_static/StateMachines/multipartPost.rl
*********************************************************************/
