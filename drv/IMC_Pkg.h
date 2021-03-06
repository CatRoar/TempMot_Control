#ifndef IMC_PKG_HEAD_H
#define IMC_PKG_HEAD_H

#ifdef IMC_PKG_EXPORTS
#define IMC_PKG_API __declspec(dllexport)
#else
#define IMC_PKG_API __declspec(dllimport)
#endif

#include "IMC_Def.h"

//设备函数
//查找以太网卡
IMC_PKG_API int WINAPI 
	PKG_IMC_FindNetCard (char  info[16][256],	//返回找到的网卡名称
						int* num) ;				//返回找到的网卡数量
//打开控制卡设备，与设备建立通信连接
IMC_PKG_API IMC_HANDLE WINAPI 
	PKG_IMC_Open (int netcardsel,			//网卡索引，由搜索网卡函数返回的结果决定
						int imcid) ;		//IMC控制卡的id，由控制卡上的拨码开关设置决定
//打开控制卡设备，与设备建立通信连接
IMC_PKG_API IMC_HANDLE WINAPI 
	PKG_IMC_OpenX (int netcardsel, 			//网卡索引，由搜索网卡函数返回的结果决定
						int imcid, 			//IMC控制卡的id，由控制卡上的拨码开关设置决定
						int timeout,		//通信超时时间，单位毫秒
						int openMode) ;		//打开模式；1：混杂模式， 0：非混杂模式
//使用密码打开控制卡设备，与设备建立通信连接
IMC_PKG_API IMC_HANDLE WINAPI 
	PKG_IMC_OpenUsePassword (int netcardsel, 	//网卡索引，由搜索网卡函数返回的结果决定
						int imcid,  			//IMC控制卡的id，由控制卡上的拨码开关设置决定
						char *password);		//密码字符串
//关闭打开的设备。
IMC_PKG_API int WINAPI 
	PKG_IMC_Close (IMC_HANDLE Handle);

//配置函数
IMC_PKG_API int WINAPI PKG_IMC_InitCfg(IMC_HANDLE handle);
//清空所有FIFO和残留的等待指令。
IMC_PKG_API int WINAPI 
	PKG_IMC_ClearIMC(IMC_HANDLE handle); 	//设备句柄，

//清零该轴的编码器计数、指令位置、目标位置等各种位置参数。
IMC_PKG_API int WINAPI 
	PKG_IMC_ClearAxis(IMC_HANDLE handle,  	//设备句柄，
					int axis);				//需要清零的轴号。
//设置指定轴的有效电平的脉冲宽度
IMC_PKG_API int WINAPI 
	PKG_IMC_SetPulWidth(IMC_HANDLE handle, 	//设备句柄，
					unsigned int ns,		//脉冲宽度，单位为纳秒
					int axis);				//需要设置脉冲宽度的轴号
//设置指定轴的脉冲和方向的有效电平
IMC_PKG_API int WINAPI 
	PKG_IMC_SetPulPolar(IMC_HANDLE handle, 	//设备句柄，
					int pul,				//脉冲信号的有效电平。非零：高电平有效； 零：低电平有效。
					int dir, 				//方向信号的有效电平。非零：高电平有效； 零：低电平有效。
					int axis);				//需要设置有效电平的轴号。
//使能/禁止控制卡接收编码器反馈
IMC_PKG_API int WINAPI 
	PKG_IMC_SetEncpEna(IMC_HANDLE handle, 	//设备句柄，
					int ena, 				//使能标志。非零：使能； 零：不使能。
					int axis);				//需要能/禁止控制卡接收编码器反馈的轴号。
//设置控制卡接收编码器反馈的计数模式和计数方向
IMC_PKG_API int WINAPI 
	PKG_IMC_SetEncpMode(IMC_HANDLE handle, 	//设备句柄，
					int mode, 				//编码器的计数模式。零：正交信号模式； 非零：脉冲+方向模式
					int dir, 				//编码器的计数方向。
					int axis);				//需要设置的轴号。
//设置编码器反馈倍率
IMC_PKG_API int WINAPI 
	PKG_IMC_SetEncpRate(IMC_HANDLE handle,  //设备句柄，
					double rate,			//倍率
					int axis); 				//需要设置的轴号。
//设置指定轴的速度和加速度限制
IMC_PKG_API int WINAPI 
	PKG_IMC_SetVelAccLim(IMC_HANDLE handle, //设备句柄，
					double vellim, 			//速度极限，单位为脉冲每毫秒。
					double acclim, 			//加速度极限，单位为脉冲每平方毫秒。
					int axis);				//需要设置速度和加速度极限的轴号
//设置每个轴的平滑度
IMC_PKG_API int WINAPI 
	PKG_IMC_SetSmooth(IMC_HANDLE handle, 	//设备句柄，
						short smooth, 		//平滑度，值越大则越平滑，但运动轨迹的误差就越大；
						int aixs); 			//轴号；	
//使能/禁止指定轴的驱动器
IMC_PKG_API int WINAPI 
	PKG_IMC_SetEna(IMC_HANDLE handle, 		//设备句柄，
					int ena, 				//使能标志。非零：使能； 零：不使能。
					int axis);				//需要使能/禁止驱动器的轴号。
//使能/禁止硬件限位输入端口和设置其有效极性。
IMC_PKG_API int WINAPI 
	PKG_IMC_Setlimit (IMC_HANDLE handle, 	//设备句柄，
					int plimEna, 			//是否使能硬件正限位功能。非零：使能； 零：不使能。
					int plimPolar, 			//正限位极性；非零：有效； 零：低电平有效。
					int nlimEna, 			//是否使能硬件负限位功能。非零：使能； 零：不使能。
					int nlimPolar, 			//负限位极性；非零：有效； 零：低电平有效。
					int axis);				//轴号。
//使能伺服报警输入和设置其有效极性
IMC_PKG_API int WINAPI 
	PKG_IMC_SetAlm (IMC_HANDLE handle, 		//设备句柄，
					int ena, 				//是否使能伺服报警输入功能。非零：使能； 零：不使能。
					int polar, 				//极性；非零：高电平有效； 零：低电平有效。
					int axis);				//轴号。
//使能伺服到位输入和设置其有效极性
IMC_PKG_API int WINAPI 
	PKG_IMC_SetINP(IMC_HANDLE handle,  		//设备句柄，
					int ena,  				//是否使能伺服到位输入功能。非零：使能； 零：不使能。
					int polar,  			//极性；非零：高电平有效； 零：低电平有效。
					int axis);				//轴号。
//设置急停输入端的有效极性
IMC_PKG_API int WINAPI 
	PKG_IMC_SetEmstopPolar(IMC_HANDLE handle, //设备句柄，
					int polar, 				//极性；非零：高电平有效； 零：低电平有效。
					int axis);				//轴号。
//设置通用输入端的有效极性
IMC_PKG_API int WINAPI 
	PKG_IMC_SetInPolar(IMC_HANDLE handle, 	//设备句柄，
					int polar, 				//极性；非零：高电平有效； 零：低电平有效。
					int inPort);			//输入端口，范围1 - 32。
//设置发生错误时，电机是否停止运动。
IMC_PKG_API int WINAPI 
	PKG_IMC_SetStopfilt(IMC_HANDLE handle,  //设备句柄，
					int stop,				//出错时是否停止运行，零：不停止； 非零：停止
					int axis);				//轴号。
//设置发生错误时，电机是否退出运动。
IMC_PKG_API int WINAPI 
	PKG_IMC_SetExitfilt(IMC_HANDLE handle,  //设备句柄，
					int exit,				//出错时是否退出运行，零：不退出；非零：退出
					int axis);				//轴号。
