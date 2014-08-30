//            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
//                    Version 2, December 2004
//
//            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
//   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#ifndef LIVE_H
#define LIVE_H

#include <pimpa.h>
#include <mumble.h>
#include <string.h>

NPObject* Live_Allocate (NPP plugin, NPClass* klass);

bool Live_HasMethod (NPObject* object, NPIdentifier name);

bool Live_Invoke (NPObject* object, NPIdentifier name, const NPVariant* argv, uint32_t argc, NPVariant* result);

static NPClass LiveClass = {
	.allocate    = Live_Allocate,
	.hasMethod   = Live_HasMethod,
	.invoke      = Live_Invoke,
	.hasProperty = Mumble_HasProperty,
	.getProperty = Mumble_GetProperty,
	.setProperty = Mumble_SetProperty,
};

#endif
