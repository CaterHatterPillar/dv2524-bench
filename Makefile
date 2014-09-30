CXXFLAGS = -O3 -Wall -fmessage-length=0
OBJS = dv2524-bench.o
LIBS = -lGLESv2 -lEGL -lm -lX11
# Paravirtualized GLES2: -lgl2
# Non-paravirtualized GLES2: -lGLESv2
# Debug flags: -O0 -g
TARGET = dv2524-bench
HEADERS = *.h shared/*.h shared/tex/*.h shared/obj/*.h
SOURCES = *.cpp shared/*.c

all: link

link: compile
	g++ $(CXXFLAGS) -o dv2524-bench *.o $(LIBS)

compile: clean
	g++ $(CXXFLAGS) -c $(HEADERS) $(SOURCES)

clean:
	rm -f $(OBJS) $(TARGET)
