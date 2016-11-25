/********************************************************************
	Rhapsody	: 7.6.1 
	Login		: Administrator
	Component	: cmsv2lxImage 
	Configuration 	: linux_static
	Model Element	: QueryXml
//!	Generated Date	: Wed, 25, Jun 2014  
	File Path	: cmsv2lxImage/linux_static/Default/QueryXml.cpp
*********************************************************************/

//## auto_generated
#include "Default/QueryXml.h"
//## link log
#include "Default/FileLog.h"
//## package Default

//## class QueryXml
QueryXml::QueryXml(xmlNodePtr root) {
    log = NULL;
    //#[ operation QueryXml(xmlNodePtr)
    this->doc=NULL;
    contextNode=root;
    context = xmlXPathNewContext((xmlDocPtr)contextNode);
    //context->namespaces = xmlGetNsList(contextNode->doc,contextNode);
    xmlXPathRegisterNs(context,BAD_CAST "xsl",BAD_CAST "http://www.w3.org/1999/XSL/Transform");
    nodeset=NULL;
    _result=NULL;
    resultIndex=0;
    unlink=false;
    //#]
}

QueryXml::QueryXml(xmlDocPtr root) {
    log = NULL;
    //#[ operation QueryXml(xmlDocPtr)
    this->doc=doc;
    contextNode=xmlDocGetRootElement(root);
    context = xmlXPathNewContext(root);
    context->namespaces = xmlGetNsList(doc,xmlDocGetRootElement(root));
    context->nsNr = 0;
    if (context->namespaces != NULL) {
        while (context->namespaces[context->nsNr] != NULL)
        //fprintf(stderr,"QueryXml: namespaces: %s\n",(char*)(context->namespaces[context->nsNr]->prefix));
        context->nsNr++;
    }
    /*xmlNsPtr * _nslist = xmlGetNsList(doc,xmlDocGetRootElement(root));
    int i=0;
    while(_nslist+i) {
    	fprintf(stderr,"QueryXml: namespaces: %s\n",(char*)((*(_nslist+i))->prefix));
    	i++;
    }
    xmlFreeNsList(*_nslist); */
    xmlXPathRegisterNs(context,BAD_CAST "xsl",BAD_CAST "http://www.w3.org/1999/XSL/Transform");
    nodeset=NULL;
    _result=NULL;
    resultIndex=0;
    unlink=false;
    
    //#]
}

QueryXml::QueryXml(xmlDocPtr doc, xmlNodePtr node) {
    log = NULL;
    //#[ operation QueryXml(xmlDocPtr,xmlNodePtr)
    //contextNode=xmlDocGetRootElement(root);
    this->doc=doc;
    context = xmlXPathNewContext(doc);
    context->node=node;
    //context->namespaces = xmlGetNsList(doc,node);
    
    context->namespaces = xmlGetNsList(doc,node);
    context->nsNr = 0;
    if (context->namespaces != NULL) {
        while (context->namespaces[context->nsNr] != NULL)
        //fprintf(stderr,"QueryXml: namespaces: %s\n",(char*)(context->namespaces[context->nsNr]->prefix));
        context->nsNr++;
    }
    
    if(log) log->getOfs()<<"QueryXml: namespaces: "<<context->namespaces<<endl<<flush;
    xmlXPathRegisterNs(context,BAD_CAST "xsl",BAD_CAST "http://www.w3.org/1999/XSL/Transform");
    nodeset=NULL;
    _result=NULL;
    resultIndex=0;
    unlink=false;
    
    //#]
}

QueryXml::QueryXml(const QueryXml& qx, xmlNodePtr node) {
    log = NULL;
    //#[ operation QueryXml(QueryXml,xmlNodePtr)
    //parentQuery=qx
    this->doc=qx.getDoc();
    context = xmlXPathNewContext(qx.getDoc());
    context->node=node;
    //context->namespaces = xmlGetNsList(qx.getDoc(),xmlDocGetRootElement(qx.getDoc()));
    if(log) log->getOfs()<<"QueryXml: namespaces: "<<context->namespaces<<endl<<flush;
    xmlXPathRegisterNs(context,BAD_CAST "xsl",BAD_CAST "http://www.w3.org/1999/XSL/Transform");
    nodeset=NULL;
    _result=NULL;
    resultIndex=0;
    unlink=false;
    
    //#]
}

QueryXml::QueryXml() {
    log = NULL;
}

