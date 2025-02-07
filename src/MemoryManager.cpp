#include "MemoryManager.h"

MemoryManager* MemoryManager::instance = nullptr;

MemoryManager::MemoryManager()
{
}

MemoryManager::~MemoryManager()
{
}

MemoryManager* MemoryManager::getInstance()
{
	if (instance == nullptr)
	{
		instance = new MemoryManager();
	}
	return instance;
}

size_t MemoryManager::alloc(size_t size)
{
	std::cout << "Allocating " << size << " bytes" << std::endl;

	void* ptr = malloc(size);

	return size;
}