//设置静态补偿的范围。
IMC_PKG_API int WINAPI 
	PKG_IMC_SetRecoupRange(IMC_HANDLE handle, //设备句柄，
					int range,				//误差补偿值；取值范围0 - 32767。
					int axis);				//轴号。
//获得控制卡中的配置信息
IMC_PKG_API int WINAPI 
	PKG_IMC_GetConfig(IMC_HANDLE handle,  	//设备句柄，
					int *steptime, 			//脉冲宽度，单位为纳秒
					int *pulpolar, 			//脉冲的有效电平；零：低电平有效； 非零：高电平有效
					int *dirpolar, 			//方向的有效电平；零：低电平有效； 非零：高电平有效
					int *encpena, 			//是否使用编码器反馈；零：禁用； 非零：使用
					int *encpmode, 			//编码器计数模式
					int *encpdir, 			//编码器计数方向
					double *encpfactor, 	//编码器倍率
					double *vellim, 		//速度极限，单位为脉冲/毫秒
					double *acclim, 		//加速度极限，单位为脉冲/平方毫秒
					int *drvena, 			//是否使能驱动器；零：不使能； 非零：使能
					int *plimena, 			//是否使用正硬件限位；零：禁用； 非零：使用
					int *plimpolar, 		//硬件正限位有效电平；零：低电平有效； 非零：高电平有效
					int *nlimena, 			//是否使用负硬件限位；零：禁用； 非零：使用
					int *nlimpolar, 		//硬件负限位有效电平；零：低电平有效； 非零：高电平有效
					int *almena, 			//是否使用伺服报警；零：禁用； 非零：使用
					int *almpolar, 			//伺服报警有效电平；零：低电平有效； 非零：高电平有效
					int *INPena, 			//是否使用伺服到位；零：禁用； 非零：使用
					int *INPpolar, 			//伺服到位有效电平；零：低电平有效； 非零：高电平有效
					int axis);				//需要获取信息的轴号
//点到点运动函数
//使轴从当前位置移动到指定的目标位置
IMC_PKG_API int WINAPI 
	PKG_IMC_MoveAbs(IMC_HANDLE handle, 		//设备句柄，
					long pos, 				//目标位置，单位为脉冲；
					double startvel, 		//起始速度，单位为脉冲每毫秒；
					double tgvel, 			//目标速度，单位为脉冲每毫秒；
					int wait, 				//是否等待运动完成后，函数才返回。非零：等待运动完成；零：不等待。
					int axis); 				//指定轴号
IMC_PKG_API int WINAPI 
	PKG_IMC_MoveAbs_P(IMC_HANDLE handle, 	//设备句柄，
					long pos, 				//目标位置，单位为脉冲；
					double startvel, 		//起始速度，单位为脉冲每毫秒；
					double tgvel, 			//目标速度，单位为脉冲每毫秒；
					int wait, 				//是否等待运动完成后，函数才返回。非零：等待运动完成；零：不等待。
					int axis); 				//指定轴号
					
//使轴从当前位置移动到指定的距离
IMC_PKG_API int WINAPI 
	PKG_IMC_MoveDist(IMC_HANDLE handle, 	//设备句柄，
					long dist, 				//移动距离，单位为脉冲；
					double startvel, 		//起始速度，单位为脉冲每毫秒；
					double tgvel, 			//目标速度，单位为脉冲每毫秒；
					int wait, 				//是否等待运动完成后，函数才返回。非零：等待运动完成；零：不等待。
					int axis); 				//指定轴号；
IMC_PKG_API int WINAPI 
	PKG_IMC_MoveDist_P(IMC_HANDLE handle, 	//设备句柄，
					long dist, 				//移动距离，单位为脉冲；
					double startvel, 		//起始速度，单位为脉冲每毫秒；
					double tgvel, 			//目标速度，单位为脉冲每毫秒；
					int wait, 				//是否等待运动完成后，函数才返回。非零：等待运动完成；零：不等待。
					int axis); 				//指定轴号；
//立即改变当前正在执行的点到点运动的运动速度
IMC_PKG_API int WINAPI 
	PKG_IMC_P2Pvel(IMC_HANDLE handle,		//设备句柄，
					double tgvel, 			//目标速度，单位为脉冲每毫秒；
					int axis);				//轴号；
IMC_PKG_API int WINAPI 
	PKG_IMC_P2Pvel_P(IMC_HANDLE handle,		//设备句柄，
					double tgvel, 			//目标速度，单位为脉冲每毫秒；
					int axis);				//轴号；
//设置当前点到点运动的加速度和减速度
IMC_PKG_API int WINAPI 
	PKG_IMC_SetAccel(IMC_HANDLE handle, 	//设备句柄，
					double accel, 			//加速度，单位为脉冲每平方毫秒；
					double decel, 			//减速度；
					int axis);				//轴号；
IMC_PKG_API int WINAPI 
	PKG_IMC_SetAccel_P(IMC_HANDLE handle, 	//设备句柄，
					double accel, 			//加速度，单位为脉冲每平方毫秒；
					double decel, 			//减速度；
					int axis);				//轴号；
//设置点到点运动模式
IMC_PKG_API int WINAPI 
	PKG_IMC_P2Pmode(IMC_HANDLE handle,  	//设备句柄，
					int mode, 				//运动模式；零：普通模式； 非零：跟踪模式
					int axis);				//轴号。
IMC_PKG_API int WINAPI 
	PKG_IMC_P2Pmode_P(IMC_HANDLE handle,  	//设备句柄，
					int mode, 				//运动模式；零：普通模式； 非零：跟踪模式
					int axis);				//轴号。
//变点到点运动的目标位置
IMC_PKG_API int WINAPI 
	PKG_IMC_P2PnewPos(IMC_HANDLE handle,  	//设备句柄，
					long tgpos, 			//新的目标位置，单位为脉冲；
					int axis);				//轴号。
IMC_PKG_API int WINAPI 
	PKG_IMC_P2PnewPos_P(IMC_HANDLE handle,  	//设备句柄，
					long tgpos, 			//新的目标位置，单位为脉冲；
					int axis);				//轴号。
//减速停止点到点运动
IMC_PKG_API int WINAPI 
	PKG_IMC_P2Pstop(IMC_HANDLE handle, 		//设备句柄，
					int axis);				//轴号。
IMC_PKG_API int WINAPI 
	PKG_IMC_P2Pstop_P(IMC_HANDLE handle, 		//设备句柄，
					int axis);				//轴号。
//使轴立即按指定的速度一直运动，直到速度被改变为止
IMC_PKG_API int WINAPI 
	PKG_IMC_MoveVel(IMC_HANDLE handle,  	//设备句柄，
					double startvel, 		//起始速度，单位为脉冲每平方毫秒； 
					double tgvel, 			//指定轴的运动速度，单位为脉冲每平方毫秒；
					int axis);				//轴号。
IMC_PKG_API int WINAPI 
	PKG_IMC_MoveVel_P(IMC_HANDLE handle,  	//设备句柄，
					double startvel, 		//起始速度，单位为脉冲每平方毫秒； 
					double tgvel, 			//指定轴的运动速度，单位为脉冲每平方毫秒；
					int axis);				//轴号。

//环形轴
//设置轴为线性轴还是环形轴。
IMC_PKG_API int WINAPI 
	PKG_IMC_SetCirAxis(IMC_HANDLE handle,  	//设备句柄，
					int isCir, 				//非零：环形轴， 0：线性轴
					int axis);				//轴号。
