
#include "mycpp.h"




 CvMemStorage* storage0=cvCreateMemStorage(0);
 CvMemStorage* storage1=cvCreateMemStorage(0);
namespace cv{


Line_label::Line_label(Mat& _src){
	_src.copyTo(edge);
	_src.copyTo(_edge);

    Label_Mat.create(_src.size(),CV_32SC1);
    Label_Mat = Scalar::all(0);
	fireWall.create(_src.size(),CV_8UC1);
	fireWall=Scalar::all(0);
	num=0;

	monitor=new int[11];
	for(int i=0;i<=10;i++)
	{
		monitor[i]=1;
	}
	storage=cvCreateMemStorage(0);
}


void Line_label::refreshEdge(Mat& _src)
{
	Label_Mat.setTo(0);
	vector<vector<CvSeq*> >().swap(*linetotal);
	cvClearMemStorage(storage);
    num=0;
	line_label(_src,8);
}


void Line_label::addEdge_prehandle(Mat& _src)
{
	num=linetotal->size();
    line_label(_src,8);
}



Get_line::Get_line(Line_label* lineObj)
{
		clear=false;
		contain=false;
		lineobj=lineObj;
}

Get_line::Get_line(){
	clear=false;
    contain=false;
}

void Get_line::refresh(){
    seq=0;
	clear=false;
	contain=false;
    vector<CvSeq*>().swap(segvec);
}



void Get_line::refresh1(){
    seq=0;
	clear=false;
	contain=false;
}



 void Line_label::line_label(Mat& src,int N_bw)
{

	
	CV_Assert( src.depth() == CV_8U );
	
	if(N_bw==4)
		line_label4(src);

	else if(N_bw==8)
	{
		line_label8(src);
	}
	else
	{
		cvSetErrMode(CV_ErrModeLeaf);
		cvError(0,"line_label","N_bw failed","line_label",26);
	}
	
	
}


 void Line_label::line_label4(Mat& _src)
{
 Mat src;
 _src.copyTo(src);
 Mat_<uchar>::iterator it = src.begin<uchar>();
 Mat_<uchar>::iterator itend = src.end<uchar>();
 for(; it!=itend; ++it)
 {        
	if(*it) 
	{
		*it=0;
		getseq(it,4);

	}
 }





}


