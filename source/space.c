//            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
//                    Version 2, December 2004
//
//            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
//   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include <space.h>
#include <vector.h>
#include <stdlib.h>
#include <string.h>

typedef struct Space {
	float* position;
	float* front;
	float* top;
} Space;

NPObject*
Space_Create (NPP plugin, float* position, float* front, float* top)
{
	NPObject* object = NPN_CreateObject(plugin, &SpaceClass);
	Space*    space  = PA_Private(object);

	space->position = position;
	space->front    = front;
	space->top      = top;

	NPN_RetainObject(object);

	return object;
}

NPObject*
Space_Allocate (NPP plugin, NPClass* klass)
{
	return PA_Object(klass, plugin, NPN_MemAlloc(sizeof(Space)));
}

void
Space_Deallocate (NPObject* object)
{
	NPN_MemFree(PA_Private(object));
	NPN_MemFree(object);
}

bool
Space_HasProperty (NPObject* object, NPIdentifier name)
{
	(void) object;

	if (!NPN_IdentifierIsString(name)) {
		return false;
	}

	NPUTF8* string = NPN_UTF8FromIdentifier(name);

	return strcmp(string, "position") == 0 ||
	       strcmp(string, "front")    == 0 ||
	       strcmp(string, "top")      == 0;
}

bool
Space_GetProperty (NPObject* object, NPIdentifier name, NPVariant* result)
{
	Space* space = PA_Private(object);

	if (!NPN_IdentifierIsString(name)) {
		return false;
	}

	NPUTF8* string = NPN_UTF8FromIdentifier(name);

	if (strcmp(string, "position") == 0) {
		OBJECT_TO_NPVARIANT(Vector_Create(PA_Plugin(object), space->position), *result);
	}
	else if (strcmp(string, "front") == 0) {
		OBJECT_TO_NPVARIANT(Vector_Create(PA_Plugin(object), space->front), *result);
	}
	else if (strcmp(string, "front") == 0) {
		OBJECT_TO_NPVARIANT(Vector_Create(PA_Plugin(object), space->top), *result);
	}
	else {
		return false;
	}

	return true;
}
