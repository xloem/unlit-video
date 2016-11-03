CXXFLAGS=$$(pkg-config gstreamer-1.0 --cflags) --std=c++11 -ggdb -Wall -Werror
LDLIBS=$$(pkg-config gstreamer-1.0 --libs) -lstdc++ -ggdb

test: main
	./main
	#G_SLICE=always-malloc G_DEBUG=gc-friendly valgrind --leak-check=full --suppressions=gst.supp ./main

main: FormatFile.o main.o FormatUtilGstreamer.o

clean:
	-rm *.o main
