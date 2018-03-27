package org.opencv.Mormor;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.app.AlertDialog;
import android.app.AlertDialog.Builder;
import android.app.ProgressDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.Bitmap.Config;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Matrix;
import android.graphics.Paint;
import android.graphics.PorterDuff.Mode;
import android.graphics.PorterDuffXfermode;
import android.graphics.Rect;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.provider.MediaStore;
import android.view.Gravity;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnLongClickListener;
import android.view.View.OnTouchListener;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.ImageView.ScaleType;
import android.widget.LinearLayout;
import android.widget.Toast;


import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Arrays;
import org.opencv.android.OpenCVLoader;


import com.morphing.morobj.Morphing;
import com.morphing.mormor.BasicOperator;
import com.morphing.morobj.Linelabel;






@SuppressLint("NewApi")
public class AnyMorphing extends Activity implements OnTouchListener,OnClickListener, BasicSliderDialog.SliderApplyCallback,DataManager.DataCallback,BrushSizeDialog.BrushSizeChangeCallback,AboutDialog.AboutCallback,EdgeprefDialog.EdgeprefCallback
 
{
	public class AnyMorphingData implements Cloneable{
		  	  
		  public Morphing mor;
		  public Linelabel lineObj;
		  public Graspy.Graspy_Thread_Data graspythreaddata;
		  public DrawingPanel.DrawingPanelData drawingpaneldata;
		  public FireWall.FireWallData firewalldata;
		  
		  boolean COULD_GENERATE=false;
		  boolean EDGE_MODE=false;
		  boolean GENERATE_CLEAR=false;
		  boolean rpoint_clear=false;
		  boolean regionclear=false;
		  boolean moveclear=false;
		  		  
		  int num_fpoint=0;
		  int num_rpoint=0;
		  public int num_wpoint=0;
		  int[] fpoint1=null;
		  int[] fpoint2=null;
		  public int[] graspPoint1=null;
		  public int[] graspPoint2=null;

		  int contour_number=1;
		  
		  public AnyMorphingData clone() throws CloneNotSupportedException{
				return (AnyMorphingData) super.clone();
			}
	}
  public AnyMorphingData anymorphingdata;
  public static String lock="lock";
  DataManager datastore;
  MyTimer mytimer;
  String bmpfile;
  Graspy graspy;
  Canvas sigcanvas;
  Canvas localcanvas;
  public Bitmap bmpnew;	
  public Bitmap sigpic;
  public Bitmap nail;
  public Bitmap nail1;
  public Bitmap base;
  Context context;
  public int picw;
  public int pich;
  float sig;
  float synratio;
  int size;
  public float[] base_point;
  int[] rpoint;
  
  boolean edge_pref;
  public boolean IS_SHIFTED;

  ProgressDialog progressDialog;
  public ImageView localImageView;
  public ImageView sigView;
  public DrawingPanel lineView;
  FireWall fireView;
  ImageButton openLoadSave;
  LinearLayout loadSaveToolbox;
  ImageButton slidersEditBtn;
  LinearLayout basicSliders;
  ImageButton editBox;
  LinearLayout paintToolboxes;
  ImageButton share;
  ImageButton infoOpen;
  ImageButton savePhoto;
  ImageButton pickPhoto;
  ImageButton takePhoto;
  ImageButton colorPick1;
  ImageButton colorPick2;
  ImageButton colorPick3;
  ImageButton colorPick4;
  ImageButton colorPick5;
  ImageButton colorPick6;
  ImageButton colorPick7;
  ImageButton colorPick8;
  ImageButton redo;
  ImageButton undo;
  public BasicSliderDialog sliderDialog;
  public AboutDialog aboutDialog;
  public EdgeprefDialog edgeprefDialog;
  
  int boxvisible;
  public boolean getlineclear;
  public boolean windowchanged;

  int Findedge_range;
  
  Paint paint;
  Paint paint_clear;
  
  public Matrix mat;
  public Matrix mat_inver;
  
  public Mystack mystack;
  public Mystackele mystackele;
  
  
  public void onCreate(Bundle paramBundle)
  {
    super.onCreate(paramBundle);
    setContentView(R.layout.main); 
    anymorphingdata=new AnyMorphingData();
    base_point=new float[2];
	boxvisible=0;
    paint=new Paint();
    paint_clear=new Paint(); 
    paint_clear.setColor(Color.BLACK);
    paint_clear.setXfermode(new PorterDuffXfermode(Mode.CLEAR));
    mat=new Matrix();
    mat_inver=new Matrix();
	this.datastore = new DataManager(this, this);
    this.Findedge_range=20;      
    
    graspy=new Graspy(this);
       
    //闂佸憡甯楃粙鎴犵磽閹捐妫橀柛銉檮椤愯棄顭跨拋瑙勫    
    File file=new File(SDCARD_ROOT_PATH+SAVE_PATH_IN_SDCARD);
    if (!file.exists())
    	file.mkdirs();
      
    initUI();
    this.datastore.onStart();
    bmpfile=AnyMorphing.SDCARD_ROOT_PATH+AnyMorphing.SAVE_PATH_IN_SDCARD+AnyMorphing.IMAGE_CAPTURE_NAME; 
	load_init(bmpfile,0);	
	changeUI();
	reset_translate();
	
    this.sliderDialog=new BasicSliderDialog(this,this,this.sig,this.synratio);
    this.aboutDialog=new AboutDialog(this, this);	
    this.edgeprefDialog=new EdgeprefDialog(AnyMorphing.this, AnyMorphing.this);
	
	firstStateSave();
	
	  boolean FirstRun=datastore.prefs.getBoolean("firstrun", true);
	  if(FirstRun){		  
		  this.onJump();
	  }
  }

 
  
  
public void initUI(){
	  
	  localImageView=(ImageView)findViewById(R.id.picview);   
	  sigView=(ImageView) findViewById(R.id.sigView);
      lineView=(DrawingPanel) findViewById(R.id.lineView);
      fireView=(FireWall) findViewById(R.id.fireView);	  
	  openLoadSave=(ImageButton) findViewById(R.id.openLoadSave);
	  loadSaveToolbox=(LinearLayout) findViewById(R.id.loadsaveToolbox);
	  openLoadSave.setOnClickListener(this);
	  slidersEditBtn=(ImageButton) findViewById(R.id.slidersEditBtn);
	  basicSliders=(LinearLayout) findViewById(R.layout.basicsliders);
	  slidersEditBtn.setOnClickListener(this);
	  editBox=(ImageButton) findViewById(R.id.editBox);
	  paintToolboxes=(LinearLayout) findViewById(R.id.paintToolbox);
	  editBox.setOnClickListener(this);
	  slidersEditBtn.setOnClickListener(this);
	  share=(ImageButton) findViewById(R.id.share);
	  share.setOnClickListener(this);
	  infoOpen=(ImageButton) findViewById(R.id.infoOpen);
	  infoOpen.setOnClickListener(this);
	  
	  pickPhoto=(ImageButton) findViewById(R.id.pickPhoto);
	  pickPhoto.setOnClickListener(L1);
	  takePhoto=(ImageButton) findViewById(R.id.takePhoto);
	  takePhoto.setOnClickListener(L10);
	  savePhoto=(ImageButton) findViewById(R.id.savePhoto);
	  savePhoto.setOnClickListener(L11);
	  colorPick1=(ImageButton) findViewById(R.id.colorPick1);
	  colorPick1.setOnClickListener(L2);
	  colorPick2=(ImageButton) findViewById(R.id.colorPick2);
	  colorPick2.setOnClickListener(L6);
	  colorPick2.setOnLongClickListener(L15);
	  colorPick3=(ImageButton) findViewById(R.id.colorPick3);
	  colorPick3.setOnClickListener(L3);
	  colorPick4=(ImageButton) findViewById(R.id.colorPick4);
	  colorPick4.setOnClickListener(L5);
	  colorPick4.setOnLongClickListener(L18);
	  colorPick5=(ImageButton) findViewById(R.id.colorPick5);
	  colorPick5.setOnClickListener(L4);
	  colorPick6=(ImageButton) findViewById(R.id.colorPick6);
	  colorPick6.setOnClickListener(L7);
	  colorPick7=(ImageButton) findViewById(R.id.colorPick7);
	  colorPick7.setOnClickListener(L9);
	  colorPick8=(ImageButton) findViewById(R.id.colorPick8);
	  colorPick8.setOnClickListener(L12);
	  
	  redo=(ImageButton) findViewById(R.id.redo);
	  redo.setOnClickListener(L14);
	  undo=(ImageButton) findViewById(R.id.undo);
	  undo.setOnClickListener(L13);
	  
	  BitmapFactory.Options opts = new BitmapFactory.Options();
	  opts.inPurgeable=true;
	  nail=BitmapFactory.decodeResource(getResources(),
              R.drawable.nail,opts);
	  nail1=BitmapFactory.decodeResource(getResources(),
              R.drawable.nail1,opts);
	  base=BitmapFactory.decodeResource(getResources(),
              R.drawable.base,opts);
  }




