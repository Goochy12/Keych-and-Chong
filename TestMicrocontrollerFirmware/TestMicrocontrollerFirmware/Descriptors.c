/*
 * Descriptors.c
 *
 * Created: 9/11/2022 11:49:27 PM
 *  Author: liamg
 */ 


#include "Descriptors.h"

/*
Descriptors are structures that provide information to the host
*/

/*
HID Class report descriptor. Constructed with special values from the USBIF HID class spec - to describe reports and capabilities of the device.
Read and parsed by host. Stored in FLASH
Type uint8.
*/
const USB_Descriptor_HIDReport_Datatype_t PROGMEM KeyboardReport[] = 
{
	//use HID drivers standard USB report with 6 keys simultaneous.
	HID_DESCRIPTOR_KEYBOARD(6)
};

/*
Device descriptor structure. Stored in FLASH.
Describes overall characteristics - USB version, VendorID & ProductID, Endpoint size and Number of Device Configurations.
Descriptor read by host when enumeration begins.
*/
const USB_Descriptor_Device_t PROGMEM DeviceDescriptor = 
{
	.Header = {.Size = sizeof(USB_Descriptor_Device_t), .Type = DTYPE_Device},
	
	.USBSpecification = VERSION_BCD(1,1,0),
	.Class = USB_CSCP_NoDeviceClass,
	.SubClass = USB_CSCP_NoDeviceSubclass,
	.Protocol = USB_CSCP_NoDeviceProtocol,
	
	.Endpoint0Size = FIXED_CONTROL_ENDPOINT_SIZE,
	
	.VendorID = 0x03EB,
	.ProductID = 0x2042,
	.ReleaseNumber = VERSION_BCD(0,0,1),
	
	.ManufacturerStrIndex = STRING_ID_Manufacturer,
	.ProductStrIndex = STRING_ID_Product,
	.SerialNumStrIndex = NO_DESCRIPTOR,
	
	.NumberOfConfigurations = FIXED_NUM_CONFIGURATIONS
	
};

/*
Configuration descriptor structure. Stored in FLASH.
Describes usage of device in one of its supported configurations. Including info on devices and endpoints.
Descriptor read by host during enumeration when selecting configuration so host may correctly communicate with device.
*/
const USB_Descriptor_Configuration_t PROGMEM ConfigurationDescriptor = 
{
	.Config = 
	{
		.Header = {.Size = sizeof(USB_Descriptor_Configuration_t), .Type = DTYPE_Configuration},
		
		.TotalConfigurationSize = sizeof(USB_Descriptor_Configuration_Header_t),
		.TotalInterfaces = 1,
		
		.ConfigurationNumber = 1,
		.ConfigurationStrIndex = NO_DESCRIPTOR,
		
		.ConfigAttributes = (USB_CONFIG_ATTR_RESERVED | USB_CONFIG_ATTR_SELFPOWERED),
		
		.MaxPowerConsumption = USB_CONFIG_POWER_MA(100)
	},
	
	.HID_Interface = 
	{
		.Header = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},
		
		.InterfaceNumber = INTERFACE_ID_KEYBOARD,
		.AlternateSetting = 0x00,
		
		.TotalEndpoints = 1,
		
		.Class = HID_CSCP_HIDClass,
		.SubClass = HID_CSCP_BootSubclass,
		.Protocol = HID_CSCP_KeyboardBootProtocol,
		
		.InterfaceStrIndex = NO_DESCRIPTOR		
	},
	
	.HID_KeyboardHID = 
	{
		.Header = {.Size = sizeof(USB_HID_Descriptor_HID_t), .Type = HID_DTYPE_HID},
		
		.HIDSpec = VERSION_BCD(1,1,1),
		.CountryCode = 0x00,
		.TotalReportDescriptors = 1,
		.HIDReportType = HID_DTYPE_Report,
		.HIDReportLength = sizeof(KeyboardReport)
	},
	
	.HID_ReportINEndpoint = 
	{
		.Header = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},
		
		.EndpointAddress = KEYBOARD_EPADDR,
		.Attributes = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
		.EndpointSize = KEYBOARD_EPSIZE,
		.PollingIntervalMS = 0x05
	},
};

/*
Language descriptor structure. Stored in FLASH.
Returned when host requests string descriptor with index 0.
Actually an array of 16 bit integers that indicates via LanguageID table (USBIF) what language the device supports.
*/
const USB_Descriptor_String_t PROGMEM LanguageString = USB_STRING_DESCRIPTOR_ARRAY(LANGUAGE_ID_ENG);

/*
Manufacture descriptor string. Stored in FLASH.
Unicode string in Human readable form.
*/
const USB_Descriptor_String_t PROGMEM ManufacturerString = USB_STRING_DESCRIPTOR(L"Liam Gooch");

/*
Product descriptor string. Stored in FLASH.
Unicode string in Human readable form.
*/
const USB_Descriptor_String_t PROGMEM ProductString = USB_STRING_DESCRIPTOR(L"Liam's Demo Keyboard");

/*
Function called by library when in device mode, and must be overrided by application code (see Library "USB Descriptors")
So that address and size of requested descriptor can be given to the library (Lufa?).
Function called when device receives GetDescriptor request on control endpoint - descriptor detailes passed back and appropriate descriptor sent to USB host.
*/
uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue, /*descriptor type in High byte, Index in Low byte*/
									const uint16_t wIndex, 
									const void** const DescriptorAddress)
{
	const uint8_t DescriptorType = (wValue >> 8);
	const uint8_t DescriptorNumber = (wValue & 0xFF);
	
	const void* Address = NULL;
	uint16_t Size = NO_DESCRIPTOR;
	
	switch(DescriptorType)
	{
		case DTYPE_Device:
			Address = &DeviceDescriptor;
			Size = sizeof(USB_Descriptor_Device_t);
			break;
		case DTYPE_Configuration:
			Address = &ConfigurationDescriptor;
			Size = sizeof(USB_Descriptor_Configuration_t);
			break;
		case DTYPE_String:
			switch(DescriptorNumber)
			{
				case STRING_ID_Language:
					Address = &LanguageString;
					Size = sizeof(LanguageString.Header.Size);
					break;
				case STRING_ID_Manufacturer:
					Address = &ManufacturerString;
					Size = sizeof(ManufacturerString.Header.Size);
					break;
				case STRING_ID_Product:
					Address = &ProductString;
					Size = sizeof(ProductString.Header.Size);
					break;
			}
			break;
		case HID_DTYPE_HID:
			Address = &ConfigurationDescriptor.HID_KeyboardHID;
			Size = sizeof(USB_HID_Descriptor_HID_t);
			break;
		case HID_DTYPE_Report:
			Address = &KeyboardReport;
			Size = sizeof(KeyboardReport);
			break;
	}
	*DescriptorAddress = Address;
	return Size;
}