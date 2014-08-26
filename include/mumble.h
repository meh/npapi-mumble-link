//            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
//                    Version 2, December 2004
//
//            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
//   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#ifndef MUMBLE_H
#define MUMBLE_H

#include <pimpa.h>
#include <stdint.h>
#include <string.h>

typedef struct Mumble {
	uint32_t version;
	uint32_t tick;

	struct {
		float position[3];
		float front[3];
		float top[3];
	} avatar;

	wchar_t name[256];

	struct {
		float position[3];
		float front[3];
		float top[3];
	} camera;

	wchar_t identity[256];

	struct {
		uint32_t      length;
		unsigned char value[256];
	} context;

	wchar_t description[2048];
} Mumble;


#if defined(XP_WIN)
	#include <Windows.h>
	
	HANDLE Mumble_Open (void);
	
	void Mumble_Close (HANDLE handle);
	
	Mumble* Mumble_Get (HANDLE handle);
#endif

bool Mumble_HasProperty (NPObject* object, NPIdentifier name);

bool Mumble_GetProperty (NPObject* object, NPIdentifier name, NPVariant* result);

#endif
