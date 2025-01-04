#pragma once


#include <dlfcn.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <functional>

// Function that loads and invokes a function dynamically using dlsym
template <typename Func, typename... Args>
auto noble_function_helper(void* handle, const char* func_name, Args&&... args) {
    void* symbol = dlsym(handle, func_name);
    if (!symbol) {
        throw std::invalid_argument("NOBLE: cannot find function " + std::string(func_name) + " in library.\n" + dlerror());
    }
    std::function<Func> func_ptr = reinterpret_cast<Func*>(symbol);
    using ReturnType = typename std::invoke_result<Func, Args...>::type;

    if constexpr (std::is_void_v<ReturnType>) {
        std::invoke(func_ptr, std::forward<Args>(args)...);
    } else {
        return std::invoke(func_ptr, std::forward<Args>(args)...);
    }
};


#define noble_function(handle, func, ...) noble_function_helper<decltype(func)>(handle, #func, ##__VA_ARGS__)

inline void* noble_file_open(const std::string& path) {
    void* handle = dlopen(path.c_str(), RTLD_LAZY);
    if (!handle) {
        throw std::runtime_error("NOBLE: Failed to open library: " + path + "\n" + dlerror());
    };
    return handle;
};
