/**
  ******************************************************************************
  * @file    GC_SignalDetect.c
  * @author  Duhanfneg
  * @version V1.0
  * @date    2017.11.07
  * @brief   Motor Signal Detect
  ******************************************************************************
  * @attention
  * 
  * 
  * 
  * 
  ******************************************************************************
  */
  
/***********************************<INCLUDES>**********************************/
#include "GC_SignalDetect.h"
#include "GC_CtrlIOTable.h"

#include "../DataType/DataType.h"
#include "../SysPeripheral/GPIO/GPIO_Man.h"
#include "../SysPeripheral/SysTick/SysTimer.h"
#include "../SysPeripheral/IRQ/IRQ_Man.h"


/*****************************************************************************
 * 私有成员定义及实现
 ****************************************************************************/


#define PWM_CH_COUNT            (4) //电机通道数
#define PWM_CH_MASK             (PWM_CH_COUNT-1)    //电机通道数掩码

//电机方向
#define PWM_DIR_UNKNOWN         (0) //方向未知
#define PWM_DIR_FORWARD         (1) //正转
#define PWM_DIR_BACKWARD        (2) //反转

//脉冲滤波
#define PWM_MIN_VALID_TIME      (15)//最小有效时间(单位:MS)

static SYS_TIME_DATA m_PwmChTimer[PWM_CH_COUNT] = {0};  //计时器
static SYS_TIME_DATA m_MotorRunTimer = {1};             //电机运行计时器
SYS_TIME_DATA g_PwmCountValidTimer = {1};               //PWM计数有效定时器

uBit32 g_ulCurDir = 0;              //当前方向
uBit32 g_ulForwardPwmCount = 0;     //正转数
uBit32 g_ulBackwardPwmCount = 0;    //反转数
Bit32  g_lPwmCount = 0;             //电机计数

const static uBit32 m_ulForwardOldCh[4]  = {3, 0, 1, 2};    //正转时序
const static uBit32 m_ulBackwardOldCh[4] = {1, 2, 3, 0};    //反转时序

//获取当前方向
static uBit32 GC_GetCurMotorDir(uBit32 ulCurPwmCh)
{
    static uBit32 s_ulOldPwmCh = 0xFF;
    
    uBit32 ulDir = PWM_DIR_UNKNOWN;
    
    if (s_ulOldPwmCh == m_ulForwardOldCh[ulCurPwmCh])
    {
        ulDir =  PWM_DIR_FORWARD;
    }
    else if (s_ulOldPwmCh == m_ulBackwardOldCh[ulCurPwmCh])
    {
        ulDir =  PWM_DIR_BACKWARD;
    }
    
    s_ulOldPwmCh = ulCurPwmCh;
    
    return ulDir;
}



/**
  * @brief  通道0中断处理接口
  * @param  None
  * @retval None
  */
static void GC_CH0_ExtiHandler(void)
{
    //上升沿
    if (GPIO_GetInputState(GC_INPUT_IO_PWM0) == true)
    {
        SysTime_StartReckon(&m_PwmChTimer[0]);
    }
    //下降沿
    else 
    {
        //只有电平时间大于最小限制值的才认为是有效脉冲
        if (SysTime_GetReckonValue(&m_PwmChTimer[0]) >= PWM_MIN_VALID_TIME)
        {
            g_ulCurDir = GC_GetCurMotorDir(0);
            
            if (g_ulCurDir == PWM_DIR_FORWARD)
            {
                g_ulForwardPwmCount++;
            }
            else if (g_ulCurDir == PWM_DIR_BACKWARD)
            {
                g_ulBackwardPwmCount++;
            }
            
            SysTime_Start(&m_MotorRunTimer, 1000);
        }
    }
      
}


/**
  * @brief  通道1中断处理接口
  * @param  None
  * @retval None
  */
