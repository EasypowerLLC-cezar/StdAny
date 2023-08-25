#pragma once

#define INIT_FLOAT_TO_BLANK				(3.123456789e+38F)
#define INIT_DOUBLE_TO_BLANK			(double(INIT_FLOAT_TO_BLANK))
#ifndef BYTE
#define BYTE unsigned char
#endif

#pragma once

#include <variant>

/////////////////////////////////////////////////////////////
//
// Renamed:
// CDatArray -> CDvlVariantArray
// CDvlRecordSet -> COleVariantTable
//

struct dvlVariant
{
public:

	enum VariantType { Long = 0, Double = 1, String = 2, Binary = 3, Boolean = 4, Null = -1 };

	VariantType		DataType = VariantType::Null;
	std::variant<long, double, std::wstring, bool>		Data;

	bool IsNull() const
	{
		return DataType == VariantType::Null;
	}
	void Clear()
	{
		DataType = VariantType::Null;
		Data.emplace<bool>(false);
	}
	dvlVariant()
	{
		DataType = VariantType::Null;
	}
	dvlVariant(float f, bool makeBlankNull = true)
	{
		if (makeBlankNull && (f == INIT_FLOAT_TO_BLANK))
		{
			DataType = VariantType::Null;
		}
		else
		{
			DataType = VariantType::Double;
			Data = (double)f;
		}
	}
	dvlVariant(double f, bool makeBlankNull = true)
	{
		if (makeBlankNull && (f == INIT_DOUBLE_TO_BLANK))
		{
			DataType = VariantType::Null;
		}
		else
		{
			DataType = VariantType::Double;
			Data = f;
		}
	}
	dvlVariant(const wchar_t* f, VariantType vType = VariantType::String)
	{
		// vType can be only VariantType::String or VariantType::Binary
		DataType = vType;
		Data = std::wstring(f);
	}
	dvlVariant(const std::wstring& f, VariantType vType = VariantType::String)
	{
		// vType can be only VariantType::String or VariantType::Binary
		DataType = vType;
		Data = f;
	}
	dvlVariant(int f)
	{
		DataType = VariantType::Long;
		Data = (long)f;
	}
	dvlVariant(long f)
	{
		DataType = VariantType::Long;
		Data = f;
	}
	dvlVariant(unsigned char f)
	{
		DataType = VariantType::Long;
		Data = (long)f;
	}
	dvlVariant(bool f)
	{
		DataType = VariantType::Boolean;
		Data = f;
	}
	dvlVariant(const BYTE* binBuffer, int size);

	long		ToLong(long blankValue = 0) const
	{
		switch (DataType)
		{
		case VariantType::Double:	return (long)(std::get<double>(Data));
		case VariantType::Long:		return (long)(std::get<long>(Data));
		case VariantType::Boolean:	return (long)(std::get<bool>(Data) ? 1 : 0);
		default:					return blankValue;
		}
	}
	unsigned char		ToByte(unsigned char blankValue = 0) const
	{
		switch (DataType)
		{
		case VariantType::Double:	return (unsigned char)(std::get<double>(Data));
		case VariantType::Long:		return (unsigned char)(std::get<long>(Data));
		case VariantType::Boolean:	return (unsigned char)(std::get<bool>(Data) ? 1 : 0);
		default:					return blankValue;
		}
	}
	float		ToFloat(float blankValue = INIT_FLOAT_TO_BLANK) const
	{
		switch (DataType)
		{
		case VariantType::Null:		return INIT_FLOAT_TO_BLANK;
		case VariantType::Double:	return (float)(std::get<double>(Data));
		case VariantType::Long:		return (float)(std::get<long>(Data));
		default:					return blankValue;
		}
	}
	double		ToDouble(double blankValue = INIT_DOUBLE_TO_BLANK) const
	{
		switch (DataType)
		{
		case VariantType::Null:		return INIT_DOUBLE_TO_BLANK;
		case VariantType::Double:	return (double)(std::get<double>(Data));
		case VariantType::Long:		return (double)(std::get<long>(Data));
		default:					return blankValue;
		}
	}
	std::wstring		ToString(const wchar_t* blankValue = L"") const
	{
		if (DataType == VariantType::String || DataType == VariantType::Binary)
		{
			return std::get<std::wstring>(Data);
		}
		else
		{
			return blankValue;
		}
	}

