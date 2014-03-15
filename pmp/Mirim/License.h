#pragma once
#include "ProTk.h"
#include "Option.h"
#include "Base64.h"
#include "BlowFish.h"

namespace Mirim
{
	class License
	{
	public:
		ProName		w_name;
		ProName		w_build;
		ProName		w_mac_address;
		ProPath		w_key;
		ProPath		w_file_path;

	public:
		License(void);
		License(const wchar_t *w_file_path, const wchar_t *w_address);
		~License(void);
		bool License::IsValid(bool verbose);


	};
}