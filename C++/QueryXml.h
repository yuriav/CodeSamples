/*********************************************************************
	Rhapsody	: 7.6.1 
	Login		: Administrator
	Component	: cmsv2lxImage 
	Configuration 	: linux_static
	Model Element	: QueryXml
//!	Generated Date	: Wed, 25, Jun 2014  
	File Path	: cmsv2lxImage/linux_static/Default/QueryXml.h
*********************************************************************/

#ifndef Default_QueryXml_H
#define Default_QueryXml_H

//## auto_generated
#include <oxf/oxf.h>
//## auto_generated
#include "Default/Default.h"
//## link log
class FileLog;

//## package Default

//## class QueryXml
class QueryXml {
public :

    //#[ type xmlXPathOp2
    typedef enum {
        XPATH_OP_END=0,
        XPATH_OP_AND,
        XPATH_OP_OR,
        XPATH_OP_EQUAL,
        XPATH_OP_CMP,
        XPATH_OP_PLUS,
        XPATH_OP_MULT,
        XPATH_OP_UNION,
        XPATH_OP_ROOT,
        XPATH_OP_NODE,
        XPATH_OP_RESET, /* 10 */
        XPATH_OP_COLLECT,
        XPATH_OP_VALUE, /* 12 */
        XPATH_OP_VARIABLE,
        XPATH_OP_FUNCTION,
        XPATH_OP_ARG,
        XPATH_OP_PREDICATE,
        XPATH_OP_FILTER, /* 17 */
        XPATH_OP_SORT /* 18 */
    /*
    #ifdef LIBXML_XPTR_ENABLED
        ,XPATH_OP_RANGETO
    #endif*/
    } xmlXPathOp2;
    
    //#]
    
    //#[ type xmlXPathStepOp2
    struct xmlXPathStepOp2 {
        xmlXPathOp2 op;              /* The identifier of the operation */
        int ch1;                    /* First child */
        int ch2;                    /* Second child */
        int value;
        int value2;
        int value3;
        void *value4;
        void *value5;
        void *cache;
        void *cacheURI;
        int rewriteType;
    };
    
    //#]
    
    //#[ type xmlXPathCompExpr2
    struct _xmlXPathCompExpr2 {
        int nbStep;                 /* Number of steps in this expression */
        int maxStep;                /* Maximum number of steps allocated */
        xmlXPathStepOp2 *steps;      /* ops for computation of this expression */
        int last;                   /* index of last step in expression */
        xmlChar *expr;              /* the expression being computed */
        xmlDictPtr dict;            /* the dictionnary to use if any */
    /*
    #ifdef DEBUG_EVAL_COUNTS
        int nb;
        xmlChar *string;
    #endif
    #ifdef XPATH_STREAMING
        xmlPatternPtr stream;
    #endif*/
    };
    typedef struct _xmlXPathCompExpr2 xmlXPathCompExpr2;
    //#]
    
    //#[ type xmlXPathAxisVal2
    typedef enum {
        AXIS_ANCESTOR = 1,
        AXIS_ANCESTOR_OR_SELF,
        AXIS_ATTRIBUTE,
        AXIS_CHILD,
        AXIS_DESCENDANT,
        AXIS_DESCENDANT_OR_SELF,
        AXIS_FOLLOWING,
        AXIS_FOLLOWING_SIBLING,
        AXIS_NAMESPACE,
        AXIS_PARENT,
        AXIS_PRECEDING,
        AXIS_PRECEDING_SIBLING,
        AXIS_SELF
    } xmlXPathAxisVal2;
    
    //#]
    
    //#[ type xmlXPathTestVal2
    typedef enum {
        NODE_TEST_NONE = 0,
        NODE_TEST_TYPE = 1,
        NODE_TEST_PI = 2,
        NODE_TEST_ALL = 3,
        NODE_TEST_NS = 4,
        NODE_TEST_NAME = 5
    } xmlXPathTestVal2;
    //#]
    
