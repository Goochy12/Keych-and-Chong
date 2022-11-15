/*
 * TestMicrocontrollerFirmware.c
 *
 * Created: 5/11/2022 11:53:07 PM
 * Author : liamg
 
 
 MAIN FILE
 */ 

#include "Keyboard.h"

uint8_t KeyboardMatrix [3][3] = {
	{HID_KEYBOARD_SC_A, HID_KEYBOARD_SC_B, HID_KEYBOARD_SC_C},
	{HID_KEYBOARD_SC_1_AND_EXCLAMATION, HID_KEYBOARD_SC_2_AND_AT, HID_KEYBOARD_SC_3_AND_HASHMARK},
	{HID_KEYBOARD_MODIFIER_LEFTSHIFT, HID_KEYBOARD_MODIFIER_LEFTGUI, HID_KEYBOARD_SC_CAPS_LOCK}
};

/*Buffer to hold previously generated HID report - for comparison purposes inside HID class driver.*/
static uint8_t PrevKeyboardHIDReportBuffer[sizeof(USB_KeyboardReport_Data_t)];

/*LUFA HID Class Driver interface configuration and state information.
Passed to all HID Class driver functions to differentiate multiple instances within the same class
*/
USB_ClassInfo_HID_Device_t Keyboard_HID_Interface =
{
	.Config =
	{
		.InterfaceNumber = INTERFACE_ID_KEYBOARD,
		.ReportINEndpoint = 
		{
			.Address = KEYBOARD_EPADDR,
			.Size = KEYBOARD_EPSIZE,
			.Banks = 1
		},
		.PrevReportINBuffer = PrevKeyboardHIDReportBuffer,
		.PrevReportINBufferSize = sizeof(PrevKeyboardHIDReportBuffer),
	},
};

/*
Main entry point
*/
int main(void)
{
	SetupHardware();
	GlobalInterruptEnable();
	
    while (1) 
    {
		HID_Device_USBTask(&Keyboard_HID_Interface);
		USB_USBTask();
    }
}

/*Configure board and chip hardware*/
void SetupHardware(){
	//disable watchdog if enabled by fuse
	MCUSR &= ~(1 << WDRF);
	wdt_disable();
	
	//disable clock division
	clock_prescale_set(clock_div_1);
	
	USB_Init();
}

//library connect event
void EVENT_USB_Device_Connect(void){
	
}

//library disconnect event
void EVENT_USB_Device_Disconnect(void){
	
}

//library configuration change event
void EVENT_USB_Device_ConfigurationChanged(void){
	bool ConfigSuccess = true;
	ConfigSuccess &= HID_Device_ConfigureEndpoints(&Keyboard_HID_Interface);
	USB_Device_EnableSOFEvents();
}

//library usb control request reception event
void EVENT_USB_Device_ControlRequest(void){
	HID_Device_ProcessControlRequest(&Keyboard_HID_Interface);
}

//usb start of frame event
void EVENT_USB_Device_StartOfFrame(void){
	HID_Device_MillisecondElapsed(&Keyboard_HID_Interface);
}

//create HID report with key presses
bool CALLBACK_HID_Device_CreateHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
										uint8_t* const ReportID,
										const uint8_t ReportType,
										void* ReportData,
										uint16_t* const ReportSize)
{
	USB_KeyboardReport_Data_t* KeyboardReport = (USB_KeyboardReport_Data_t*)ReportData;
	
	KeyboardReport->KeyCode[1] = HID_KEYBOARD_SC_A;
	
	*ReportSize = sizeof(USB_KeyboardReport_Data_t);
	return false;
}

void CALLBACK_HID_Device_ProcessHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
										const uint8_t ReportID,
										const uint8_t ReportType,
										const void* ReportData,
										const uint16_t ReportSize)
{
	
}