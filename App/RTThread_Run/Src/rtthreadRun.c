#include "rtthreadRun.h"

static rt_thread_t keyPB03IrqThread = RT_NULL;

static rt_thread_t test = RT_NULL;

uint8_t i = 0;

static rt_sem_t test_pause_sem = RT_NULL;

void test_entry(void *parameter)
{
    while (1)
    {
        i++;
        if (i == 100)
        {
            i = 0;
        }
        rt_thread_mdelay(1000);
        if (rt_sem_take(test_pause_sem, RT_WAITING_NO) == RT_EOK)
        {
            if (rt_thread_suspend(test) != RT_EOK) // 暂停当前线程
            {
                rt_kprintf("test Stop ERROR!\n"); // 打印暂停日志
            }
            rt_schedule(); // 强制调度
        }
    }
}

void getTestData()
{
    rt_kprintf("i\t:%d\n", i);
}
MSH_CMD_EXPORT(getTestData, To get(test) Thread data);

void findDrivers(int argc, char *argv[])
{
    if (argc != 2)
    {
        return;
    }
    rt_device_t device = rt_device_find(argv[1]);
    if (device == RT_NULL)
    {
        rt_kprintf("%s NONE!\n", argv[1]);
    }
    else
    {
        rt_kprintf("%s OK!\n", argv[1]);
    }
}
MSH_CMD_EXPORT(findDrivers, To fine device);

int RT_Thread_Init()
{
    keyPB03IrqThread = rt_thread_create("keyPB03", KeyPB03_Irq_entry, RT_NULL, 512, 10, 10);
    if (keyPB03IrqThread == RT_NULL)
    {
        return RT_ERROR;
    }
    rt_thread_startup(keyPB03IrqThread);
    /* 创建信号量 */
    test_pause_sem = rt_sem_create("test_pause", 0, RT_IPC_FLAG_PRIO);
    test = rt_thread_create("test", test_entry, RT_NULL, 1024, 10, 10);
    if (test != RT_NULL)
    {
        // rt_thread_control(test,RT_THREAD_CTRL_STARTUP,RT_NULL);
        rt_thread_startup(test);
        rt_sem_release(test_pause_sem);
    }
    return RT_EOK;
}