QueryXml::~QueryXml() {
    //#[ operation ~QueryXml()
    //if(_result) {xmlXPathFreeNodeSetList(_result);_result=NULL;}
    if(_result) {xmlXPathFreeObject(_result);_result=NULL;}
    if(context) {
            if (context->namespaces != NULL) {
                xmlFree( context->namespaces );
            }
    	xmlXPathFreeContext(context);
    	context=NULL;
    }
    this->doc=NULL;
    //#]
    cleanUpRelations();
}

void QueryXml::dumpStep(xmlXPathCompExpr2 * comp, xmlXPathStepOp2 * op, int i) {
    //#[ operation dumpStep(xmlXPathCompExpr2 *,xmlXPathStepOp2 *,int)
    if(log) {
    
    log->getOfs()<<"   "<<"["<<i<<"]"<<endl<<flush;
    }
    
            if(log && i>=0) {
            	//log->getOfs()<<"QueryXml:"<<endl<<flush;
            	//log->getOfs()<<"      "<<pctxt->valueNr<<endl<<flush;
            	
            	//log->getOfs()<<"      "<<<<endl<<flush;
            	//xmlXPathCompExpr2 *test=(xmlXPathCompExpr2*)(pctxt->comp);
            	if(comp->expr) log->getOfs()<<"      "<<"Expr:"<</*(char*)(test->expr)<<*/endl<<flush;
            	log->getOfs()<<"      "<<"Steps:"<<comp->nbStep<<endl<<flush;
            	log->getOfs()<<"      "<<"Steps:last:"<<comp->last<<endl<<flush;
            	//int i;
            		log->getOfs()<<endl<<"      "<<"Steps:"<<comp->steps<<endl<<flush;
            			log->getOfs()<<"      "<<"Steps:op:"<<op->op<<" "<<flush;
            			switch(op->op){
            case XPATH_OP_END:
    	    log->getOfs()<<"END"<<flush; break;
            case XPATH_OP_AND:
    	    log->getOfs()<<"AND"<<flush; break;
            case XPATH_OP_OR:
    	    log->getOfs()<<"OR"<<flush; break;
            case XPATH_OP_EQUAL:
    	     if (op->value)
    		 log->getOfs()<<"EQUAL ="<<flush;
    	     else
    		 log->getOfs()<<"EQUAL !="<<flush;
    	     break;
            case XPATH_OP_CMP:
    	     if (op->value)
    		 log->getOfs()<<"CMP <"<<flush;
    	     else
    		 log->getOfs()<<"CMP >"<<flush;
    	     if (!op->value2)
    		 log->getOfs()<<"="<<flush;
    	     break;
            case XPATH_OP_PLUS:
    	     if (op->value == 0)
    		 log->getOfs()<<"PLUS -"<<flush;
    	     else if (op->value == 1)
    		 log->getOfs()<<"PLUS +"<<flush;
    	     else if (op->value == 2)
    		 log->getOfs()<<"PLUS unary -"<<flush;
    	     else if (op->value == 3)
    		 log->getOfs()<<"PLUS unary - -"<<flush;
    	     break;
            case XPATH_OP_MULT:
    	     if (op->value == 0)
    		 log->getOfs()<<"MULT *"<<flush;
    	     else if (op->value == 1)
    		 log->getOfs()<<"MULT div"<<flush;
    	     else
    		 log->getOfs()<<"MULT mod"<<flush;
    	     break;
            case XPATH_OP_UNION:
    	     log->getOfs()<<"UNION"<<flush; break;
            case XPATH_OP_ROOT:
    	     log->getOfs()<<"ROOT"<<flush; break;
            case XPATH_OP_NODE:
    	     log->getOfs()<<"NODE"<<flush; break;
            case XPATH_OP_RESET:
    	     log->getOfs()<<"RESET"<<flush; break;
            case XPATH_OP_SORT:
    	     log->getOfs()<<"SORT"<<flush; break;
            case XPATH_OP_COLLECT: {
    	    xmlXPathAxisVal2 axis = (xmlXPathAxisVal2)op->value;
    	    xmlXPathTestVal2 test = (xmlXPathTestVal2)op->value2;
    	    xmlXPathTypeVal2 type = (xmlXPathTypeVal2)op->value3;
    	    const xmlChar *prefix = (xmlChar*)(op->value4);
    	    const xmlChar *name = (xmlChar*)(op->value5);
            
    	    log->getOfs()<<"COLLECT "<<flush;
    	    switch (axis) {
    		case AXIS_ANCESTOR:
    		    log->getOfs()<<" 'ancestors' "<<flush; break;
    		case AXIS_ANCESTOR_OR_SELF:
    		    log->getOfs()<<" 'ancestors-or-self' "<<flush; break;
    		case AXIS_ATTRIBUTE:
    		    log->getOfs()<<" 'attributes' "<<flush; break;
    		case AXIS_CHILD:
    		    log->getOfs()<<" 'child' "<<flush; break;
    		case AXIS_DESCENDANT:
    		    log->getOfs()<<" 'descendant' "<<flush; break;
    		case AXIS_DESCENDANT_OR_SELF:
    		    log->getOfs()<<" 'descendant-or-self' "<<flush; break;
    		case AXIS_FOLLOWING:
    		    log->getOfs()<<" 'following' "<<flush; break;
    		case AXIS_FOLLOWING_SIBLING:
    		    log->getOfs()<<" 'following-siblings' "<<flush; break;
    		case AXIS_NAMESPACE:
    		    log->getOfs()<<" 'namespace' "<<flush; break;
    		case AXIS_PARENT:
    		    log->getOfs()<<" 'parent' "<<flush; break;
    		case AXIS_PRECEDING:
    		    log->getOfs()<<" 'preceding' "<<flush; break;
    		case AXIS_PRECEDING_SIBLING:
    		    log->getOfs()<<" 'preceding-sibling' "<<flush; break;
    		case AXIS_SELF:
    		    log->getOfs()<<" 'self' "<<flush; break;
    	    }
    	    switch (test) {
                    case NODE_TEST_NONE:
    		    log->getOfs()<<"'none' "<<flush; break;
                    case NODE_TEST_TYPE:
    		    log->getOfs()<<"'type' "<<flush; break;
                    case NODE_TEST_PI:
    		    log->getOfs()<<"'PI' "<<flush; break;
                    case NODE_TEST_ALL:
    		    log->getOfs()<<"'all' "<<flush; break;
                    case NODE_TEST_NS:
    		    log->getOfs()<<"'namespace' "<<flush; break;
                    case NODE_TEST_NAME:
    		    log->getOfs()<<"'name' "<<flush; break;
    	    }
    	    switch (type) {
                    case NODE_TYPE_NODE:
    		    log->getOfs()<<"'node' "<<flush; break;
                    case NODE_TYPE_COMMENT:
    		    log->getOfs()<<"'comment' "<<flush; break;
                    case NODE_TYPE_TEXT:
    		    log->getOfs()<<"'text' "<<flush; break;
                    case NODE_TYPE_PI:
    		    log->getOfs()<<"'PI' "<<flush; break;
    	    }
    	    
    	    if(test==NODE_TEST_NAME && type==NODE_TYPE_NODE && axis==AXIS_CHILD && collectNodes) {
    	    	//string str("");
    	    	//str=(char*)name;
    	    	log->getOfs()<<"collectNodes:"<<(char*)name<<endl<<flush;
    	    	xpathNodes.push_back((char*)name);
    	    }
    	    if (prefix != NULL)
    		log->getOfs()<<prefix<<flush;
    	    if (name != NULL)
    		log->getOfs()<< (const char *) name<<flush;
    	    break;
    
            }
    	case XPATH_OP_VALUE: {
    	    xmlXPathObjectPtr object = (xmlXPathObjectPtr) op->value4;
    
    	    log->getOfs()<<"ELEM "<<flush;
    	    log->getOfs()<< object->type <<flush;
    	    log->getOfs()<< object->floatval<<endl<<flush;
    	    //xmlXPathDebugDumpObject(output, object, 0);
    	    goto finish;
    	}
    	case XPATH_OP_VARIABLE: {
    	    const xmlChar *prefix = (xmlChar*)(op->value5);
    	    const xmlChar *name = (xmlChar*)(op->value4);
    
    	    if (prefix != NULL)
    		log->getOfs()<<"VARIABLE %s:%s"<<flush;
    	    else
    		log->getOfs()<<"VARIABLE %s"<<flush;
    	    break;
    	}
    	case XPATH_OP_FUNCTION: {
    	    int nbargs = op->value;
    	    const xmlChar *prefix = (xmlChar*)(op->value5);
    	    const xmlChar *name = (xmlChar*)(op->value4);
    
    	    if (prefix != NULL)
    		log->getOfs()<<"FUNCTION %s:%s(%d args)"<<flush;
    	    else
    		log->getOfs()<<"FUNCTION %s(%d args)"<<flush;
    	    break;
    	}
            case XPATH_OP_ARG: log->getOfs()<<"ARG"<<flush; break;
            case XPATH_OP_PREDICATE: log->getOfs()<<"PREDICATE"<<flush; break;
            case XPATH_OP_FILTER: log->getOfs()<<"FILTER"<<flush; break;
    
            				default:
            					log->getOfs()<<"UNKNOWN"<<endl<<flush;
            			}
            			log->getOfs()<<endl<<flush;        			
            			log->getOfs()<<"      "<<"Steps:ch1:"<<op->ch1<<endl<<flush;
            			log->getOfs()<<"      "<<"Steps:ch2:"<<op->ch2<<endl<<flush;
            			log->getOfs()<<"      "<<"Steps:v:"<<op->value<<endl<<flush;
            			log->getOfs()<<"      "<<"Steps:v2:"<<op->value2<<endl<<flush;
            			log->getOfs()<<"      "<<"Steps:v3:"<<op->value3<<endl<<flush;
            			if(op->value4) log->getOfs()<<"      "<<"Steps:v4:"<<(char*)(op->value4)<<endl<<flush;
            			if(op->value5) log->getOfs()<<"      "<<"Steps:v5:"<<(char*)(op->value5)<<endl<<flush;
            			log->getOfs()<<"      "<<"Steps:rt:"<<op->rewriteType<<endl<<flush;
    finish:
    	if(op->ch1<0 && op->ch2<0) collectNodes=false;
        if (op->ch1 >= 0)
            dumpStep(comp, &comp->steps[op->ch1],op->ch1);
        if (op->ch2 >= 0)
            dumpStep(comp, &comp->steps[op->ch2],op->ch2);
    }
    //#]
}

