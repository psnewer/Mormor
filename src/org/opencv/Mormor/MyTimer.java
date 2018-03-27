package org.opencv.Mormor;


import com.morphing.morobj.Getline;

public class MyTimer { 
	  
    private Thread thread;
    
    public Getline Line1;
    
    public AnyMorphing anymorphing;
    
    public int[] temp_edge;
  
    public MyTimer(AnyMorphing anymorphing){
    	this.anymorphing=anymorphing;
    	Line1=new Getline(anymorphing.anymorphingdata.lineObj.nativeObj);
    }

    
    public void myTest() {  
        thread = new Thread(){  
            @Override  
            public void run() {  
                Line1._getline(anymorphing.anymorphingdata.fpoint1,anymorphing.anymorphingdata.fpoint2,temp_edge);
                anymorphing.handler.sendEmptyMessage(3);
          	   
            }  
        };  
        thread.start();  
    }  
    
    public void myTest1() {  
        thread = new Thread(){  
            @Override  
            public void run() {  
                Line1._getline(anymorphing.fireView.firewalldata.wpoint1,temp_edge);
                anymorphing.handler.sendEmptyMessage(2);
            }  
        };  
        thread.start();  
    }  



}
