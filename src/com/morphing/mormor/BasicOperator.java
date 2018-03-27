package com.morphing.mormor;

import java.io.IOException;

import android.media.ExifInterface;

public class BasicOperator {
	
	public static int readPictureDegree(String path) {  
	    int degree  = 0;  
	    try {  
	            ExifInterface exifInterface = new ExifInterface(path);  
	            int orientation = exifInterface.getAttributeInt(ExifInterface.TAG_ORIENTATION, ExifInterface.ORIENTATION_NORMAL);  
	            switch (orientation) {  
	            case ExifInterface.ORIENTATION_ROTATE_90:  
	                    degree = 90;  
	                    break;  
	            case ExifInterface.ORIENTATION_ROTATE_180:  
	                    degree = 180;  
	                    break;  
	            case ExifInterface.ORIENTATION_ROTATE_270:  
	                    degree = 270;  
	                    break;  
	            }  
	    } catch (IOException e) {  
	            e.printStackTrace();  
	    }  
	    return degree;  
	}  

}
