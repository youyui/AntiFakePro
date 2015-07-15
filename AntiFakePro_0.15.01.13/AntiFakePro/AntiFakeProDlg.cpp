
// AntiFakeProDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AntiFakePro.h"
#include "AntiFakeProDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IplImage *cjImage1;
IplImage *cjImage2;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAntiFakeProDlg 对话框




CAntiFakeProDlg::CAntiFakeProDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAntiFakeProDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_dist = 0.0;
	m_message = _T("");
}

void CAntiFakeProDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DIST, m_dist);
	DDX_Text(pDX, IDC_STATIC_MEAASGE, m_message);
}

BEGIN_MESSAGE_MAP(CAntiFakeProDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPENSRCONE, &CAntiFakeProDlg::OnBnClickedButtonOpensrcone)
	ON_BN_CLICKED(IDC_BUTTON_OPENSRCTWO, &CAntiFakeProDlg::OnBnClickedButtonOpensrctwo)
	ON_BN_CLICKED(IDC_BUTTON_PROPROCES, &CAntiFakeProDlg::OnBnClickedButtonProproces)
	ON_BN_CLICKED(IDC_BUTTON_FEATURE, &CAntiFakeProDlg::OnBnClickedButtonFeature)
	ON_BN_CLICKED(IDC_BUTTON_CANDIST, &CAntiFakeProDlg::OnBnClickedButtonCandist)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CAntiFakeProDlg 消息处理程序

BOOL CAntiFakeProDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	stdImage1 = cvCreateImage(cvSize(NORM_WIDTH,NORM_HEIGHT),8,1);
	stdImage2 = cvCreateImage(cvSize(NORM_WIDTH,NORM_HEIGHT),8,1);
#if CUT
	textureImage1 = cvCreateImage(cvSize(NORM_WIDTH-CUT_WIDTH,NORM_HEIGHT-CUT_HEIGHT),8,1);
	textureImage2 = cvCreateImage(cvSize(NORM_WIDTH-CUT_WIDTH,NORM_HEIGHT-CUT_HEIGHT),8,1);
    cjImage1 = cvCreateImage(cvSize(NORM_WIDTH-CUT_WIDTH,NORM_HEIGHT-CUT_HEIGHT),8,1);
	cjImage2 = cvCreateImage(cvSize(NORM_WIDTH-CUT_WIDTH,NORM_HEIGHT-CUT_HEIGHT),8,1);
#else
	textureImage1 = cvCreateImage(cvSize(NORM_WIDTH,NORM_HEIGHT),8,1);
	textureImage2 = cvCreateImage(cvSize(NORM_WIDTH,NORM_HEIGHT),8,1);
#endif
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAntiFakeProDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

HBRUSH CAntiFakeProDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	
	switch(pWnd->GetDlgCtrlID()){
		case IDC_STATIC_MEAASGE : pDC->SetTextColor(RGB(255,0,0)); break;
	}
	return hbr;
}

void CAntiFakeProDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAntiFakeProDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/////////////////////////////////////////////////////////////////////
/////////////////////////Start from here////////////////////////////
////////////////////////////////////////////////////////////////////
void CAntiFakeProDlg::OnBnClickedButtonOpensrcone()
{
	// TODO: 
	CString strPath=GetPathname();
	srcImage1=cvLoadImage(strPath);
	DrawPicToHDC(srcImage1,IDC_STATIC_SRC1);
}


void CAntiFakeProDlg::OnBnClickedButtonOpensrctwo()
{
	// TODO: 
	CString strPath=GetPathname();
	srcImage2=cvLoadImage(strPath);
	DrawPicToHDC(srcImage2,IDC_STATIC_SRC2);
}


