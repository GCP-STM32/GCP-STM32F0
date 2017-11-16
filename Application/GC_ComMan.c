/**
  ******************************************************************************
  * @file    Demo.c
  * @author  Duhanfneg
  * @version V1.0
  * @date    2017.11.07
  * @brief   demo
  ******************************************************************************
  * @attention
  * 
  * 
  * 
  * 
  ******************************************************************************
  */
  
/***********************************<INCLUDES>**********************************/
#include "GC_ComMan.h"
#include "GC_SignalDetect.h"

#include "../DataType/DataType.h"
#include "../SysPeripheral/UART/UART.h"

#include <string.h>
#include <stdio.h>

#define GC_CMD_BUFF_LEN     (64)

/*****************************************************************************
 * 私有成员定义及实现
 ****************************************************************************/

#define GC_CMD_GET_PUSH    "x:GET_PULSE."

static uBit8 uCmdBuff[GC_CMD_BUFF_LEN] = {0};   //定义指令缓冲区
     
     
/*****************************************************************************
 * 通信管理相关控制接口
 ****************************************************************************/


/**
  * @brief  通信管理单元初始化
  * @param  None
  * @retval 0-成功 非0-失败
  */
uBit32 GC_ComInit(void)
{
    
    return 0;
}


/**
  * @brief  通信处理
  * @param  None
  * @retval None
  */
void GC_ComHandler(void)
{
    static uBit32 ulRxIndex = 0;
    
    //如果成功接收到数据
    if (UART_RecvBuff(0, &uCmdBuff[ulRxIndex], 1))
    {
        //如果已经接收到结束符,则进行指令处理
        if (uCmdBuff[ulRxIndex] == '.')
        {
            //获取PWM数
            if (memcmp(uCmdBuff, GC_CMD_GET_PUSH, ulRxIndex+1) == 0)
            {
                char uTempBuff[64] = {0};
                
                //假如数据有效
                if (SysTime_CheckExpiredState(&g_PwmCountValidTimer) == 0)
                {
                    Bit32 lPwmCount = GC_GetPwmCount();
                    
                    if (lPwmCount > 0)
                    {
                        sprintf(uTempBuff, "x:+%ld.", lPwmCount);
                    }
                    else 
                    {
                        sprintf(uTempBuff, "x:%ld.", lPwmCount);
                    }
                }
                else 
                {
                    sprintf(uTempBuff, "x:NULL.");
                }
                
                UART_SendBuff(0, (uBit8 *)uTempBuff, ulRxIndex+1);
                ulRxIndex = 0;
                
                return;
            }
        }
        
        ulRxIndex++;
    }
      
}