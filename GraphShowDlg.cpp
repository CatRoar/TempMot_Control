// GraphShowDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Template_Control.h"
#include "GraphShowDlg.h"
#include "afxdialogex.h"

// CGraphShowDlg 对话框

IMPLEMENT_DYNAMIC(CGraphShowDlg, CDialogEx)

CGraphShowDlg::CGraphShowDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGraphShowDlg::IDD, pParent)
{
	Gdiplus::GdiplusStartup(&m_pGdiToken, &m_gdiplusStartupInput, NULL);
}

CGraphShowDlg::~CGraphShowDlg()
{
	if (bitmap != nullptr)
	{
		delete bitmap;
		bitmap = nullptr;
	}
	Gdiplus::GdiplusShutdown(m_pGdiToken);
}

void CGraphShowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CHECK1, m_TempCheck1);
	DDX_Control(pDX, IDC_CHECK2, m_TempCheck2);
	DDX_Control(pDX, IDC_CHECK3, m_TempCheck3);
	DDX_Control(pDX, IDC_CHECK4, m_TempCheck4);
	DDX_Control(pDX, IDC_CHECK5, m_TempCheck5);
	DDX_Control(pDX, IDC_CHECK6, m_TempCheck6);
	DDX_Control(pDX, IDC_CHECK7, m_TempCheck7);
	DDX_Control(pDX, IDC_CHECK8, m_TempCheck8);
	DDX_Control(pDX, IDC_CHECK9, m_TempCheck9);
	DDX_Control(pDX, IDC_CHECK10, m_TempCheck10);
	DDX_Control(pDX, IDC_CHECK11, m_TempCheck11);
	DDX_Control(pDX, IDC_EDIT1, m_TimeStartCtr);
	DDX_Control(pDX, IDC_EDIT2, m_TimeEndCtr);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_TimeStart);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_DateStart);
	DDX_Control(pDX, IDC_DATETIMEPICKER3, m_DateEnd);
	DDX_Control(pDX, IDC_DATETIMEPICKER4, m_TimeEnd);
}


BEGIN_MESSAGE_MAP(CGraphShowDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CGraphShowDlg::OnBnClickedButton1)
	ON_WM_MOUSEWHEEL()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CHECK1, &CGraphShowDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CGraphShowDlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CGraphShowDlg::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK4, &CGraphShowDlg::OnBnClickedCheck4)
	ON_BN_CLICKED(IDC_CHECK5, &CGraphShowDlg::OnBnClickedCheck5)
	ON_BN_CLICKED(IDC_CHECK6, &CGraphShowDlg::OnBnClickedCheck6)
	ON_BN_CLICKED(IDC_CHECK7, &CGraphShowDlg::OnBnClickedCheck7)
	ON_BN_CLICKED(IDC_CHECK8, &CGraphShowDlg::OnBnClickedCheck8)
	ON_BN_CLICKED(IDC_CHECK9, &CGraphShowDlg::OnBnClickedCheck9)
	ON_BN_CLICKED(IDC_CHECK10, &CGraphShowDlg::OnBnClickedCheck10)
	ON_BN_CLICKED(IDC_CHECK11, &CGraphShowDlg::OnBnClickedCheck11)
END_MESSAGE_MAP()


// CGraphShowDlg 消息处理程序
BOOL CGraphShowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CWnd *pWnd = NULL;

	for (int i = 0; i < 11; i++)
	{
		m_ValidFlag[i] = 0;
	}
	m_PaintFlag = FALSE;
	pDC = NULL;
	
	pWnd = GetDlgItem(IDC_STATIC_GRAPH);//获取控件句柄  
	
	pWnd->GetWindowRect(&windowRect);
	staticRect = windowRect;
	ScreenToClient(&staticRect);
	windowRect.top += staticRect.top;
	windowRect.left += staticRect.left;
	windowRect.bottom += staticRect.top;
	windowRect.right += staticRect.left;
	m_Rect.Height = staticRect.bottom - staticRect.top;
	m_Rect.Width = staticRect.right - staticRect.left;
	m_Rect.X = 0;
	m_Rect.Y = 0;
	m_RectBmp.Height = staticRect.bottom - staticRect.top;
	m_RectBmp.Width = staticRect.right - staticRect.left;
	m_RectBmp.X = 0;
	m_RectBmp.Y = 0;
	
	bitmap = nullptr;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

