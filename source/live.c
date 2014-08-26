//            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
//                    Version 2, December 2004
//
//            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
//   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include <live.h>
#include <snapshot.h>
#include <mumble.h>

NPObject*
Live_Allocate (NPP plugin, NPClass* klass)
{
	return PA_Object(klass, plugin, Mumble_Get(PA_Self(plugin)));
}

bool
Live_HasMethod (NPObject* object, NPIdentifier name)
{
	(void) object;

	if (NPN_IdentifierIsString(name)) {
		NPUTF8* string = NPN_UTF8FromIdentifier(name);

		if (strcmp(string, "snapshot") == 0) {
			return true;
		}
	}

	return false;
}

bool
Live_Invoke (NPObject* object, NPIdentifier name, const NPVariant* argv, uint32_t argc, NPVariant* result)
{
	(void) argv;
	(void) argc;

	if (NPN_IdentifierIsString(name)) {
		NPUTF8* string = NPN_UTF8FromIdentifier(name);

		if (strcmp(string, "snapshot") == 0) {
			NPObject* snapshot = NPN_CreateObject(PA_Plugin(object), &SnapshotClass);
			NPN_RetainObject(snapshot);

			OBJECT_TO_NPVARIANT(snapshot, *result);
			
			return true;
		}
	}

	return false;
}
