/*
 * Descriptors.h
 *
 * Created: 6/11/2022 9:11:05 PM
 *  Author: Liam
 */ 


#ifndef DESCRIPTORS_H_
#define DESCRIPTORS_H_

	#include <avr/pgmspace.h>			//access data stored in flash memory (program space)
	#include <LUFA/Drivers/USB/USB.h>	//access USB header
	
	/*Type Definitions:*/
	/*
	Device configuration descriptor. Define in Descriptor.c.
	Describes device usage to host. 
	*/
	typedef struct
	{
		USB_Descriptor_Configuration_Header_t Config;
		
		//keyboard HID interface
		USB_Descriptor_Interface_t HID_Interface;
		USB_HID_Descriptor_HID_t HID_KeyboardHID;
		USB_Descriptor_Endpoint_t HID_ReportINEndpoint;
	} USB_Descriptor_Configuration_t;
		
	/*
	Enum for device interface descriptor IDs within the device. Each interface descriptor should have a single ID associated with it.
	*/
	enum InterfaceDescriptors_t
	{
		INTERFACE_ID_KEYBOARD = 0,
	};
	
	/*
	Enum for String descriptor IDs within the device. Each string descriptor should have a single ID associated with it.
	*/
	enum StringDescriptors_t
	{
		STRING_ID_Language = 0,
		STRING_ID_Manufacturer = 1,
		STRING_ID_Product = 2,
	};
	
	/*
	Endpoint address of Keyboard HID reporting IN endpoint
	*/
	#define KEYBOARD_EPADDR (ENDPOINT_DIR_IN | 0)
	
	/*
	Size in bytes of Keyboard HID reporting IN endpoint
	*/
	#define KEYBOARD_EPSIZE 8
	
	/*
	function prototype
	*/
	uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
										const uint16_t wIndex,
										const void** const DescriptorAddress,
										uint8_t* const DescriptorMemorySpace
										)
										ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);		


#endif /* DESCRIPTORS_H_ */