package org.opencv.Mormor;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import android.annotation.SuppressLint;
import android.content.Context;
import android.content.SharedPreferences;
import android.graphics.BitmapFactory;
import android.graphics.BitmapFactory.Options;

public class DataManager implements Cloneable{
	  AnyMorphing anymorphing;
	  SharedPreferences prefs;
	  SharedPreferences.Editor prefsEdit;


	public DataManager(Context paramContext, AnyMorphing paramAnyMorphing)
	  {
	    this.anymorphing = paramAnyMorphing;
	    this.prefs = paramAnyMorphing.getPreferences(0);
	    this.prefsEdit = this.prefs.edit();	    
	  }
	
	
	void recallPrefs()
	  {
	    anymorphing.sig = this.prefs.getFloat("sig", 1);
	    
	    anymorphing.synratio = this.prefs.getFloat("synratio", 1);
	    
	    anymorphing.size= this.prefs.getInt("siz", 15);
	    
	    anymorphing.anymorphingdata.mor.initParam(anymorphing.sig, anymorphing.synratio);
	    
	    anymorphing.lineView.paint_clear.setStrokeWidth(anymorphing.size);
	    
	  }
	
	@SuppressLint("NewApi")
	void onStart()
	  {
		BitmapFactory.Options opts = new Options();
		opts.inJustDecodeBounds = true;
		BitmapFactory.decodeResource(anymorphing.getResources(),
                R.drawable.rabbit,opts);
		int imageHeight = opts.outHeight;
		int imageWidth = opts.outWidth;
		opts.inSampleSize=resize(imageHeight,imageWidth);
		opts.inJustDecodeBounds=false;
		opts.inMutable=true;	
	    opts.inPurgeable=true;
		InputStream is=anymorphing.getResources().openRawResource(R.drawable.rabbit);
		 File file=new File(AnyMorphing.SDCARD_ROOT_PATH+AnyMorphing.SAVE_PATH_IN_SDCARD+AnyMorphing.IMAGE_CAPTURE_NAME);
		 file.deleteOnExit();
		 OutputStream stream = null;
		try {
			stream = new FileOutputStream(file);
		} catch (FileNotFoundException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
        int ch;
		 byte[] buf=new byte[1024];
	        try {
				while ((ch = is.read(buf)) != -1) {   
				    stream.write(buf,0,ch);   
				}
				stream.flush();
		        stream.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				
			}		        
	        anymorphing.bmpnew=BitmapFactory.decodeFile(AnyMorphing.SDCARD_ROOT_PATH+AnyMorphing.SAVE_PATH_IN_SDCARD+AnyMorphing.IMAGE_CAPTURE_NAME,opts);	        
	  }

	
	public static int resize(int height,int width){
		int r=1;
		double r1=height/600.0;
		double r2=width/600.0;
		if(width<=600||height<=600||width*height<=1000000)
			r=1;
		else
			r=(int) Math.ceil( (r1<r2?r1:r2));
		if(height/r*width/r>1000000)
			r=(int)Math.ceil((r1>r2?r1:r2));
		return r;
		
	}
	
	
	void saveprefs(float paramFloat1,float paramFloat3,int paramInt4){
		
		this.prefsEdit.putFloat("sig", paramFloat1);
	    this.prefsEdit.commit();
	    this.prefsEdit.putFloat("synration", paramFloat3);
	    this.prefsEdit.commit();
	    this.prefsEdit.putInt("siz",paramInt4);
	    this.prefsEdit.commit();
		
	}
	
		  
	  public abstract interface DataCallback
	  {
	    public abstract void setBitmap();
	  }
	  
	  public DataManager clone() throws CloneNotSupportedException{
			return (DataManager) super.clone();
		}
}
