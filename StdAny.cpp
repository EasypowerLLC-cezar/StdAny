// StdAny.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "master.h"

class BaseAbstract
{
public:
	virtual std::string GetName() const = 0;
	virtual int GetAge() const = 0;

	int GetYOB()
	{
		return 2023 - GetAge();
	}

	int GetNameLength()
	{
		return (int)GetName().length();
	}
};

class BaseImplentorForCezar
{
public:
	std::wstring GetName() const
	{
		return L"Cezar";
	}
	int GetAge() const
	{
		return 65;
	}
};


dvlVariant getSomeDouble()
{
	return dvlVariant(123.7);
}

struct person
{
	std::wstring Name;
	int Age;

	person(const wchar_t * name, int age)
	{
		Name = name;
		Age = age;
	}
};

struct Alert
{
	int Number = 0;
	std::wstring Name;
	int Level = 0;

	Alert(int number, const wchar_t* name, int level)
	{
		Number = number;
		Name = name;
		Level = level;
	}
};

int main()
{
	std::vector<Alert> alerts;
	alerts.push_back(Alert(3, L"Mama", 1));
	alerts.push_back(Alert(4, L"Zuzu", 2));
	alerts.push_back(Alert(5, L"Gaga", 3));

	for (auto alert : alerts)
	{
		alert.Level += 100;
	}
	for (auto& alert : alerts)
	{
		alert.Level += 1000;
	}

	std::vector<float> vsrc = { 1.4f, 0.f, 43.7882f };
	std::vector<float> vtgt = vsrc;
	vsrc[0] = 2.8f;
	vtgt[1] = 56;

	vsrc.insert(vsrc.begin() + 2, 45.8f);
	vsrc.erase(vsrc.begin() + 1);

	std::vector<person> people = { person(L"cezar", 65), person(L"Zuzula", 45), person(L"kasia", 38)};
	people.insert(people.begin() + 1, person(L"Gosia", 64));
	people.erase(people.begin() + 2);
	people.at(2).Age = 39;

	std::unordered_set<int> numberSet = { 5, 34, 0, -3, 5, 35, 5 };
	auto copySet = numberSet;
	numberSet.insert(5);
	numberSet.erase(0);
	numberSet.erase(0);
	numberSet.erase(5);
	numberSet.erase(459);

	numberSet.insert(32);
	numberSet.insert(5);
	numberSet.insert(32);

	numberSet.erase(-3);

	// test hex to bin
	auto hex0 = L"10006FA1056BBC7600001643DAF2";
	auto len0 = wcslen(hex0);
	
	int len1 = 0;
	auto bin1 = dvlVariant::HexToBytes(hex0, len1);
	assert(len1 == len0 / 2);

	auto hex2 = dvlVariant::BytesToHex(bin1, len1);
	assert(wcscmp(hex2.c_str(), hex0) == 0);

	int len3 = 0;
	auto bin3 = dvlVariant::HexToBytes(hex2.c_str(), len3);
	assert(len3 == len0 / 2);

	auto hex4 = dvlVariant::BytesToHex(bin3, len3);
	assert(wcscmp(hex4.c_str(), hex0) == 0);

	delete[] bin1;
	delete[] bin3;

	// test std::wstring
	auto sz = new wchar_t[24];
	wcscpy_s(sz, 24, L"Mama ma kota");
	std::wstring mmk = sz;
	delete[] sz;
	assert(wcscmp(mmk.c_str(), L"Mama ma kota") == 0);


	std::vector<dvlVariant> myvar;
	myvar.push_back(dvlVariant(45));
	myvar.push_back(2.4f);
	myvar.push_back(L"Mama");
	myvar.push_back(906);
	myvar.push_back(getSomeDouble());

	dvlVariant x;
	std::wcout << x.DataType << L"\n";

	x = 4.6;
	std::wcout << x.DataType << L"\n";

	x = L"Zzuzu";
	std::wcout << x.DataType << L"\n";
	auto x1 = x.ToString();

	x = 5;
	auto bx = x.ToBool();
	auto fx = x.ToFloat();
	auto dx = x.ToDouble();
	auto ix = x.ToInt();
	auto lx = x.ToLong();

	x = 12.8;
	bx = x.ToBool();
	fx = x.ToFloat();
	dx = x.ToDouble();
	ix = x.ToInt();
	lx = x.ToLong();

	x = 0.f;
	bx = x.ToBool();
	fx = x.ToFloat();
	dx = x.ToDouble();
	ix = x.ToInt();
	lx = x.ToLong();

	x = true;
	bx = x.ToBool();
	fx = x.ToFloat();
	dx = x.ToDouble();
	ix = x.ToInt();
	lx = x.ToLong();

	x = false;
	bx = x.ToBool();
	fx = x.ToFloat();
	dx = x.ToDouble();
	ix = x.ToInt();
	lx = x.ToLong();

	x = INIT_FLOAT_TO_BLANK;
	bx = x.ToBool();
	fx = x.ToFloat();
	dx = x.ToDouble();
	ix = x.ToInt();
	lx = x.ToLong();

	int binSize = 0;
	BYTE buff0[] = {(BYTE)76, BYTE(0), BYTE(23), BYTE(0)};
	x = dvlVariant(buff0, 4);
	auto buff1 = x.ToBinary(binSize);
	assert(binSize == 4);
	for (int i = 0; i < binSize; i++)
	{
		assert(buff1[i] == buff0[i]);
	}
	auto bufHex = x.ToString();
	int size2 = 0;
	auto buff2 = dvlVariant::HexToBytes(bufHex.c_str(), size2);
	assert(size2 == 4);
	for (int i = 0; i < size2; i++)
	{
		assert(buff2[i] == buff0[i]);
	}

	delete[] buff1;
	delete[] buff2;

    std::wcout << L"myVar = " << myvar.size() << L"\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
