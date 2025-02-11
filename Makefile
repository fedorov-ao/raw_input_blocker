.SUFFIXES:

VERSION = 0.5.2

HEADERS = logging.hpp util.hpp vkeys.hpp user32.hpp config.hpp
SOURCES = wrapper.cpp logging.cpp vkeys.cpp user32.cpp
#If compiled with -On, dll can not be loaded
#CFLAGS = -std=c++11 -I. -D_WIN32_WINNT=0x0501
CFLAGS = -std=c++11 -I. -DNDEBUG -Os -ffunction-sections -fdata-sections
LDFLAGS = -static-libstdc++ -static-libgcc -shared -s -Wl,--gc-sections,--exclude-all-symbols,--kill-at

CC32 = i686-w64-mingw32-g++-win32
TARGET32 = user32.dll
CFLAGS32 = -m32 $(CFLAGS)
OBJECTS32 = $(SOURCES:%.cpp=%.o)

%.o: %.cpp $(HEADERS)
	$(CC32) $(CFLAGS32) -c $< -o $@

build32: $(OBJECTS32)
	$(CC32) $(CFLAGS32) -o $(TARGET32) $(OBJECTS32) $(LDFLAGS)

CC64 = x86_64-w64-mingw32-g++
TARGET64 = user32.dll_64
CFLAGS64 = -m64 $(CFLAGS)
OBJECTS64 = $(SOURCES:%.cpp=%.o64)

%.o64: %.cpp $(HEADERS)
	$(CC64) $(CFLAGS64) -c $< -o $@

build64: $(OBJECTS64)
	$(CC64) $(CFLAGS64) -o $(TARGET64) $(OBJECTS64) $(LDFLAGS)

build: build32 build64

PACKAGE = raw_input_blocker_$(VERSION).zip

package: build32 build64
	rm -f $(PACKAGE)
	zip -9 $(PACKAGE) $(TARGET32) $(TARGET64) user32.cfg

clean:
	rm  -f *.o *.o64 *.def *.lib 2>1

vacuum: clean
	rm  -f *.dll *.dll_64 *.zip 2>1 
