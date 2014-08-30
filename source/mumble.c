//            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
//                    Version 2, December 2004
//
//            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
//   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#include <mumble.h>
#include <context.h>
#include <space.h>
#include <stdlib.h>

#if defined(XP_WIN)
	HANDLE
	Mumble_Open (void)
	{
		HANDLE handle = OpenFileMappingW(FILE_MAP_ALL_ACCESS, FALSE, L"MumbleLink");
	
		if (handle == NULL) {
			handle = CreateFileMappingW(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(Mumble), L"MumbleLink");
		}
	
		return handle;
	}
	
	void
	Mumble_Close (HANDLE handle)
	{
		CloseHandle(handle);
	}
	
	Mumble*
	Mumble_Get (HANDLE handle)
	{
		return MapViewOfFile(handle, SECTION_MAP_READ, 0, 0, sizeof(Mumble));
	}
#endif

char*
_string (wchar_t* string, size_t size)
{
	char* result = NPN_MemAlloc(size * sizeof(wchar_t));
	wcstombs(result, string, size * sizeof(wchar_t));

	return result;
}

bool
Mumble_HasProperty (NPObject* object, NPIdentifier name)
{
	(void) object;

	if (NPN_IdentifierIsString(name)) {
		NPUTF8* string = NPN_UTF8FromIdentifier(name);

		return strcmp(string, "version")     == 0 ||
		       strcmp(string, "tick")        == 0 ||
		       strcmp(string, "avatar")      == 0 ||
		       strcmp(string, "name")        == 0 ||
		       strcmp(string, "camera")      == 0 ||
		       strcmp(string, "identity")    == 0 ||
		       strcmp(string, "context")     == 0 ||
		       strcmp(string, "description") == 0;
	}

	return false;
}

bool
Mumble_GetProperty (NPObject* object, NPIdentifier name, NPVariant* result)
{
	Mumble* mumble = PA_Private(object);

	if (!NPN_IdentifierIsString(name)) {
		return false;
	}

	NPUTF8* string = NPN_UTF8FromIdentifier(name);

	if (strcmp(string, "version") == 0) {
		DOUBLE_TO_NPVARIANT(mumble->version, *result);
	}
	else if (strcmp(string, "tick") == 0) {
		DOUBLE_TO_NPVARIANT(mumble->tick, *result);
	}
	else if (strcmp(string, "avatar") == 0) {
		OBJECT_TO_NPVARIANT(Space_Create(PA_Plugin(object),
		                                 mumble->avatar.position,
		                                 mumble->avatar.front,
		                                 mumble->avatar.top),
		                    *result);
	}
	else if (strcmp(string, "name") == 0) {
		STRINGZ_TO_NPVARIANT(_string(mumble->name, 256), *result);
	}
	else if (strcmp(string, "camera") == 0) {
		OBJECT_TO_NPVARIANT(Space_Create(PA_Plugin(object),
		                                 mumble->camera.position,
		                                 mumble->camera.front,
		                                 mumble->camera.top),
		                    *result);
	}
	else if (strcmp(string, "identity") == 0) {
		STRINGZ_TO_NPVARIANT(_string(mumble->identity, 256), *result);
	}
	else if (strcmp(string, "context") == 0) {
		OBJECT_TO_NPVARIANT(Context_Create(PA_Plugin(object),
		                                   &mumble->context.length,
		                                   mumble->context.value),
		                    *result);
	}
	else if (strcmp(string, "description") == 0) {
		STRINGZ_TO_NPVARIANT(_string(mumble->description, 2048), *result);
	}
	else {
		return false;
	}

	return true;
}

bool
Mumble_SetProperty (NPObject* object, NPIdentifier name, const NPVariant* value)
{
	Mumble* mumble = PA_Private(object);

	if (!NPN_IdentifierIsString(name)) {
		return false;
	}

	NPUTF8* string = NPN_UTF8FromIdentifier(name);

	if (strcmp(string, "version") == 0) {
		if (!NPVARIANT_IS_DOUBLE(*value)) {
			return false;
		}

		mumble->version = NPVARIANT_TO_DOUBLE(*value);
	}
	else if (strcmp(string, "tick") == 0) {
		if (!NPVARIANT_IS_DOUBLE(*value)) {
			return false;
		}

		mumble->tick = NPVARIANT_TO_DOUBLE(*value);
	}
	else if (strcmp(string, "name") == 0) {
		if (!NPVARIANT_IS_STRING(*value)) {
			return false;
		}

		mbstowcs(mumble->name, NPVARIANT_TO_STRING(*value).UTF8Characters, 256);
	}
	else if (strcmp(string, "identity") == 0) {
		if (!NPVARIANT_IS_STRING(*value)) {
			return false;
		}

		mbstowcs(mumble->identity, NPVARIANT_TO_STRING(*value).UTF8Characters, 256);
	}
	else if (strcmp(string, "description") == 0) {
		if (!NPVARIANT_IS_STRING(*value)) {
			return false;
		}

		mbstowcs(mumble->description, NPVARIANT_TO_STRING(*value).UTF8Characters, 2048);
	}
	else {
		return false;
	}

	return true;
}
