#include "jni.h"
#include "android/bitmap.h"
#include "mycpp.h"

using namespace cv;


  extern "C"
  {

  JNIEXPORT jlong JNICALL Java_com_morphing_morobj_Morphing_morphing0(JNIEnv* env, jobject obj,jlong nativeObj);
  JNIEXPORT jlong JNICALL Java_com_morphing_morobj_Morphing_morphing0(JNIEnv* env, jobject obj,jlong nativeObj){

     Morphing *mor=new Morphing((Line_label*)nativeObj);
	 return (jlong)mor;
}


        JNIEXPORT jlong JNICALL Java_com_morphing_morobj_Morphing_morphing2(JNIEnv* env, jobject obj,jlong nativeObj);
        JNIEXPORT jlong JNICALL Java_com_morphing_morobj_Morphing_morphing2(JNIEnv* env, jobject obj,jlong nativeObj){

        	Morphing&   mor = *((Morphing*)nativeObj);
            Morphing   *_mor=new Morphing(mor);
            _mor->monitor=new int[18];
            for(int i=0;i<=17;i++)
            {
            	_mor->monitor[i]=1;
            }
      	    return (jlong)_mor;

      }


        JNIEXPORT void JNICALL Java_com_morphing_morobj_Morphing_setlineobj0(JNIEnv* env, jobject obj,jlong nativeObj,jlong labelnativeObj);
        JNIEXPORT void JNICALL Java_com_morphing_morobj_Morphing_setlineobj0(JNIEnv* env, jobject obj,jlong nativeObj,jlong labelnativeObj){

        	Morphing&   mor = *((Morphing*)nativeObj);
            mor.lineobj=(Line_label*)labelnativeObj;

      }



        JNIEXPORT void JNICALL Java_com_morphing_morobj_Morphing_getaxis10(JNIEnv* env, jobject obj,jlong nativeObj,jintArray fpoint1, jintArray fpoint2,jintArray fpoint3,jint contour_number);
        JNIEXPORT void JNICALL Java_com_morphing_morobj_Morphing_getaxis10(JNIEnv* env, jobject obj,jlong nativeObj,jintArray fpoint1, jintArray fpoint2,jintArray fpoint3,jint contour_number){

        	    Morphing&   mor = *((Morphing*)nativeObj);

          		  jint* cbuf1;
          		  jint* cbuf2;
          		  jint* cbuf3;


                 cbuf1 = env->GetIntArrayElements(fpoint1, 0);
          		 cbuf2 = env->GetIntArrayElements(fpoint2, 0);
          		 cbuf3 = env->GetIntArrayElements(fpoint3, 0);

          		 CvPoint point1,point2,point3;
          		 point1.x=(int)(*cbuf1);
          		 point1.y=(int)(*(cbuf1+1));
          		 point2.x=(int)(*cbuf2);
          		 point2.y=(int)(*(cbuf2+1));
          		 point3.x=(int)(*cbuf3);
          		 point3.y=(int)(*(cbuf3+1));
          		 mor.rpoint=point3;

          		 mor.getaxis1(point1,point2,point3,(int)contour_number);
          		 mor.getaxis2(point3,(int)contour_number);


            }




        JNIEXPORT void JNICALL Java_com_morphing_morobj_Morphing_initParam0(JNIEnv* env, jobject obj,jlong nativeObj,jfloat sig, jfloat synratio);
        JNIEXPORT void JNICALL Java_com_morphing_morobj_Morphing_initParam0(JNIEnv* env, jobject obj,jlong nativeObj,jfloat sig, jfloat synratio){
        	Morphing&   mor = *((Morphing*)nativeObj);

               mor.sig=(double)sig;
           if((float)synratio<0.01)
               mor.synrtio=0.01;
           else
        	   mor.synrtio=(double)synratio;
        }

        JNIEXPORT void JNICALL Java_com_morphing_morobj_Morphing_setcontourcolor0(JNIEnv* env, jobject obj,jlong nativeObj);
        JNIEXPORT void JNICALL Java_com_morphing_morobj_Morphing_setcontourcolor0(JNIEnv* env, jobject obj,jlong nativeObj){
                   Morphing& mor=*((Morphing*)nativeObj);
                   mor.lineobj->release(3);
                   Mat tmp=mor.lineobj->bmpsig;
                   CvPoint point5;
                   for(int i=0;i<mor.contour_new_coordin.cols;++i)
                      {
                         point5.x=*mor.contour_new_coordin.ptr<int>(0,i);
                         point5.y=*mor.contour_new_coordin.ptr<int>(1,i);
                         if(point5.x>=0&&point5.y>=0&&point5.x<tmp.cols&&point5.y<tmp.rows)
                         {
                         tmp.at<Vec4b>(point5)=Vec4b(0,255,0,255);
                         }
                       }
                }


        JNIEXPORT void JNICALL Java_com_morphing_morobj_Morphing_setLine0(JNIEnv* env, jobject obj,jlong nativeObj,jint n);
        JNIEXPORT void JNICALL Java_com_morphing_morobj_Morphing_setLine0(JNIEnv* env, jobject obj,jlong nativeObj,jint n){
                   Morphing& mor=*((Morphing*)nativeObj);
                   CvPoint pt;
                   Mat tmp=mor.lineobj->bmpsig;

                   //更新temp_edge;
                   if((int)n==1){
            		   for (int i=0;i<mor.seq1->total;i++)
            		      {
            		        CvPoint current_point=*CV_GET_SEQ_ELEM(CvPoint,mor.seq1,i);
            		        tmp.at<Vec4b>(current_point)=Vec4b(0,0,0,0);
            		      }
                	   for(int i=0;i<mor.contour_new_coordin1.cols;++i)
                	      {
                	        pt.x=*mor.contour_new_coordin1.ptr<int>(0,i);
                	        pt.y=*mor.contour_new_coordin1.ptr<int>(1,i);
                	        if(pt.x>=0&&pt.y>=0&&pt.x<tmp.cols&&pt.y<tmp.rows)
                	          {
                	            tmp.at<Vec4b>(pt)=Vec4b(0,255,0,255);
                	          }
                	       }
                   }
                   else if((int)n==2){
            		   for (int i=0;i<mor.seq1->total;i++)
            		      {
            		        CvPoint current_point=*CV_GET_SEQ_ELEM(CvPoint,mor.seq1,i);
            		        tmp.at<Vec4b>(current_point)=Vec4b(0,0,0,0);
            		      }
            		   for (int i=0;i<mor.seq2->total;i++)
            		      {
            		        CvPoint current_point=*CV_GET_SEQ_ELEM(CvPoint,mor.seq2,i);
            		        tmp.at<Vec4b>(current_point)=Vec4b(0,0,0,0);
            		      }

                	   for(int i=0;i<mor.contour_new_coordin1.cols;++i)
                	      {
                	        pt.x=*mor.contour_new_coordin1.ptr<int>(0,i);
                	        pt.y=*mor.contour_new_coordin1.ptr<int>(1,i);
                	        if(pt.x>=0&&pt.y>=0&&pt.x<tmp.cols&&pt.y<tmp.rows)
                	          {
                	            tmp.at<Vec4b>(pt)=Vec4b(0,255,0,255);
                	          }
                	       }
                	   for(int i=0;i<mor.contour_new_coordin2.cols;++i)
                	      {
                	        pt.x=*mor.contour_new_coordin2.ptr<int>(0,i);
                	        pt.y=*mor.contour_new_coordin2.ptr<int>(1,i);
                	        if(pt.x>=0&&pt.y>=0&&pt.x<tmp.cols&&pt.y<tmp.rows)
                	          {
                	            tmp.at<Vec4b>(pt)=Vec4b(0,255,0,255);
                	          }
                	       }

                   }

                }


        JNIEXPORT void JNICALL Java_com_morphing_morobj_Morphing_clearLine0(JNIEnv* env, jobject obj,jlong nativeObj,jint n);
        JNIEXPORT void JNICALL Java_com_morphing_morobj_Morphing_clearLine0(JNIEnv* env, jobject obj,jlong nativeObj,jint n){
                   Morphing& mor=*((Morphing*)nativeObj);
                   CvPoint pt;
                   Mat tmp=mor.lineobj->bmpsig;

                   //更新temp_edge;
                   if((int)n==1){
                	   for(int i=0;i<mor.contour_new_coordin1.cols;++i)
                	      {
                	        pt.x=*mor.contour_new_coordin1.ptr<int>(0,i);
                	        pt.y=*mor.contour_new_coordin1.ptr<int>(1,i);
                	        if(pt.x>=0&&pt.y>=0&&pt.x<tmp.cols&&pt.y<tmp.rows)
                	          {
                	            tmp.at<Vec4b>(pt)=Vec4b(0,0,0,0);
                	          }
                	       }
                   }
                   else if((int)n==2){
                	   for(int i=0;i<mor.contour_new_coordin1.cols;++i)
                	      {
                	        pt.x=*mor.contour_new_coordin1.ptr<int>(0,i);
                	        pt.y=*mor.contour_new_coordin1.ptr<int>(1,i);
                	        if(pt.x>=0&&pt.y>=0&&pt.x<tmp.cols&&pt.y<tmp.rows)
                	          {
                	            tmp.at<Vec4b>(pt)=Vec4b(0,0,0,0);
                	          }
                	       }
                	   for(int i=0;i<mor.contour_new_coordin2.cols;++i)
                	      {
                	        pt.x=*mor.contour_new_coordin2.ptr<int>(0,i);
                	        pt.y=*mor.contour_new_coordin2.ptr<int>(1,i);
                	        if(pt.x>=0&&pt.y>=0&&pt.x<tmp.cols&&pt.y<tmp.rows)
                	          {
                	            tmp.at<Vec4b>(pt)=Vec4b(0,0,0,0);
                	          }
                	       }

                   }
                }




        JNIEXPORT void JNICALL Java_com_morphing_morobj_Morphing_runmorphing(JNIEnv* env, jobject obj,jlong nativeObj,jintArray point4,jint num_rpoint,jint contour_number);
        JNIEXPORT void JNICALL Java_com_morphing_morobj_Morphing_runmorphing(JNIEnv* env, jobject obj,jlong nativeObj,jintArray point4,jint num_rpoint,jint contour_number){
        	               Morphing&   mor = *((Morphing*)nativeObj);
                           mor.lineobj->release(3);

                           Mat tmp=mor.lineobj->bmpsig;
        	               CvPoint point5;
        	               if((int)contour_number==1)
        	            	   mor.contour_new_coordin=mor.contour_new_coordin1;
        	               else if((int)contour_number==2)
        	            	   mor.contour_new_coordin=mor.contour_new_coordin2;
                           if(mor.contour_new_coordin.data!=NULL){
        	               for(int i=0;i<mor.contour_new_coordin.cols;++i)
        	                 {
        	                   point5.x=*mor.contour_new_coordin.ptr<int>(0,i);
        	                   point5.y=*mor.contour_new_coordin.ptr<int>(1,i);
        	                   if(point5.x>=0&&point5.x<tmp.cols&&point5.y>=0&&point5.y<tmp.rows)
        	                    {
        	                     tmp.at<Vec4b>(point5)=Vec4b(0,0,0,0);
        	                    }
        	                 }
                           }
                           jint* cbuf;
                           cbuf = env->GetIntArrayElements(point4, 0);
                           CvPoint pt;
                           pt.x=(int)(*cbuf);
                           pt.y=(int)(*(cbuf+1));
                           mor.getaxis2(pt,(int)contour_number);
                           mor.getpoint((int)contour_number);

                           int smooth_step;
                           if(mor.seq->total>60)
                        	   smooth_step=8;
                           else if(mor.seq->total<10)
                        	   smooth_step=4;
                           else
                        	   smooth_step=6;

                           mor.smoothcontour(smooth_step,2);
                           linization(mor.contour_new_coordin).copyTo(mor.contour_new_coordin);
                           *mor.graspPoint.ptr<double>(0,0)=(double)cvRound(*mor.graspPoint.ptr<double>(0,0));
                           *mor.graspPoint.ptr<double>(1,0)=(double)cvRound(*mor.graspPoint.ptr<double>(1,0));
                           mor.smoothcontour(smooth_step,1);
                           linization(mor.contour_new_coordin).copyTo(mor.contour_new_coordin);
                           *mor.graspPoint.ptr<double>(0,0)=(double)cvRound(*mor.graspPoint.ptr<double>(0,0));
                           *mor.graspPoint.ptr<double>(1,0)=(double)cvRound(*mor.graspPoint.ptr<double>(1,0));

                           if((int)contour_number==1)
                           {
                        	   //压栈
                        	   mor.release(14);
                        	   mor.contour_new_coordin.copyTo(mor.contour_new_coordin1);
                           }
                           else if((int)contour_number==2)
                           {
                        	   //压栈
                        	   mor.release(15);
                        	   mor.contour_new_coordin.copyTo(mor.contour_new_coordin2);
                           }

                           //锟斤拷锟斤拷graspPoint;
                           jclass morph = (env)->FindClass("com/morphing/morobj/Morphing");
                           jfieldID grasppoint = (env)->GetFieldID(morph,"graspPoint","[I");
                           jintArray t1=env->NewIntArray(2);
                           jint* int_t1=env->GetIntArrayElements(t1,NULL);
                           int a1=*mor.graspPoint.ptr<double>(0,0);
                           int a2=*mor.graspPoint.ptr<double>(1,0);
                           env->SetIntArrayRegion(t1, 0, 1,(jint*)&a1);
                           env->SetIntArrayRegion(t1, 1, 1,(jint*)&a2);
                           env->SetObjectField(obj,grasppoint,t1);
                           env->ReleaseIntArrayElements(t1,int_t1,JNI_ABORT);
  }


        JNIEXPORT jboolean JNICALL Java_com_morphing_morobj_Morphing_Islogical0(JNIEnv* env, jobject obj,jlong nativeObj,jintArray temp_edge);
        JNIEXPORT jboolean JNICALL Java_com_morphing_morobj_Morphing_Islogical0(JNIEnv* env, jobject obj,jlong nativeObj,jintArray temp_edge){


        	               Morphing&   mor = *((Morphing*)nativeObj);
        	               if(mor.seq1)
        	               {
                           jint* cbuf;
                           cbuf = env->GetIntArrayElements(temp_edge, 0);
                           CvPoint pt;
                           pt.x=(int)(*cbuf);
                           pt.y=(int)(*(cbuf+1));
                           int ind;
                           schar* b1=cvSeqSearch(mor.seq1,&pt,0,0,&ind);
                           if(b1==NULL)
                           {
                        	   return (jboolean)true;
                           }
                           else
                           {
                        	   return (jboolean)false;
                           }
        	               }
        	               else
                          return (jboolean)true;

  }




        JNIEXPORT void JNICALL Java_com_morphing_morobj_Morphing_generateimage0(JNIEnv* env, jobject obj,jlong nativeObj,jint n);
        JNIEXPORT void JNICALL Java_com_morphing_morobj_Morphing_generateimage0(JNIEnv* env, jobject obj,jlong nativeObj,jint n){
                           Morphing&   mor = *((Morphing*)nativeObj);

                           //压栈
//                           mor.lineobj->release(5);

                           Mat tmp=mor.lineobj->bmp;
                           Mat _tmp=mor.lineobj->_bmp;
                           Mat tmp1=mor.lineobj->bmp1;
                           Mat mdf=mor.lineobj->mdf;

                           if((int)n==0||(int)n==1)
                           {
                        	   mor.inpute_region2p(1);
                           }
                           else if((int)n==2)
                           {
                               mor.inpute_region4p(1);
                           }

                           double a=(double)(mor.lineobj->bmp1.rows)/(double)(mor.lineobj->bmp.rows);
                           double b=(double)(mor.lineobj->bmp1.cols)/(double)(mor.lineobj->bmp.cols);
                           for (int i=0;i<mor.new_region.rows;++i)
                           	{	int a1=*mor.new_region.ptr<int>(i,1);
                           	    int a2=*mor.new_region.ptr<int>(i,0);
                           	    int a33=*mor.map_region.ptr<int>(1,i);
                           	    int a44=*mor.map_region.ptr<int>(0,i);
                                if(a33>=0&&a33<tmp.rows&&a44>=0&&a44<tmp.cols)
                                {
                                	if(*mdf.ptr<uchar>(a33,a44)==0)
                                	{
                                		int a3=(a33+1)*a-1;
                                		int a4=(a44+1)*b-1;
                           		        *tmp.ptr<Vec4b>(a1,a2)=*tmp1.ptr<Vec4b>(a3,a4);
                                	}
                                	else
                                		*tmp.ptr<Vec4b>(a1,a2)=*_tmp.ptr<Vec4b>(a33,a44);
                                }
                           	}

                           if((int)n==0||(int)n==1)
                           {
                        	   if(mor.left_region.rows>0)
                                 mor.inpute_region2p(2);
                           }
                           else if((int)n==2)
                           {
                        	   if(mor.left_region.rows>0)
                                 mor.inpute_region4p(2);
                           }
                           for (int i=0;i<mor.left_region.rows;++i)
                           	{	int a1=*mor.left_region.ptr<int>(i,1);
                           	    int a2=*mor.left_region.ptr<int>(i,0);
                           	    int a33=*mor.map_region.ptr<int>(1,i);
                           	    int a44=*mor.map_region.ptr<int>(0,i);
                                if(a33>=0&&a33<tmp.rows&&a44>=0&&a44<tmp.cols)
                                {
                                	if(*mdf.ptr<uchar>(a33,a44)==0)
                                	{
                                		int a3=(a33+1)*a-1;
                                		int a4=(a44+1)*b-1;
                           		        *tmp.ptr<Vec4b>(a1,a2)=*tmp1.ptr<Vec4b>(a3,a4);
                                	}
                                	else
                                		*tmp.ptr<Vec4b>(a1,a2)=*_tmp.ptr<Vec4b>(a33,a44);
                                }
                           	}
                        }


        JNIEXPORT void JNICALL Java_com_morphing_morobj_Morphing_generatecontour0(JNIEnv* env, jobject obj,jlong nativeObj,jint contour_number);
        JNIEXPORT void JNICALL Java_com_morphing_morobj_Morphing_generatecontour0(JNIEnv* env, jobject obj,jlong nativeObj,jint contour_number){
                                   Morphing&   mor = *((Morphing*)nativeObj);

                                   Mat tmp=mor.lineobj->bmpsig;

                                   for (int i=0;i<mor.contour_new_coordin.cols;++i)
                                      {
                                	   int i1=*mor.contour_new_coordin.ptr<int>(1,i);
                                	   int i2=*mor.contour_new_coordin.ptr<int>(0,i);
                                	   if(i1>=0&&i1<tmp.rows&&i2>=0&&i2<tmp.cols)
                                        *tmp.ptr<Vec4b>(i1,i2)=Vec4b(0,0,0,0);
                                      }
                                   int smooth_step;
                                   if(mor.seq->total>60)
                                	   smooth_step=8;
                                   else if(mor.seq->total<10)
                                	   smooth_step=4;
                                   else
                                	   smooth_step=6;
                                	   mor.getpoint((int)contour_number);
                                	   mor.smoothcontour(smooth_step,2);
                                	   linization(mor.contour_new_coordin).copyTo( mor.contour_new_coordin);
                                       *mor.graspPoint.ptr<double>(0,0)=(double)cvRound(*mor.graspPoint.ptr<double>(0,0));
                                       *mor.graspPoint.ptr<double>(1,0)=(double)cvRound(*mor.graspPoint.ptr<double>(1,0));
                                	   mor.smoothcontour(smooth_step,1);
                                	   linization(mor.contour_new_coordin).copyTo( mor.contour_new_coordin);
                                       *mor.graspPoint.ptr<double>(0,0)=(double)cvRound(*mor.graspPoint.ptr<double>(0,0));
                                       *mor.graspPoint.ptr<double>(1,0)=(double)cvRound(*mor.graspPoint.ptr<double>(1,0));

                                   for (int i=0;i<mor.contour_new_coordin.cols;++i)
                                   	{
                                	   int i1=*mor.contour_new_coordin.ptr<int>(1,i);
                                	   int i2=*mor.contour_new_coordin.ptr<int>(0,i);
                                	   if(i1>=0&&i1<tmp.rows&&i2>=0&&i2<tmp.cols)
                                   		*tmp.ptr<Vec4b>(i1,i2)=Vec4b(0,255,0,255);
                                   	}

                                   if((int)contour_number==1)
                                   {
                                	   //压栈
//                                	   mor.release(14);
                                	   mor.contour_new_coordin.copyTo(mor.contour_new_coordin1);
                                   }
                                   else if((int)contour_number==2)
                                   {
                                	   //压栈
//                                	   mor.release(15);
                                	   mor.contour_new_coordin.copyTo(mor.contour_new_coordin2);
                                   }
                                   //锟斤拷锟斤拷graspPoint;
                                   jclass morph = (env)->FindClass("com/morphing/morobj/Morphing");
                                   jfieldID grasppoint = (env)->GetFieldID(morph,"graspPoint","[I");
                                   jintArray t1=env->NewIntArray(2);
                                   jint* int_t1=env->GetIntArrayElements(t1,NULL);
                                   int a1=*mor.graspPoint.ptr<double>(0,0);
                                   int a2=*mor.graspPoint.ptr<double>(1,0);
                                   env->SetIntArrayRegion(t1, 0, 1,(jint*)&a1);
                                   env->SetIntArrayRegion(t1, 1, 1,(jint*)&a2);
                                   env->SetObjectField(obj,grasppoint,t1);
                                   env->ReleaseIntArrayElements(t1,int_t1,JNI_ABORT);

                                }


        JNIEXPORT jboolean JNICALL Java_com_morphing_morobj_Morphing_generate0(JNIEnv* env, jobject obj,jlong nativeObj,jint num_rpoint);
        JNIEXPORT jboolean JNICALL Java_com_morphing_morobj_Morphing_generate0(JNIEnv* env, jobject obj,jlong nativeObj,jint num_rpoint){


                           Morphing&   mor = *((Morphing*)nativeObj);
                           bool clear=false;
                           //压栈
                           Mat tmp=mor.lineobj->bmp;
                           Mat _tmp=mor.lineobj->_bmp;
                           Mat tmp1=mor.lineobj->bmp1;
                           Mat mdf=mor.lineobj->mdf;

                           if((int)num_rpoint==0||(int)num_rpoint==1)
                           {
                           	if( mor.get_originregion2p())
                           	 if(mor.get_region2p())
                           	 {
                           	   mor.inpute_region2p(1);
                           	   clear=true;
                           	 }
                           }
                           else if((int)num_rpoint==2)
                           {
                           	if(mor.get_originregion4p())
                           	if(mor.get_region4p())
                           	{
                           	  mor.inpute_region4p(1);
                           	  clear=true;
                           	}
                           }

                           if(clear)
                           {
                         	   mor.lineobj->release(5);
                           double a=(double)(mor.lineobj->bmp1.rows)/(double)(mor.lineobj->bmp.rows);
                           double b=(double)(mor.lineobj->bmp1.cols)/(double)(mor.lineobj->bmp.cols);
                           for (int i=0;i<mor.new_region.rows;++i)
                           	{	int a1=*mor.new_region.ptr<int>(i,1);
                           	    int a2=*mor.new_region.ptr<int>(i,0);
                           	    int a33=*mor.map_region.ptr<int>(1,i);
                           	    int a44=*mor.map_region.ptr<int>(0,i);
                                if(a33>=0&&a33<tmp.rows&&a44>=0&&a44<tmp.cols)
                                {
                                	if(*mdf.ptr<uchar>(a33,a44)==0)
                                	{
                                		int a3=(a33+1)*a-1;
                                		int a4=(a44+1)*b-1;
                           		        *tmp.ptr<Vec4b>(a1,a2)=*tmp1.ptr<Vec4b>(a3,a4);
                                	}
                                	else
                                		*tmp.ptr<Vec4b>(a1,a2)=*_tmp.ptr<Vec4b>(a33,a44);
                                }
                           	}
                           mor.get_leftregion();
                           if((int)num_rpoint==0||(int)num_rpoint==1)
                           {
                        	   if(mor.left_region.rows>0)
                                  mor.inpute_region2p(2);
                           }
                           else if((int)num_rpoint==2)
                           {
                        	   if(mor.left_region.rows>0)
                                  mor.inpute_region4p(2);
                           }
                           for (int i=0;i<mor.left_region.rows;++i)
                           	{	int a1=*mor.left_region.ptr<int>(i,1);
                           	    int a2=*mor.left_region.ptr<int>(i,0);
                           	    int a33=*mor.map_region.ptr<int>(1,i);
                           	    int a44=*mor.map_region.ptr<int>(0,i);
                                if(a33>=0&&a33<tmp.rows&&a44>=0&&a44<tmp.cols)
                                {
                                	if(*mdf.ptr<uchar>(a33,a44)==0)
                                	{
                                		int a3=(a33+1)*a-1;
                                		int a4=(a44+1)*b-1;
                           		        *tmp.ptr<Vec4b>(a1,a2)=*tmp1.ptr<Vec4b>(a3,a4);
                                	}
                                	else
                                		*tmp.ptr<Vec4b>(a1,a2)=*_tmp.ptr<Vec4b>(a33,a44);
                                }
                           	}

                           }
                     return (jboolean)clear;
                        }




        JNIEXPORT void JNICALL Java_com_morphing_morobj_Morphing_delete0(JNIEnv* env, jobject obj,jlong nativeObj);
        JNIEXPORT void JNICALL Java_com_morphing_morobj_Morphing_delete0(JNIEnv* env, jobject obj,jlong nativeObj){

        	Morphing&   mor = *((Morphing*)nativeObj);
            mor._Morphing();

      }
  }
