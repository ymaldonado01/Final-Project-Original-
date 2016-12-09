/*******************************************************************************
* File Name: V_LOW.c  
* Version 2.10
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "V_LOW.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        V_LOW_PC =   (V_LOW_PC & \
                                (uint32)(~(uint32)(V_LOW_DRIVE_MODE_IND_MASK << (V_LOW_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (V_LOW_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: V_LOW_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void V_LOW_Write(uint8 value) 
{
    uint8 drVal = (uint8)(V_LOW_DR & (uint8)(~V_LOW_MASK));
    drVal = (drVal | ((uint8)(value << V_LOW_SHIFT) & V_LOW_MASK));
    V_LOW_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: V_LOW_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  V_LOW_DM_STRONG     Strong Drive 
*  V_LOW_DM_OD_HI      Open Drain, Drives High 
*  V_LOW_DM_OD_LO      Open Drain, Drives Low 
*  V_LOW_DM_RES_UP     Resistive Pull Up 
*  V_LOW_DM_RES_DWN    Resistive Pull Down 
*  V_LOW_DM_RES_UPDWN  Resistive Pull Up/Down 
*  V_LOW_DM_DIG_HIZ    High Impedance Digital 
*  V_LOW_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void V_LOW_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(V_LOW__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: V_LOW_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro V_LOW_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 V_LOW_Read(void) 
{
    return (uint8)((V_LOW_PS & V_LOW_MASK) >> V_LOW_SHIFT);
}


/*******************************************************************************
* Function Name: V_LOW_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 V_LOW_ReadDataReg(void) 
{
    return (uint8)((V_LOW_DR & V_LOW_MASK) >> V_LOW_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(V_LOW_INTSTAT) 

    /*******************************************************************************
    * Function Name: V_LOW_ClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 V_LOW_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(V_LOW_INTSTAT & V_LOW_MASK);
		V_LOW_INTSTAT = maskedStatus;
        return maskedStatus >> V_LOW_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */