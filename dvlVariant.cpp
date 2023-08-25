#include "master.h"
#include "dvlVariant.h"

//***********************************************
dvlVariant::dvlVariant(const BYTE* binBuffer, int size)
{
	DataType = VariantType::Binary;
	Data = BytesToHex(binBuffer, size);
}
//***********************************************
BYTE* dvlVariant::ToBinary(int& size) const
{
	size = 0;
	if (DataType == VariantType::Binary)
	{
		auto hex = ToString();
		return HexToBytes(hex.c_str(), size);
	}
	else
	{
		assert(false);
	}
	return nullptr;
}

static const wchar_t * _hexSymbols = L"0123456789ABCDEF";
//***********************************************
/*static*/ std::wstring dvlVariant::ByteToHex(unsigned char c)
{
	std::wstring hex;
	auto h = c / 16;
	auto l = c % 16;
	hex.push_back(_hexSymbols[h]);
	hex.push_back(_hexSymbols[l]);
	return hex;
}
//***********************************************
/*static*/ std::wstring dvlVariant::BytesToHex(const BYTE* buffer, int length)
{
	std::wstring hex;
	hex.reserve(length * 2 + 2);
	for (int i = 0; i < length; i++)
	{
		auto c = buffer[i];
		hex.append(dvlVariant::ByteToHex(c));
	}
	return hex;
}
//****************************************************************************
static int hexToIndex(wchar_t c)
{
	if (c >= L'A' && c <= L'F')
	{
		return c - L'A' + 10;
	}
	else if (c >= L'a' && c <= L'f')
	{
		return c - L'a' + 10;
	}
	else if (c >= L'0' && c <= L'9')
	{
		return c - L'0';
	}
	else
	{
		assert(false);
		// throw exception
		return 0;
	}
}
//***********************************************
/*static*/ BYTE* dvlVariant::HexToBytes(const wchar_t* hex, int& bufSize)
{
	BYTE* buffer = nullptr;
	if (auto hexLength = hex != nullptr ? wcslen(hex) : 0; hexLength > 0)
	{
		assert(hexLength % 2 == 0);
		bufSize = (int)hexLength / 2;
		buffer = new BYTE[bufSize];
		for (int i = 0; i < bufSize; i++)
		{
			auto hexCharh = hexToIndex(hex[i * 2]);
			auto hexCharl = hexToIndex(hex[i * 2 + 1]);
			if (hexCharh < 0 || hexCharh >= 16 || hexCharl < 0 || hexCharl >= 16)
			{
				assert(false);
			}
			buffer[i] = (unsigned char)(hexCharh * 16 + hexCharl);
		}
	}
	return buffer;
}
