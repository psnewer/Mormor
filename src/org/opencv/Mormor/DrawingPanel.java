package org.opencv.Mormor;

import java.util.Vector;

import android.annotation.SuppressLint;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.PorterDuffXfermode;
import android.graphics.Bitmap.Config;
import android.graphics.PorterDuff.Mode;
import android.graphics.Path;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.View;
import android.widget.ImageView;
import org.opencv.Mormor.AnyMorphing;

import com.morphing.mormor.PathType;

public class DrawingPanel extends ImageView
 
{


	public Vector<PathType> file;
	
	public Paint paint;
    public Paint paint_clear;
    public Canvas mcanvas;
    public Canvas linecanvas;
    public Bitmap bmp;
    public Bitmap linepic;

    public AnyMorphing anymorphing;
	public boolean NeedClone;
	private DrawThread drawthread;
    
    float[] delta;
    private float mX,mY;
    float dx,dy,TOUCH_TORLERANCE;
    Path path ;
    public boolean drawclear;
    
    public DrawingPanelData drawingpaneldata=new DrawingPanelData();
    
    public DrawingPanel(Context context, AttributeSet attrs) {
		super(context, attrs);
		// TODO Auto-generated constructor stub
	    paint=new Paint();
	    paint.setColor(Color.RED);
	    paint.setDither(true);
	    paint.setStyle(Paint.Style.STROKE);
	    paint.setStrokeJoin(Paint.Join.ROUND);   
        paint.setStrokeCap(Paint.Cap.ROUND);
          
        path=new Path();

	    paint_clear=new Paint();
	    paint_clear.setXfermode(new PorterDuffXfermode(Mode.CLEAR)); 
	    paint_clear.setDither(true);
	    paint_clear.setStyle(Paint.Style.STROKE);
	    paint_clear.setStrokeJoin(Paint.Join.ROUND);   
        paint_clear.setStrokeCap(Paint.Cap.ROUND);	
        TOUCH_TORLERANCE=5;
        delta=new float[2];
	    
	}

    
    public class DrawingPanelData implements Cloneable{     
    	public int pathend=0;
    	public int pathstart=0;
    	
		  public DrawingPanelData clone() throws CloneNotSupportedException{
				return (DrawingPanelData) super.clone();
	}
    }
    
    
    public class DrawThread extends Thread{
            @Override  
        	public void run()
      	  {
            	//����fpoint
            	if(anymorphing.anymorphingdata.num_fpoint==1){
            		if(anymorphing.anymorphingdata.fpoint1!=null){
            			int color=linepic.getPixel(anymorphing.anymorphingdata.fpoint1[0], anymorphing.anymorphingdata.fpoint1[1]);
            			if((color&0xff000000)==0){
            				anymorphing.anymorphingdata.lineObj.setFpoint(anymorphing.anymorphingdata.fpoint1);
            			}
            		}          			
            	}
            	else if(anymorphing.anymorphingdata.num_fpoint==2){
            		if(anymorphing.anymorphingdata.fpoint1!=null){
            			int color=linepic.getPixel(anymorphing.anymorphingdata.fpoint1[0], anymorphing.anymorphingdata.fpoint1[1]);
            			if((color&0xff000000)==0){
            				anymorphing.anymorphingdata.lineObj.setFpoint(anymorphing.anymorphingdata.fpoint1);
            			}
            		}
            		if(anymorphing.anymorphingdata.fpoint2!=null){
            			int color=linepic.getPixel(anymorphing.anymorphingdata.fpoint2[0], anymorphing.anymorphingdata.fpoint2[1]);
            			if((color&0xff000000)==0){
            				anymorphing.anymorphingdata.lineObj.setFpoint(anymorphing.anymorphingdata.fpoint2);
            			}
            		}
            			
            	}
      				if(NeedClone){
      		        anymorphing.anymorphingdata.lineObj.addEdge(anymorphing.anymorphingdata.mor.nativeObj,anymorphing.anymorphingdata.num_rpoint,anymorphing.anymorphingdata.EDGE_MODE);				

      				//压栈
      				anymorphing.stateSave();
      				}
      				else{
      					anymorphing.anymorphingdata.lineObj.addEdge_1(anymorphing.anymorphingdata.mor.nativeObj,anymorphing.anymorphingdata.num_rpoint,anymorphing.anymorphingdata.EDGE_MODE);
      				}
      	  }
    	
    }


@SuppressLint("NewApi")
public void init(AnyMorphing anymorphing){
       this.anymorphing=anymorphing;
	   bmp=Bitmap.createBitmap(anymorphing.picw, anymorphing.pich, Config.ALPHA_8); 
	   linepic=Bitmap.createBitmap(anymorphing.picw,anymorphing.pich,Config.ARGB_8888);   
	   linecanvas=new Canvas(linepic);
	   mcanvas = new Canvas(bmp);  
	   paint.setStrokeWidth(1); 
	   paint_clear.setStrokeWidth(anymorphing.size);
	   file=new Vector<PathType>();
	   drawclear=false;
  }
  
  
  public void setListener(int i){
	  if(i==1){
		  this.setOnTouchListener(T1);
	  }
	  else if(i==2){
		  this.setOnTouchListener(T2);
	  }
  }
  
  
  OnTouchListener T1=new OnTouchListener(){
	  public boolean onTouch(View v, MotionEvent event) {
		  synchronized(AnyMorphing.class){
	      float[] coords={event.getX(),event.getY()};
	  	  anymorphing.mat_inver.mapPoints(coords,coords);
	  	  float x = coords[0]; 
		  float y = coords[1];
		  
	      switch (event.getAction()) 
	      {	          
	          case MotionEvent.ACTION_DOWN:
	        	   if(anymorphing.IS_SHIFTED){
	        	    	  delta[0]=anymorphing.base_point[0]-x;
	        	      	  delta[1]=anymorphing.base_point[1]-y;
	        	      }
	        	      else{
	        	    	  delta[0]=0;
	        	    	  delta[1]=0;
	        	      }
	        	  x=x+delta[0];
	        	  y=y+delta[1];
	        	  path=new Path();   
	              path.moveTo(x, y);   
	              mX = x;   
	              mY = y;          
	          break;
	          case MotionEvent.ACTION_MOVE:
	        	  x=x+delta[0];
	        	  y=y+delta[1];  
	        	  dx=Math.abs(x-mX);
	        	  dy=Math.abs(y-mY);
	        	  if(dx>=TOUCH_TORLERANCE||dy>=TOUCH_TORLERANCE){
	              path.quadTo(mX, mY, (x + mX)/2, (y + mY)/2);   
	              mX = x;   
	              mY = y;
	              linecanvas.drawPath(path, paint_clear);
	              invalidate(); 
	              drawclear=true;
	        	  }
	              break;
	          case MotionEvent.ACTION_UP:
	        	  if(drawclear){
		          x=x+delta[0];
		          y=y+delta[1];  
	        	  path.lineTo(x, y);   	              
	              linecanvas.drawPath(path, paint_clear);
	              invalidate();	                            
	              mcanvas.drawPath(path, paint_clear);
	              setRunning(true);
	              checkfile();
	              file.add(new PathType(path,1,anymorphing.anymorphingdata.EDGE_MODE));
	              anymorphing.mystackele.release(7);
	              drawclear=false;
	        	  }
	              break;    	         	              
	              default:
	            	  break;
	      }
	         return true;
		  }
	  }
	  };

