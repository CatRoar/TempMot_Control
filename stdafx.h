
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持

#include <afxsock.h>
#include "drv/IMC_Pkg.h"
#include "drv/ParamDef.h"
#pragma comment(lib, "drv/IMC_Pkg.lib")

//点动参数结构体
typedef struct JOG_INFO_tag
{
	float startvel;		//起始速度
	float tagvel;		//目标速度
	float accvel;		//加速度
}JOG_INFO;

//回零参数结构体
typedef struct HOME_INFO_tag
{
	float tagvel;		//目标速度
	float accvel;		//加速度
	float compatevel;	//反向补偿
	int dir;			//回零方向
}HOME_INFO;

//设备参数设置结构体
typedef struct DEVICE_INFO_tag
{
	int PULnum;			//电机每转所需转数
	double ScrewValue;  //丝杠导程
	double Scale;		//电机脉冲数和移动距离的比例关系
	int ReduceValue;	//减速比
}DEVICE_INFO;

typedef struct CFG_INFO_tag
{
	int ena;		//使能驱动器
	int steptime;	//脉冲宽度
	int pulpolar;	//脉冲电平
	int dirpolar;	//方向电平
	double vellim;	//速度极限
	double acclim;	//加速度极限
	int plimitena;	//硬件限位
	int plimitpolar;	//限位电平
	int nlimitena;	//硬件限位
	int nlimitpolar;	//限位电平
	int almena;	//伺服报警使能
	int almpolar;	//伺服报警电平
	int INPena;	//伺服到位使能
	int INPpolar;	//伺服到位电平
	double encpfactor;	//反馈倍率
	int encpena;	//反馈使能
	int encpmode;	//反馈计数模式
	int encpdir;	//反馈计数方向
	int res;		//保留
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