bool QueryXml::exist() {
    //#[ operation exist()
    if(nodeset){
    return true;
    } else return false;
    //#]
}

void QueryXml::result(string & out) {
    //#[ operation result(string &)
    out="";
    if(nodeset){
    	xmlChar * _val=xmlNodeGetContent(nodeset->nodeTab[resultIndex]);
    	out=(char*)_val;
    	xmlFree(_val);
    /*	if(unlink){
    		xmlUnlinkNode(nodeset->nodeTab[resultIndex]);
    		nodeset->nodeTab[resultIndex]=NULL;
    	}*/
    	resultIndex++;
    	if(resultIndex>nodeset->nodeNr) {
    		resultIndex=0;
    		out="";
    	}
    } else {
    	out="";
    }
    
    //#]
}

void QueryXml::result(bool& out) {
    //#[ operation result(bool)
    out=true;
    //#]
}

void QueryXml::result(xmlNodePtr & out) {
    //#[ operation result(xmlNodePtr &)
    if(nodeset){
    	if(log) log->getOfs()<<"QueryXml: index "<<resultIndex<<endl<<flush;
    	if(log) log->getOfs()<<"QueryXml: Nr "<<nodeset->nodeNr<<endl<<flush;
    	out=nodeset->nodeTab[resultIndex];
    	if(unlink){
    		xmlUnlinkNode(nodeset->nodeTab[resultIndex]);
    		nodeset->nodeTab[resultIndex]=NULL;
    	}
    	resultIndex++;
    	if(resultIndex>nodeset->nodeNr) {
    		resultIndex=0;
    		out=NULL;
    	}
    } else {
    	out=NULL;
    }
    //#]
}

