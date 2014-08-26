//            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
//                    Version 2, December 2004
//
//            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
//   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#ifndef SPACE_H
#define SPACE_H

#include <pimpa.h>

NPObject* Space_Create (NPP plugin, float* position, float* front, float* top);

NPObject* Space_Allocate (NPP plugin, NPClass* klass);

void Space_Deallocate (NPObject* object);

bool Space_HasProperty (NPObject* object, NPIdentifier name);

bool Space_GetProperty (NPObject* object, NPIdentifier name, NPVariant* result);

static NPClass SpaceClass = {
	.allocate    = Space_Allocate,
	.deallocate  = Space_Deallocate,
	.hasProperty = Space_HasProperty,
	.getProperty = Space_GetProperty,
};


#endif