//设置单向或双向环形轴。
IMC_PKG_API int WINAPI 
	PKG_IMC_SetCirMode(IMC_HANDLE handle,  	//设备句柄，
					int mode, 				//非零：双向环形[-cirpos, cirpos]， 0：单向环形[0, cirpos]
					int axis);				//轴号。
//设置环形轴的最大位置。
IMC_PKG_API int WINAPI 
	PKG_IMC_SetCirPos(IMC_HANDLE handle,  	//设备句柄，
					long cirpos, 			//环形轴的最大位置
					int axis);				//轴号。
//插补函数
//立即将参与插补运动的轴号映射到X、Y、Z、A、B、…、等对应的标识上
IMC_PKG_API int WINAPI 
	PKG_IMC_AxisMap(IMC_HANDLE handle, 		//设备句柄，
					int axis[], 			//需要映射的轴号的数组
					int num, 				//需要映射的轴的数量
					int fifo);				//对哪个插补空间进行映射，可选SEL_PFIFO1和SEL_PFIFO2。
//立即启用插补空间
IMC_PKG_API int WINAPI
	PKG_IMC_PFIFOrun (IMC_HANDLE handle, 	//设备句柄，
					int fifo);				//启用哪个插补空间，可选SEL_PFIFO1或SEL_PFIFO2。
//设置速度规划方式。
IMC_PKG_API int WINAPI
	PKG_IMC_SetPFIFOvelMode (IMC_HANDLE handle, //设备句柄，
					int mode,				//速度规划模式
					int fifo);				//设置哪个插补空间的速度规划模式，可选SEL_PFIFO1或SEL_PFIFO2。
//立即改变插补的加速度
IMC_PKG_API int WINAPI 
	PKG_IMC_SetPFIFOaccel (IMC_HANDLE handle, //设备句柄，
					double accel, 			//插补的加速度，单位为脉冲每平方毫秒； 
					int fifo);				//设置哪个插补空间的插补的加速度，可选SEL_PFIFO1或SEL_PFIFO2。
//单段直线插补（绝对运动）
IMC_PKG_API int WINAPI 
	PKG_IMC_Line_Pos(IMC_HANDLE handle, 	//设备句柄，
					long pos[], 			//参与插补运动的轴的位置，单位为脉冲；
					int axisNum, 			//参与插补运动的轴数；
					double tgvel, 			//插补运动的速度，单位为脉冲每平方毫秒；
					double endvel, 			//插补运动的末端速度，单位为脉冲每平方毫秒；
					int wait, 				//是否等待插补运动完成，函数才返回。非零：等待运动完成；零：不等待。
					int fifo);				//指定将此运动指令发送到哪个FIFO中执行，可选SEL_PFIFO1或SEL_PFIFO2。
//单段直线插补（相对运动）
IMC_PKG_API int WINAPI 
	PKG_IMC_Line_Dist(IMC_HANDLE handle, 	//设备句柄，
					long dist[], 			//参与插补运动的轴的移动距离，单位为脉冲；
					int axisNum, 			//参与插补运动的轴数；
					double tgvel, 			//插补运动的速度，单位为脉冲每平方毫秒；
					double endvel,			//插补运动的末端速度，单位为脉冲每平方毫秒；
					int wait, 				//是否等待插补运动完成，函数才返回。非零：等待运动完成；零：不等待。
					int fifo);				//指定将此运动指令发送到哪个FIFO中执行，可选SEL_PFIFO1或SEL_PFIFO2。
//多段连续直线插补（绝对运动）
IMC_PKG_API int WINAPI 
	PKG_IMC_MulLine_Pos (IMC_HANDLE handle, //设备句柄，
					long* pos, 				//多段参与插补运动的轴的位置，单位为脉冲；
					int axisNum, 			//参与插补运动的轴数；
					int segNum, 			//插补运动的段数；
					double tgvel, 			//插补运动的速度，单位为脉冲每平方毫秒；
					double endvel, 			//插补运动的最后一段的结束速度，单位为脉冲每平方毫秒；
					int wait, 				//是否等待插补运动完成，函数才返回。非零：等待运动完成；零：不等待。
					int fifo);				//指定将此运动指令发送到哪个FIFO中执行，可选SEL_PFIFO1或SEL_PFIFO2。
//多段连续直线插补（相对运动）
IMC_PKG_API int WINAPI 
	PKG_IMC_MulLine_Dist (IMC_HANDLE handle, //设备句柄，
					long* dist, 			//多段参与插补运动的轴的移动距离，单位为脉冲； 
					int axisNum, 			//参与插补运动的轴数；
					int segNum, 			//插补运动的段数；
					double tgvel, 			//插补运动的速度，单位为脉冲每平方毫秒；
					double endvel, 			//插补运动的最后一段的结束速度，单位为脉冲每平方毫秒；
					int wait, 				//是否等待插补运动完成，函数才返回。非零：等待运动完成；零：不等待。
					int fifo);				//指定将此运动指令发送到哪个FIFO中执行，可选SEL_PFIFO1或SEL_PFIFO2。
//圆弧插补（绝对运动）
IMC_PKG_API int WINAPI 
	PKG_IMC_Arc_Pos(IMC_HANDLE handle, 		//设备句柄，
					long endx, 				//参与圆弧插补的X轴的终点的位置，单位为脉冲；
					long endy, 				//参与圆弧插补的Y轴的终点的位置，单位为脉冲；
					long cx, 				//参与圆弧插补的X轴的圆心，单位为脉冲；
					long cy, 				//参与圆弧插补的Y轴的圆心，单位为脉冲； 
					int dir, 				//圆弧运动的方向
					double tgvel, 			//插补运动的速度，单位为脉冲每平方毫秒；
					double endvel, 			//插补运动的结束速度，单位为脉冲每平方毫秒；
					int wait, 				//是否等待插补运动完成，函数才返回。非零：等待运动完成；零：不等待。
					int fifo) ;				//指定将此运动指令发送到哪个FIFO中执行，可选SEL_PFIFO1或SEL_PFIFO2。
//圆弧插补（相对运动）
IMC_PKG_API int WINAPI 
	PKG_IMC_Arc_Dist(IMC_HANDLE handle, 	//设备句柄，
					long dist_x, 			//参与圆弧插补的X轴的终点相对于起点的距离，单位为脉冲；
					long dist_y, 			//参与圆弧插补的Y轴的终点相对于起点的距离，单位为脉冲；
					long dist_cx, 			//参与圆弧插补的X轴的圆心相对于起点的距离，单位为脉冲；
					long dist_cy, 			//参与圆弧插补的Y轴的圆心相对于起点的距离，单位为脉冲；
					int dir, 				//圆弧运动的方向
					double tgvel, 			//插补运动的速度，单位为脉冲每平方毫秒；
					double endvel, 			//插补运动的结束速度，单位为脉冲每平方毫秒；
					int wait, 				//是否等待插补运动完成，函数才返回。非零：等待运动完成；零：不等待。
					int fifo);				//指定将此运动指令发送到哪个FIFO中执行，可选SEL_PFIFO1或SEL_PFIFO2。
//圆弧直线插补（绝对运动）
IMC_PKG_API int WINAPI 
	PKG_IMC_ArcLine_Pos(IMC_HANDLE handle, 	//设备句柄，
					long endx, 				//参与圆弧插补的X轴的终点的位置，单位为脉冲；
					long endy, 				//参与圆弧插补的Y轴的终点的位置，单位为脉冲；
					long cx, 				//参与圆弧插补的X轴的圆心，单位为脉冲；
					long cy, 				//参与圆弧插补的Y轴的圆心，单位为脉冲；
					int dir, 				//圆弧运动的方向； 
					long pos[], 			//跟随圆弧插补运动的轴的位置，单位为脉冲； 
					int axisNum, 			//跟随圆弧插补运动的轴数；
					double tgvel, 			//插补运动的速度，单位为脉冲每平方毫秒；
					double endvel, 			//插补运动的结束速度，单位为脉冲每平方毫秒；
					int wait, 				//是否等待插补运动完成，函数才返回。非零：等待运动完成；零：不等待。
					int fifo);				//指定将此运动指令发送到哪个FIFO中执行，可选SEL_PFIFO1或SEL_PFIFO2。
