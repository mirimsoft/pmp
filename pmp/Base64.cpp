#include <string.h>
#include "base64.h"

/* aaaack but it's fast and const should make it shared text page. */
static const unsigned char pr2six[256] =
{
	/* ASCII table */
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 62, 64, 64, 64, 63,
	52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 64, 64, 64, 64, 64, 64,
	64,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
	15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 64, 64, 64, 64, 64,
	64, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
	41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64
};


static const char basis_64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

namespace Mirim
{
	int Base64::GetDecodeLength(const char *bufcoded)
	{
		int nbytesdecoded;
		register const unsigned char *bufin;
		register int nprbytes;

		bufin = (const unsigned char *) bufcoded;
		while(pr2six[*(bufin++)] <= 63);

		nprbytes = static_cast<int>((bufin -(const unsigned char *) bufcoded) - 1);
		nbytesdecoded = ((nprbytes + 3) / 4) * 3;

		return nbytesdecoded + 1;
	}

	int Base64::Decode(const char *bufcoded, char *bufplain)
	{
		int nbytesdecoded;
		register const unsigned char *bufin;
		register unsigned char *bufout;
		register int nprbytes;

		bufin = (const unsigned char *) bufcoded;
		while(pr2six[*(bufin++)] <= 63);
		nprbytes = static_cast<int>((bufin -(const unsigned char *) bufcoded) - 1);
		nbytesdecoded = ((nprbytes + 3) / 4) * 3;

		bufout = (unsigned char *) bufplain;
		bufin = (const unsigned char *) bufcoded;

		while(nprbytes > 4) 
		{
			*(bufout++) = (unsigned char)(pr2six[*bufin] << 2 | pr2six[bufin[1]] >> 4);
			*(bufout++) = (unsigned char)(pr2six[bufin[1]] << 4 | pr2six[bufin[2]] >> 2);
			*(bufout++) = (unsigned char)(pr2six[bufin[2]] << 6 | pr2six[bufin[3]]);
			bufin += 4;
			nprbytes -= 4;
		}

		/* Note:(nprbytes == 1) would be an error, so just ingore that case */
		if (nprbytes > 1) 
		{
			*(bufout++) = (unsigned char)(pr2six[*bufin] << 2 | pr2six[bufin[1]] >> 4);
		}
		if (nprbytes > 2) 
		{
			*(bufout++) = (unsigned char)(pr2six[bufin[1]] << 4 | pr2six[bufin[2]] >> 2);
		}
		if (nprbytes > 3) 
		{
			*(bufout++) = (unsigned char)(pr2six[bufin[2]] << 6 | pr2six[bufin[3]]);
		}

		*(bufout++) = '\0';
		nbytesdecoded -= (4 - nprbytes) & 3;
		return nbytesdecoded;
	}

	int Base64::GetEncodeLength(int len)
	{
		return((len + 2) / 3 * 4) + 1;
	}

	int Base64::Encode(const char *string, char *encoded)
	{
		int i;
		char *p;

		int len = static_cast<int>(strlen(string));

		p = encoded;
		for(i = 0; i < len - 2; i += 3)
		{
			*p++ = basis_64[(string[i] >> 2) & 0x3F];
			*p++ = basis_64[((string[i] & 0x3) << 4) | ((int)(string[i + 1] & 0xF0) >> 4)];
			*p++ = basis_64[((string[i + 1] & 0xF) << 2) | ((int)(string[i + 2] & 0xC0) >> 6)];
			*p++ = basis_64[string[i + 2] & 0x3F];
		}
		if (i < len)
		{
			*p++ = basis_64[(string[i] >> 2) & 0x3F];
			if (i == (len - 1))
			{
				*p++ = basis_64[((string[i] & 0x3) << 4)];
				*p++ = '=';
			}
			else 
			{
				*p++ = basis_64[((string[i] & 0x3) << 4) | ((int)(string[i + 1] & 0xF0) >> 4)];
				*p++ = basis_64[((string[i + 1] & 0xF) << 2)];
			}

			*p++ = '=';
		}

		*p++ = '\0';

		return static_cast<int>(p - encoded);
	}

	int Base64::Decode(const wchar_t *w_input, wchar_t *w_output)
	{
		try
		{
			size_t length =  wcslen(w_input);
			char *input = (char *) malloc(sizeof(char) * length);
			wcstombs(input, w_input, length);

			size_t decode_length = this->GetDecodeLength(input);
			char *output = (char *) malloc(sizeof(char) * decode_length);

			size_t count = this->Decode(input, output);
			mbstowcs(w_output, output, 256);

			free(input);
			free(output);

			return (int)count;
		}
		catch(...)
		{
			return -1;
		}
	}

	int Base64::Encode(const wchar_t *w_input, wchar_t *w_output)
	{
		try
		{
			size_t length =  wcslen(w_input) + 1;
			char *input = (char *) malloc(sizeof(char) * length);

			size_t encode_length = this->GetEncodeLength(static_cast<int>(length));
			char *output = (char *) malloc(sizeof(char) * encode_length + 1);

			wcstombs(input, w_input, length);

			size_t count = this->Encode(input, output);
			mbstowcs(w_output, output, encode_length + 1);

			free(input);
			free(output);

			return static_cast<int>(count);
		}
		catch(...)
		{
			return -1;
		}
	}
}
