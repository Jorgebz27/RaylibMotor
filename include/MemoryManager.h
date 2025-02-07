#pragma once
#include <iostream>

class MemoryManager
{
public:

	static MemoryManager* getInstance();
	size_t alloc(size_t size);

private:

	static MemoryManager* instance;
	// Evita hacer copias
	MemoryManager(const MemoryManager&) = delete; 
	MemoryManager& operator=(const MemoryManager&) = delete;
	//
	MemoryManager();
	~MemoryManager();
};

