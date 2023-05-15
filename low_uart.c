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