	  OnTouchListener T2=new OnTouchListener(){
		  public boolean onTouch(View v, MotionEvent event) {
			  synchronized(AnyMorphing.class){
		                  float[] coords={event.getX(),event.getY()};
		                  anymorphing.mat_inver.mapPoints(coords,coords);
		                  float x = coords[0]; 
		                  float y = coords[1];
		                  
      switch (event.getAction()) 
      {
          case MotionEvent.ACTION_DOWN:
        	   if(anymorphing.IS_SHIFTED){
        	    	  delta[0]=anymorphing.base_point[0]-x;
        	      	  delta[1]=anymorphing.base_point[1]-y;
        	      }
        	      else{
        	    	  delta[0]=0;
        	    	  delta[1]=0;
        	      }
        	  x=x+delta[0];
        	  y=y+delta[1];
        	  path=new Path();   
              path.moveTo(x, y);   
              mX = x;   
              mY = y;          
          break;
          case MotionEvent.ACTION_MOVE:
        	  x=x+delta[0];
        	  y=y+delta[1];  
        	  dx=Math.abs(x-mX);
        	  dy=Math.abs(y-mY);
        	  if(dx>=TOUCH_TORLERANCE||dy>=TOUCH_TORLERANCE){
              path.quadTo(mX, mY, (x + mX)/2, (y + mY)/2);  
              mX = x;   
              mY = y; 
              linecanvas.drawPath(path, paint);
              invalidate();
              drawclear=true;
        	  }
              break;  
          case MotionEvent.ACTION_UP:
        	  if(drawclear){
	          x=x+delta[0];
	          y=y+delta[1];  
        	  drawclear=false;
        	  path.lineTo(x, y);   
              linecanvas.drawPath(path, paint);
              invalidate();              
              mcanvas.drawPath(path, paint); 
              setRunning(true);
              checkfile();
              file.add(new PathType(path,2,true));
              anymorphing.mystackele.release(7);
        	  }
              break;    
              default:
            	  break;              
      }
      return true;
			  }
  }
	  };
	  
	  
	  public void checkfile(){
		  for(int i=file.size()-1;i>=drawingpaneldata.pathend;i--)
			  file.remove(i);
	  }
	  
	  
	  
	  public void clear(){
		  if(anymorphing.anymorphingdata.num_rpoint>0){
	    	anymorphing.mystackele.release(9);
	    	linecanvas.drawPaint(paint_clear);
		  }
	    	if(anymorphing.anymorphingdata.EDGE_MODE){
	    	anymorphing.mystackele.release(1);
	    	anymorphing.anymorphingdata.EDGE_MODE=false;
	    	anymorphing.colorPick1.setSelected(false);
	    	}
	 	    checkfile();
	 	    file.add(new PathType(null,0,false));
	 	    drawingpaneldata.pathstart=file.size()-1;
	 	    anymorphing.mystackele.release(7);
	 	    mcanvas.drawPaint(paint_clear);
	 	    invalidate();
	  }
	  
	  
		public void setRunning(boolean NeedClone)
		  {
			this.NeedClone=NeedClone;
	        drawthread = new DrawThread(); 
	        drawthread.start(); 
		  }

 
}

/* Location:           C:\dex2jar-0.0.7-SNAPSHOT\classes.dex.dex2jar.jar
 * Qualified Name:     com.toonfx.toonpaint.DrawingPanel
 * JD-Core Version:    0.6.2
 */