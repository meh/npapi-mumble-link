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

NPObject* Context_Create (NPP plugin, uint32_t* length, uint8_t* data);

NPObject* Context_Allocate (NPP plugin, NPClass* klass);

void Context_Deallocate (NPObject* object);

bool Context_HasProperty (NPObject* object, NPIdentifier name);

bool Context_GetProperty (NPObject* object, NPIdentifier name, NPVariant* result);

bool Context_SetProperty (NPObject* object, NPIdentifier name, const NPVariant* value);

bool Context_Enumerate (NPObject* object, NPIdentifier** names, uint32_t* length);

static NPClass ContextClass = {
	.allocate    = Context_Allocate,
	.deallocate  = Context_Deallocate,
	.hasProperty = Context_HasProperty,
	.getProperty = Context_GetProperty,
	.setProperty = Context_SetProperty,
	.enumerate   = Context_Enumerate,
};

#endif
