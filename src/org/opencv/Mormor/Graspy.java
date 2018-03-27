package org.opencv.Mormor;

import java.util.Arrays;

import android.annotation.SuppressLint;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.PorterDuffXfermode;
import android.graphics.Rect;
import android.graphics.PorterDuff.Mode;


public class Graspy
{
	
public class Graspy_Thread extends Thread{
	public void run()
	  {
			while(_run){
              if(graspythreaddata.sig==3){
              	if(src_Pos!=null)
              	canvas.drawCircle(src_Pos[0],src_Pos[1],3,paint_clear); 
              	if(ModifyFpoint){
              		Rect rec;
              		if(anymorphing.anymorphingdata.fpoint1!=null){
              		rec=new Rect(anymorphing.anymorphingdata.fpoint1[0]-8,anymorphing.anymorphingdata.fpoint1[1]-8,anymorphing.anymorphingdata.fpoint1[0]+8,anymorphing.anymorphingdata.fpoint1[1]+8);
             		    canvas.drawBitmap(anymorphing.nail,null,rec,anymorphing.paint);
              		}
              		if(anymorphing.anymorphingdata.fpoint2!=null){
             		    rec=new Rect(anymorphing.anymorphingdata.fpoint2[0]-8,anymorphing.anymorphingdata.fpoint2[1]-8,anymorphing.anymorphingdata.fpoint2[0]+8,anymorphing.anymorphingdata.fpoint2[1]+8);
          		    canvas.drawBitmap(anymorphing.nail,null,rec,anymorphing.paint);
              		}
          		    ModifyFpoint=false;
              	}
              	if(graspythreaddata.dst_Pos!=null){
              	canvas.drawCircle(graspythreaddata.dst_Pos[0],graspythreaddata.dst_Pos[1],3,paint2);
              	src_Pos=Arrays.copyOf(graspythreaddata.dst_Pos,2);
              	}
              	try {
              		synchronized(this){
						this.wait(500);
						}
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
              	if(graspythreaddata.sig==3)
                  graspythreaddata.sig=4;
              }
              else if(graspythreaddata.sig==4){
              	if(src_Pos!=null)
              	canvas.drawCircle(src_Pos[0],src_Pos[1],3,paint_clear); 
              	if(ModifyFpoint){
              		Rect rec;
              		if(anymorphing.anymorphingdata.fpoint1!=null){
              		rec=new Rect(anymorphing.anymorphingdata.fpoint1[0]-8,anymorphing.anymorphingdata.fpoint1[1]-8,anymorphing.anymorphingdata.fpoint1[0]+8,anymorphing.anymorphingdata.fpoint1[1]+8);
             		    canvas.drawBitmap(anymorphing.nail,null,rec,anymorphing.paint);
              		}
              		if(anymorphing.anymorphingdata.fpoint2!=null){
             		    rec=new Rect(anymorphing.anymorphingdata.fpoint2[0]-8,anymorphing.anymorphingdata.fpoint2[1]-8,anymorphing.anymorphingdata.fpoint2[0]+8,anymorphing.anymorphingdata.fpoint2[1]+8);
          		    canvas.drawBitmap(anymorphing.nail,null,rec,anymorphing.paint);
              		}
          		    ModifyFpoint=false;
              	}
              	if(graspythreaddata.dst_Pos!=null){
              	canvas.drawCircle(graspythreaddata.dst_Pos[0],graspythreaddata.dst_Pos[1],3,paint1);
              	src_Pos=Arrays.copyOf(graspythreaddata.dst_Pos,2);
              	}
              	try {
              		synchronized(this){
						this.wait(500);
              		}
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
              	if(graspythreaddata.sig==4)
              	graspythreaddata.sig=3;
              }               
              anymorphing.sigView.postInvalidate();
              
			}
	  }
	
};
public AnyMorphing anymorphing;
public Graspy_Thread graspythread;

public Paint paint1;
public Paint paint2;
public Paint paint_clear;
public Canvas canvas;
public int[] src_Pos;
public boolean _run;
public boolean ModifyFpoint;
public Graspy_Thread_Data graspythreaddata;
public class Graspy_Thread_Data implements Cloneable{
	
	public int sig=0;
	public int[] dst_Pos;		
	  public Graspy_Thread_Data clone() throws CloneNotSupportedException{
			return (Graspy_Thread_Data) super.clone();
}
}

public Graspy(AnyMorphing anymorphing){
	this.anymorphing=anymorphing;
	graspythreaddata=new Graspy_Thread_Data();
    paint1=new Paint();
    paint1.setColor(Color.GREEN);
    paint2=new Paint();
    paint2.setColor(Color.WHITE);
    paint_clear=new Paint();
    paint_clear.setXfermode(new PorterDuffXfermode(Mode.CLEAR)); 
}


@SuppressLint("NewApi")
public void setPos(int[] Pos){
	graspythreaddata.dst_Pos=Arrays.copyOf(Pos, 2);		
}


public void setSig(int n){
	
	if(n==3||n==4){
		if((graspythreaddata.sig==3||graspythreaddata.sig==4)&&_run){
			this.graspythreaddata.sig=n;
			_run=true;
		}
		else{
			this.graspythreaddata.sig=n;
			_run=true;
			graspythread=new Graspy_Thread();
			graspythread.start();
		}
		
	}
	else{
		_run=false;		
		if(graspythreaddata.sig==3||graspythreaddata.sig==4){			
			if(Graspy_Thread.interrupted())
				this.notify();				
		}
            if(n==0){    
            	if(src_Pos!=null)
            	canvas.drawCircle(src_Pos[0],src_Pos[1],3,paint_clear); 
            	src_Pos=null;
            	graspythreaddata.dst_Pos=null;

            }
            else if(n==1){
            	if(src_Pos!=null)
            	canvas.drawCircle(src_Pos[0],src_Pos[1],3,paint_clear); 
            	if(ModifyFpoint){
            		Rect rec;
            		if(anymorphing.anymorphingdata.fpoint1!=null){
            		rec=new Rect(anymorphing.anymorphingdata.fpoint1[0]-8,anymorphing.anymorphingdata.fpoint1[1]-8,anymorphing.anymorphingdata.fpoint1[0]+8,anymorphing.anymorphingdata.fpoint1[1]+8);
           		    canvas.drawBitmap(anymorphing.nail,null,rec,anymorphing.paint);
            		}
            		if(anymorphing.anymorphingdata.fpoint2!=null){
           		    rec=new Rect(anymorphing.anymorphingdata.fpoint2[0]-8,anymorphing.anymorphingdata.fpoint2[1]-8,anymorphing.anymorphingdata.fpoint2[0]+8,anymorphing.anymorphingdata.fpoint2[1]+8);
        		    canvas.drawBitmap(anymorphing.nail,null,rec,anymorphing.paint);
            		}
        		    ModifyFpoint=false;
            	}           		               	
            	canvas.drawCircle(graspythreaddata.dst_Pos[0],graspythreaddata.dst_Pos[1],3,paint1); 
            	src_Pos=Arrays.copyOf(graspythreaddata.dst_Pos,2);

            }
            else if(n==2){
            	if(src_Pos!=null)
            	canvas.drawCircle(src_Pos[0],src_Pos[1],3,paint_clear); 
            	if(ModifyFpoint){
            		Rect rec;
            		if(anymorphing.anymorphingdata.fpoint1!=null){
            		rec=new Rect(anymorphing.anymorphingdata.fpoint1[0]-8,anymorphing.anymorphingdata.fpoint1[1]-8,anymorphing.anymorphingdata.fpoint1[0]+8,anymorphing.anymorphingdata.fpoint1[1]+8);
           		    canvas.drawBitmap(anymorphing.nail,null,rec,anymorphing.paint);
            		}
            		if(anymorphing.anymorphingdata.fpoint2!=null){
           		    rec=new Rect(anymorphing.anymorphingdata.fpoint2[0]-8,anymorphing.anymorphingdata.fpoint2[1]-8,anymorphing.anymorphingdata.fpoint2[0]+8,anymorphing.anymorphingdata.fpoint2[1]+8);
        		    canvas.drawBitmap(anymorphing.nail,null,rec,anymorphing.paint);
            		}
        		    ModifyFpoint=false;
            	}
            	canvas.drawCircle(graspythreaddata.dst_Pos[0],graspythreaddata.dst_Pos[1],3,paint2);
            	src_Pos=Arrays.copyOf(graspythreaddata.dst_Pos,2);
            	
            }
            this.graspythreaddata.sig=n;
	}
			

}


public void clear(){
	if(src_Pos!=null)
	canvas.drawCircle(src_Pos[0],src_Pos[1],3,paint_clear);
}

	
}
