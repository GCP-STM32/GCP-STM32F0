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
#include "GC_CtrlIOTable.h"
#include "../SysPeripheral/GPIO/GPIO_Man.h"



//输入IO表
static GPIO_DATA m_InputIOTable[] = 
{
    {0,   0},
    {0,   1},
    {0,   2},
    {0,   3},
};


//输出IO表
static GPIO_DATA m_OutputIOTable[] = 
{
    //LED灯
    {0,  4}, 
    
    //BLE使能脚
    {0, 7},

};


//控制IO表
const GPIO_CTRL_TABLE GC_CtrlIOTable = 
{
    m_OutputIOTable,
    m_InputIOTable,
    sizeof(m_OutputIOTable)/sizeof(GPIO_DATA),
    sizeof(m_InputIOTable)/sizeof(GPIO_DATA),
    
};