void QueryXml::run(const char * xpath) {
    //#[ operation run(char *)
    resultIndex=0;
    
    	if (context == NULL) {
    		return;
    	}
    
    	//if(_result) {xmlXPathFreeNodeSetList(_result);_result=NULL;}
    	if(_result) {xmlXPathFreeObject(_result);_result=NULL;}
    	//_result = xmlXPathEvalExpression(BAD_CAST xpath, context);
        //**********************************************************
        
     if(1){   
        xmlXPathParserContextPtr pctxt;
        xmlXPathObjectPtr res, tmp;
        int stack = 0;
    
        //CHECK_CTXT(ctxt)
    
        xmlXPathInit();
    
        pctxt = xmlXPathNewParserContext(BAD_CAST xpath, context);
        if (pctxt == NULL)
            return;
        xmlXPathEvalExpr(pctxt);
    
        if ((*pctxt->cur != 0) || (pctxt->error != XPATH_EXPRESSION_OK)) {
            xmlXPatherror(pctxt, __FILE__, __LINE__, XPATH_EXPR_ERROR);
            if(log) log->getOfs()<<"QueryXml: string result: xpath error"<<endl<<flush;
            res = NULL;
        } else {
            res = valuePop(pctxt);
            //debug ParserContext
            xmlXPathCompExpr2 *test=(xmlXPathCompExpr2*)(pctxt->comp);
            collectNodes=true; 
            dumpStep(test,&test->steps[test->last],test->last);
    
        }
        do {
            tmp = valuePop(pctxt);
            if (tmp != NULL) {
            	if(log) log->getOfs()<<"QueryXml: pop: "<<tmp<<endl<<flush;
                //xmlXPathReleaseObject(ctxt, tmp);
                xmlXPathFreeObject(tmp);
                stack++;
            }
        } while (tmp != NULL);
        if ((stack != 0) && (res != NULL)) {
            /*xmlGenericError(xmlGenericErrorContext,
                    "xmlXPathEvalExpression: %d object left on the stack\n",
                    stack); */
            if(log) log->getOfs()<<"QueryXml: stack is not empty"<<endl<<flush;
        }
        xmlXPathFreeParserContext(pctxt);
        
        _result=res;
      }
      
    	if (_result == NULL) {
    		//xmlXPathFreeContext(context);
    		//context=NULL;
    		if(log) log->getOfs()<<"QueryXml: no result"<<endl<<flush;
    		nodeset=NULL;
    		return;
    	}
    	if(log) log->getOfs()<<"QueryXml: result type:"<<_result->type<<endl<<flush;
    	if(_result->type==XPATH_STRING) {
    		if(log) log->getOfs()<<"QueryXml: string result:"<<(char*)(_result->stringval)<<endl<<flush;
    	}
    	if(xmlXPathNodeSetIsEmpty(_result->nodesetval)){
    		//xmlXPathFreeNodeSetList(_result);
    		if(log) log->getOfs()<<"QueryXml: empty:"<<endl<<flush;
    		xmlXPathFreeObject(_result);
    		_result=NULL;
    		nodeset=NULL;
    	} else {
    		nodeset=_result->nodesetval;
    	}
    
    
    //#]
}

