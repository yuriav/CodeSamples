package reports;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.sql.Date;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Map;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.transform.Source;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import javax.xml.transform.stream.StreamSource;

import org.apache.commons.io.FileUtils;
import org.apache.poi.xssf.usermodel.XSSFCell;
import org.apache.poi.xssf.usermodel.XSSFRow;
import org.apache.poi.xssf.usermodel.XSSFSheet;
import org.apache.poi.xssf.usermodel.XSSFWorkbook;
import org.basex.core.Context;
import org.basex.core.cmd.Add;
import org.basex.core.cmd.Close;
import org.basex.core.cmd.CreateDB;
import org.basex.core.cmd.Delete;
import org.basex.core.cmd.Open;
import org.basex.core.cmd.XQuery;
import org.basex.query.QueryException;
import org.basex.query.QueryProcessor;
import org.basex.query.value.Value;
import org.stringtemplate.v4.ST;
import org.stringtemplate.v4.STGroup;
import org.stringtemplate.v4.STGroupFile;
import org.w3c.dom.Document;
import org.xml.sax.InputSource;

public class CollectData {
	
	private java.sql.Connection  con = null;
	private String userdir;
	private STGroup groupOebs;
	private ST sqltemplate1;
	private ST xmltemplate1;

	private Context context;
	
	private HyperionData hypdata = new HyperionData();
	
	private String sqlStatement12Init = "begin " +
			"APPS.FND_GLOBAL.APPS_INITIALIZE(1171,50550 ,510);" +
			"mo_global.init (fnd_global.application_short_name);" +
			"mo_global.set_policy_context ('S', fnd_global.org_id);" +
			"end;";

	public ByteArrayOutputStream os = null;
	
	public String username="";
	public Date date=null;
	public Integer days=0;
	public String currency="";
	Double[] currencyValues={1.0,0.0,0.0};
	Double conversionRate=1.0;
	
	class ArtParents {
		String art;
		String desc;
		Integer flag=0;
		public String getArt() {
			return art;
		}
		public String getDesc() {
			return desc;
		}
		public int getFlag() {
			return flag;
		}
	}
	private ArrayList<ArtParents> arts = new ArrayList<ArtParents>();
	public ArrayList<String> markedArticles = new ArrayList<String>();
	
	class Invoice {
		Integer invoiceid;
		String number;
		Double amount;
		Double paid; //???
		String currency;
		String art;
		String vendor;
		String description;
		String date;
		String dateVal;
		String category;
		public String getNumber() {
			return number;
		}
		public Integer getInvoiceid() {
			return invoiceid;
		}
		public String getArt() {
			return art;
		}
		public String getCurrency() {
			return currency;
		}
		public String getDescription() {
			return description;
		}
		public String getVendor() {
			return vendor;
		}
		public Double getAmount() {
			return amount;
		}
		public Double getPaid() {
			return paid;
		}
		public String getDate() {
			return date;
		}
		public String getDateVal() {
			return dateVal;
		}
		public String getCategory() {
			return category;
		}
	}

	private ArrayList<Invoice> invoiceList = new ArrayList<Invoice>();
	
	public void init(Context _context){
		// TODO Auto-generated method stub
		userdir = System.getProperty("user.dir");
		groupOebs = new STGroupFile(userdir+"/templates/baseXPayments1/oebs.stg");
		groupOebs.delimiterStartChar='#';
		groupOebs.delimiterStopChar='#';
		
        try {
            Class.forName("oracle.jdbc.driver.OracleDriver");
            con = java.sql.DriverManager.getConnection(
                    "jdbc:oracle:thin:@upgr12.ebs.ntv.ru:1533/PROD12",
                    "apps",
                    "******");
            PreparedStatement initR12 = con.prepareStatement(sqlStatement12Init);
            ResultSet rsInit = initR12.executeQuery();
            rsInit.close();
        } catch(Exception e){
        	try {
	        	if(!con.isClosed()) {
	        		con.close();
	        	}
        	} catch (Exception e2) {
        		System.out.println("Error Close : " + e2.getMessage());
        	}
            e.printStackTrace();
            System.out.println("Error Trace in Connection : " + e.getMessage());
        }
        
        context = _context;
        
	}

	ResultSet query(ST _st) throws SQLException {
		String sqlStatement = _st.render();
		//System.out.println(sqlStatement);
		PreparedStatement pst  = con.prepareStatement(sqlStatement,ResultSet.TYPE_SCROLL_INSENSITIVE,ResultSet.CONCUR_READ_ONLY);
        ResultSet res = pst.executeQuery();
        return res;
	}
	
