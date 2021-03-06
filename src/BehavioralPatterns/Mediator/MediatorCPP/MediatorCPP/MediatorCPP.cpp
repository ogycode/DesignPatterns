#include "stdafx.h"

using namespace std;

class IColleague;

//Интерфейс медиатора
class IMediator
{
public:
	virtual void Send(string const& msg, IColleague * coll) const = 0;
};

//Интерфейс обькта между которыми будет происходить общение
class IColleague
{
protected:
	IMediator * med;

public:
	IColleague(IMediator* mediator) : med(mediator) {}
};

//Конкретный обект общения
class ColleagueJack : public virtual IColleague
{
public:
	ColleagueJack(IMediator * med) : IColleague(med) {}

	void Send(string const& msg) { med->Send(msg, this); }
	void Notify(string const& msg) { cout << "Jack gets message: '" << msg << "'" << endl; }
};

//Конкретный обект общения
class ColleagueJhon : public virtual IColleague
{
public:
	ColleagueJhon(IMediator * med) : IColleague(med) {}

	void Send(string const& msg) { med->Send(msg, this); }
	void Notify(string const& msg) { cout << "Jhon gets message: '" << msg << "'" << endl; }
};

//Реализация конкретного посредника в общении между двумя обьектами
class MediatorJackJhon : public virtual IMediator
{
protected:
	ColleagueJack * jack;
	ColleagueJhon * jhon;

public:
	void SetJack(ColleagueJack * j) { jack = j; }
	void SetJhon(ColleagueJhon * j) { jhon = j; }

	virtual void Send(string const& msg, IColleague *coll) const override
	{
		if (coll == jack)
			jhon->Notify(msg);
		else if (coll == jhon)
			jack->Notify(msg);
	}
};

int main()
{
	system("color 70");
	setlocale(0, "");
	SetConsoleTitle(TEXT("Mediator"));

	MediatorJackJhon mjj;

	ColleagueJack jack(&mjj);
	ColleagueJhon jhon(&mjj);

	mjj.SetJack(&jack);
	mjj.SetJhon(&jhon);

	jack.Send("Hello, what's up?");
	jhon.Send("Hi, im fine, and you?");

	system("pause");
	return 0;
}

