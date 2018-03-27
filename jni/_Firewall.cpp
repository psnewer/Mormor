#include "jni.h"
#include "android/bitmap.h"
#include "mycpp.h"
using namespace cv;


  extern "C"
  {


  JNIEXPORT jlong JNICALL Java_org_opencv_Mormor_FireWall_FireWall0(JNIEnv* env, jobject obj,jobject bmp);
  JNIEXPORT jlong JNICALL Java_org_opencv_Mormor_FireWall_FireWall0(JNIEnv* env, jobject obj,jobject bmp){

	             Firewall* fire=new Firewall();
      	  		 AndroidBitmapInfo  info;
      	         void*              pixels = 0;
      	  		 CV_Assert( AndroidBitmap_getInfo(env, bmp, &info) >= 0 );
      	         CV_Assert( AndroidBitmap_lockPixels(env, bmp, &pixels) >= 0 );
      	         CV_Assert( pixels );
      	  		 Mat temp(info.height,info.width,CV_8UC4,pixels);
      	  		 fire->firebmp=temp;
      	  		 AndroidBitmap_unlockPixels(env, bmp);
      	  		 return (jlong)fire;
    }

  JNIEXPORT void JNICALL Java_org_opencv_Mormor_FireWall_setContour0(JNIEnv* env, jobject obj,jlong lineobjnativeObj,jlong nativeObj,jlong seq);
  JNIEXPORT void JNICALL Java_org_opencv_Mormor_FireWall_setContour0(JNIEnv* env, jobject obj,jlong lineobjnativeObj,jlong nativeObj,jlong seq){

	             Firewall&   fire = *((Firewall*)nativeObj);
	             Line_label&  lineobj=*((Line_label*)lineobjnativeObj);
	             CvSeq* _seq=(CvSeq*)seq;
	             for(int i=0;i<_seq->total;i++)
	                {
	                   CvPoint pt=*CV_GET_SEQ_ELEM(CvPoint,_seq,i);
	                   fire.firebmp.at<Vec4b>(pt)=Vec4b(0,255,255,255);
	                   lineobj.fireWall.at<uchar>(pt)=255;
	                }
    }







  }
