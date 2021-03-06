#include "stdafx.h"

using namespace std;

//Интерфейс состояния
class IState
{
public:
	virtual void Handle() = 0;
};

//Конкретное состояние
class PlayState : public virtual IState
{
public:
	virtual void Handle() override { cout << "Playing in the game!\n"; }
};

//Конкретное состояние
class PauseState : public virtual IState
{
public:
	virtual void Handle() override { cout << "Pause in the game!\n"; }
};

//Объект игры, виджет
class GameWidget
{
	IState * state;

public:
	GameWidget() {}

	void SetState(IState * s) { state = s; }
	void Action() { state->Handle(); }
};

int main()
{
	system("color 70");
	setlocale(0, "");
	SetConsoleTitle(TEXT("State"));

	PlayState ps;
	PauseState ss;

	GameWidget gw;

	gw.SetState(&ps);

	gw.Action();

	gw.SetState(&ss);

	gw.Action();

	system("pause");
    return 0;
}

