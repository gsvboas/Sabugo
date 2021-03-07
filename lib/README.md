This directory is reserved for Sabugo Library outputs. 
It should be empty at all times make (or mingw32-make) clean is called; And it should contain the static 
sabugo library libsabugo.a, as well as static libraries of its external dependencies (e.g., GLFW, GLEW, etc).

Link against sabugo by specifying this folder as link target directory and linking against libsabugo.a.

GCC:
	gcc <application_source_codes.c, ...> -o <application_executable_name> -L<sabugo_root_dir>/lib -lsabugo (...)
