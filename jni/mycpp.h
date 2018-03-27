#ifndef _MYCPP_H
#define _MYCPP_H



#include <opencv2/opencv.hpp>

#ifdef __cplusplus
#include <math.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <vector>
#include <set>
#include <algorithm>




 namespace cv{


class Line_label{
public:
    int* monitor;
	void release(int i);
	Mat _bmp;
	int static picw;
	int static pich;

 vector<vector<CvSeq*> >* linetotal;
 Mat edge;
 Mat _edge;
 Mat alph8;
 Mat bmp;
 Mat bmp1;
 Mat mdf;
 Mat bmpsig;
 Mat fireWall;
 bool newele_needed;
 bool Is_single;
 Mat Label_Mat;
 Mat Label_Mat_std;
 int num;
 int* Label_Mat_data;

 CvMemStorage* storage;
Line_label(Mat& _src);

void refreshEdge(Mat& edge);

void addEdge_prehandle(Mat& _src);

void line_label(Mat& src,int N_bw);

void line_label4(Mat& src);

void line_label8(Mat& src);

vector<CvSeq*> getseq(Mat_<uchar>::iterator it,int N_bw);
 
void _Line_label();

void clearMemStorage();

};


class sortCriterion {
public:
    bool operator() (const CvPoint& a, const CvPoint& b) const ;
};


class Get_line
{
public:

bool    clear;
bool    contain;
CvSeq*  seq;
static vector<CvSeq*> segvec;
Line_label* lineobj;

Get_line(Line_label* lineobj);

Get_line();

void refresh();

void refresh1();

CvSeq* getline(CvPoint point1,CvPoint point2);

void getline1(Get_line& line,CvPoint point1,CvPoint point2,CvPoint point3);

CvSeq* get_circleline(CvPoint point1,CvPoint point2,CvPoint point3);

void checkLine(Get_line& line,CvPoint point1,CvPoint point2,CvPoint point3);
};


CvSeq* linear_link(CvPoint point1,CvPoint point2,bool add_endpoint);

vector<CvPoint> find_neibors(CvPoint pt,int range,Mat& Label_Mat);

double point_dist(CvPoint pt1,CvPoint pt2);

Mat getvector(CvPoint& pt1,CvPoint& pt2);

bool Is_neg(Mat& arr1,Mat& arr2,double alpha);

Mat linization(Mat& src);

bool operator== (const CvPoint &a, const CvPoint &b) ;
template <class InputIterator, class T>bool _find( InputIterator first,InputIterator last,const T& value);

void alrm_signal(int);

void refreshStorage0();


class Morphing
{
public:

	int* monitor;
	void release(int i);

	Line_label* lineobj;

	CvSeq *seq;
	CvSeq *seq1;
	CvSeq *seq2;

	double sig;
	double  synrtio;

	double alpha1;
	double alpha2;
	double alpha4;
	double alpha5;

	Mat graspPoint;

	Mat origin_region;
	Mat origin_regionmat;
	Mat new_regionmat;
	Mat new_region;
	Mat map_region;
	Mat left_region;

	Mat    contour_new_coordin;
	Mat    contour_new_coordin1;
	Mat    contour_new_coordin2;
	Mat    contour_origin_coordin;//��������ߵĳ�ʼ���
	Mat    contour_origin_coordin1;
	Mat    contour_origin_coordin2;

	Morphing();
    Morphing(Line_label* lineobj);
    void _Morphing();
	void getaxis1(CvPoint pt1,CvPoint pt2,CvPoint pt3,int n);
	void getaxis2(CvPoint pt,int n);
	void getpoint(int n);//��������������
	void getpoint4p();
	void smoothcontour(int n,int cyn);

	void getregion(Mat& contour_mat,Mat& region_mat,Mat& region_mat1,Mat& region,Mat& mat_region);
	bool get_originregion2p();
	bool get_region2p();
	bool get_originregion4p();
	bool get_region4p();
	void get_leftregion();
	void get_innerpoint(Mat& region_mat,Mat& region,Mat& mat_region,int point[],int n);
	void inpute_region2p(int n);
	void inpute_region4p(int n);
	CvPoint fpoint1;
    CvPoint fpoint2;
    CvPoint rpoint;
    CvPoint rpoint1;
    CvPoint rpoint2;
	Mat A1,_A1,B1,_B1,C1,_C1,D1,_D1,E1,_E1;
    Mat A2,_A2,B2,_B2,C2,_2C,D2,_D2,E2,_E2;
private:

    Mat P1,P2;

	double* length11;
	double* length12;
	double* length21;
	double* length22;
	Mat  length_r1;
	Mat  length_r2;

};


class Firewall{
public :
	Mat firebmp;

};

}
#endif

#else

#endif
