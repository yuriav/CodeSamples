/*********************************************************************
	Rhapsody	: 7.6.1 
	Login		: Administrator
	Component	: cmsv2lxImage 
	Configuration 	: linux_static
	Model Element	: formNameParse
//!	Generated Date	: Wed, 25, Jun 2014  
	File Path	: cmsv2lxImage/linux_static/StateMachines/formNameParse.rl
*********************************************************************/

#ifndef StateMachines_formNameParse_H
#define StateMachines_formNameParse_H

//Machine Definition
%%{

machine test1;

action accept { res = 1; }
action not_accept { res = 0; }
action nameCollect {buffer.push_back(fc);}
action xpathCollect {
	buffer.push_back(fc);
	if(fc=='/') {
		path.push_back(pathNode);
		pathNode.clear();
	} else { 
		pathNode.push_back(fc);
	}
}
action xpathStart {site->getFileLog()->getOfs()<<"name:"<<buffer<<endl<<flush;buffer.clear();}
action xpathEnd {
    xpath=buffer;
	site->getFileLog()->getOfs()<<"xpath:"<<xpath<<endl<<flush;buffer.clear();

	if(1){//Check for instance node existance
	site->getFileLog()->getOfs()<<"Check for missing nodes:"<<_postx<<endl<<flush;

	path.push_back(pathNode);pathNode.clear();
	vector<string>::iterator i;
	_node=_postx;
	string _str("");
	QueryXml q(_node);
	for(i=path.begin();i!=path.end();i++){
		xmlNodePtr _cnode=NULL;
		_str=*i;
		site->getFileLog()->getOfs()<<"test:"<<_str<<endl<<flush;
		if(_str.empty()) continue;
    	{		
    				QueryXml q2(q,_node);
    				q2.setLog(site->getFileLog());
    				q2.run((char*)(_str.c_str()));
    				q2.result(_cnode);
    			
		if(_cnode==NULL) {
			list<string>::reverse_iterator rit;
			list<string> xn=q2.getXpathNodes();
			site->getFileLog()->getOfs()<<"test:"<<xn.size()<<endl<<flush;
			/*
  			for ( rit=xn.rbegin() ; rit != xn.rend(); rit++ ) {
    			site->getFileLog()->getOfs()<<"test:"<<*rit<<endl<<flush;
            }*/
            if(!xn.empty()) {
            	rit=xn.rbegin();
				site->getFileLog()->getOfs()<<"add node 1:"<<*rit<<" to "<<_node->name<<endl<<flush;
				_cnode=xmlAddChild(_node,xmlNewNode(NULL, BAD_CAST (*rit).c_str()));
			} else {
				site->getFileLog()->getOfs()<<"add node 2:"<<_str<<" to "<<_node->name<<endl<<flush;
				_cnode=xmlAddChild(_node,xmlNewNode(NULL, BAD_CAST (_str).c_str()));
			}
		} else {
			if(isArray) {
			}
			/*xmlNodePtr _lookupNode=_node->children;
			while(_lookupNode) {
				if(strcmp((char*)(_lookupNode->name),(_str).c_str())==0) {
					break;
				}
				_lookupNode=_lookupNode->next;
			}
			if(_lookupNode==NULL) {
				_node=xmlAddChild(_node,xmlNewNode(NULL, BAD_CAST (_str).c_str()));
			}*/
			//_node=_node->children; 
		}
		}
		_node=_cnode; 

/*		if(_node->children==NULL) {
			site->getFileLog()->getOfs()<<"add node:"<<*i<<endl<<flush;
			xmlAddChild(_node,xmlNewNode(NULL, BAD_CAST (*i).c_str()));
		} else {
			xmlNodePtr _lookupNode=_node->children;
			while(_lookupNode) {
				if(strcmp((char*)(_lookupNode->name),(*i).c_str())==0) {
					break;
				}
				_lookupNode=_lookupNode->next;
			}
			if(_lookupNode==NULL) {
				_node=xmlAddChild(_node,xmlNewNode(NULL, BAD_CAST (*i).c_str()));
			}
		}
		_node=_node->children; 
*/
	}
	site->getFileLog()->getOfs()<<"xpath:"<<buffer<<endl<<flush;buffer.clear();
	path.clear();
	}

}
action endName {
  if(!xpath.empty()){
	result = xmlXPathEvalExpression((xmlChar*)(xpath.c_str()), context);
	if (result == NULL) {
		site->getFileLog()->getOfs()<<"Error in xmlXPathEvalExpression: "<<xpath<<endl<<flush;
		//return -1;
	}
	if(xmlXPathNodeSetIsEmpty(result->nodesetval)){
		xmlXPathFreeObject(result);
        site->getFileLog()->getOfs()<<"No result"<<endl<<flush;
	} else {
		xmlNodeSetPtr nodeset=result->nodesetval;
		site->getFileLog()->getOfs()<<"Result Nr "<<nodeset->nodeNr<<endl<<flush;
		bool _skip=false;
		if(nodeset->nodeTab[0]->children) {
			if(nodeset->nodeTab[0]->children->type==XML_CDATA_SECTION_NODE) {
				site->getFileLog()->getOfs()<<"Test XML_CDATA_SECTION_NODE"<<XML_CDATA_SECTION_NODE<<endl<<flush;
				site->getFileLog()->getOfs()<<"Test XML_CDATA_SECTION_NODE"<<nodeset->nodeTab[0]->children->type<<endl<<flush;
				xmlNodeSetContent(nodeset->nodeTab[0]->children,BAD_CAST buffer.c_str());
				_skip=true;
			}
		}
		if(!_skip) {
			site->getFileLog()->getOfs()<<"Test XML_CDATA_SECTION_NODE"<<XML_CDATA_SECTION_NODE<<endl<<flush;
			site->getFileLog()->getOfs()<<"Test XML_CDATA_SECTION_NODE"<<nodeset->nodeTab[0]->type<<endl<<flush;
			xmlNodeSetContent(nodeset->nodeTab[0],BAD_CAST buffer.c_str());
			xmlXPathFreeObject(result);
		}
	}
	isArray=false;
  }
	site->getFileLog()->getOfs()<<"value:"<<buffer<<endl<<flush;buffer.clear();xpath.clear();path.clear();
}
action valueStart {buffer.clear();}
action valueCollect {buffer.push_back(fc);}
action storeName {
	site->getFileLog()->getOfs()<<"store name:"<<buffer<<endl<<flush;buffer.clear();
}
action appendXPathComp {
	path.push_back(buffer);
	site->getFileLog()->getOfs()<<"append xpath component :"<<buffer<<endl<<flush;
	buffer.clear();
}

action setArray {
	isArray=true;
}

main :=
start:
State_3: (
  ([(] @ 3 -> State_4 |
  [=] @ 3 -> StateValue) @storeName |
  any @ 1 @nameCollect  -> State_3),
State_4: (
  [)] @ 3 @xpathEnd  -> State_5 |
  any @ 1 @xpathCollect  -> State_4),
State_5: (
  [=] @valueStart -> StateValue |
  "\0" @accept -> final),
StateValue: (
  [&] @ 3 @endName  -> final |
  any @ 1 @valueCollect -> StateValue);
}%%