	void xquery(String tname) throws QueryException {
		xquery(groupOebs.getInstanceOf(tname));
	}

	void xquery(String tname,Object val1) throws QueryException {
		xquery(groupOebs.getInstanceOf(tname),val1);
	}
	
	String xquery(ST _st) throws QueryException {
		QueryProcessor proc = new QueryProcessor(_st.render(), context);
		String _val = proc.value().toString();
		proc.close();
		return _val;
	}

	void xquery(ST _st,Object val1) throws QueryException {
		_st.add("p1", val1);
		QueryProcessor proc = new QueryProcessor(_st.render(), context);
		proc.value();
		proc.close();
		_st.remove("p1");
	}

	
	public void loadArticles() {
        XSSFWorkbook wbs=null;

        String userdir = System.getProperty("user.dir");
		File dt = new File(userdir+"/data/baseXPayments1/articles.xlsx");
		//File outfile = new File(userdir+"/data/Книга2Анна_v2_h11_fill.xlsx");
		
		try {
		        wbs = new XSSFWorkbook(new ByteArrayInputStream(FileUtils.readFileToByteArray(dt)));
		} catch (Exception e) {
		                System.out.print("ERROR: ");
		                System.out.println( e.getMessage() );
		                System.out.println("\nStack Trace: ");
		                e.printStackTrace();
		                System.exit(1);
        }
		XSSFSheet s = wbs.getSheetAt(0);

        XSSFRow r = null;
        XSSFCell c = null;
        r = s.getRow(4);
        c = r.getCell(1);
        System.out.println("Cell Value: " +c.getStringCellValue());
        try {
        	XSSFCell art=null,flag=null,artReplace=null;
        	int i=4;
        	do {
	            r = s.getRow(i);
	            if(r==null) break;
	            art = r.getCell(1);
	            artReplace = r.getCell(4);
	            flag = r.getCell(3);
	            if(flag!=null) {
		            //System.out.println("Cell Value: " +flag.getNumericCellValue());
	            	if(artReplace !=null) {
	            		System.out.println("Replace: "+art.getStringCellValue());
	            		markedArticles.add(artReplace.getStringCellValue());
	            	} else {
	            		markedArticles.add(art.getStringCellValue());
	            	}
	            }
	            if(art!=null) {
		            //System.out.println("Cell Value: " +art.getStringCellValue());
	            } else break;
	            i++;
        	} while(art!=null);
        } catch(Exception e) {
        	e.printStackTrace();
        }
		
	}
	
	public void loadCFOS() {
		try {
			ST t = groupOebs.getInstanceOf("cfoList");
			ResultSet rs = query(t);
			String parentCfo = "";
			String parentFlag="";
			while(rs.next()){
				parentFlag = rs.getString("PARENT");
				if(parentFlag.contains("Да")) {
					parentCfo = rs.getString("FLEX_VALUE");
				}
			}
		} catch(Exception e) {
			e.printStackTrace();
		}
		
	}
	
