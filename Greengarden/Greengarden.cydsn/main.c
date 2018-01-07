#include "project.h"
#include <stdio.h>

#define STARTING_HOUR 10
#define ENDING_HOUR 20
#define NUMBER_OF_MEASUREMENTS 10
#define BUFFER_SIZE 256
#define OFF 1
#define ON 0

char buffer[BUFFER_SIZE];

void checkLight()
{
    // Get current hour
    int hour = RTC_GetHours(RTC_GetTime());
    sprintf(buffer, "Current hour: %d\r\n", hour);
    UART_UartPutString(buffer);
    
    // Check whether hour is outside of designated time frame - if so, turn it off
    if(hour < STARTING_HOUR || hour > ENDING_HOUR){
        sprintf(buffer, "Outside of timeframe\r\n");
        UART_UartPutString(buffer);
        
        Pin_LED_blue_Write(OFF);
    }
    else {
        int positive_measurements = NUMBER_OF_MEASUREMENTS;
        // Make several measurements of the light sensor
        for(int i = 0; i < NUMBER_OF_MEASUREMENTS; i++){
            positive_measurements -= Pin_Light_Sensor_Read();
            CyDelay(50);
        }
        sprintf(buffer, "Number of total measurements: %d\t Number of positive measurements: %d\r\n", NUMBER_OF_MEASUREMENTS, positive_measurements);
        UART_UartPutString(buffer);
        
        // If the light sensor catches not enough light, turn on the LED's
        if (positive_measurements < NUMBER_OF_MEASUREMENTS/2)
        {
            sprintf(buffer, "Turning LEDs on\r\n");
            UART_UartPutString(buffer);

            Pin_LED_blue_Write(ON);   
        } 
        // Else turn them off
        else 
        {
            sprintf(buffer, "Turning LEDs off\r\n");
            UART_UartPutString(buffer);
            
            Pin_LED_blue_Write(OFF);
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

CY_ISR(Pin_Light_Sensor_Handler)
{
    checkLight();
    
    Pin_Light_Sensor_ClearInterrupt();
}

int main(void)
{
    /* Enable global interrupts. */   
    CyGlobalIntEnable; 

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    UART_Start();
    RTC_Start();
    Pin_Light_Sensor_int_StartEx(Pin_Light_Sensor_Handler);
    
    sprintf(buffer, "Let's go\r\n");
    UART_UartPutString(buffer);
    
    for(;;)
    {
      
        /* Place your application code here. */
//        checkLight();
//        checkMoisture();
//        
//        CyDelay(1000);
    }
}

/* [] END OF FILE */
