#include "stdafx.h"

using namespace std;

//Интерфейс для будущего составного обьекта
class IText
{
public:
	typedef shared_ptr<IText> sPtr;

	virtual void Draw() = 0;
	virtual void Add(const sPtr&) { throw runtime_error("IText can not be added to a leaf"); }
};

//Составной объект с потомками
class CompositeText : virtual public IText
{
private:
	list<sPtr> children;

public:
	virtual void Draw() override
	{
		for (sPtr& sptr : children)
			sptr->Draw();
	}
	virtual void Add(const sPtr& sptr) override
	{
		children.push_back(sptr);
	}
	void Remove(const sPtr& sptr)
	{
		children.remove(sptr);
	}
	void Replace(const sPtr& oldValue, const sPtr& newValue)
	{
		replace(children.begin(), children.end(), oldValue, newValue);
	}

};

//Составной обьект без потомков
class Letter : public virtual IText
{
private:
	char symbol;

public:
	Letter(char c) : symbol(c) {}

	virtual void Draw() override
	{
		cout << symbol;
	}
};

int main()
{
	system("color 70");
	setlocale(0, "");
	SetConsoleTitle(TEXT("Composite"));

	IText::sPtr symSpace(new Letter(' '));
	IText::sPtr symH(new Letter('H'));
	IText::sPtr symE(new Letter('E'));
	IText::sPtr symL(new Letter('L'));
	IText::sPtr symO(new Letter('O'));
	IText::sPtr symW(new Letter('W'));
	IText::sPtr symR(new Letter('R'));
	IText::sPtr symD(new Letter('D'));
	IText::sPtr symI(new Letter('I'));
	IText::sPtr symComma(new Letter(','));
	IText::sPtr symExcl(new Letter('!'));
	IText::sPtr symNewLine(new Letter('\n'));

	//symSpace->Add(nullptr);   exception, couse -> line 12

	IText::sPtr wordHello(new CompositeText);
	wordHello->Add(symH);
	wordHello->Add(symE);
	wordHello->Add(symL);
	wordHello->Add(symL);
	wordHello->Add(symO);

	IText::sPtr wordWorld(new CompositeText);
	wordWorld->Add(symW);
	wordWorld->Add(symO);
	wordWorld->Add(symR);
	wordWorld->Add(symL);
	wordWorld->Add(symD);

	IText::sPtr wordHi(new CompositeText);
	wordHi->Add(symH);
	wordHi->Add(symI);

	CompositeText text;

	text.Add(wordHello);
	text.Add(symComma);
	text.Add(symSpace);
	text.Add(wordWorld);
	text.Add(symExcl);
	text.Add(symNewLine);

	text.Draw();

	text.Replace(wordHello, wordHi);

	text.Draw();

	text.Remove(wordWorld);
	text.Remove(symComma);
	text.Remove(symSpace);

	text.Draw();

	system("pause");
    return 0;
}

