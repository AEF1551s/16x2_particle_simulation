#include <serial_com.h>

void serial_com_init(){
    uart2_init();
}


int _write(int file, char *ptr, int len)
{
    /* Implement your write code here, this is used by puts and printf for example */
    int i = 0;
    for (i = 0; i < len; i++)
        // Send debug UART data
        //  ITM_SendChar((*ptr++));
        uart2_write((*ptr++));
    return len;
}
