/**
  ******************************************************************************
  * @file    GCIOCtrl.c
  * @author  Duhanfneg
  * @version V1.0
  * @date    2017.10.20
  * @brief   
  ******************************************************************************
  * @attention
  * 
  * 
  * 
  * 
  ******************************************************************************
  */
   
   
/***********************************<INCLUDES>**********************************/
#include "GC_HwCtrl.h"
#include "GC_CtrlIOTable.h"

#include "../DataType/DataType.h"
#include "../SysPeripheral/GPIO/GPIO_Man.h"
#include "../SysPeripheral/KEY/KEY.h"
#include "../SysPeripheral/SysTick/SysTimer.h"
#include "../SysPeripheral/SysCtrl/SysCtrl.h"
#include "../SysPeripheral/EXTI/EXTI.h"
#include "../SysPeripheral/UART/UART.h"



/*****************************************************************************
 * 私有成员定义及实现
 ****************************************************************************/
#define GC_LED_TOGGLE_TIME          (100)       //LED翻转时间(MS)
static SYS_TIME_DATA m_LedCtrlTimer  = {1};     //LED控定时器


/**
  * @brief  IO初始化
  * @param  None
  * @retval None
  */
static void GC_IOConfig(void)
{
    //设置控制IO资源表
    GPIO_SetCtrlTable((GPIO_CTRL_TABLE *)&GC_CtrlIOTable);
    
    //初始化资源表内的IO
    GPIO_InitIOTable((GPIO_CTRL_TABLE *)&GC_CtrlIOTable);
    
    
}


/*****************************************************************************
 * 硬件配置接口
 ****************************************************************************/

/**
  * @brief  系统硬件初始化
  * @param  None
  * @retval None
  */
void GC_HwInit(void)
{
    //初始化IO
    GC_IOConfig();
    
    //初始化外部中断
    EXTI_Init(GC_INPUT_IO_PWM0, EXTI_TRG_RISING | EXTI_TRG_FALLING);
    EXTI_Init(GC_INPUT_IO_PWM1, EXTI_TRG_RISING | EXTI_TRG_FALLING);
    EXTI_Init(GC_INPUT_IO_PWM2, EXTI_TRG_RISING | EXTI_TRG_FALLING);
    EXTI_Init(GC_INPUT_IO_PWM3, EXTI_TRG_RISING | EXTI_TRG_FALLING);
    
    //使能BLE输出
    GPIO_MAN_SetOutputPinLogicToggle(GC_OUTPUT_IO_BLE_EN, 1);
    GPIO_MAN_SetOutputPinState(GC_OUTPUT_IO_BLE_EN, 1);
    
    //使能串口0
    UART_Init(0, 9600);
    
}


/*****************************************************************************
 * LED显示线程接口
 ****************************************************************************/

/**
  * @brief  LED 流水灯循环
  * @param  None
  * @retval None
  */
void GC_MainWorkLedShow(void)
{
    if (SysTime_CheckExpiredState(&m_LedCtrlTimer))
    {
        SysTime_StartOneShot(&m_LedCtrlTimer, GC_LED_TOGGLE_TIME); //设置下一次执行的时间
        
        GPIO_ToggleOutputState(GC_OUTPUT_IO_LED);
    }

}