  public void onWindowFocusChanged(boolean hasFocus) {
        super.onWindowFocusChanged(hasFocus);
        if(!windowchanged){
	    windowchanged=true;
	    setScaleType();
        width = localImageView.getWidth();  
        height = localImageView.getHeight(); 
        currentStatus=STATUS_INIT;
        refresh_translate(); 
      }
  }
  
  public void firstStateSave(){

	  mystackele.Clone_FireWall=true;
	  mystackele.Clone_DrawingPanel=true;
	  mystackele.Clone_graspy=true;
	  mystackele.Mor_Indeed=true;
	  mystackele.Lineobj_Indeed=true;
      stateSave();		
  }
  
  
  
  public void refresh_shift(){
	    		colorPick4.setSelected(false);
		    	colorPick4.setActivated(false);
		    	if(IS_SHIFTED){
		    		sigcanvas.drawBitmap(base,base_point[0]-11,base_point[1]-23,paint_clear);	
		    	    checkCircle();
		    	    sigView.invalidate();
		    	}
  }
  
  
	private void basepointclear() {
 	    IS_SHIFTED=false;
 	    base_point=new float[2];
 	    rpoint=null;
	}
	
	
  public void checkCircle(){
	  if(anymorphingdata.num_fpoint==1){
		  Rect rec=new Rect(anymorphingdata.fpoint1[0]-8,anymorphingdata.fpoint1[1]-8,anymorphingdata.fpoint1[0]+8,anymorphingdata.fpoint1[1]+8);
 		  sigcanvas.drawBitmap(nail,null,rec,paint);
	  }
	  else if(anymorphingdata.num_fpoint==2){
		  Rect rec=new Rect(anymorphingdata.fpoint1[0]-8,anymorphingdata.fpoint1[1]-8,anymorphingdata.fpoint1[0]+8,anymorphingdata.fpoint1[1]+8);
 		  sigcanvas.drawBitmap(nail,null,rec,paint);
 		  rec=new Rect(anymorphingdata.fpoint2[0]-8,anymorphingdata.fpoint2[1]-8,anymorphingdata.fpoint2[0]+8,anymorphingdata.fpoint2[1]+8);
 		  sigcanvas.drawBitmap(nail,null,rec,paint);
	  }

	  if(null!=fireView.firewalldata.wpoint1){
		  Rect rec=new Rect(fireView.firewalldata.wpoint1[0]-8,fireView.firewalldata.wpoint1[1]-8,fireView.firewalldata.wpoint1[0]+8,fireView.firewalldata.wpoint1[1]+8);
	      fireView.firecanvas.drawBitmap(nail1,null,rec,paint);
	  }
	  if(null!=fireView.firewalldata.wpoint2){
		  Rect rec=new Rect(fireView.firewalldata.wpoint2[0]-8,fireView.firewalldata.wpoint2[1]-8,fireView.firewalldata.wpoint2[0]+8,fireView.firewalldata.wpoint2[1]+8);
	      fireView.firecanvas.drawBitmap(nail1,null,rec,paint); 
	  }
		  
  }
  
  static {
 	if(!OpenCVLoader.initDebug()){
 		
 	}
 	else
 	System.loadLibrary("bwlabel1");
 }

  


OnTouchListener T2=new OnTouchListener(){
public boolean onTouch(View v, MotionEvent event) {
    int action = event.getAction();
    float[] coords={event.getX(),event.getY()};
	mat_inver.mapPoints(coords,coords);
    switch (action) {
    case MotionEvent.ACTION_DOWN: 
    	if((anymorphingdata.num_rpoint==1||anymorphingdata.num_rpoint==2)&&anymorphingdata.rpoint_clear){
    		int[] _coords={(int)coords[0],(int)coords[1]};
    		if(Arrays.equals(anymorphingdata.fpoint1,_coords)||Arrays.equals(anymorphingdata.fpoint2, _coords))
  			  return true;
    		   mystackele.release(4);               
    		   rpoint=_coords;   
               anymorphingdata.mor.morphing(rpoint,anymorphingdata.num_rpoint,anymorphingdata.contour_number);
               anymorphingdata.mor.setcontourcolor(); 
  			   mystackele.release(6);
  			   graspy.ModifyFpoint=true; 
  			   if(anymorphingdata.contour_number==1)
  				   anymorphingdata.graspPoint1=Arrays.copyOf(anymorphingdata.mor.graspPoint, 2);
  			   else if(anymorphingdata.contour_number==2)
  				   anymorphingdata.graspPoint2=Arrays.copyOf(anymorphingdata.mor.graspPoint, 2);
               graspy.setPos(anymorphingdata.mor.graspPoint);  
               graspy.setSig(3);
               lineView.linecanvas.drawPoint(-1, -1, lineView.paint_clear);
               lineView.invalidate();
               
               mystackele.release(9);
               anymorphingdata.moveclear=true;
    	}
    	else{
    		   int[] temp_edge;
                temp_edge=anymorphingdata.lineObj.Isedge(coords,Findedge_range,anymorphingdata.EDGE_MODE);
        int[] null_point={-1,-1};
        if(!Arrays.equals(null_point,temp_edge)){
      	  if(anymorphingdata.num_fpoint==0||anymorphingdata.num_fpoint==1){
      		if(anymorphingdata.num_fpoint==1&&Arrays.equals(anymorphingdata.fpoint1, temp_edge))
    			  return true;
      		   Rect rec=new Rect(temp_edge[0]-8,temp_edge[1]-8,temp_edge[0]+8,temp_edge[1]+8);
      		   sigcanvas.drawBitmap(nail,null,rec,paint);
               sigView.invalidate();
               anymorphingdata.num_fpoint=anymorphingdata.num_fpoint+1;
               if(anymorphingdata.num_fpoint==1){
            	   mystackele.release(11);
              	   anymorphingdata.fpoint1=temp_edge;
                   stateSave();	
       		       Toast toast = Toast.makeText(getApplicationContext(),
   				     R.string.SELECTENDPOINT, Toast.LENGTH_SHORT);
   				   toast.setGravity(Gravity.CENTER|Gravity.BOTTOM, 0, 60);
   				   toast.show();
              	 }
               if(anymorphingdata.num_fpoint==2){
            	   mystackele.release(12);
              	   anymorphingdata.fpoint2=temp_edge;
              	   stateSave();
       		       Toast toast = Toast.makeText(getApplicationContext(),
   				     R.string.SELECTDRAGPOINT, Toast.LENGTH_SHORT);
   				   toast.setGravity(Gravity.CENTER|Gravity.BOTTOM, 0, 60);
   				   toast.show();
               }
      	  }
      
      	  else if((anymorphingdata.num_rpoint==0||anymorphingdata.num_rpoint==1)&&!anymorphingdata.rpoint_clear&&getlineclear){
      		  checkLine1();
      		if(Arrays.equals(anymorphingdata.fpoint1,temp_edge)||Arrays.equals(anymorphingdata.fpoint2, temp_edge)||!anymorphingdata.mor.Is_logical(temp_edge))
    			  return true;
      				getlineclear=false;  
      		        mytimer.temp_edge=temp_edge;    		      
            	    mytimer.myTest();     		  
      	  }       
        }
    	  }
        break;
    case MotionEvent.ACTION_MOVE: 
    	if((anymorphingdata.num_rpoint==1||anymorphingdata.num_rpoint==2)&&anymorphingdata.rpoint_clear){
    		int[] _coords={(int)coords[0],(int)coords[1]};
    		if(Arrays.equals(anymorphingdata.fpoint1,_coords)||Arrays.equals(anymorphingdata.fpoint2, _coords))
  			  return true;
    		   mystackele.release(4);               
    		   rpoint=_coords;   
               anymorphingdata.mor.morphing(rpoint,anymorphingdata.num_rpoint,anymorphingdata.contour_number);
               anymorphingdata.mor.setcontourcolor(); 
  			   mystackele.release(6);
  			   graspy.ModifyFpoint=true; 
  			   if(anymorphingdata.contour_number==1)
  				   anymorphingdata.graspPoint1=Arrays.copyOf(anymorphingdata.mor.graspPoint, 2);
  			   else if(anymorphingdata.contour_number==2)
  				   anymorphingdata.graspPoint2=Arrays.copyOf(anymorphingdata.mor.graspPoint, 2);
               graspy.setPos(anymorphingdata.mor.graspPoint);  
               graspy.setSig(3);
               lineView.linecanvas.drawPoint(-1, -1, lineView.paint_clear);
               lineView.invalidate();
               
               mystackele.release(9);
               anymorphingdata.moveclear=true;
    	}
        break;
    case MotionEvent.ACTION_UP:
    	if(anymorphingdata.moveclear){
    		anymorphingdata.moveclear=false;
    		anymorphingdata.COULD_GENERATE=true;
    		stateSave();
    	}
        break;
    default:
        break;
    }

    return true;
}
};




public void stateSave(){
	 try {
		mystackele.setClone();
	} catch (CloneNotSupportedException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	}
	 mystack.current_ind++;   
     mystack.removeRange(mystack.current_ind,mystack.size());
	 mystack.push(mystackele);			 
     
     mystackele=new Mystackele(AnyMorphing.this);
}




public void onClick(View v) {
	if(v==openLoadSave){
		if(boxvisible==1){
			loadSaveToolbox.setVisibility(4);
		    boxvisible=0;
		}
		else{
			hidebox(boxvisible);
			loadSaveToolbox.setVisibility(0);
		    boxvisible=1;
		    refreshUI(null);
		}
	}
	
	else if(v==slidersEditBtn){
		if(boxvisible==2){
			this.sliderDialog.dismiss();
			boxvisible=0;
		}
		else{
			hidebox(boxvisible);	    
			sliderDialog.show();
			boxvisible=2;
			refreshUI(null);
		}
	}
	
	else if(v==editBox){
		if(boxvisible==3){
			paintToolboxes.setVisibility(4);
		    boxvisible=0;
		}
		else{
			hidebox(boxvisible);
			paintToolboxes.setVisibility(0);
		    boxvisible=3;
		}
	}
	
	else if(v==share){
		    Uri uri=getSharepic();
            shareTo(uri);
	}
	
	else if(v==infoOpen){
		if(boxvisible==5){
			this.aboutDialog.dismiss();
		    boxvisible=0;
		}
		else{
			hidebox(boxvisible);					    
			this.aboutDialog.show();
		    boxvisible=5;
		    refreshUI(null);
		}
	}
		
}



void hidebox(int n){
	switch (n){
	case(1):{
		loadSaveToolbox.setVisibility(4);
	
	}break;
	case(2):{
		this.sliderDialog.dismiss();
		
	}break;
	case(3):{
		paintToolboxes.setVisibility(4);
		
	}break;
	case(4):{
		
	}break;
	case(5):{
		aboutDialog.dismiss();
		
	}break;
	
	default:break;
	
	}
}




private Uri getSharepic() {
	String str=SDCARD_ROOT_PATH+SAVE_PATH_IN_SDCARD+"sharepic.jpg";
    File file=new File(str);
    file.delete();	
    file.deleteOnExit();
    FileOutputStream stream;
	try {
		stream = new FileOutputStream(file);
		bmpnew.compress(Bitmap.CompressFormat.JPEG, 100, stream);
		stream.close();
		stream.flush();		
	} catch (Exception e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	}
	Uri uri=Uri.fromFile(file);
	return uri;

}




private void shareTo(Uri uri) {
    
    Intent shareIntent = new Intent(android.content.Intent.ACTION_SEND);
    shareIntent.putExtra(Intent.EXTRA_SUBJECT, getString(R.string.SHAREPIC));
    if(uri!=null){  
        shareIntent.putExtra(Intent.EXTRA_STREAM, uri);  
        shareIntent.setType("image/*");   
    }else{  
        shareIntent.setType("text/plain");   
    } 
    shareIntent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK); 
    startActivityForResult(Intent.createChooser(shareIntent, getString(R.string.SHARE)),4); 
}




