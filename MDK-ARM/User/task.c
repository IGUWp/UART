#include "task.h"
#include "usart.h"

/**
 *  @brief ��������ú�����1ms��,���ж�ʹ�û����������һ����ʱ������һ��1ms�ж�
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
