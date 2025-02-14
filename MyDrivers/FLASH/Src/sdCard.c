/*
 * sdCard.h
 *
 *  Created on: 2025年2月1日
 *      Author: 26448
 */

#include "sdCard.h"
#include "sdio.h"
#include "drv_sdio.h"
#include "dfs_fs.h"
#include "dfs_file.h"
#include "dfs_posix.h"
#include "rtdbg.h"

static int SDCard_FileSystem_Init(void)
{
    rt_thread_delay(100);
    DIR *dirp = opendir("SDCard");
    if (dirp == RT_NULL)
    {
        mkdir("SDCard", 0x777);
        if ((dirp = opendir("SDCard")) == RT_NULL)
        {
            LOG_E("opendir(SDCard)\tERROR!");
            return RT_ERROR;
        }
    }
    if (closedir(dirp) != RT_EOK)
    {
        LOG_E("closedir(SDCard)\tERROR!");
        return RT_ERROR;
    }
    if (rt_device_find("sd0") == RT_NULL)
    {
        LOG_E("SDCard connot INIT");
    }
    if (dfs_mount("sd0", "/SDCard", "elm", 0, 0) != RT_EOK)
    {
        LOG_E("SDCard FileSystem connot INIT!");
        return RT_ERROR;
    }
    LOG_D("SDCard FileSystem OK!");
    return RT_EOK;
}
INIT_APP_EXPORT(SDCard_FileSystem_Init);