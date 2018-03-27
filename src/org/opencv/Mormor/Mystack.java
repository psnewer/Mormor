package org.opencv.Mormor;

import java.util.Stack;

@SuppressWarnings("serial")
public class Mystack extends Stack<Mystackele> {
	public int current_ind;
	int bfdir;
	
	public Mystack(){
		current_ind=-1;
		bfdir=0;
	}
	
	public void removeRange(int ind1,int ind2){
		for(int i=ind1;i<ind2;i++){
			Mystackele ele=(Mystackele) this.get(i);
			if(ele.Lineobj_Indeed)
				ele.anymorphingdata.lineObj.delete();
				if(ele.Mor_Indeed)
					ele.anymorphingdata.mor.delete();
		}
		super.removeRange(ind1, ind2);
	}
	
	
	public void clear(){
		super.clear();
		current_ind=-1;
		bfdir=0;
	}

}
