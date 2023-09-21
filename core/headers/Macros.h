#pragma once
#include <functional>

#define FORWARD_CALL(fn) [this](auto&& ...args) -> decltype(auto) {return this->fn(std::forward<decltype(args)>(args)...);}
