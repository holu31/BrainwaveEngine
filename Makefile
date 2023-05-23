CC=g++
CFLAGS = -fPIC -O2 -g -I include/ -I /usr/include/bullet/ -I /usr/include/freetype2/ -std=c++20

LDFLAGS = -lglfw -lvulkan -lstb -lBulletCollision -lLinearMath -lBulletDynamics \
 -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi -lfreetype

.PHONY: all
all: build.cpp

build.cpp:
	$(CC) $(CFLAGS) -c -o bin/engine.o src/core/engine.cpp
	$(CC) $(CFLAGS) -c -o bin/input.o src/core/input.cpp
	$(CC) $(CFLAGS) -c -o bin/shaders.o src/render/shaders.cpp
	$(CC) $(CFLAGS) -c -o bin/mesh.o src/render/mesh.cpp
	$(CC) $(CFLAGS) -c -o bin/camera.o src/render/camera.cpp
	$(CC) $(CFLAGS) -c -o bin/texture.o src/render/texture.cpp
	$(CC) $(CFLAGS) -c -o bin/text.o src/render/text.cpp
	$(CC) $(CFLAGS) -c -o bin/physics.o src/physics/physics.cpp
	$(CC) $(CFLAGS) -c -o bin/physicsObj.o src/physics/physicsObj.cpp
	
	$(CC) $(CFLAGS) -shared -o core.so $(wildcard bin/*.o) glad/glad.c $(LDFLAGS)

build.game:

	mkdir -p build/$(build)/

	$(CC) $(CFLAGS) -o build/$(build)/$(build) $(file) ./core.so -lBulletCollision -lLinearMath -lBulletDynamics -lBulletSoftBody

	cp -r resources/ build/$(build)/
	cp core.so build/$(build)/

clean:
	rm bin/*