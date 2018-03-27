#include "jni.h"
#include <time.h>
#include "android/bitmap.h"
#include <mycpp.h>
using namespace cv;


 vector<CvSeq*> Get_line::segvec;
 int Line_label::picw;
 int Line_label::pich;
  extern "C"
  {
      JNIEXPORT jlong JNICALL Java_com_morphing_morobj_Linelabel_linelabel0(JNIEnv* env, jobject obj,jobject bmpnew,jobject sigpic,jobject alph8,jstring file,jint degree);
      JNIEXPORT jlong JNICALL Java_com_morphing_morobj_Linelabel_linelabel0(JNIEnv* env, jobject obj,jobject bmpnew,jobject sigpic,jobject alph8,jstring file,jint degree){

    	         char* rtn = NULL;
    	         jclass clsstring = env->FindClass("java/lang/String");
    	         jstring strencode = env->NewStringUTF("utf-8");
    	         jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
    	         jbyteArray barr= (jbyteArray)env->CallObjectMethod(file, mid, strencode);
    	         jsize alen = env->GetArrayLength(barr);
    	         jbyte* ba = env->GetByteArrayElements(barr, JNI_FALSE);
    	         if (alen > 0)
    	           {
    	             rtn = (char*)malloc(alen + 1);
    	             memcpy(rtn, ba, alen);
    	             rtn[alen] = 0;
    	           }
    	         env->ReleaseByteArrayElements(barr, ba, 0);

    	  		 AndroidBitmapInfo  info;
    	         void*              pixels = 0;
    	         void*              pixelssig=0;
    	         void*              pixelsalph8;
    	  		 CV_Assert( AndroidBitmap_getInfo(env, bmpnew, &info) >= 0 );
    	         CV_Assert( info.format == ANDROID_BITMAP_FORMAT_RGBA_8888 ||
    	         info.format == ANDROID_BITMAP_FORMAT_RGB_565 );
    	         CV_Assert( AndroidBitmap_lockPixels(env, bmpnew, &pixels) >= 0 );
    	         CV_Assert( pixels );
    	  		 Mat tmp(info.height, info.width, CV_8UC4, pixels);

    	  		 CV_Assert( AndroidBitmap_getInfo(env, sigpic, &info) >= 0 );
    	         CV_Assert( info.format == ANDROID_BITMAP_FORMAT_RGBA_8888 ||
    	         info.format == ANDROID_BITMAP_FORMAT_RGB_565 );
    	         CV_Assert( AndroidBitmap_lockPixels(env, sigpic, &pixelssig) >= 0 );
    	         CV_Assert( pixelssig );
    	  		 Mat tmpsig(info.height, info.width, CV_8UC4, pixelssig);

    	  		 CV_Assert( AndroidBitmap_getInfo(env, alph8, &info) >= 0 );
    	         CV_Assert( info.format == ANDROID_BITMAP_FORMAT_RGBA_8888 ||
    	         info.format == ANDROID_BITMAP_FORMAT_RGB_565||info.format == ANDROID_BITMAP_FORMAT_A_8 );
    	         CV_Assert( AndroidBitmap_lockPixels(env, alph8, &pixelsalph8) >= 0 );
    	         CV_Assert( pixelsalph8 );
    	  		 Mat tmpalph8(info.height, info.width, CV_8UC1, pixelsalph8);

    	  		 Line_label::picw=tmpalph8.cols;
    	  		 Line_label::pich=tmpalph8.rows;
    	  		 Mat bgr,mGray,cedge,edge,cedge0,cedge1,cedge2,out;
    	  		 cvtColor(tmp,bgr,CV_BGRA2BGR);
    	  		 cvtColor(bgr,bgr,CV_BGR2Lab);
    	  		 bilateralFilter(bgr,out,5,100,0);
    	  		 cvtColor(out,out,CV_Lab2BGR);
    	  		 cvtColor(out,mGray, CV_BGR2GRAY);
    	  		 Size ksize;
    	  		 ksize.width=0;
    	  		 ksize.height=0;
    	  		 GaussianBlur(mGray,cedge,ksize,1);
    	  		 int edgeThresh=30;
    	  		 Canny(cedge,edge, edgeThresh, 50, 3,true);

    	  		 Line_label* lineobj=new Line_label(edge);
    	  		 lineobj->linetotal=new vector<vector<CvSeq*> >;
    	  		 lineobj->line_label(edge,8);
    	  		 lineobj->bmp=tmp;
    	  		 tmp.copyTo(lineobj->_bmp);
    	  		 lineobj->mdf=Mat(tmp.rows,tmp.cols,CV_8UC1,cvScalar(0));
    	  		 lineobj->bmpsig=tmpsig;
    	  		 lineobj->alph8=tmpalph8;
    	  		 lineobj->bmp1=imread(rtn,1);
    	  		 if((int)degree==90){
    	  			transpose(lineobj->bmp1, lineobj->bmp1);
    	  			flip(lineobj->bmp1, lineobj->bmp1, 1);
    	  		 }
    	  		 else if((int)degree==180){
    	  			flip(lineobj->bmp1, lineobj->bmp1, 0);
    	  			flip(lineobj->bmp1, lineobj->bmp1, 1);
    	  		 }
    	  		 else if((int)degree==270){
    	  			transpose(lineobj->bmp1, lineobj->bmp1);
    	  			flip(lineobj->bmp1, lineobj->bmp1, 0);
    	  		 }
    	  		 CvMat _bmp1=lineobj->bmp1;
    	  		 cvConvertImage(&_bmp1,&_bmp1,CV_CVTIMG_SWAP_RB);
    	  		 AndroidBitmap_unlockPixels(env, bmpnew);
    	  		 AndroidBitmap_unlockPixels(env, sigpic);
    	  		 AndroidBitmap_unlockPixels(env, alph8);

    	  		 cvDecRefData(&_bmp1);
    	  		 return (jlong)lineobj;
  }






      JNIEXPORT void JNICALL Java_com_morphing_morobj_Linelabel_refreshpointer0(JNIEnv* env, jobject obj,jlong nativeObj);
      JNIEXPORT void JNICALL Java_com_morphing_morobj_Linelabel_refreshpointer0(JNIEnv* env, jobject obj,jlong nativeObj){

    	      Line_label& lineobj=*((Line_label*)nativeObj);
              lineobj._bmp.copyTo(lineobj.bmp);
      }



      JNIEXPORT void JNICALL Java_com_morphing_morobj_Linelabel_refreshLabel0(JNIEnv* env, jobject obj,jlong nativeObj);
      JNIEXPORT void JNICALL Java_com_morphing_morobj_Linelabel_refreshLabel0(JNIEnv* env, jobject obj,jlong nativeObj){

    	      Morphing& mor=*((Morphing*)nativeObj);
    	      mor.lineobj->fireWall.setTo(0);
    	      Mat bgr,mGray,cedge,out;
    	      cvtColor(mor.lineobj->bmp,bgr,CV_BGRA2BGR);
    	      cvtColor(bgr,bgr,CV_BGR2Lab);
    	      bilateralFilter(bgr,out,5,100,0);
    	      cvtColor(out,out,CV_Lab2BGR);
    	      cvtColor(out,mGray, CV_BGR2GRAY);
    	      Size ksize;
    	      ksize.width=0;
    	      ksize.height=0;
    	      GaussianBlur(mGray,cedge,ksize,1);
    	      int edgeThresh=30;

    	      mor.lineobj->release(2);
    	      mor.lineobj->release(3);
    	      Canny(cedge,mor.lineobj->edge, edgeThresh, edgeThresh*2.5, 3,true);
    	      mor.lineobj->edge.copyTo(mor.lineobj->_edge);
    	      mor.lineobj->refreshEdge(mor.lineobj->edge);

    	      //é‡æ–°åˆ¶ä½œbmp1
              Mat mdf;
              bitwise_or(mor.origin_regionmat,mor.new_regionmat,mdf);
              multiply(mdf,255,mdf);
              mor.lineobj->release(6);
              bitwise_or(mdf,mor.lineobj->mdf,mor.lineobj->mdf);

              //ÊÍ·ÅÄÚ´æ
              mor.origin_region.release();
              mor.new_region.release();
              mor.left_region.release();
              mor.map_region.release();

      }

      JNIEXPORT jboolean JNICALL Java_com_morphing_morobj_Linelabel_createbmp0(JNIEnv* env, jobject obj,jlong nativeObj);
      JNIEXPORT jboolean JNICALL Java_com_morphing_morobj_Linelabel_createbmp0(JNIEnv* env, jobject obj,jlong nativeObj){
    	      Line_label& lineobj=*((Line_label*)nativeObj);
    	      Size ksize;
    	      ksize.width=lineobj.bmp1.cols;
    	      ksize.height=lineobj.bmp1.rows;
    	      Mat _mdf,__mdf,_bmp,__bmp,bmp1,bmp2;
    	      cvtColor(lineobj.bmp,__bmp,CV_BGRA2BGR);
    	      resize(lineobj.mdf,_mdf,ksize,0,0);
    	      resize(__bmp,_bmp,ksize,0,0);
    	      __bmp.release();
    	      vector<Mat> mv(3,_mdf);
    	      _mdf.release();
    	      merge(mv,__mdf);
    	      bitwise_and(__mdf,_bmp,bmp1);
    	      _bmp.release();
    	      bitwise_not(__mdf,__mdf);
    	      bitwise_and(__mdf,lineobj.bmp1,bmp2);
    	      __mdf.release();
    	      bitwise_or(bmp1,bmp2,bmp1);
    	      bmp2.release();
    	      CvMat _bmp1=bmp1;
    	      cvConvertImage( &_bmp1, &_bmp1, CV_CVTIMG_SWAP_RB );
    	      char str[25];
    	      sprintf(str, "%ld", time(0));
//    	      vector<int> compression_params;
//    	          compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
//    	          compression_params.push_back(100);
    	      bool clear=imwrite("/mnt/sdcard/Mormor/"+(string)str+".jpg",bmp1);
    	      cvDecRefData(&_bmp1);
    	      return (jboolean)clear;
            }


      JNIEXPORT jlong JNICALL Java_com_morphing_morobj_Linelabel_linelabel1(JNIEnv* env, jobject obj, jlong l_addr);
      JNIEXPORT jlong JNICALL Java_com_morphing_morobj_Linelabel_linelabel1(JNIEnv* env, jobject obj, jlong l_addr){

      	     Line_label&   lineobj = *((Line_label*)l_addr);
             Line_label* _lineobj=new Line_label(lineobj);
             _lineobj->monitor=new int[11];
             for (int i=0;i<=10;i++)
             {
            	 _lineobj->monitor[i]=1;
             }
             return (jlong)_lineobj;
  }


      JNIEXPORT void JNICALL Java_com_morphing_morobj_Linelabel_setcopy0(JNIEnv* env, jobject obj, jlong l_addr);
      JNIEXPORT void JNICALL Java_com_morphing_morobj_Linelabel_setcopy0(JNIEnv* env, jobject obj, jlong l_addr){

      	     Line_label&   lineobj = *((Line_label*)l_addr);
      	     if(!lineobj.monitor[4])
      	     lineobj.bmp.copyTo(lineobj._bmp);

  }


      JNIEXPORT void JNICALL Java_com_morphing_morobj_Linelabel_setContourMode0(JNIEnv* env, jobject obj, jlong l_addr,jint n);
      JNIEXPORT void JNICALL Java_com_morphing_morobj_Linelabel_setContourMode0(JNIEnv* env, jobject obj, jlong l_addr,jint n){

      	     Morphing&   mor = *((Morphing*)l_addr);
      	     CvPoint current_point;
      	     Mat tmp=mor.lineobj->bmpsig;
      	     Mat edge_;
      	     bitwise_or(mor.lineobj->alph8,mor.lineobj->_edge,edge_);
        	 int fromTo[]={0,3};
        	 mixChannels(&edge_,1,&mor.lineobj->bmpsig,1,fromTo,1);
        	 fromTo[0]=0;
        	 fromTo[1]=0;
        	 mixChannels(&edge_,1,&mor.lineobj->bmpsig,1,fromTo,1);
    	     if((int)n==1)
    	     {
    	    	for (int i=1;i<mor.seq1->total-1;i++)
    	    	   {
    	    	   	 current_point=*CV_GET_SEQ_ELEM(CvPoint,mor.seq1,i);
    	    	   	 tmp.at<Vec4b>(current_point)=Vec4b(0,0,0,0);
    	    	   }
    	     	for(int i=0;i<mor.contour_new_coordin1.cols;++i)
    	     	   {
    	     	     current_point.x=*mor.contour_new_coordin1.ptr<int>(0,i);
    	     	     current_point.y=*mor.contour_new_coordin1.ptr<int>(1,i);
    	     	     if(current_point.x>=0&&current_point.y>=0&&current_point.x<tmp.cols&&current_point.y<tmp.rows)
    	     	       {
    	     	         tmp.at<Vec4b>(current_point)=Vec4b(0,255,0,255);
    	     	       }
    	     	   }
    	     }
    	     else if((int)n==2)
    	     {
    	    	for (int i=1;i<mor.seq1->total-1;i++)
    	    	   {
    	    	   	 current_point=*CV_GET_SEQ_ELEM(CvPoint,mor.seq1,i);
    	    	   	 tmp.at<Vec4b>(current_point)=Vec4b(0,0,0,0);
    	    	   }
    	    	for (int i=1;i<mor.seq2->total-1;i++)
    	    	   {
    	    	   	 current_point=*CV_GET_SEQ_ELEM(CvPoint,mor.seq2,i);
    	    	   	 tmp.at<Vec4b>(current_point)=Vec4b(0,0,0,0);
    	    	   }
    	     	   for(int i=0;i<mor.contour_new_coordin1.cols;++i)
    	     	      {
    	     	        current_point.x=*mor.contour_new_coordin1.ptr<int>(0,i);
    	     	        current_point.y=*mor.contour_new_coordin1.ptr<int>(1,i);
    	     	        if(current_point.x>=0&&current_point.y>=0&&current_point.x<tmp.cols&&current_point.y<tmp.rows)
    	     	          {
    	     	            tmp.at<Vec4b>(current_point)=Vec4b(0,255,0,255);
    	     	          }
    	     	       }
    	     	   for(int i=0;i<mor.contour_new_coordin2.cols;++i)
    	     	      {
    	     	        current_point.x=*mor.contour_new_coordin2.ptr<int>(0,i);
    	     	        current_point.y=*mor.contour_new_coordin2.ptr<int>(1,i);
    	     	        if(current_point.x>=0&&current_point.y>=0&&current_point.x<tmp.cols&&current_point.y<tmp.rows)
    	     	          {
    	     	            tmp.at<Vec4b>(current_point)=Vec4b(0,255,0,255);
    	     	          }
    	     	       }
    	     }

  }



      JNIEXPORT void JNICALL Java_com_morphing_morobj_Linelabel_setContourMode1(JNIEnv* env, jobject obj, jlong l_addr);
      JNIEXPORT void JNICALL Java_com_morphing_morobj_Linelabel_setContourMode1(JNIEnv* env, jobject obj, jlong l_addr){

    	  Line_label&   lineobj = *((Line_label*)l_addr);
    	  int fromTo[]={0,3};
    	  mixChannels(&lineobj.edge,1,&lineobj.bmpsig,1,fromTo,1);
    	  fromTo[0]=0;
    	  fromTo[1]=0;
    	  mixChannels(&lineobj.edge,1,&lineobj.bmpsig,1,fromTo,1);
  }



      JNIEXPORT void JNICALL Java_com_morphing_morobj_Linelabel_setFreeMode0(JNIEnv* env, jobject obj, jlong l_addr,jint n);
      JNIEXPORT void JNICALL Java_com_morphing_morobj_Linelabel_setFreeMode0(JNIEnv* env, jobject obj, jlong l_addr,jint n){

           Morphing&   mor = *((Morphing*)l_addr);

     	   CvPoint current_point;
     	   Mat tmp=mor.lineobj->bmpsig;
     	   int fromTo[]={0,3};
     	   mixChannels(&mor.lineobj->alph8,1,&mor.lineobj->bmpsig,1,fromTo,1);
     	   fromTo[0]=0;
     	   fromTo[1]=0;
     	  mixChannels(&mor.lineobj->alph8,1,&mor.lineobj->bmpsig,1,fromTo,1);
 	     if((int)n==1)
 	     {
 	    	for (int i=1;i<mor.seq1->total-1;i++)
 	    	   {
 	    	   	 current_point=*CV_GET_SEQ_ELEM(CvPoint,mor.seq1,i);
 	    	   	 tmp.at<Vec4b>(current_point)=Vec4b(0,0,0,0);
 	    	   }
     	   for(int i=0;i<mor.contour_new_coordin1.cols;++i)
     	      {
     	        current_point.x=*mor.contour_new_coordin1.ptr<int>(0,i);
     	        current_point.y=*mor.contour_new_coordin1.ptr<int>(1,i);
     	        if(current_point.x>=0&&current_point.y>=0&&current_point.x<tmp.cols&&current_point.y<tmp.rows)
     	          {
     	            tmp.at<Vec4b>(current_point)=Vec4b(0,255,0,255);
     	          }
     	       }
 	     }
 	     else if((int)n==2)
 	     {
 	    	for (int i=1;i<mor.seq1->total-1;i++)
 	    	   {
 	    	   	 current_point=*CV_GET_SEQ_ELEM(CvPoint,mor.seq1,i);
 	    	     tmp.at<Vec4b>(current_point)=Vec4b(0,0,0,0);
 	    	   }
 	    	for (int i=1;i<mor.seq2->total-1;i++)
 	    	   {
 	    	   	 current_point=*CV_GET_SEQ_ELEM(CvPoint,mor.seq2,i);
 	    	     tmp.at<Vec4b>(current_point)=Vec4b(0,0,0,0);
 	    	   }
     	   for(int i=0;i<mor.contour_new_coordin1.cols;++i)
     	      {
     	        current_point.x=*mor.contour_new_coordin1.ptr<int>(0,i);
     	        current_point.y=*mor.contour_new_coordin1.ptr<int>(1,i);
     	        if(current_point.x>=0&&current_point.y>=0&&current_point.x<tmp.cols&&current_point.y<tmp.rows)
     	          {
     	            tmp.at<Vec4b>(current_point)=Vec4b(0,255,0,255);
     	          }
     	       }
     	   for(int i=0;i<mor.contour_new_coordin2.cols;++i)
     	      {
     	        current_point.x=*mor.contour_new_coordin2.ptr<int>(0,i);
     	        current_point.y=*mor.contour_new_coordin2.ptr<int>(1,i);
     	        if(current_point.x>=0&&current_point.y>=0&&current_point.x<tmp.cols&&current_point.y<tmp.rows)
     	          {
     	            tmp.at<Vec4b>(current_point)=Vec4b(0,255,0,255);
     	          }
     	       }
 	     }
        }


      JNIEXPORT void JNICALL Java_com_morphing_morobj_Linelabel_setFreeMode1(JNIEnv* env, jobject obj, jlong l_addr);
      JNIEXPORT void JNICALL Java_com_morphing_morobj_Linelabel_setFreeMode1(JNIEnv* env, jobject obj, jlong l_addr){

    	  Line_label&   lineobj = *((Line_label*)l_addr);
    	  int fromTo[]={1,3};
    	  mixChannels(&lineobj.bmpsig,1,&lineobj.bmpsig,1,fromTo,1);
          Mat temp(lineobj.bmpsig.rows,lineobj.bmpsig.cols,CV_8UC1,cvScalar(0));
          fromTo[0]=0;
          fromTo[1]=0;
          mixChannels(&temp,1,&lineobj.bmpsig,1,fromTo,1);
          fromTo[0]=0;
          fromTo[1]=2;
          mixChannels(&temp,1,&lineobj.bmpsig,1,fromTo,1);
        }



      JNIEXPORT void JNICALL Java_com_morphing_morobj_Linelabel_setTempMode0(JNIEnv* env, jobject obj, jlong l_addr,jboolean EDGE_MODE);
      JNIEXPORT void JNICALL Java_com_morphing_morobj_Linelabel_setTempMode0(JNIEnv* env, jobject obj, jlong l_addr,jboolean EDGE_MODE){

    	  Line_label&   lineobj = *((Line_label*)l_addr);
    	  Mat edge_;
    	  if((bool)EDGE_MODE)
    	  bitwise_or(lineobj._edge,lineobj.alph8,edge_);
    	  else
    		  edge_=lineobj.alph8;
    	  lineobj.bmpsig.setTo(0);
    	  int fromTo[]={0,3};
    	  mixChannels(&edge_,1,&lineobj.bmpsig,1,fromTo,1);
    	  fromTo[0]=0;
    	  fromTo[1]=0;
    	  mixChannels(&edge_,1,&lineobj.bmpsig,1,fromTo,1);
  }



      JNIEXPORT void JNICALL Java_com_morphing_morobj_Linelabel_concateLineview0(JNIEnv* env, jobject obj, jlong l_addr,jboolean EDGE_MODE);
      JNIEXPORT void JNICALL Java_com_morphing_morobj_Linelabel_concateLineview0(JNIEnv* env, jobject obj, jlong l_addr,jboolean EDGE_MODE){

    	  Line_label&   lineobj = *((Line_label*)l_addr);
    	  if((bool)EDGE_MODE)
    	  {
    	  Mat edge_;
    	  CvMat _edge_=lineobj.bmpsig;
    	  extractImageCOI(&_edge_,edge_,3);
          bitwise_or(lineobj.alph8,edge_,edge_);
    	  int fromTo[]={0,3};
    	  mixChannels(&edge_,1,&lineobj.bmpsig,1,fromTo,1);
    	  fromTo[0]=0;
    	  fromTo[1]=0;
    	  mixChannels(&edge_,1,&lineobj.bmpsig,1,fromTo,1);
    	  cvDecRefData(&_edge_);
    	  }
    	  else
    	  {
        	  int fromTo[]={0,3};
        	  mixChannels(&lineobj.alph8,1,&lineobj.bmpsig,1,fromTo,1);
        	  fromTo[0]=0;
        	  fromTo[1]=0;
        	  mixChannels(&lineobj.alph8,1,&lineobj.bmpsig,1,fromTo,1);
    	  }
  }



      JNIEXPORT jintArray JNICALL Java_com_morphing_morobj_Linelabel_Isedge0(JNIEnv* env, jobject obj,jfloatArray coords, jint range,jlong nativeObj,jboolean EDGE_MODE);
      JNIEXPORT jintArray JNICALL Java_com_morphing_morobj_Linelabel_Isedge0(JNIEnv* env, jobject obj,jfloatArray coords, jint range,jlong nativeObj,jboolean EDGE_MODE){

    	     Line_label&   lineobj = *((Line_label*)nativeObj);

      		 jfloat *cbuf;
      		 CvPoint pt;
           	 jintArray result = env->NewIntArray(2);
      		 cbuf = env->GetFloatArrayElements(coords,0);
      		 pt.x=(int)(*cbuf);
      		 pt.y=(int)(*(cbuf+1));
             CvPoint __pt;
      	     __pt.x=-1;
      	     __pt.y=-1;
      	     double current_dist=1000;
      	     Mat _Label_Mat;
      	     lineobj.edge.type();

     	     if(pt.x>=0&&pt.x<lineobj.picw&&pt.y>=0&&pt.y<lineobj.pich)
     	        {
        	      if((bool)EDGE_MODE)
        	         {
        		       _Label_Mat=lineobj.Label_Mat;
      	               if(_Label_Mat.at<int>(pt)!=0)
      	                  {
      			            __pt=pt;
      	                  }
      		           else
      		              {
      	                    for(int i=1;i<=(int)range/2;i++)
      	                        {
      		                      if(i>(int)current_dist)
      			                     break;
      		                      vector<Mat> vec_mat;
      		                      Mat sub_mat1;
      		                      Mat sub_mat2;
      		                      Mat sub_mat3;
      		                      Mat sub_mat4;
      		                      bool sig_cols=false;
      		                      bool sig_rows=false;

      		                      int n1=pt.x-i;
      		                      if(n1<0){
      		                           while(n1<0)
      			                            n1+=1;
      		                           sig_cols=true;
      		                      }

      		                      int n2=pt.x+i;
      		                      if(n2>=_Label_Mat.cols){
      		                           while(n2>=_Label_Mat.cols)
      			                           n2-=1;
      		                      }

      		                      int m1=pt.y-i;
      		                      if(m1<0){
      		                           while(m1<0)
      			                           m1+=1;
      		                           sig_rows=true;
      		                      }

      		                      int m2=pt.y+i;
      		                      if(m2>=_Label_Mat.rows){
      		                           while(m2>=_Label_Mat.rows)
      			                            m2-=1;
      		                      }

      		                     if(pt.x-i>=0)
      		                          sub_mat3=_Label_Mat(Range(m1,m2+1),Range(pt.x-i,pt.x-i+1));
      		                     if(pt.x+i<_Label_Mat.cols)
      		                          sub_mat4=_Label_Mat(Range(m1,m2+1),Range(pt.x+i,pt.x+i+1));
      		                     if(pt.y-i>=0)
      		                          sub_mat1=_Label_Mat(Range(pt.y-i,pt.y-i+1),Range(n1,n2+1));
      		                     if(pt.y+i<_Label_Mat.rows)
      		                          sub_mat2=_Label_Mat(Range(pt.y+i,pt.y+i+1),Range(n1,n2+1));

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
      			                                if(number>0)
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
      				                               if(_dist<current_dist)
      				                                  {
      		                                            current_dist=_dist;
      					                                __pt=_pt;
      				                                  }

      			                                    }
      		                                       }
      		                                      }
      		                                     }
      		                                    }
      		                                   }
        	         }
        	    else
        	      {
        		     _Label_Mat=lineobj.alph8;
            	     if(_Label_Mat.at<uchar>(pt)!=0)
            	        {
            			  __pt=pt;
            	        }
            		 else
            		    {
            	         for(int i=1;i<=(int)range/2;i++)
            	            {
            		          if(i>(int)current_dist)
            			         break;
            		          vector<Mat> vec_mat;
  		                      Mat sub_mat1;
  		                      Mat sub_mat2;
  		                      Mat sub_mat3;
  		                      Mat sub_mat4;
  		                      bool sig_cols=false;
  		                      bool sig_rows=false;

  		                      int n1=pt.x-i;
  		                      if(n1<0){
  		                           while(n1<0)
  			                            n1+=1;
  		                           sig_cols=true;
  		                      }

  		                      int n2=pt.x+i;
  		                      if(n2>=_Label_Mat.cols){
  		                           while(n2>=_Label_Mat.cols)
  			                           n2-=1;
  		                      }

  		                      int m1=pt.y-i;
  		                      if(m1<0){
  		                           while(m1<0)
  			                           m1+=1;
  		                           sig_rows=true;
  		                      }

  		                      int m2=pt.y+i;
  		                      if(m2>=_Label_Mat.rows){
  		                           while(m2>=_Label_Mat.rows)
  			                            m2-=1;
  		                      }

  		                      if(pt.x-i>=0)
  		                          sub_mat3=_Label_Mat(Range(m1,m2+1),Range(pt.x-i,pt.x-i+1));
  		                      if(pt.x+i<_Label_Mat.cols)
  		                          sub_mat4=_Label_Mat(Range(m1,m2+1),Range(pt.x+i,pt.x+i+1));
  		                      if(pt.y-i>=0)
  		                          sub_mat1=_Label_Mat(Range(pt.y-i,pt.y-i+1),Range(n1,n2+1));
  		                      if(pt.y+i<_Label_Mat.rows)
  		                          sub_mat2=_Label_Mat(Range(pt.y+i,pt.y+i+1),Range(n1,n2+1));

  		                    vec_mat.push_back(sub_mat1);
  		                    vec_mat.push_back(sub_mat2);
  		                    vec_mat.push_back(sub_mat3);
  		                    vec_mat.push_back(sub_mat4);


            		          for(vector<Mat>::size_type j=0;j!=vec_mat.size();++j)
            		             {
            			           Mat current_mat=vec_mat[j];
            			           if(current_mat.data)
            			             {
            			               for(Mat_<uchar>::iterator it_m = current_mat.begin<uchar>();it_m!=current_mat.end<uchar>();++it_m)
            			                  {
            			                    uchar number=*it_m;
            			                    if(number>0)
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
            				                    if(_dist<current_dist)
            				                      {
            		                                current_dist=_dist;
            					                    __pt=_pt;
            				                      }
            			                       }
            		                         }
            		                       }
            		                     }
            		                   }
            		                }
        	                     }
     		                  }
      	  env->SetIntArrayRegion(result, 0, 1,(jint*) &__pt.x);
      	  env->SetIntArrayRegion(result, 1, 1,(jint*) &__pt.y);
          env->ReleaseFloatArrayElements(coords, cbuf, 0);
          return result;
     }




      JNIEXPORT void JNICALL Java_com_morphing_morobj_Linelabel_addEdge0(JNIEnv* env, jobject obj,jlong nativeObj,jint num_rpoint,jboolean EDGE_MODE);
      JNIEXPORT void JNICALL Java_com_morphing_morobj_Linelabel_addEdge0(JNIEnv* env, jobject obj,jlong nativeObj,jint num_rpoint,jboolean EDGE_MODE){

    	             Morphing& mor = *((Morphing*)nativeObj);
                     mor.lineobj->release(3);
          	         Mat edge_temp,erase_origin;
           	  	     Mat edge_;
           	  	     CvMat _edge_=mor.lineobj->bmpsig;
           	  	     extractImageCOI(&_edge_,edge_,3);
          	  		 if((bool)EDGE_MODE)
          	  		 {
          	  			 bitwise_and(edge_,mor.lineobj->edge,mor.lineobj->_edge);
          	  		     bitwise_and(mor.lineobj->alph8,mor.lineobj->_edge,edge_temp);
           	  		     if((int)num_rpoint==1){
           	  		       for (int i=0;i<mor.seq1->total;i++)
           	  		        {
           	  		    	  CvPoint current_point=*CV_GET_SEQ_ELEM(CvPoint,mor.seq1,i);
           	  		    	  if(mor.lineobj->edge.at<uchar>(current_point)>0)
           	  		    	  mor.lineobj->_edge.at<uchar>(current_point)=255;
           	  		        }
           	  		 }
           	  		     else if((int)num_rpoint==2)
           	  		     {
           	  		       for (int i=0;i<mor.seq1->total;i++)
           	  		       {
           	  		          CvPoint current_point=*CV_GET_SEQ_ELEM(CvPoint,mor.seq1,i);
           	  		          if(mor.lineobj->edge.at<uchar>(current_point)>0)
           	  		       	  mor.lineobj->_edge.at<uchar>(current_point)=255;
           	  		       }
           	  		       for (int i=0;i<mor.seq2->total;i++)
           	  		   	   {
           	  		   	  	  CvPoint current_point=*CV_GET_SEQ_ELEM(CvPoint,mor.seq2,i);
           	  		   	      if(mor.lineobj->edge.at<uchar>(current_point)>0)
           	  		   	  	  mor.lineobj->_edge.at<uchar>(current_point)=255;
           	  		   	   }
           	  		     }
          	  		 }
          	  		 else
          	  		 {
          	  			bitwise_and(mor.lineobj->alph8,mor.lineobj->_edge,edge_temp);
          	  		 }
          	  		 bitwise_xor(mor.lineobj->_edge,edge_temp,erase_origin);
          	  		 mor.lineobj->refreshEdge(erase_origin);
          	  	     mor.lineobj->addEdge_prehandle(mor.lineobj->alph8);

          	  	     cvDecRefData(&_edge_);

        }


      JNIEXPORT void JNICALL Java_com_morphing_morobj_Linelabel_addEdge1(JNIEnv* env, jobject obj,jlong nativeObj,jint num_rpoint,jboolean EDGE_MODE);
      JNIEXPORT void JNICALL Java_com_morphing_morobj_Linelabel_addEdge1(JNIEnv* env, jobject obj,jlong nativeObj,jint num_rpoint,jboolean EDGE_MODE){
    	     Morphing& mor = *((Morphing*)nativeObj);
   	         Mat edge_temp,erase_origin;
   	  	     Mat edge_;
   	  	     CvMat _edge_=mor.lineobj->bmpsig;
   	  	     extractImageCOI(&_edge_,edge_,3);

   	  		 if((bool) EDGE_MODE)
   	  		 {
   	  			 bitwise_and(edge_,mor.lineobj->edge,mor.lineobj->_edge);
   	  			 bitwise_and(mor.lineobj->alph8,mor.lineobj->_edge,edge_temp);
   	  		     if((int)num_rpoint==1){
   	  		       for (int i=0;i<mor.seq1->total;i++)
   	  		        {
   	  		    	  CvPoint current_point=*CV_GET_SEQ_ELEM(CvPoint,mor.seq1,i);
   	  		    	  if(mor.lineobj->edge.at<uchar>(current_point)>0)
   	  		    	  mor.lineobj->_edge.at<uchar>(current_point)=255;
   	  		        }
   	  		 }
   	  		     else if((int)num_rpoint==2)
   	  		     {
   	  		       for (int i=0;i<mor.seq1->total;i++)
   	  		       {
   	  		          CvPoint current_point=*CV_GET_SEQ_ELEM(CvPoint,mor.seq1,i);
   	  		          if(mor.lineobj->edge.at<uchar>(current_point)>0)
   	  		       	  mor.lineobj->_edge.at<uchar>(current_point)=255;
   	  		       }
   	  		       for (int i=0;i<mor.seq2->total;i++)
   	  		   	   {
   	  		   	  	  CvPoint current_point=*CV_GET_SEQ_ELEM(CvPoint,mor.seq2,i);
   	  		   	      if(mor.lineobj->edge.at<uchar>(current_point)>0)
   	  		   	  	  mor.lineobj->_edge.at<uchar>(current_point)=255;
   	  		   	   }
   	  		     }
   	  		 }
   	  		 else
   	  		 {
   	  			 bitwise_and(mor.lineobj->alph8,mor.lineobj->_edge,edge_temp);
   	  		 }
   	  		 bitwise_xor(edge_temp,mor.lineobj->_edge,erase_origin);

   	  		 mor.lineobj->refreshEdge(erase_origin);
   	  	     mor.lineobj->addEdge_prehandle(mor.lineobj->alph8);

   	  	     cvDecRefData(&_edge_);

      }


      JNIEXPORT void JNICALL Java_com_morphing_morobj_Linelabel_clearfirebmp0(JNIEnv* env, jobject obj,jlong nativeObj);
      JNIEXPORT void JNICALL Java_com_morphing_morobj_Linelabel_clearfirebmp0(JNIEnv* env, jobject obj,jlong nativeObj){

    	      Line_label& lineobj=*((Line_label*)nativeObj);
    		  lineobj.fireWall.setTo(0);
      }


      JNIEXPORT void JNICALL Java_com_morphing_morobj_Linelabel_setFpoint0(JNIEnv* env, jobject obj,jlong nativeObj,jintArray fpoint);
      JNIEXPORT void JNICALL Java_com_morphing_morobj_Linelabel_setFpoint0(JNIEnv* env, jobject obj,jlong nativeObj,jintArray fpoint){

    	      Line_label& lineobj=*((Line_label*)nativeObj);
    	      jint* cbuf = env->GetIntArrayElements(fpoint, 0);
      		  int x=(int)(*cbuf);
      		  int y=(int)(int)(*(cbuf+1));
      		  *lineobj.alph8.ptr<uchar>(y,x)=255;
      }


      JNIEXPORT void JNICALL Java_com_morphing_morobj_Linelabel_clearMemStorage0(JNIEnv* env, jobject obj,jlong nativeObj);
      JNIEXPORT void JNICALL Java_com_morphing_morobj_Linelabel_clearMemStorage0(JNIEnv* env, jobject obj,jlong nativeObj){

    	  Line_label& lineobj=*((Line_label*)nativeObj);
    	  lineobj.clearMemStorage();
    	  vector<vector<CvSeq*> >().swap(*lineobj.linetotal);
      }


      JNIEXPORT void JNICALL Java_com_morphing_morobj_Linelabel_delete0(JNIEnv* env, jobject obj,jlong nativeObj);
      JNIEXPORT void JNICALL Java_com_morphing_morobj_Linelabel_delete0(JNIEnv* env, jobject obj,jlong nativeObj){

    	  Line_label& lineobj=*((Line_label*)nativeObj);
                   lineobj._Line_label();

      }


  }
