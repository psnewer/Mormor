package com.morphing.morobj;

import org.opencv.Mormor.AnyMorphing;

public class Morphing {

	
	public long nativeObj;
	
	public int[] graspPoint;
	
	public Morphing(Linelabel lineObj){
		synchronized(AnyMorphing.class){
		nativeObj=morphing0(lineObj.nativeObj);
		}
	}
	
	public Morphing(Morphing mor){
		synchronized(AnyMorphing.class){
		nativeObj=morphing2(mor.nativeObj);
		this.graspPoint=mor.graspPoint;
		}
	}
	
	public void setLineobj(Linelabel lineObj){
		synchronized(AnyMorphing.class){
		setlineobj0(nativeObj,lineObj.nativeObj);
		}
	}
	
	public void getaxis1(int[] fpoint1,int[] fpoint2,int[] rpoint,int contour_number){
		synchronized(AnyMorphing.class){
		getaxis10(this.nativeObj,fpoint1,fpoint2,rpoint,contour_number);
		}
	}
	
	public void initParam(float paramInt1,float paramInt3){
		synchronized(AnyMorphing.class){
		initParam0(nativeObj,paramInt1,paramInt3);
		}
	}
	
	public void setcontourcolor(){
		synchronized(AnyMorphing.class){
		 setcontourcolor0(nativeObj);
		}
	}
	
	
	public void setLine(int n){
		synchronized(AnyMorphing.class){
		setLine0(this.nativeObj,n);
		}
	}
	
	
    public void clearLine(int n){
    	synchronized(AnyMorphing.class){
    	clearLine0(this.nativeObj,n);
    	}
    }
	
	public void morphing(int [] point4,int num_rpoint,int contour_number){
		synchronized(AnyMorphing.class){
		   runmorphing(nativeObj, point4,num_rpoint,contour_number);
		}
	}

	
	public boolean Is_logical(int[] temp_edge){
		synchronized(AnyMorphing.class){
		return Islogical0(this.nativeObj,temp_edge);
		}
	}
	
	public boolean generate(int num_rpoint){
		synchronized(AnyMorphing.class){
		 return generate0(this.nativeObj,num_rpoint);
		}
	}
	
	
	public void generate_image(int n){
		synchronized(AnyMorphing.class){
		generateimage0(this.nativeObj,n);
		}
	}
	
	public void generate_contour(int n){
		synchronized(AnyMorphing.class){
		generatecontour0(this.nativeObj,n);
		}
	}
	
	public void delete(){
		synchronized(AnyMorphing.class){
		delete0(nativeObj);
		}
	}
	
	public static native long morphing0(long nativeObj);
	public static native long morphing2(long nativeObj);
	public static native void setlineobj0(long nativeObj,long labelnativeObj);
	public static native void getaxis10(long nativeObj,int[] fpoint1,int[] fpoint2,int[] rpoint,int contour_number);
	public static native void initParam0(long nativeObj,float paramInt1,float paramInt3);
	public static native void setcontourcolor0(long nativeObj);
	public static native void setLine0(long nativeObj,int n);
	public static native void clearLine0(long nativeObj,int n);
	public native void runmorphing(long nativeObj,int[] point4,int num_rpoint,int contour_number);
	public static native void generateimage0(long nativeObj,int n);
	public native void generatecontour0(long nativeObj,int n);
	public static native boolean generate0(long nativeObj,int num_rpoint);
	public static native boolean Islogical0(long nativeObj,int[] temp_edge);
	public static native void delete0(long nativeObj);
}
