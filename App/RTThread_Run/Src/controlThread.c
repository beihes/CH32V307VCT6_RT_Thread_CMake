#include "controlThread.h"

// 恢复任务
void Start_Thread(rt_thread_t thread)
{
    if ((thread->stat & RT_THREAD_STAT_MASK) == RT_THREAD_SUSPEND)
    {
        rt_thread_resume(thread);
        //thread->stat = RT_THREAD_RUNNING | (thread->stat & ~RT_THREAD_STAT_MASK);
        rt_kprintf("%s\t:Thread RESUME\n", thread->name);
    }
    else
    {
        rt_kprintf("Thread %s is not in suspend state, cannot resume\n", thread->name);
    }
}

// 暂停任务
void Stop_Thread(rt_thread_t thread)
{
    char midSemName[40] = "";
    sprintf(midSemName, "%s_pause", thread->name);
    rt_sem_t midSem = (rt_sem_t)rt_object_find(midSemName, RT_Object_Class_Semaphore);
    if (midSem!=RT_NULL)
    {
        rt_sem_release(midSem);
        //thread->stat = RT_THREAD_SUSPEND | (thread->stat & ~RT_THREAD_STAT_MASK);
        rt_kprintf("%s\t:Thread STOP\n", thread->name);
    }
    else
    {
        rt_kprintf("Thread %s Sem connot find\n", thread->name);
    }
}

void Control_Thread(int argc, char *argv[])
{
    if (argc < 3)
    {
        rt_kprintf("Usage: Control_Thread\ncmd: [-c creat_thread] [-d delete_thread] [-s thread_state]\nthreadName: [thread_name]\n");
        return;
    }

    // 获取任务名称
    char *thread_name = argv[3];
    rt_thread_t thread = rt_thread_find(thread_name); // 查找任务
    if (thread == RT_NULL)
    {
        rt_kprintf("Thread %s not found\n", thread_name);
        return;
    }

    char *cmdStr = argv[1];
    char *cmdData = argv[2];
    if (strcmp(cmdStr, "-c")==0)
    {
        rt_kprintf("DEBUG\t:create thread!\n");
    }
    else if(strcmp(cmdStr,"-d")==0)
    {
        rt_kprintf("DEBUG\t:delete thread!\n");
    }
    else if (strcmp(cmdStr, "-s") == 0)
    {
        switch (cmdData[0])
        {
        case '0':
            // 暂停任务
            Stop_Thread(thread);
            return;
        case '1':
            // 恢复任务
            Start_Thread(thread);
            return;
        default:
            rt_kprintf("please input 0(close) or 1(open)");
            return;
        }
    }
    else
    {
        rt_kprintf("please check input\n");
    }
}
MSH_CMD_EXPORT(Control_Thread, To Control Thread);