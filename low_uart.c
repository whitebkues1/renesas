#include "hal_data.h"

volatile bool uart_send_complete_flag = false;
volatile bool uart_receive_complete_flag = false;

int __io_putchar(int ch);
int __io_getchar(void);
int _write(int fd,char *pBuffer,int size);
int _read(int fd, char *pBuffer, int size);

void user_uart_callback (uart_callback_args_t * p_args)
{
    if(p_args->event == UART_EVENT_TX_COMPLETE)
    {
        uart_send_complete_flag = true;
    }

    if(UART_EVENT_RX_COMPLETE == p_args->event)
    {
        uart_receive_complete_flag = true;
    }
}

#ifdef __GNUC__
    #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
    #define GETCHAR_PROTOTYPE int __io_getchar(void)
#else
    #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

PUTCHAR_PROTOTYPE
{
    R_SCI_UART_Write(&g_uart0_ctrl, (uint8_t *)&ch, 1);
    while(uart_send_complete_flag == false){}
    uart_send_complete_flag = false;
    return ch;
}

GETCHAR_PROTOTYPE
{
    uint8_t ch = 0;
    R_SCI_UART_Read(&g_uart0_ctrl, (uint8_t *)&ch, 1);
    while(uart_receive_complete_flag == false){}
    uart_receive_complete_flag = false;
    return ch;
}

int _write(int fd,char *pBuffer,int size)
{
    (void)fd;
    for(int i=0;i<size;i++)
    {
        __io_putchar(*pBuffer++);
    }
    return size;
}

int _read(int fd, char *pBuffer, int size)
{
    (void)fd;
    (void)size;
    *pBuffer = __io_getchar();
    return 1;
}
