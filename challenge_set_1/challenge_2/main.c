#include "dcrypto.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// inverse of what we did in problem 1
char dec_to_hex(char dec)
{
	if (dec >= 0 && dec <= 9)
		return dec + '0';
	if (dec >= 10 && dec <= 15)
		return dec - 10 + 'a';
	return -1;
}


// decimal string to hex string
void dec_string_to_hex(char* dec, char* hex, size_t len)
{
	for (size_t i = 0; i < len; ++i)
		hex[i] = dec_to_hex(dec[i]);
}


//convert hex character buffer to decimal values
void hex_string_to_dec(const char* hex, char* dec, size_t len)
{
	for (size_t i = 0; i < len; ++i)
		dec[i] = hex_to_dec(hex[i]);
}


// equal length xor
void dec_xor(const char* arg0, const char* arg1, char* output, size_t len)
{
	for (size_t i = 0; i < len; ++i)
		output[i] = arg0[i] ^ arg1[i];
}


// cryptopals set 1 problem 2
int main()
{

	char* arg0 = "1c0111001f010100061a024b53535009181c";
	char* arg1 = "686974207468652062756c6c277320657965";
	size_t len = strlen(arg0);

	// convert hex values into decimal values
	char d_arg0[len];
	char d_arg1[len];
	hex_string_to_dec(arg0, d_arg0, len);
	hex_string_to_dec(arg1, d_arg1, len);

	// create an output buffer for our results
	char xor[len];

	// perform our xor
	dec_xor(d_arg0, d_arg1, xor, len);


	// convert back to hex
	char xor_hex[len];
	dec_string_to_hex(xor, xor_hex, len);

	// print results
	printf("%s \n", xor_hex);
	return 0;
}