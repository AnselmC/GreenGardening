/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include <stdio.h>
//Global variable definitions
#define startingHour 10
#define endingHour 20


void checkLight(){
}
int main(void)
{
    uint16 sensorval;
    char msg[10];
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    UART_Start();
    
    for(;;)
    {
        /* Place your application code here. */
        sensorval = Pin_Moisture_Sensor_Read();
        sprintf(msg, "%3d\r\n", sensorval);
        UART_UartPutString(msg);
        CyDelay(500);
    }
}

/* [] END OF FILE */
