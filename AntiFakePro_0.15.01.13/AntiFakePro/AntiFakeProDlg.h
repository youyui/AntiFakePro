
// AntiFakeProDlg.h : ͷ�ļ�
//
#include "cv.h"
#include "highgui.h"
#include "CvvImage.h"
#include <math.h>
#include <vector>
using namespace std;

#define CUT   1
#define CUT_WIDTH   40
#define CUT_HEIGHT  40
#define NORM_WIDTH    400
#define NORM_HEIGHT   400
#define BLOCK_WIDTH   50
#define BLOCK_HEIGHT  50


#pragma once
// CAntiFakeProDlg �Ի���
class CAntiFakeProDlg : public CDialogEx
{
// ����
public:
	CAntiFakeProDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ANTIFAKEPRO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	//my function 
	IplImage *srcImage1;
	IplImage *srcImage2;
	IplImage *stdImage1;
	IplImage *stdImage2;
	IplImage* textureImage1;
	IplImage* textureImage2;
	void DrawPicToHDC(IplImage * img, UINT ID);
	CString GetPathname();
	void denoise(IplImage* src, IplImage* dst,int iterations,int thresh);
	void killnoise(IplImage* src,IplImage* dst,int iterations,int thre);
	void RegionLabel(IplImage* src,IplImage*dst,double minarea);
	float FeatureMarch(IplImage* src1,IplImage*src2,double minarea);
	int Cal_simil(IplImage* src1,IplImage*src2,int mindist);
	float cal_angle(uchar *data,int step,int width, int height);

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	double m_dist;
	afx_msg void OnBnClickedButtonOpensrcone();
	afx_msg void OnBnClickedButtonOpensrctwo();
	afx_msg void OnBnClickedButtonProproces();
	afx_msg void OnBnClickedButtonFeature();
	afx_msg void OnBnClickedButtonCandist();
	CString m_message;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
