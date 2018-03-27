
#include "mycpp.h"
#include <signal.h>




namespace cv{

double v[]={0,-1,1,0};
Mat rotate_90mat(2,2,CV_64FC1,v);

Morphing::Morphing()
	{
	  monitor=new int[18];
	  seq1=0;
	  seq2=0;
	  for(int i=0;i<=17;i++)
	  {
		  monitor[i]=1;
	  }
	}


Morphing::Morphing(Line_label* lineobj)
	{
	  this->lineobj=lineobj;
	  monitor=new int[18];
	  seq1=0;
	  seq2=0;
	  for(int i=0;i<=17;i++)
	  {
		  monitor[i]=1;
	  }
	  origin_regionmat.create(lineobj->pich,lineobj->picw,CV_8UC1);
	  new_regionmat.create(lineobj->pich,lineobj->picw,CV_8UC1);
	}


void Morphing::getaxis1(CvPoint pt1,CvPoint pt2,CvPoint pt3,int n)
{
	//鍘嬫爤
	release(16);

	Mat coordin1,coordin2,coordin3,_P1,_P2,P_,C__,A,B,C,A_,B_,C_;
	fpoint1=pt1;
	fpoint2=pt2;
	rpoint=pt3;

	A=getvector(pt1,pt3);
	B=getvector(pt2,pt3);
	C=getvector(pt1,pt2);


	gemm(rotate_90mat,A,1,0,0,A_,GEMM_1_T);
	gemm(rotate_90mat,B,1,0,0,B_,GEMM_1_T);
	gemm(rotate_90mat,C,1,0,0,C_,GEMM_1_T);

	int*  v1=new int[2];
	v1[0]=pt1.x;
	v1[1]=pt1.y;
	int*  v2=new int[2];
	v2[0]=pt2.x;
	v2[1]=pt2.y;
	int* v3=new int[2];
	v3[0]=pt3.x;
	v3[1]=pt3.y;
	P1=Mat(1,2,CV_32SC1,v1);
	P2=Mat(1,2,CV_32SC1,v2);
	Mat P3(1,2,CV_32SC1,v3);

	    int (*p)[2]=new int[(*seq).total][2];
		cvCvtSeqToArray(seq,p);
		Mat contour((*seq).total,2,CV_32SC1,p);

		 _P1=repeat(P1,(*seq).total,1);
		 _P2=repeat(P2,(*seq).total,1);

		subtract(contour,_P1,coordin1);
		subtract(contour,_P2,coordin2);

		subtract(P3,P1,P_);
		transpose(C_,C__);
		double* length=new double[3];
		length[0]=point_dist(pt1,pt3);
		length[1]=point_dist(pt2,pt3);
		P_.convertTo(P_,CV_64FC1);
		length[2]=std::abs(P_.dot(C__));
		if(length[2]==0)
			length[2]=1e-30;

		contour_origin_coordin.release();
		contour_origin_coordin.create((*seq).total,6,CV_64FC1);
		Mat temp;
		coordin1.convertTo(coordin1,CV_64FC1);
		coordin2.convertTo(coordin2,CV_64FC1);
		gemm(coordin1,A,1,0,0,temp);
		temp.copyTo(contour_origin_coordin.col(0));
		gemm(coordin2,B,1,0,0,temp);
		temp.copyTo(contour_origin_coordin.col(1));
		gemm(coordin1,C,1,0,0,temp);
		temp.copyTo(contour_origin_coordin.col(2));
		gemm(coordin1,A_,1,0,0,temp);
		temp.copyTo(contour_origin_coordin.col(3));
		gemm(coordin2,B_,1,0,0,temp);
		temp.copyTo(contour_origin_coordin.col(4));
		gemm(coordin1,C_,1,0,0,temp);
		temp.copyTo(contour_origin_coordin.col(5));

		double wa=*contour_origin_coordin.ptr<double>(10,0);

		if(n==1)
		{
			release(17);
			A1=A;
			B1=B;
			C1=C;
			_A1=A_;
			_B1=B_;
			_C1=C_;
			length11=length;
			contour_origin_coordin.copyTo(contour_origin_coordin1);
			rpoint1=pt3;
		}

		if(n==2)
		{
			release(18);
			D1=A;
			E1=B;
			C1=C;
			_D1=A_;
			_E1=B_;
			_C1=C_;
			length12=length;
			contour_origin_coordin.copyTo(contour_origin_coordin2);
			rpoint2=pt3;
		}
		delete[] p;
}



Mat getvector(CvPoint& pt1,CvPoint& pt2)
{
	Mat Vc;
	double va[]={pt1.x,pt1.y};
	double vb[]={pt2.x,pt2.y};
	Mat Va(2,1,CV_64FC1,va);
	Mat Vb(2,1,CV_64FC1,vb);
	subtract(Vb,Va,Vc);
	Mat arr;
	normalize(Vc,arr,1,0,NORM_L2);
	return arr;
}




void Morphing::getaxis2(CvPoint pt,int n)
{
	Mat A,B,A_,B_,P1_;
    A=getvector(fpoint1,pt);
	B=getvector(fpoint2,pt);
	gemm(rotate_90mat,A,1,0,0,A_,GEMM_1_T);
	gemm(rotate_90mat,B,1,0,0,B_,GEMM_1_T);
	C2=C1;
	_2C=_C1;

	int  v1[]={pt.x,pt.y};
	Mat P_(2,1,CV_32SC1,v1);
	transpose(P1,P1_);
	subtract(P_,P1_,P_);
	double* length=new double[3];
	length[0]=point_dist(fpoint1,pt);
	length[1]=point_dist(fpoint2,pt);
	P_.convertTo(P_,CV_64FC1);
	length[2]=std::abs(P_.dot(_2C));

	if(length[2]==0)
		length[2]=1e-30;
	bool IS_NEG;

if(n==1)
{
	A2=A;
	B2=B;
	_A2=A_;
	_B2=B_;
	length21=length;
	alpha1=acos(A1.dot(A2));
	alpha2=acos(B1.dot(B2));
	if(alpha1!=alpha1)
	{
		alpha1=0;
	}
	if(alpha2!=alpha2)
	{
		alpha2=0;
	}
	IS_NEG=Is_neg(A1,A2,alpha1);
	if(IS_NEG)
		alpha1=-alpha1;
	IS_NEG=Is_neg(B1,B2,alpha2);
	if(IS_NEG)
	alpha2=-alpha2;

	Mat l1(3,1,CV_64FC1,length11);
	Mat l2(3,1,CV_64FC1,length21);
	length_r1.create(3,1,CV_64FC1);
	divide(l2,l1,length_r1);
}
else if(n==2)
{
	D2=A;
	E2=B;
	_D2=A_;
	_E2=B_;
	length22=length;
	alpha4=acos(D1.dot(D2));
	alpha5=acos(E1.dot(E2));
	if(alpha4!=alpha4)
	{
		alpha4=0;
	}
	if(alpha5!=alpha5)
	{
		alpha5=0;
	}
	IS_NEG=Is_neg(D1,D2,alpha4);
	if(IS_NEG)
		alpha4=-alpha4;
	IS_NEG=Is_neg(E1,E2,alpha5);
	if(IS_NEG)
	alpha5=-alpha5;

	Mat l1(3,1,CV_64FC1,length12);
	Mat l2(3,1,CV_64FC1,length22);
	length_r2.create(3,1,CV_64FC1);
	divide(l2,l1,length_r2);
}

}




void Morphing::getpoint(int n)
{

	//鍘嬫爤

	Mat A,B,A_,B_,P1__,P2__,T1,T2,_W,T,value_aug1,W,_b,b,_CC,_length_r,WH;
	double a1[2];

    if(n==1)
    {
	   _CC=contour_origin_coordin1;
	   a1[0]=alpha1;
	   a1[1]=alpha2;
	   _length_r=repeat(length_r1,2,1);
	   *_length_r.ptr<double>(2,0)=1;
	   seq=seq1;
	   contour_origin_coordin1.copyTo(contour_origin_coordin);
	   rpoint=rpoint1;
	   A=A2;
	   B=B2;
	   A_=_A2;
	   B_=_B2;
    }
    else if(n==2)
    {
    	_CC=contour_origin_coordin2;
    	a1[0]=alpha4;
    	a1[1]=alpha5;
    	_length_r=repeat(length_r2,2,1);
    	*_length_r.ptr<double>(2,0)=1;
    	seq=seq2;
    	contour_origin_coordin2.copyTo(contour_origin_coordin);
    	rpoint=rpoint2;
    	A=D2;
    	B=E2;
    	A_=_D2;
    	B_=_E2;
    }

	Mat H;
	H.create(2,6,CV_64FC1);
    Mat alpha_(1,2,CV_64FC1,a1);
    Mat _alpha=repeat(alpha_,(*seq).total,1);

	double _synrtio[]={1,1,1,synrtio,synrtio,1};
	Mat __synrtio(6,1,CV_64FC1,_synrtio);
	multiply(_length_r,__synrtio,_length_r);
	contour_new_coordin.create(2,(*seq).total,CV_64FC1);

	transpose(P1,P1__);
	transpose(P2,P2__);
    P1__.convertTo(P1__,CV_64FC1);
    P2__.convertTo(P2__,CV_64FC1);

	double _exm1[]={pow(0.1,sig),pow(0.1,sig),pow(0.1,sig),pow(0.1,sig),pow(0.1,sig),pow(0.1,sig)};
	Mat exm1(6,1,CV_64FC1,_exm1);

	for(int i=1;i<(*seq).total-1;i++)
	{
		double w1=std::abs(*contour_origin_coordin.ptr<double>(i,3));
		double w2=std::abs(*contour_origin_coordin.ptr<double>(i,4));
		double w3=std::abs(*contour_origin_coordin.ptr<double>(i,5));
		double w[]={-w1,-w2,-w3,-w1,-w2,-w3};
		W=Mat(6,1,CV_64FC1,w);
		double sig1=std::abs(w3);
		if(sig1==0)
			sig1=1e-30;
		multiply(W,exm1,W);
		exp(W,W);
		
		double _value_aug1[]={P1__.dot(A),P2__.dot(B),P1__.dot(C1),P1__.dot(A_),P2__.dot(B_),P1__.dot(_C1)};
	    value_aug1=Mat(6,1,CV_64FC1,_value_aug1);
	    _b=_CC.row(i);
		transpose(_b,b);

		multiply(b,_length_r,b);
		add(b,value_aug1,b);
		multiply(W,b,b);

        A.copyTo(H.col(0));
        B.copyTo(H.col(1));
        C1.copyTo(H.col(2));
        A_.copyTo(H.col(3));
        B_.copyTo(H.col(4));
        _C1.copyTo(H.col(5));

		transpose(W,_W);
		WH=repeat(_W,2,1);
		multiply(H,WH,H);
		gemm(H,H,1,0,0,T1,GEMM_2_T);
		gemm(H,b,1,0,0,T2);
		invert(T1,T1);
		gemm(T1,T2,1,0,0,T);

		T.copyTo(contour_new_coordin.col(i));

		//閿熸枻鎷峰彇graspPoint;
		CvPoint gpt=*CV_GET_SEQ_ELEM(CvPoint,seq,i);
		if(gpt==rpoint){
			T.copyTo(graspPoint);
		}

	}

	*contour_new_coordin.ptr<double>(0,0)=(double)fpoint1.x;
	*contour_new_coordin.ptr<double>(1,0)=(double)fpoint1.y;
	*contour_new_coordin.ptr<double>(0,(*seq).total-1)=(double)fpoint2.x;
	*contour_new_coordin.ptr<double>(1,(*seq).total-1)=(double)fpoint2.y;

}


void Morphing::smoothcontour(int n,int cyn)
{

  contour_new_coordin.convertTo(contour_new_coordin,CV_64FC1,1,0);

  Mat current_neiborhood,center_point,A,U,V,S,projection,new_coordin,temp,current_point,RN,main_axis,norm_current_point;

for(int k=1;k<=cyn;++k)
  {

  for (int i=1;i<contour_new_coordin.cols-1;++i)
  {
     current_point=contour_new_coordin.col(i);
	 int t;
	 int left=i-n/2;
	 if(left<0)
	 {
		 t=i;
		 left=0;
	 }
	 else
		 t=n/2;
	 int right=i+n/2;
	 if(right>=contour_new_coordin.cols)
		 right=contour_new_coordin.cols-1;
	 int num_neibors=right-left+1;
	 current_neiborhood=contour_new_coordin.colRange(left,right+1);
	 center_point=current_neiborhood.col(0);
	 RN=repeat(center_point,1,num_neibors);
	 subtract(current_neiborhood,RN,A);
	 SVD::compute(A,S,U,V);
	 main_axis=U.col(0);
	 norm_current_point=A.col(t);
	 double point_new_coordin=main_axis.dot(norm_current_point);
	 double _temp[]={point_new_coordin,point_new_coordin};
	 temp=Mat(2,1,CV_64FC1,_temp);
     multiply(temp,main_axis,projection);
	 add(center_point,projection,new_coordin);

	 if(*current_point.ptr<double>(0,0)==*graspPoint.ptr<double>(0,0)&&*current_point.ptr<double>(1,0)==*graspPoint.ptr<double>(1,0))
	 {
		 new_coordin.copyTo(graspPoint);
	 }

	 new_coordin.copyTo(contour_new_coordin.col(i));
  }

}
}


bool Morphing::get_region2p()
{
	new_region.release();
	new_regionmat.setTo(0);

	Mat region_mat(lineobj->pich,lineobj->picw,CV_8UC1);
	region_mat = Scalar::all(0);
	Mat region_mat1(lineobj->pich,lineobj->picw,CV_8UC1);
    region_mat1 = Scalar::all(0);
    Mat contour_mat;
    Mat temp_mat(1,2,CV_32SC1);
	for (int i=0;i<contour_new_coordin1.cols;i++)
	{
		int l1=*contour_new_coordin1.ptr<int>(0,i);
		int r1=*contour_new_coordin1.ptr<int>(1,i);

			if(l1<0)
				l1=0;
			else if(l1>=lineobj->picw)
				l1=lineobj->picw-1;
			if(r1<0)
				r1=0;
			else if(r1>=lineobj->pich)
				r1=lineobj->pich-1;

		  if(*region_mat.ptr<uchar>(r1,l1)==0)
		    *region_mat.ptr<uchar>(r1,l1)=255;
		  else
		    *region_mat1.ptr<uchar>(r1,l1)=255;
		*temp_mat.ptr<int>(0,0)=l1;
		*temp_mat.ptr<int>(0,1)=r1;
		contour_mat.push_back(temp_mat);
     }

	LineIterator line_iterator(region_mat, fpoint1, fpoint2,8,0);
	for(int i=0;i<line_iterator.count;i++)
	   {
	   int offset, x, y;
	   offset = line_iterator.ptr - (uchar*)(region_mat.data);
       y = offset/region_mat.cols;
       x = (offset - y*region_mat.cols);
	   if(*region_mat.ptr<uchar>(y,x)==255)
	   {
           *temp_mat.ptr<int>(0,0)=x;
           *temp_mat.ptr<int>(0,1)=y;
           new_region.push_back(temp_mat);
	   }
	   *region_mat.ptr<uchar>(y,x)=255;
	   *region_mat1.ptr<uchar>(y,x)=255;
	   line_iterator++;
	   }

	//閿熸枻鎷烽敓鏂ゆ嫹firewall
	bitwise_or(region_mat,lineobj->fireWall,region_mat);
	getregion(contour_mat,region_mat,region_mat1,new_region,new_regionmat);
	if(new_region.rows>0&&new_region.cols>0)
	  return true;
	else
		return false;

}



bool Morphing::get_originregion2p()
{

        origin_region.release();
        origin_regionmat.setTo(0);
	    Mat region_mat(lineobj->pich,lineobj->picw,CV_8UC1);
	    region_mat = Scalar::all(0);
	    Mat region_mat1(lineobj->pich,lineobj->picw,CV_8UC1);
	    region_mat1 = Scalar::all(0);
	    Mat contour_mat;
	    Mat temp_mat(1,2,CV_32SC1);
	    CvPoint current_point;
		for (int i=0;i<(*seq1).total;i++)
		{
		   current_point=*CV_GET_SEQ_ELEM(CvPoint,seq1,i);
           *temp_mat.ptr<int>(0,0)=current_point.x;
           *temp_mat.ptr<int>(0,1)=current_point.y;
           contour_mat.push_back(temp_mat);
		   if(region_mat.at<uchar>(current_point)==0)
		           region_mat.at<uchar>(current_point)=255;
		   		else
		           region_mat1.at<uchar>(current_point)=255;
		}

		LineIterator line_iterator(region_mat, fpoint1, fpoint2,8,0);
		for(int i=0;i<line_iterator.count;i++)
		   {
		   int offset, x, y;
		   offset = line_iterator.ptr - (uchar*)(region_mat.data);
	       y = offset/region_mat.cols;
	       x = (offset - y*region_mat.cols);
		   if(*region_mat.ptr<uchar>(y,x)==255)
		   {
	           *temp_mat.ptr<int>(0,0)=x;
	           *temp_mat.ptr<int>(0,1)=y;
	           origin_region.push_back(temp_mat);
		   }
		   *region_mat.ptr<uchar>(y,x)=255;
		   *region_mat1.ptr<uchar>(y,x)=255;
		   line_iterator++;
		   }

//		bitwise_or(region_mat,lineobj->fireWall,region_mat);
		getregion(contour_mat,region_mat,region_mat1,origin_region,origin_regionmat);
		if(origin_region.rows>0&&origin_region.cols>0)
			  return true;
			else
				return false;
}


bool Morphing::get_originregion4p()
{

        origin_region.release();
        origin_regionmat.setTo(0);
        Mat region_mat(lineobj->pich,lineobj->picw,CV_8UC1);
		region_mat = Scalar::all(0);
		Mat region_mat1(lineobj->pich,lineobj->picw,CV_8UC1);
		region_mat1 = Scalar::all(0);
		Mat contour_mat;
		Mat temp_mat(1,2,CV_32SC1);
		CvPoint current_point;
	for (int i=0;i<(*seq1).total;i++)
	{
		current_point=*CV_GET_SEQ_ELEM(CvPoint,seq1,i);
        *temp_mat.ptr<int>(0,0)=current_point.x;
        *temp_mat.ptr<int>(0,1)=current_point.y;
        contour_mat.push_back(temp_mat);
		if(region_mat.at<uchar>(current_point)==0)
		{
           region_mat.at<uchar>(current_point)=255;
		}
		else
           region_mat1.at<uchar>(current_point)=255;
	}
	for (int i=(*seq2).total-1;i>=0;i--)
	{
		current_point=*CV_GET_SEQ_ELEM(CvPoint,seq2,i);
        *temp_mat.ptr<int>(0,0)=current_point.x;
        *temp_mat.ptr<int>(0,1)=current_point.y;
        contour_mat.push_back(temp_mat);
		if(region_mat.at<uchar>(current_point)==0)
           region_mat.at<uchar>(current_point)=255;
		else
           region_mat1.at<uchar>(current_point)=255;

	}

//	bitwise_or(region_mat,lineobj->fireWall,region_mat);

	getregion(contour_mat,region_mat,region_mat1,origin_region,origin_regionmat);
	if(origin_region.rows>0&&origin_region.cols>0)
	  return true;
	else
		return false;

}



bool Morphing::get_region4p()
{

	    new_region.release();
	    new_regionmat.setTo(0);
        Mat region_mat(lineobj->pich,lineobj->picw,CV_8UC1);
		region_mat = Scalar::all(0);
		Mat region_mat1(lineobj->pich,lineobj->picw,CV_8UC1);
		region_mat1 = Scalar::all(0);
		Mat contour_mat;
        Mat temp_mat(1,2,CV_32SC1);
	for (int i=0;i<contour_new_coordin1.cols;i++)
	{
		int l1=*contour_new_coordin1.ptr<int>(0,i);
		int r1=*contour_new_coordin1.ptr<int>(1,i);

			if(l1<0)
				l1=0;
			else if(l1>=lineobj->picw)
				l1=lineobj->picw-1;
			if(r1<0)
				r1=0;
			else if(r1>=lineobj->pich)
				r1=lineobj->pich-1;
	    if(*region_mat.ptr<uchar>(r1,l1)==0)
          *region_mat.ptr<uchar>(r1,l1)=255;
	    else
          *region_mat1.ptr<uchar>(r1,l1)=255;
	    *temp_mat.ptr<int>(0,0)=l1;
	    *temp_mat.ptr<int>(0,1)=r1;
		contour_mat.push_back(temp_mat);
	}
	for (int i=contour_new_coordin2.cols-1;i>=0;i--)
	{
		int l1=*contour_new_coordin2.ptr<int>(0,i);
		int r1=*contour_new_coordin2.ptr<int>(1,i);

			if(l1<0)
				l1=0;
			else if(l1>=lineobj->picw)
				l1=lineobj->picw-1;

			if(r1<0)
				r1=0;
			else if(r1>=lineobj->pich)
				r1=lineobj->pich-1;

	    if(*region_mat.ptr<uchar>(r1,l1)==0)
           *region_mat.ptr<uchar>(r1,l1)=255;
	    else
           *region_mat1.ptr<uchar>(r1,l1)=255;
	    *temp_mat.ptr<int>(0,0)=l1;
	    *temp_mat.ptr<int>(0,1)=r1;
		contour_mat.push_back(temp_mat);
	}

	bitwise_or(region_mat,lineobj->fireWall,region_mat);

	getregion(contour_mat,region_mat,region_mat1,new_region,new_regionmat);
	if(new_region.rows>0&&new_region.cols>0)
	    return true;
	else
		return false;

}



void Morphing:: get_leftregion()
{
	   Mat origin_regionleft;
	   left_region.release();
	   bitwise_and(new_regionmat,origin_regionmat,origin_regionleft);
	   bitwise_xor(origin_regionleft,origin_regionmat,origin_regionleft);

	   for(int i=0;i<origin_region.rows;i++)
	   {
		  Mat current_point=origin_region.row(i);
		  int x1=*current_point.ptr<int>(0,0);
		  int y1=*current_point.ptr<int>(0,1);
		  if(*origin_regionleft.ptr<uchar>(y1,x1)>0)
		  {
			 left_region.push_back(current_point);

			   Mat pt(1,2,CV_32SC1);
			   int x,y;
			   if(*lineobj->_edge.ptr<uchar>(y1,x1)>0)
			   {
				 for(int j=1;j<=2;j++)
				  {
				   x=x1-j;
				   y=y1;
				   if(x>=0)
				   if(*origin_regionleft.ptr<uchar>(y,x)==0)
				   {
					   *pt.ptr<int>(0,0)=x;
					   *pt.ptr<int>(0,1)=y;
					   left_region.push_back(pt);
					   *origin_regionleft.ptr<uchar>(y,x)=1;
				   }
				   x=x1+j;
				   y=y1;
				   if(x<origin_regionleft.cols)
				   if(*origin_regionleft.ptr<uchar>(y,x)==0)
				   {
					   *pt.ptr<int>(0,0)=x;
					   *pt.ptr<int>(0,1)=y;
					   left_region.push_back(pt);
					   *origin_regionleft.ptr<uchar>(y,x)=1;
				   }
				   x=x1;
				   y=y1-j;
				   if(y>=0)
				   if(*origin_regionleft.ptr<uchar>(y,x)==0)
				   {
					   *pt.ptr<int>(0,0)=x;
					   *pt.ptr<int>(0,1)=y;
					   left_region.push_back(pt);
					   *origin_regionleft.ptr<uchar>(y,x)=1;
				   }
				   x=x1;
				   y=y1+j;
				   if(y<origin_regionleft.rows)
				   if(*origin_regionleft.ptr<uchar>(y,x)==0)
				   {
					   *pt.ptr<int>(0,0)=x;
					   *pt.ptr<int>(0,1)=y;
					   left_region.push_back(pt);
					   *origin_regionleft.ptr<uchar>(y,x)=1;
				   }
			   }

			   }
		  }
	   }

}



void Morphing::getregion(Mat& contour_mat,Mat& region_mat,Mat& region_mat1,Mat& region,Mat& mat_region)
{
	int sig=0;
	bool inner_point_clear=false;
    int n1;
	int inner_point[2];
  if(*lineobj->fireWall.ptr<uchar>(*contour_mat.ptr<int>(0,1),*contour_mat.ptr<int>(0,0))==0)
	{
	for(n1=1;n1<contour_mat.rows-1;n1++)
	{
		sig=n1;
		if(*lineobj->fireWall.ptr<uchar>(*contour_mat.ptr<int>(n1,1),*contour_mat.ptr<int>(n1,0))==255)
			break;
		if(*region_mat1.ptr<uchar>(*contour_mat.ptr<int>(n1,1),*contour_mat.ptr<int>(n1,0))==255)
		    continue;
		if(*region_mat.ptr<uchar>(*contour_mat.ptr<int>(n1,1),*contour_mat.ptr<int>(n1,0))==255)
		{
		    region.push_back(contour_mat.row(n1));
		    *mat_region.ptr<uchar>(*contour_mat.ptr<int>(n1,1),*contour_mat.ptr<int>(n1,0))==1;
		}
	int n2,n3;
	if(n1>0)
	{
		n2=n1-1;;
	}
	if(n1<contour_mat.rows-1)
	{
		n3=n1+1;
	}

	int a1[]={*contour_mat.ptr<int>(n1,0),*contour_mat.ptr<int>(n1,1)};
	int a2[]={*contour_mat.ptr<int>(n2,0),*contour_mat.ptr<int>(n2,1)};
	int a3[]={*contour_mat.ptr<int>(n3,0),*contour_mat.ptr<int>(n3,1)};

	int t1,t2;
	if((a1[0]-a2[0])*(a1[0]-a3[0])<0)//閿熸枻鎷烽敓閾版唻鎷烽敓鏂ゆ嫹
	{
       t1=a1[1]-1;
       t2=a1[1]+1;
       if(t1>=0)
    	   if(*mat_region.ptr<uchar>(t1,a1[0])>0||*region_mat.ptr<uchar>(t1,a1[0])>0)
    		   continue;
       if(t2<region_mat.rows)
    	   if(*mat_region.ptr<uchar>(t2,a1[0])>0||*region_mat.ptr<uchar>(t2,a1[0])>0)
    		   continue;
	   while(--t1>=0)
	   {
		   if(*region_mat.ptr<uchar>(t1,a1[0])>0||*mat_region.ptr<uchar>(t1,a1[0])>0)
			   break;
	   }
	   if(t1>=0)
	   {
		   while(++t2<=region_mat.rows-1)
		   {
			   if(*region_mat.ptr<uchar>(t2,a1[0])>0||*mat_region.ptr<uchar>(t2,a1[0])>0)
				   break;
		   }
	   }
	   if(t1==-1)
	   {
         inner_point[0]=a1[0];
		 inner_point[1]=a1[1]+1;
		 inner_point_clear=true;
	   }
	   else if(t2==region_mat.rows)
	   {
		   inner_point[0]=a1[0];
		   inner_point[1]=a1[1]-1;
		   inner_point_clear=true;
	   }

	}
	else if((a1[1]-a2[1])*(a1[1]-a3[1])<0)//閿熸枻鎷烽敓鎻唻鎷烽敓鏂ゆ嫹
	{
		t1=a1[0]-1;
		t2=a1[0]+1;
		if(t1>=0)
			if(*mat_region.ptr<uchar>(a1[1],t1)>0||*region_mat.ptr<uchar>(a1[1],t1)>0)
				continue;
		if(t2<region_mat.cols)
			if(*mat_region.ptr<uchar>(a1[1],t2)>0||*region_mat.ptr<uchar>(a1[1],t2)>0)
				continue;
	   while(--t1>=0)
	   {
		   if(*region_mat.ptr<uchar>(a1[1],t1)>0||*mat_region.ptr<uchar>(a1[1],t1)>0)
			   break;
	   }
	   if(t1>=0)
	   {
		   while(++t2<=region_mat.cols-1)
		   {
				   if(*region_mat.ptr<uchar>(a1[1],t2)>0||*mat_region.ptr<uchar>(a1[1],t2)>0)
				   break;
		   }
	   }
	   if(t1==-1)
	   {
         inner_point[0]=a1[0]+1;
		 inner_point[1]=a1[1];
		 inner_point_clear=true;
	   }
	   else if(t2==region_mat.cols)
	   {
		   inner_point[0]=a1[0]-1;
		   inner_point[1]=a1[1];
		   inner_point_clear=true;
	   }

	}

	if(inner_point_clear&&*region_mat1.ptr<uchar>(a1[1],a1[0])==0)
	{
	Mat temp_mat(1,2,CV_32SC1,inner_point);
	region.push_back(temp_mat);
	*mat_region.ptr<uchar>(inner_point[1],inner_point[0])=1;
	int* point1=new int[2];
	point1[0]=inner_point[0]-1;
	point1[1]=inner_point[1];
	int* point2=new int[2];
	point2[0]=inner_point[0]+1;
	point2[1]=inner_point[1];
	int* point3=new int[2];
	point3[0]=inner_point[0];
	point3[1]=inner_point[1]-1;
	int* point4=new int[2];
	point4[0]=inner_point[0];
	point4[1]=inner_point[1]+1;
	if(point1[0]>=0)
	get_innerpoint(region_mat,region,mat_region,point1,1);
	if(point2[0]<region_mat.cols)
	get_innerpoint(region_mat,region,mat_region,point2,2);
	if(point3[1]>=0)
	get_innerpoint(region_mat,region,mat_region,point3,3);
	if(point4[1]<region_mat.rows)
	get_innerpoint(region_mat,region,mat_region,point4,4);
	}
	inner_point_clear=false;
}
}

  if(*lineobj->fireWall.ptr<uchar>(*contour_mat.ptr<int>(contour_mat.rows-1,1),*contour_mat.ptr<int>(contour_mat.rows-1,0))==0)
   {
    inner_point_clear=false;
	for(n1=contour_mat.rows-2;n1>sig;n1--)
	{
		if(*lineobj->fireWall.ptr<uchar>(*contour_mat.ptr<int>(n1,1),*contour_mat.ptr<int>(n1,0))==255)
			break;
		if(*region_mat1.ptr<uchar>(*contour_mat.ptr<int>(n1,1),*contour_mat.ptr<int>(n1,0))==255)
		   continue;
		if(*region_mat.ptr<uchar>(*contour_mat.ptr<int>(n1,1),*contour_mat.ptr<int>(n1,0))==255)
		{
		    region.push_back(contour_mat.row(n1));
		    *mat_region.ptr<uchar>(*contour_mat.ptr<int>(n1,1),*contour_mat.ptr<int>(n1,0))==1;
		}
	int n2,n3;
	if(n1>0)
	{
		n2=n1-1;;
	}
	if(n1<contour_mat.rows-1)
	{
		n3=n1+1;
	}

	int a1[]={*contour_mat.ptr<int>(n1,0),*contour_mat.ptr<int>(n1,1)};
	int a2[]={*contour_mat.ptr<int>(n2,0),*contour_mat.ptr<int>(n2,1)};
	int a3[]={*contour_mat.ptr<int>(n3,0),*contour_mat.ptr<int>(n3,1)};

	int t1,t2;
	if((a1[0]-a2[0])*(a1[0]-a3[0])<0)//閿熸枻鎷烽敓閾版唻鎷烽敓鏂ゆ嫹
	{
       t1=a1[1]-1;
       t2=a1[1]+1;
       if(t1>=0)
    	   if(*mat_region.ptr<uchar>(t1,a1[0])>0||*region_mat.ptr<uchar>(t1,a1[0])>0)
    		   continue;
       if(t2<region_mat.rows)
    	   if(*mat_region.ptr<uchar>(t2,a1[0])>0||*region_mat.ptr<uchar>(t2,a1[0])>0)
    		   continue;
	   while(--t1>=0)
	   {
		   if(*region_mat.ptr<uchar>(t1,a1[0])>0||*mat_region.ptr<uchar>(t1,a1[0])>0)
			   break;
	   }
	   if(t1>=0)
	   {

		   while(++t2<=region_mat.rows-1)
		   {
			   if(*region_mat.ptr<uchar>(t2,a1[0])>0||*mat_region.ptr<uchar>(t2,a1[0])>0)
				   break;
		   }
	   }
	   if(t1==-1)
	   {
         inner_point[0]=a1[0];
		 inner_point[1]=a1[1]+1;
		 inner_point_clear=true;
	   }
	   else if(t2==region_mat.rows)
	   {
		   inner_point[0]=a1[0];
		   inner_point[1]=a1[1]-1;
		   inner_point_clear=true;
	   }

	}
	else if((a1[1]-a2[1])*(a1[1]-a3[1])<0)//閿熸枻鎷烽敓鎻唻鎷烽敓鏂ゆ嫹
	{
		t1=a1[0]-1;
		t2=a1[0]+1;
		if(t1>=0)
			if(*mat_region.ptr<uchar>(a1[1],t1)>0||*region_mat.ptr<uchar>(a1[1],t1)>0)
				continue;
		if(t2<region_mat.cols)
			if(*mat_region.ptr<uchar>(a1[1],t2)>0||*region_mat.ptr<uchar>(a1[1],t2)>0)
				continue;
	   while(--t1>=0)
	   {
		   if(*region_mat.ptr<uchar>(a1[1],t1)>0||*mat_region.ptr<uchar>(a1[1],t1)>0)
			   break;
	   }
	   if(t1>=0)
	   {

		   while(++t2<=region_mat.cols-1)
		   {
				   if(*region_mat.ptr<uchar>(a1[1],t2)>0||*mat_region.ptr<uchar>(a1[1],t2)>0)
				   break;
		   }
	   }
	   if(t1==-1)
	   {
         inner_point[0]=a1[0]+1;
		 inner_point[1]=a1[1];
	     inner_point_clear=true;
	   }
	   else if(t2==region_mat.cols)
	   {
		   inner_point[0]=a1[0]-1;
		   inner_point[1]=a1[1];
		   inner_point_clear=true;
	   }

	}

	if(inner_point_clear&&*region_mat1.ptr<uchar>(a1[1],a1[0])==0)
	{
	Mat temp_mat(1,2,CV_32SC1,inner_point);
	region.push_back(temp_mat);
	*mat_region.ptr<uchar>(inner_point[1],inner_point[0])=1;
	int* point1=new int[2];
	point1[0]=inner_point[0]-1;
	point1[1]=inner_point[1];
	int* point2=new int[2];
	point2[0]=inner_point[0]+1;
	point2[1]=inner_point[1];
	int* point3=new int[2];
	point3[0]=inner_point[0];
	point3[1]=inner_point[1]-1;
	int* point4=new int[2];
	point4[0]=inner_point[0];
	point4[1]=inner_point[1]+1;
	if(point1[0]>=0)
	get_innerpoint(region_mat,region,mat_region,point1,1);
	if(point2[0]<region_mat.cols)
	get_innerpoint(region_mat,region,mat_region,point2,2);
	if(point3[1]>=0)
	get_innerpoint(region_mat,region,mat_region,point3,3);
	if(point4[1]<region_mat.rows)
	get_innerpoint(region_mat,region,mat_region,point4,4);
	}
	inner_point_clear=false;
}
}

}




void Morphing::get_innerpoint(Mat& region_mat,Mat& region,Mat& mat_region,int* point,int n)
{
	Mat point_inner(1,2,CV_32SC1);
	vector<int*> vec1,vec2,vec3,vec4;
	if(n==1)
		vec1.push_back(point);
	else if(n==2)
		vec2.push_back(point);
	else if(n==3)
		vec3.push_back(point);
	else if(n==4)
		vec4.push_back(point);
	while(!vec1.empty()||!vec2.empty()||!vec3.empty()||!vec4.empty())
	{
		while(!vec1.empty()){
			int* point1=vec1.back();
			vec1.pop_back();

		    if(*region_mat.ptr<uchar>(point1[1],point1[0])==255)
			{
				*point_inner.ptr<int>(0,0)=point1[0];
				*point_inner.ptr<int>(0,1)=point1[1];
				region.push_back(point_inner);
				*mat_region.ptr<uchar>(point1[1],point1[0])=1;
			}
		    else if(*mat_region.ptr<uchar>(point1[1],point1[0])==0)
			{
				*point_inner.ptr<int>(0,0)=point1[0];
			    *point_inner.ptr<int>(0,1)=point1[1];
				region.push_back(point_inner);
				*mat_region.ptr<uchar>(point1[1],point1[0])=1;

				int* point11=new int[2];
				point11[0]=point1[0]-1;
				point11[1]=point1[1];
				int* point12=new int[2];
				point12[0]=point1[0];
				point12[1]=point1[1]-1;
				int* point13=new int[2];
				point13[0]=point1[0];
				point13[1]=point1[1]+1;
				if(point11[0]>=0)
				 vec1.push_back(point11);
				else
					delete[] point11;
				if(point12[1]>=0)
				 vec3.push_back(point12);
				else
					delete[] point12;
				if(point13[1]<region_mat.rows)
				 vec4.push_back(point13);
				else
					delete[] point13;
			}
			delete[] point1;
		}
		while(!vec2.empty()){
			int* point2=vec2.back();
			vec2.pop_back();

			if(*region_mat.ptr<uchar>(point2[1],point2[0])==255)
				{
					*point_inner.ptr<int>(0,0)=point2[0];
					*point_inner.ptr<int>(0,1)=point2[1];
					region.push_back(point_inner);
					*mat_region.ptr<uchar>(point2[1],point2[0])=1;
				}
			else if(*mat_region.ptr<uchar>(point2[1],point2[0])==0)
			{
				*point_inner.ptr<int>(0,0)=point2[0];
				*point_inner.ptr<int>(0,1)=point2[1];
				region.push_back(point_inner);1;
				*mat_region.ptr<uchar>(point2[1],point2[0])=1;

				int* point21=new int[2];
				point21[0]=point2[0]+1;
				point21[1]=point2[1];
			    int* point22=new int[2];
			    point22[0]=point2[0];
			    point22[1]=point2[1]-1;
				int* point23=new int[2];
				point23[0]=point2[0];
				point23[1]=point2[1]+1;
				if(point21[0]<region_mat.cols)
				  vec2.push_back(point21);
				else
					delete[] point21;
				if(point22[1]>=0)
				  vec3.push_back(point22);
				else
					delete[] point22;
				if(point23[1]<region_mat.rows)
				  vec4.push_back(point23);
				else
					delete[] point23;
			}
			delete[] point2;
		}
		while(!vec3.empty()){
			int* point3=vec3.back();
			vec3.pop_back();

			if(*region_mat.ptr<uchar>(point3[1],point3[0])==255)
				{
				    *point_inner.ptr<int>(0,0)=point3[0];
					*point_inner.ptr<int>(0,1)=point3[1];
					region.push_back(point_inner);
					*mat_region.ptr<uchar>(point3[1],point3[0])=1;
				}
			else if(*mat_region.ptr<uchar>(point3[1],point3[0])==0)
			{
				*point_inner.ptr<int>(0,0)=point3[0];
				*point_inner.ptr<int>(0,1)=point3[1];
				region.push_back(point_inner);
				*mat_region.ptr<uchar>(point3[1],point3[0])=1;

			    int* point31=new int[2];
			    point31[0]=point3[0];
			    point31[1]=point3[1]-1;
			    int* point32=new int[2];
			    point32[0]=point3[0]-1;
			    point32[1]=point3[1];
			    int* point33=new int[2];
			    point33[0]=point3[0]+1;
			    point33[1]=point3[1];
			    if(point31[1]>=0)
			     vec3.push_back(point31);
			    else
			    	delete[] point31;
			    if(point32[0]>=0)
			     vec1.push_back(point32);
			    else
			    	delete[] point32;
			    if(point33[0]<region_mat.cols)
			     vec2.push_back(point33);
			    else
			    	delete[] point33;
			}
			delete[] point3;
		}
		while(!vec4.empty()){
			int* point4=vec4.back();
			vec4.pop_back();

			if(*region_mat.ptr<uchar>(point4[1],point4[0])==255)
				{
				  *point_inner.ptr<int>(0,0)=point4[0];
				  *point_inner.ptr<int>(0,1)=point4[1];
				  region.push_back(point_inner);
				  *mat_region.ptr<uchar>(point4[1],point4[0])=1;
				}
			else if(*mat_region.ptr<uchar>(point4[1],point4[0])==0)
			{
				*point_inner.ptr<int>(0,0)=point4[0];
				*point_inner.ptr<int>(0,1)=point4[1];
				region.push_back(point_inner);
				*mat_region.ptr<uchar>(point4[1],point4[0])=1;

				int* point41=new int[2];
				point41[0]=point4[0];
				point41[1]=point4[1]+1;
				int* point42=new int[2];
				point42[0]=point4[0]-1;
				point42[1]=point4[1];
				int* point43=new int[2];
				point43[0]=point4[0]+1;
				point43[1]=point4[1];
				if(point41[1]<region_mat.rows)
				 vec4.push_back(point41);
				else
					delete[] point41;
				if(point42[0]>=0)
				 vec1.push_back(point42);
				else
					delete[] point42;
				if(point43[0]<region_mat.cols)
				 vec2.push_back(point43);
				else
					delete[] point43;
			}
			delete[] point4;
		}
	}
}



void Morphing::inpute_region4p(int n)
{
	Mat target_region;

	if(n==1)
	{
		target_region=new_region;
	}
	else if(n==2)
	{
		target_region=left_region;
	}

	Mat H,P1__,P2__,_P1,_P2;
	H.create(2,8,CV_64FC1);
	Mat(A1).copyTo(H.col(0));
	Mat(B1).copyTo(H.col(1));
	Mat(D1).copyTo(H.col(2));
	Mat(E1).copyTo(H.col(3));
	Mat(_A1).copyTo(H.col(4));
	Mat(_B1).copyTo(H.col(5));
	Mat(_D1).copyTo(H.col(6));
	Mat(_E1).copyTo(H.col(7));

	transpose(P1,P1__);
	transpose(P2,P2__);
	_P1=repeat(P1,target_region.rows,1);
	_P2=repeat(P2,target_region.rows,1);
	P1__.convertTo(P1__,CV_64FC1);
	P2__.convertTo(P2__,CV_64FC1);
	double _value_aug2[]={P1__.dot(A1),P2__.dot(B1),P1__.dot(D1),P2__.dot(E1),P1__.dot(_A1),P2__.dot(_B1),P1__.dot(_D1),P2__.dot(_E1)};
	Mat value_aug2(8,1,CV_64FC1,_value_aug2);
	 double length_2r[]={length21[0],length21[1],length22[0],length22[1]};
	 double length_1r[]={length11[0],length11[1],length12[0],length12[1]};
	Mat l1(1,4,CV_64FC1,length_1r);
	Mat l2(1,4,CV_64FC1,length_2r);
	Mat length_r4p;
	divide(l2,l1,length_r4p);
	transpose(length_r4p,length_r4p);

	Mat _length_r=repeat(length_r4p,2,1);
	double _synrtio[]={1,1,1,1,synrtio,synrtio,synrtio,synrtio};
	Mat __synrtio(8,1,CV_64FC1,_synrtio);
	multiply(_length_r,__synrtio,_length_r);

	//閸掓湹缍旈崸鎰垼
	Mat a1,b1,_W1,W1_,_W2,W2_,_W4,W4_,_W5,W5_;
	subtract(target_region,_P1,a1);
	a1.convertTo(a1,CV_64FC1);
	subtract(target_region,_P2,b1);
	b1.convertTo(b1,CV_64FC1);
	gemm(a1,A2,1,0,0,_W1);
	gemm(a1,_A2,1,0,0,W1_);
	gemm(b1,B2,1,0,0,_W2);
	gemm(b1,_B2,1,0,0,W2_);
	gemm(a1,D2,1,0,0,_W4);
	gemm(a1,_D2,1,0,0,W4_);
	gemm(b1,E2,1,0,0,_W5);
	gemm(b1,_E2,1,0,0,W5_);

	double _exm1[]={pow(0.1,sig),pow(0.1,sig),pow(0.1,sig),pow(0.1,sig),pow(0.1,sig),pow(0.1,sig)};
    Mat exm1(8,1,CV_64FC1,_exm1);

	map_region.create(2,target_region.rows,CV_32SC1);

	Mat W,b,_W,T1,T2,T,WH,_H;
	for(int i=0;i<target_region.rows;i++)
	{

		double _w1=*_W1.ptr<double>(i,0);
		double w1_=*W1_.ptr<double>(i,0);
		double _w2=*_W2.ptr<double>(i,0);
		double w2_=*W2_.ptr<double>(i,0);
		double _w4=*_W4.ptr<double>(i,0);
		double w4_=*W4_.ptr<double>(i,0);
		double _w5=*_W5.ptr<double>(i,0);
		double w5_=*W5_.ptr<double>(i,0);

		double w1=std::abs(w1_);
		double w2=std::abs(w2_);
		double w4=std::abs(w4_);
		double w5=std::abs(w5_);
		double w[]={-w1,-w2,-w4,-w5,-w1,-w2,-w4,-w5};
		W=Mat(8,1,CV_64FC1,w);

		multiply(W,exm1,W);
		exp(W,W);

		double _b[]={_w1,_w2,_w4,_w5,w1_,w2_,w4_,w5_};
		b=Mat(8,1,CV_64FC1,_b);
		divide(b,_length_r,b);
		add(b,value_aug2,b);
		multiply(W,b,b);

		transpose(W,_W);
		WH=repeat(_W,2,1);
		multiply(H,WH,_H);

		gemm(_H,_H,1,0,0,T1,GEMM_2_T);
		gemm(_H,b,1,0,0,T2);
		invert(T1,T1);
		gemm(T1,T2,1,0,0,T);
		*map_region.ptr<int>(0,i)=cvRound(*T.ptr<double>(0,0));
		*map_region.ptr<int>(1,i)=cvRound(*T.ptr<double>(1,0));

	}

}



void Morphing::inpute_region2p(int n)
{
	Mat target_region;
	if(n==1)
	{
		target_region=new_region;
	}
	else if(n==2)
	{
		target_region=left_region;
	}

	Mat H,_H;
	H.create(2,6,CV_64FC1);
	A1.copyTo(H.col(0));
	B1.copyTo(H.col(1));
	C1.copyTo(H.col(2));
	_A1.copyTo(H.col(3));
	_B1.copyTo(H.col(4));
	_C1.copyTo(H.col(5));

	Mat P1__,P2__,_P1,_P2;
	transpose(P1,P1__);
	transpose(P2,P2__);
	_P1=repeat(P1,target_region.rows,1);
	_P2=repeat(P2,target_region.rows,1);
	P1__.convertTo(P1__,CV_64FC1);
	P2__.convertTo(P2__,CV_64FC1);
	double _value_aug2[]={P1__.dot(A1),P2__.dot(B1),P1__.dot(C1),P1__.dot(_A1),P2__.dot(_B1),P1__.dot(_C1)};
	Mat value_aug2(6,1,CV_64FC1,_value_aug2);

	double _synrtio[]={1,1,1,synrtio,synrtio,1};
	Mat __synrtio(6,1,CV_64FC1,_synrtio);
	Mat _length_r=repeat(length_r1,2,1);
	*_length_r.ptr<double>(2,0)=1;
	if(n==2)
		*_length_r.ptr<double>(5,0)=1;
	multiply(_length_r,__synrtio,_length_r);

	//閸掓湹缍旈崸鎰垼
	Mat a1,b1,_W1,W1_,_W2,W2_,_W3,W3_;
	subtract(target_region,_P1,a1);
	a1.convertTo(a1,CV_64FC1);
	subtract(target_region,_P2,b1);
	b1.convertTo(b1,CV_64FC1);
	gemm(a1,A2,1,0,0,_W1);
	gemm(a1,_A2,1,0,0,W1_);
	gemm(b1,B2,1,0,0,_W2);
	gemm(b1,_B2,1,0,0,W2_);
	gemm(a1,C2,1,0,0,_W3);
	gemm(a1,_2C,1,0,0,W3_);

	double _exm1[]={pow(0.1,sig),pow(0.1,sig),pow(0.1,sig),pow(0.1,sig),pow(0.1,sig),pow(0.1,sig)};
    Mat exm1(6,1,CV_64FC1,_exm1);

	map_region.create(2,target_region.rows,CV_32SC1);

	Mat W,b,_W,T1,T2,T;
	for(int i=0;i<target_region.rows;i++)
	{

		double _w1=*_W1.ptr<double>(i,0);
		double w1_=*W1_.ptr<double>(i,0);
		double _w2=*_W2.ptr<double>(i,0);
		double w2_=*W2_.ptr<double>(i,0);
		double _w3=*_W3.ptr<double>(i,0);
		double w3_=*W3_.ptr<double>(i,0);

		double w1=std::abs(w1_);
		double w2=std::abs(w2_);
		double w3=std::abs(w3_);
		double w[]={-w1,-w2,-w3,-w1,-w2,-w3};
		W=Mat(6,1,CV_64FC1,w);
		multiply(W,exm1,W);
		exp(W,W);

		double _b[]={_w1,_w2,_w3,w1_,w2_,w3_};
		b=Mat(6,1,CV_64FC1,_b);

		divide(b,_length_r,b);

		add(b,value_aug2,b);

		multiply(W,b,b);

		transpose(W,_W);
		Mat WH=repeat(_W,2,1);
		multiply(H,WH,_H);

		gemm(_H,_H,1,0,0,T1,GEMM_2_T);
		gemm(_H,b,1,0,0,T2);
		invert(T1,T1);
		gemm(T1,T2,1,0,0,T);
		*map_region.ptr<int>(0,i)=cvRound(*T.ptr<double>(0,0));
		*map_region.ptr<int>(1,i)=cvRound(*T.ptr<double>(1,0));

	}
}





bool Is_neg(Mat& arr1,Mat& arr2,double alpha)
{
	Mat c,IS;
	double a[]={cos(alpha),sin(alpha),-sin(alpha),cos(alpha)},_c[2],_IS[2];
	Mat b(2,2,CV_64FC1,a);
	gemm(b,arr1,1,0,0,c,GEMM_1_T);
	absdiff(arr2,c,IS);
	double sum=cv::sum(IS).val[0];
	if(sum<0.001)
		return false;
	else
		return true;
}



Mat linization(Mat& src)
{
	CvPoint pt1,pt2;
	CvMemStorage* storage=cvCreateMemStorage(0);
	CvSeq* seq=cvCreateSeq(CV_SEQ_ELTYPE_POINT,sizeof(CvSeq),sizeof(CvPoint),storage);
	CvSeq* seq1;
	for (int i=0;i<src.cols-1;i++)
	{	  
      pt1.x=cvRound(*src.ptr<double>(0,i));
	  pt1.y=cvRound(*src.ptr<double>(1,i));
	  pt2.x=cvRound(*src.ptr<double>(0,i+1));
	  pt2.y=cvRound(*src.ptr<double>(1,i+1));
	  cvSeqPush(seq,&pt1);
	  seq1=linear_link(pt1,pt2,false);
	  cvSeqInsertSlice(seq,(*seq).total,seq1);
	}
	cvSeqPush(seq,&pt2);
	int (*p);
    p=new int[(*seq).total*2];
	cvCvtSeqToArray(seq,p);
	Mat mm((*seq).total,2,CV_32SC1,p);
	transpose(mm,mm);
	cvReleaseMemStorage(&storage);
	return mm;
}