 void Line_label::line_label8(Mat& _src)
{
	 //压栈
	 Mat src;
    _src.copyTo(src);
	Mat_<uchar>::iterator it = src.begin<uchar>();
    Mat_<uchar>::iterator itend = src.end<uchar>();
	Label_Mat_data=(int*)Label_Mat.data;
 for(; it!=itend; ++it)
 {   
	if(*it) 
	{
   		num=num+1;
		Is_single=false;
		newele_needed=true;
		vector<CvSeq*> temp_container;
		temp_container=getseq(it,8);
		if(Is_single)
		{		
				if(newele_needed)
				{
					linetotal->push_back(temp_container);
				}
				else
				{
			      (linetotal->at(linetotal->size()-1)).insert((linetotal->at(linetotal->size()-1)).end(),temp_container.begin(),temp_container.end());
				}
	}

}
}

}


vector<CvSeq*> Line_label::getseq(Mat_<uchar>::iterator it,int N_bw)
{

	vector<vector<CvSeq*> >_current_container;
	vector<CvSeq*> current_container;
	vector<vector<CvSeq*> >_linetotal_slice;
	vector<vector<Mat_<uchar>::iterator> > _points;
    vector<Mat_<uchar>::iterator> points;

	 points.push_back(it);
	 while(!points.empty())
	 {
		 Mat_<uchar>::iterator _it=points.back();
		 CvPoint pt=_it.pos();
		 bool COULD_PUSH=false;
		 if(_points.empty())
			 COULD_PUSH=true;
		 else if(_points.back().size()>1)
			 COULD_PUSH=true;
		 if(COULD_PUSH&&(*_it))
		 {
			*_it=0;
			Label_Mat_data[_it.lpos()]=num;

		 _points.resize(_points.size()+1);
		 _current_container.resize(_current_container.size()+1);
		 _linetotal_slice.resize(_linetotal_slice.size()+1);
		 _points.back().push_back(_it);
	    if(N_bw==8)
	     {
		   if((*(_it+edge.cols+1))==255)
		    {
			 CvPoint _pt=(_it+edge.cols+1).pos();
		     if(_pt.x==(pt.x+1)&&_pt.y<=edge.rows-1)
		       {
		         _points.back().push_back((_it+edge.cols+1));
		         points.push_back(_it+edge.cols+1);
			     Label_Mat_data[(_it+edge.cols+1).lpos()]=num;
		        }
		     }
		 	if((*(_it-edge.cols+1))==255)
		     {
			      CvPoint _pt=(_it-edge.cols+1).pos();
		      if(_pt.x==(pt.x+1)&&_pt.y>=0)
		        {
		         _points.back().push_back((_it-edge.cols+1));
		         points.push_back(_it-edge.cols+1);
			     Label_Mat_data[(_it-edge.cols+1).lpos()]=num;
		         }
		      }
			if((*(_it+edge.cols-1))==255)
		      {
			      CvPoint _pt=(_it+edge.cols-1).pos();
		     if(_pt.x==(pt.x-1)&&_pt.y<=edge.rows-1)
		       {
		         _points.back().push_back((_it+edge.cols-1));
		          points.push_back(_it+edge.cols-1);
			     Label_Mat_data[(_it+edge.cols-1).lpos()]=num;
		         }
		        }
		 	if((*(_it-edge.cols-1))==255)
		      {
			    CvPoint _pt=(_it-edge.cols-1).pos();
		      if(_pt.x==(pt.x-1)&&_pt.y>=0)
		        {
		         _points.back().push_back((_it-edge.cols-1));
		         points.push_back(_it-edge.cols-1);
			     Label_Mat_data[(_it-edge.cols-1).lpos()]=num;
		        }
		       }
	 }

	        if((*(_it+1))==255)
	         {
		      CvPoint _pt=(_it+1).pos();
		     if(_pt.x==(pt.x+1))
	          {
		       _points.back().push_back((_it+1));
		        points.push_back(_it+1);
		       Label_Mat_data[(_it+1).lpos()]=num;
	           }
	          }
	 	    if((*(_it-1))==255)
	         {
              CvPoint _pt=(_it-1).pos();
		      if(_pt.x==(pt.x-1))
	           {
		        _points.back().push_back((_it-1));
		        points.push_back(_it-1);
		        Label_Mat_data[(_it-1).lpos()]=num;
	            }
	          }
		    if((*(_it+edge.cols))==255)
	         {
		      CvPoint _pt=(_it+edge.cols).pos();
		      if(_pt.y<=edge.rows-1)
	           {
		        _points.back().push_back((_it+edge.cols));
		        points.push_back(_it+edge.cols);
		        Label_Mat_data[(_it+edge.cols).lpos()]=num;
	           }
	          }
	 	    if((*(_it-edge.cols))==255)
	          {
		       CvPoint _pt=(_it-edge.cols).pos();
		      if(_pt.y>=0)
	           {
                _points.back().push_back((_it-edge.cols));
                points.push_back(_it-edge.cols);
		        Label_Mat_data[(_it-edge.cols).lpos()]=num;
	            }
	           }
	        if(_points.back().size()==1)
	          {
	           CvSeq* temp_seq=cvCreateSeq(CV_SEQ_ELTYPE_POINT,sizeof(CvSeq),sizeof(CvPoint),storage);
			   CvPoint temp_pt=_it.pos();
		       cvSeqPush(temp_seq,&temp_pt);
			   _current_container.back().push_back(temp_seq);
			   Is_single=true;
	           }
		  }
		 else if((!*_it)&&(_points.back().size()>1))
		 {
			 points.pop_back();
			 _points.back().pop_back();

		 }

		 else if(_points.back().size()==1)
	      {
		   vector<CvSeq*>& current_container1=_current_container[_current_container.size()-1];
		   vector<CvSeq*>& linetotal_slice1=_linetotal_slice[_linetotal_slice.size()-1];
		   if(_current_container.size()>=2)
		    {
		    vector<CvSeq*>& current_container2=_current_container[_current_container.size()-2];
		    vector<CvSeq*>& linetotal_slice2=_linetotal_slice[_linetotal_slice.size()-2];
			for(vector<CvSeq*>::iterator iter_cur=current_container2.begin();iter_cur!=current_container2.end();++iter_cur)
			 {
				CvSeq* _iter_cur=cvCloneSeq(*iter_cur);
				cvSeqInvert(_iter_cur);
			    for(vector<CvSeq*>::iterator iter_temp=current_container1.begin();iter_temp!=current_container1.end();++iter_temp)
				{
					CvSeq* _iter_=cvCloneSeq(*iter_temp);
					cvSeqInsertSlice(_iter_,_iter_->total,_iter_cur);
			        linetotal_slice2.push_back(_iter_);
				}
			}
	        for(vector<CvSeq*>::iterator _iter_temp=current_container1.begin();_iter_temp!=current_container1.end();++_iter_temp)
	           {
				  Mat_<uchar>::iterator _pt=_points[_points.size()-2][0];
				  CvPoint pt=_pt.pos();
			      cvSeqPush(*_iter_temp,&pt);
			      current_container2.push_back(*_iter_temp);
	           }
            _points[_points.size()-2].pop_back();
	 }
		 else
			 current_container=current_container1;
		 if(!linetotal_slice1.empty())
		  {
		   Is_single=false;
		   if(newele_needed)
		    {
			 linetotal->push_back(linetotal_slice1);
			 newele_needed=false;
		    }
			else
			{
			 (linetotal->at(linetotal->size()-1)).insert((linetotal->at(linetotal->size()-1)).end(),linetotal_slice1.begin(),linetotal_slice1.end());
		    }
		}
			else
				 Is_single=true;
	     _current_container.pop_back();
	     _linetotal_slice.pop_back();
	     _points.pop_back();
	     points.pop_back();
	 }
	 }
	 return current_container;
}




CvSeq* Get_line::getline(CvPoint point1,CvPoint point2)
{

    vector<std::set<int> >dupPoint1;
	  vector<vector<CvPoint> > vec1;
	  CvPoint current_point1,current_point2;
    vector<bool> pts;
    vector<bool> inver;
    vector<vector<CvPoint> >myvecs;
    vector<CvPoint> myvec;
    vector<CvSeq*> segclear;
	  vector<CvPoint> temp_vec;
	  vector<int> num_seq;
	  vector<double> predists;
	  vector<int> end_num;
	  double predist;
	  temp_vec.push_back(point1);
	  vec1.push_back(temp_vec);
	  pts.push_back(false);
	  end_num.push_back(0);
    std::set<int> dupPoint2;
    predist=point_dist(point1,point2)+0.001;
	  predists.push_back(predist);
	  current_point1=point1;
	  current_point2=point2;

	  seq=0;
	  int ind1,ind2,p2;
	  double d,predist1;
	  CvPoint link_point;
	  CvSeq* seq0;

	  while(!vec1.empty()&&!clear&&segvec.size()<500)
	  {
		  vector<CvPoint>& current_neibors=vec1.back();

		 if(current_neibors.empty())
		  {
		  if(!pts.back())
			{
		     if(!segclear.empty())
		     {
		        segclear.pop_back();
		        inver.pop_back();
		     }
		     predists.pop_back();
			 }
			 else
			 {
				 current_point2=current_point1;
				 dupPoint2=dupPoint1.back();
				 dupPoint1.pop_back();
			 }
			 vec1.pop_back();
			 end_num.pop_back();
			 num_seq.pop_back();
			 myvecs.pop_back();
			 pts.pop_back();
		     continue;
		 }
		 predist=predists.back();
		 while(!current_neibors.empty()&&!clear&&segvec.size()<500)
		 	{
			 CvPoint current_neibor=current_neibors.front();
			 current_point1=current_neibor;
			 if(vec1.size()>num_seq.size())
			 {
			     int j=0;
			     num_seq.push_back(j);
			     myvecs.push_back(vector<CvPoint>());
			 }
			 if(dupPoint2.find(lineobj->Label_Mat.at<int>(current_point1))!=dupPoint2.end())
			 {
				 current_neibors.pop_back();
			 	 continue;
			 }

			 int a1=lineobj->Label_Mat.at<int>(current_point1);
			 int a2=lineobj->Label_Mat.at<int>(current_point2);
			 vector<CvSeq*> current_vec_seq1((*(lineobj->linetotal))[a1-1]);
		 	 if(a1==a2)
		 	 {
		 		CvSlice slice;
		 		for(vector<CvSeq*>::iterator it=current_vec_seq1.begin();it!=current_vec_seq1.end();++it)
		 		 {
		 			 schar* b1=cvSeqSearch(*it,&current_point1,0,0,&ind1);
		 			 schar* b2=cvSeqSearch(*it,&current_point2,0,0,&ind2);
		 			 if(b1!=NULL&&b2!=NULL)
		 			 {
		 				 slice=cvSlice(min(ind1,ind2),max(ind1,ind2)+1);
		 				 CvSeq* seq0=cvSeqSlice(*it,slice,storage0,0);
		 				 clear=true;
		 				 if(ind1>ind2)
		 					 inver.push_back(true);
		 				 else
		 					 inver.push_back(false);
		                 segclear.push_back(seq0);
		                 break;
		 			 }
		 		 }
		 	 }
		 	 else//閿熸枻鎷烽敓鏂ゆ嫹鍚屼竴閿熸枻鎷烽敓绔鎷烽敓杈冿綇鎷烽敓鏂ゆ嫹point1閿熸枻鎷穚oint2閿熸枻鎷烽敓鏂ゆ嫹閿熸枻鎷�
		 	 {
		 		myvec=myvecs.back();
		 		for(int i=num_seq.back();i<current_vec_seq1.size();i++)
		 		{

		 			CvSeq* current_seq=current_vec_seq1[i];
		 			int ind;
		 			schar* b=cvSeqSearch(current_seq,&current_neibor,0,0,&ind);
		 			if(b!=NULL)
		 			{
		 			  for(int k=end_num.back();k<2;k++)
		 			   {
		 				end_num.back()++;
		 				if(k==0)
		 				 {
		 					CvPoint* start_point=CV_GET_SEQ_ELEM(CvPoint,current_seq,0);
		 					if(_find(myvec.begin(),myvec.end(),*start_point))
		 					   continue;
		 					else
		 					   d=point_dist(*start_point,current_point2);
		 					myvec.push_back(*start_point);
			 				if(d<predist)
			 				{
			 					link_point=*start_point;
			 				    p2=0;
			 				    predist1=d;
			 				}
			 				else
			 					continue;
		 				}
		 				else{
		 					CvPoint* end_point=CV_GET_SEQ_ELEM(CvPoint,current_seq,current_seq->total-1);
		 					num_seq.back()++;
		 					end_num.back()=0;
		 					if(_find(myvec.begin(),myvec.end(),*end_point))
		 					   continue;
		 					else
		 					   d=point_dist(*end_point,current_point2);
		 					myvec.push_back(*end_point);
		 					if(d<predist)
		 					  {
		 					    link_point=*end_point;
		 						p2=current_seq->total-1;
		 						predist1=d;
		 					  }
		 					else
		 						continue;
		 				}

		 				if(ind<p2)
		 				{
		 					CvSlice slice=cvSlice(ind,p2+1);
		 					seq0=cvSeqSlice(current_seq,slice,storage0,0);
		 					segvec.push_back(seq0);
		 				}
		 				else
		 				{
		                    CvSlice slice=cvSlice(p2,ind+1);
		 					seq0=cvSeqSlice(current_seq,slice,storage0,0);
		 					segvec.push_back(seq0);
		 				}

		 			vector<CvPoint> neibors=find_neibors(link_point,10,lineobj->Label_Mat);
		 			if(!neibors.empty())
		 			{
		 				pts.push_back(false);
		 			    vec1.push_back(neibors);
		 			    end_num.push_back(0);
		 			    if(ind>p2)
		 			    	inver.push_back(true);
		 			    else
		 			    	inver.push_back(false);
		 			    segclear.push_back(seq0);
		 			    predists.push_back(predist1);
		 			    break;
		 			}

		 			}

		 			if(vec1.size()>num_seq.size())
		 				break;
		 		}
		 			else
		 				num_seq.back()++;
		 	 }

		 	 }
		 	 if(vec1.size()>num_seq.size()||clear)
		 		 break;
		 	 else
		 	 {
		 	    current_neibors.erase(current_neibors.begin());
		 	    num_seq.back()=0;
		 	    myvecs.back().clear();
		 	    if(!pts.back())
		 	     {
		 	       dupPoint2.insert(lineobj->Label_Mat.at<int>(current_point1));
                 dupPoint1.push_back(dupPoint2);
                 dupPoint2.clear();
		 	       vector<CvPoint> temp_vec;
		 	       temp_vec.push_back(current_point2);
		 	       vec1.push_back(temp_vec);
		 	       pts.push_back(true);
		 	       end_num.push_back(0);
		 	       current_point2=current_point1;
		 	       break;
		 	    }
		 	 }
		 	}
	  }


	  if(clear)
	  {
		  seq=cvSeqSlice(segclear.back(),CV_WHOLE_SEQ,storage1,1);
		  segclear.pop_back();
		  if(inver.back())
			  cvSeqInvert(seq);
		  inver.pop_back();
		  pts.pop_back();
		  while(!pts.empty())
		  {

				  CvSeq* seq1=cvSeqSlice(segclear.back(),CV_WHOLE_SEQ,storage1,1);
				  if(inver.back())
					  cvSeqInvert(seq1);
				  CvPoint _point1=*CV_GET_SEQ_ELEM(CvPoint,seq1,seq1->total-1);
				  CvPoint _point2=*CV_GET_SEQ_ELEM(CvPoint,seq,0);
				  CvSeq* seq2=linear_link(_point1,_point2,false);
				  cvSeqInsertSlice(seq,0,seq2);
				  cvSeqInsertSlice(seq,0,seq1);
				  segclear.pop_back();
				  inver.pop_back();
				  if(pts.back())
				  	{
					  cvSeqInvert(seq);
					  pts.pop_back();
			        }
			  pts.pop_back();
		  }
	  }
	  else
		  seq=NULL;
	return seq;

}