public void refreshParam(){
	  edge_pref=true;
      basepointclear();
	  windowchanged=false;
	  getlineclear=true;
	  mat.reset();
	  mat_inver.reset();	
}




public void refreshUI(View v){
	
	if(v==null){
		refresh_shift();
		if(!anymorphingdata.EDGE_MODE)
			colorPick1.setSelected(false);
		colorPick2.setSelected(false);
		colorPick3.setSelected(false);
		colorPick4.setActivated(false);
		colorPick4.setSelected(false);
		colorPick5.setSelected(false);
		colorPick6.setSelected(false);
		colorPick7.setSelected(false);
		colorPick8.setSelected(true);
		localImageView.setOnTouchListener(T5);
        lineView.setOnTouchListener(null);
        fireView.setOnTouchListener(null); 
	}
	else if(v==colorPick1){
		checkLine1();
	}
	else if(v==colorPick2){
		checkLine1();
		colorPick2.setSelected(true);
		colorPick3.setSelected(false);
		colorPick4.setActivated(false);
		colorPick4.setSelected(false);
		colorPick5.setSelected(false);
		colorPick6.setSelected(false);
		colorPick7.setSelected(false);
		colorPick8.setSelected(false);
	}
	else if(v==colorPick3){
		checkLine1();
		colorPick2.setSelected(false);
		colorPick3.setSelected(true);
		colorPick4.setSelected(false);
		colorPick5.setSelected(false);
		colorPick6.setSelected(false);
		colorPick7.setSelected(false);
		colorPick8.setSelected(false);		
	}
	else if(v==colorPick4){
		checkLine1();
		if(colorPick4.isActivated()){
		colorPick3.setSelected(false);
		colorPick2.setSelected(false);
		}
		colorPick5.setSelected(false);
		colorPick6.setSelected(false);
		colorPick7.setSelected(false);
		colorPick8.setSelected(false);
	}
	else if(v==colorPick5){
		checkLine1();
		refresh_shift();
		colorPick2.setSelected(false);
		colorPick3.setSelected(false);
		colorPick4.setActivated(false);
		colorPick4.setSelected(false);
		colorPick5.setSelected(true);
		colorPick6.setSelected(false);
		colorPick7.setSelected(false);
		colorPick8.setSelected(false);		
	}
	else if(v==colorPick6){
		checkLine1();
		refresh_shift();
		if(colorPick6.isSelected()){
		colorPick2.setSelected(false);
		colorPick3.setSelected(false);
		colorPick4.setActivated(false);
		colorPick4.setSelected(false);
		colorPick5.setSelected(false);
		colorPick7.setSelected(false);
		colorPick8.setSelected(false);
		}
		
	}
	else if(v==colorPick7){
		checkLine1();
		refresh_shift();
		colorPick2.setSelected(false);
		colorPick3.setSelected(false);
		colorPick4.setActivated(false);
		colorPick4.setSelected(false);
		colorPick5.setSelected(false);
		colorPick6.setSelected(false);
		colorPick7.setSelected(true);
		colorPick8.setSelected(false);
	}
	else if(v==colorPick8){
		checkLine1();
		refresh_shift();
		colorPick2.setSelected(false);
		colorPick3.setSelected(false);
		colorPick4.setActivated(false);
		colorPick4.setSelected(false);
		colorPick5.setSelected(false);
		colorPick6.setSelected(false);
		colorPick7.setSelected(false);
		colorPick8.setSelected(true);	
	}
}




OnClickListener L1=new OnClickListener(){
	public void onClick(View v){
	    Intent localIntent1 = new Intent();
	    localIntent1.setAction(Intent.ACTION_PICK);
	    localIntent1.setType("image/*");
	    int PICK_PHOTO=1;
	    startActivityForResult(localIntent1, PICK_PHOTO);
	}
};



OnClickListener L2=new OnClickListener(){
	public void onClick(View v){
				
		mystackele.release(1);		
		if(!anymorphingdata.EDGE_MODE){			
			anymorphingdata.EDGE_MODE=true;
	        anymorphingdata.lineObj.setContourMode(anymorphingdata.mor.nativeObj,anymorphingdata.num_rpoint);
	        colorPick1.setSelected(true);
			}
		
		else{
			anymorphingdata.EDGE_MODE=false;
			anymorphingdata.lineObj.setFreeMode(anymorphingdata.mor.nativeObj,anymorphingdata.num_rpoint);
			colorPick1.setSelected(false);
		}
		
		refreshUI(v);
		lineView.linecanvas.drawPoint(-1, -1, lineView.paint_clear);
	    lineView.invalidate();
	    stateSave();
	};
	
};




OnClickListener L3=new OnClickListener(){
	public void onClick(View v){
		refreshUI(v);
	    localImageView.setOnTouchListener(null);
	    fireView.setOnTouchListener(null);
	    lineView.setListener(2);
	    if(IS_SHIFTED){
	    	colorPick4.setSelected(true);
	    	sigcanvas.drawBitmap(base,base_point[0]-11,base_point[1]-23,paint);	   	    
	  	    sigView.invalidate();
	    }	    
	    else{
	    	colorPick4.setSelected(false);
	    	colorPick4.setActivated(false);
	    	if(IS_SHIFTED){
	    		sigcanvas.drawBitmap(base,base_point[0]-11,base_point[1]-23,paint_clear);	
	    	    sigView.invalidate();
	    	}
	    	
	    }
	    	
	}
};




private int currentStatus=0;
public static final int STATUS_NONE = 0;
public static final int STATUS_INIT = 1;
public static final int STATUS_PINCHZOOM = 2;
public static final int STATUS_MOVE = 3;

