CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -std=c89

SABUGO_SRC=./src/sabugo
SABUGO_CORE=$(SABUGO_SRC)/core
SABUGO_RENDERER=$(SABUGO_SRC)/renderer

VENDOR_SRC=./src/vendor

MINGW32_LIB=/C/mingw64/x86_64-w64-mingw32/lib

.PHONY:clean\
    vendor-full-build\
    glfw-build\
    glew-build\
    vendor-full-clean\
    glfw-clean\
    glew-clean\
    vendor-suite\
    sabugo-rendering-suite

./sandbox/demo/bin/demo:\
    ./sandbox/demo/src/demo.c\
    sabugo-rendering-suite
	$(CC) -I./src $< -o $@ $(CFLAGS) -L./lib -lsabugo 

sabugo-rendering-suite:\
    vendor-suite\
    ./lib/libsabugo.a

./lib/libsabugo.a:\
    $(SABUGO_CORE)/.obj/window.o\
    $(SABUGO_RENDERER)/.obj/renderer.o\
    $(SABUGO_RENDERER)/.obj/sbgl.o
	ar -rcs $@ ./lib/glfw_obj/*
	ar -rs $@ ./lib/gdi32_obj/*
	ar -rs $@ ./lib/glew32_obj/*
	ar -rs $@ ./lib/opengl32_obj/*
	ar -rs $@ $^
	touch $@

$(SABUGO_CORE)/.obj/%.o:\
    $(SABUGO_CORE)/%.c
	@if [ ! -d "$(SABUGO_CORE)/.obj" ]; then mkdir $(SABUGO_CORE)/.obj; fi
	$(CC) -I./src -c $< -o $@ $(CFLAGS)
	touch $@

$(SABUGO_RENDERER)/.obj/%.o:\
    $(SABUGO_RENDERER)/%.c
	@if [ ! -d "$(SABUGO_RENDERER)/.obj" ]; then mkdir $(SABUGO_RENDERER)/.obj; fi
	$(CC) -I./src -c $< -o $@ $(CFLAGS)
	touch $@

clean:
	rm -f ./sandbox/demo/bin/*
	rm -f ./lib/*.a
	
	@if [ -d $(SABUGO_CORE)/.obj ]; then rm -r $(SABUGO_CORE)/.obj; fi
	@if [ -d $(SABUGO_RENDERER)/.obj ]; then rm -r $(SABUGO_RENDERER)/.obj; fi
	
	@if [ -d ./lib/glfw_obj ]; then rm -r ./lib/glfw_obj; fi
	@if [ -d ./lib/gdi32_obj ]; then rm -r ./lib/gdi32_obj; fi
	@if [ -d ./lib/glew32_obj ]; then rm -r ./lib/glew32_obj; fi
	@if [ -d ./lib/opengl32_obj ]; then rm -r ./lib/opengl32_obj; fi


vendor-suite:\
    vendor-full-build
	cp $(VENDOR_SRC)/GLFW/*.a ./lib
	cp $(VENDOR_SRC)/GL/*.a ./lib
	@mkdir ./lib/glfw_obj &&\
	    mv ./lib/libglfw.a ./lib/glfw_obj &&\
	    cd ./lib/glfw_obj &&\
	    ar -x libglfw.a
	@mkdir ./lib/gdi32_obj &&\
	    mv ./lib/libgdi32.a ./lib/gdi32_obj &&\
	    cd ./lib/gdi32_obj &&\
	    ar -x libgdi32.a
	@mkdir ./lib/glew32_obj &&\
	    mv ./lib/libglew32.a ./lib/glew32_obj &&\
	    cd ./lib/glew32_obj &&\
	    ar -x libglew32.a
	@mkdir ./lib/opengl32_obj &&\
	    mv ./lib/libopengl32.a ./lib/opengl32_obj &&\
	    cd ./lib/opengl32_obj &&\
	    ar -x libopengl32.a
	@mv ./lib/glfw_obj/libglfw.a ./lib/libglfw.a
	@mv ./lib/gdi32_obj/libgdi32.a ./lib/libgdi32.a
	@mv ./lib/glew32_obj/libglew32.a ./lib/libglew32.a
	@mv ./lib/opengl32_obj/libopengl32.a ./lib/libopengl32.a


vendor-full-build:\
    $(VENDOR_SRC)/GLFW\
    $(VENDOR_SRC)/GL
	
$(VENDOR_SRC)/GLFW:
	if [ -d "$(VENDOR_SRC)/GLFW" ]; then rm -rf "$(VENDOR_SRC)/GLFW"; fi
	git clone https://github.com/glfw/glfw $(VENDOR_SRC)/glfw-build
	mkdir $(VENDOR_SRC)/glfw-build/build
	cd $(VENDOR_SRC)/glfw-build/build\
	    && cmake -G "MinGW Makefiles" ..\
	    && mingw32-make
	mv $(VENDOR_SRC)/glfw-build/include/GLFW $(VENDOR_SRC)/.
	mv $(VENDOR_SRC)/glfw-build/build/src/libglfw3.a $(VENDOR_SRC)/GLFW/libglfw.a
	cp $(MINGW32_LIB)/libgdi32.a $(VENDOR_SRC)/GLFW/libgdi32.a
	if [ -d "$(VENDOR_SRC)/glfw-build" ]; then rm -rf $(VENDOR_SRC)/glfw-build; fi

$(VENDOR_SRC)/GL:
	if [ -d "$(VENDOR_SRC)/GL" ]; then rm -rf "$(VENDOR_SRC)/GL"; fi
	git clone https://github.com/nigels-com/glew $(VENDOR_SRC)/glew-build
	cd $(VENDOR_SRC)/glew-build/auto && mingw32-make
	cd $(VENDOR_SRC)/glew-build/build/cmake\
	    && cmake -G "MinGW Makefiles" .\
	    && mingw32-make
	mv $(VENDOR_SRC)/glew-build/include/GL $(VENDOR_SRC)/.
	mv $(VENDOR_SRC)/glew-build/build/cmake/lib/libglew32.a $(VENDOR_SRC)/GL/libglew32.a
	cp $(MINGW32_LIB)/libopengl32.a $(VENDOR_SRC)/GL/libopengl32.a
	if [ -d "$(VENDOR_SRC)/glew-build" ]; then rm -rf $(VENDOR_SRC)/glew-build; fi

vendor-full-clean:\
    glfw-clean\
    glew-clean

glfw-clean:
	@if [ -d $(VENDOR_SRC)/GLFW ]; then rm -r $(VENDOR_SRC)/GLFW; fi
	@if [ -d $(VENDOR_SRC)/glfw-build ]; then rm -r $(VENDOR_SRC)/glfw-build; fi

glew-clean:
	@if [ -d $(VENDOR_SRC)/GL ]; then rm -r $(VENDOR_SRC)/GL; fi
	@if [ -d $(VENDOR_SRC)/glew-build ]; then rm -r $(VENDOR_SRC)/glew-build; fi


