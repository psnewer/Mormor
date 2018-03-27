package org.opencv.Mormor;

import android.app.Dialog;
import android.content.Context;
import android.os.Bundle;
import android.view.Gravity;
import android.view.View;
import android.view.Window;
import android.widget.CheckBox;
import android.widget.ImageButton;

public class EdgeprefDialog extends Dialog {
	
	 private EdgeprefCallback callback;
	 public ImageButton dismiss;
	 public CheckBox edgepref;
	 public boolean ischecked;
	 Context context;

	public EdgeprefDialog(Context paramContext, EdgeprefCallback paramBrushSizeChangeCallback)
	  {
	    super(paramContext);
	    this.context=paramContext;
	    this.callback = paramBrushSizeChangeCallback;
	    getWindow().getAttributes().gravity = Gravity.BOTTOM|Gravity.CENTER;
	    requestWindowFeature(Window.FEATURE_NO_TITLE);
	  }

	  protected void onCreate(Bundle paramBundle)
	  {
	    super.onCreate(paramBundle);
	    setContentView(R.layout.edgeprefdialog);
	    edgepref=(CheckBox) findViewById(R.id.Edgepref);
	    dismiss = (ImageButton)findViewById(R.id.Edgeprefdismiss);
	    dismiss.setOnClickListener(L1); 
	  }
	  
	  public abstract interface EdgeprefCallback
	  {
	    public abstract void onEdgepref(boolean paramBoolean);
	  }
	  
		View.OnClickListener L1=new View.OnClickListener(){
			public void onClick(View v){		
				EdgeprefDialog.this.dismiss();
				callback.onEdgepref(edgepref.isChecked());			
			};
		};

}
