package reports;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

import com.essbase.api.base.*;
import com.essbase.api.metadata.IEssCubeOutline;
import com.essbase.api.metadata.IEssDimension;
import com.essbase.api.metadata.IEssMember;
import com.essbase.api.session.*;
//import com.essbase.api.datasource.*;
import com.essbase.api.dataquery.*;
import com.essbase.api.datasource.IEssCube;
import com.essbase.api.datasource.IEssOlapApplication;
import com.essbase.api.datasource.IEssOlapFileObject;
import com.essbase.api.datasource.IEssOlapServer;
import com.essbase.api.domain.*;

import org.apache.commons.io.FileUtils;
//import org.apache.commons.io.FileUtils;
import org.apache.poi.ss.usermodel.*;
import org.apache.poi.ss.util.CellRangeAddress;
import org.apache.poi.xssf.usermodel.*;
import org.stringtemplate.v4.*;


public class HyperionData {

    private static String s_userName = "admin";
    private static String s_password = "*******";

    private static String s_olapSvrName = "hyperion.ntv-tv.ru";
    private static String s_provider = "http://hyperion.ntv-tv.ru:13080/aps/JAPI"; // Default

    private static String s_appName = "NTV2014";
    private static String s_cubeName = "Budget";

    private static String inputDataFile = "/data/baseXPayments1/СрезДляPayments.xlsx";

    private static final int FAILURE_CODE = 1;

    private static IEssCube cube = null;

    public static IEssbase essCalc = null;
    public static IEssOlapServer olapSvrCalc = null;
    public static IEssOlapApplication appCalc = null;
    public static IEssCube cubeCalc = null;

    public static IEssCubeOutline otl = null;

    public IEssbase ess = null;
    public IEssCubeView cv = null;

    //Interface
    public Map<String,HData> arts = new HashMap<String,HData>();
        
    public HyperionData(){
    	System.out.println("Start");
    }
    
    public void run() {
        XSSFWorkbook wbs=null;

        String userdir = System.getProperty("user.dir");
		File dt = new File(userdir+inputDataFile);
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
		XSSFSheet s = wbs.getSheetAt(0);  //Plan
		XSSFSheet s1 = wbs.getSheetAt(1); //Fact
        XSSFSheet s2 = wbs.getSheetAt(2); //Final BDDS

        XSSFRow r = null;
        XSSFCell c = null;
        r = s.getRow(0);
        c = r.getCell(1);
        System.out.println("Cell Value: " +c.getStringCellValue());

    	
    	try {
	    	ess = IEssbase.Home.create(IEssbase.JAPI_VERSION);
	
	        // Sign On to the Provider
	        IEssDomain dom
	            = ess.signOn(s_userName, s_password, false, null, s_provider);

	        cv = dom.openCubeView("NTV",
                    s_olapSvrName, s_appName, s_cubeName);
	        
	        IEssGridView grid = cv.getGridView();
	        
	        grid.setSize(arts.size()+3, 14);
	        
	        //Copy grid values
	        try {
	            r = s.getRow(0);
		        for(int i=0;i<14;i++) {
		            c = r.getCell(i);
		            if(c!=null) {
			            System.out.println("Cell Value: " +c.getStringCellValue());
			            grid.setValue(0, i, c.getStringCellValue());
		            }
		        }
		        r = s.getRow(1);
		        for(int i=0;i<14;i++) {
		            c = r.getCell(i);
		            if(c!=null) {
			            System.out.println("Cell Value: " +c.getStringCellValue());
			            grid.setValue(1, i, c.getStringCellValue());
		            }
		        }
		        //Fill articles
		        /*
		        for(int i=0;i<14;i++) {
		        	r = s.getRow(1);
		            c = r.getCell(i);
		            System.out.println("Cell Value: " +c.getStringCellValue());
		            grid.setValue(1, i, c.getStringCellValue());
		        }*/
		        {
			        int ir=2;
			        for(Map.Entry<String, HData> art : arts.entrySet()) {
			        	/*if(art.getKey().contains("GPM2007CC011129")) {
			        		grid.setValue(ir, 0, "CF_GPM2007CC0111239");
			        	} else {
			        		grid.setValue(ir, 0, "CF_"+art.getKey());
			        	}*/
			        	grid.setValue(ir, 0, "CF_"+art.getKey());
			        	ir++;
			        }
		        }
		        cv.performOperation(cv.createIEssOpRetrieve());
		        
		        //System.out.println("3>> " + grid.getValue(0, 9));

		        {
			        int ir=2;
			        for(ir=2;ir<grid.getCountRows();ir++) {
			        	try {
				        	//System.out.println(">> " + grid.getStringValue(ir, 0).substring(grid.getStringValue(ir, 0).indexOf("CF_")+3));
					        //System.out.println(">> " + grid.getDoubleValue(ir, 1));
					        arts.put(grid.getStringValue(ir, 0).substring(grid.getStringValue(ir, 0).indexOf("CF_")+3), new HData(grid.getDoubleValue(ir, 1), grid.getDoubleValue(ir, 2),0.0));
			        	} catch(Exception e) {
			        		System.out.println("ExceptionValue: " + grid.getStringValue(ir, 1));
			        	}
			        }
		        }

		        grid.setValue(0, 9,"S_Факт");
		        cv.performOperation(cv.createIEssOpRetrieve());
		        
		        {
			        int ir=2;
			        for(ir=2;ir<grid.getCountRows();ir++) {
			        	try {
				        	//System.out.println(">> " + grid.getStringValue(ir, 0).substring(grid.getStringValue(ir, 0).indexOf("CF_")+3));
					        //System.out.println(">> " + grid.getDoubleValue(ir, 1));
					        HData hd = arts.get(grid.getStringValue(ir, 0).substring(grid.getStringValue(ir, 0).indexOf("CF_")+3));
					        hd.fact = grid.getDoubleValue(ir, 2);
			        	} catch(Exception e) {
			        		System.out.println("ExceptionValue: " + grid.getStringValue(ir, 1));
			        	}
			        }
		        }

		        
		        {
			        for(Map.Entry<String, HData> art : arts.entrySet()) {
			        	System.out.println(">>> "+art.getKey());
			        	System.out.println(">>> "+art.getValue().yplan);
			        	System.out.println(">>> "+art.getValue().plan);
			        	System.out.println(">>> "+art.getValue().fact);
			        }
		        }

		        
	        } catch(Exception e) {
	        	e.printStackTrace();
	        }
	        System.out.println(grid.getCountColumns()+" "+grid.getCountRows());
	        
	        cv.close();
	        
    	} catch(Exception e) {
    		e.printStackTrace();
    	}
    }
    
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
        // Create JAPI instance.
		HyperionData hypdata = new HyperionData();
		hypdata.arts.put("23120B23120B",new HData());
		hypdata.arts.put("GPM2007CC011129",new HData());
		//hypdata.arts.add("230000230000");
		hypdata.run();
		
	}

}