	public void runTest1() {

		try {
			new Open("PayList_"+username).execute(context);
		{
			ST xout = groupOebs.getInstanceOf("xoutQuery");
			DateFormat formatXQDate = new SimpleDateFormat("yyyy-MM-dd'T'HH:mm:ss.SSS");
			xout.add("date1", formatXQDate.format(date));
			Calendar c = Calendar.getInstance(); 
			c.setTime(date); 
			c.add(Calendar.DATE, days);
			xout.add("date2", formatXQDate.format(c.getTime()));
			System.out.println(xout.render());
			QueryProcessor proc = new QueryProcessor(xout.render(), context);
			//System.out.println(proc.value().serialize().toString());
	        DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
	        Document dom=null;
	        try {
	        	DocumentBuilder db = dbf.newDocumentBuilder();
	        	dom = db.parse(new InputSource(new ByteArrayInputStream(proc.value().serialize().toString().getBytes("utf-8"))));
	        } catch (Exception e) {
	        	e.printStackTrace();
	        }

	        StreamResult r = null;
	        
	        try {
	        	TransformerFactory tf = TransformerFactory.newInstance("net.sf.saxon.TransformerFactoryImpl",null);
	        	//TransformerFactory tf = TransformerFactory.newInstance("org.apache.xalan.processor.TransformerFactoryImpl",null);
	        	//TransformerFactory tf = TransformerFactory.newInstance("javax.xml.transform.TransformerFactory",null);
	        	Source xslt = new StreamSource(userdir+"/templates/baseXPayments1/pay_list2.xsl");
	        	Transformer t = tf.newTransformer(xslt);
	        	DOMSource src = new DOMSource(dom);
	        	os = new ByteArrayOutputStream();
	        	r = new StreamResult(os);
	        	//t.setOutputProperty(OutputKeys.INDENT, "yes");
	        	//t.setOutputProperty(OutputKeys.METHOD, "xml");
	        	t.transform(src, r);
	        	//System.out.println(r.getOutputStream().toString());
	        } catch (Exception e) {
	        	e.printStackTrace();
	        }        

	        try {
	        	FileOutputStream fos = new FileOutputStream("out2.xml");
	        	fos.write(proc.value().serialize().toArray());
	        	//fos.write(os.toByteArray());
	        	fos.close();
	        } catch(Exception e) {
	        	e.printStackTrace();
	        }
	        
	        try {
	        	FileOutputStream fos = new FileOutputStream("out2.xls");
	        	//fos.write(proc.value().serialize().toArray());
	        	fos.write(os.toByteArray());
	        	fos.close();
	        } catch(Exception e) {
	        	e.printStackTrace();
	        }
	        
	        proc.close();
		}

		
		//System.out.println(new XQuery("//p_date").execute(context));

		new Delete("Requests").execute(context);
		new Close().execute(context);

		System.out.println("End.");

    } catch(Exception e) {
    	e.printStackTrace();
    }

	}
	