//圆弧直线插补（相对运动）
IMC_PKG_API int WINAPI 
	PKG_IMC_ArcLine_Dist(IMC_HANDLE handle, //设备句柄，
					long dist_x, 			//参与圆弧插补的X轴的终点相对于起点的距离，单位为脉冲；
					long dist_y, 			//参与圆弧插补的Y轴的终点相对于起点的距离，单位为脉冲；
					long dist_cx, 			//参与圆弧插补的X轴的圆心相对于起点的距离，单位为脉冲；
					long dist_cy, 			//参与圆弧插补的Y轴的圆心相对于起点的距离，单位为脉冲；
					int dir, 				//圆弧运动的方向； 
					long dist[], 			//跟随圆弧插补运动的轴的移动距离，单位为脉冲；
					int axisNum, 			//跟随圆弧插补运动的轴数；
					double tgvel, 			//插补运动的速度，单位为脉冲每平方毫秒；
					double endvel, 			//插补运动的结束速度，单位为脉冲每平方毫秒；
					int wait, 				//是否等待插补运动完成，函数才返回。非零：等待运动完成；零：不等待。
					int fifo);				//指定将此运动指令发送到哪个FIFO中执行，可选SEL_PFIFO1或SEL_PFIFO2。
//立即改变插补的进给倍率。当进给倍率设为0时，可实现插补的暂停，再次设为非零则解除暂停
IMC_PKG_API int WINAPI 
	PKG_IMC_SetFeedrate (IMC_HANDLE handle, //设备句柄，
					double rate, 			//进给倍率； 
					int fifo);				//设置哪个插补空间的插补的进给倍率，可选SEL_PFIFO1或SEL_PFIFO2。
//立即停止插补运动
IMC_PKG_API int WINAPI 
	PKG_IMC_PFIFOstop (IMC_HANDLE handle, 	//设备句柄，
					int fifo);				//停止哪个插补空间的插补，可选SEL_PFIFO1或SEL_PFIFO2。
//立即停止插补运动
IMC_PKG_API int WINAPI 
	PKG_IMC_isPstop (IMC_HANDLE handle,  	//设备句柄，
					int fifo);				//哪个插补空间的插补停止，可选SEL_PFIFO1或SEL_PFIFO2。
//立即清空发到插补空间中未被执行的所有指令
IMC_PKG_API int WINAPI 
	PKG_IMC_PFIFOclear (IMC_HANDLE handle, 	//设备句柄，
					int fifo);				//清空哪个插补空间的指令，可选SEL_PFIFO1或SEL_PFIFO2。

//齿轮函数
//设置指定轴跟随电子手轮运动
IMC_PKG_API int WINAPI  
	PKG_IMC_HandWheel(IMC_HANDLE Handle, 	//设备句柄，
					double rate, 			//电子手轮倍率；
					int axis);				//跟随手轮运动的轴号；
//设置从动轴跟随主动轴运动
IMC_PKG_API int WINAPI  
	PKG_IMC_Gear1 (IMC_HANDLE Handle, 		//设备句柄，
					double rate, 			//齿轮倍率；
					int master, 			//主动轴号
					int axis);				//从动轴的轴号。
//设置从动轴跟随主动轴运动
IMC_PKG_API int WINAPI  
	PKG_IMC_Gear2 (IMC_HANDLE Handle, 	//设备句柄，
					double rate, 			//齿轮倍率；
					int master, 			//主动轴号
					int axis);				//从动轴的轴号。
//立即脱离电子手轮或齿轮的啮合
IMC_PKG_API int WINAPI  
	PKG_IMC_ExitGear (IMC_HANDLE Handle, 	//设备句柄，
					int axis);				//从动轴的轴号。


//IO设置函数
//对输出端口进行控制
IMC_PKG_API int WINAPI 
	PKG_IMC_SetOut(IMC_HANDLE handle, 		//设备句柄，
					int outPort, 			//输出端口；范围是1 – 48；
					int data, 				//控制输出端口的状态； 零：断开输出端口； 非零：连通输出端口。
					int fifo);				//指定将此指令发送到哪个FIFO中执行。

 //搜零函数
//设置当前搜零过程中使用的高速度和低速度
IMC_PKG_API int WINAPI 
	PKG_IMC_SetHomeVel(IMC_HANDLE handle, 	//设备句柄，
					double hight, 			//搜零过程中使用的高速度，单位为脉冲每毫秒；
					double low, 			//搜零过程中使用的低速度，单位为脉冲每毫秒；
					int axis);				//轴号；
//设置编码器索引信号的极性
IMC_PKG_API int WINAPI 
	PKG_IMC_SetHomeIndexPolar(IMC_HANDLE handle, //设备句柄，
					int polar,				//索引信号的极性， 非零：上升沿有效， 0：下降沿有效
					int axis);				//轴号；
//使用零点开关搜索零点
IMC_PKG_API int WINAPI 
	PKG_IMC_HomeSwitch1 (IMC_HANDLE Handle, //设备句柄，
					int dir, 				//搜零方向。零：正方向搜零；非零：负方向搜零；
					int riseEdge, 			//指定检测原点开关的边沿；零：下降沿； 非零：上升沿
					long pos, 				//设置零点时刻零点开关的位置值；
					long stpos, 			//搜零结束时，电机停止的位置；
					double movVel,			//设置零点后移动到停止位置时的速度
					int wait,				//是否等待搜零结束
					int axis);				//轴号。
//使用零点开关搜索零点
IMC_PKG_API int WINAPI 
	PKG_IMC_HomeSwitch2 (IMC_HANDLE Handle, //设备句柄，
					int dir, 				//搜零方向。零：正方向搜零；非零：负方向搜零；
					int riseEdge, 			//指定检测原点开关的边沿；零：下降沿； 非零：上升沿
					long pos, 				//设置零点时刻零点开关的位置值；
					long stpos, 			//搜零结束时，电机停止的位置；
					double movVel,			//设置零点后移动到停止位置时的速度
					int wait,				//是否等待搜零结束
					int axis) ;				//轴号。
//使用零点开关搜索零点
IMC_PKG_API int WINAPI 
	PKG_IMC_HomeSwitch3 (IMC_HANDLE Handle, //设备句柄，
					int dir, 				//搜零方向。零：正方向搜零；非零：负方向搜零；
					int riseEdge, 			//指定检测原点开关的边沿；零：下降沿； 非零：上升沿
					long pos, 				//设置零点时刻零点开关的位置值；
					long stpos, 			//搜零结束时，电机停止的位置；
					double movVel,			//设置零点后移动到停止位置时的速度
					int wait,				//是否等待搜零结束
					int axis);				//轴号。
//使用零点开关和索引信号搜索零点
IMC_PKG_API int WINAPI 
	PKG_IMC_HomeSwitchIndex1 (IMC_HANDLE Handle, //设备句柄，
					int dir, 					//搜零方向。零：正方向搜零；非零：负方向搜零；
					int riseEdge, 				//指定检测原点开关的边沿；零：下降沿； 非零：上升沿
					long pos, 					//设置零点时刻零点开关的位置值；
					long stpos, 				//搜零结束时，电机停止的位置；
					double movVel,				//设置零点后移动到停止位置时的速度
					int wait,					//是否等待搜零结束
					int axis);					//轴号。