private float centerPointX;
private float centerPointY;
private float precenterPointX;
private float precenterPointY;
private float lastXMove;
private float lastYMove;
private float movedDistanceX;
private float movedDistanceY;
private int width; 
private int height; 
private float initRatio; 
private double lastFingerDis;
private double currentfingerDis;
OnTouchListener T5=new OnTouchListener(){
	@Override
	public boolean onTouch(View v,MotionEvent event) {
		switch (event.getActionMasked()) {
		case MotionEvent.ACTION_DOWN:
			if(event.getPointerCount() == 1){
				lastXMove=event.getX();
				lastYMove=event.getY();
			}
			break;
		case MotionEvent.ACTION_POINTER_DOWN:
			if(event.getPointerCount() == 2){
				centerPointBetweenFingers(event);
				precenterPointX=centerPointX;
				precenterPointY=centerPointY;
				lastFingerDis = distanceBetweenFingers(event);
			}
			break;
		case MotionEvent.ACTION_MOVE:
			if (event.getPointerCount() == 1) {
				float xMove = event.getX();
				float yMove = event.getY();
				currentStatus = STATUS_MOVE;
				movedDistanceX = xMove - lastXMove;
				movedDistanceY = yMove - lastYMove;
				refresh_translate();
				lastXMove = xMove;
				lastYMove = yMove;
			} else if (event.getPointerCount() == 2) {
				currentStatus=STATUS_PINCHZOOM;
				centerPointBetweenFingers(event);
				currentfingerDis = distanceBetweenFingers(event);
				
				refresh_translate();
				lastFingerDis = currentfingerDis;
			}
			break;
		case MotionEvent.ACTION_POINTER_UP:
			if (event.getPointerCount() == 2) {
				if(event.getActionIndex()==1){
				lastXMove = event.getX(0);
				lastYMove = event.getY(0);
				}else if(event.getActionIndex()==0){
					lastXMove = event.getX(1);
					lastYMove = event.getY(1);
				}
			}
			break;
		case MotionEvent.ACTION_UP:
			break;
		default:
			break;
		}
		return true;
}

};




private double distanceBetweenFingers(MotionEvent event) {  
    float disX = Math.abs(event.getX(0) - event.getX(1));  
    float disY = Math.abs(event.getY(0) - event.getY(1));  
    return Math.sqrt(disX * disX + disY * disY);  
} 



private void centerPointBetweenFingers(MotionEvent event) {  
    float xPoint0 = event.getX(0);  
    float yPoint0 = event.getY(0);  
    float xPoint1 = event.getX(1);  
    float yPoint1 = event.getY(1);  
    centerPointX = (xPoint0 + xPoint1) / 2;  
    centerPointY = (yPoint0 + yPoint1) / 2;  
} 



public void refresh_translate(){
    switch (currentStatus) {  
    case STATUS_PINCHZOOM:  
        pinchZoom(); 
        currentStatus=STATUS_NONE;
        break;  
    case STATUS_MOVE:  
        move();  
        currentStatus=STATUS_NONE;
        break;  
    case STATUS_INIT:  
        initBitmap(); 
        currentStatus=STATUS_NONE;
        break;
    default: 
    	currentStatus=STATUS_NONE;
        break;  
    }

}



private void initBitmap() {  
    if (bmpnew != null) {  
        mat.reset();   
        if (picw > width || pich > height) { 
        	float ratio;
            if ((float)picw - width > (float)pich - height) {  
                ratio = width / (picw * 1.0f);  
                mat.postScale(ratio, ratio);  
                float translateY = (height - (pich * ratio)) / 2f;  
                mat.postTranslate(0, translateY);  
            } else {  
                ratio = height / (pich * 1.0f);  
                mat.postScale(ratio, ratio);  
                float translateX = (width - (picw * ratio)) / 2f;  
                mat.postTranslate(translateX, 0);  
            }
            initRatio=ratio;
        } else {  
            float translateX = (width - bmpnew.getWidth()) / 2f;  
            float translateY = (height - bmpnew.getHeight()) / 2f;  
            mat.postTranslate(translateX, translateY);  
            initRatio=1f;
        }  
        
        setTranslate(); 
    }  
}



private void move(){
	float[] values = new float[9];
	mat.getValues(values);
    if(values[Matrix.MTRANS_X]+movedDistanceX<-values[Matrix.MSCALE_X]*picw||values[Matrix.MTRANS_X]+movedDistanceX>width)
    	movedDistanceX=0;
    if(values[Matrix.MTRANS_Y]+movedDistanceY<-values[Matrix.MSCALE_Y]*pich||values[Matrix.MTRANS_Y]+movedDistanceY>height)
    	movedDistanceY=0;
        mat.postTranslate(movedDistanceX, movedDistanceY);   
        setTranslate(); 
}




private void pinchZoom() {  

	movedDistanceX = centerPointX-precenterPointX;
	movedDistanceY = centerPointY-precenterPointY;
	precenterPointX=centerPointX;
	precenterPointY=centerPointY; 
	float scaledRatio=(float) (currentfingerDis/lastFingerDis);
	float[] values = new float[9];
	mat.getValues(values);
    if(values[Matrix.MTRANS_X]+movedDistanceX<-values[Matrix.MSCALE_X]*picw||values[Matrix.MTRANS_X]+movedDistanceX>width)
    	movedDistanceX=0;
    if(values[Matrix.MTRANS_Y]+movedDistanceY<-values[Matrix.MSCALE_Y]*pich||values[Matrix.MTRANS_Y]+movedDistanceY>height)
    	movedDistanceY=0;
    mat.postTranslate(movedDistanceX, movedDistanceY);   
	mat.postScale(scaledRatio, scaledRatio,centerPointX,centerPointY); 
	mat.getValues(values);
	if(values[Matrix.MTRANS_X]+movedDistanceX<-values[Matrix.MSCALE_X]*picw||values[Matrix.MTRANS_X]+movedDistanceX>width||values[Matrix.MTRANS_Y]+movedDistanceY<-values[Matrix.MSCALE_Y]*pich||values[Matrix.MTRANS_Y]+movedDistanceY>height||values[Matrix.MSCALE_X]<initRatio)
	{
		mat.postScale(1f/scaledRatio, 1f/scaledRatio,centerPointX,centerPointY);
	}  

    setTranslate();
} 




public void setTranslate(){
	localImageView.setImageMatrix(mat);	
	sigView.setImageMatrix(mat);
	lineView.setImageMatrix(mat);
	fireView.setImageMatrix(mat);
	mat.invert(mat_inver);	
}




OnTouchListener T6=new OnTouchListener(){
public boolean onTouch(View v, MotionEvent event) {
	int action = event.getAction();
    float[] coords={event.getX(),event.getY()};
	mat_inver.mapPoints(coords,coords);
    switch (action) {
    case MotionEvent.ACTION_DOWN:
    	int[] temp_edge;
            temp_edge=anymorphingdata.lineObj.Isedge(coords,Findedge_range,anymorphingdata.EDGE_MODE);
        int[] null_point={-1,-1};
        if(!Arrays.equals(null_point,temp_edge)){
      	  if(anymorphingdata.num_wpoint==0){              
               anymorphingdata.num_wpoint=1;              
              	 fireView.setWpoint(1,temp_edge);//闂佸憡锚椤戝棝鎮ラ敓锟�            	 
              	 stateSave();
   			     Toast toast = Toast.makeText(getApplicationContext(),
    				     R.string.SELECTSECONDF, Toast.LENGTH_SHORT);
    				   toast.setGravity(Gravity.CENTER|Gravity.BOTTOM, 0, 60);
    				   toast.show();
      	  }
      	  else if(anymorphingdata.num_wpoint==1){       		  
      		mytimer.temp_edge=temp_edge;
      		if(getlineclear){  
      			getlineclear=false;   			
      	        mytimer.myTest1();
      		  }
      	  }

        }
        break;

    case MotionEvent.ACTION_UP:

        break;

    default:
        break;
    }

       return true;
}
};



