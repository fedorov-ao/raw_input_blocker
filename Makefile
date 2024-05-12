CC = i686-w64-mingw32-g++-win32
TARGET = user32.dll
HEADERS = wrapper.hpp logging.hpp util.hpp
SOURCES = wrapper.cpp logging.cpp
OBJECTS = $(SOURCES:%.cpp=%.o)
#If compiled with -On, dll can not be loaded
#CFLAGS = -std=c++11 -I. -D_WIN32_WINNT=0x0501
CFLAGS = -std=c++11 -I. -DNDEBUG -Os -ffunction-sections -fdata-sections
LDFLAGS = -static-libstdc++ -static-libgcc -shared -s -Wl,--gc-sections,--exclude-all-symbols,--kill-at

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $*.cpp

debug: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

clean:
	rm  *.o *.def *.lib *.dll 2>1