//使用零点开关和索引信号搜索零点
IMC_PKG_API int WINAPI 
	PKG_IMC_HomeSwitchIndex2 (IMC_HANDLE Handle, //设备句柄，
					int dir, 				//搜零方向。零：正方向搜零；非零：负方向搜零；
					int riseEdge, 			//指定检测原点开关的边沿；零：下降沿； 非零：上升沿
					long pos, 				//设置零点时刻零点开关的位置值；
					long stpos, 			//搜零结束时，电机停止的位置；
					double movVel,			//设置零点后移动到停止位置时的速度
					int wait,				//是否等待搜零结束
					int axis) ;				//轴号。
//使用零点开关和索引信号搜索零点
IMC_PKG_API int WINAPI 
	PKG_IMC_HomeSwitchIndex3 (IMC_HANDLE Handle, 	//设备句柄，
					int dir, 				//搜零方向。零：正方向搜零；非零：负方向搜零；
					int riseEdge, 			//指定检测原点开关的边沿；零：下降沿； 非零：上升沿
					long pos, 				//设置零点时刻零点开关的位置值；
					long stpos, 			//搜零结束时，电机停止的位置；
					double movVel,			//设置零点后移动到停止位置时的速度
					int wait,				//是否等待搜零结束
					int axis);				//轴号。
//使用索引信号搜索零点
IMC_PKG_API int WINAPI 
	PKG_IMC_HomeIndex (IMC_HANDLE Handle, 	//设备句柄，
					int dir, 				//搜零方向。零：正方向搜零；非零：负方向搜零；
					long pos, 				//设置零点时刻零点开关的位置值；
					long stpos, 			//搜零结束时，电机停止的位置；
					double movVel,			//设置零点后移动到停止位置时的速度
					int wait,				//是否等待搜零结束
					int axis);				//轴号。
//把该轴的当前位置设定为指定值
IMC_PKG_API int WINAPI 
	PKG_IMC_SetPos (IMC_HANDLE Handle, 		//设备句柄，
					long pos, 				//设置的指定值，单位为脉冲；
					int axis);				//轴号。
//立即停止搜零运动
IMC_PKG_API int WINAPI 
	PKG_IMC_HomeStop (IMC_HANDLE Handle, 	//设备句柄，
					int axis);				//需要停止搜零运动的轴号。

//获取状态函数
//获取轴数
 IMC_PKG_API int WINAPI 
 PKG_IMC_GetNaxis(IMC_HANDLE Handle); 		//设备句柄，

//获得所有轴的机械位置。
 IMC_PKG_API int WINAPI 
	 PKG_IMC_GetEncp(IMC_HANDLE Handle, 	//设备句柄，
	 				long pos[], 			//用于保存机械位置的数组；单位为脉冲；
					int axisnum);			//控制卡的轴数。
 //获得所有轴的指令位置
 IMC_PKG_API int WINAPI 
	 PKG_IMC_GetCurpos(IMC_HANDLE Handle, 	//设备句柄，
	 				long pos[], 			//用于保存指令位置的数组；单位为脉冲；
					int axisnum);			//控制卡的轴数。
 //获得所有轴的错误状态
 IMC_PKG_API int WINAPI 
	 PKG_IMC_GetErrorReg(IMC_HANDLE Handle, //设备句柄，
	 				unsigned short err[], 	//用于保存所有轴的错误状态；有错误则相应的位会置1。
					int axisnum);			//控制卡的轴数。
 //获得所有轴的运动状态
 IMC_PKG_API int WINAPI 
	 PKG_IMC_GetMoving(IMC_HANDLE Handle, 	//设备句柄，
					unsigned short moving[],//用于保存所有轴的运动状态，零：已停止运动； 非零：正在运动中
					int axisnum);			//控制卡的轴数。
 //获得所有轴的功能输入端口状态
 IMC_PKG_API int WINAPI 
	 PKG_IMC_GetAin(IMC_HANDLE Handle,  	//设备句柄，
					unsigned short ain[][6],//用于保存所有轴功能输入端的状态
					int axisnum);			//控制卡的轴数。
 //获得所有通用输入端口的状态
 IMC_PKG_API int WINAPI 
	 PKG_IMC_GetGin(IMC_HANDLE Handle, 		//设备句柄，
					unsigned short gin[32]);//用于保存所有通用输入端的状态。
 //获得所有输出端口的状态
 IMC_PKG_API int WINAPI 
	 PKG_IMC_GetGout(IMC_HANDLE Handle, 	//设备句柄，
					unsigned short gout[48]);//用于保存所有输出端的状态
 
 IMC_PKG_API int WINAPI 
	 PKG_IMC_ClearError(IMC_HANDLE Handle,  //设备句柄，
					int axis);				//需要清除错误的轴号
//其他功能函数
 //所有轴立即急停或解除急停状态
IMC_PKG_API int WINAPI 
	PKG_IMC_Emstop(IMC_HANDLE Handle, 		//设备句柄，
					int isStop);			//急停还是解除急停；非零：急停； 零：解除急停。
//对所有轴立即暂停或解除暂停状态
IMC_PKG_API int WINAPI 
	PKG_IMC_Pause(IMC_HANDLE Handle, 		//设备句柄，
					int pause);				//暂停还是解除暂停状态；非零：暂停； 零：解除暂停。

//退出等待运动完成
IMC_PKG_API void WINAPI 
	PKG_IMC_ExitWait();
//当函数返回错误是，使用此函数获得错误提示
IMC_PKG_API const char * WINAPI 
	PKG_IMC_GetFunErrStr();
//获得错误寄存器是字符串说明
IMC_PKG_API const char * WINAPI 
	PKG_IMC_GetRegErrorStr(unsigned short err);

//ADD事件
//将某个寄存器的值与另一个寄存器的值进行相加，将结果保存到目标寄存器
IMC_PKG_API int WINAPI PKG_Fill_ADD32(EventInfo *info,	//事件结构体指针，事件指令将填充事件到此指针指向的地址中
					short  EventType, 					//事件类型，由枚举IMC_EventType中的成员赋值
					short Src1, short Src1_axis,		//寄存器1的地址和其对应的轴号
                    short Src2, short Src2_axis, 		//寄存器2的地址和其对应的轴号
                    short dest, short dest_axis);		//目标寄存器的地址和其对应的轴号
//将某个寄存器的值与指定数值进行相加，将结果保存到目标寄存器
IMC_PKG_API int WINAPI PKG_Fill_ADD32i(EventInfo *info, //事件结构体指针，事件指令将填充事件到此指针指向的地址中
					short  EventType, 					//事件类型，由枚举IMC_EventType中的成员赋值
					short Src1, short Src1_axis, 		//寄存器1的地址和其对应的轴号
                    long data, 							//32位整数
                    short dest, short dest_axis);		//目标寄存器的地址和其对应的轴号
//将某个寄存器的值与另一个寄存器的值进行相加，将结果保存到目标寄存器
IMC_PKG_API int WINAPI PKG_Fill_ADD48(EventInfo *info,	//事件结构体指针，事件指令将填充事件到此指针指向的地址中 
					short  EventType, 					//事件类型，由枚举IMC_EventType中的成员赋值
					short Src1, short Src1_axis, 		//寄存器1的地址和其对应的轴号
                    short Src2, short Src2_axis,  		//寄存器2的地址和其对应的轴号
                    short dest, short dest_axis);		//目标寄存器的地址和其对应的轴号