afx_msg BOOL CGraphShowDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	CWnd *pWnd = NULL;
	pWnd = GetDlgItem(IDC_STATIC_GRAPH);//获取控件句柄  
	pWnd->GetWindowRect(&windowRect);
	staticRect = windowRect;
	ScreenToClient(&staticRect);
	windowRect.top += staticRect.top;
	windowRect.left += staticRect.left;
	windowRect.bottom += staticRect.top;
	windowRect.right += staticRect.left;
	if (pt.x < windowRect.right && pt.x > windowRect.left && pt.y > windowRect.top && pt.y < windowRect.bottom)
	{
		m_RectBmp.X -= zDelta * 1;
	}
	if (m_PaintFlag == TRUE)
	{
		RePaint(bitmap);
	}
	return true;
}

afx_msg void CGraphShowDlg::OnPaint()
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
	CWnd *pWnd = NULL;
	pWnd = GetDlgItem(IDC_STATIC_GRAPH);//获取控件句柄  
	pWnd->GetWindowRect(&windowRect);

	staticRect = windowRect;
	ScreenToClient(&staticRect);
	windowRect.top += staticRect.top;
	windowRect.left += staticRect.left;
	windowRect.bottom += staticRect.top;
	windowRect.right += staticRect.left;

	if (m_PaintFlag == TRUE)
	{
		RePaint(bitmap);
	}
}

int CGraphShowDlg::RePaint(Gdiplus::Bitmap *bitmap)
{
	float scale = 1;
	int width = 0, height = 0, widthClient = 0, heightClient = 0;
	int x = 0, y = 0;

	if (bitmap == NULL)
	{
		return -1;
	}

	CWnd *pWnd = NULL;
	pWnd = GetDlgItem(IDC_STATIC_GRAPH);//获取控件句柄  
	pWnd->GetWindowRect(&windowRect);
	pDC = pWnd->GetDC();

	auto bmHeight = bitmap->GetHeight();
	auto bmWidth = bitmap->GetWidth();
	if (pDC != NULL && pDC->m_hDC != NULL)
	{
		Gdiplus::Graphics g(pDC->m_hDC);

		if (m_RectBmp.Y < 0 || bmHeight != 260 || bmWidth < 1)
		{
			return -1;
		}

		if (m_RectBmp.X < 0)
		{
			m_RectBmp.X = 0;
		}

		scale = (float)bmHeight / (float)m_Rect.Height;
		width = (int)m_Rect.Width * scale;
		height = bmHeight;
		x = (int)m_RectBmp.X * scale;
		widthClient = m_Rect.Width;
		heightClient = m_Rect.Height;

		if (width > bmWidth)
		{
			width = bmWidth;
			m_Rect.Width = bmWidth;
		}
		else if (m_RectBmp.X + width > bmWidth)
		{
			x = bmWidth - width;
			m_RectBmp.X = x;
		}

		g.DrawImage(bitmap, m_Rect, x, y, width, height, Gdiplus::Unit::UnitPixel);

		ReleaseDC(pDC);
		pDC = NULL;
		return 1;
	}
	else
	{
		ReleaseDC(pDC);
		pDC = NULL;
		return -1;
	}

}

void CGraphShowDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	int dataLength = 0, height = 260, width = 0, heightY = 260 - 20 - 8, widthX = 0;
	bool flagF = false;
	float temp[11];
	float curMax = -1000, curMin = 1000;
	double step = 10.0, stepX = 100.0, stepY = 77;
	double scaleX = 1.0;
	double scaleY = 1.0;
	CString strTimeStart, strTimeEnd, strTimeStartEx, strTimeEndEx, strLog, strFN, strTag;
	time_t timec = 0, timep[2] = { 0 }, times[2] = { 0 };
	FILETIME ft;
	ULARGE_INTEGER uli;
	SYSTEMTIME lpSystemTime[2], lpSystemTimeTag;
	CStdioFile mf;
	vector<CString> vecFN;
	vector<time_t> vecTime;
	vector<float> vecData[11];

	m_DateStart.GetWindowTextA(strTimeStart);
	m_TimeStart.GetWindowTextA(strTimeStartEx);
	m_DateEnd.GetWindowTextA(strTimeEnd);
	m_TimeEnd.GetWindowTextA(strTimeEndEx);
	
	strTimeStart += "-";
	strTimeStart += strTimeStartEx;
	strTimeEnd += "-";
	strTimeEnd += strTimeEndEx;
	//strTimeStart.Format("2018:7:29:14:01:00");
	//strTimeEnd.Format("2018:7:29:14:02:00");

	StringToSysTime(strTimeStart, &lpSystemTime[0]);
	StringToSysTime(strTimeEnd, &lpSystemTime[1]);

	if ((SystemTimeToFileTime(&lpSystemTime[0], &ft)) == false)
	{
		MessageBox("无效起始时间");
		return;
	}
	uli.HighPart = ft.dwHighDateTime;
	uli.LowPart = ft.dwLowDateTime;
	times[0] = (double)uli.QuadPart / 10000.0;

	if ((SystemTimeToFileTime(&lpSystemTime[1], &ft)) == false)
	{
		MessageBox("无效起始时间");
		return;
	}
	uli.HighPart = ft.dwHighDateTime;
	uli.LowPart = ft.dwLowDateTime;
	times[1] = (double)uli.QuadPart / 10000.0;


	// 加载文件
	if (mf.Open("FileRecord.txt", CFile::modeRead) != true)
	{
		MessageBox("FileRecord无法加载");
		return;
	}

	while (false != mf.ReadString(strLog))
	{
		if (StringToData1(strLog, &timep[0], &timep[1], &strFN) == false)
		{
			MessageBox("FileRecord无法加载");
			return;
		}
		if (timep[0] <= times[0] && timep[1] >= times[1])
		{
			vecFN.push_back(strFN);
		}
		if (timep[0] <= times[0] && timep[1] >= times[0] && timep[1] < times[1])
		{
			vecFN.push_back(strFN);
		}
		if (timep[0] <= times[1] && timep[1] >= times[1] && timep[0] > times[0])
		{
			vecFN.push_back(strFN);
		}
		if (timep[0] > times[0] && timep[1] < times[1])
		{
			vecFN.push_back(strFN);
		}
	}
	if (mf.m_hFile != CFile::hFileNull)
	{
		mf.Close();
	}
	if (vecFN.size() == 0)
	{
		MessageBox("没有相关数据");
		return;
	}

	dataLength = (double)(times[1] - times[0]) / (double)500;

	if (dataLength > 500)
	{
		step = 5000.0 / (double)dataLength;
		stepX = 10.0 * 5000.0 / (double)dataLength;
	}

	width = dataLength * step + 0.000001;

	// 为GDI 绘图创建文件流 --------------------------------
	IStream *pStrmBmp;
	BITMAPFILEHEADER fileHeader;
	BITMAPINFOHEADER bitmapHeader;

	CreateStreamOnHGlobal(NULL, TRUE, &pStrmBmp);

	//Create Bitmap File Header
	fileHeader.bfType = 0x4D42;
	fileHeader.bfSize = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+width*height * 3;
	fileHeader.bfReserved1 = 0;
	fileHeader.bfReserved2 = 0;
	fileHeader.bfOffBits = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);

	//Create Bitmap Info Header
	bitmapHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapHeader.biWidth = width;
	bitmapHeader.biHeight = height;
	bitmapHeader.biPlanes = 1;
	bitmapHeader.biBitCount = 24;
	bitmapHeader.biCompression = 0;		//BI_RGB
	bitmapHeader.biSizeImage = width*height * 3;

	//write data, white color
	BYTE *data = new BYTE[width * height * 3]();
	for (int i = 0; i < width * height * 3; ++i)
	{
		data[i] = 0;
	}

	pStrmBmp->Write(&fileHeader, sizeof(BITMAPFILEHEADER), NULL);
	pStrmBmp->Write(&bitmapHeader, sizeof(BITMAPINFOHEADER), NULL);
	pStrmBmp->Write(data, width * height * 3, NULL);

	//-----------------------------------------------------
	if (bitmap != nullptr)
	{
		delete bitmap;
		bitmap = nullptr;
	}
	bitmap = new Gdiplus::Bitmap(pStrmBmp);

	Gdiplus::Graphics g(bitmap);

	Gdiplus::Point pntAxis[3];
	Gdiplus::Point pntData[11];
	Gdiplus::PointF pntTag[2];
	Gdiplus::Point pntDataPre[11];
	Gdiplus::Point pntDataSeg[2];

	Gdiplus::Color cData[11] = { Color(255, 0, 0), Color(191, 63, 0), Color(128, 128, 0),
		Color(63, 191, 0), Color(0, 255, 0), Color(0, 191, 63), Color(0, 128, 128),
		Color(0, 63, 191), Color(0, 0, 255), Color(63, 0, 191), Color(128, 0, 128) };

	Gdiplus::Pen penAxis(Color(255, 255, 255), 2);
	Gdiplus::Pen penData0(Color(0, 0, 0), 1);
	SolidBrush  brushText(Color(255, 255, 255));
	/*Gdiplus::Pen penData1(Color(255, 0, 0), 1);
	Gdiplus::Pen penData2(Color(191, 63, 0), 1);
	Gdiplus::Pen penData3(Color(128, 128, 0), 1);
	Gdiplus::Pen penData4(Color(63, 191, 0), 1);
	Gdiplus::Pen penData5(Color(0, 255, 0), 1);
	Gdiplus::Pen penData6(Color(0, 191, 63), 1);
	Gdiplus::Pen penData7(Color(0, 128, 128), 1);
	Gdiplus::Pen penData8(Color(0, 63, 191), 1);
	Gdiplus::Pen penData9(Color(0, 0, 255), 1);
	Gdiplus::Pen penData10(Color(63, 0, 191), 1);
	Gdiplus::Pen penData11(Color(128, 0, 128), 1);
	Gdiplus::Pen penData(Color(128, 0, 128), 1)[11];*/
	FontFamily fontFamily(L"SimSun");
	Gdiplus::Font font(&fontFamily, 12, FontStyleRegular, UnitPixel);

	Gdiplus::Status gStatus;
	bool flagBroken = 0;

	//bitmap.create;
	pntAxis[0].X = 40;
	pntAxis[0].Y = 4;
	pntAxis[1].X = 40;
	pntAxis[1].Y = height - 20;
	pntAxis[2].X = width - 10;
	pntAxis[2].Y = height - 20;
	widthX = width - 50 - 8;

	gStatus = g.DrawLines(&penAxis, pntAxis, 3);
	penAxis.SetWidth(1);
	for (int i = 0; i < vecFN.size(); i++)
	{
		if (mf.Open(vecFN.at(i), CFile::modeRead) == false)
		{
			MessageBox("无法读取温度数据");
			return;
		}

		while (mf.ReadString(strLog))
		{
			if (strLog == "")
			{
				continue;
			}
			if (StringToData2(strLog, &timec, &temp[0], &temp[1], &temp[2], &temp[3],
				&temp[4], &temp[5], &temp[6], &temp[7], &temp[8], &temp[9], &temp[10]) == false)
			{
				MessageBox("FileRecord无法加载");
				return;
			}
			if (timec != 0 && timec < times[1] && timec > times[0])
			{
				vecTime.push_back(timec);
				for (int j = 0; j < 11; j++)
				{
					if (fabs(temp[j] - INVALID_TEMP) < 0.000001 || m_ValidFlag[j] == false)
					{
						vecData[j].push_back(temp[j]);
						continue;
					}
					vecData[j].push_back(temp[j]);
					if (temp[j] > curMax)
					{
						curMax = temp[j];
					}
					if (temp[j] < curMin)
					{
						curMin = temp[j];
					}
				}
			}
		}
		mf.Close();
	}

	scaleX = (double)widthX / (double)dataLength;
	scaleY = (double)heightY / (double)(curMax - curMin);

	for (int i = 0; i < 4; i++)
	{
		pntTag[0].Y = pntAxis[0].Y + stepY * i;
		pntTag[0].X = pntAxis[0].X - 40;
		strTag.Format("%5.1f", curMax - i * (curMax - curMin) / 3.0);
		g.DrawString(strTag.AllocSysString(), strTag.GetLength(), &font, pntTag[0], &brushText);
		pntTag[0].X = pntAxis[0].X - 4;
		pntTag[1].X = pntTag[0].X + widthX + 4;
		pntTag[1].Y = pntTag[0].Y;
		g.DrawLine(&penAxis, pntTag[0], pntTag[1]);
	}

	pntData[0].X = pntAxis[1].X + 4;
	pntData[0].Y = pntAxis[1].Y - (vecData[0].at(0) - curMin) * scaleY - 4;
	pntData[1].X = pntAxis[1].X + 4;
	pntData[1].Y = pntAxis[1].Y - (vecData[1].at(0) - curMin) * scaleY - 4;
	pntData[2].X = pntAxis[1].X + 4;
	pntData[2].Y = pntAxis[1].Y - (vecData[2].at(0) - curMin) * scaleY - 4;
	pntData[3].X = pntAxis[1].X + 4;
	pntData[3].Y = pntAxis[1].Y - (vecData[3].at(0) - curMin) * scaleY - 4;
	pntData[4].X = pntAxis[1].X + 4;
	pntData[4].Y = pntAxis[1].Y - (vecData[4].at(0) - curMin) * scaleY - 4;
	pntData[5].X = pntAxis[1].X + 4;
	pntData[5].Y = pntAxis[1].Y - (vecData[5].at(0) - curMin) * scaleY - 4;
	pntData[6].X = pntAxis[1].X + 4;
	pntData[6].Y = pntAxis[1].Y - (vecData[6].at(0) - curMin) * scaleY - 4;
	pntData[7].X = pntAxis[1].X + 4;
	pntData[7].Y = pntAxis[1].Y - (vecData[7].at(0) - curMin) * scaleY - 4;
	pntData[8].X = pntAxis[1].X + 4;
	pntData[8].Y = pntAxis[1].Y - (vecData[8].at(0) - curMin) * scaleY - 4;
	pntData[9].X = pntAxis[1].X + 4;
	pntData[9].Y = pntAxis[1].Y - (vecData[9].at(0) - curMin) * scaleY - 4;
	pntData[10].X = pntAxis[1].X + 4;
	pntData[10].Y = pntAxis[1].Y - (vecData[10].at(0) - curMin) * scaleY - 4;

	for (int i = 0; i < 11; i++)
	{
		pntDataPre[i] = pntData[i];
	}
	// 逐点绘制
	penData0.SetWidth(1);
	for (int i = 1; i < vecTime.size(); i++)
	{
		for (int j = 0; j < 11; j++)
		{
			if (fabs(vecData[j].at(i) - INVALID_TEMP) < 0.000001)
			{
				pntData[j].X = pntAxis[1].X + 4 + scaleX * (double)(vecTime.at(i) - vecTime.at(0)) / (double)500;
				//pntData[j].Y = pntAxis[1].Y;
				continue;
			}
			pntData[j].Y = pntAxis[1].Y - (vecData[j].at(i) - curMin) * scaleY - 4;
			pntData[j].X = pntAxis[1].X + 4 + scaleX * (double)(vecTime.at(i) - vecTime.at(0)) / (double)500;
		}
		if (abs(pntData[0].X - pntDataPre[0].X) < 2)
		{
			continue;
		}
		for (int j = 0; j < 11; j++)
		{
			if (fabs(vecData[j].at(i) - INVALID_TEMP) < 0.000001)
			{
				//pntData[j].Y = pntAxis[1].Y;
				continue;
			}
			if (vecTime.at(i) - vecTime.at(i - 1) > 999)
			{
				flagBroken = true;
			}
			if (m_ValidFlag[j] == true)
			{
				if (flagBroken == true)
				{
					flagBroken = false;
					pntDataSeg[0] = pntData[j];
				}
				else
				{
					pntDataSeg[0] = pntDataPre[j];
				}
				pntDataSeg[1] = pntData[j];
				penData0.SetColor(cData[j]);
				gStatus = g.DrawLines(&penData0, pntDataSeg, 2);
			}
		}
		if (i % 10 == 0)
		{
			pntTag[1].Y = pntAxis[1].Y + 4;
			pntTag[1].X = pntData[0].X;
			strTag.Format("%5.1f", (double)(vecTime.at(i) - vecTime.at(0)) / 1000.0);
			g.DrawString(strTag.AllocSysString(), strTag.GetLength(), &font, pntTag[1], &brushText);
			pntTag[0].X = pntTag[1].X;
			pntTag[0].Y = pntTag[1].Y - heightY - 8;
			g.DrawLine(&penAxis, pntTag[0], pntTag[1]);
		}
		for (int j = 0; j < 11; j++)
		{
			if (fabs(vecData[j].at(i) - INVALID_TEMP) < 0.000001)
			{
				//pntData[j].Y = pntAxis[1].Y;
				continue;
			}
			pntDataPre[j] = pntData[j];
		}
	}

	//g.DrawImage(&bitmap, &r, 0, 0, 1024, 512);
	string strFN2;
	CLSID pngClsid;
	WCHAR  *wcX;
	GetEncoderClsid(L"image/bmp", &pngClsid);
	strFN.Format("profile_%d-%d-%d_%d-%d-%dto%d-%d-%d_%d-%d-%d.bmp", lpSystemTime[0].wYear,
		lpSystemTime[0].wMonth, lpSystemTime[0].wDay, lpSystemTime[0].wHour, lpSystemTime[0].wMinute,
		lpSystemTime[0].wSecond, lpSystemTime[1].wYear, lpSystemTime[1].wMonth, lpSystemTime[1].wDay,
		lpSystemTime[1].wHour, lpSystemTime[1].wMinute, lpSystemTime[1].wSecond);
	wcX = strFN.AllocSysString();
	

	if (data)
	{
		delete data;
		data = NULL;
	}

	if (bitmap->GetLastStatus() == Gdiplus::Ok)
	{
		m_PaintFlag = true;
		RePaint(bitmap);
	}
	gStatus = bitmap->Save(wcX, &pngClsid, nullptr);
}


