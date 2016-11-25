package ntv.iadb;
import oracle.apps.fnd.cp.request.*;
import java.sql.*;
import java.util.*;
import java.io.*;
import java.sql.SQLException;

import interbase.interclient.*;
/*import oracle.jdbc.*;*/
import oracle.sql.*;
import oracle.apps.fnd.util.*;


public class UploadConcurrent implements JavaConcurrentProgram  {
	
    public static final String RCS_ID = "$Header$";
    public static java.sql.Connection IBASEconn;
    public static java.sql.Connection ORAconn;
    
    protected CpContext ctx;
    protected int execResult;
    
    static final int rmContracts = 0;
    static final int rmStructure = 1;
    static final int rmShows = 2;
    static final int rmPayments = 3;
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
	    

	}
	
	void handleException(Exception e, String msg) {
	  this.ctx.getLogFile().writeln(msg, 0);
	  this.ctx.getLogFile().writeln(e.getMessage(), 0);
	  execResult = ReqCompletion.ERROR;
	}
	
	void trace(String msg) {
		this.ctx.getLogFile().writeln(msg, 0);
	}
	
	java.sql.Connection connectToInterbase() throws Exception {
		java.sql.Connection res;
		try {
            trace("Connecting to Interbase");
	        Class.forName("interbase.interclient.Driver");
            trace("Found interbase driver");
            
            interbase.interclient.DataSource dSource = new interbase.interclient.DataSource();
            trace("Interbase character ser: " + dSource.getCharSet() );
            dSource.setServerName("s-ost-ibase2.ntv-tv.ru");
            dSource.setDatabaseName("d:/data/htb.gdb");
            res = dSource.getConnection("AAAA", "1234");
            
            trace("Connected");
		}
		catch (SQLException e) {
			handleException(e, "Error when connecting to interbase");
			throw new Exception();
		}
        return res;
	}
	
	java.sql.Connection connectToOracle()  throws Exception {
		java.sql.Connection res;
		try {
			res = ctx.getJDBCConnection();
		    res.setAutoCommit(false);
		}
		catch (SQLException e) {
			handleException(e, "Error when connecting to Oracle");
			throw new Exception();
		}
        return res;
	}
	
	void refreshTable(int tableNumber) throws Exception {
		int maxRetry=3;
		
		while(maxRetry>0) {
			if(maxRetry < 3) {
				trace("Retry " + maxRetry);
				try {
					if (!IBASEconn.isClosed() ) IBASEconn.close();
				} catch(Exception e) {
					trace("Reconnect failed");
				}
				IBASEconn = connectToInterbase();
			}
			try {
	            trace("test - 1");
	          java.sql.PreparedStatement preparestmt = IBASEconn.prepareStatement("execute procedure pr_oracle1(?)");
	            trace("test - 2");
	          preparestmt.setInt(1, tableNumber);
	            trace("test - 3");
	          preparestmt.executeUpdate();
	            trace("test - 4");
	          preparestmt.close();
	            trace("test - 5");
		    //Thread.sleep(2000);
	          maxRetry=-1;
			}
			catch (SQLException exception) {
				maxRetry--;
				handleException(exception, "Error on table resynch " + new Integer(tableNumber).toString() );
				if(maxRetry == 0) throw new Exception();
	     	}
		}
	}
	
	String getCode(byte ch) {
		return "/" + new Integer(ch).toString(); 
	}
	String getCode(char ch) {
		return "/" + new Integer(ch).toString(); 
	}
	
	String stringToCodes1(String str) {
		StringBuffer buf = new StringBuffer(str);
		String res = new String();
		int len = buf.length();
		for (int i = (len - 1); i >= 0; i--) {
	         res = res + getCode(buf.charAt(i));
	      }
        return res.toString();
	}

	String stringToCodes(String str) {
		String res = new String();
		try {
			byte [] buf	= str.getBytes("Cp1251");
			int len = buf.length;
			for (int i = (len - 1); i >= 0; i--) {
		         res = res + getCode(buf[i]);
		      }
		}
		catch (Exception e) {
			handleException(e, "Could not convert encoding");
		}
        return res;
	}
	
	// trim whitespaces when copying a string
	// convert string time into number of seconds
	void copyValue(java.sql.ResultSet rs,
			       int pIndex,
			       int pType,
			       java.sql.PreparedStatement pstmt) throws Exception
	{
		try {
			switch (pType) {
			case Types.INTEGER:
				int ival = rs.getInt(pIndex);
				if (rs.wasNull() ) pstmt.setNull(pIndex, pType);
				else pstmt.setInt(pIndex, ival);
				break;
			case Types.VARCHAR:
				byte [] bval = rs.getBytes(pIndex);
				if (rs.wasNull() ) pstmt.setNull(pIndex, pType);
				else pstmt.setString(pIndex, new String(bval, "Cp1251").trim() );
				break;
			case Types.TIME:
				byte [] tval = rs.getBytes(pIndex);
				pstmt.setNull(pIndex, Types.DATE);
				//if (rs.wasNull() ) pstmt.setNull(pIndex, Types.DATE);
//				String strTime =  new String(tval, "Cp1251").trim();
//				String [] hhmi = strTime.split(".");
//				int seconds = 0;
//				if (hhmi.length == 2) {
//					seconds = (new Integer(hhmi[0]).intValue() * 60 + new Integer(hhmi[1]).intValue() ) * 60;
//					java.sql.Date tmval = new java.sql.Date(seconds * 1000);
					//pstmt.setDate(pIndex, tmval);
//				}
//				else 
					//pstmt.setNull(pIndex, Types.DATE);
				break;
			case Types.DATE:
				java.sql.Date dval = rs.getDate(pIndex);
				if (rs.wasNull() ) pstmt.setNull(pIndex, pType);
				else pstmt.setDate(pIndex, dval);
				break;
			}
		}
	    catch (Exception e) {
	    	handleException(e, "Error on valueCopy for column " + new Integer(pIndex).toString() );
	    	throw e;
	    }
	}
	
	void copyTableToShadow(String srcName, String destName, String [] colList, int [] typesList) throws Exception  {
		int maxRetry=3;
		
		while(maxRetry>0) {
			trace("Retry " + maxRetry);
			if(maxRetry < 3) {
				trace("Retry " + maxRetry);
				//if (!IBASEconn.isClosed() ) IBASEconn.close();
				IBASEconn = connectToInterbase();
			}
			String truncateSql = "truncate table " + destName;
			String colCommaSeparated = "";
			String valQuestions = "";
			
			if (colList.length != typesList.length) 
				throw new Exception("Error in copyTableToShadow parameters");
			
			for (int i = 0; i < colList.length; i++) {
				colCommaSeparated = (colCommaSeparated.length() == 0 ? colList[i] : colCommaSeparated + ", " + colList[i]);
				valQuestions = (valQuestions.length() == 0 ? "?" : valQuestions + ", ?");
			}
			String insertSql = "insert into " +  destName + " (" +  colCommaSeparated + " ) VALUES (" + valQuestions + ")";
			String selectSql = "SELECT " + colCommaSeparated + " FROM " + srcName;
			
			trace("copy table " + srcName);
			java.sql.PreparedStatement preparestmt = ORAconn.prepareStatement(truncateSql);
	        preparestmt.executeUpdate();
	        preparestmt.close();
			trace("truncated table " + destName);
			
			trace("prepared SQL: ");
			trace(selectSql);
			trace(insertSql);
			
			preparestmt = ORAconn.prepareStatement(insertSql);
	        java.sql.Statement stmt = IBASEconn.createStatement();
			try {
		        java.sql.ResultSet rs = stmt.executeQuery(selectSql);
		        
		        while (rs.next() ) {
			        try {
			        	for (int nCol = 0; nCol < typesList.length; nCol++) 
			        		copyValue(rs, nCol + 1, typesList[nCol], preparestmt);
			        }
			        catch (Exception e) {
			        	handleException(e, "Error preparing data: " + new String(rs.getBytes("B0NAME1"), "Cp1251") );
			        }
			        try {
			            preparestmt.executeUpdate();
			        }
			        catch (Exception e) {
			        	handleException(e, "Error on recording to Oracle");
			        }
		        }
		        preparestmt.close();
		        ORAconn.commit();
		        rs.close();
		        stmt.close();
		        maxRetry=-1;
			} catch (Exception e) {
				trace("Exception"+maxRetry);
				maxRetry--;
			}
			finally {
				//stmt.close();
		        ORAconn.commit();
			}
		}
	}

	void copyProducts() throws Exception {
		String [] colListT1 = {"B0KOD", "B0NAME1", "B0NAME2", "N_F", "OT_Z", "HDMP",
				               "B4KOD", "B5KOD", "B5NOMER_DOG", "B5DATA_DOG",
				               "B5S25KOD", "B5S25NAME", "B5S_P", "B5CYMMA", "B5CYMMA1", 
				               "B5CPOK_PER1", "B5CPOK_PER2",
				               "B5SKOL_POK", "B5P_EX", "DATA_D", "B5S22KOD", "B5S22NAME"};
		int [] typeListT1 = {Types.INTEGER, Types.VARCHAR, Types.VARCHAR, Types.INTEGER, Types.INTEGER,
						     Types.INTEGER, Types.INTEGER, Types.INTEGER, Types.VARCHAR, Types.DATE, 
				             Types.INTEGER, Types.VARCHAR, Types.INTEGER, Types.INTEGER, Types.INTEGER,
				             Types.DATE, Types.DATE, 
				             Types.INTEGER, Types.INTEGER, Types.DATE, Types.INTEGER, Types.VARCHAR};
		
		copyTableToShadow("T1", "xxhtb.tbl_po_t1_shadow", colListT1, typeListT1);
    }

	void copySeries() throws Exception {
		String [] colListT2 = {"B0KOD", "ID", 
	               "BS1KOD", "BS1NAME1", "BS1NAME2", "BS1NOMER", "BS1S23KOD", 
	               "BS2KOD", "BS2NAME1", "BS2NAME2", "BS2NOMER", "BS2S23KOD",
	               "NREC", "CUR_DATE"};
		int [] typeListT2 = {Types.INTEGER, Types.INTEGER,
			             Types.INTEGER, Types.VARCHAR, Types.VARCHAR, Types.INTEGER, Types.INTEGER,
			             Types.INTEGER, Types.VARCHAR, Types.VARCHAR, Types.INTEGER, Types.INTEGER,
			             Types.INTEGER, Types.DATE};

		copyTableToShadow("T2", "xxhtb.tbl_po_t2_shadow", colListT2, typeListT2);
	}

	void copyRights() throws Exception {
		String [] colListT3 = {"B0KOD", "B5KOD",
				               "BS1KOD", "BS1NOMER", "BS2KOD", "BS2NOMER",
				               "NREC", "CUR_DATE"};
		int [] typeListT3 = {Types.INTEGER, Types.INTEGER,
				             Types.INTEGER, Types.INTEGER, Types.INTEGER,Types.INTEGER,
				             Types.INTEGER, Types.DATE};
		copyTableToShadow("T3", "xxhtb.tbl_po_t3_shadow", colListT3, typeListT3);
    }

	void copyShows() throws Exception {
		String [] colListT4 = {"B0KOD", "B5KOD",
				               "BS1KOD", "BS2KOD", 
				               "DATA_POK", "VTIME", "POVTOR", "S1KOD",
				               "NREC", "CUR_DATE", "HRON_F"};
		
		int [] typeListT4 = {Types.INTEGER, Types.INTEGER ,
				             Types.INTEGER, Types.INTEGER, 
				             Types.DATE, Types.VARCHAR, Types.VARCHAR, Types.INTEGER,
				             Types.INTEGER, Types.DATE, Types.VARCHAR};
		copyTableToShadow("T4", "xxhtb.tbl_po_t4_shadow", colListT4, typeListT4);
    }

	void replicateContracts() throws Exception {
		refreshTable(1);
		copyProducts();
	}
	
	void copyStructure() throws Exception {
		copyProducts();
		copySeries();
		copyRights();
	}
	
	void replicateStructure() throws Exception {
		refreshTable(1);
		refreshTable(2);
		refreshTable(3);
		copyStructure();
	}
	
	void replicateShows() throws Exception {
		refreshTable(4);
		copyShows();
	}
	
	void replicatePayments() throws Exception {
		refreshTable(5);
		
	}
	
	void replicate(int level) throws Exception {
		
		try {
			ORAconn = connectToOracle();
			IBASEconn = connectToInterbase();
			
			switch (level) {
			case rmContracts: replicateContracts();
  	        		break;
			case rmStructure: replicateStructure();
			        break;
			case rmShows: replicateShows();
			        break;
			case rmPayments: replicatePayments();
			        break;
			}
		}
		catch (Exception e) {
			handleException(e, "Error on replication");
			throw e;
		}
		finally {
			if (!ORAconn.isClosed() ) ORAconn.close();
			if (!IBASEconn.isClosed() ) IBASEconn.close();
		}
	}

	public void runProgram(CpContext ctx) {
		this.ctx = ctx;
		int replicationMode = rmStructure;
		//Locale l;
		trace("IADB Replication");
		trace(this.ctx.getLocale().getDisplayName() ); 
		int res = ReqCompletion.NORMAL;
		trace("check parameters");
		ParameterList params = ctx.getParameterList();
		if (params.hasMoreElements() ) {
			NameValueType namevaluetype = params.nextParameter();
			trace("found parameter " + namevaluetype.getName() + " = " + namevaluetype.getValue() );
			if (namevaluetype.getName().equalsIgnoreCase("P_REPLICATION_MODE") ) {
				String strVal = namevaluetype.getValue();
				trace("setting replication mode to " + strVal);
				if (strVal.equalsIgnoreCase("CONTRACTS") )
					replicationMode = rmContracts;
				else if (strVal.equalsIgnoreCase("STRUCTURE") )
					replicationMode = rmStructure; 
				else if (strVal.equalsIgnoreCase("SHOWS") )
					replicationMode = rmShows;
				else if (strVal.equalsIgnoreCase("PAYMENTS") )
					replicationMode = rmPayments;
			}
		}
        
		try {
			replicate(replicationMode);
		}
		catch (Exception e) {
			res = ReqCompletion.ERROR;
		}
		
        ctx.getReqCompletion().setCompletion(res, "");
	}
}