//将某个寄存器的值与指定数值进行相加，将结果保存到目标寄存器
IMC_PKG_API int WINAPI PKG_Fill_ADD48i(EventInfo *info, //事件结构体指针，事件指令将填充事件到此指针指向的地址中
					short  EventType, 					//事件类型，由枚举IMC_EventType中的成员赋值
					short Src1, short Src1_axis, 		//寄存器1的地址和其对应的轴号
                    __int64 data, 						//64位整数
                    short dest, short dest_axis);		//目标寄存器的地址和其对应的轴号

//CMP事件
//将某个寄存器的值与另一个寄存器的值进行相减，将结果保存到目标寄存器
IMC_PKG_API int WINAPI PKG_Fill_CMP32(EventInfo *info,  //事件结构体指针，事件指令将填充事件到此指针指向的地址中
					short  EventType, 					//事件类型，由枚举IMC_EventType中的成员赋值
					short Src1, short Src1_axis, 		//寄存器1的地址和其对应的轴号
                    short Src2, short Src2_axis,  		//寄存器2的地址和其对应的轴号
                    short dest, short dest_axis);		//目标寄存器的地址和其对应的轴号
//将某个寄存器的值与指定数值进行相减，将结果保存到目标寄存器
IMC_PKG_API int WINAPI PKG_Fill_CMP32i(EventInfo *info, //事件结构体指针，事件指令将填充事件到此指针指向的地址中
					short  EventType, 					//事件类型，由枚举IMC_EventType中的成员赋值
					short Src1, short Src1_axis, 		//寄存器1的地址和其对应的轴号
                    long data, 							//32位整数
                    short dest, short dest_axis);		//目标寄存器的地址和其对应的轴号
//将某个寄存器的值与另一个寄存器的值进行相减，将结果保存到目标寄存器
IMC_PKG_API int WINAPI PKG_Fill_CMP48(EventInfo *info,  //事件结构体指针，事件指令将填充事件到此指针指向的地址中
					short  EventType, 					//事件类型，由枚举IMC_EventType中的成员赋值
					short Src1, short Src1_axis, 		//寄存器1的地址和其对应的轴号
                    short Src2, short Src2_axis,  		//寄存器2的地址和其对应的轴号
                    short dest, short dest_axis);		//目标寄存器的地址和其对应的轴号
//将某个寄存器的值与指定数值进行相减，将结果保存到目标寄存器
IMC_PKG_API int WINAPI PKG_Fill_CMP48i(EventInfo *info, //事件结构体指针，事件指令将填充事件到此指针指向的地址中
					short  EventType, 					//事件类型，由枚举IMC_EventType中的成员赋值
					short Src1, short Src1_axis, 		//寄存器1的地址和其对应的轴号
                    __int64 data, 						//64位整数
                    short dest, short dest_axis);		//目标寄存器的地址和其对应的轴号

//SCA事件
//将某个寄存器的值乘以另一个寄存器指定的倍率，将结果保存到目标寄存器
IMC_PKG_API int WINAPI PKG_Fill_SCA32(EventInfo *info,  //事件结构体指针，事件指令将填充事件到此指针指向的地址中
					short  EventType, 					//事件类型，由枚举IMC_EventType中的成员赋值
					short Src1, short Src1_axis, 		//寄存器1的地址和其对应的轴号
                    short Src2, short Src2_axis,  		//寄存器2的地址和其对应的轴号
                    short dest, short dest_axis);		//目标寄存器的地址和其对应的轴号
//将某个寄存器的值乘以指定的倍率，将结果保存到目标寄存器
IMC_PKG_API int WINAPI PKG_Fill_SCA32i(EventInfo *info,  //事件结构体指针，事件指令将填充事件到此指针指向的地址中
					short  EventType, 					//事件类型，由枚举IMC_EventType中的成员赋值
					short Src1, short Src1_axis, 		//寄存器1的地址和其对应的轴号
                    long data, 							//32位整数
                    short dest, short dest_axis);		//目标寄存器的地址和其对应的轴号
//将某个寄存器的值乘以另一个寄存器指定的倍率，将结果保存到目标寄存器
IMC_PKG_API int WINAPI PKG_Fill_SCA48(EventInfo *info,  //事件结构体指针，事件指令将填充事件到此指针指向的地址中
					short  EventType, 					//事件类型，由枚举IMC_EventType中的成员赋值
					short Src1, short Src1_axis, 		//寄存器1的地址和其对应的轴号
                    short Src2, short Src2_axis,  		//寄存器2的地址和其对应的轴号
                    short dest, short dest_axis);		//目标寄存器的地址和其对应的轴号
//将某个寄存器的值乘以乘以指定的倍率，将结果保存到目标寄存器
IMC_PKG_API int WINAPI PKG_Fill_SCA48i(EventInfo *info, //事件结构体指针，事件指令将填充事件到此指针指向的地址中
					short  EventType, 					//事件类型，由枚举IMC_EventType中的成员赋值
					short Src1, short Src1_axis, 		//寄存器1的地址和其对应的轴号
                    __int64 data, 						//64位整数
                    short dest, short dest_axis);		//目标寄存器的地址和其对应的轴号
//MUL事件
//
IMC_PKG_API int WINAPI PKG_Fill_MUL32L(EventInfo *info, //事件结构体指针，事件指令将填充事件到此指针指向的地址中
					short  EventType, 					//事件类型，由枚举IMC_EventType中的成员赋值
					short Src1, short Src1_axis, 		//寄存器1的地址和其对应的轴号
                    short Src2, short Src2_axis,  		//寄存器2的地址和其对应的轴号
                    short dest, short dest_axis);		//目标寄存器的地址和其对应的轴号
//
IMC_PKG_API int WINAPI PKG_Fill_MUL32iL(EventInfo *info,//事件结构体指针，事件指令将填充事件到此指针指向的地址中
					short  EventType, 					//事件类型，由枚举IMC_EventType中的成员赋值
					short Src1, short Src1_axis, 		//寄存器1的地址和其对应的轴号
                    long data, 							//32位整数
                    short dest, short dest_axis);		//目标寄存器的地址和其对应的轴号
//
IMC_PKG_API int WINAPI PKG_Fill_MUL32A(EventInfo *info, //事件结构体指针，事件指令将填充事件到此指针指向的地址中
					short  EventType, 					//事件类型，由枚举IMC_EventType中的成员赋值
					short Src1, short Src1_axis, 		//寄存器1的地址和其对应的轴号
                    short Src2, short Src2_axis,  		//寄存器2的地址和其对应的轴号
                    short dest, short dest_axis);		//目标寄存器的地址和其对应的轴号
//
IMC_PKG_API int WINAPI PKG_Fill_MUL32iA(EventInfo *info,//事件结构体指针，事件指令将填充事件到此指针指向的地址中
					short  EventType, 					//事件类型，由枚举IMC_EventType中的成员赋值
					short Src1, short Src1_axis, 		//寄存器1的地址和其对应的轴号
                    long data, 							//32位整数
                    short dest, short dest_axis);		//目标寄存器的地址和其对应的轴号

//COP事件
//将某个16位寄存器的值赋值给目标寄存器
IMC_PKG_API int WINAPI PKG_Fill_COP16(EventInfo *info,  //事件结构体指针，事件指令将填充事件到此指针指向的地址中
					short  EventType, 					//事件类型，由枚举IMC_EventType中的成员赋值
					short Src1, short Src1_axis, 		//寄存器1的地址和其对应的轴号
                    short dest, short dest_axis);		//目标寄存器的地址和其对应的轴号