 CvSeq* Get_line::get_circleline(CvPoint point1,CvPoint point2,CvPoint point3)
 {
	 Mat Label_Mat1;
	 lineobj->Label_Mat.convertTo(Label_Mat1,CV_8UC1);
       Get_line line1(lineobj);
	   line1.getline(point3,point1);
	   checkLine(line1,point1,point2,point3);
	   if(line1.clear&&!line1.contain)
	   {
	   Get_line line2(lineobj);
	   line2.getline(point3,point2);
	   checkLine(line2,point2,point1,point3);
	   if(line2.clear&&!line2.contain)
	   {
       cvSeqPopFront(line1.seq);
       cvSeqInvert(line1.seq);
       cvSeqInsertSlice(line1.seq,(*line1.seq).total,line2.seq);
       clear=true;
       contain=false;
       seq=line1.seq;
	   }
	   else if(line2.clear&&line2.contain)
		   contain=true;
	   }
	   else if(line1.clear&&line1.contain)
		   contain=true;
	   return seq;
 }




void Get_line::checkLine(Get_line& line,CvPoint point1,CvPoint point2,CvPoint point3)
{

	bool COULD_PUSH=false;
	int ind;
	Get_line temp_line(lineobj);
	if(!line.clear)
		COULD_PUSH=true;
	else if(cvSeqSearch(line.seq,&point2,0,0,&ind)!=NULL)
	{
		COULD_PUSH=true;
		line.contain=true;
	}
	else{
		CvPoint pt=*CV_GET_SEQ_ELEM(CvPoint,line.seq,1);
		double d1=point_dist(point3,point2);
		double d2=point_dist(pt,point2);
		double d3=point_dist(point3,point1);
		double d4=point_dist(pt,point1);
		if(d2<=d1&&d3<=d4)
		{
		  COULD_PUSH=true;
		}
	}
	 if(COULD_PUSH)
	 {
        getline1(temp_line,point1,point2,point3);

   	 COULD_PUSH=false;

   		if(!temp_line.clear)
   			COULD_PUSH=true;
   		else if(cvSeqSearch(temp_line.seq,&point2,0,0,&ind)!=NULL)
   		{
   			COULD_PUSH=true;
   		}
   		else{
   			CvPoint pt=*CV_GET_SEQ_ELEM(CvPoint,temp_line.seq,1);
   			double d1=point_dist(point3,point2);
   			double d2=point_dist(pt,point2);
   			double d3=point_dist(point3,point1);
   			double d4=point_dist(pt,point1);
   			if(d2<=d1&&d3<=d4)
   			{
   			  COULD_PUSH=true;
   			}
   		}
   	 if(COULD_PUSH)
   	 {
   		 temp_line.refresh1();
   		 getline1(temp_line,point3,point2,point1);
   		 if(temp_line.clear&&!temp_line.contain)
   		 {
   			CvPoint pt=*CV_GET_SEQ_ELEM(CvPoint,temp_line.seq,temp_line.seq->total-2);
   			double d1=point_dist(point3,point2);
   			double d2=point_dist(pt,point2);
   			double d3=point_dist(point3,point1);
   			double d4=point_dist(pt,point1);
   			if(d2>=d1||d4<=d3)
   			{
   			  cvSeqInvert(temp_line.seq);
   			  line=temp_line;
   			}
   		 }

   	 }
   	 else
   		 line=temp_line;

     }

}



void Get_line::getline1(Get_line& line,CvPoint point1,CvPoint point2,CvPoint point3)
{
	 int a3=lineobj->Label_Mat.at<int>(point3);
    vector<CvSeq*> current_vec_seq3((*(lineobj->linetotal))[a3-1]);
    CvPoint link_point;
    CvSlice slice;
    int ind,ind1,ind3;
    int ind2=0;
    vector<CvPoint>neibors;
	 for(vector<CvSeq*>::iterator it=current_vec_seq3.begin();it!=current_vec_seq3.end();++it)
	 {
		 schar* b3=cvSeqSearch(*it,&point3,0,0,&ind3);
		 if(b3!=NULL)
		 {
			schar* b2=cvSeqSearch(*it,&point2,0,0,&ind2);
			if(b2!=NULL)
			{
				if(ind2<ind3)
				{
					ind=(*it)->total;
					link_point=*CV_GET_SEQ_ELEM(CvPoint,*it,(*it)->total-1);
					 for(int i=ind2+1;i<ind;i++)
						{
						 CvPoint current_point=*CV_GET_SEQ_ELEM(CvPoint,*it,i);
						 lineobj->Label_Mat.at<int>(current_point)=lineobj->linetotal->size()+1;
						 }
					 neibors=find_neibors(link_point,10,lineobj->Label_Mat);
					 for(int i=ind2+1;i<ind;i++)
					 	{
					 	 CvPoint current_point=*CV_GET_SEQ_ELEM(CvPoint,*it,i);
					 	 lineobj->Label_Mat.at<int>(current_point)=a3;
					 	}
				}
				else
				{
					ind=0;
					link_point=*CV_GET_SEQ_ELEM(CvPoint,*it,0);
					for(int i=0;i<ind2;i++)
					   {
						CvPoint current_point=*CV_GET_SEQ_ELEM(CvPoint,*it,i);
					    lineobj->Label_Mat.at<int>(current_point)=lineobj->linetotal->size()+1;
					    }
					neibors=find_neibors(link_point,10,lineobj->Label_Mat);
					for(int i=0;i<ind2;i++)
						{
						 CvPoint current_point=*CV_GET_SEQ_ELEM(CvPoint,*it,i);
						 lineobj->Label_Mat.at<int>(current_point)=a3;
						}
				}
			}
			else
			{
				CvPoint startpoint=*CV_GET_SEQ_ELEM(CvPoint,*it,0);
				CvPoint endpoint=*CV_GET_SEQ_ELEM(CvPoint,*it,(*it)->total-1);
				double d1=point_dist(point1,startpoint);
				double d2=point_dist(point1,endpoint);

				if(d1>=d2)
				  {
					ind=0;
					link_point=startpoint;
					neibors=find_neibors(link_point,10,lineobj->Label_Mat);
				  }
				else
				  {
					ind=(*it)->total;
					link_point=endpoint;
					neibors=find_neibors(link_point,10,lineobj->Label_Mat);
				  }
			}

				for(vector<CvPoint>::iterator _it=neibors.begin();_it!=neibors.end();++_it)
				 {
				    line.refresh1();
				 	line.getline(*_it,point1);
				    if(line.clear)
				 	 {
				 	   if(cvSeqSearch(line.seq,&point2,0,0,&ind2)==NULL)
				 		 {
				 		  CvSeq* seq0=linear_link(link_point,*_it,false);
				 		  CvSlice slice;
				 		  CvSeq* seq1;
				 		  if(ind<ind3)
				 		    {
				 		     slice=cvSlice(ind,ind3+1);
				 		     seq1=cvSeqSlice(*it,slice,storage1,1);
				 		     cvSeqInvert(seq1);
				 		    }
				 		   else
				 		    {
				 		     slice=cvSlice(ind3,ind);
				 		     seq1=cvSeqSlice(*it,slice,storage1,1);
				 		     }
				 		    cvSeqInsertSlice(line.seq,0,seq0);
				 		    cvSeqInsertSlice(line.seq,0,seq1);
				 		    line.contain=false;
				 		    break;
				 		   }
				 	   else
				 		   line.contain=true;
				 		 }
		}

				 if(line.clear&&!line.contain)
					 break;
	 }

}

}


CvSeq* linear_link(CvPoint point1,CvPoint point2,bool add_endpoint)
{
	int cols=std::max<int>(Line_label::picw,std::abs(point1.x-point2.x)+1);
	int rows=std::max<int>(Line_label::pich,std::abs(point1.y-point2.y)+1);
	if(cols>5000)
		cols=1000;
	if(rows>5000)
		rows=1000;
	Mat A(rows,cols,CV_8UC1);
	CvSeq* seq=cvCreateSeq(CV_SEQ_ELTYPE_POINT,sizeof(CvSeq),sizeof(CvPoint),storage1);
    int shift1=0;
    int shift2=0;
    int shift3=0;
    int shift4=0;
    CvPoint pt;
    if(std::min<int>(point1.x,point2.x)<0)
    {
      shift1=-std::min<int>(point1.x,point2.x);
      point1.x=point1.x+shift1;
      point2.x=point2.x+shift1;
    }
    else if(std::max<int>(point1.x,point2.x)>=cols)
    {
    	shift3=cols-1-std::max<int>(point1.x,point2.x);
    	point1.x=point1.x+shift3;
    	point2.x=point2.x+shift3;
    }
    if(std::min<int>(point1.y,point2.y)<0)
    {
    	shift2=-std::min<int>(point1.y,point2.y);
    	point1.y=point1.y+shift2;
    	point2.y=point2.y+shift2;
    }
    else if(std::max<int>(point1.y,point2.y)>=rows)
    {
    	shift4=rows-1-std::max<int>(point1.y,point2.y);
    	point1.y=point1.y+shift4;
    	point2.y=point2.y+shift4;
    }

	LineIterator line_iterator(A,point1,point2,8,0);

	int i1,i2;
	if(add_endpoint)
	{
		i1=0;
		i2=line_iterator.count;
	}
	else
	{
		line_iterator++;
		i1=1;
		i2=line_iterator.count-1;
	}

       for(int i=i1;i<i2;i++)
	   {
	   int offset, x, y; 
	   offset = (line_iterator.ptr - (uchar*)A.data);
       y = offset/A.cols;
       x = (offset - y*A.cols);
       if(shift1!=0)
       {
    	  x=x-shift1;
       }
       else if(shift3!=0)
       {
    	  x=x-shift3;
       }
       if(shift2!=0)
       {
    	  y=y-shift2;
       }
       else if(shift4!=0)
       {
    	  y=y-shift4;
       }
	   pt.x=x;
	   pt.y=y;
	   cvSeqPush(seq,&pt);
	   line_iterator++;
	   }
	 return seq;

}


vector<CvPoint> find_neibors(CvPoint pt,int range,Mat& Label_Mat)
{
	vector<CvPoint> vec;
	vector<int> number_ind;
	vector<double> number_dist;

	for(int i=1;i<=range;i++)
	{		
		vector<Mat> vec_mat;
		Mat sub_mat1;
		Mat sub_mat2;
		Mat sub_mat3;
		Mat sub_mat4;
		bool sig_cols=false;;
		bool sig_rows=false;

		int n1=pt.x-i;
		if(n1<0){
		     while(n1<0)
			       n1+=1;
		     sig_cols=true;
		}

		int n2=pt.x+i;
		if(n2>=Label_Mat.cols){
		     while(n2>=Label_Mat.cols)
			      n2-=1;
		}

		int m1=pt.y-i;
		if(m1<0){
		     while(m1<0)
			       m1+=1;
		     sig_rows=true;
		}

		int m2=pt.y+i;
		if(m2>=Label_Mat.rows){
		      while(m2>=Label_Mat.rows)
			        m2-=1;
		}

	     if(pt.x-i>=0)
			 sub_mat3=Label_Mat(Range(m1,m2+1),Range(pt.x-i,pt.x-i+1));
		 if(pt.x+i<Label_Mat.cols)
			 sub_mat4=Label_Mat(Range(m1,m2+1),Range(pt.x+i,pt.x+i+1));
		 if(pt.y-i>=0)
			 sub_mat1=Label_Mat(Range(pt.y-i,pt.y-i+1),Range(n1,n2+1));
		 if(pt.y+i<Label_Mat.rows)
			 sub_mat2=Label_Mat(Range(pt.y+i,pt.y+i+1),Range(n1,n2+1));

		 vec_mat.push_back(sub_mat1);
		 vec_mat.push_back(sub_mat2);
		 vec_mat.push_back(sub_mat3);
		 vec_mat.push_back(sub_mat4);

		for(vector<Mat>::size_type j=0;j!=vec_mat.size();++j)
		{
			Mat current_mat=vec_mat[j];
			if(current_mat.data)
			{
			for(Mat_<int>::iterator it_m = current_mat.begin<int>();it_m!=current_mat.end<int>();++it_m)
			{
			int number=*it_m;
			if(number!=0&&number!=Label_Mat.at<int>(pt))
			{
				   CvPoint _pt;
				   if(j==0)
				   {
                      _pt.y=pt.y-i;
                      if(!sig_cols)
				          _pt.x=pt.x+it_m.lpos()-i;
                      else
                    	  _pt.x=pt.x+it_m.lpos()+i+1-current_mat.cols;
				   }
				   else if(j==1)
				   {
                      _pt.y=pt.y+i;
                      if(!sig_cols)
				          _pt.x=pt.x+it_m.lpos()-i;
                      else
                    	  _pt.x=pt.x+it_m.lpos()+i+1-current_mat.cols;
				   }
				   else if(j==2)
				   {
                      _pt.x=pt.x-i;
                      if(!sig_rows)
				          _pt.y=pt.y+it_m.lpos()-i;
                      else
                    	  _pt.y=pt.y+it_m.lpos()+i+1-current_mat.rows;
				   }
				   else if(j==3)
				   {
                      _pt.x=pt.x+i;
                      if(!sig_rows)
				          _pt.y=pt.y+it_m.lpos()-i;
                      else
                    	  _pt.y=pt.y+it_m.lpos()+i+1-current_mat.rows;
				   }

				   double _dist=point_dist(_pt,pt);
				   vector<int>::iterator it=std::find(number_ind.begin(),number_ind.end(),number);
				   if(it==number_ind.end())
				   {
		              vec.push_back(_pt);
			          number_ind.push_back(number);
				      number_dist.push_back(_dist);
				   }
				   else if(_dist<number_dist[it-number_ind.begin()])
				   {
					   vec[it-number_ind.begin()]=_pt;
					   number_dist[it-number_ind.begin()]=_dist;
					   number_ind[it-number_ind.begin()]=number;
				   }
			   
			}
		}
		}
		}
		}
	return vec;
	}


double point_dist(CvPoint pt1,CvPoint pt2)
{
	 double Array1[]={pt1.x,pt1.y};
     double Array2[]={pt2.x,pt2.y};
     Mat Mat1(1,2,CV_64FC1,Array1);
     Mat Mat2(1,2,CV_64FC1,Array2);
	 double dist=norm(Mat2,Mat1,NORM_L2);
	 return dist;
}


bool operator== (const CvPoint &a, const CvPoint &b)  {
     /*鍏堟瘮杈冨悕瀛楋紱鑻ュ悕瀛楃浉鍚岋紝鍒欐瘮杈冨勾榫勩�灏忕殑杩斿洖true*/
if(a.x==b.x&a.y==b.y)
return true;
else
return false;
 }



template <class InputIterator, class T>inline bool _find( InputIterator first,InputIterator last,const T& value)
{
for(;first!=last;++first)
{
	if((*first)==value)
	{
		return true;
		break;
	}
}
return false;
}



void Line_label::release(int i)
{

		switch (i)
		{

		case 2:
			if(monitor[1])
			{
			edge=edge.clone();
			monitor[1]=0;
			}
			break;
		case 3:
			if(monitor[2])
			{
			_edge=_edge.clone();
			monitor[2]=0;
			}
			break;

		case 5:
			if(monitor[4])
			{
			_bmp=_bmp.clone();
			monitor[4]=0;
			}
			break;
		case 6:
			if(monitor[5])
			{
			mdf=mdf.clone();
			monitor[5]=0;
			}
			break;

		default:
			break;
		}

}


void refreshStorage0()
{
	cvReleaseMemStorage(&storage0);
    storage0=cvCreateMemStorage(0);
}


void Line_label::clearMemStorage()
{
	    cvReleaseMemStorage(&storage);
	    cvReleaseMemStorage(&storage0);
	    storage0=cvCreateMemStorage(0);
	    cvReleaseMemStorage(&storage1);
	    storage1=cvCreateMemStorage(0);
}

void Line_label::_Line_label()
{
   delete[] monitor;
   this->~Line_label();
}



};
