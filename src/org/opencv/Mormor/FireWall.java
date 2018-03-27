package org.opencv.Mormor;

import java.util.Arrays;
import java.util.Vector;

import org.opencv.Mormor.AnyMorphing;

import com.morphing.mormor.FireType;

import android.annotation.SuppressLint;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Matrix;
import android.graphics.Paint;
import android.graphics.PorterDuffXfermode;
import android.graphics.Bitmap.Config;
import android.graphics.PorterDuff.Mode;
import android.graphics.Rect;
import android.util.AttributeSet;
import android.widget.ImageView;

public class FireWall extends ImageView {
    public Paint paint_clear;
    public Paint paint;
    public Bitmap firebmp;
    public Canvas firecanvas;
    public AnyMorphing anymorphing;
    
    Matrix mat;
    Matrix mat_inver;
    public FireWallData firewalldata=new FireWallData();
    public long nativeObj;
    public Vector<FireType> file;                                                                                                                                  
    
    public class FireWallData implements Cloneable {        
        public int[] wpoint1;
        public int[] wpoint2;
        
        public int startind=0;
        public int endind=0;
        public FireWallData clone() throws CloneNotSupportedException{
    		return (FireWallData) super.clone();
    	}
    }
    
  public FireWall(Context paramContext)
  {
    super(paramContext); 

  }
  
  public FireWall(Context paramContext, AttributeSet paramAttributeSet)
  {
    super(paramContext, paramAttributeSet); 
    paint_clear=new Paint();
    paint_clear.setXfermode(new PorterDuffXfermode(Mode.CLEAR));  
    paint=new Paint();
    mat=new Matrix();
    mat_inver=new Matrix();
  }

@SuppressLint("NewApi")
public void init(AnyMorphing anymorphing){   
	    this.anymorphing=anymorphing;
	    firebmp=Bitmap.createBitmap(anymorphing.picw, anymorphing.pich, Config.ARGB_8888);	    	    	    
	    firecanvas=new Canvas(firebmp);	
	    file=new Vector<FireType>();
	    this.nativeObj=FireWall0(firebmp);
  }
  
 
@SuppressLint("NewApi")
public void setWpoint(int num_wpoint,int[] wpoint){
	  if(num_wpoint==1){
		  firewalldata.wpoint1=Arrays.copyOf(wpoint, 2);
		  num_wpoint=1;
		  Rect rec=new Rect(firewalldata.wpoint1[0]-8,firewalldata.wpoint1[1]-8,firewalldata.wpoint1[0]+8,firewalldata.wpoint1[1]+8);
		  firecanvas.drawBitmap(anymorphing.nail1,null,rec,paint);
		  checkfile();
		  file.add(new FireType(wpoint,0,1));
		  anymorphing.mystackele.release(8);
		  invalidate();
	  }
	  else if(num_wpoint==2){		  
		  firewalldata.wpoint2=Arrays.copyOf(wpoint, 2);
		  num_wpoint=2;
		  Rect rec=new Rect(firewalldata.wpoint2[0]-8,firewalldata.wpoint2[1]-8,firewalldata.wpoint2[0]+8,firewalldata.wpoint2[1]+8);
		  firecanvas.drawBitmap(anymorphing.nail1,null,rec,paint);
		  long seq=anymorphing.mytimer.Line1.getSeq();
		  checkfile();
		  file.add(new FireType(wpoint,seq,2));
		  anymorphing.mystackele.release(8);
		  invalidate();
	  }
		  
  }



 public void reDraw(){
	firecanvas.drawPaint(paint_clear);
	anymorphing.anymorphingdata.lineObj.clearfirebmp();
	
	for(int i=firewalldata.startind;i<firewalldata.endind;i++){
		FireType _fire=file.get(i);
		if(_fire.Type==1){
			Rect rec=new Rect(_fire.wpoint1[0]-8,_fire.wpoint1[1]-8,_fire.wpoint1[0]+8,_fire.wpoint1[1]+8);
			firecanvas.drawBitmap(anymorphing.nail1,null,rec,paint);
		}
		else if(_fire.Type==2){
			Rect rec=new Rect(_fire.wpoint2[0]-8,_fire.wpoint2[1]-8,_fire.wpoint2[0]+8,_fire.wpoint2[1]+8);
			firecanvas.drawBitmap(anymorphing.nail1,null,rec,paint);
			setContour(_fire.seq);
		}
		else if(_fire.Type==0){
    		firecanvas.drawPaint(paint_clear);
    		anymorphing.anymorphingdata.lineObj.clearfirebmp();
		}
	}	
	invalidate();
 }
  
  
  public void clear(){	  
	  anymorphing.anymorphingdata.num_wpoint=0;
	  checkfile();
	  file.add(new FireType(null,0,0));
	  firewalldata.startind=file.size()-1;
	  anymorphing.mystackele.release(8);
	  firecanvas.drawPaint(paint_clear);
	  firewalldata.wpoint1=null;
	  firewalldata.wpoint2=null;
	  invalidate();
  }
  
  
  public void checkfile(){
	  for(int i=file.size()-1;i>=firewalldata.endind;i--)
		  file.remove(i);
  }
  
  public void setContour(long seq){
	  synchronized(AnyMorphing.class){
	  setContour0(anymorphing.anymorphingdata.lineObj.nativeObj,this.nativeObj,seq);
	  }
  }
  
  
  public static native long FireWall0(Bitmap bmp);
  public static native void setContour0(long lineobjnativeObj,long nativeObj,long seq);
  
}
