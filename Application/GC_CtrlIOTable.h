#ifndef  __GC_IO_CTRL_H
#define  __GC_IO_CTRL_H

#include "../SysPeripheral/GPIO/GPIO_Man.h"
//输出IO编号
typedef enum
{
    GC_OUTPUT_IO_LED,
    GC_OUTPUT_IO_BLE_EN,
    
}GC_OUTPUT_IO_TABLE;


//输入IO编号
typedef enum
{
    GC_INPUT_IO_PWM0 = 0,
    GC_INPUT_IO_PWM1,
    GC_INPUT_IO_PWM2,
    GC_INPUT_IO_PWM3,

}GC_INPUT_IO_TABLE;


//格子柜控制IO资源表
extern const GPIO_CTRL_TABLE GC_CtrlIOTable;



#endif /* __GC_IO_CTRL_H */
