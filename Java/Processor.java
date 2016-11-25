package com.logicus.client;

import java.util.ArrayList;
import java.util.List;

/*
import name.pehl.totoe.xml.client.Document;
import name.pehl.totoe.xml.client.Node;
import name.pehl.totoe.xml.client.XmlParser;
*/

import com.google.gwt.user.client.ui.HasValue;
import com.google.gwt.xml.client.NodeList;
import com.google.gwt.event.dom.client.ChangeEvent;
import com.google.gwt.event.dom.client.ChangeHandler;
import com.google.gwt.event.dom.client.HasChangeHandlers;
import com.google.gwt.user.client.ui.Widget;
import com.google.gwt.user.client.Window;
import com.google.gwt.xml.client.Document;
import com.google.gwt.xml.client.Text;
import com.google.gwt.xml.client.XMLParser;

public class Processor {
	
	static ArrayList<Widget> _fieldList = new ArrayList<Widget>();
	
	//List<Node> products = null;
	
	Document xmlTemplate = null;
	
	public void addField(Widget w) {
/*		((HasChangeHandlers) w).addChangeHandler(new ChangeHandler() {
			public void onChange(ChangeEvent ev) {
				
			}
		});*/
		_fieldList.add(w);
	}
	
	public void setXml(String xml) {
		System.out.println(xml);
		xmlTemplate = XMLParser.parse(xml);
		System.out.println(xmlTemplate);
		//products = xmlTemplate.selectNodes("/data/user");		
	}
	
	public void setData(String xml) {
/*		Document xmlData = new XmlParser().parse(xml);;
		for(Widget w : _fieldList) {
			List<Node> dataSetNodes = xmlData.selectNodes(w.getElement().getAttribute("name"));
			for(Node n : dataSetNodes) {
				((HasValue<String>) w).setValue(n.selectValue("text()"));
			}
		}
*/
		Document xmlData = XMLParser.parse(xml);
		for(Widget w : _fieldList) {
			NodeList dataSetNodes = xmlData.getElementsByTagName(w.getElement().getAttribute("name"));
			//for(int i=0;i<1;i++) {
			if(dataSetNodes.getLength()>0) {
				if(dataSetNodes.item(0).hasChildNodes()) {
					((HasValue<String>) w).setValue("Test:"+dataSetNodes.item(0).getFirstChild().getNodeValue());
				}
			}
		}
	}
	
	public String getStringData() {
/*		for(Widget w : _fieldList) {
			List<Node> dataSetNodes = xmlTemplate.selectNodes(w.getElement().getAttribute("name"));
			for(Node n : dataSetNodes) {
				((HasValue<String>) w).setValue(n.selectValue("text()"));
			}
		}
*/
		System.out.println(_fieldList.size());
		for(Widget w : _fieldList) {
			System.out.println(w.getElement().getAttribute("name"));
			System.out.println(xmlTemplate);
			NodeList dataSetNodes = xmlTemplate.getElementsByTagName(w.getElement().getAttribute("name"));
			//for(int i=0;i<1;i++) {
			if(dataSetNodes.getLength()>0) {
				if(dataSetNodes.item(0).hasChildNodes()) {
					dataSetNodes.item(0).getFirstChild().setNodeValue(((HasValue<String>) w).getValue());
				} else {
					dataSetNodes.item(0).appendChild(xmlTemplate.createTextNode(((HasValue<String>) w).getValue()));
				}
			}
		}
		return xmlTemplate.toString();
	}
}
