//            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
//                    Version 2, December 2004
//
//            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
//   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#ifndef CONTEXT_H
#define CONTEXT_H

#include <pimpa.h>

NPObject* Vector_Create (NPP plugin, float* data);

NPObject* Vector_Allocate (NPP plugin, NPClass* klass);

void Vector_Deallocate (NPObject* object);

bool Vector_HasProperty (NPObject* object, NPIdentifier name);

bool Vector_GetProperty (NPObject* object, NPIdentifier name, NPVariant* result);

bool Vector_SetProperty (NPObject* object, NPIdentifier name, const NPVariant* value);

static NPClass VectorClass = {
	.allocate    = Vector_Allocate,
	.deallocate  = Vector_Deallocate,
	.hasProperty = Vector_HasProperty,
	.getProperty = Vector_GetProperty,
	.setProperty = Vector_SetProperty,
};

#endif
