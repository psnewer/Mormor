package org.opencv.Mormor;

import android.app.Dialog;
import android.content.Context;
import android.os.Bundle;
import android.view.Gravity;
import android.view.View;
import android.widget.ImageButton;
import android.widget.SeekBar;

public class BrushSizeDialog extends Dialog implements SeekBar.OnSeekBarChangeListener{
	
	 private BrushSizeChangeCallback callback;
	 public SeekBar seekbar;
	 public ImageButton dismiss;
	 public int size;
	 BrushSizePreview localBrushSizePreview;

	public BrushSizeDialog(Context paramContext, BrushSizeChangeCallback paramBrushSizeChangeCallback, int paramInt1)
	  {
	    super(paramContext);
	    this.callback = paramBrushSizeChangeCallback;
	    this.size = paramInt1;
	    getWindow().getAttributes().gravity = Gravity.BOTTOM|Gravity.CENTER;
	  }

	  protected void onCreate(Bundle paramBundle)
	  {
	    super.onCreate(paramBundle);
	    setContentView(R.layout.brushsizedialog);
	    setTitle(R.string.BRUSH_SIZE);
	    seekbar = (SeekBar)findViewById(R.id.brushSizeSlider);
	    seekbar.setProgress(size);
	    seekbar.setOnSeekBarChangeListener(this);
	    dismiss = (ImageButton)findViewById(R.id.brushsizedismissBtn);
	    dismiss.setOnClickListener(L1);
	    localBrushSizePreview = (BrushSizePreview)findViewById(R.id.brushSizeView);
	    localBrushSizePreview.setSizeAndColor(size);    
	  }
	  
	  public abstract interface BrushSizeChangeCallback
	  {
	    public abstract void onBrushSizeChange(int paramInt);
	  }
	  
		View.OnClickListener L1=new View.OnClickListener(){
			public void onClick(View v){		
				BrushSizeDialog.this.dismiss();
			};
		};

	@Override
	public void onProgressChanged(SeekBar seekbar, int arg1, boolean arg2) {
		// TODO Auto-generated method stub
		if (this.seekbar == seekbar){
	        this.size = arg1;
	        localBrushSizePreview.setSizeAndColor(size);
	        callback.onBrushSizeChange(arg1);
	    }
		
	}

	@Override
	public void onStartTrackingTouch(SeekBar arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void onStopTrackingTouch(SeekBar arg0) {
		// TODO Auto-generated method stub
		
	}

}