void CAntiFakeProDlg::OnBnClickedButtonProproces()
{
	// TODO:
	int blockSize = 25;
	int constValue = 10;//原先10
	IplConvKernel* Element = cvCreateStructuringElementEx(3,3,2,2,CV_SHAPE_ELLIPSE,NULL);//自己加的
	IplConvKernel* Element2 = cvCreateStructuringElementEx(3,3,1,1,CV_SHAPE_ELLIPSE,NULL);//自己加的
	IplConvKernel* Element3 = cvCreateStructuringElementEx(3,3,1,1,CV_SHAPE_CROSS,NULL);//自己加的
	IplConvKernel * myModel=cvCreateStructuringElementEx(5,5,2,2,CV_SHAPE_ELLIPSE); //自定义5*5,参考点（3,3）的矩形模板
//	IplConvKernel* Element = cvCreateStructuringElementEx(3,3,1,1,CV_SHAPE_CROSS,NULL);//自己加的
	//MSR(srcImage1,10,20,30,3);
	IplImage* grayImage1 = cvCreateImage(cvGetSize(srcImage1),8,1);
	IplImage*gra2 =  cvCreateImage(cvSize(400,400),8,1);
	
	cvCvtColor(srcImage1,grayImage1,CV_RGB2GRAY);
	cvResize(grayImage1,gra2);
	cvAdaptiveThreshold(gra2,gra2, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY_INV, blockSize, constValue);	
//	cvSmooth(gra2,gra2,CV_MEDIAN);  //中值滤波
	
	cvSaveImage("../result/src1_binary.bmp",gra2);
	IplImage *img_erode1 = cvCreateImage(cvGetSize(gra2), 8, 1);  
	IplImage *img_dilate1 = cvCreateImage(cvGetSize(gra2), 8, 1); 
	killnoise(gra2,gra2,1,2);
	denoise(gra2,gra2,2,3);
	cvDilate(gra2,img_dilate1,Element,1);
	cvSmooth(img_dilate1,img_dilate1,CV_MEDIAN);
// 	cvErode(img_dilate1,img_erode1,Element2,1);
// 
// 	denoise(img_erode1,img_erode1,3,3);
// 
// 	cvDilate(img_erode1,img_erode1,Element,1);


	cvSaveImage("../result/src2_dilate_erode.bmp",grayImage1);
	denoise(img_dilate1, gra2,2,3);
	cvSaveImage("../result/src1_denoise.bmp",gra2);
	cvCopy(gra2,stdImage1,0);
	cvSaveImage("../result/src1_norm.bmp",stdImage1);
	DrawPicToHDC(stdImage1, IDC_STATIC_SHOW);

	//MSR(srcImage2,10,20,30,3);
	IplImage* grayImage2 = cvCreateImage(cvGetSize(srcImage2),8,1);
	IplImage* gra22 = cvCreateImage(cvSize(400,400),8,1);
	cvCvtColor(srcImage2,grayImage2,CV_RGB2GRAY);
	cvResize(grayImage2,gra22,1);
	cvAdaptiveThreshold(gra22,gra22, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY_INV, blockSize, constValue);
//	cvSmooth(gra22,gra22,CV_MEDIAN);
	cvSaveImage("../result/src2_binary.bmp",gra22);
	IplImage *img_erode2 = cvCreateImage(cvGetSize(gra22), 8, 1);  
	IplImage *img_dilate2 = cvCreateImage(cvGetSize(gra22), 8, 1); 
	killnoise(gra22,gra22,1,2);
	denoise(gra22,gra22,2,3);
	cvDilate(gra22,img_dilate2,Element,1);
	cvSmooth(img_dilate2,img_dilate2,CV_MEDIAN);
// 	cvErode(img_dilate2,img_erode2,Element2,1);
// 
// 	denoise(img_erode2,img_erode2,3,3);
// 
// 	cvDilate(img_erode2,img_erode2,Element,1);

	cvSaveImage("../result/src2_dilate_erode.bmp",gra22);
	denoise(img_dilate2, gra22,2,3);
	cvSaveImage("../result/src2_denoise.bmp",gra22);
	cvCopy(gra22,stdImage2,0);
	cvSaveImage("../result/src2_norm.bmp",stdImage2);
	DrawPicToHDC(stdImage2, IDC_STATIC_SHOW_TWO);

#if CUT
	cvSetImageROI(stdImage1,cvRect(CUT_WIDTH/2,CUT_HEIGHT/2,stdImage1->width-CUT_WIDTH,stdImage1->height-CUT_HEIGHT));
	cvCopy(stdImage1,cjImage1);
	cvResetImageROI(stdImage1);
	cvSetImageROI(stdImage2,cvRect(CUT_WIDTH/2,CUT_HEIGHT/2,stdImage2->width-CUT_WIDTH,stdImage2->height-CUT_HEIGHT));
	cvCopy(stdImage2,cjImage2);
	cvResetImageROI(stdImage2);
#endif
	
}


