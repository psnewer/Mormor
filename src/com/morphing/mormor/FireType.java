package com.morphing.mormor;

import java.util.Arrays;

public class FireType {
	public int Type;
	public int[] wpoint1;
	public int[] wpoint2;
	public long seq;
	
	public FireType(int[] wpoint,long seq,int n){
		if(n==1){
			Type=1;
			wpoint1=Arrays.copyOf(wpoint, 2);
		}
		else if(n==2){
			Type=2;
			wpoint2=Arrays.copyOf(wpoint, 2);
			this.seq=seq;
		}
		else if(n==0){
			Type=0;
		}
	}

}