 void alrm_signal(int signo)
 {
     if(signo != SIGALRM)
     {
         printf("unexpect signal %d/n", signo);
         exit(1);
     }
     pthread_exit(0);

     return;
 }






 void Morphing::release(int i)
 {
		double* temp;
 		switch (i)
 		{
 		case 1:
 			if(monitor[0])
 			{
 			monitor[0]=0;
 			}
 			break;
 		case 2:
 			if(monitor[1])
 			 {
 			   A1=A1.clone();
 			   _A1=_A1.clone();
 			   monitor[1]=0;
 			 }
 			 break;
 		case 3:
 		    if(monitor[2])
 		 	{
 	 			B1=B1.clone();
 	 			_B1=_B1.clone();
 		 	   monitor[2]=0;
 		 	}
 		 	break;
 		case 4:
 		    if(monitor[3])
 		 	{
 		       C1=C1.clone();
 		       _C1=_C1.clone();
 		 	   monitor[3]=0;
 		 	}
 		 	break;
 		case 5:
 		    if(monitor[4])
 		 	{
 		    	D1=D1.clone();
 		    	_D1=_D1.clone();
 		 	   monitor[4]=0;
 		 	}
 		 	break;
 		case 6:
 		    if(monitor[5])
 		 	{
 		    	E1=E1.clone();
 		    	_E1=_E1.clone();
 		 	   monitor[5]=0;
 		 	}
 		 	break;
 		case 7:
 		    if(monitor[6])
 		 	{
 		    	A2=A2.clone();
 		    	_A2=_A2.clone();
 		 	   monitor[6]=0;
 		 	}
 		 	break;
 		case 8:
 		    if(monitor[7])
 		 	{
 		    	B2=B2.clone();
 		    	_B2=_B2.clone();
 		 	   monitor[7]=0;
 		 	}
 		 	break;
 		case 9:
 		    if(monitor[8])
 		 	{
 		    	C2=C2.clone();
 		    	_2C=_2C.clone();
 		 	   monitor[8]=0;
 		 	}
 		 	break;
 		case 10:
 		    if(monitor[9])
 		 	{
 		    	D2=D2.clone();
 		    	_D2=_D2.clone();
 		 	   monitor[9]=0;
 		 	}
 		 	break;
 		case 11:
 		    if(monitor[10])
 		 	{
 		    	E2=E2.clone();
 		    	_E2=_E2.clone();
 		 	   monitor[10]=0;
 		 	}
 		 	break;
 		case 14:
 			if(monitor[13])
 			{
 			contour_new_coordin1=contour_new_coordin1.clone();
 			monitor[13]=0;
 			}
 			break;
 		case 15:
 			if(monitor[14])
 			{
 			contour_new_coordin2=contour_new_coordin2.clone();
 			monitor[14]=0;
 			}
 			break;
 		case 16:
 			if(monitor[15])
 			{
 			contour_origin_coordin=contour_origin_coordin.clone();
 			monitor[15]=0;
 			}
 			break;
 		case 17:
 			if(monitor[16])
 			{
 			contour_origin_coordin1=contour_origin_coordin1.clone();
 			monitor[16]=0;
 			}
 			break;
 		case 18:
 			if(monitor[17])
 			{
 			contour_origin_coordin2=contour_origin_coordin2.clone();
 			monitor[17]=0;
 			}
 			break;
 		case 19:
 			if(monitor[18])
 			{
 			P1=P1.clone();
 			monitor[18]=0;
 			}
 			break;
 		case 20:
 			if(monitor[19])
 			{
 			P2=P2.clone();
 			monitor[19]=0;
 			}
 			break;
 		case 21:
 			if(monitor[20])
 			{
 			monitor[20]=0;
 			}
 			break;
 		case 22:
 			if(monitor[21])
 			{
 			monitor[21]=0;
 			}
 			break;
 		case 23:
 			if(monitor[22])
 			{
 			monitor[22]=0;
 			}
 			break;
 		case 24:
 			if(monitor[23])
 			{
 			length_r1=length_r1.clone();
 			monitor[23]=0;
 			}
 			break;
 		case 25:
 			if(monitor[24])
 			{
 			length_r2=length_r2.clone();
 			monitor[24]=0;
 			}
 			break;
 		default:
 			break;
 		}

 }

 void Morphing::_Morphing()
 {
	 delete[] monitor;
	 this->~Morphing();
 }
}
