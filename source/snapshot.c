//            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
//                    Version 2, December 2004
//
//            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
//   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include <pimpa.h>
#include <live.h>
#include <snapshot.h>
#include <mumble.h>

NPObject*
Snapshot_Allocate (NPP plugin, NPClass* klass)
{
	Mumble* self = (Mumble*) Mumble_Get(PA_Self(plugin));
	Mumble* copy = (Mumble*) NPN_MemAlloc(sizeof(Mumble));

	memcpy(copy, self, sizeof(Mumble));

	return PA_Object(klass, plugin, copy);
}

void
Snapshot_Deallocate (NPObject* object)
{
	NPN_MemFree(object);
}
