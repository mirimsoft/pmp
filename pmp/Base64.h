#ifndef _BASE64_H_
#define _BASE64_H_

#include <cstdlib>

namespace Mirim
{
	class Base64
	{
	public:
		int Base64::GetEncodeLength(int len);
		int Base64::Encode(const char *plain_src, char * coded_dst);
		int Base64::Encode(const wchar_t *w_input, wchar_t *w_output);

		int Base64::GetDecodeLength(const char * coded_src);
		int Base64::Decode(const char *coded_src, char * plain_dst);
		int Base64::Decode(const wchar_t *w_input, wchar_t *w_output);
	};
}
#endif //_BASE64_H_