int CGraphShowDlg::GetEncoderClsid(const WCHAR* format, CLSID* pClsid)

{
	UINT  num = 0;          // number of image encoders
	UINT  size = 0;         // size of the image encoder array in bytes

	ImageCodecInfo* pImageCodecInfo = NULL;
	GetImageEncodersSize(&num, &size);

	if (size == 0)
		return -1;  // Failure

	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == NULL)
		return -1;  // Failure

	GetImageEncoders(num, size, pImageCodecInfo);

	for (UINT j = 0; j < num; ++j)
	{
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;  // Success
		}
	}


	free(pImageCodecInfo);
	return -1;  // Failure
}

BOOL CGraphShowDlg::StringToSysTime(CString strTime, SYSTEMTIME *lSystemTime)
{
	int index[2] = { 0 };
	int temp = 0;
	CString strTemp;

	/*for (int i = 0; i < strTime.GetLength(); i++)
	{
		if (strTime[i] < 48 || strTime[i] > 58)
		{
			return false;
		}
	}*/
	lSystemTime->wDayOfWeek = 0;
	lSystemTime->wMilliseconds = 0;
	// year
	index[1] = strTime.Find("/", index[0]);
	if (index[1] < 0)
	{
		return false;
	}
	strTemp = strTime.Mid(index[0], index[1] - index[0]);
	if (strTemp == "")
	{
		return false;
	}
	temp = _ttoi(strTemp);
	if (temp < 1900 || temp > 2100)
	{
		return false;
	}
	lSystemTime->wYear = (WORD)temp;
	index[0] = index[1] + 1;

	//month
	index[1] = strTime.Find("/", index[0]);
	if (index[1] < 0)
	{
		return false;
	}
	strTemp = strTime.Mid(index[0], index[1] - index[0]);
	if (strTemp == "")
	{
		return false;
	}
	temp = _ttoi(strTemp);
	if (temp < 1 || temp > 12)
	{
		return false;
	}
	lSystemTime->wMonth = (WORD)temp;
	index[0] = index[1] + 1;

	//date
	index[1] = strTime.Find("-", index[0]);
	if (index[1] < 0)
	{
		return false;
	}
	strTemp = strTime.Mid(index[0], index[1] - index[0]);
	if (strTemp == "")
	{
		return false;
	}
	temp = _ttoi(strTemp);
	if (temp < 1 || temp > 31)
	{
		return false;
	}
	lSystemTime->wDay = (WORD)temp;
	index[0] = index[1] + 1;

	// hour
	index[1] = strTime.Find(":", index[0]);
	if (index[1] < 0)
	{
		return false;
	}
	strTemp = strTime.Mid(index[0], index[1] - index[0]);
	if (strTemp == "")
	{
		return false;
	}
	temp = _ttoi(strTemp);
	if (temp < 0 || temp > 23)
	{
		return false;
	}
	lSystemTime->wHour = (WORD)temp;

	index[0] = index[1] + 1;

	// minute
	index[1] = strTime.Find(":", index[0]);
	if (index[1] < 0)
	{
		return false;
	}
	strTemp = strTime.Mid(index[0], index[1] - index[0]);
	if (strTemp == "")
	{
		return false;
	}
	temp = _ttoi(strTemp);
	if (temp < 0 || temp > 59)
	{
		return false;
	}
	lSystemTime->wMinute = (WORD)temp;
	index[0] = index[1] + 1;

	// second
	strTemp = strTime.Mid(index[0], strTemp.GetLength());
	if (strTemp == "")
	{
		return false;
	}
	temp = _ttoi(strTemp);
	if (temp < 0 || temp > 59)
	{
		return false;
	}
	lSystemTime->wSecond = (WORD)temp;



	return true;
}

