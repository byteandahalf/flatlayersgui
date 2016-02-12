#pragma once

struct Button {
	uintptr_t** vtable; // 0
	bool isActive; // 4
	bool isVisible; // 5
};
