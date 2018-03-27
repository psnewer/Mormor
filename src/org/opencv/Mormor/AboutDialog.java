package org.opencv.Mormor;

import android.app.Dialog;
import android.content.Context;
import android.os.Bundle;
import android.text.method.LinkMovementMethod;
import android.view.Gravity;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.TextView;


public class AboutDialog extends Dialog{
	
	ImageButton dismissButton;
	Button teach;
	private AboutCallback aboutcallback;
	TextView tv;

	public  AboutDialog(Context paramContext,AboutCallback aboutcallback)
	  {
	    super(paramContext);
	    this.aboutcallback=aboutcallback;
	    getWindow().getAttributes().gravity = Gravity.BOTTOM|Gravity.RIGHT;
	    requestWindowFeature(Window.FEATURE_NO_TITLE);
	  }

	
	protected void onCreate(Bundle paramBundle)
	  {
	    super.onCreate(paramBundle);
	    setContentView(R.layout.aboutlayout);
	    setTitle("About Mormor");
	    init_UI();
        WindowManager.LayoutParams lp=getWindow().getAttributes();
        lp.alpha=0.6f;
        getWindow().setAttributes(lp);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_DIM_BEHIND);
	  }
	
	
	public void init_UI(){
      dismissButton=(ImageButton) findViewById(R.id.aboutdismissBtn);
      dismissButton.setOnClickListener(T1);
      teach=(Button) findViewById(R.id.clearAllSettings);
      teach.setOnClickListener(T2);
      tv=(TextView)findViewById(R.id.aboutText);
      tv.setMovementMethod(LinkMovementMethod.getInstance());
	}
	
	
	public void dismiss(){
		super.dismiss();
		aboutcallback.onAboutDismiss();
	}
	
	android.view.View.OnClickListener T1=new View.OnClickListener(){
		public void onClick(View v){
			dismiss();	
		};
	};	
	
    android.view.View.OnClickListener T2=new View.OnClickListener(){
			public void onClick(View v){
				dismiss();
                aboutcallback.onJump();
			};
		};
	
		abstract interface AboutCallback
		  {
	        public abstract void onJump();
	        public abstract void onAboutDismiss();
		  }

}