void CAntiFakeProDlg::OnBnClickedButtonFeature()
{
	// TODO:
#if CUT
	cvCopy(cjImage1,textureImage1);
	cvCopy(cjImage2,textureImage2);
#else
	cvCopy(stdImage1,textureImage1);
	cvCopy(stdImage2,textureImage2);
#endif

	IplImage *textureImage1_rgb = cvCreateImage(cvGetSize(stdImage1),8,3);
	cvMerge(stdImage1,stdImage1,stdImage1,0,textureImage1_rgb);
	RegionLabel(stdImage1,textureImage1_rgb,50);    //连通域
	cvSaveImage("../result/src1_label.bmp",textureImage1_rgb);
	DrawPicToHDC(textureImage1_rgb, IDC_STATIC_SHOW);
	IplImage *textureImage2_rgb = cvCreateImage(cvGetSize(stdImage2),8,3);
	cvMerge(stdImage2,stdImage2,stdImage2,0,textureImage2_rgb);
	RegionLabel(stdImage2,textureImage2_rgb,50);
	cvSaveImage("../result/src2_label.bmp",textureImage2_rgb);
	DrawPicToHDC(textureImage2_rgb, IDC_STATIC_SHOW_TWO);

}


void CAntiFakeProDlg::OnBnClickedButtonCandist()
{
	// TODO:
	//cvSaveImage("1111.bmp",textureImage1);
	//cvSaveImage("2211.bmp",textureImage2);
	float machResult = FeatureMarch(textureImage1,textureImage2,50);
	m_dist = machResult;
	if(machResult>25.0){
		m_message = "Successfully! - 正品";
	}
	else{
		m_message = "Failed! - 非正品";
	}
	UpdateData(false);
#if 0
	int num_for = NORM_WIDTH/BLOCK_WIDTH*NORM_HEIGHT/BLOCK_HEIGHT;
	vector<IplImage*> imageout1 = division(textureImage1,BLOCK_WIDTH,BLOCK_HEIGHT);
	vector<IplImage*> imageout2 = division(textureImage2,BLOCK_WIDTH,BLOCK_HEIGHT);
	int hist_size = 256;
	double distan = 0.0f;
	CvHistogram *Histogram1 = cvCreateHist(1,&hist_size,CV_HIST_ARRAY);
	CvHistogram *Histogram2 = cvCreateHist(1,&hist_size,CV_HIST_ARRAY);
	for(int i = 0; i<num_for; i++){
		cvCalcHist(&imageout1.at(i),Histogram1,0,0);
		cvCalcHist(&imageout2.at(i),Histogram2,0,0);
		for(int j=0;j<hist_size;j++){
			distan += (Histogram1->mat.data.fl[0]-Histogram2->mat.data.fl[0])*(Histogram1->mat.data.fl[0]-Histogram2->mat.data.fl[0]);
		}
	}
	m_dist = sqrt(distan);
	UpdateData(false);
#endif
}


/////////////////////////////////////////////////////////////////////
void CAntiFakeProDlg::DrawPicToHDC(IplImage* img, UINT ID)
{
	CDC *pDC = GetDlgItem(ID)->GetDC();
	HDC hDC= pDC->GetSafeHdc();
	CRect rect; 
	GetDlgItem(ID)->GetClientRect(&rect); 
	CvvImage cimg; 
	cimg.CopyOf(img); 
	cimg.DrawToHDC(hDC,&rect); 
	ReleaseDC(pDC); 
}


//////////////////////////////////////////////////////////////////////
CString CAntiFakeProDlg::GetPathname(void)
{
	CString Pathstr;
	CFileDialog fileDlg( TRUE);
	fileDlg.m_ofn.lpstrTitle="Open IPEG Dialog";
	fileDlg.m_ofn.lpstrFilter="Jpeg File(*.jpg) \0 *.jpg";
	if(IDOK==fileDlg.DoModal())  
		Pathstr=fileDlg.GetPathName();
	else
		MessageBox("File Open Error!");
	return Pathstr;
}

