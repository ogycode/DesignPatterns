#include "stdafx.h"

using namespace std;

//Обьект котрый будет обрабатыватся
class CriminalAction
{
public:
	string Description;
	int Complexity;

	CriminalAction(string d, int c) : Description(d), Complexity(c) {}
};

//Обработчик
class Cop
{
private:
	Cop * Successor = nullptr;

public:
	string Name;
	int Deduction;

	Cop(string n, int d) : Name(n), Deduction(d) {}

	void SetSuccessor(Cop* c)
	{
		Successor = c;
	}
	void HandleRequest(CriminalAction * ca)
	{
		if (ca->Complexity <= Deduction)
			cout << "Take the action '"<< ca->Description <<"' is officer " << Name << endl;
		else if (Successor != nullptr)
			Successor->HandleRequest(ca);
		else
			cout << "This action can not take any officer!" << endl;
	}
};

int main()
{
	system("color 70");
	setlocale(0, "");
	SetConsoleTitle(TEXT("Chain of responsibility"));

	Cop* Antony = new Cop("Antony", 4);
	Cop* Tony = new Cop("Tony", 6);
	Cop* Sahra = new Cop("Sahra", 12);

	Antony->SetSuccessor(Tony);
	Tony->SetSuccessor(Sahra);

	list<CriminalAction *> cas;

	cas.push_back(new CriminalAction("Steal food", 1));
	cas.push_back(new CriminalAction("Steal money", 2));
	cas.push_back(new CriminalAction("Steal pet", 3));
	cas.push_back(new CriminalAction("Hit girlfriend", 4));
	cas.push_back(new CriminalAction("Hit some peoples", 5));
	cas.push_back(new CriminalAction("Kill some pets", 6));
	cas.push_back(new CriminalAction("Kill some human", 7));
	cas.push_back(new CriminalAction("Terrorism", 100));

	for (auto * c : cas)
	{
		Antony->HandleRequest(c);
		delete c;
	}

	delete Antony;
	delete Tony;
	delete Sahra;

	system("pause");
	return 0;
}

