package org.opencv.Mormor;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.util.AttributeSet;
import android.view.View;

public class BrushSizePreview extends View{
	
	public int size;

	  public BrushSizePreview(Context paramContext)
	  {
	    super(paramContext);
	  }

	  public BrushSizePreview(Context paramContext, AttributeSet paramAttributeSet)
	  {
	    super(paramContext, paramAttributeSet);
	  }

	  protected void onDraw(Canvas paramCanvas)
	  {
		super.onDraw(paramCanvas);
	    Paint localPaint = new Paint();
	    localPaint.setDither(true);
	    localPaint.setAntiAlias(true);
	    localPaint.setColor(Color.WHITE);
	    localPaint.setStyle(Paint.Style.STROKE);
	    localPaint.setStrokeJoin(Paint.Join.ROUND);
	    localPaint.setStrokeCap(Paint.Cap.ROUND);
	    localPaint.setStrokeWidth(size);
	    float f3 = getWidth() / 2;
	    float f4 = getHeight() / 2;
	    paramCanvas.drawPoint(f3, f4, localPaint);
	  }

	  public void setSizeAndColor(int size)
	  {
	    this.size = size;
	    invalidate();
	  }

}
