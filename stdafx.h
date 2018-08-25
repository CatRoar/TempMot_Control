
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��

#include <afxsock.h>
#include "drv/IMC_Pkg.h"
#include "drv/ParamDef.h"
#pragma comment(lib, "drv/IMC_Pkg.lib")

//�㶯�����ṹ��
typedef struct JOG_INFO_tag
{
	float startvel;		//��ʼ�ٶ�
	float tagvel;		//Ŀ���ٶ�
	float accvel;		//���ٶ�
}JOG_INFO;

//��������ṹ��
typedef struct HOME_INFO_tag
{
	float tagvel;		//Ŀ���ٶ�
	float accvel;		//���ٶ�
	float compatevel;	//���򲹳�
	int dir;			//���㷽��
}HOME_INFO;

//�豸�������ýṹ��
typedef struct DEVICE_INFO_tag
{
	int PULnum;			//���ÿת����ת��
	double ScrewValue;  //˿�ܵ���
	double Scale;		//������������ƶ�����ı�����ϵ
	int ReduceValue;	//���ٱ�
}DEVICE_INFO;

typedef struct CFG_INFO_tag
{
	int ena;		//ʹ��������
	int steptime;	//������
	int pulpolar;	//�����ƽ
	int dirpolar;	//�����ƽ
	double vellim;	//�ٶȼ���
	double acclim;	//���ٶȼ���
	int plimitena;	//Ӳ����λ
	int plimitpolar;	//��λ��ƽ
	int nlimitena;	//Ӳ����λ
	int nlimitpolar;	//��λ��ƽ
	int almena;	//�ŷ�����ʹ��
	int almpolar;	//�ŷ�������ƽ
	int INPena;	//�ŷ���λʹ��
	int INPpolar;	//�ŷ���λ��ƽ
	double encpfactor;	//��������
	int encpena;	//����ʹ��
	int encpmode;	//��������ģʽ
	int encpdir;	//������������
	int res;		//����
}CFG_INFO;


#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