//将某个32位寄存器的值赋值给目标寄存器
IMC_PKG_API int WINAPI PKG_Fill_COP32(EventInfo *info,  //事件结构体指针，事件指令将填充事件到此指针指向的地址中
					short  EventType, 					//事件类型，由枚举IMC_EventType中的成员赋值
					short Src1, short Src1_axis, 		//寄存器1的地址和其对应的轴号
                    short dest, short dest_axis);		//目标寄存器的地址和其对应的轴号
//将某个48位寄存器的值赋值给目标寄存器
IMC_PKG_API int WINAPI PKG_Fill_COP48(EventInfo *info,  //事件结构体指针，事件指令将填充事件到此指针指向的地址中
					short  EventType, 					//事件类型，由枚举IMC_EventType中的成员赋值
					short Src1, short Src1_axis, 		//寄存器1的地址和其对应的轴号
                    short dest, short dest_axis);		//目标寄存器的地址和其对应的轴号

//SET事件
//将指定的数值赋值给16位目标寄存器
IMC_PKG_API int WINAPI PKG_Fill_SET16(EventInfo *info,  //事件结构体指针，事件指令将填充事件到此指针指向的地址中
					short  EventType, 					//事件类型，由枚举IMC_EventType中的成员赋值
					short data, 						//16位整数
                    short dest, short dest_axis);		//目标寄存器的地址和其对应的轴号
//将指定的数值赋值给32位目标寄存器
IMC_PKG_API int WINAPI PKG_Fill_SET32(EventInfo *info,  //事件结构体指针，事件指令将填充事件到此指针指向的地址中
					short  EventType, 					//事件类型，由枚举IMC_EventType中的成员赋值
					long data, 							//32位整数
                    short dest, short dest_axis);		//目标寄存器的地址和其对应的轴号
//将指定的数值赋值给48位目标寄存器
IMC_PKG_API int WINAPI PKG_Fill_SET48(EventInfo *info,  //事件结构体指针，事件指令将填充事件到此指针指向的地址中
					short  EventType, 					//事件类型，由枚举IMC_EventType中的成员赋值
					__int64 data, 						//64位整数
                    short dest, short dest_axis);		//目标寄存器的地址和其对应的轴号


//OR事件
//将某个寄存器的值与另一个寄存器的值进行或运算，将结果保存到目标寄存器
IMC_PKG_API int WINAPI PKG_Fill_OR16(EventInfo *info,	//事件结构体指针，事件指令将填充事件到此指针指向的地址中
					short  EventType, 					//事件类型，由枚举IMC_EventType中的成员赋值
					short Src1, short Src1_axis, 		//寄存器1的地址和其对应的轴号
                    short Src2, short Src2_axis,  		//寄存器2的地址和其对应的轴号
                    short dest, short dest_axis);		//目标寄存器的地址和其对应的轴号
//将某个寄存器的值与另一个寄存器的值进行或运算，将结果保存到目标寄存器
IMC_PKG_API int WINAPI PKG_Fill_OR16B(EventInfo *info,  //事件结构体指针，事件指令将填充事件到此指针指向的地址中
					short  EventType, 					//事件类型，由枚举IMC_EventType中的成员赋值
					short Src1, short Src1_axis, 		//寄存器1的地址和其对应的轴号
                    short Src2, short Src2_axis,  		//寄存器2的地址和其对应的轴号
                    short dest, short dest_axis);		//目标寄存器的地址和其对应的轴号
//将某个寄存器的值与指定的数值进行或运算，将结果保存到目标寄存器
IMC_PKG_API int WINAPI PKG_Fill_OR16i(EventInfo *info,  //事件结构体指针，事件指令将填充事件到此指针指向的地址中
					short  EventType, 					//事件类型，由枚举IMC_EventType中的成员赋值
					short Src1, short Src1_axis, 		//寄存器1的地址和其对应的轴号
					short data, 						//16位整数
                    short dest, short dest_axis);		//目标寄存器的地址和其对应的轴号
//将某个寄存器的值与指定的数值进行或运算，将结果保存到目标寄存器
IMC_PKG_API int WINAPI PKG_Fill_OR16iB(EventInfo *info, //事件结构体指针，事件指令将填充事件到此指针指向的地址中
					short  EventType, 					//事件类型，由枚举IMC_EventType中的成员赋值
					short Src1, short Src1_axis, 		//寄存器1的地址和其对应的轴号
					short data, 						//16位整数
                    short dest, short dest_axis);		//目标寄存器的地址和其对应的轴号

//AND事件
//将某个寄存器的值与另一个寄存器的值进行与运算，将结果保存到目标寄存器
IMC_PKG_API int WINAPI PKG_Fill_AND16(EventInfo *info,  //事件结构体指针，事件指令将填充事件到此指针指向的地址中
					short  EventType, 					//事件类型，由枚举IMC_EventType中的成员赋值
					short Src1, short Src1_axis, 		//寄存器1的地址和其对应的轴号
                    short Src2, short Src2_axis,  		//寄存器2的地址和其对应的轴号
                    short dest, short dest_axis);		//目标寄存器的地址和其对应的轴号
//将某个寄存器的值与另一个寄存器的值进行与运算，将结果保存到目标寄存器
IMC_PKG_API int WINAPI PKG_Fill_AND16B(EventInfo *info, //事件结构体指针，事件指令将填充事件到此指针指向的地址中
					short  EventType, 					//事件类型，由枚举IMC_EventType中的成员赋值
					short Src1, short Src1_axis, 		//寄存器1的地址和其对应的轴号
                    short Src2, short Src2_axis,  		//寄存器2的地址和其对应的轴号
                    short dest, short dest_axis);		//目标寄存器的地址和其对应的轴号
//将某个寄存器的值与指定的数值进行与运算，将结果保存到目标寄存器
IMC_PKG_API int WINAPI PKG_Fill_AND16i(EventInfo *info, //事件结构体指针，事件指令将填充事件到此指针指向的地址中
					short  EventType, 					//事件类型，由枚举IMC_EventType中的成员赋值
					short Src1, short Src1_axis, 		//寄存器1的地址和其对应的轴号
					short data, 						//16位整数
                    short dest, short dest_axis);		//目标寄存器的地址和其对应的轴号
//将某个寄存器的值与指定的数值进行与运算，将结果保存到目标寄存器
IMC_PKG_API int WINAPI PKG_Fill_AND16iB(EventInfo *info, //事件结构体指针，事件指令将填充事件到此指针指向的地址中
					short  EventType, 					//事件类型，由枚举IMC_EventType中的成员赋值
					short Src1, short Src1_axis, 		//寄存器1的地址和其对应的轴号
					short data, 						//16位整数
                    short dest, short dest_axis);		//目标寄存器的地址和其对应的轴号


//XOR事件
//将某个寄存器的值与另一个寄存器的值进行异或运算，将结果保存到目标寄存器
IMC_PKG_API int WINAPI PKG_Fill_XOR16(EventInfo *info,	//事件结构体指针，事件指令将填充事件到此指针指向的地址中
					short  EventType, 					//事件类型，由枚举IMC_EventType中的成员赋值
					short Src1, short Src1_axis, 		//寄存器1的地址和其对应的轴号
                    short Src2, short Src2_axis,  		//寄存器2的地址和其对应的轴号
                    short dest, short dest_axis);		//目标寄存器的地址和其对应的轴号
//将某个寄存器的值与另一个寄存器的值进行异或运算，将结果保存到目标寄存器
IMC_PKG_API int WINAPI PKG_Fill_XOR16B(EventInfo *info,	//事件结构体指针，事件指令将填充事件到此指针指向的地址中
					short  EventType, 					//事件类型，由枚举IMC_EventType中的成员赋值
					short Src1, short Src1_axis, 		//寄存器1的地址和其对应的轴号
                    short Src2, short Src2_axis,  		//寄存器2的地址和其对应的轴号
                    short dest, short dest_axis);		//目标寄存器的地址和其对应的轴号
