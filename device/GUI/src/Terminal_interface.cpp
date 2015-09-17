
#include "Terminal_Interface.h"

using namespace STR;

__TTY::__TTY () {}
	
void __TTY::operator () (void *buff, uint32_t size)
{
	this->Buff = (char *)buff;
	this->Size = size;
	this->Cursor = 0;
}

__TEXT __TTY::Print ()
{
	__TEXT text;
	text.Buff.Ram = this->Buff;
	text.Size = this->Cursor;
	return text;
}

void __TTY::Clear ()
{
	for (int32_t i = this->Size; i > 0; i--) {
		this->Buff[i] = 0;
	}
	this->Cursor = 0;
}

__TTY &__TTY::Print (int32_t cursor, char *str, uint32_t size)
{
	if (this->Cursor + size > this->Size) return *this;
	this->Cursor = cursor;
	uint32_t i = 0;
	while (size--) {
		this->Buff[cursor++] = str[i++];
	}
	this->Cursor = cursor;
	return *this;
}

__TTY &__TTY::Print (char *str, uint32_t size)
{
	if (this->Cursor + size > this->Size) return *this;
	uint32_t cursor = this->Cursor;
	uint32_t i = 0;
	while (size--) {
		this->Buff[cursor++] = str[i++];
	}
	this->Cursor = cursor;
	return *this;	
}

__TTY &__TTY::Print (int32_t cursor, char *str)
{
	this->Cursor = cursor;
	uint32_t i = 0;
	uint32_t s = this->Size - cursor;
	while (str[i] && i < s) {
		this->Buff[cursor++] = str[i++];
	}
	this->Cursor = cursor + i;
	return *this;
}

__TTY &__TTY::Print (char *str)
{
	uint32_t cursor = this->Cursor;
	uint32_t i = 0;
	uint32_t s = this->Size - cursor;
	while (str[i] && i < s) {
		this->Buff[cursor++] = str[i++];
	}
	this->Cursor = cursor + i;
	return *this;
}

__TTY &__TTY::Char (int32_t cursor, char A)
{
	if (cursor + 1 > this->Size)  {
		return *this;
	} else {}
  this->Buff[cursor++] = A;
	this->Cursor = cursor;
	return *this;	
}

__TTY &__TTY::Char (char A)
{
	if (this->Cursor + 1 > this->Size)  {
		return *this;
	} else {}
  this->Buff[this->Cursor++] = A;
	return *this;	
}

__TTY &__TTY::operator << (char *A)
{
	return this->Print(0, A);
}

__TTY &__TTY::operator << (int32_t A)
{
	char temp[10];
	itoa(A, temp, 10);
	this->Print(0, temp, strlen(temp));
	return *this;
}

__TTY &__TTY::operator << (char A)
{
	this->Char(0, A);
	return *this;
}

__TTY &__TTY::operator + (char *A)
{
	return this->Print(A);
}

__TTY &__TTY::operator + (int32_t A)
{
	char temp[10];
	itoa(A, temp, 10);
	this->Print(temp, strlen(temp));
	return *this;
}

__TTY &__TTY::operator + (char A)
{
	this->Char(A);
	return *this;
}

/*End Of File*/

