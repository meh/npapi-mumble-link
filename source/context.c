//            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
//                    Version 2, December 2004
//
//            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
//   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include <context.h>
#include <stdlib.h>
#include <string.h>

typedef struct Context {
	uint32_t* length;
	uint8_t*  data;
} Context;

NPObject*
Context_Create (NPP plugin, uint32_t* length, uint8_t* data)
{
	NPObject* object  = NPN_CreateObject(plugin, &ContextClass);
	Context*  context = PA_Private(object);

	context->length = length;
	context->data   = data;

	NPN_RetainObject(object);

	return object;
}

NPObject*
Context_Allocate (NPP plugin, NPClass* klass)
{
	return PA_Object(klass, plugin, NPN_MemAlloc(sizeof(Context)));
}

void
Context_Deallocate (NPObject* object)
{
	NPN_MemFree(PA_Private(object));
	NPN_MemFree(object);
}

bool
Context_HasProperty (NPObject* object, NPIdentifier name)
{
	if (NPN_IdentifierIsString(name)) {
		return strcmp(NPN_UTF8FromIdentifier(name), "length") == 0;
	}

	Context* context = PA_Private(object);
	uint32_t index   = NPN_IntFromIdentifier(name);

	if (index >= *context->length) {
		return false;
	}

	return true;
}

bool
Context_GetProperty (NPObject* object, NPIdentifier name, NPVariant* result)
{
	Context* context = PA_Private(object);

	if (NPN_IdentifierIsString(name)) {
		if (strcmp(NPN_UTF8FromIdentifier(name), "length") == 0) {
			DOUBLE_TO_NPVARIANT(*context->length, *result);

			return true;
		}
	
		return false;
	}

	uint32_t index = NPN_IntFromIdentifier(name);

	if (index >= *context->length) {
		return false;
	}

	DOUBLE_TO_NPVARIANT(context->data[index], *result);

	return true;
}

bool
Context_SetProperty (NPObject* object, NPIdentifier name, const NPVariant* value)
{
	Context* context = PA_Private(object);

	if (NPN_IdentifierIsString(name)) {
		if (strcmp(NPN_UTF8FromIdentifier(name), "length") == 0) {
			if (!NPVARIANT_IS_DOUBLE(*value)) {
				return false;
			}

			if (NPVARIANT_TO_DOUBLE(*value) > 255) {
				return false;
			}

			*context->length = NPVARIANT_TO_DOUBLE(*value);

			return true;
		}
	
		return false;
	}

	uint32_t index = NPN_IntFromIdentifier(name);

	if (index >= *context->length) {
		return false;
	}

	if (!NPVARIANT_IS_DOUBLE(*value)) {
		return false;
	}

	if (NPVARIANT_TO_DOUBLE(*value) > 255) {
		return false;
	}

	context->data[index] = NPVARIANT_TO_DOUBLE(*value);

	return true;
}
