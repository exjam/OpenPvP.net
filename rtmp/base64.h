#pragma once

#include "types.h"

class Base64 {
public:
	static char b64(char v){
		if(v <= 25)
			return 'A' + v;
		else if(v <= 51)
			return 'a' + (v - 26);
		else if(v <= 61)
			return '0' + (v - 52);
		else if(v == 62)
			return '+';
		else if(v == 63)
			return '/';
		else
			return 0;
	}

	static std::string encode(const std::string& source){
		return encode((uint8*)source.c_str(), source.length());
	}

	static std::string encode(uint8* data, uint32 length){
		std::string result;

		for(uint32 i = 0; i < length; i += 3){
			uint8 out[4];
			uint8 in[3] = { 0, 0, 0};
			uint32 r = length - i;
			if(r > 3) r = 3;
			memcpy(in, data + i, r);

			out[0] = in[0] >> 2;
			out[1] = ((in[0] & 0x3) << 4) + (in[1] >> 4);
			out[2] = ((in[1] & 0xF) << 2) + (in[2] >> 6);
			out[3] = in[2] & 0x3F;

			for(uint32 j = 0; j < r + 1; ++j)
				result.push_back(b64(out[j]));

			for(uint32 j = r; j < 3; ++j)
				result.push_back('=');
		}

		return result;
	}
};
