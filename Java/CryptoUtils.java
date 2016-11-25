package cloud.crypt;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.security.DigestInputStream;
import java.security.InvalidAlgorithmParameterException;
import java.security.InvalidKeyException;
import java.security.Key;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.spec.KeySpec;
 
import javax.crypto.BadPaddingException;
import javax.crypto.Cipher;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.SecretKeyFactory;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;

import org.apache.commons.codec.binary.Base64;

public class CryptoUtils {
    private static final String ALGORITHM = "AES";
    private static final String TRANSFORMATION = "AES/CBC/NoPadding";
    private static final Integer blockLength = 256;
    
    public static void encrypt(String key, File inputFile, File outputFile)
            throws CryptoException {
        doCrypto(Cipher.ENCRYPT_MODE, key, inputFile, outputFile);
    }
 
    public static void decrypt(String key, File inputFile, File outputFile)
            throws CryptoException {
        doCrypto(Cipher.DECRYPT_MODE, key, inputFile, outputFile);
    }
 
    private static void doCrypto(int cipherMode, String key, File inputFile,
            File outputFile) throws CryptoException {
        try {
        	String fileMD5="";
        	String calcMD5="";
        	switch(cipherMode) {
        	case 1:{
	        	//System.out.println("mode:"+cipherMode);
	        	MessageDigest md = MessageDigest.getInstance("MD5");
	            //String initVector = "****************";
	            String initVector = "***************";
	            IvParameterSpec iv = new IvParameterSpec(initVector.getBytes("UTF-8"));
	        	//SecretKeyFactory keyFactory = SecretKeyFactory.getInstance(ALGORITHM);
	        	//KeySpec ks = 
	            SecretKeySpec secretKey = new SecretKeySpec(key.getBytes(),ALGORITHM);
	            Cipher cipher = Cipher.getInstance(TRANSFORMATION);
	            cipher.init(cipherMode, secretKey,iv);
	             
	            FileInputStream inputStream = new FileInputStream(inputFile);
	            FileOutputStream outputStream = new FileOutputStream(outputFile);
	            byte[] inputBytes = new byte[blockLength];
	            Integer bytesread=129384;
	            char[] test1 = new char[Integer.SIZE/Byte.SIZE];
	            byte[] header = new byte[Integer.SIZE/Byte.SIZE];
	            byte[] type={0};
	            for(int i=0;i<Integer.SIZE/Byte.SIZE;i++) {
	            	//System.out.println("===:"+(bytesread & 0xFF));
	            	test1[i] = (char)(bytesread & 0xFF);
	            	header[i]=(byte)test1[i];
	            	bytesread=bytesread>>8;
	            }
	            Integer test2=0;
	            String istr="";
	            for(int i=(Integer.SIZE/Byte.SIZE)-1;i>=0;i--) {
	            	test2=test2 | ((int)header[i] & 0xFF);
	            	if(i>0) test2=test2<<8;
	            	//System.out.println("++:"+test2+" "+(char)header[i]);
	            }
	            //System.out.println(test2);
	            while(inputStream.available()>0) {
	                bytesread = inputStream.read(inputBytes,0,blockLength);
	                md.update(inputBytes, 0, bytesread);
	                //System.out.print(","+bytesread);
	                if(bytesread<blockLength) {
	                	for(int i=bytesread;i<blockLength;i++) {
	                		inputBytes[i]=0;
	                	}
	                }
	                //System.out.println(bytesread);
	                byte[] outputBytes = cipher.doFinal(inputBytes,0,blockLength);
		            for(int i=0;i<Integer.SIZE/Byte.SIZE;i++) {
		            	//System.out.println("===:"+(bytesread & 0xFF));
		            	test1[i] = (char)(bytesread & 0xFF);
		            	header[i]=(byte)test1[i];
		            	bytesread=bytesread>>8;
		            }
		            type[0]=1;
		            outputStream.write(type,0,1);
	                outputStream.write(header,0,4);
	                outputStream.write(outputBytes,0,blockLength);
	            }
	            byte[] digest = md.digest();
	            int l=digest.length;
	            for(int i=0;i<Integer.SIZE/Byte.SIZE;i++) {
	            	//System.out.println("===:"+(bytesread & 0xFF));
	            	test1[i] = (char)(l & 0xFF);
	            	header[i]=(byte)test1[i];
	            	l=l>>8;
	            }
	            type[0]=2;
	            outputStream.write(type,0,1);
                outputStream.write(header,0,4);
                outputStream.write(digest,0,digest.length);
                
	            //System.out.println(org.apache.commons.codec.digest.DigestUtils.md5Hex(digest));
	            
	            inputStream.close();
	            outputStream.close();	            
        	}
	            break;
        	case 2:
        	{
	        	//System.out.println("mode:"+cipherMode);
	        	MessageDigest md = MessageDigest.getInstance("MD5");
	            //String initVector = "*****************";
	        	String initVector = "*****************";
	        	IvParameterSpec iv = new IvParameterSpec(initVector.getBytes("UTF-8"));
	        	SecretKeySpec secretKey = new SecretKeySpec(key.getBytes(), ALGORITHM);
	            Cipher cipher = Cipher.getInstance(TRANSFORMATION);
	            cipher.init(cipherMode, secretKey,iv);
	             
	            FileInputStream inputStream = new FileInputStream(inputFile);
	            FileOutputStream outputStream = new FileOutputStream(outputFile);
	            //byte[] inputBytes = new byte[16];
	            Integer bytesread=129384;
	            char[] test1 = new char[Integer.SIZE/Byte.SIZE];
	            byte[] header = new byte[Integer.SIZE/Byte.SIZE];
	            byte[] type = {0};
	            while(inputStream.available()>0) {
	            	bytesread = inputStream.read(type,0,1);
	            	if(bytesread<1) {
	            		System.out.println("Header error");
	            		break;
	            	}
	            	bytesread = inputStream.read(header,0,4);
	            	if(bytesread<4) {
	            		System.out.println("Header error");
	            		break;
	            	}
		            Integer test2=0;
		            for(int i=(Integer.SIZE/Byte.SIZE)-1;i>=0;i--) {
		            	test2=test2 | ((int)header[i] & 0xFF);
		            	if(i>0) test2=test2<<8;
		            	//System.out.println("++:"+test2+" "+header[i]);
		            }
		            //System.out.println("++:"+test2);
		            if(type[0]==1) {
			            byte[] inputBytes = new byte[blockLength];
		            	bytesread = inputStream.read(inputBytes,0,blockLength);
		                if(bytesread<blockLength) {
		                	System.out.println("Decript block error");
		                	break;
		                }
		                //System.out.println(test2);	                
	                	byte[] outputBytes = cipher.doFinal(inputBytes,0,blockLength);
	                	md.update(outputBytes, 0, test2);
	                	outputStream.write(outputBytes,0,test2);
		            } else if(type[0]==2) {
			            byte[] inputBytes = new byte[test2];
		            	bytesread = inputStream.read(inputBytes,0,test2);
		                if(bytesread<test2) {
		                	System.out.println("hash sum block error");
		                	break;
		                }
		                //System.out.println(test2);
		                fileMD5=org.apache.commons.codec.binary.Hex.encodeHexString(inputBytes);
		            	//System.out.println("MD5 from file:"+fileMD5);
	                }
	            }
	            
	            inputStream.close();
	            outputStream.close();

	            byte[] digest = md.digest();
	            calcMD5=org.apache.commons.codec.binary.Hex.encodeHexString(digest);
	            //System.out.println(calcMD5);
	            if(calcMD5.contentEquals(fileMD5)) {
	            	System.out.println("OK");
	            } else {
	            	System.out.println("Error");
	            }
        	}
        		break;
        	default:
        		System.out.println(cipherMode);
        	}
        } catch (InvalidAlgorithmParameterException | NoSuchPaddingException | NoSuchAlgorithmException
                | InvalidKeyException | BadPaddingException
                | IllegalBlockSizeException | IOException ex) {
            throw new CryptoException("Error encrypting/decrypting file", ex);
        }
    }
}

