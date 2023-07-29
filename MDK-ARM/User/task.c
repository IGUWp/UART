#include "task.h"
#include "usart.h"

/**
 *  @brief 主任务调用函数（1ms）,在中断使用或者真机开启一个定时器生成一个1ms中断
 */
void Task_Excute(uint8_t *task_1ms_flag)
{
    if (*task_1ms_flag == 1)
    {
        *task_1ms_flag = 0;
        Uart_task();
    }
    
    Usrt_Process();
}
