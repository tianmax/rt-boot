/*
 * The early init code for MIPS
 * Copyright ZhaoXiaowei 2018
 * Github:github.com/zhaohengbo
 */

#include <kernel/rtthread.h>
#include <finsh/shell.h>
#include <common/global.h>

ALIGN(RT_ALIGN_SIZE)
static char main_thread_stack[0x400];
struct rt_thread main_thread;
void rt_thread_main_thread_entry(void* parameter)
{
	extern int rt_hw_boot_eth_init(void);
	extern int lwip_system_init(void);
	lwip_system_init();
	rt_hw_boot_eth_init();
#ifdef RT_USING_FINSH
    /* init finsh */
    finsh_system_init();
    finsh_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
    while (1)
    {
		//rt_kprintf("test on qca9533\n");
		rt_thread_mdelay(1000);
    }
}

int rt_application_init(void)
{
	rt_thread_init(&main_thread,
                   "main_thread",
                   &rt_thread_main_thread_entry,
                   RT_NULL,
                   &main_thread_stack[0],
                   sizeof(main_thread_stack),12,5);
	
    rt_thread_startup(&main_thread);
    return 0;
}
