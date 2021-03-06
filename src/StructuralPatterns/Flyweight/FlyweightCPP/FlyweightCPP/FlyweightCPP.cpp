#include "stdafx.h"

using namespace std;

//Интерфейс приспособленца
class IChar
{
public:
	virtual ~IChar() {};
	virtual void Draw() = 0;

protected:
	char symbol;
	int symbolSize;
};

//Конкретный приспособленец
class Char : public virtual IChar
{
public:
	Char(char s, int z)
	{
		symbol = s;
		symbolSize = z;
	}

	virtual void Draw() override
	{
		cout << symbol << " as " << symbolSize << " points" << endl;
	}
};

//Фабрика приспособленцев
template<int CharSize = 10>
class Factory
{
private:
	typedef map<char, IChar*> Characters;
	Characters chars;

public:
	virtual ~Factory()
	{
		for (Characters::const_iterator it = chars.begin(); it != chars.end(); ++it)
			delete it->second;
	}

	//Возвращаем или создаем конкретного приспособленца
	IChar& GetChar(char key)
	{
		Characters::const_iterator it = chars.find(key);

		if (chars.end() == it)
		{
			IChar* c = new Char(key, CharSize);
			chars[key] = c;
			return *c;
		}
		else
			return *it->second;
	}
};

int main()
{
	system("color 70");
	setlocale(0, "");
	SetConsoleTitle(TEXT("Flyweight"));

	string text = "DDasfFGaaD";

	Factory<24> f;

	for (string::const_iterator it = text.begin(); it != text.end(); ++it)
	{
		IChar& ca = f.GetChar(*it);
		ca.Draw();
	}

	cout << "\n\n\n" << endl;

	Factory<48> f2;

	for (string::const_iterator it = text.begin(); it != text.end(); ++it)
	{
		IChar& ca = f2.GetChar(*it);
		ca.Draw();
	}


	system("pause");
    return 0;
}

