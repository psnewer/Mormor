#include "jni.h"
#include <signal.h>
#include <errno.h>
#include <time.h>
#include "android/bitmap.h"
#include "mycpp.h"
using namespace cv;

  extern "C"
  {

  JNIEXPORT jlong JNICALL Java_com_morphing_morobj_Getline_getline2(JNIEnv* env, jobject obj,jlong nativeObj);
  JNIEXPORT jlong JNICALL Java_com_morphing_morobj_Getline_getline2(JNIEnv* env, jobject obj,jlong nativeObj){

	 Get_line* Line1=new Get_line();
	 Line1->lineobj=(Line_label*)nativeObj;
	 return (jlong)Line1;

}


  JNIEXPORT void JNICALL Java_com_morphing_morobj_Getline_setLineobj0(JNIEnv* env, jobject obj,jlong getlinenativeobj,jlong nativeObj);
  JNIEXPORT void JNICALL Java_com_morphing_morobj_Getline_setLineobj0(JNIEnv* env, jobject obj,jlong getlinenativeobj,jlong nativeObj){

	 Get_line& Line1=*((Get_line*)getlinenativeobj);
	 Line1.lineobj=(Line_label*)nativeObj;
}



            pthread_mutex_t mutex_timeout;
    		pthread_cond_t  cond_timeout;
    		struct parameter
    		         {
    		        	CvPoint pt1;
    		        	CvPoint pt2;
    		        	CvPoint pt3;
    		        	long nativeObj;
    		         };
    		 void* thread_work(void * param)
    		  {

    			 struct parameter *pstru;
    			       pstru = ( struct parameter *) param;
    			       Get_line& Line1=*((Get_line*)pstru->nativeObj);
    			       if(pstru->pt3.x!=-1)
    			         Line1.get_circleline(pstru->pt1,pstru->pt2,pstru->pt3);
    			       else
    			    	 Line1.seq=Line1.getline(pstru->pt1,pstru->pt2);
    		          pthread_mutex_lock(&mutex_timeout);
    		          pthread_cond_signal(&cond_timeout);
    		          pthread_mutex_unlock(&mutex_timeout);
    		      return NULL;
    		  }

        JNIEXPORT jint JNICALL Java_com_morphing_morobj_Getline_getline0(JNIEnv* env, jobject obj,jlong nativeObj,jintArray fpoint1, jintArray fpoint2,jintArray fpoint3);
        JNIEXPORT jint JNICALL Java_com_morphing_morobj_Getline_getline0(JNIEnv* env, jobject obj,jlong nativeObj,jintArray fpoint1, jintArray fpoint2,jintArray fpoint3){

  		  jint* cbuf1;
  		  jint* cbuf2;
  		  jint* cbuf3;

          jint clear=0;
          cbuf1 = env->GetIntArrayElements(fpoint1, 0);
  		  cbuf2 = env->GetIntArrayElements(fpoint2, 0);
  		  cbuf3 = env->GetIntArrayElements(fpoint3, 0);

  		  Get_line& Line1=*((Get_line*)nativeObj);

  		  struct parameter arg;
  		  CvPoint point1,point2,point3;
  		  arg.pt1.x=(int)(*cbuf1);
  		  arg.pt1.y=(int)(*(cbuf1+1));
  		  arg.pt2.x=(int)(*cbuf2);
  		  arg.pt2.y=(int)(*(cbuf2+1));
  		  arg.pt3.x=(int)(*cbuf3);
  		  arg.pt3.y=(int)(*(cbuf3+1));
          arg.nativeObj=(long)nativeObj;

  		  pthread_mutex_init(&mutex_timeout, NULL);
  		  pthread_cond_init(&cond_timeout, NULL);

         pthread_t thread;
         int rc;
         struct sigaction action;
         memset(&action, 0, sizeof(action));
         sigemptyset(&action.sa_mask);
         action.sa_flags = 0;
         action.sa_handler = alrm_signal;
         rc = sigaction(SIGALRM, &action, NULL);
         if(rc)
             {
                 exit(1);
             }

         struct timespec m_time;
         m_time.tv_sec = time(NULL) + 3;
         m_time.tv_nsec = 0;

         Line1.refresh();
         rc = pthread_create(&thread, NULL, thread_work, &arg);
         if(rc)
          {
            exit(1);
          }

         pthread_mutex_lock(&mutex_timeout);
         int res = pthread_cond_timedwait(&cond_timeout, &mutex_timeout, (const struct timespec *)&m_time);
         pthread_mutex_unlock(&mutex_timeout);
         if(res == ETIMEDOUT)//timeout
          {
           pthread_kill(thread, SIGALRM);
           refreshStorage0();
           Line1.refresh();
           clear=5;
          }
         else{
              if(Line1.clear)
               {
                clear=1;
               }
              else
               {
            	  if(!Line1.segvec.empty())
                  clear=2;
               }
                     }

  		 return clear;
    }






        JNIEXPORT jint JNICALL Java_com_morphing_morobj_Getline_getline3(JNIEnv* env, jobject obj,jlong nativeObj,jintArray fpoint1, jintArray fpoint2);
        JNIEXPORT jint JNICALL Java_com_morphing_morobj_Getline_getline3(JNIEnv* env, jobject obj,jlong nativeObj,jintArray fpoint1, jintArray fpoint2){


          		  jint* cbuf1;
          		  jint* cbuf2;

                  jint clear=0;
                  cbuf1 = env->GetIntArrayElements(fpoint1, 0);
          		  cbuf2 = env->GetIntArrayElements(fpoint2, 0);

          		  struct parameter arg;
          		  arg.pt1.x=(int)(*cbuf1);
          		  arg.pt1.y=(int)(*(cbuf1+1));
          		  arg.pt2.x=(int)(*cbuf2);
          		  arg.pt2.y=(int)(*(cbuf2+1));
          		  arg.pt3.x=-1;
          		  arg.pt3.y=-1;
          		  arg.nativeObj=(long)nativeObj;

          		  pthread_mutex_init(&mutex_timeout, NULL);
          		  pthread_cond_init(&cond_timeout, NULL);

          		  Get_line& Line1=*((Get_line*)nativeObj);

          		pthread_t thread;
          		int rc;
          		struct sigaction action;
          	    memset(&action, 0, sizeof(action));
          		sigemptyset(&action.sa_mask);
          		action.sa_flags = 0;
          		action.sa_handler = alrm_signal;
          		rc = sigaction(SIGALRM, &action, NULL);
          		if(rc)
          		  {
          		   exit(1);
          		  }
          		struct timespec m_time;
          		m_time.tv_sec = time(NULL) + 3;
          		m_time.tv_nsec = 0;

          		Line1.refresh();
          		rc = pthread_create(&thread, NULL, thread_work, &arg);

          		if(rc)
          		  {
          		   exit(1);
          		  }

          		pthread_mutex_lock(&mutex_timeout);
          		int res = pthread_cond_timedwait(&cond_timeout, &mutex_timeout, (const struct timespec *)&m_time);
          		pthread_mutex_unlock(&mutex_timeout);
          		if(res == ETIMEDOUT)//timeout
          		  {
          		   pthread_kill(thread, SIGALRM);
          		   refreshStorage0();
          		   Line1.refresh();
          		   clear=5;
          		  }
          	    else{
          		      if(Line1.clear)
          		        {
          		          clear=3;
          		        }
          		      else
          		        {
          		    	  if(!Line1.segvec.empty())
          		          clear=4;
          		        }
          		    }

          	return clear;

            }




        JNIEXPORT void JNICALL Java_com_morphing_morobj_Getline_lineRefresh0(JNIEnv* env, jobject obj,jlong nativeObj,jlong mornativeObj,jint num_rpoint,jint clear);
        JNIEXPORT void JNICALL Java_com_morphing_morobj_Getline_lineRefresh0(JNIEnv* env, jobject obj,jlong nativeObj,jlong mornativeObj,jint num_rpoint,jint clear){

  		 Get_line& Line1=*((Get_line*)nativeObj);
         Morphing& mor=*((Morphing*)mornativeObj);

  		 if((int)clear==1)
  		 {
  			 mor.lineobj->release(3);

  			 Mat tmp=Line1.lineobj->bmpsig;
  			 mor.seq=Line1.seq;
  			 for(int i=0;i<mor.seq->total;i++)
  			 {
  				CvPoint point5=*CV_GET_SEQ_ELEM(CvPoint,Line1.seq,i);
  				tmp.at<Vec4b>(point5)=Vec4b(0,255,0,255);
  			 }


  			int (*p);
  			    p=new int[Line1.seq->total*2];
  				cvCvtSeqToArray(Line1.seq,p);
  				Mat mm(Line1.seq->total,2,CV_32SC1,p);
  				transpose(mm,mm);
  				mm.copyTo(mor.contour_new_coordin);

  	  			 if((int)num_rpoint==0)
  	  			 {
  	  				 mor.release(14);
  	  				 mor.seq1=Line1.seq;
  	  				 mor.contour_new_coordin.copyTo(mor.contour_new_coordin1);
  	  			 }

  	  			 else if((int)num_rpoint==1)
  	  			 {
  	  				 mor.release(15);
  	  				 mor.seq2=Line1.seq;
  	  				 mor.contour_new_coordin.copyTo(mor.contour_new_coordin2);
  	  			 }
  	    		 //回收内存
  	    		 delete[] p;
  		 }
  		 else if((int)clear==2)
  		 {
  			 Mat tmp=Line1.lineobj->bmpsig;

  			for(vector<CvSeq*>::iterator it=Line1.segvec.begin();it!=Line1.segvec.end();++it)
  			{
  	  			 for(int i=0;i<(*it)->total;i++)
  	  			 {
  	  				CvPoint point5=*CV_GET_SEQ_ELEM(CvPoint,*it,i);
  	  				tmp.at<Vec4b>(point5)=Vec4b(255,255,255,255);
  	  			 }
  			}
  		 }

  		 Line1.refresh();
  		 refreshStorage0();

    }


        JNIEXPORT void JNICALL Java_com_morphing_morobj_Getline_lineRefresh1(JNIEnv* env, jobject obj,jlong nativeObj,jlong mornativeObj,jobject firebmp,jint clear);
        JNIEXPORT void JNICALL Java_com_morphing_morobj_Getline_lineRefresh1(JNIEnv* env, jobject obj,jlong nativeObj,jlong mornativeObj,jobject firebmp,jint clear){

          		 Get_line& Line1=*((Get_line*)nativeObj);
                 Morphing& mor=*((Morphing*)mornativeObj);

                 AndroidBitmapInfo  info;
                 void*              pixels = 0;
                 CV_Assert( AndroidBitmap_getInfo(env, firebmp, &info) >= 0 );
                 CV_Assert( info.format == ANDROID_BITMAP_FORMAT_RGBA_8888 ||
                 info.format == ANDROID_BITMAP_FORMAT_RGB_565 );
                 CV_Assert( AndroidBitmap_lockPixels(env, firebmp, &pixels) >= 0 );
                 CV_Assert( pixels );
                 Mat tmp(info.height, info.width, CV_8UC4, pixels);

                 if((int)clear==3){
                 for(int i=0;i<Line1.seq->total;i++)
                   {
                      CvPoint pt=*CV_GET_SEQ_ELEM(CvPoint,Line1.seq,i);
                      tmp.at<Vec4b>(pt)=Vec4b(0,255,255,255);
                      mor.lineobj->fireWall.at<uchar>(pt)=255;
                   }
                 }
                 else if((int)clear==4){
                	 for(vector<CvSeq*>::iterator it=Line1.segvec.begin();it!=Line1.segvec.end();++it)
                	   	{
                	   	  	for(int i=0;i<(*it)->total;i++)
                	   	  	 {
                	   	  		CvPoint point5=*CV_GET_SEQ_ELEM(CvPoint,*it,i);
                	   	  		tmp.at<Vec4b>(point5)=Vec4b(255,255,255,255);
                	   	  	  }
                	   	}
                 }

                 AndroidBitmap_unlockPixels(env, firebmp);
                 Line1.refresh();
                 refreshStorage0();

            }



        JNIEXPORT jlong JNICALL Java_com_morphing_morobj_Getline_getSeq0(JNIEnv* env, jobject obj,jlong nativeObj);
        JNIEXPORT jlong JNICALL Java_com_morphing_morobj_Getline_getSeq0(JNIEnv* env, jobject obj,jlong nativeObj){

      	 Get_line& Line1=*((Get_line*)nativeObj);
      	 return (jlong)Line1.seq;

      }


        JNIEXPORT void JNICALL Java_com_morphing_morobj_Getline_clearMem0(JNIEnv* env, jobject obj,jlong nativeObj);
        JNIEXPORT void JNICALL Java_com_morphing_morobj_Getline_clearMem0(JNIEnv* env, jobject obj,jlong nativeObj){

      	 Get_line& Line1=*((Get_line*)nativeObj);
      	 Line1.refresh();
      	 Line1.~Get_line();

      }
  }