OnClickListener L4=new OnClickListener(){
	public void onClick(View v){
		refreshUI(v);
		localImageView.setOnTouchListener(T2);
		lineView.setOnTouchListener(null);
		fireView.setOnTouchListener(null);
		
		if(anymorphingdata.num_rpoint==0){
		if(anymorphingdata.num_fpoint==0){
		    Toast toast = Toast.makeText(getApplicationContext(),
				     R.string.SELECTSTARTPOINT, Toast.LENGTH_SHORT);
				   toast.setGravity(Gravity.CENTER|Gravity.BOTTOM, 0, 60);
				   toast.show();
		}
		else if(anymorphingdata.num_fpoint==1){
		           Toast toast = Toast.makeText(getApplicationContext(),
				     R.string.SELECTENDPOINT, Toast.LENGTH_SHORT);
				   toast.setGravity(Gravity.CENTER|Gravity.BOTTOM, 0, 60);
				   toast.show();
		}
		else if(anymorphingdata.num_fpoint==2){
		           Toast toast = Toast.makeText(getApplicationContext(),
				     R.string.SELECTDRAGPOINT, Toast.LENGTH_SHORT);
				   toast.setGravity(Gravity.CENTER|Gravity.BOTTOM, 0, 60);
				   toast.show();
		}
		}
      
    if(anymorphingdata.graspythreaddata.sig==3||anymorphingdata.graspythreaddata.sig==4){
       anymorphingdata.rpoint_clear=true;
        
      if(anymorphingdata.contour_number==2){
    	if(null!=anymorphingdata.mor.graspPoint)
    	anymorphingdata.graspPoint2=Arrays.copyOf(anymorphingdata.mor.graspPoint, 2);
        anymorphingdata.mor.graspPoint=anymorphingdata.graspPoint1;
    }
      if(null!=anymorphingdata.mor.graspPoint){
      	mystackele.release(6);
         graspy.setPos(anymorphingdata.mor.graspPoint);  
         graspy.setSig(3); 
      }
        } 
    
	 anymorphingdata.contour_number=1;
    
	};
};




OnClickListener L5=new OnClickListener(){
	public void onClick(View v){				     
		         localImageView.setOnTouchListener(T3);
		         lineView.setOnTouchListener(null); 
		         fireView.setOnTouchListener(null);
		         colorPick4.setActivated(true);
		         colorPick4.setSelected(false);		         
		         if(IS_SHIFTED){
		        	    sigcanvas.drawBitmap(base,base_point[0]-11,base_point[1]-23,paint_clear);
						sigView.invalidate();
					}
		         IS_SHIFTED=false;
				Toast toast = Toast.makeText(getApplicationContext(),
						      R.string.EDGE_PREFSET, Toast.LENGTH_SHORT);
						      toast.setGravity(Gravity.CENTER|Gravity.BOTTOM, 0, 60);
						      toast.show();
			refreshUI(v);
	}
	
};



OnClickListener L6=new OnClickListener(){
	public void onClick(View v){
		refreshUI(v);
		localImageView.setOnTouchListener(null);
		fireView.setOnTouchListener(null);
		lineView.setListener(1);
		if(IS_SHIFTED){
	    	colorPick4.setSelected(true);
	    	sigcanvas.drawBitmap(base,base_point[0]-11,base_point[1]-23,paint); 	   	    
	  	    sigView.invalidate();
	    }
	    else{
	    	colorPick4.setSelected(false);
	    	colorPick4.setActivated(false);
	    	if(IS_SHIFTED){
	    		sigcanvas.drawBitmap(base,base_point[0]-11,base_point[1]-23,paint_clear);
	    	    sigView.invalidate();
	    	}
	    }
		Toast toast = Toast.makeText(getApplicationContext(),
			     R.string.BRUSHSIZESET, Toast.LENGTH_SHORT);
			   toast.setGravity(Gravity.CENTER|Gravity.BOTTOM, 0, 60);
			   toast.show();
	}
};



OnClickListener L7=new OnClickListener(){
	public void onClick(View v){
	 if(anymorphingdata.num_rpoint==1){
		    Toast toast = Toast.makeText(getApplicationContext(),
				     R.string.SELECTDRAGPOINT, Toast.LENGTH_SHORT);
				   toast.setGravity(Gravity.CENTER|Gravity.BOTTOM, 0, 60);
				   toast.show();
	 }
     
     if(anymorphingdata.graspythreaddata.sig==3||anymorphingdata.graspythreaddata.sig==4){
    	 localImageView.setOnTouchListener(T2);
 		 lineView.setOnTouchListener(null);
 		 fireView.setOnTouchListener(null);			
         colorPick6.setSelected(true);
         refreshUI(v);
         
         if(anymorphingdata.num_rpoint==1)
             anymorphingdata.rpoint_clear=false;
          else 
         	 anymorphingdata.rpoint_clear=true;
         
        if(anymorphingdata.contour_number==1){
        	if(null!=anymorphingdata.mor.graspPoint)
        	anymorphingdata.graspPoint1=Arrays.copyOf(anymorphingdata.mor.graspPoint, 2);
            anymorphingdata.mor.graspPoint=anymorphingdata.graspPoint2;
        }
        
            if(null!=anymorphingdata.mor.graspPoint){
            	mystackele.release(6);
               graspy.setPos(anymorphingdata.mor.graspPoint);  
               graspy.setSig(3); 
            }
            anymorphingdata.contour_number=2; 
     }

	}
};




OnClickListener L9=new OnClickListener(){
	public void onClick(View v){
		if(anymorphingdata.num_wpoint==0)
		{
			  Toast toast = Toast.makeText(getApplicationContext(),
	   				     R.string.SELECTFIRSTF, Toast.LENGTH_SHORT);
	   				   toast.setGravity(Gravity.CENTER|Gravity.BOTTOM, 0, 60);
	   				   toast.show();
		}
		else if(anymorphingdata.num_wpoint==1){
			  Toast toast = Toast.makeText(getApplicationContext(),
	   				     R.string.SELECTSECONDF, Toast.LENGTH_SHORT);
	   				   toast.setGravity(Gravity.CENTER|Gravity.BOTTOM, 0, 60);
	   				   toast.show();
		}
		refreshUI(v);
        localImageView.setOnTouchListener(null);
        lineView.setOnTouchListener(null);
        fireView.setOnTouchListener(T6);       
	}
	
};



