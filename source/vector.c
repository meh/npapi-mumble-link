//            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
//                    Version 2, December 2004
//
//            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
//   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include <vector.h>
#include <stdlib.h>
#include <string.h>

typedef struct Vector {
	float* x;
	float* y;
	float* z;
} Vector;

NPObject*
Vector_Create (NPP plugin, float* data)
{
	NPObject* object = NPN_CreateObject(plugin, &VectorClass);
	Vector*   vector = PA_Private(object);

	vector->x = &data[0];
	vector->y = &data[1];
	vector->z = &data[2];

	NPN_RetainObject(object);

	return object;
}

NPObject*
Vector_Allocate (NPP plugin, NPClass* klass)
{
	return PA_Object(klass, plugin, NPN_MemAlloc(sizeof(Vector)));
}

void
Vector_Deallocate (NPObject* object)
{
	NPN_MemFree(PA_Private(object));
	NPN_MemFree(object);
}

bool
Vector_HasProperty (NPObject* object, NPIdentifier name)
{
	(void) object;

	if (!NPN_IdentifierIsString(name)) {
		return false;
	}

	NPUTF8* string = NPN_UTF8FromIdentifier(name);

	return strcmp(string, "x") == 0 ||
	       strcmp(string, "y") == 0 ||
	       strcmp(string, "z") == 0;
}

bool
Vector_GetProperty (NPObject* object, NPIdentifier name, NPVariant* result)
{
	Vector* vector = PA_Private(object);

	if (!NPN_IdentifierIsString(name)) {
		return false;
	}

	NPUTF8* string = NPN_UTF8FromIdentifier(name);

	if (strcmp(string, "x") == 0) {
		DOUBLE_TO_NPVARIANT(*vector->x, *result);
	}
	else if (strcmp(string, "y") == 0) {
		DOUBLE_TO_NPVARIANT(*vector->y, *result);
	}
	else if (strcmp(string, "z") == 0) {
		DOUBLE_TO_NPVARIANT(*vector->z, *result);
	}
	else {
		return false;
	}

	return true;
}