//将某个寄存器的值与指定的数值进行异或运算，将结果保存到目标寄存器
IMC_PKG_API int WINAPI PKG_Fill_XOR16i(EventInfo *info,	//事件结构体指针，事件指令将填充事件到此指针指向的地址中
					short  EventType, 					//事件类型，由枚举IMC_EventType中的成员赋值
					short Src1, short Src1_axis, 		//寄存器1的地址和其对应的轴号
					short data, 						//16位整数
                    short dest, short dest_axis);		//目标寄存器的地址和其对应的轴号
//将某个寄存器的值与指定的数值进行异或运算，将结果保存到目标寄存器
IMC_PKG_API int WINAPI PKG_Fill_XOR16iB(EventInfo *info,//事件结构体指针，事件指令将填充事件到此指针指向的地址中
					short  EventType,					//事件类型，由枚举IMC_EventType中的成员赋值
					short Src1, short Src1_axis, 		//寄存器1的地址和其对应的轴号
					short data,							//16位整数
                    short dest, short dest_axis);		//目标寄存器的地址和其对应的轴号


//底层函数封装
//设置多个寄存器为指定值
IMC_PKG_API int WINAPI 
	PKG_IMC_SetMulParam(IMC_HANDLE Handle,	//设备句柄，
						WR_MUL_DES pdes[],	//WR_MUL_DES结构体数组；
						int ArrNum,			//pdes数组中有效数据的个数；
						int fifo);			//指定将此指令发送到哪个FIFO中
//设置16位寄存器为指定值
IMC_PKG_API int WINAPI 
	PKG_IMC_SetParam16(IMC_HANDLE Handle, 	//设备句柄，
						short paramloc,		//寄存器地址；
						short data,			//16位整型数据
						int axis,			//轴号；
						int fifo);			//指定将此指令发送到哪个FIFO中
//设置32位寄存器为指定值
IMC_PKG_API int WINAPI 
	PKG_IMC_SetParam32(IMC_HANDLE Handle, 	//设备句柄，
						short paramloc, 	//寄存器地址；
						int data, 			//32位整型数据
						int axis,			//轴号；
						int fifo);			//指定将此指令发送到哪个FIFO中
//设置48位寄存器为指定值
IMC_PKG_API int WINAPI 
	PKG_IMC_SetParam48(IMC_HANDLE Handle, 	//设备句柄，
						short paramloc, 	//寄存器地址；
						__int64 data, 		//64位整型数据
						int axis,			//轴号；
						int fifo);			//指定将此指令发送到哪个FIFO中
//将寄存器某个位的值设为指定值（1或者0）
IMC_PKG_API int WINAPI 
	PKG_IMC_SetParamBit(IMC_HANDLE Handle, 	//设备句柄，
						short paramloc, 	//寄存器地址；
						short bit,			//寄存器的某个位，范围 0 – 15；
						short val, 			//指定的值, 1或者0；
						int axis,			//轴号；
						int fifo);			//指定将此指令发送到哪个FIFO中
//将寄存器指定的位的值由1变为0或者由0变为1
IMC_PKG_API int WINAPI 
	PKG_IMC_TurnParamBit(IMC_HANDLE Handle, //设备句柄，
					short paramloc, 		//寄存器地址；
					short bit, 				//寄存器的某个位，范围 0 – 15；
					int axis,				//轴号；
					int fifo);				//指定将此指令发送到哪个FIFO中
//置位或清零寄存器的某些位
IMC_PKG_API int WINAPI 
	PKG_IMC_ORXORParam(IMC_HANDLE Handle, 	//设备句柄，
					short paramloc, 		//寄存器地址；
					short ORdata, 			//与寄存器进行相或的值；
					short XORdata, 			//与寄存器进行相异或的值；
					int axis,				//轴号；
					int fifo);				//指定将此指令发送到哪个FIFO中
//阻塞FIFO执行后续指令，直到寄存器的某个位变为指定值或超时为止
IMC_PKG_API int WINAPI 
	PKG_IMC_WaitParamBit(IMC_HANDLE Handle,	//设备句柄，
					short paramloc, 		//寄存器地址；
					short bit, 				//寄存器的某个位，范围 0 – 15；
					short val, 				//指定值，1或0；
					int timeout, 			//超时时间，单位为毫秒；
					int axis, 				//轴号；
					int fifo);				//指定将此指令发送到哪个FIFO中
//阻塞FIFO执行后续指令，直到超过设定的时间为止
IMC_PKG_API int WINAPI 
	PKG_IMC_WaitTime(IMC_HANDLE Handle,		//设备句柄，
					int time, 				//等待时间，单位为毫秒
					int fifo);				//指定将此指令发送到哪个FIFO中
//阻塞FIFO执行后续指令，直到寄存器的值变为指定值或超时为止
IMC_PKG_API int WINAPI 
	PKG_IMC_WaitParam(IMC_HANDLE Handle, 	//设备句柄，
					short paramloc, 		//寄存器地址；
					short data, 			//指定的值；
					int timeout, 			//超时时间，单位为毫秒；
					int axis, 				//轴号；
					int fifo);				//指定将此指令发送到哪个FIFO中
//阻塞FIFO执行后续指令，直到寄存器的值与mask进行相与后的值与data值相等或超时为止
IMC_PKG_API int WINAPI 
	PKG_IMC_WaitParamMask(IMC_HANDLE Handle,//设备句柄，
					short paramloc, 		//寄存器地址；
					short mask, 			//与寄存器进行相与的值
					short data, 			//用于比较的值；
					int timeout, 			//超时时间，单位为毫秒；
					int axis, 				//轴号；
					int fifo);				//指定将此指令发送到哪个FIFO中
//读取多个寄存器的值
IMC_PKG_API int WINAPI 
	PKG_IMC_GetMulParam(IMC_HANDLE Handle, 	//设备句柄，
					WR_MUL_DES pdes[], 		//WR_MUL_DES结构体数组；
					int ArrNum);			//WR_MUL_DES结构体数组的有效成员个数。
//读取16位寄存器的值
IMC_PKG_API int WINAPI 
	PKG_IMC_GetParam16(IMC_HANDLE Handle, 	//设备句柄，
					short paramloc, 		//寄存器地址；
					short* data, 			//16位整型变量的地址，用于保存16位寄存器的值；
					int axis);				//轴号；
//读取32位寄存器的值
IMC_PKG_API int WINAPI 
	PKG_IMC_GetParam32(IMC_HANDLE Handle, 	//设备句柄，
					short paramloc, 		//寄存器地址；
					int *data, 				//32位整型变量的地址，用于保存32位寄存器的值；
					int axis);				//轴号；
//读取48位寄存器的值
IMC_PKG_API int WINAPI 
	PKG_IMC_GetParam48(IMC_HANDLE Handle, 	//设备句柄，
					short paramloc, 		//寄存器地址；
					__int64 *data, 			//64位整型变量的地址，用于保存48位寄存器的值；
					int axis);				//轴号；

//将设置的事件安装到控制卡中
IMC_PKG_API int WINAPI 
	PKG_IMC_InstallEvent(IMC_HANDLE Handle, //设备句柄，
					EventInfo pEvent[], 		//事件结构体数组，由事件填充函数填充；
					int EventNum	//事件指令的数量；
					);
//停止安装的事件运行(卸载事件）
IMC_PKG_API int WINAPI 
	PKG_IMC_StopEvent(IMC_HANDLE Handle); //设备句柄，
#endif