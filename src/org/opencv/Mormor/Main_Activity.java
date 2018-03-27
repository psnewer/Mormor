package org.opencv.Mormor;

import com.morphing.mormor.MyFragmentPageAdapter;
import android.content.Intent;
import android.os.Bundle;
import android.support.v4.app.FragmentActivity;
import android.support.v4.view.ViewPager;
import android.support.v4.view.ViewPager.OnPageChangeListener;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
public class Main_Activity extends FragmentActivity implements OnPageChangeListener{
	
	ImageButton back;
	ImageButton forward;
	Button start;
	int current_ind;
	
    private ViewPager mViewPager;
    private MyFragmentPageAdapter mAdapter;
    private LinearLayout mIndicatorGroup;
    private ImageView[] mIndicatorImage;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main_activity);
        this.setTitle(R.string.TeachTitle);
        current_ind=0;
        initUI();		             
        initIndicator();
}
    
    
    private void initUI(){
		  forward=(ImageButton) findViewById(R.id.next);
		  forward.setOnClickListener(T1);
		  back=(ImageButton) findViewById(R.id.previous);
		  back.setOnClickListener(T1);
		  back.setVisibility(4);
		  start=(Button) findViewById(R.id.start);
		  start.setOnClickListener(T1);
		  mViewPager = (ViewPager) findViewById(R.id.viewpager);
		  mViewPager.setOnPageChangeListener(this);
	      mAdapter =  new MyFragmentPageAdapter(getSupportFragmentManager());               
	      mViewPager.setAdapter(mAdapter);
	      mViewPager.setCurrentItem(0);
	      mIndicatorGroup = (LinearLayout)findViewById(R.id.indicator_group);
	      mIndicatorImage = new ImageView[mAdapter.getCount()]; 
    }
    
    @SuppressWarnings("deprecation")
	private void initIndicator()  
    {  
        for (int i = 0; i < mAdapter.getCount(); i ++)  
        {  
            ImageView imageView = new ImageView(this);  
            imageView.setLayoutParams(new ViewGroup.LayoutParams(20,20));  
            imageView.setPadding(5, 5, 5, 5);  
            imageView.setImageResource(R.drawable.indicator);
            
            if (i == 0)  
            {  
            	imageView.setAlpha(255);
            } 
            else  
            {  
            	imageView.setAlpha(100);
            }  
            mIndicatorImage[i] = imageView;  
            mIndicatorGroup.addView(mIndicatorImage[i]);  
        }  
    }  
    
	  OnClickListener T1=new OnClickListener(){

			@Override
			public void onClick(View arg0) {
				// TODO Auto-generated method stub
				if(arg0==back&&current_ind>0)
				    mViewPager.setCurrentItem(current_ind-1);
				else if(arg0==forward&&current_ind<9)
					mViewPager.setCurrentItem(current_ind+1);
				else if(arg0==start){
					onJump(false);
				}
					
			};
		};
	@Override
	public void onPageScrollStateChanged(int arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void onPageScrolled(int arg0, float arg1, int arg2) {
		// TODO Auto-generated method stub
		
	}


	@SuppressWarnings("deprecation")
	@Override
	public void onPageSelected(int arg0) {
		// TODO Auto-generated method stub
		current_ind = arg0;
		
        for (int i = 0; i < mIndicatorImage.length; i ++)  
        {  
            if (i == arg0)  
            {  
            	mIndicatorImage[i].setAlpha(255);            	
            }  
            else  
            {  
            	mIndicatorImage[i].setAlpha(100);
            }  
        } 
        if (arg0 == 0)  
        {   
        	back.setVisibility(4);
        	forward.setVisibility(0);
        } 
        else if(arg0==8)
        { 
        	back.setVisibility(0);
        	forward.setVisibility(4);
        }  
        else
        {
        	back.setVisibility(0);
        	forward.setVisibility(0);
        }
	}
	
	
	public void onJump(boolean arg){
		Intent intent=new Intent();
		intent.putExtra("onback", arg);
        intent.setClass(Main_Activity.this, AnyMorphing.class);
        setResult(RESULT_OK, intent);        
        intent.addFlags(Intent.FLAG_ACTIVITY_SINGLE_TOP);
        intent.addFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);	 
        finish();
	}
	
	
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		// TODO Auto-generated method stub
		if (keyCode == KeyEvent.KEYCODE_BACK) {
            onJump(true);	
		}
		return super.onKeyDown(keyCode, event);
	}
    
}
