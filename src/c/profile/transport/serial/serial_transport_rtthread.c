#include <uxr/client/profile/transport/serial/serial_transport_rtthread.h>
#include <uxr/client/profile/transport/serial/serial_transport_platform.h>

#include <sys/types.h>

#define DEBUG_SECTION_NAME  "uxr_uart"
#define DEBUG_LEVEL         DEBUG_LOG
#include <rtdbg.h>

static int sem_initialized = 0;
static struct rt_semaphore uxr_uart_rx_sem;

static rt_err_t uart_callback(rt_device_t dev, rt_size_t size)
{
    // Place here your writing bytes platform code
    rt_sem_release(&uxr_uart_rx_sem);

    return RT_EOK;
}

bool uxr_init_serial_platform(struct uxrSerialPlatform* platform, int fd, uint8_t remote_addr, uint8_t local_addr)
{
    // Place here your writing bytes platform code
    (rt_device_t)fd = rt_device_find(platform->dev);
    if(!fd)
    {
        LOG_E("Failed to open device %s", fd);
        return false;
    }
    if(sem_initialized == 0)
    {
        rt_sem_init(&fd, "uxr_uart_rx_sem", 0, RT_IPC_FLAG_FIFO);
        sem_initialized = 1;
    }
    rt_device_open(fd, RT_DEVICE_FLAG_INT_RX);
    rt_device_set_rx_indicate(fd, uart_callback);

    // Return true if success
    return true;
}

bool uxr_close_serial_platform(struct uxrSerialPlatform* platform)
{
    // Place here your writing bytes platform code
    if (!(platform->dev)) {
        LOG_E("Failed to close device %s",platform->dev);
        return false;
    }
    rt_device_close(platform->dev);
    rt_sem_detach(&uxr_uart_rx_sem);
    sem_initialized = 0;

    // Return true if success
    return true;
}

size_t uxr_write_serial_data_platform(uxrSerialPlatform* platform, uint8_t* buf, size_t len, uint8_t* errcode)
{
    // Place here your writing bytes platform code
    rt_ssize_t bytes_written = rt_device_write(platform->dev, 0, (void*)buf, (rt_size_t)len);

    // Return number of bytes written
    return bytes_written;
}

size_t uxr_read_serial_data_platform(uxrSerialPlatform* platform, uint8_t* buf, size_t len, int timeout, uint8_t* errcode)
{
    // Place here your reading bytes platform code
    int tick = rt_tick_get();
    for(int i = 0; i < len; i++)
    {
        if(sem_initialized == 0)
        {
            rt_sem_init(&uxr_uart_rx_sem, "uxr_uart_rx_sem", 0, RT_IPC_FLAG_FIFO);
            sem_initialized = 1;
        }
        while(rt_device_read(platform->dev, -1, &buf[i], 1) != 1)
        {
            rt_sem_take(&uxr_uart_rx_sem, timeout);
            if((rt_tick_get() - tick ) > timeout)
            {
                LOG_E("Read timeout");
                return i;
            } 
        }
    }

    return len;
}