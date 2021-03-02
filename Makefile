CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -std=c89

# Linkage
LINK_GLFW=-lglfw
LINK_GLEW=-lGLEW
LINK_GL=-lGL
LINK_EXTERNAL=$(LINK_GLFW) $(LINK_GLEW) $(LINK_GL)


# Modules
SABUGO_SRC=src/Sabugo
SABUGO_CORE=$(SABUGO_SRC)/Core
SABUGO_RENDERER=$(SABUGO_SRC)/Renderer

# Defines
DEFINE_CORE_BACKEND=-DGLFW_BACKEND
DEFINE_RENDERER_BACKEND=-DGL_BACKEND

# Demo
DEMO_SRC=./sandbox/demo/src
DEMO_BIN=./sandbox/demo/bin



$(DEMO_BIN)/demo:$(DEMO_SRC)/demo.c lib/libsabugo.a
	$(CC) -I./src/Sabugo $< -o $@ $(CFLAGS) $(LINK_EXTERNAL) -lm -L./lib -lsabugo
	touch $@

lib/libsabugo.a:$(SABUGO_CORE)/.obj/Window.o\
		$(SABUGO_CORE)/.obj/Log.o\
		$(SABUGO_RENDERER)/.obj/GraphicalContext.o\
		$(SABUGO_RENDERER)/.obj/Shapes.o\
		$(SABUGO_RENDERER)/.obj/Renderer.o\
		$(SABUGO_RENDERER)/.obj/Shader.o
	ar -rcs $@ $^
	touch $@

$(SABUGO_CORE)/.obj/%.o:$(SABUGO_CORE)/%.c
	@if [ ! -d "$(SABUGO_CORE)/.obj" ]; then mkdir "$(SABUGO_CORE)/.obj"; fi
	$(CC) -I./src/Sabugo -c $< -o $@ $(CFLAGS) $(DEFINE_CORE_BACKEND)
	touch $@

$(SABUGO_RENDERER)/.obj/%.o:$(SABUGO_RENDERER)/%.c
	@if [ ! -d "$(SABUGO_RENDERER)/.obj" ]; then mkdir "$(SABUGO_RENDERER)/.obj"; fi
	$(CC) -I./src/Sabugo -c $< -o $@ $(CFLAGS) $(DEFINE_RENDERER_BACKEND)
	touch $@
documentation:
	doxygen docs/dconfig
clean:
	@echo "Cleaning up..."
	@if [ -d "$(SABUGO_CORE)/.obj" ]; then rm -r "$(SABUGO_CORE)/.obj"; fi
	@if [ -d "$(SABUGO_RENDERER)/.obj" ]; then rm -r "$(SABUGO_RENDERER)/.obj"; fi
	rm -f ./lib/*.a
	rm -f ./sandbox/demo/bin/*
