//            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
//                    Version 2, December 2004
//
//            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
//   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#include <mumble.h>
#include <string.h>

NPObject* Snapshot_Allocate (NPP plugin, NPClass* klass);

static NPClass SnapshotClass = {
	.allocate    = Snapshot_Allocate,
	.hasProperty = Mumble_HasProperty,
	.getProperty = Mumble_GetProperty,
	.setProperty = Mumble_SetProperty,
	.enumerate   = Mumble_Enumerate,
};

#endif
