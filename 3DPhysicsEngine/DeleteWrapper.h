#pragma once

#include <type_traits>

template <class Type>
struct DeleteWrapper {
	Type object;

	template <typename... Args>
	DeleteWrapper(Args... args) : object(std::forward<Args>(args)...) {}

	~DeleteWrapper() {
		object.Delete();
	}
};