BOOL CGraphShowDlg::StringToData1(CString strTime, time_t *time1, time_t *time2, CString *FileName)
{
	int index = 0, indexNext = 0;
	CString strTemp;
	if ((indexNext = strTime.Find(":", index)) == 0)
	{
		return false;
	}
	strTemp = strTime.Mid(index, indexNext - index);
	*time1 = _ttoll(strTemp);
	index = indexNext + 1;

	if ((indexNext = strTime.Find(":", index)) == 0)
	{
		return false;
	}
	strTemp = strTime.Mid(index, indexNext - index);
	*time2 = _ttoll(strTemp);
	index = indexNext + 1;

	*FileName = strTime.Mid(index, strTime.GetLength());

	return true;
}

BOOL CGraphShowDlg::StringToData2(CString strSrc, time_t *timet, float *t1, float *t2, float *t3,
	float *t4, float *t5, float *t6, float *t7, float *t8, float *t9,
	float *t10, float *t11)
{
	int index = 0, indexNext = 0;
	CString strTemp;
	if ((indexNext = strSrc.Find(":", index)) == 0)
	{
		return false;
	}
	strTemp = strSrc.Mid(index, indexNext - index);
	*timet = _ttoll(strTemp);
	index = indexNext + 1;

	if ((indexNext = strSrc.Find(":", index)) == 0)
	{
		return false;
	}
	strTemp = strSrc.Mid(index, indexNext - index);
	*t1 = _ttof(strTemp);
	index = indexNext + 1;

	if ((indexNext = strSrc.Find(":", index)) == 0)
	{
		return false;
	}
	strTemp = strSrc.Mid(index, indexNext - index);
	*t2 = _ttof(strTemp);
	index = indexNext + 1;

	if ((indexNext = strSrc.Find(":", index)) == 0)
	{
		return false;
	}
	strTemp = strSrc.Mid(index, indexNext - index);
	*t3 = _ttof(strTemp);
	index = indexNext + 1;

	if ((indexNext = strSrc.Find(":", index)) == 0)
	{
		return false;
	}
	strTemp = strSrc.Mid(index, indexNext - index);
	*t4 = _ttof(strTemp);
	index = indexNext + 1;

	if ((indexNext = strSrc.Find(":", index)) == 0)
	{
		return false;
	}
	strTemp = strSrc.Mid(index, indexNext - index);
	*t5 = _ttof(strTemp);
	index = indexNext + 1;

	if ((indexNext = strSrc.Find(":", index)) == 0)
	{
		return false;
	}
	strTemp = strSrc.Mid(index, indexNext - index);
	*t6 = _ttof(strTemp);
	index = indexNext + 1;

	if ((indexNext = strSrc.Find(":", index)) == 0)
	{
		return false;
	}
	strTemp = strSrc.Mid(index, indexNext - index);
	*t7 = _ttof(strTemp);
	index = indexNext + 1;

	if ((indexNext = strSrc.Find(":", index)) == 0)
	{
		return false;
	}
	strTemp = strSrc.Mid(index, indexNext - index);
	*t8 = _ttof(strTemp);
	index = indexNext + 1;

	if ((indexNext = strSrc.Find(":", index)) == 0)
	{
		return false;
	}
	strTemp = strSrc.Mid(index, indexNext - index);
	*t9 = _ttof(strTemp);
	index = indexNext + 1;

	if ((indexNext = strSrc.Find(":", index)) == 0)
	{
		return false;
	}
	strTemp = strSrc.Mid(index, indexNext - index);
	*t10 = _ttof(strTemp);
	index = indexNext + 1;

	strTemp = strSrc.Mid(index, strSrc.GetLength());
	*t11 = _ttof(strTemp);

	return true;
}

