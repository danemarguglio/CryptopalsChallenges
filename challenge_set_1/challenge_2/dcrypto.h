#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// convert an ascii hex value to decimal
char hex_to_dec(char ch)
{
	// all ascii characters are sequential
	// A - 65, B - 66, ...
	// a - 97, b - 98, ...
	// so we can convert it into decimal as follows
	// hex A = 65
	// hex F = 70
	// F - A = 70 - 65 = 5
	// since [A-F] are 10 + [0-5] we add 10 to get our decimal value
	// F - A + 10 = 70 - 65 + 10 = 15
	if (ch >= '0' && ch <= '9')
		return ch - '0';
	if (ch >= 'A' && ch <= 'F')
		return ch - 'A' + 10;
	if (ch >= 'a' && ch <= 'f')
		return ch - 'a' + 10;

	// this will only work for hex numbers
	return -1;
}


// calculates the size of a b64 string for a given size of a hex string
// three hex characters make up 2 b64 characters
#define B64_LEN(len) ((len*2)/3 + ((len*2)%3 != 0))


// takes in three hex values, outputs two b64 values
void hex_to_b64(const char* hex, char* b64_out)
{
	const static char* b64_lookup = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	// hex holds 4 bits of data (0-15)
	// b64 holds 6 bits of data (0-65)

	// hex digits come in as a char, they only uses the lower nibble
	// they look like this in memory (4 bits)
	// 0000 aaaa
	// 0000 bbbb
	// 0000 cccc

	// b0 - We need the all the bits from a, and half from b
	// 0000 aaaa  a
	// 00aa aa00  a << 2
	// 0000 00bb  b >> 2
	// 00aa aabb  a << 2 | b >>2

	// b1 - We need the other half of the bits from b, and all of c
	// 0000 bbbb  b
	// bbbb 0000  b << 4
	// 0011 0000  0x30
	// 00bb 0000  (b << 4) & 0x30
	// 00bb cccc  (b << 4) & 0x30 | c

	char a = hex[0];
	char b = hex[1];
	char c = hex[2];

	char b0 = a << 2 | b >> 2;
	char b1 = ((b << 4) & 0x30) | c;

	b64_out[0] = b64_lookup[b0];
	b64_out[1] = b64_lookup[b1];

	return;
}


// takes in a buffer of hex characters, converts them to b64 and outputs them to b64_out buffer
void hex_string_to_b64(const char* hex, char* b64_out)
{
	size_t len = strlen(hex);
	size_t b64_pad = (len * 2) % 3;
	size_t b64_len = B64_LEN(len);
	
	// hold the converted hex data + any padding we need
	char hex_data[len + b64_pad];

	// convert all the hex ascii into actual numerical data
	for (size_t i = 0; i < len; ++i)
		hex_data[i] = hex_to_dec(hex[i]);

	// add padding bytes as necessary
	for (size_t i = 0; i < b64_pad; ++i)
		hex_data[len+i] = 0x00;

	// do the conversion, two b64 values at a time
	for (size_t i = 0; i < b64_len / 2; i++)
		hex_to_b64(&hex_data[i*3], &b64_out[2*i]);

	return;
}