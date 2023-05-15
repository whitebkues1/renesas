#include "hal_data.h"

volatile bool uart_send_complete_flag = false;
volatile bool uart_receive_complete_flag = false;

int __io_putchar(int ch);
int __io_getchar(void);
int _write(int fd,char *pBuffer,int size);
int _read(int fd, char *pBuffer, int size);