void CGraphShowDlg::OnBnClickedCheck1()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_TempCheck1.GetCheck())
	{
		m_ValidFlag[0] = true;
	}
	else
	{
		m_ValidFlag[0] = false;
	}
}


void CGraphShowDlg::OnBnClickedCheck2()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_TempCheck2.GetCheck())
	{
		m_ValidFlag[1] = true;
	}
	else
	{
		m_ValidFlag[1] = false;
	}
}


void CGraphShowDlg::OnBnClickedCheck3()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_TempCheck3.GetCheck())
	{
		m_ValidFlag[2] = true;
	}
	else
	{
		m_ValidFlag[2] = false;
	}
}


void CGraphShowDlg::OnBnClickedCheck4()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_TempCheck4.GetCheck())
	{
		m_ValidFlag[3] = true;
	}
	else
	{
		m_ValidFlag[3] = false;
	}
}


void CGraphShowDlg::OnBnClickedCheck5()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_TempCheck5.GetCheck())
	{
		m_ValidFlag[4] = true;
	}
	else
	{
		m_ValidFlag[4] = false;
	}
}


void CGraphShowDlg::OnBnClickedCheck6()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_TempCheck6.GetCheck())
	{
		m_ValidFlag[5] = true;
	}
	else
	{
		m_ValidFlag[5] = false;
	}
}


void CGraphShowDlg::OnBnClickedCheck7()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_TempCheck7.GetCheck())
	{
		m_ValidFlag[6] = true;
	}
	else
	{
		m_ValidFlag[6] = false;
	}
}


void CGraphShowDlg::OnBnClickedCheck8()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_TempCheck8.GetCheck())
	{
		m_ValidFlag[7] = true;
	}
	else
	{
		m_ValidFlag[7] = false;
	}
}


void CGraphShowDlg::OnBnClickedCheck9()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_TempCheck9.GetCheck())
	{
		m_ValidFlag[8] = true;
	}
	else
	{
		m_ValidFlag[8] = false;
	}
}


void CGraphShowDlg::OnBnClickedCheck10()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_TempCheck10.GetCheck())
	{
		m_ValidFlag[9] = true;
	}
	else
	{
		m_ValidFlag[9] = false;
	}
}


void CGraphShowDlg::OnBnClickedCheck11()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_TempCheck11.GetCheck())
	{
		m_ValidFlag[10] = true;
	}
	else
	{
		m_ValidFlag[10] = false;
	}
}

