#include "project.h"
#include <stdio.h>
#define STARTING_HOUR 10
#define ENDING_HOUR 20
#define NUMBER_OF_MEASUREMENTS 10
#define BUFFER_SIZE 256

char buffer[BUFFER_SIZE];

void checkLight()
{
    // Get current hour
    int hour = RTC_GetHours(RTC_GetTime());
    sprintf(buffer, "Current hour: %d\n", hour);
    UART_UartPutString(buffer);
    
    // Check whether hour is outside of designated time frame - if so, turn it off
    if(hour < STARTING_HOUR || hour > ENDING_HOUR){
        Pin_LED_blue_Write(0);
    }
    else {
        int positive_measurements = 0;
        // Make several measurements of the light sensor
        for(int i = 0; i < NUMBER_OF_MEASUREMENTS; i++){
            positive_measurements += Pin_Light_Sensor_Read();
        }
        sprintf(buffer, "Number of total measurements: %d\n Number of positive measurements: %d\n", NUMBER_OF_MEASUREMENTS, positive_measurements);
        UART_UartPutString(buffer);
        // If the light sensor catches enough light, turn off the LED's
        if (positive_measurements > NUMBER_OF_MEASUREMENTS/2)
        {
            sprintf(buffer, "Turning LEDs off\n");
            UART_UartPutString(buffer);
            
            Pin_LED_blue_Write(0);   
        } 
        // Else turn them on
        else 
        {
            sprintf(buffer, "Turning LEDs on\n");
            UART_UartPutString(buffer);
            Pin_LED_blue_Write(1);
        }
    }
}
void checkMoisture()
{
    if (Pin_Moisture_Sensor_Read())
    {
        Pin_pump_Write(1);   
    } 
    else 
    {
        Pin_pump_Write(0);
    }
}

int main(void)
{
    /* Enable global interrupts. */   
    CyGlobalIntEnable; 

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    UART_Start();
    RTC_Start();
    for(;;)
    {
      
        /* Place your application code here. */
        checkLight();
        checkMoisture();
        
        CyDelay(1000);
    }
}

/* [] END OF FILE */
