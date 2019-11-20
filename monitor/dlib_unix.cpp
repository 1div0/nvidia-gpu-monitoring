#include "dlib_unix.h"
#include "utils.h"


dlib_handle_t load_dlib_or_halt(std::string_view lib_name) {
  dlib_handle_t handle = dlopen(lib_name.data(), RTLD_LAZY);
   
  if (handle == NULL) {
    // TODO: get error message by calling dlerror()
    halt(
      "failed to load NVML library by name '" + std::string(lib_name) + "'; " +
      "make sure Nvidia drivers are installed and '" +
      std::string(LIBS_PATH_ENV_VAR) + "' env var contains path to the library"
    );
  }  

  return handle;
}


dfunc_handle_t load_dfunc_or_halt(dlib_handle_t lib_handle, std::string_view func_name) {
  dfunc_handle_t func_handle = dlsym(lib_handle, func_name.data());

  if (func_handle == NULL) {
    // TODO: get error message by calling dlerror()
    halt("failed to load '" + std::string(func_name) + "' function from library");
  }

  return func_handle;
}


void unload_dlib(dlib_handle_t lib_handle) {
  dlclose(lib_handle);
}