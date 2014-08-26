//            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
//                    Version 2, December 2004
//
//            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
//   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include <pimpa.h>
#include <mumble.h>
#include <live.h>
#include <stdio.h>

static HANDLE _handle = NULL;

PAMetadata*
PA_Metadata (void)
{
	static PAMetadata meta = {
		.name        = "Mumble Link",
		.description = "Mumble Link interface plugin.",
		.version     = "1.0.0.0",
		.mime        = "application/x-mumble-link:mbl:Mumble Link",
	};

	return &meta;
}

bool
PA_Initialize (void)
{
	_handle = Mumble_Open();

	return true;
}

bool
PA_Shutdown (void)
{
	Mumble_Close(_handle);

	return true;
}

void*
PA_New (const char* mime, int argc, char* argn[], char* argv[])
{
	(void) mime;
	(void) argc;
	(void) argn;
	(void) argv;

	return _handle;
}

bool
PA_Destroy (void* pointer)
{
	(void) pointer;

	return true;
}

NPObject*
PA_Interface (NPP plugin)
{
	return NPN_CreateObject(plugin, &LiveClass);
}