///////////////////////////////////////////////////////////////////////
void CAntiFakeProDlg::denoise(IplImage* src, IplImage* dst,int iterations,int thresh)
{
	for( int i=0; i<iterations; i++ ){
		uchar *data=(uchar*)src->imageData;  
		int step=src->widthStep;  
		for (int i=3;i<src->height-3;i++){ 
			for(int j=3;j<src->width-3;j++)  
			{  
				if(0==data[i*step+j]) continue;
				int num = 0;
				if(255 == data[(i-3)*step+(j-3)]) { num++; }
				if(255 == data[(i-3)*step+(j-2)]) { num++; }
				if(255 == data[(i-3)*step+(j-1)]) { num++; }
				if(255 == data[(i-3)*step+(j  )]) { num++; }
				if(255 == data[(i-3)*step+(j+1)]) { num++; }
				if(255 == data[(i-3)*step+(j+2)]) { num++; }
				if(255 == data[(i-3)*step+(j+3)]) { num++; }
				if(255 == data[(i-2)*step+(j+3)]) { num++; }
				if(255 == data[(i-1)*step+(j+3)]) { num++; }
				if(255 == data[(i  )*step+(j+3)]) { num++; }
				if(255 == data[(i+1)*step+(j+3)]) { num++; }
				if(255 == data[(i+2)*step+(j+3)]) { num++; }
				if(255 == data[(i+3)*step+(j+3)]) { num++; }
				if(255 == data[(i+3)*step+(j+2)]) { num++; }
				if(255 == data[(i+3)*step+(j+1)]) { num++; }
				if(255 == data[(i+3)*step+(j  )]) { num++; }
				if(255 == data[(i+3)*step+(j-1)]) { num++; }
				if(255 == data[(i+3)*step+(j-2)]) { num++; }
				if(255 == data[(i+3)*step+(j-3)]) { num++; }
				if(255 == data[(i+2)*step+(j-3)]) { num++; }
				if(255 == data[(i+1)*step+(j-3)]) { num++; }
				if(255 == data[(i  )*step+(j-3)]) { num++; }
				if(255 == data[(i-1)*step+(j-3)]) { num++; }
				if(255 == data[(i-2)*step+(j-3)]) { num++; }
				if( num<thresh ){
					data[i*step+j] = 0;
				}
				else{
					data[i*step+j] = 255;
				}
			}  
			cvCopy(src,dst);
		}
	}
}

void CAntiFakeProDlg::killnoise(IplImage* src, IplImage* dst,int iterations,int thre)
{
	for( int i=0; i<iterations; i++ ){
		uchar *data=(uchar*)src->imageData;  
		int step=src->widthStep;  
		for (int i=1;i<src->height-1;i++){ 
			for(int j=1;j<src->width-1;j++)  
			{  
				if(0==data[i*step+j]) continue;
				int num = 0;
				if(255 == data[(i-1)*step+(j-1)]) { num++; }
				if(255 == data[(i-1)*step+(j)]) { num++; }
				if(255 == data[(i-1)*step+(j+1)]) { num++; }
				if(255 == data[(i)*step+(j-1)]) { num++; }
				if(255 == data[(i)*step+(j+1)]) { num++; }
				if(255 == data[(i+1)*step+(j-1)]) { num++; }
				if(255 == data[(i+1)*step+(j)]) { num++; }
				if(255 == data[(i+1)*step+(j+1)]) { num++; }
				if( num<thre ){
					data[i*step+j] = 0;
				}
				else{
					data[i*step+j] = 255;
				}
			}  
			cvCopy(src,dst);
		}
	}
}
//////////////////////////////////////////////////////////////////////
void CAntiFakeProDlg::RegionLabel(IplImage* src,IplImage*dst,double minarea)
{
	CvMemStorage* storage = cvCreateMemStorage(0);  
	CvSeq* contour = 0; 
	int count = 0; 
	static CvScalar colors[] = {  {{0,0,255}},{{0,128,255}},{{0,255,255}},{{0,255,0}}, 
	{{255,128,0}},{{255,255,0}},{{255,0,0}},{{255,0,255}} };

	int contour_num = cvFindContours(src, storage, &contour, sizeof(CvContour), CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);   
	for(; contour != 0; contour = contour->h_next)  
	{    
		count++;  
		double tmparea = fabs(cvContourArea(contour)); 
		CvRect aRect = cvBoundingRect( contour, 0 ); 
		if ( (tmparea <= minarea) ||  (aRect.height<10 && aRect.width<10) || ( aRect.x<10||aRect.y<10) ) {
			continue;
		}
		cvRectangle(dst, cvPoint(aRect.x,aRect.y), cvPoint(aRect.x+aRect.width,aRect.y+aRect.height), colors[count%8],1, 8, 0);
		CvFont font;
		cvInitFont( &font, CV_FONT_VECTOR0,0.3, 0.3, 0, 1, 8);
		char str[30];
		itoa((int)tmparea, str, 15);
		cvPutText(dst, str , cvPoint(aRect.x,aRect.y+10), &font, colors[count%8]);
	}
	printf("The total number of contours is:%d\n", count); 
}


