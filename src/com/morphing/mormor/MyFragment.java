package com.morphing.mormor;

import org.opencv.Mormor.R;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
/**
 * 用于创建Fragment对象，作为ViewPager的叶片
 * @author ZHF
 *
 */
public class MyFragment extends Fragment {
                                                                                                                                                                                                                                                                                                                  
    int mNum; //页号
    public static MyFragment newInstance(int num) {
        MyFragment fragment = new MyFragment();
        Bundle args = new Bundle();
        args.putInt("num", num);
        fragment.setArguments(args);
        return fragment;
    }
    
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mNum = getArguments() != null ? getArguments().getInt("num") : 0;
    }
    
    /**为Fragment加载布局时调用**/
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
            Bundle savedInstanceState) {
                                                                                                                                                                                                                                                                                                                      
        View view=null;
        switch(mNum){
        case 0:
        	view=inflater.inflate(R.layout.teach1, container,false);
        	break;
        case 1:
        	view=inflater.inflate(R.layout.teach2, container,false);
        	break;
        case 2:
        	view=inflater.inflate(R.layout.teach3, container,false);
        	break;
        case 3:
        	view=inflater.inflate(R.layout.teach4, container,false);
        	break;
        case 4:
        	view=inflater.inflate(R.layout.teach5, container,false);
        	break;
        case 5:
        	view=inflater.inflate(R.layout.teach6, container,false);
        	break;
        case 6:
        	view=inflater.inflate(R.layout.teach7, container,false);
        	break;
        case 7:
        	view=inflater.inflate(R.layout.teach8, container,false);
        	break;
        case 8:
        	view=inflater.inflate(R.layout.teach9, container,false);
        	break;
        default:
        	break;     	
        }
        return view;
    }
}