OnClickListener L13=new OnClickListener(){
	public void onClick(View v){
		
		if(mytimer.Line1.clear==2||mytimer.Line1.clear==4){
			checkLine1();
		}
		else{			
		if(mystack.current_ind>0)
			mystack.current_ind--;
		else if(mystack.current_ind==0)
			return;
		if(mystack.current_ind>=0){
         Mystackele ele=(Mystackele) mystack.get(mystack.current_ind);
         try {
			ele.restore(1);
		} catch (CloneNotSupportedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
         mystack.bfdir=1;   
         
         checkUI(null);
		}		
		}
	}
};




OnClickListener L14=new OnClickListener(){
	public void onClick(View v){
		
		checkLine1();
		
		if(mystack.current_ind<mystack.size()-1)
			mystack.current_ind++;
		else if(mystack.current_ind==mystack.size()-1)
			return;
		if(mystack.current_ind<mystack.size()){
         Mystackele ele=(Mystackele) mystack.get(mystack.current_ind);
         try {
			ele.restore(2);
		} catch (CloneNotSupportedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
         mystack.bfdir=2;
         
         checkUI(null);
		}
		}
};



public void checkUI(View v){
	if(v==null){
		if(colorPick6.isSelected()){
			if(anymorphingdata.num_rpoint==0){
				refreshUI(null);
			}
			else if(anymorphingdata.num_rpoint==1&&anymorphingdata.contour_number==1){
				refreshUI(null);
			}
			else if(anymorphingdata.num_rpoint==2&&anymorphingdata.contour_number!=2){
				refreshUI(null);
			}
		}
		else if(colorPick4.isActivated()||colorPick4.isSelected()){
			if(IS_SHIFTED){
				sigcanvas.drawBitmap(base,base_point[0]-11,base_point[1]-23,paint); 
			}
			else{
				sigcanvas.drawBitmap(base,base_point[0]-11,base_point[1]-23,paint_clear);				
			}
			sigView.invalidate();
		}
	}
}



OnTouchListener T3=new OnTouchListener(){
public boolean onTouch(View v,MotionEvent event) {
	
	int action = event.getAction();
    switch (action) {
    case MotionEvent.ACTION_DOWN:
    	float[] coords={event.getX(),event.getY()};
    	mat_inver.mapPoints(coords,coords);
    	if(edge_pref){  	
        int[] temp_edge=anymorphingdata.lineObj.Isedge(coords,Findedge_range,anymorphingdata.EDGE_MODE);
        int[] null_point={-1,-1};
    	if(IS_SHIFTED){ 
    		originpixels_inpute();
    	}
        if(!Arrays.equals(null_point,temp_edge)){ 
        	base_point[0]=(float)temp_edge[0]; 
        	base_point[1]=(float)temp_edge[1];
        } 
        else{
    		base_point=coords;
    	}
    	}
    	else{
        	if(IS_SHIFTED){ 
        		originpixels_inpute();
        	}
    		base_point=coords; 		
    	}
    	 sigcanvas.drawBitmap(base,base_point[0]-11,base_point[1]-23,paint);
    	 sigView.invalidate();
    	break;  
    case MotionEvent.ACTION_UP:
    	IS_SHIFTED=true;
	       Toast toast = Toast.makeText(getApplicationContext(),
		     R.string.RECLICK, Toast.LENGTH_SHORT);
		   toast.setGravity(Gravity.CENTER|Gravity.BOTTOM, 0, 60);
		   toast.show();
    	break;
    default:
        break;
}
    return true;
}

};



public void setScaleType(){
	localImageView.setScaleType(ScaleType.MATRIX);
	sigView.setScaleType(ScaleType.MATRIX);
	lineView.setScaleType(ScaleType.MATRIX);
	fireView.setScaleType(ScaleType.MATRIX);
}





public void reset_translate(){
	mat.reset();
	localImageView.setImageMatrix(mat);
	sigView.setImageMatrix(mat);
	lineView.setImageMatrix(mat);
	fireView.setImageMatrix(mat);								
	mat.invert(mat_inver);	
}



public void originpixels_inpute(){
	sigcanvas.drawBitmap(base,base_point[0]-11,base_point[1]-23,paint_clear);
	checkCircle();
	sigView.invalidate();
}


public void inpute_fpointicon(int n){
    if(n==0){
    	if(anymorphingdata.fpoint1!=null){
    		mystackele.release(11);
    	sigcanvas.drawRect(anymorphingdata.fpoint1[0]-8, anymorphingdata.fpoint1[1]-8, anymorphingdata.fpoint1[0]+8,anymorphingdata.fpoint1[1]+8, paint_clear);
    	}
		anymorphingdata.fpoint1=null;
		if(anymorphingdata.fpoint2!=null){
			mystackele.release(12);
		sigcanvas.drawRect(anymorphingdata.fpoint2[0]-8, anymorphingdata.fpoint2[1]-8, anymorphingdata.fpoint2[0]+8,anymorphingdata.fpoint2[1]+8, paint_clear);
		}
		anymorphingdata.fpoint2=null;
		anymorphingdata.num_fpoint=0;
    }
	else if(anymorphingdata.fpoint1!=null&&(n==1)){
		mystackele.release(11);
		sigcanvas.drawRect(anymorphingdata.fpoint1[0]-8, anymorphingdata.fpoint1[1]-8, anymorphingdata.fpoint1[0]+8,anymorphingdata.fpoint1[1]+8, paint_clear);
		anymorphingdata.fpoint1=null;
		anymorphingdata.num_fpoint=0;
	}
	else if(anymorphingdata.fpoint2!=null&&(n==2)){
		mystackele.release(12);
		sigcanvas.drawRect(anymorphingdata.fpoint2[0]-8, anymorphingdata.fpoint2[1]-8, anymorphingdata.fpoint2[0]+8,anymorphingdata.fpoint2[1]+8, paint_clear);
		anymorphingdata.fpoint2=null;
		anymorphingdata.num_fpoint=1;
	}
	sigView.invalidate();
}


public static final String SDCARD_ROOT_PATH = android.os.Environment.getExternalStorageDirectory().getAbsolutePath();//闁荤姳璀﹂崹鎵閿燂拷 
public static final String SAVE_PATH_IN_SDCARD = "/Mormor/"; //闂佹悶鍎辨晶鑺ユ櫠閺嶎厼鐭楀┑鐘插�瀵版挸霉閻樺磭澧柡鍡欏枛楠炴垿顢欓懡銈囶啍闁诲孩绋掕摫闁哄鍟粋鎺旀崉閹帊绮� 
public static final String SAVE_TEMPPATH_IN_SDCARD = "/Mormor/Temp/";
public static final String IMAGE_CAPTURE_NAME = "cameraTmp.png"; //闂佺粯鎸嗛崨顓ф毈闂佸憡鑹剧粔鎯扳叿  

OnClickListener L10=new OnClickListener(){
	public void onClick(View v){
    Intent localIntent = new Intent("android.media.action.IMAGE_CAPTURE"); 
    File out=new File(SDCARD_ROOT_PATH+  
          SAVE_PATH_IN_SDCARD,IMAGE_CAPTURE_NAME);
    out.delete();
    out.deleteOnExit();
try {
	out.createNewFile();
} catch (IOException e) {
	// TODO Auto-generated catch block
	e.printStackTrace();
}

  localIntent.putExtra(MediaStore.EXTRA_OUTPUT, Uri.fromFile(out));
  
  startActivityForResult(localIntent, 2);
}
};

OnClickListener L11=new OnClickListener(){
	public void onClick(View v){
//		new SaveDialog(AnyMorphing.this,AnyMorphing.this).show();
		saveDialog();
}
};


OnClickListener L12=new OnClickListener(){
	
	public void onClick(View v){
//		reloadDialog();
		refreshUI(null);
}
};

OnLongClickListener L15 =new OnLongClickListener(){
	@Override
	public boolean onLongClick(View arg0) {
		// TODO Auto-generated method stub
		new BrushSizeDialog(AnyMorphing.this, AnyMorphing.this,AnyMorphing.this.size).show();
		return true;
	}
};


OnLongClickListener L18 =new OnLongClickListener(){
	@Override
	public boolean onLongClick(View arg0) {
		// TODO Auto-generated method stub
		edgeprefDialog.show();
		return true;
	}
};



public void onActivityResult(int paramInt1, int paramInt2, Intent paramIntent)
{
	  super.onActivityResult(paramInt1, paramInt2, paramIntent);
	  if (paramInt1 == 1 && paramInt2 == RESULT_OK && null != paramIntent){
		  
		  Uri selectedImage=null;
		  selectedImage = paramIntent.getData();
		  bmpfile=decodeUri(selectedImage);
		  synchronized(AnyMorphing.class){
		  res_recycle();
		  bmpRecycle();
		  }
		  anymorphingdata=new AnyMorphingData();
		  if(bmpfile!=null)
		     getBmp(bmpfile,0);
		  else{
			  Bundle extras=paramIntent.getExtras();
			  bmpnew=(Bitmap) extras.get("data");
              try {				
                      File file=new File(AnyMorphing.SDCARD_ROOT_PATH+AnyMorphing.SAVE_PATH_IN_SDCARD+AnyMorphing.IMAGE_CAPTURE_NAME);
                      file.delete();	
                      FileOutputStream stream = new FileOutputStream(file);
                      bmpnew.compress(Bitmap.CompressFormat.PNG, 100, stream);
            		  bmpfile=SDCARD_ROOT_PATH+SAVE_PATH_IN_SDCARD+IMAGE_CAPTURE_NAME;
            		  bmpnew.recycle();
            		  getBmp(bmpfile,0);
                      stream.flush();
                      stream.close();	                    
                } catch (Exception e) {
                     // TODO Auto-generated catch block
                      e.printStackTrace(); 
                      savefailedDialog();
                }
		  }
		  load_init(bmpfile,0);
		  
		  changeUI();
		  reset_translate();

		  firstStateSave();
		  
	  }
	  else if(paramInt1 == 2&& paramInt2 == RESULT_OK){
		  bmpfile=SDCARD_ROOT_PATH+  
	              SAVE_PATH_IN_SDCARD+IMAGE_CAPTURE_NAME;
		  int degree = BasicOperator.readPictureDegree(bmpfile);
		  synchronized(AnyMorphing.class){
          res_recycle();
		  bmpRecycle();
		  }
		  anymorphingdata=new AnyMorphingData();
		  getBmp(bmpfile,degree);		  
		  load_init(bmpfile,degree);
		  
		  changeUI();
		  reset_translate();

		  firstStateSave();
	  }
	  else if(paramInt1 == 3 && paramInt2 == RESULT_OK){
             boolean onback=paramIntent.getBooleanExtra("onback", false);
             if(onback){
            	 if(datastore.prefs.getBoolean("firstrun", true))
            		 this.finish();
             }
             else{
     		      datastore.prefsEdit.putBoolean("firstrun",false);
     		      datastore.prefsEdit.commit();
             }
	  }	
	  else if(paramInt1 == 4 && paramInt2 == RESULT_OK){

	  }	  
}



public String decodeUri(Uri uri){
	 String path = null;
     if("file".equals(uri.getScheme())){
	      path=uri.getPath();
         }
	 else if(null!=uri){
	 String[] proj = {MediaStore.Images.Media.DATA};
	 Cursor cursor = getContentResolver().query(uri, proj, null, null, null); 
	 if(cursor.moveToFirst()){
     int column_index = cursor.getColumnIndexOrThrow(MediaStore.Images.Media.DATA);
     path = cursor.getString(column_index);
	 }
	 cursor.close();
	 }
     return path;
}


public void bmpRecycle(){
      bmpnew.recycle();
      graspy.setSig(0);
	  sigpic.recycle();
	  lineView.linepic.recycle();
	  fireView.firebmp.recycle();
	  lineView.bmp.recycle();	  
}


public void getBmp(String file,int degree){
	  BitmapFactory.Options opts = new BitmapFactory.Options();
	  opts.inJustDecodeBounds=true;
	  opts.inPurgeable=true;
	  BitmapFactory.decodeFile(file,opts);                  
	  int imageHeight = opts.outHeight;
	  int imageWidth = opts.outWidth;
	  opts.inSampleSize=DataManager.resize(imageHeight,imageWidth);
	  opts.inJustDecodeBounds=false;
	  opts.inMutable=true;
	  bmpnew = BitmapFactory.decodeFile(file,opts);
	  bmpnew = rotaingImageView(degree,bmpnew);
}


public void res_recycle(){
	Mystackele ele=(Mystackele) mystack.get(0);
	ele.anymorphingdata.lineObj.clearMemStorage();
	mytimer.Line1.clearMem();
	mystack.removeRange(0,mystack.size());  
	mystack.clear();	
}



public Bitmap rotaingImageView(int angle , Bitmap bitmap) {  
    //闂佸搫鍟鍫澝归崱娑樼倞闁告挆鍐炬毈 闂佸憡鏌ｉ崝瀣礊閿燂拷 
	if(angle!=0&&bitmap!=null){
    Matrix matrix = new Matrix();;  
    matrix.postRotate(angle);
    try{
    Bitmap resizedBitmap = Bitmap.createBitmap(bitmap, 0, 0,  
            bitmap.getWidth(), bitmap.getHeight(), matrix, true); 
    if(bitmap!=resizedBitmap)
    {
       bitmap.recycle();
       bitmap=resizedBitmap;
    }
	}

	catch(OutOfMemoryError ex){
		
	}        
}
	return bitmap;
}



public void load_init(String file,int degree){
	
	  this.picw=bmpnew.getWidth();
	  this.pich=bmpnew.getHeight();      
      sigpic=Bitmap.createBitmap(picw,pich,Config.ARGB_8888);
	  lineView.drawingpaneldata=lineView.new DrawingPanelData();
	  anymorphingdata.drawingpaneldata=lineView.drawingpaneldata;
	  
	  fireView.firewalldata=fireView.new FireWallData();
	  anymorphingdata.firewalldata=fireView.firewalldata;
      lineView.init(this);
      fireView.init(this);   
	  anymorphingdata.lineObj=new Linelabel(bmpnew,lineView.linepic,lineView.bmp,file,degree);
	  anymorphingdata.mor=new Morphing(anymorphingdata.lineObj);
	  mystack=new Mystack();
	  mystackele=new Mystackele(AnyMorphing.this); 	  
	  mytimer=new MyTimer(AnyMorphing.this);	  		  		  
	  datastore.recallPrefs();  
	  refreshUI(null);
	  refreshParam();	
}

public void changeUI(){
	localcanvas=new Canvas(this.bmpnew);
	localImageView.setImageBitmap(this.bmpnew);
	lineView.setImageBitmap(lineView.linepic);
	sigView.setImageBitmap(sigpic);
	sigcanvas=new Canvas(sigpic);
	fireView.setImageBitmap(fireView.firebmp);	
	graspy.canvas=new Canvas(sigpic);
}



protected void onStart()
{
  super.onStart();  
}

  public void onDestroy()
  {
    super.onDestroy();
    res_recycle();  
    File file=new File(SDCARD_ROOT_PATH+  
            SAVE_PATH_IN_SDCARD,IMAGE_CAPTURE_NAME);
    file.delete();
  }

  protected void onPause()
  {
    super.onPause();
  }

  protected void onRestart()
  {
    super.onRestart();
  }

  protected void onResume()
  {
    super.onResume();
  }
  
  
  
  
  
  public void onSliderApply(float paramFloat,int n){	  
	  refresh_param(paramFloat,n);
	  if((anymorphingdata.GENERATE_CLEAR&&anymorphingdata.regionclear)||anymorphingdata.num_rpoint>0){
		  checkLine1();
	      generate_image(); 
	  }

  }
  




public void refresh_param(float paramFloat,int n){
	if(n==1)
	    this.sig=paramFloat;
	else if(n==3)
	    this.synratio=paramFloat;
    if(anymorphingdata.mor!=null)
      anymorphingdata.mor.initParam(this.sig,this.synratio);
      datastore.saveprefs(this.sig,this.synratio,this.size);  
}


public void generate_image(){

	if(anymorphingdata.GENERATE_CLEAR&&anymorphingdata.regionclear){
		
    	progressDialog = ProgressDialog.show(AnyMorphing.this, "Processing...", "Please wait...", true, false);
		new Thread(){
			public void run(){	
					anymorphingdata.mor.generate_image(anymorphingdata.num_rpoint);	
				handler.sendEmptyMessage(4);	 	 
		}
	}.start(); 
	}
	else{
		if(anymorphingdata.num_rpoint==1)
		          anymorphingdata.mor.generate_contour(anymorphingdata.num_rpoint);
		else if(anymorphingdata.num_rpoint==2)
			      anymorphingdata.mor.generate_contour(anymorphingdata.contour_number);
        mystackele.release(6);
        graspy.setPos(anymorphingdata.mor.graspPoint);  
        graspy.setSig(3);
        lineView.linecanvas.drawPoint(-1, -1, lineView.paint_clear);
	    lineView.invalidate();
	}
}


@Override
public void setBitmap() {
	localImageView.setImageBitmap(bmpnew);
	localcanvas.setBitmap(bmpnew);
	localcanvas.drawPoint(-1, -1, paint_clear);
	localImageView.invalidate();
}


@Override
public boolean onTouch(View v, MotionEvent event) {
	// TODO Auto-generated method stub
	return false;
}


@SuppressLint("HandlerLeak")
public Handler handler = new Handler(){   
	  
    @Override  
    public void handleMessage(Message msg) {   
        if(msg.what==0) {  
        //闂佺绻戞繛濠偽涚喊顣榦gressDialog         	
    	inpute_fpointicon(0);   
    	anymorphingdata.graspPoint1=null;
    	anymorphingdata.graspPoint2=null;  
    	localcanvas.drawPoint(-1, -1, paint_clear);
 	    localImageView.invalidate(); 
 	    mystackele.release(6);
 	    graspy.setSig(0); 
 	    fireView.clear();
 	    lineView.clear();
 	    basepointclear();
 	    progressDialog.dismiss(); 	    
 	    int hoffset;
 	    if(getResources().getDisplayMetrics().heightPixels>=1200)
 		   hoffset=300;
 	    else 
 		   hoffset=250;
		Toast toast = Toast.makeText(getApplicationContext(),
				      R.string.SLIDEAGAIN, Toast.LENGTH_SHORT);
				      toast.setGravity(Gravity.CENTER|Gravity.BOTTOM, 0, hoffset);
				      toast.show();
	    refreshUI(null);
    }
    else if(msg.what==2){
    	getlineclear=true;
        if(mytimer.Line1.clear==3){
        	  fireView.setWpoint(2,mytimer.temp_edge);
			  mytimer.Line1.lineRefresh(anymorphingdata.mor.nativeObj,fireView.firebmp,mytimer.Line1.clear);
			  fireView.firecanvas.drawPoint(-1, -1, fireView.paint_clear);
			  fireView.invalidate();  
			  anymorphingdata.num_wpoint=0;//闂佸憡锚椤戝棝鎮ラ敓锟�   			 	 
			  stateSave();
  	  }
		  else if(mytimer.Line1.clear==4){			  
			  Toast toast = Toast.makeText(getApplicationContext(),
   				     R.string.CONTOUR_CONNECTION, Toast.LENGTH_SHORT);
   				   toast.setGravity(Gravity.CENTER, 0, 0);
   				   toast.show();
   				   mytimer.Line1.lineRefresh(anymorphingdata.mor.nativeObj,fireView.firebmp,mytimer.Line1.clear);
   				   fireView.firecanvas.drawPoint(-1, -1, fireView.paint_clear);
   				   fireView.invalidate();
		  }
		  else if(mytimer.Line1.clear==5){			  
			  Toast toast = Toast.makeText(getApplicationContext(),
    				     R.string.CONTOUR_CONNECTION, Toast.LENGTH_SHORT);
    				   toast.setGravity(Gravity.CENTER, 0, 0);
    				   toast.show();
    				   mytimer.Line1.lineRefresh(anymorphingdata.mor.nativeObj,fireView.firebmp,mytimer.Line1.clear);
    				   fireView.firecanvas.drawPoint(-1, -1, fireView.paint_clear);
    				   fireView.invalidate();
		  }
		  else{
	  			Toast toast = Toast.makeText(getApplicationContext(),
	 				     R.string.CONTOUR_CONNECTION, Toast.LENGTH_SHORT);
	 		    toast.setGravity(Gravity.CENTER, 0, 0);
	 			toast.show();
			    mytimer.Line1.lineRefresh(anymorphingdata.mor.nativeObj,fireView.firebmp,mytimer.Line1.clear);
			    fireView.firecanvas.drawPoint(-1, -1, fireView.paint_clear);
			    fireView.invalidate();
		  }
    }
    else if(msg.what==3)
    {
    	getlineclear=true;
    	if(mytimer.Line1.clear==1){
  			if(anymorphingdata.num_rpoint==0||(anymorphingdata.num_rpoint==1)){
  				mystackele.release(4);                  
  				mytimer.Line1.lineRefresh(anymorphingdata.mor.nativeObj,anymorphingdata.num_rpoint,mytimer.Line1.clear);
  				mystackele.release(9);
   			        			  
      		    anymorphingdata.num_rpoint=anymorphingdata.num_rpoint+1;
      		    anymorphingdata.rpoint_clear=true;
      		    rpoint=mytimer.temp_edge;       			  
  		        anymorphingdata.mor.getaxis1(anymorphingdata.fpoint1,anymorphingdata.fpoint2,rpoint,anymorphingdata.contour_number); 
  		        lineView.linecanvas.drawPoint(-1, -1, lineView.paint_clear);
                lineView.invalidate(); 
              
                mystackele.release(6);
                anymorphingdata.mor.graspPoint=rpoint;
                if(anymorphingdata.contour_number==1)
                	anymorphingdata.graspPoint1=Arrays.copyOf(anymorphingdata.mor.graspPoint, 2);
                else if(anymorphingdata.contour_number==2)
                	anymorphingdata.graspPoint2=Arrays.copyOf(anymorphingdata.mor.graspPoint, 2);
                graspy.setPos(anymorphingdata.mor.graspPoint);  
                graspy.setSig(3);                 
                anymorphingdata.COULD_GENERATE=true;
                stateSave();
  		  } 
  		  }
  		  
  		  else if(mytimer.Line1.clear==2){       				    			  
  			Toast toast = Toast.makeText(getApplicationContext(),
 				     R.string.CONTOUR_CONNECTION, Toast.LENGTH_SHORT);
 				   toast.setGravity(Gravity.CENTER, 0, 0);
 				   toast.show();
 	  			   mytimer.Line1.lineRefresh(anymorphingdata.mor.nativeObj,anymorphingdata.num_rpoint,mytimer.Line1.clear);
 	  			   lineView.linecanvas.drawPoint(-1, -1, lineView.paint_clear);
 	  			   lineView.invalidate();
  		  }
  		else if(mytimer.Line1.clear==5){ 			
  			Toast toast = Toast.makeText(getApplicationContext(),
				     R.string.CONTOUR_CONNECTION, Toast.LENGTH_SHORT);
				   toast.setGravity(Gravity.CENTER, 0, 0);
				   toast.show();
				   mytimer.Line1.lineRefresh(anymorphingdata.mor.nativeObj,anymorphingdata.num_rpoint,mytimer.Line1.clear);
				   lineView.linecanvas.drawPoint(-1, -1, lineView.paint_clear);
				   lineView.invalidate();
		  }
  		else{
  			Toast toast = Toast.makeText(getApplicationContext(),
				     R.string.CONTOUR_CONNECTION, Toast.LENGTH_SHORT);
		    toast.setGravity(Gravity.CENTER, 0, 0);
		    toast.show();
  			mytimer.Line1.lineRefresh(anymorphingdata.mor.nativeObj,anymorphingdata.num_rpoint,mytimer.Line1.clear);
  			lineView.linecanvas.drawPoint(-1, -1, lineView.paint_clear);
  			lineView.invalidate();
  		}

    }
    else if(msg.what==4){
    	localcanvas.drawPoint(-1, -1, paint_clear);
    	localImageView.invalidate();
    	progressDialog.dismiss();
    }
             
    }

};   



@Override
public void ongenerate() {
	
	if(anymorphingdata.COULD_GENERATE){
    checkLine1();
    anymorphingdata.COULD_GENERATE=false;
	anymorphingdata.GENERATE_CLEAR=true;
	anymorphingdata.rpoint_clear=false;
	mystackele.release(4);
	mystackele.release(3);	
    	progressDialog = ProgressDialog.show(AnyMorphing.this, "Processing...", "Please wait...", true, false);
		new Thread(){
			public void run(){	
				       anymorphingdata.regionclear=anymorphingdata.mor.generate(anymorphingdata.num_rpoint);	
				handler.sendEmptyMessage(0);	 	 
		}
	}.start(); 	

	
	} 
}


@Override
public void onJump() {
	// TODO Auto-generated method stub
	Intent itent=new Intent();
    itent.setClass(AnyMorphing.this, Main_Activity.class);
    startActivityForResult(itent,3);
}

public boolean onKeyDown(int keyCode, KeyEvent event) {
	// TODO Auto-generated method stub
	return super.onKeyDown(keyCode, event);
}



@Override
public void onAboutDismiss() {
	// TODO Auto-generated method stub
	this.boxvisible=0;
}

@Override
public void onSliderDismiss() {
	// TODO Auto-generated method stub
	  this.boxvisible=0;
	  if(anymorphingdata.GENERATE_CLEAR){
	  anymorphingdata.COULD_GENERATE=false;
	  anymorphingdata.GENERATE_CLEAR=false;		  
	  anymorphingdata.num_rpoint=0;	  
	  anymorphingdata.contour_number=1;
	  
	  stateSave();
	  new Thread(){
			public void run(){
					if(anymorphingdata.regionclear)
			 	               anymorphingdata.lineObj.refreshLabel(anymorphingdata.mor.nativeObj);
			 	               anymorphingdata.regionclear=false;
		}
	}.start(); 	
	  }
}

@Override
public void onBrushSizeChange(int paramInt) {
	// TODO Auto-generated method stub
	AnyMorphing.this.size=paramInt;
	datastore.saveprefs(this.sig,this.synratio,this.size); 
	lineView.paint_clear.setStrokeWidth(paramInt);
}

@Override
public void onEdgepref(boolean paramBoolean) {
	// TODO Auto-generated method stub
	edge_pref=paramBoolean;
}


public void checkLine1(){
	if(mytimer.Line1.clear==2){
//		mytimer.Line1.inputeLine_1(anymorphingdata.EDGE_MODE);
    	anymorphingdata.lineObj.setTempMode(anymorphingdata.EDGE_MODE);
    	anymorphingdata.mor.setLine(anymorphingdata.num_rpoint); 
    	lineView.linecanvas.drawPoint(-1, -1, lineView.paint_clear);
    	lineView.invalidate();
    	mytimer.Line1.clear=0;
	}
	else if(mytimer.Line1.clear==4){
		fireView.reDraw();
		mytimer.Line1.clear=0;
	}
}




         int resolution=0;
         public void saveDialog(){
	            AlertDialog.Builder builder = new Builder(AnyMorphing.this); 
	            builder.setTitle(R.string.SAVE_IMAGE_TITLE);
	            builder.setSingleChoiceItems(R.array.save_resolution, 0,new DialogInterface.OnClickListener() {
                                                         public void onClick(DialogInterface dialog, int which) {
                                                                resolution=which;
                                                              }
                                                         });
	            builder.setPositiveButton(R.string.Save,  new DialogInterface.OnClickListener() {
                                                @SuppressWarnings("null")
												@Override
                                                public void onClick(DialogInterface dialog, int which) {
			                                           try {				
				                                             if(resolution==0)
				                                                {
					                                             String time=Long.valueOf(System.currentTimeMillis()).toString();	
					                                             File file=new File(AnyMorphing.SDCARD_ROOT_PATH+AnyMorphing.SAVE_PATH_IN_SDCARD+time+".jpg");
					                                             file.delete();	
					                                             FileOutputStream stream = new FileOutputStream(file);
				                                                 bmpnew.compress(Bitmap.CompressFormat.JPEG, 100, stream);
				                                                 stream.flush();
					                                             stream.close();	
				                                                }
				                                             else if(resolution==1){
					                                             boolean clear=anymorphingdata.lineObj.createbmp();	
					                                             if(!clear){
				                                            	 Exception e = null;
				                                            	 throw e;
					                                             }
				                                                }                                              
						
			                                               } catch (Exception e) {
				                                                // TODO Auto-generated catch block
				                                                 e.printStackTrace(); 
				                                                 savefailedDialog();
			                                               }	
			                                               resolution=0;
                                                           dialog.dismiss();
                                                          }
                                                      });
	            builder.setNegativeButton(R.string.CANCEL, new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {
    	        resolution=0;
                dialog.dismiss();
                 }
              });
	          builder.create().show();
          }
         
         public void savefailedDialog(){
             AlertDialog.Builder builder = new Builder(AnyMorphing.this);
             builder.setMessage(R.string.SAVE_FAILED);
             builder.setIcon(R.drawable.error);
             builder.setTitle(R.string.ERROR);
             builder.setNeutralButton(R.string.CANCEL,new DialogInterface.OnClickListener() {
                 @Override
                 public void onClick(DialogInterface dialog, int which) {
                 dialog.dismiss();
                }
              });
             builder.create().show();
         }

  }



/* Location:           C:\dex2jar-0.0.7-SNAPSHOT\classes.dex.dex2jar.jar
 * Qualified Name:     com.toonfx.toonpaint.ToonPAINT
 * JD-Core Version:    0.6.2
 */