#include "w25xxx.h"
#include "dfs_fs.h"
#include "drv_spi.h"
#include "spi_flash_sfud.h"

static int W25XXX_Init(void)
{
    if (rt_hw_spi_device_attach("spi1", "spi1_0", GPIOA, GPIO_Pin_2))
    {
        return RT_ERROR;
    }
    if (rt_sfud_flash_probe("W25Q32", "spi1_0") == RT_NULL)
    {
        LOG_E("W25Q32 connot INIT");
        return RT_ERROR;
    }
    return RT_EOK;
}
INIT_COMPONENT_EXPORT(W25XXX_Init);

static int W25XXX_FileSystem_Init(void)
{
    if (dfs_mount("W25Q32", "/", "elm", 0, 0))
    {
        LOG_E("W25Q32 FileSystem connot INIT!");
        return RT_ERROR;
    }
    return RT_EOK;
}
INIT_ENV_EXPORT(W25XXX_FileSystem_Init);