package com.morphing.mormor;

import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentPagerAdapter;

/**
 * ×Ô¶¨ÒåfragmentÊÊÅäÆ÷
 * @author ZHF
 *
 */
public class MyFragmentPageAdapter extends FragmentPagerAdapter {


	public MyFragmentPageAdapter(android.support.v4.app.FragmentManager fm) {
		super(fm);
		// TODO Auto-generated constructor stub
	}
	@Override
    public int getCount() {
        return 9;
    }
	
    @Override
    public Fragment getItem(int position) {
                return MyFragment.newInstance(position);
    }
}