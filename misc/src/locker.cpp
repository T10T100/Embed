#include "locker.h"

Locker::Locker (){}
	
void Locker::Unlock (uint32_t id)
{
	this->lock = false;
}

void Locker::Lock (uint32_t id)
{
	this->lock = true;
}

bool Locker::Test ()
{
	return this->lock;
}

