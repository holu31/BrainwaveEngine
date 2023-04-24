CC=g++
OBJECTS=bin/engine.o bin/shaders.o bin/mesh.o bin/camera.o
CFLAGS = -fPIC -O2 -I include/ -std=c++20

LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

.PHONY: all
all: build.cpp

build.cpp:
	$(CC) $(CFLAGS) -c -o bin/engine.o src/core/engine.cpp
	$(CC) $(CFLAGS) -c -o bin/shaders.o src/render/shaders.cpp
	$(CC) $(CFLAGS) -c -o bin/mesh.o src/render/mesh.cpp
	$(CC) $(CFLAGS) -c -o bin/camera.o src/render/camera.cpp
	
	$(CC) $(CFLAGS) -shared -o core.so $(OBJECTS) glad/glad.c $(LDFLAGS)

build.game:

	mkdir -p build/$(build)/

	$(CC) $(CFLAGS) -o build/$(build)/$(build) $(file) ./core.so

	cp -r assets/ build/$(build)/
	cp core.so build/$(build)/