void QueryXml::set(string & val) {
    //#[ operation set(string &)
    if(nodeset) {
    	xmlNodeSetContent(nodeset->nodeTab[0],BAD_CAST (val.c_str()));
    }
    //#]
}

xmlXPathObjectPtr QueryXml::get_result() const {
    return _result;
}

void QueryXml::set_result(xmlXPathObjectPtr p__result) {
    _result = p__result;
}

xmlXPathContextPtr QueryXml::getContext() const {
    return context;
}

void QueryXml::setContext(xmlXPathContextPtr p_context) {
    context = p_context;
}

xmlNodePtr QueryXml::getContextNode() const {
    return contextNode;
}

void QueryXml::setContextNode(xmlNodePtr p_contextNode) {
    contextNode = p_contextNode;
}

xmlDocPtr QueryXml::getDoc() const {
    return doc;
}

void QueryXml::setDoc(xmlDocPtr p_doc) {
    doc = p_doc;
}

xmlNodeSetPtr QueryXml::getNodeset() const {
    return nodeset;
}

void QueryXml::setNodeset(xmlNodeSetPtr p_nodeset) {
    nodeset = p_nodeset;
}

int QueryXml::getResultIndex() const {
    return resultIndex;
}

void QueryXml::setResultIndex(int p_resultIndex) {
    resultIndex = p_resultIndex;
}

bool QueryXml::getUnlink() const {
    return unlink;
}

void QueryXml::setUnlink(bool p_unlink) {
    unlink = p_unlink;
}

list<string> QueryXml::getXpathNodes() const {
    return xpathNodes;
}

void QueryXml::setXpathNodes(list<string> p_xpathNodes) {
    xpathNodes = p_xpathNodes;
}

FileLog* QueryXml::getLog() const {
    return log;
}

void QueryXml::setLog(FileLog* p_FileLog) {
    log = p_FileLog;
}

void QueryXml::cleanUpRelations() {
    if(log != NULL)
        {
            log = NULL;
        }
}

bool QueryXml::getCollectNodes() const {
    return collectNodes;
}

void QueryXml::setCollectNodes(bool p_collectNodes) {
    collectNodes = p_collectNodes;
}

/*********************************************************************
	File Path	: cmsv2lxImage/linux_static/Default/QueryXml.cpp
*********************************************************************/