//////////////////////////////////////////////////////////////////////
float CAntiFakeProDlg::FeatureMarch(IplImage* src1,IplImage*src2,double minarea)
{
	//cvSaveImage("1122.bmp",src1);
	//cvSaveImage("2222.bmp",src2);
	IplImage *src1_org = cvCloneImage(src1);
	IplImage *src2_org = cvCloneImage(src2);
	//cvSaveImage("1133.bmp",src1_org);
	//cvSaveImage("2233.bmp",src2_org);
	CvMemStorage* storage1 = cvCreateMemStorage(0); 
	CvMemStorage* storage2 = cvCreateMemStorage(0); 
	CvSeq* contour1 = 0;  
	int count1 = 0;      
	int contour_num1 = cvFindContours(src1, storage1, &contour1, sizeof(CvContour), CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE); 
	int num_match = 0;
	for(; contour1 != 0; contour1 = contour1->h_next)  
	{    
		double tmparea1 = fabs(cvContourArea(contour1)); 
		CvRect Rect1 = cvBoundingRect( contour1, 0 ); 
		if ( (tmparea1 <= minarea) ||  (Rect1.height<10 && Rect1.width<10) || (Rect1.x<10 || Rect1.y<10) ) {
			continue;
		}
		count1++;
		int count2 = 0;
		CvRect Rect2_min;
		int mindist = 99999;
	    CvSeq* contour2 = 0;
		int contour_num2 = cvFindContours(src2, storage2, &contour2, sizeof(CvContour), CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
		for(; contour2 != 0; contour2 = contour2->h_next)  
		{    
			count2++;  
			double tmparea2 = fabs(cvContourArea(contour2)); 
			CvRect Rect2 = cvBoundingRect( contour2, 0 ); 
			if(count2==1){Rect2_min = Rect2;}
			if ( (tmparea2 <= minarea) ||  (Rect2.height<10 && Rect2.width<10) || ( Rect2.x<10||Rect2.y<10) ) {
				continue;
			}
			int x = abs(Rect1.x - Rect2.x);
			int y = abs(Rect1.y - Rect2.y);
			int dist = (x*x+y*y);
			if( dist < mindist ){
				Rect2_min = Rect2;
				mindist = dist;
			}
		}   

		IplImage *src1_object = cvCreateImage(cvSize(Rect1.width,Rect1.height),8,1);
		IplImage *src2_object = cvCreateImage(cvSize(Rect2_min.width,Rect2_min.height),8,1);
		cvSetImageROI(src1_org,Rect1);
		cvSetImageROI(src2_org,Rect2_min);
		cvCopy(src1_org,src1_object);
		cvCopy(src2_org,src2_object);
		num_match = num_match + Cal_simil(src1_object,src2_object,mindist);
		cvResetImageROI(src1_org);
		cvResetImageROI(src2_org);
	}
	return (num_match*100.0/count1);
}


////////////////////////////////////////////////////////////////////
int CAntiFakeProDlg::Cal_simil(IplImage* src1,IplImage*src2,int mindist)
{
	cvSaveImage("123.bmp",src1);
	cvSaveImage("456.bmp",src2);

	int length1=0, length2=0;
	float angle1=0,  angle2=0;
	
	uchar *data1=(uchar*)src1->imageData;
	uchar *data2=(uchar*)src2->imageData;
	int step1=src1->widthStep; 
	int step2=src2->widthStep;

	// condition1: width/height < 4 pixel
	if( src1->width<=8 || src1->height<=8 ){
		length1 = src1->width <= src1->height ? src1->height : src1->width;
		angle1  = src1->width <= src1->height ? 90.0f        : 0.0f;  
	}
	else if ( src1->width > 5*src1->height){
		length1 = src1->width;
		angle1  = 0.0f; 
	}
	else if ( src1->height > 5*src1->width){
		length1 = src1->height;
		angle1  = 90.0f; 
	}
	else{
		angle1 = cal_angle(data1,step1,src1->width,src1->height);
		length1 = sqrt(double(src1->width*src1->width+src1->height*src1->height));
	}

	if( src2->width<=8 || src2->height<=8 ){
		length2 = src2->width <= src2->height ? src2->height : src2->width;
		angle2  = src2->width <= src2->height ? 90.0f        : 0.0f; 
	}
	else if ( src2->width > 5*src2->height){
		length2 = src2->width;
		angle2  = 0.0f; 
	}
	else if ( src2->height > 5*src2->width){
		length2 = src2->height;
		angle2  = 90.0f; 
	}
	else{
		angle2 = cal_angle(data2,step2,src2->width,src2->height);
		length2 = sqrt(double(src2->width*src2->width+src2->height*src2->height));
	}

	//匹配连通域 原150  60
	if( abs(angle1-angle2)<10 || (abs(angle1-angle2)>170) ){
		if( mindist<400 && abs(length1-length2)<150 ){
			return 1;
		}
		else{
			return  0;
		}
	}
	//原100  20
	else if( abs(angle1-angle2)<15 || (abs(angle1-angle2)>165) ){
		if( mindist<200 && abs(length1-length2)<80){
			return 1;
		}
		else{
			return  0;
		}
	}
	else{
		return  0;
	}
	return 0;
}


float CAntiFakeProDlg::cal_angle(uchar *data,int step,int width, int height)
{
	float angle = 0;
	int lt_numBlack=0, rt_numBlack=0, lb_numBlack=0, rb_numBlack=0;
	lt_numBlack = ( 0==data[0*step+0] ? (lt_numBlack+1) : (lt_numBlack) );
	lt_numBlack = ( 0==data[0*step+1] ? (lt_numBlack+1) : (lt_numBlack) );
	lt_numBlack = ( 0==data[1*step+0] ? (lt_numBlack+1) : (lt_numBlack) );
	rt_numBlack = ( 0==data[0*step+(width-1)]  ? (rt_numBlack+1) : (rt_numBlack) );
	rt_numBlack = ( 0==data[0*step+(width-2)]  ? (rt_numBlack+1) : (rt_numBlack) );
	rt_numBlack = ( 0==data[1*step+(width-1)]  ? (rt_numBlack+1) : (rt_numBlack) );
	lb_numBlack = ( 0==data[(height-1)*step+0] ? (lb_numBlack+1) : (lb_numBlack) );
	lb_numBlack = ( 0==data[(height-1)*step+1] ? (lb_numBlack+1) : (lb_numBlack) );
	lb_numBlack = ( 0==data[(height-2)*step+0] ? (lb_numBlack+1) : (lb_numBlack) );
	rb_numBlack = ( 0==data[(height-1)*(width-1)] ? (rb_numBlack+1) : (rb_numBlack) );
	rb_numBlack = ( 0==data[(height-1)*(width-2)] ? (rb_numBlack+1) : (rb_numBlack) );
	rb_numBlack = ( 0==data[(height-2)*(width-1)] ? (rb_numBlack+1) : (rb_numBlack) );
	if(lt_numBlack==0 && rt_numBlack==0 && lb_numBlack==0 && rb_numBlack==0 ){
		return angle;
	}
	int sort_point[4] = {lt_numBlack, rt_numBlack, lb_numBlack, rb_numBlack};
	int sortindex[4] = {0,1,2,3}; 
	for(int n=0; n<4;n++){
		for(int m=n+1; m<4; m++){
			if(sort_point[n]<sort_point[m]){
				int tem = sort_point[n];
				sort_point[n] = sort_point[m];
				sort_point[m] = tem;
				int index = sortindex[n];
				sortindex[n] = sortindex[m];
				sortindex[m] = index;
			}
		}
	}
	switch (sortindex[2]){
		case 0: switch(sortindex[3]){
					case 1: angle = 0.0f; break;
					case 2: angle = 90.0f; break;
					case 3: angle = 180.0f - atan(height*1.0/width); break;
				}
				break;
		case 1:switch(sortindex[3]){
					case 0: angle = 0.0f; break;
					case 2: angle = atan(height*1.0/width); break;
					case 3: angle = 90.0f; break;
			   }
			   break;
		case 2:switch(sortindex[3]){
					case 0: angle = 90.0f; break;
					case 1: angle = atan(height*1.0/width); break;
					case 3: angle = 90.0f; break;
			   }
			   break;
		case 3:switch(sortindex[3]){
					case 0: angle = 180.0f - atan(height*1.0/width); break;
					case 1: angle = 90.0f; break;
					case 2: angle =  0.0f; break;
			   }
			   break;
	}
	return angle;
}
