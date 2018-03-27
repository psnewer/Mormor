package com.morphing.morobj;

import org.opencv.Mormor.AnyMorphing;

import android.graphics.Bitmap;

public class Linelabel {
	public long nativeObj;
	
public Linelabel(){
	
}
	public Linelabel(Bitmap bmpnew,Bitmap sigpic,Bitmap alph8,String file,int degree){
		synchronized(AnyMorphing.class){
	       this.nativeObj=linelabel0(bmpnew,sigpic,alph8,file,degree);
		}
	}
	
	public Linelabel(Linelabel lineObj){
		synchronized(AnyMorphing.class){
		this.nativeObj=linelabel1(lineObj.nativeObj);
		}
	}
	
	public void setCopy(){
		synchronized(AnyMorphing.class){
		setcopy0(this.nativeObj);
		}
	}
	
	public void setContourMode(long mornativeObj,int n){
		synchronized(AnyMorphing.class){
		setContourMode0(mornativeObj,n);
		}
	}
	
	
	public void setContourMode1(){
		synchronized(AnyMorphing.class){
		setContourMode1(this.nativeObj);
		}
	}
	
	
	public void setTempMode(boolean EDGE_MODE){
		synchronized(AnyMorphing.class){
		setTempMode0(this.nativeObj,EDGE_MODE);
		}
	}

	
	public void concateLineview(boolean EDGE_MODE){
		synchronized(AnyMorphing.class){
		concateLineview0(this.nativeObj,EDGE_MODE);
		}
	}
	
	public  int[] Isedge(float[] coords,int range,boolean EDGE_MODE){
		synchronized(AnyMorphing.class){
		return Isedge0(coords,range,this.nativeObj,EDGE_MODE);
		}
	}
	
	public  int[] addline(Object[] points){
		synchronized(AnyMorphing.class){
		return addline0(points);
		}
		
	}
	
	public void setFreeMode(long mornativeObj,int n){
		synchronized(AnyMorphing.class){
		setFreeMode0(mornativeObj,n);
		}
		
	}
	
	public void addEdge(long nativeObj,int num_rpoint,boolean EDGE_MODE){
		synchronized(AnyMorphing.class){
		addEdge0(nativeObj,num_rpoint,EDGE_MODE);
		}
	}
	
	public void addEdge_1(long nativeObj,int num_rpoint,boolean EDGE_MODE){
		synchronized(AnyMorphing.class){
		addEdge1(nativeObj,num_rpoint,EDGE_MODE);
		}
	}
	
	
	public void refreshPointer(){
		synchronized(AnyMorphing.class){
		 refreshpointer0(this.nativeObj);
		}
	}
	
	public void refreshLabel(long mornativeObj){
		synchronized(AnyMorphing.class){
		refreshLabel0(mornativeObj);
		}
	}
	
	public boolean createbmp(){
		synchronized(AnyMorphing.class){
		return createbmp0(nativeObj);
		}
	}
	
	public void clearfirebmp(){
		synchronized(AnyMorphing.class){
		clearfirebmp0(nativeObj);
		}
	}
	
	public void setFpoint(int[] fpoint){
		synchronized(AnyMorphing.class){
		setFpoint0(nativeObj,fpoint);
		}
	}
	
	public void delete(){
		synchronized(AnyMorphing.class){
		delete0(nativeObj);
		}
	}
	
	public void clearMemStorage(){
		synchronized(AnyMorphing.class){
		clearMemStorage0(this.nativeObj);
		}
	}
	public static native long linelabel0(Bitmap bmpnew,Bitmap sigpic,Bitmap alph8,String file,int degree);
	public static native long linelabel1(long nativeObj);
	public static native void setcopy0(long nativeObj);
	public static native void setContourMode0(long nativeObj,int n);
	public static native void setContourMode1(long nativeObj);
	public static native int[] Isedge0(float[] coords,int range,long nativeObj,boolean EDGE_MODE);
	public static native int[] addline0(Object[] points);
	public static native void setFreeMode0(long nativeObj,int n);
	public static native void setTempMode0(long nativeObj,boolean EDGE_MODE);
	public static native void concateLineview0(long nativeObj,boolean EDGE_MODE);
	public static native void addEdge0(long nativeObj,int num_rpoint,boolean EDGE_MODE);
	public static native void addEdge1(long nativeObj,int num_rpoint,boolean EDGE_MODE);
	public static native void refreshpointer0(long nativeObj);
	public static native void refreshLabel0(long mornativeObj);
	public static native boolean createbmp0(long nativeObj);
	public static native void clearfirebmp0(long nativeObj);
	public static native void setFpoint0(long nativeObj,int[] fpoint);
	public static native void delete0(long nativeObj);
	public static native void clearMemStorage0(long nativeObj);
}