	int			ToInt(int blankValue = 0) const
	{
		return (int)ToLong((long)blankValue);
	}
	bool		ToBool(bool blankValue = false) const
	{
		switch (DataType)
		{
		case VariantType::Double:	return std::get<double>(Data) != 0.0;
		case VariantType::Long:		return std::get<long>(Data) != 0;
		case VariantType::Boolean:	return std::get<bool>(Data);
		default:					return blankValue;
		}
	}
	BYTE* ToBinary(int& size) const;

	static std::wstring ByteToHex(unsigned char c);
	static std::wstring BytesToHex(const BYTE* buffer, int length);
	static BYTE* HexToBytes(const wchar_t* hex, int& size);
};


class CDvlVariantArray : public std::vector<dvlVariant>
{
public:

	CDvlVariantArray()
	{
	}
	CDvlVariantArray(dvlVariant v1)
	{
		this->push_back(v1);
	}
	CDvlVariantArray(dvlVariant v1, dvlVariant v2)
	{
		this->push_back(v1);
		this->push_back(v2);
	}
	CDvlVariantArray(dvlVariant v1, dvlVariant v2, dvlVariant v3)
	{
		this->push_back(v1);
		this->push_back(v2);
		this->push_back(v3);
	}
	CDvlVariantArray(dvlVariant v1, dvlVariant v2, dvlVariant v3, dvlVariant v4)
	{
		this->push_back(v1);
		this->push_back(v2);
		this->push_back(v3);
		this->push_back(v4);
	}
	CDvlVariantArray(dvlVariant v1, dvlVariant v2, dvlVariant v3, dvlVariant v4, dvlVariant v5)
	{
		this->push_back(v1);
		this->push_back(v2);
		this->push_back(v3);
		this->push_back(v4);
		this->push_back(v5);
	}
	CDvlVariantArray(dvlVariant v1, dvlVariant v2, dvlVariant v3, dvlVariant v4, dvlVariant v5, dvlVariant v6)
	{
		this->push_back(v1);
		this->push_back(v2);
		this->push_back(v3);
		this->push_back(v4);
		this->push_back(v5);
		this->push_back(v6);
	}
	CDvlVariantArray(dvlVariant v1, dvlVariant v2, dvlVariant v3, dvlVariant v4, dvlVariant v5, dvlVariant v6, dvlVariant v7)
	{
		this->push_back(v1);
		this->push_back(v2);
		this->push_back(v3);
		this->push_back(v4);
		this->push_back(v5);
		this->push_back(v6);
		this->push_back(v7);
	}
	CDvlVariantArray(dvlVariant v1, dvlVariant v2, dvlVariant v3, dvlVariant v4, dvlVariant v5, dvlVariant v6, dvlVariant v7, dvlVariant v8)
	{
		this->push_back(v1);
		this->push_back(v2);
		this->push_back(v3);
		this->push_back(v4);
		this->push_back(v5);
		this->push_back(v6);
		this->push_back(v7);
		this->push_back(v8);
	}
	virtual ~CDvlVariantArray()
	{
	}
	inline void Clear()
	{
		this->clear();
	}
	CDvlVariantArray	CopyFrom(const CDvlVariantArray& other)
	{
		this->Clear();
		for (auto v : other)
		{
			this->push_back(v);
		}
		return *this;
	}
	CDvlVariantArray* CopyFrom(const CDvlVariantArray* other)
	{
		CopyFrom(*other);
		return this;
	}
};