//Implementation
%% write data;

  int cs;
  int res=0;
  char *p, *pe;

  p = str;
  pe = p + strlen(str);

  string buffer;
  string xpath;

  bool isArray=false; 
  xpath.clear();
  buffer.clear();
  xmlNodePtr _postx=instance;
  xmlNodePtr _node=NULL;
  int plevel=0;
  vector<string> path;
  string pathNode;
  pathNode.clear();
  path.clear();

  site->getFileLog()->getOfs()<<"Start Parse Post\n"<<flush;
  
  xmlXPathContextPtr context;
  xmlXPathObjectPtr result;

  context = xmlXPathNewContext((xmlDocPtr)instance);
  if (context == NULL) {
	site->getFileLog()->getOfs()<<"Error in xmlXPathNewContext"<<endl<<flush;
	return -1;
  }
  
  while(p!=pe) {

  %% write init;
  %% write exec;
  
  site->getFileLog()->getOfs()<<"end loop\n"<<flush;

  }

  //if(!path.empty()) xmlAddChild(_node,xmlNewText(BAD_CAST buffer.c_str()));

  if(!xpath.empty()){
	result = xmlXPathEvalExpression((xmlChar*)(xpath.c_str()), context);
	if (result == NULL) {
		site->getFileLog()->getOfs()<<"Error in xmlXPathEvalExpression: "<<xpath<<endl<<flush;
		//return -1;
	}
	if(xmlXPathNodeSetIsEmpty(result->nodesetval)){
		xmlXPathFreeObject(result);
        site->getFileLog()->getOfs()<<"No result"<<endl<<flush;
	} else {
		xmlNodeSetPtr nodeset=result->nodesetval;
		site->getFileLog()->getOfs()<<"Result Nr "<<nodeset->nodeNr<<endl<<flush;
		bool _skip=false;
		if(nodeset->nodeTab[0]->children) {
			if(nodeset->nodeTab[0]->children->type==XML_CDATA_SECTION_NODE) {
				site->getFileLog()->getOfs()<<"Test XML_CDATA_SECTION_NODE"<<XML_CDATA_SECTION_NODE<<endl<<flush;
				site->getFileLog()->getOfs()<<"Test XML_CDATA_SECTION_NODE"<<nodeset->nodeTab[0]->children->type<<endl<<flush;
				xmlNodeSetContent(nodeset->nodeTab[0]->children,BAD_CAST buffer.c_str());
				_skip=true;
			}
		}
		if(!_skip) {
			site->getFileLog()->getOfs()<<"Test XML_CDATA_SECTION_NODE"<<XML_CDATA_SECTION_NODE<<endl<<flush;
			site->getFileLog()->getOfs()<<"Test XML_CDATA_SECTION_NODE"<<nodeset->nodeTab[0]->type<<endl<<flush;
			xmlNodeSetContent(nodeset->nodeTab[0],BAD_CAST buffer.c_str());
			xmlXPathFreeObject(result);
		}
	}
  }


