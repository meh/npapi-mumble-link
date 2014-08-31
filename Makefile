CC      = i686-pc-mingw32-gcc
AR      = i686-pc-mingw32-ar
WINDRES = i686-pc-mingw32-windres
CFLAGS  = -std=c11 -Wall -Iinclude -Ivendor/pimpa/include -DXP_WIN=1 -ggdb
LDFLAGS = -Wl,--enable-stdcall-fixup

LIBRARY  = npMumbleLink.dll
SOURCES  = source/main.c source/mumble.c source/live.c source/snapshot.c source/context.c source/space.c source/vector.c
OBJECTS  = $(SOURCES:.c=.o)
PIMPA    = vendor/pimpa

all: $(SOURCES) $(LIBRARY)

$(LIBRARY) : $(OBJECTS) $(PIMPA) resource.res
	$(CC) $(CFLAGS) $(LDFLAGS) -shared -o $(LIBRARY) $(OBJECTS) $(PIMPA)/libpimpa.a resource.res export.def

.PHONY: $(PIMPA)
$(PIMPA):
	$(MAKE) -C $(PIMPA) CC="$(CC)" AR="$(AR)" CFLAGS="-DXP_WIN=1 -ggdb"

resource.res: resource.rc
	$(WINDRES) -i resource.rc -O coff -o resource.res

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f source/*.o
	rm -f resource.res
	rm -f npMumbleLink.dll
	$(MAKE) -C $(PIMPA) clean
