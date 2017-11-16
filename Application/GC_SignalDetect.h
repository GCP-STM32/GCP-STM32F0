#ifndef  __GC_SIGNAL_DETECT_H
#define  __GC_SIGNAL_DETECT_H

#include "../SysPeripheral/SysTick/SysTimer.h"

extern SYS_TIME_DATA g_PwmCountValidTimer;

#ifdef __cplusplus
extern "C"
{
#endif
    

/*****************************************************************************
 * 电机信号检测相关控制接口
 ****************************************************************************/

//信号检测功能初始化
void GC_SignalDetect_Init(void);


//获取PWM数(带方向特性)
Bit32 GC_GetPwmCount(void);


//信号检测主线程
void GC_SignalDetectHandler(void);
    
    
#ifdef __cplusplus
}
#endif

#endif /* __GC_SIGNAL_DETECT_H */
