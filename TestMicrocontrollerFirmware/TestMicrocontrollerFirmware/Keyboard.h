/*
 * Keyboard.h
 *
 * Created: 6/11/2022 9:09:43 PM
 *  Author: Liam
 */ 


#ifndef KEYBOARD_H_
#define KEYBOARD_H_

	//includes
	#include <avr/io.h>		//inputs and outputs
	#include <avr/wdt.h>	//watchdog timer handling - used to detect and recover from malfunctions
	#include <avr/power.h>	//power reduction management
	#include <avr/interrupt.h>
	#include <stdbool.h>	//boolean
	#include <string.h>		//string
	
	#include "Descriptors.h"
	
	#include <LUFA/Drivers/USB/USB.h>
	#include <LUFA/Platform/Platform.h>
	
	#define ColumnPins [3] = {PINB4, PINB5, PINB6};
	
	#define RowPins [3] = {PINB7, PINC7, PINC6};
	
	#define ColumnDDR [3] = {DDRB, DDRB, DDRB};
	
	#define RowDDR [3] = {DDRB, DDRC, DDRC};
	
	#define ColumnPorts [3] = {PORTB, PORTB, PORTB};
	
	#define RowPorts [3] = {PORTB, PORTC, PORTC};
	
	
	//function prototypes
	void SetupHardware(void);
	
	void EVENT_USB_Device_Connect(void);
	void EVENT_USB_Device_Disconnect(void);
	void EVENT_USB_Device_ConfigurationChanged(void);
	void EVENT_USB_Device_ControlRequest(void);
	void EVENT_USB_Device_StartOfFrame(void);
	
	bool CALLBACK_HID_Device_CreateHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
											uint8_t* const ReportID,
											const uint8_t ReportType,
											void* ReportData,
											uint16_t* const ReportSize);
											
	void CALLBACK_HID_Device_ProcessHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
											const uint8_t ReportID,
											const uint8_t ReportType,
											const void* ReportData,
											const uint16_t ReportSize);




#endif /* KEYBOARD_H_ */