static void GC_CH1_ExtiHandler(void)
{
    //上升沿
    if (GPIO_GetInputState(GC_INPUT_IO_PWM1) == true)
    {
        SysTime_StartReckon(&m_PwmChTimer[1]);
    }
    //下降沿
    else 
    {
        //只有电平时间大于最小限制值的才认为是有效脉冲
        if (SysTime_GetReckonValue(&m_PwmChTimer[1]) >= PWM_MIN_VALID_TIME)
        {
            g_ulCurDir = GC_GetCurMotorDir(1);
            
            if (g_ulCurDir == PWM_DIR_FORWARD)
            {
                g_ulForwardPwmCount++;
            }
            else if (g_ulCurDir == PWM_DIR_BACKWARD)
            {
                g_ulBackwardPwmCount++;
            }
            
            SysTime_Start(&m_MotorRunTimer, 1000);
        }
    }
      
}


/**
  * @brief  通道2中断处理接口
  * @param  None
  * @retval None
  */
static void GC_CH2_ExtiHandler(void)
{
    //上升沿
    if (GPIO_GetInputState(GC_INPUT_IO_PWM2) == true)
    {
        SysTime_StartReckon(&m_PwmChTimer[2]);
    }
    //下降沿
    else 
    {
        //只有电平时间大于最小限制值的才认为是有效脉冲
        if (SysTime_GetReckonValue(&m_PwmChTimer[2]) >= PWM_MIN_VALID_TIME)
        {
            g_ulCurDir = GC_GetCurMotorDir(2);
            
            if (g_ulCurDir == PWM_DIR_FORWARD)
            {
                g_ulForwardPwmCount++;
            }
            else if (g_ulCurDir == PWM_DIR_BACKWARD)
            {
                g_ulBackwardPwmCount++;
            }
            
            SysTime_Start(&m_MotorRunTimer, 1000);
        }
    }
      
}


/**
  * @brief  通道3中断处理接口
  * @param  None
  * @retval None
  */
static void GC_CH3_ExtiHandler(void)
{
    //上升沿
    if (GPIO_GetInputState(GC_INPUT_IO_PWM3) == true)
    {
        SysTime_StartReckon(&m_PwmChTimer[3]);
    }
    //下降沿
    else 
    {
        //只有电平时间大于最小限制值的才认为是有效脉冲
        if (SysTime_GetReckonValue(&m_PwmChTimer[3]) >= PWM_MIN_VALID_TIME)
        {
            g_ulCurDir = GC_GetCurMotorDir(3);
            
            if (g_ulCurDir == PWM_DIR_FORWARD)
            {
                g_ulForwardPwmCount++;
            }
            else if (g_ulCurDir == PWM_DIR_BACKWARD)
            {
                g_ulBackwardPwmCount++;
            }
            
            SysTime_Start(&m_MotorRunTimer, 1000);
        }
    }
      
}



/*****************************************************************************
 * 电机信号检测相关控制接口
 ****************************************************************************/

//信号检测功能初始化
void GC_SignalDetect_Init(void)
{
    IRQ_SetTrgCallback(GC_CH0_ExtiHandler, IRQ_TRG_EXTI0);
    IRQ_SetTrgCallback(GC_CH1_ExtiHandler, IRQ_TRG_EXTI1);
    IRQ_SetTrgCallback(GC_CH2_ExtiHandler, IRQ_TRG_EXTI2);
    IRQ_SetTrgCallback(GC_CH3_ExtiHandler, IRQ_TRG_EXTI3);
    
}


//获取PWM数(带方向特性)
Bit32 GC_GetPwmCount(void)
{
    
    return (g_ulForwardPwmCount - g_ulBackwardPwmCount);
}


//清空PWM数
void GC_ResetPwmCount(void)
{
    g_ulForwardPwmCount = 0;
    g_ulBackwardPwmCount = 0;
    
}


//获取电机运行状态
//0-停止
//1-运行
uBit32 GC_GetMotorRunState(void)
{
    if (SysTime_CheckExpiredState(&m_MotorRunTimer))
    {
        return 0;
    }

    return 1;
}


//信号检测主线程
void GC_SignalDetectHandler(void)
{
    static uBit32 s_OldMotorState = 0;
    
    if (GC_GetMotorRunState() != s_OldMotorState)
    {
        s_OldMotorState = !s_OldMotorState;
        
        //假如电机开始运行
        if (s_OldMotorState)
        {
            GC_ResetPwmCount(); //清空PWM数
            SysTime_Start(&g_PwmCountValidTimer, 0);
        }
        else 
        {
            SysTime_Start(&g_PwmCountValidTimer, 20000);
        }
    }
    
}