/*old
  if(!xpath.empty()){
	result = xmlXPathEvalExpression((xmlChar*)("'aaa' = 'aaa'"), context);
	if (result == NULL) {
		site->getFileLog()->getOfs()<<"Error in xmlXPathEvalExpression: "<<xpath<<endl<<flush;
		//return -1;
	}
	if(xmlXPathNodeSetIsEmpty(result->nodesetval)){
		site->getFileLog()->getOfs()<<"No result "<<result->type<<endl<<flush;
		xmlXPathFreeObject(result);
	} else {
		xmlNodeSetPtr nodeset=result->nodesetval;
		site->getFileLog()->getOfs()<<"Result Nr "<<nodeset->nodeNr<<endl<<flush;
		xmlNodeSetContent(nodeset->nodeTab[0],BAD_CAST buffer.c_str());
		xmlXPathFreeObject(result);
	}
  }
*/  
  site->getFileLog()->getOfs()<<"value:"<<buffer<<endl<<flush;buffer.clear();

  site->getFileLog()->getOfs()<<"end scan\n"<<flush;
  
  xmlXPathFreeContext(context);
  //xmlAddChild(httpParams,_postx);

		xmlBufferPtr _xbuf;
		const xmlChar *_xbufContent=NULL;
	
		_xbuf=xmlBufferCreate();
		xmlNodeDump(_xbuf,NULL,_postx,0,0);
		_xbufContent=xmlBufferContent(_xbuf);
		site->getFileLog()->getOfs()<<(char*)_xbufContent<<flush;
                xmlBufferFree(_xbuf);

  //xmlFreeNode(_node);
  _node=NULL;
  
  return res;

#endif
/*********************************************************************
	File Path	: cmsv2lxImage/linux_static/StateMachines/formNameParse.rl
*********************************************************************/
