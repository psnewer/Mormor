package com.morphing.mormor;

import android.graphics.Path;

public class PathType {
	public int Type;
	public Path path;
	public boolean drawclear=false;
	
	public PathType(Path path,int n,boolean drawclear){
		this.path=path;
		Type=n;
		this.drawclear=drawclear;
	}

}
