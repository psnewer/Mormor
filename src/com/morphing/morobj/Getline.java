package com.morphing.morobj;

import org.opencv.Mormor.AnyMorphing;

import android.graphics.Bitmap;

public class Getline {
	public long nativeObj;
	public int clear;


	public Getline(long nativeObj){
		synchronized(AnyMorphing.class){
		this.nativeObj=getline2(nativeObj);
		}
		clear=0;
	}
	
	public void setLineobj(Linelabel lineobj){
		synchronized(AnyMorphing.class){
		setLineobj0(nativeObj,lineobj.nativeObj);
		}
	}
	
	
	public void _getline(int[] fpoint1,int[] fpoint2,int[] fpoint3){
		synchronized(AnyMorphing.class){
	    clear=getline0(nativeObj,fpoint1,fpoint2,fpoint3);
		}
	}	
	
	public void _getline(int[] fpoint1,int[] fpoint2){
		synchronized(AnyMorphing.class){
	    clear=getline3(nativeObj,fpoint1,fpoint2);
		}
	}

	public void lineRefresh(long mornativeObj,int num_rpoint,int clear){
		synchronized(AnyMorphing.class){
		lineRefresh0(nativeObj,mornativeObj,num_rpoint,clear);
		}
	}
	
	public void lineRefresh(long mornativeObj,Bitmap firebmp,int clear){
		synchronized(AnyMorphing.class){
		lineRefresh1(nativeObj,mornativeObj,firebmp,clear);
		}
	}

	
	public long getSeq(){
		synchronized(AnyMorphing.class){
		return getSeq0(this.nativeObj);
		}
	}
	
	
	public void clearMem(){
		synchronized(AnyMorphing.class){
		clearMem0(this.nativeObj);
		}
	}
	
	public static native void setLineobj0(long getlinenativeobj,long nativeObj);
	public static native int getline0(long nativeObj,int[] fpoint1,int[] fpoint2,int[] fpoint3);
	public static native int getline3(long nativeObj,int[] fpoint1,int[] fpoint2);
	public static native long getline2(long nativeObj);
	public static native void lineRefresh0(long nativeObj,long mornativeObj,int num_rpoint,int clear);
	public static native void lineRefresh1(long nativeObj,long mornativeObj,Bitmap firebmp,int clear);
	public static native long getSeq0(long nativeObj);
	public static native void clearMem0(long nativeObj);
}