	public void run(){
				
        try {
			new CreateDB("PayList_"+username).execute(context);
			new Close().execute(context);
			new Open("PayList_"+username).execute(context);
/*			{
				QueryProcessor proc = new QueryProcessor("/requests", context);
				Value result = proc.value();
				
				if(result.serialize().toString()!="") {
					System.out.println("Database lock.");
					new Close().execute(context);
					return;
				};
			}
*/
//			new Delete("PayList1").execute(context);
//			new Delete("InvoiceList").execute(context);

			new Add("PayList1","<paylist/>").execute(context);
			new Add("InvoiceList","<invoices/>").execute(context);
			new Add("CostCenters","<cfos/>");
//			new Add("Requests","<requests/>").execute(context);
			
			DateFormat format = new SimpleDateFormat("dd.MM.yyyy");
			DateFormat formatXLS = new SimpleDateFormat("yyyy-MM-dd");
			DateFormat formatVal = new SimpleDateFormat("yyyyMMdd"); 
			
			ST xinit = groupOebs.getInstanceOf("xinit");
			xinit.add("date", "17.08.2016");
			xquery(xinit);
			
			ST currT = groupOebs.getInstanceOf("currency");			
			currT.add("date", "17.08.2016");
			ST xcurrT = groupOebs.getInstanceOf("xcurrency");
			System.out.println(currT.render());
			
			ResultSet curr = query(currT);
			while(curr.next()){
				String _curr=curr.getString("FROM_CURRENCY");
				xcurrT.add("name", _curr);
				Double _rate = curr.getDouble("CONVERSION_RATE");
				xcurrT.add("rate", _rate);
				xquery(xcurrT);
				if(_curr.contentEquals("EUR") && currency.contentEquals("EUR")) {
					conversionRate = _rate;
				}
				if(_curr.contentEquals("USD") && currency.contentEquals("USD")) {
					conversionRate = _rate;
				}
				xcurrT.remove("name");
				xcurrT.remove("rate");
			}
			
			ST articles = groupOebs.getInstanceOf("articlesList");
			ST parents = groupOebs.getInstanceOf("articleParents");
			ResultSet art = query(articles);
			
			/*
			while(art.next()){
				hypdata.arts.add(art.getString("DETAIL_ARTICLE"));
			}
			*/
			
			while(art.next()){
				System.out.print(art.getString("DETAIL_ARTICLE"));
				hypdata.arts.put(art.getString("DETAIL_ARTICLE"),new HData());
				xquery("xlvl2",art.getString("DETAIL_ARTICLE"));
				
				parents.add("article",art.getString("DETAIL_ARTICLE"));
				ResultSet artParents = query(parents);
				boolean getDescription = true;
				ST xParents = groupOebs.getInstanceOf("xparents");
				while(artParents.next()) {
					if(getDescription) {
						ArtParents ap = new ArtParents();
						ap.art = artParents.getString("FLEX_VALUE");
						ap.desc = artParents.getString("DESCRIPTION");
						if(markedArticles.contains(ap.art)) {
							ap.flag=1;
						}
						xParents.add("desc", ap);						
						getDescription = false;
					}
					ArtParents ap = new ArtParents();
					ap.art = artParents.getString("FLEX_VALUE");
					if(ap.art.contains("GPM2007CC011129")) ap.art = "GPM2007CC0111239";
					hypdata.arts.put(ap.art,new HData());
					ap.desc = artParents.getString("DESCRIPTION");
					if(markedArticles.contains(ap.art)) {
						ap.flag=1;
					}
					xParents.add("parents", ap);
					System.out.println(artParents.getString("FLEX_VALUE"));
				}
				
				parents.remove("article");
				System.out.println(xParents.render());
				xquery(xParents);


			}
			art.close();
			
			{
				ST invoices = groupOebs.getInstanceOf("invoices");
				ST xinvoice = groupOebs.getInstanceOf("addInvoiceToList");
				
				invoices.add("filter", "and INVOICE_TYPE_LOOKUP_CODE = 'PREPAYMENT'");
				ResultSet inv = query(invoices);
				while(inv.next()){
					Invoice i = new Invoice();
					i.number = inv.getString("INVOICE_NUM");
					//System.out.println(i.number);
					i.invoiceid = inv.getInt("INVOICE_ID");
					i.currency = inv.getString("INVOICE_CURRENCY_CODE");
					if(!(i.currency.contentEquals("RUB"))) {
						i.amount = inv.getDouble("INVOICE_AMOUNT") * inv.getDouble("EXCHANGE_RATE");
						i.paid = inv.getDouble("AMOUNT_PAID") * inv.getDouble("EXCHANGE_RATE");
					} else {
						i.amount = inv.getDouble("INVOICE_AMOUNT");
						i.paid = inv.getDouble("AMOUNT_PAID");					
					}
					i.amount = i.amount / conversionRate;
					i.paid = i.paid / conversionRate;
					//check1
					//check2
					xinvoice.add("invoice", i);
					try {
						xquery(xinvoice);
					} catch(Exception e) {
						e.printStackTrace();
						System.out.println("skip1 "+inv.getInt("INVOICE_ID")+" "+inv.getString("INVOICE_NUM"));
					}
					xinvoice.remove("invoice");

				}
				invoices.remove("filter");
				{
					QueryProcessor proc = new QueryProcessor("/invoices", context);
					System.out.println(proc.value().serialize().toString());
				}
			}
			
			ST invoices = groupOebs.getInstanceOf("invoices2");
			ST xinvoice = groupOebs.getInstanceOf("xinvoice");
			ST xinvoiceCheck = groupOebs.getInstanceOf("xinvoiceCheck");
			ResultSet inv = query(invoices);
			
			while(inv.next()){
				Invoice i = new Invoice();
				i.number = inv.getString("INVOICE_NUM");
				//System.out.println(i.number);
				i.invoiceid = inv.getInt("INVOICE_ID");
				i.vendor = inv.getString("VENDOR_NAME");
				if(i.vendor != null)
				if(i.vendor.contains("&")) {
					String tmp1 = i.vendor.replace("&", "&amp;");
					i.vendor = tmp1;
				}

				i.art = inv.getString("DETAIL_ARTICLE");
				i.currency = inv.getString("INVOICE_CURRENCY_CODE");
				i.date = formatXLS.format(inv.getDate("TERMS_DATE"));
				i.dateVal = formatVal.format(inv.getDate("TERMS_DATE"));
				if(!(i.currency.contentEquals("RUB"))) {
					i.amount = inv.getDouble("INVOICE_AMOUNT") * inv.getDouble("EXCHANGE_RATE");
					i.paid = inv.getDouble("AMOUNT_PAID") * inv.getDouble("EXCHANGE_RATE");
				} else {
					i.amount = inv.getDouble("INVOICE_AMOUNT");
					i.paid = inv.getDouble("AMOUNT_PAID");					
				}
				i.amount = i.amount / conversionRate;
				i.paid = i.paid / conversionRate;				
				if(Math.round(((i.amount-i.paid)*100)/i.amount) < 11) {
					//System.out.println("Skip by percent "+i.number);
					i.category = "tenPercent";
					//continue;
				}
				
				
				i.description = inv.getString("DESCRIPTION");
				if(i.description != null)
				if(i.description.contains("&")) {
					String tmp1 = i.description.replace("&", "&amp;");
					i.description = tmp1;
				}
				//System.out.println();
				//invoiceList.add(i);
				xinvoiceCheck.add("invoice", i);
				xinvoice.add("invoice", i);
				//System.out.println(xinvoice.render());
				try {
					String val = xquery(xinvoiceCheck);
					//if(val.contentEquals("()")) {
					//System.out.println(val+" "+inv.getInt("INVOICE_ID")+" "+inv.getString("INVOICE_NUM"));
					//}
					xquery(xinvoice);
					//System.out.println(val);
				} catch(Exception e) {
					e.printStackTrace();
					System.out.println("skip1 "+inv.getInt("INVOICE_ID")+" "+inv.getString("INVOICE_NUM"));
					//Ошибка 1378337
				}
				xinvoiceCheck.remove("invoice");
				xinvoice.remove("invoice");
			}
			inv.close();

			//System.exit(0);

			ST invoiceDist = groupOebs.getInstanceOf("invoicesDistribution");
			ST xinvoiceDist = groupOebs.getInstanceOf("xinvoiceDist");
			
			ResultSet invd = query(invoiceDist);
			while(invd.next()){
				xinvoiceDist.add("invoiceid", invd.getInt("INVOICE_ID"));
				//xinvoiceDist.add("name", invd.getString("DETAIL_COST_CENTER"));
				ST cfo = groupOebs.getInstanceOf("CFODescription");
				cfo.add("cfo", invd.getString("DETAIL_COST_CENTER"));
				ResultSet CFODescr = query(cfo);
				if(CFODescr.next()) {
					xinvoiceDist.add("name", CFODescr.getString("DESCRIPTION"));
				} else {
					xinvoiceDist.add("name", invd.getString("DETAIL_COST_CENTER"));
				}
				xinvoiceDist.add("amount", invd.getDouble("AMOUNT"));
				xinvoiceDist.add("code", invd.getString("LINE_TYPE_LOOKUP_CODE"));
				xinvoiceDist.add("article", invd.getString("DETAIL_ARTICLE"));

				//System.out.println(xinvoiceDist.render());
				try {
					xquery(xinvoiceDist);
				} catch(Exception e) {
//					e.printStackTrace();
					//System.out.println("skip2 "+invd.getInt("INVOICE_ID"));
				}
				
				xinvoiceDist.remove("invoiceid");
				xinvoiceDist.remove("name");
				xinvoiceDist.remove("amount");
				xinvoiceDist.remove("code");
				xinvoiceDist.remove("article");
			}
			invd.close();
			
			ST contracts1 = groupOebs.getInstanceOf("contracts1");
			ST xc1 = groupOebs.getInstanceOf("xContractInfo1");
			ArrayList<String> str1arr = new ArrayList<String>();
			
			ResultSet c1 = query(contracts1);
			while(c1.next()){
				//System.out.println(c1.getInt("INVOICE_ID"));
				String invoice = Integer.toString(c1.getInt("INVOICE_ID"));
				String contractid = c1.getString("attribute14");
				str1arr.add("<id>"+invoice+"</id><cid>"+contractid+"</cid>");
				xc1.add("id", c1.getInt("INVOICE_ID"));
				//xc1.add("", c1.getInt("PO_HEADER_ID"));
				xc1.add("cid", c1.getString("K_NUMBER"));
				//System.out.println(xc1.render());
				try {
					xquery(xc1);
				} catch(Exception e) {
//					e.printStackTrace();
					System.out.println("skip3 "+c1.getInt("INVOICE_ID"));
				}
				xc1.remove("id");
				xc1.remove("cid");
			}
			/*{
				System.out.println(str1arr.size());
				QueryProcessor proc = new QueryProcessor(xc1.render(), context);
				String[] vals = str1arr.toArray(new String[str1arr.size()]);
			    proc.bind("ids", vals);
				System.out.println(proc.value());
				proc.close();
			}*/
			c1.close();

			ST contracts2 = groupOebs.getInstanceOf("contracts2");
			ST xc2 = groupOebs.getInstanceOf("xContractInfo2");
			
			ResultSet c2 = query(contracts2);
			while(c2.next()){
				xc2.add("id", c2.getInt("INVOICE_ID"));
				xc2.add("cid", c2.getString("XXAP_CONTRACT_NUMBER"));
				try {
					xquery(xc2);
				} catch(Exception e) {
					if(c2.getInt("INVOICE_ID") == 1367011) {
//						e.printStackTrace();
					}
					System.out.println("skip4 "+c2.getInt("INVOICE_ID")+" "+c2.getString("XXAP_CONTRACT_NUMBER"));
				}
				xc2.remove("id");
				xc2.remove("cid");
			}
			c1.close();
			
			hypdata.run();
			
			ST xhplan = groupOebs.getInstanceOf("xHypPlan");
			
			{
		        for(Map.Entry<String, HData> a : hypdata.arts.entrySet()) {
		        	System.out.println(">>> "+a.getKey());
		        	System.out.println(">>> "+a.getValue());
		        	xhplan.add("art",a.getKey());
		        	xhplan.add("val",a.getValue().yplan);
		        	xhplan.add("val2",a.getValue().plan);
		        	xhplan.add("fact",a.getValue().fact);
		        	try {
						xquery(xhplan);
					} catch(Exception e) {
						e.printStackTrace();
					}
		        	xhplan.remove("art");
		        	xhplan.remove("val");
		        	xhplan.remove("val2");
		        	xhplan.remove("fact");
		        }
			}
			
			{
				QueryProcessor proc = new QueryProcessor("declare variable $ids external; $ids", context);
				String[] vals = { "a", "b", "c" };
			    proc.bind("ids", vals);
				System.out.println(proc.value());
				proc.close();
			}

			{
				ST xout=null;
				if(date != null) {
					xout = groupOebs.getInstanceOf("xoutQuery2");
					DateFormat formatXQDate = new SimpleDateFormat("yyyy-MM-dd'T'HH:mm:ss.SSS");
					xout.add("date1", formatXQDate.format(date));
					Calendar c = Calendar.getInstance(); 
					c.setTime(date); 
					c.add(Calendar.DATE, days);
					xout.add("date2", formatXQDate.format(c.getTime()));
				} else {
					xout = groupOebs.getInstanceOf("xoutQuery");
				}
				System.out.println(xout.render());
				QueryProcessor proc = new QueryProcessor(xout.render(), context);
				//System.out.println(proc.value().serialize().toString());
		        DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
		        Document dom=null;
		        try {
		        	DocumentBuilder db = dbf.newDocumentBuilder();
		        	dom = db.parse(new InputSource(new ByteArrayInputStream(proc.value().serialize().toString().getBytes("utf-8"))));
		        } catch (Exception e) {
		        	e.printStackTrace();
		        }

		        StreamResult r = null;
		        
		        try {
		        	TransformerFactory tf = TransformerFactory.newInstance("net.sf.saxon.TransformerFactoryImpl",null);
		        	//TransformerFactory tf = TransformerFactory.newInstance("org.apache.xalan.processor.TransformerFactoryImpl",null);
		        	//TransformerFactory tf = TransformerFactory.newInstance("javax.xml.transform.TransformerFactory",null);
		        	Source xslt = new StreamSource(userdir+"/templates/baseXPayments1/pay_list2.xsl");
		        	Transformer t = tf.newTransformer(xslt);
		        	DOMSource src = new DOMSource(dom);
		        	os = new ByteArrayOutputStream();
		        	r = new StreamResult(os);
		        	//t.setOutputProperty(OutputKeys.INDENT, "yes");
		        	//t.setOutputProperty(OutputKeys.METHOD, "xml");
		        	t.transform(src, r);
		        	//System.out.println(r.getOutputStream().toString());
		        } catch (Exception e) {
		        	e.printStackTrace();
		        }        

		        try {
		        	FileOutputStream fos = new FileOutputStream("out2.xml");
		        	fos.write(proc.value().serialize().toArray());
		        	//fos.write(os.toByteArray());
		        	fos.close();
		        } catch(Exception e) {
		        	e.printStackTrace();
		        }
		        
		        try {
		        	FileOutputStream fos = new FileOutputStream("out2.xls");
		        	//fos.write(proc.value().serialize().toArray());
		        	fos.write(os.toByteArray());
		        	fos.close();
		        } catch(Exception e) {
		        	e.printStackTrace();
		        }
		        
		        proc.close();
			}

			
			//System.out.println(new XQuery("//p_date").execute(context));


			//System.out.println(result.serialize().toString());
			new Delete("Requests").execute(context);
			
			new Close().execute(context);
			
			System.out.println("End.");

        } catch(Exception e) {
        	e.printStackTrace();
        }
		
	}
	
	public void done() throws SQLException {
		con.close();
	}
		
}
