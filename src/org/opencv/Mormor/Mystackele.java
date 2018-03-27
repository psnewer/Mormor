

package org.opencv.Mormor;

import java.util.Arrays;
import com.morphing.mormor.PathType;
import com.morphing.morobj.Linelabel;
import com.morphing.morobj.Morphing;

import android.annotation.SuppressLint;
import android.graphics.Rect;

public class Mystackele {
	
	        public int[] monitor=new int[14];

			public AnyMorphing anymorphing_origin;
	
            public AnyMorphing.AnyMorphingData anymorphingdata;
            
            public boolean Clone_DrawingPanel=false;
            public boolean Clone_FireWall=false;
            public boolean Clone_Edge=false;
            public boolean pre_Clone_Edge;
            public boolean Clone_fpoint1;
            public boolean Clone_fpoint2;
            public boolean Clone_lineObj;
            public boolean Clone_mor;
            public boolean Clone_graspy;
            public boolean Lineobj_Indeed;
            public boolean Mor_Indeed;
            public boolean NEED_REFRESH;
            public boolean Clone_Line;
            
            public boolean pre_Clone_fpoint1;
            public boolean pre_Clone_fpoint2;
            public boolean pre_Clone_lineObj;
            public boolean pre_Clone_mor;
            public boolean pre_Clone_graspy;
            public boolean pre_Clone_DrawingPanel=false;
            public boolean pre_Clone_FireWall=false;
            public boolean pre_NEED_REFRESH;
            public boolean pre_Clone_Line;
                     
            
            public Mystackele(AnyMorphing anymorphing){
            	this.anymorphing_origin=anymorphing;
            	Arrays.fill(monitor,1);
            }
            
            @SuppressLint("NewApi")
			public void release(int i){

            		switch (i){
            		case 1:
            			if(monitor[1]==1){  
            			monitor[1]=0;
            			Mystackele preele=(Mystackele) anymorphing_origin.mystack.get(anymorphing_origin.mystack.current_ind);
            			preele.pre_Clone_Edge=true;
            			Clone_Edge=true;
            			}
            			break;
            		case 2:
            			if(monitor[2]==1){
            				if(anymorphing_origin.base_point!=null)
            			       anymorphing_origin.base_point=Arrays.copyOf(anymorphing_origin.base_point,2);
            			monitor[2]=0;
            			}
            			break;
            		case 3:
            			if(monitor[3]==1){
            			      anymorphing_origin.anymorphingdata.lineObj=new Linelabel(anymorphing_origin.anymorphingdata.lineObj);
            			anymorphing_origin.anymorphingdata.mor.setLineobj(anymorphing_origin.anymorphingdata.lineObj);
            			anymorphing_origin.mytimer.Line1.setLineobj(anymorphing_origin.anymorphingdata.lineObj);
            			Mystackele preele=(Mystackele) anymorphing_origin.mystack.get(anymorphing_origin.mystack.current_ind);
            			preele.pre_Clone_lineObj=true;
            			Clone_lineObj=true;
            			Lineobj_Indeed=true;
            			monitor[3]=0;
            			}
            			break;
            		case 4:
            			if(monitor[4]==1){
            			      anymorphing_origin.anymorphingdata.mor=new Morphing(anymorphing_origin.anymorphingdata.mor);
                  			  Mystackele preele=(Mystackele) anymorphing_origin.mystack.get(anymorphing_origin.mystack.current_ind);
                			  preele.pre_Clone_mor=true;
            			      Clone_mor=true;
            			      Mor_Indeed=true;
            			      monitor[4]=0;
            			}
            			break;
            		case 5:
            			if(monitor[5]==1){
             			    monitor[5]=0;
            			}
            			break;
            		case 6:
            			if(monitor[6]==1){
                			Mystackele preele=(Mystackele) anymorphing_origin.mystack.get(anymorphing_origin.mystack.current_ind);
                			preele.pre_Clone_graspy=true;
            				Clone_graspy=true;
            				monitor[6]=0;
            			}
            			break;
            		case 7:
            			if(monitor[7]==1){
            				anymorphing_origin.lineView.drawingpaneldata.pathend=anymorphing_origin.lineView.file.size();
            				Mystackele preele=(Mystackele) anymorphing_origin.mystack.get(anymorphing_origin.mystack.current_ind);
                			preele.pre_Clone_DrawingPanel=true;
            				Clone_DrawingPanel=true;
                			preele.pre_NEED_REFRESH=true;
                			NEED_REFRESH=true;
            				monitor[7]=0;
            			}
            			break;
            		case 8:
            			if(monitor[8]==1){
            				anymorphing_origin.fireView.firewalldata.endind=anymorphing_origin.fireView.file.size();
            				Mystackele preele=(Mystackele) anymorphing_origin.mystack.get(anymorphing_origin.mystack.current_ind);
                			preele.pre_Clone_FireWall=true;
            				Clone_FireWall=true;
            				monitor[8]=0;
            			}
            			break;
            		case 9:
            			if(monitor[9]==1){
            				Mystackele preele=(Mystackele) anymorphing_origin.mystack.get(anymorphing_origin.mystack.current_ind);
                			preele.pre_Clone_Line=true;
                			Clone_Line=true;
            			    monitor[9]=0;
            			}
            			break;
            		case 10:
            			if(monitor[10]==1){
            			    monitor[10]=0;
            			}
            			break;
            		case 11:
            			if(monitor[11]==1){
            				if(anymorphing_origin.anymorphingdata.fpoint1!=null)
            			     anymorphing_origin.anymorphingdata.fpoint1=Arrays.copyOf(anymorphing_origin.anymorphingdata.fpoint1,2);
            				Mystackele preele=(Mystackele) anymorphing_origin.mystack.get(anymorphing_origin.mystack.current_ind);
                			preele.pre_Clone_fpoint1=true;
                			this.Clone_fpoint1=true;
            			    monitor[11]=0;
            			}
            			break;
            		case 12:
            			if(monitor[12]==1){
            				if(anymorphing_origin.anymorphingdata.fpoint2!=null)
            			       anymorphing_origin.anymorphingdata.fpoint2=Arrays.copyOf(anymorphing_origin.anymorphingdata.fpoint2,2);
            				Mystackele preele=(Mystackele) anymorphing_origin.mystack.get(anymorphing_origin.mystack.current_ind);
                			preele.pre_Clone_fpoint2=true;
                			this.Clone_fpoint2=true;
            			    monitor[12]=0;
            			}
            			break;
            		case 13:
            			if(monitor[13]==1){

            			    monitor[13]=0;
            			}
            			break;
            		}            		

            }
            
