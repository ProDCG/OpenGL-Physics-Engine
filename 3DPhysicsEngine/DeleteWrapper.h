#pragma once

// c++ std import
#include <type_traits>

// template for class types, acts as a wrapper for deletion (saves lines of code)
template <class Type>
struct DeleteWrapper {
	Type object;

	// constructor and deconstructor
	template <typename... Args>
	DeleteWrapper(Args... args) : object(std::forward<Args>(args)...) {}

	~DeleteWrapper() {
		object.Delete();
	}
};