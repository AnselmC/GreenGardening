#include "project.h"

void checkLight()
{
    if (Pin_Light_Sensor_Read())
    {
        Pin_LED_blue_Write(0);   
    } 
    else 
    {
        Pin_LED_blue_Write(1);
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
    
    for(;;)
    {
        /* Place your application code here. */
        checkLight();
        checkMoisture();
        
        CyDelay(1000);
    }
}

/* [] END OF FILE */