            public void setClone() throws CloneNotSupportedException{
            		           	
            	if(Clone_lineObj){
            		anymorphing_origin.anymorphingdata.lineObj.setCopy();
            	}
            	if(Clone_graspy){
            		anymorphing_origin.anymorphingdata.graspythreaddata=anymorphing_origin.graspy.graspythreaddata.clone();
            		
            	}
            	if(Clone_DrawingPanel){ 
            		anymorphing_origin.anymorphingdata.drawingpaneldata=anymorphing_origin.lineView.drawingpaneldata.clone();
            		
            	}
            	if(Clone_FireWall){           		  
            		anymorphing_origin.anymorphingdata.firewalldata=anymorphing_origin.fireView.firewalldata.clone();
            		
            	}
            	this.anymorphingdata=anymorphing_origin.anymorphingdata.clone();

            }
            
           
            @SuppressLint("NewApi")
			public void restore(int n) throws CloneNotSupportedException{
            	anymorphing_origin.anymorphingdata=this.anymorphingdata.clone();
            	boolean sigViewrefresh=false;
            	boolean lineViewrefresh=false;
            	
            	boolean MODIFYLINE=false;
            if((n==1&&pre_Clone_fpoint1)||(n==2&&Clone_fpoint1)){
            	if(anymorphing_origin.anymorphingdata.num_fpoint==1&&anymorphing_origin.anymorphingdata.fpoint1!=null){
            		Rect rec=new Rect(anymorphing_origin.anymorphingdata.fpoint1[0]-8,anymorphing_origin.anymorphingdata.fpoint1[1]-8,anymorphing_origin.anymorphingdata.fpoint1[0]+8,anymorphing_origin.anymorphingdata.fpoint1[1]+8);
            		anymorphing_origin.sigcanvas.drawBitmap(anymorphing_origin.nail,null,rec,anymorphing_origin.paint);
            		sigViewrefresh=true;
            	}
            	else if(anymorphing_origin.anymorphingdata.num_fpoint==0&&((anymorphing_origin.anymorphingdata.fpoint1==null&&n==1)||(Clone_fpoint2))){
            		Mystackele nextele=null;
            		if(n==1)
            		nextele=(Mystackele) anymorphing_origin.mystack.get(anymorphing_origin.mystack.current_ind+1);
            		else if(n==2)
            			nextele=(Mystackele) anymorphing_origin.mystack.get(anymorphing_origin.mystack.current_ind-1);
            		if(nextele.anymorphingdata.fpoint1!=null){
            		    Rect rec=new Rect(nextele.anymorphingdata.fpoint1[0]-8,nextele.anymorphingdata.fpoint1[1]-8,nextele.anymorphingdata.fpoint1[0]+8,nextele.anymorphingdata.fpoint1[1]+8);
            		    anymorphing_origin.sigcanvas.drawBitmap(anymorphing_origin.nail,null,rec,anymorphing_origin.paint_clear);
            		    sigViewrefresh=true;
            		}
            	}           	
            }
            if((n==1&&pre_Clone_fpoint2)||(n==2&&Clone_fpoint2)){
            	if(anymorphing_origin.anymorphingdata.num_fpoint==2&&anymorphing_origin.anymorphingdata.fpoint2!=null&&anymorphing_origin.anymorphingdata.fpoint1!=null){
            		Rect rec=new Rect(anymorphing_origin.anymorphingdata.fpoint2[0]-8,anymorphing_origin.anymorphingdata.fpoint2[1]-8,anymorphing_origin.anymorphingdata.fpoint2[0]+8,anymorphing_origin.anymorphingdata.fpoint2[1]+8);
            		anymorphing_origin.sigcanvas.drawBitmap(anymorphing_origin.nail,null,rec,anymorphing_origin.paint);
            		rec=new Rect(anymorphing_origin.anymorphingdata.fpoint1[0]-8,anymorphing_origin.anymorphingdata.fpoint1[1]-8,anymorphing_origin.anymorphingdata.fpoint1[0]+8,anymorphing_origin.anymorphingdata.fpoint1[1]+8);
            		anymorphing_origin.sigcanvas.drawBitmap(anymorphing_origin.nail,null,rec,anymorphing_origin.paint);
            		sigViewrefresh=true;
            	}
            	else if((anymorphing_origin.anymorphingdata.num_fpoint==1&&anymorphing_origin.anymorphingdata.fpoint2==null)||(anymorphing_origin.anymorphingdata.num_fpoint==0&&Clone_fpoint1)){
            		Mystackele nextele = null;
            		if(n==1)
            	    nextele=(Mystackele) anymorphing_origin.mystack.get(anymorphing_origin.mystack.current_ind+1);
            		else if(n==2)
            			nextele=(Mystackele) anymorphing_origin.mystack.get(anymorphing_origin.mystack.current_ind-1);
            		if(nextele.anymorphingdata.fpoint2!=null){
            		Rect rec=new Rect(nextele.anymorphingdata.fpoint2[0]-8,nextele.anymorphingdata.fpoint2[1]-8,nextele.anymorphingdata.fpoint2[0]+8,nextele.anymorphingdata.fpoint2[1]+8);
            		anymorphing_origin.sigcanvas.drawBitmap(anymorphing_origin.nail,null,rec,anymorphing_origin.paint_clear);
            		sigViewrefresh=true;
            		}
            }            	
            }
            
        	if((n==1&&pre_Clone_lineObj)||(n==2&&Clone_lineObj)){
        		anymorphing_origin.anymorphingdata.lineObj.refreshPointer();
        		anymorphing_origin.anymorphingdata.mor.setLineobj(anymorphing_origin.anymorphingdata.lineObj);
    			anymorphing_origin.mytimer.Line1.setLineobj(anymorphing_origin.anymorphingdata.lineObj);
    			anymorphing_origin.localcanvas.drawPoint(-1, -1, anymorphing_origin.paint_clear);
        	    anymorphing_origin.localImageView.invalidate();
        	}
        	if((n==1&&pre_Clone_mor)||(n==2&&Clone_mor)){
        		anymorphing_origin.anymorphingdata.mor.initParam(anymorphing_origin.sig,anymorphing_origin.synratio);
        	}
        	if((n==1&&pre_Clone_graspy)||(n==2&&Clone_graspy)){
        		anymorphing_origin.graspy.graspythreaddata=anymorphingdata.graspythreaddata.clone();
        		anymorphing_origin.graspy.clear();
        		anymorphing_origin.graspy.setSig(anymorphing_origin.graspy.graspythreaddata.sig);
        		sigViewrefresh=true;
        	}
        	if((n==1&&pre_Clone_DrawingPanel)||(n==2&&Clone_DrawingPanel)){
        		
        		anymorphing_origin.lineView.drawingpaneldata=anymorphingdata.drawingpaneldata.clone();       	
        		anymorphing_origin.lineView.mcanvas.drawPaint(anymorphing_origin.lineView.paint_clear);
        		anymorphing_origin.anymorphingdata.lineObj.setContourMode1();	
        		for (int i=anymorphing_origin.lineView.drawingpaneldata.pathstart;i<anymorphing_origin.lineView.drawingpaneldata.pathend;i++){
        			PathType _path=anymorphing_origin.lineView.file.get(i);
        			if(_path.Type==1){        				
        			    anymorphing_origin.lineView.mcanvas.drawPath(_path.path, anymorphing_origin.lineView.paint_clear); 
        			    if(_path.drawclear)
        			    anymorphing_origin.lineView.linecanvas.drawPath(_path.path, anymorphing_origin.lineView.paint_clear); 	
        			}
        			else if(_path.Type==2){
        				anymorphing_origin.lineView.mcanvas.drawPath(_path.path, anymorphing_origin.lineView.paint); 
            			anymorphing_origin.lineView.linecanvas.drawPath(_path.path, anymorphing_origin.lineView.paint);
        			}
        			else if(_path.Type==0&&!anymorphing_origin.anymorphingdata.EDGE_MODE){
        				anymorphing_origin.lineView.mcanvas.drawPaint(anymorphing_origin.lineView.paint_clear);
        				anymorphing_origin.lineView.linecanvas.drawPaint(anymorphing_origin.lineView.paint_clear);
        			}
        		}
        		
        		anymorphing_origin.anymorphingdata.lineObj.concateLineview(anymorphing_origin.anymorphingdata.EDGE_MODE);       		        		 
        		if(anymorphing_origin.anymorphingdata.num_rpoint>0)
        			MODIFYLINE=true;
        		lineViewrefresh=true;
        	}
        	
        	if((n==1&&pre_NEED_REFRESH)||(n==2&&NEED_REFRESH)){
         		anymorphing_origin.lineView.setRunning(false);
        	}
        	
        	if((n==1&&pre_Clone_FireWall)||(n==2&&Clone_FireWall)){
        		anymorphing_origin.fireView.firewalldata=anymorphingdata.firewalldata.clone();
                anymorphing_origin.fireView.reDraw();
        	}
        	
            if((n==1&&pre_Clone_Edge)||(n==2&&Clone_Edge)){
            	if(anymorphing_origin.anymorphingdata.EDGE_MODE){
            	    anymorphing_origin.anymorphingdata.lineObj.setContourMode(anymorphing_origin.anymorphingdata.mor.nativeObj,anymorphing_origin.anymorphingdata.num_rpoint);
            	    anymorphing_origin.colorPick1.setSelected(true);
            	}
            	else{
            	    anymorphing_origin.anymorphingdata.lineObj.setFreeMode(anymorphing_origin.anymorphingdata.mor.nativeObj,anymorphing_origin.anymorphingdata.num_rpoint);	
            	    anymorphing_origin.colorPick1.setSelected(false);
            	}
            	lineViewrefresh=true;
            }
                    	
            
            if((n==1&&pre_Clone_Line)||(n==2&&Clone_Line)||MODIFYLINE){
            	
            	if(n==1){
            		Mystackele nextele=(Mystackele) anymorphing_origin.mystack.get(anymorphing_origin.mystack.current_ind+1);
            		if(anymorphing_origin.anymorphingdata.num_rpoint==nextele.anymorphingdata.num_rpoint)
            		    nextele.anymorphingdata.mor.clearLine(nextele.anymorphingdata.num_rpoint);
            		else
            			anymorphing_origin.anymorphingdata.lineObj.setTempMode(anymorphing_origin.anymorphingdata.EDGE_MODE);
            	}
            	else if(n==2){
            		Mystackele preele=(Mystackele) anymorphing_origin.mystack.get(anymorphing_origin.mystack.current_ind-1);
            		if(anymorphing_origin.anymorphingdata.num_rpoint==preele.anymorphingdata.num_rpoint)
            		    preele.anymorphingdata.mor.clearLine(preele.anymorphingdata.num_rpoint);
            		else
            			anymorphing_origin.anymorphingdata.lineObj.setTempMode(anymorphing_origin.anymorphingdata.EDGE_MODE);
            	}           	    
            	    anymorphing_origin.anymorphingdata.mor.setLine(anymorphing_origin.anymorphingdata.num_rpoint);             	    
            	lineViewrefresh=true;
            }

        	
            if(sigViewrefresh){
            	anymorphing_origin.sigView.invalidate();
            }
            if(lineViewrefresh){
            	anymorphing_origin.lineView.linecanvas.drawPoint(-1, -1, anymorphing_origin.lineView.paint_clear);
            	anymorphing_origin.lineView.invalidate();
            }
          }
   

}
