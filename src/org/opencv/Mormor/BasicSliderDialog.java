package org.opencv.Mormor;

import android.app.Dialog;
import android.content.Context;
import android.os.Bundle;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.SeekBar;

public class BasicSliderDialog extends Dialog
implements SeekBar.OnSeekBarChangeListener,Cloneable{
	
	private float sig;
	private float synratio;
	int i,j,k;
	private SeekBar sigBar;
	private SeekBar synratioBar;
	ImageButton sliderDialogDismiss;
	private SliderApplyCallback callback;

	Button generate;
	
	public BasicSliderDialog(Context paramContext, SliderApplyCallback paramSliderApplyCallback, float paramFloat1, float paramFloat3)
	  {
	    super(paramContext, 2131034112);
	    getWindow().getAttributes().gravity = 80;
	    requestWindowFeature(Window.FEATURE_NO_TITLE);
	    this.callback = paramSliderApplyCallback;
	    this.sig = paramFloat1;
	    this.synratio = paramFloat3; 
	    _calculateSliderPositions1(this.sig);
	    _calculateSliderPositions3(this.synratio);
	  }

	
	void calculateSliderPositions1(int paramInt1)
	  {
	    this.sig=paramInt1/100f*3f;
	  }
	
	void _calculateSliderPositions1(float paramFloat1)
	  {
		float temp=paramFloat1/3f*100f;
	    this.i=Math.round(temp);
	  }
	
	
	void calculateSliderPositions3(int paramInt3)
	  {
	    this.synratio=paramInt3/100f*3.5f;
	  }
	
	void _calculateSliderPositions3(float paramFloat3)
	  {
	    float temp=paramFloat3/3.5f*100f;
	    this.k=Math.round(temp);
	  }
	
	protected void onCreate(Bundle paramBundle)
	  {
	    super.onCreate(paramBundle);
	    setContentView(R.layout.basicsliders);
	    this.sigBar = (SeekBar)findViewById(R.id.sigSlider);
	    this.synratioBar = (SeekBar)findViewById(R.id.scaleSlider);
	    sigBar.setProgress(i);
	    synratioBar.setProgress(k);
	    sigBar.setOnSeekBarChangeListener(this);
	    synratioBar.setOnSeekBarChangeListener(this);	
	    init_UI();
        WindowManager.LayoutParams lp=getWindow().getAttributes();
        lp.alpha=1f;
        getWindow().setAttributes(lp);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_DIM_BEHIND);
	  }
	
	
	public void init_UI(){
		generate=(Button)findViewById(R.id.Generate);
		generate.setOnClickListener(L1);
		sliderDialogDismiss = (ImageButton)findViewById(R.id.sliderdismissBtn);
		sliderDialogDismiss.setOnClickListener(L2);
	}
	
	View.OnClickListener L1=new View.OnClickListener(){
		public void onClick(View v){		
             callback.ongenerate();
		};
	};
	
	View.OnClickListener L2=new View.OnClickListener(){
		public void onClick(View v){
			dismiss();	 
		};
	};
	
	
	public void dismiss(){
		super.dismiss();
		callback.onSliderDismiss();
	}
	
	public void onProgressChanged(SeekBar paramSeekBar, int paramInt, boolean paramBoolean)
	  {	    
	    if (paramSeekBar == sigBar){
	        this.i = paramInt;
	    }
	    else if (paramSeekBar == synratioBar){
	        this.k= paramInt;
	    }
	     
	  }


	
	
	abstract interface SliderApplyCallback
	  {
		public abstract void onSliderApply(float paramInt, int n);
		public abstract void onSliderDismiss();
        public abstract void ongenerate();
	  }





	@Override
	public void onStartTrackingTouch(SeekBar seekBar) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void onStopTrackingTouch(SeekBar seekBar) {
		// TODO Auto-generated method stub
	    if (seekBar == sigBar){
	      calculateSliderPositions1(this.i);
	      callback.onSliderApply(this.sig,1);
	    }
	    else if (seekBar == synratioBar){
	        calculateSliderPositions3(this.k);
	        callback.onSliderApply(this.synratio,3);
	    }
	     
	}




	  public BasicSliderDialog clone() throws CloneNotSupportedException{
			return (BasicSliderDialog) super.clone();
		}



}
