#########################################################################
#you can use this makefile if you don't wanna use cmake for your project
#but first,you must build the libvisual_tool.so and copy it to your frequently-used directory for .so,such as /lib or /usr/lib
#if you use the cmake to build the libvisual_tool.so and then the .so file will located in cmake-build-debug/devel/lib/



CC=g++
INCLUDE_DIR=-I/opt/ros/kinetic/include/ -Iinclude/

# directory that catkin_LIBRARIES located
LIB_DIR=-L/opt/ros/kinetic/lib/ -L/usr/lib/x86_64-linux-gnu/
catkin_LIBRARIES=	\
-lroscpp	\
-lcpp_common	\
-lrosconsole	\
-lrostime

LIBS=-lvisual_tool $(catkin_LIBRARIES)
TARGET=libvisual_tool.so

all:build_so demo_main

#build libvisual_tool.so
build_so: src/visual_tool.cpp
	$(CC) $(INCLUDE_DIR) -shared -fPIC -o $(TARGET) src/visual_tool.cpp
	cp $(TARGET) /lib
demo_main: src/demo_main.cpp
	@echo 'include directory ' $(INCLUDE_DIR)
	@echo 'libs = ' $(LIBS)
	$(CC) $(INCLUDE_DIR) -o demo_main src/demo_main.cpp $(LIB_DIR) $(LIBS)
clean:
	rm -rf testVisual