    //#[ type xmlXPathTypeVal2
    typedef enum {
        NODE_TYPE_NODE = 0,
        NODE_TYPE_COMMENT = XML_COMMENT_NODE,
        NODE_TYPE_TEXT = XML_TEXT_NODE,
        NODE_TYPE_PI = XML_PI_NODE
    } xmlXPathTypeVal2;
    
    //#]
    
    ////    Constructors and destructors    ////
    
    //## operation QueryXml(xmlNodePtr)
    QueryXml(xmlNodePtr root);
    
    //## operation QueryXml(xmlDocPtr)
    QueryXml(xmlDocPtr root);
    
    //## operation QueryXml(xmlDocPtr,xmlNodePtr)
    QueryXml(xmlDocPtr doc, xmlNodePtr node);
    
    //## operation QueryXml(QueryXml,xmlNodePtr)
    QueryXml(const QueryXml& qx, xmlNodePtr node);
    
    //## auto_generated
    QueryXml();
    
    //## operation ~QueryXml()
    ~QueryXml();
    
    ////    Operations    ////
    
    //## operation dumpStep(xmlXPathCompExpr2 *,xmlXPathStepOp2 *,int)
    void dumpStep(xmlXPathCompExpr2 * comp, xmlXPathStepOp2 * op, int i);
    
    //## operation exist()
    bool exist();
    
    //## operation result(string &)
    void result(string & out);
    
    //## operation result(bool)
    void result(bool& out);
    
    //## operation result(xmlNodePtr &)
    void result(xmlNodePtr & out);
    
    //## operation run(char *)
    void run(const char * xpath);
    
    //## operation set(string &)
    void set(string & val);
    
    ////    Additional operations    ////
    
    //## auto_generated
    xmlXPathObjectPtr get_result() const;
    
    //## auto_generated
    void set_result(xmlXPathObjectPtr p__result);
    
    //## auto_generated
    xmlXPathContextPtr getContext() const;
    
    //## auto_generated
    void setContext(xmlXPathContextPtr p_context);
    
    //## auto_generated
    xmlNodePtr getContextNode() const;
    
    //## auto_generated
    void setContextNode(xmlNodePtr p_contextNode);
    
    //## auto_generated
    xmlDocPtr getDoc() const;
    
    //## auto_generated
    void setDoc(xmlDocPtr p_doc);
    
    //## auto_generated
    xmlNodeSetPtr getNodeset() const;
    
    //## auto_generated
    void setNodeset(xmlNodeSetPtr p_nodeset);
    
    //## auto_generated
    int getResultIndex() const;
    
    //## auto_generated
    void setResultIndex(int p_resultIndex);
    
    //## auto_generated
    bool getUnlink() const;
    
    //## auto_generated
    void setUnlink(bool p_unlink);
    
    //## auto_generated
    list<string> getXpathNodes() const;
    
    //## auto_generated
    void setXpathNodes(list<string> p_xpathNodes);
    
    //## auto_generated
    FileLog* getLog() const;
    
    //## auto_generated
    void setLog(FileLog* p_FileLog);

protected :

    //## auto_generated
    void cleanUpRelations();

private :

    //## auto_generated
    bool getCollectNodes() const;
    
    //## auto_generated
    void setCollectNodes(bool p_collectNodes);
    
    ////    Attributes    ////

protected :

    xmlXPathObjectPtr _result;		//## attribute _result
    
    bool collectNodes;		//## attribute collectNodes
    
    xmlXPathContextPtr context;		//## attribute context
    
    xmlNodePtr contextNode;		//## attribute contextNode
    
    xmlDocPtr doc;		//## attribute doc
    
    xmlNodeSetPtr nodeset;		//## attribute nodeset
    
    int resultIndex;		//## attribute resultIndex
    
    bool unlink;		//## attribute unlink
    
    list<string> xpathNodes;		//## attribute xpathNodes
    
    ////    Relations and components    ////
    
    FileLog* log;		//## link log
};

#endif
/*********************************************************************
	File Path	: cmsv2lxImage/linux_static/Default/QueryXml.h
*********************************************************************/
