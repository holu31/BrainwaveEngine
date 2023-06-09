CC=g++
CFLAGS = -fPIC -O2 -g -I include/ -std=c++20

LDFLAGS = -lglfw -lvulkan -lstb -lBulletCollision -lLinearMath -lBulletDynamics \
 -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi -lfreetype

.PHONY: all clean
all: all/core.so

all/core.so:
	$(CC) $(CFLAGS) -c -o bin/engine.o src/core/engine.cpp
	$(CC) $(CFLAGS) -c -o bin/input.o src/core/input.cpp
	$(CC) $(CFLAGS) -c -o bin/obj.o src/core/obj.cpp
	$(CC) $(CFLAGS) -c -o bin/maploader.o src/core/maploader.cpp
	$(CC) $(CFLAGS) -c -o bin/sound.o src/core/sound.cpp
	$(CC) $(CFLAGS) -c -o bin/shaders.o src/render/shaders.cpp
	$(CC) $(CFLAGS) -c -o bin/mesh.o src/render/mesh.cpp
	$(CC) $(CFLAGS) -c -o bin/sprite2d.o src/render/sprite2d.cpp
	$(CC) $(CFLAGS) -c -o bin/camera.o src/render/camera.cpp
	$(CC) $(CFLAGS) -c -o bin/texture.o src/render/texture.cpp
	$(CC) $(CFLAGS) -c -o bin/light.o src/render/light.cpp
	$(CC) $(CFLAGS) -c -o bin/text.o src/ui/text.cpp
	$(CC) $(CFLAGS) -c -o bin/physics.o src/physics/physics.cpp
	$(CC) $(CFLAGS) -c -o bin/physicsObj.o src/physics/physicsObj.cpp
	
	$(CC) $(CFLAGS) -shared -o core.so $(wildcard bin/*.o) glad/glad.c $(LDFLAGS)

build.game:

	mkdir -p build/$(build)/
	mkdir -p build/$(build)/lib64

	$(CC) $(CFLAGS) -o build/$(build)/$(build) $(file) ./core.so \
		 ./lib64/ikpFlac.so ./lib64/ikpMP3.so ./lib64/libIrrKlang.so \
		 -lBulletCollision -lLinearMath -lBulletDynamics -lBulletSoftBody

	cp -r resources/ build/$(build)/
	cp core.so build/$(build)/

	cp lib64/ikpFlac.so build/$(build)/lib64/
	cp lib64/ikpMP3.so build/$(build)/lib64/
	cp lib64/libIrrKlang.so build/$(build)/lib64/

build.mapcreator:

	$(CC) $(CFLAGS) -o mapcreator/mapcreator mapcreator/src/mapcreator.cpp ./core.so -lstb -lBulletCollision -lLinearMath -lBulletDynamics -lBulletSoftBody

	cp -r resources/ mapcreator/
	cp core.so mapcreator/

clean:
	rm bin/*