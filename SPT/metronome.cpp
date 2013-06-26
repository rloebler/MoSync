#include <MAUtil/Environment.h>
#include <MAUtil/Moblet.h>
#include "MAHeaders.h"
#include <MAUtil/String.h>
#include "metronome.h"
#include "main.h"
#include "mainscreen.h"


using namespace MAUtil;

int isRunning = false;
int tmrPeriod;
static int beatCounter = 0;


class ShotTimer : public MAUtil::TimerListener {
public:
	void runTimerEvent()
	{
		PlaySound();
	}
};

class SeriesPauseTimer : public MAUtil::TimerListener {
public:
	void runTimerEvent()
	{
		if(isMetronomeRunning())
			StartMetronome();
	}
};

ShotTimer shotTimer;
SeriesPauseTimer seriesPauseTimer;


void StartSeriesPauseTimer() {
	MAUtil::Environment::getEnvironment().addTimer(&seriesPauseTimer,PERIOD_SEREIS_PAUSE, 1);
}

void StopSeriesPauseTimer() {
	MAUtil::Environment::getEnvironment().removeTimer(&seriesPauseTimer);
}

void PlaySound()  {
	MainScreen* mAppScreen = GetScreenHandle();
	mAppScreen->SetGreenLight(ON);
	mAppScreen->SetRedLight(OFF);

	// Play different sound on first beat
	if(beatCounter==0) {
		mAppScreen->ClearBulletHoles();
		maSoundPlay(R_WATERDROP,0,maGetDataSize(R_PING));
	}
	else  {
		mAppScreen->AddBulletHoles(beatCounter-1);
		maSoundPlay(R_PING,0,maGetDataSize(R_PING));
	}

	//typically there are 6 beats. One to start + 1 for each of 5 shots
	beatCounter++;
	beatCounter = beatCounter % beats;

	if(beatCounter==0)  {
		StopMetronome();
		StartSeriesPauseTimer();
	}

	isRunning = true;
}


void StartMetronome() {
	    StopSeriesPauseTimer();
		MAUtil::Environment::getEnvironment().addTimer(&shotTimer,tmrPeriod, 0);
		beatCounter = 0;		// Reset so we can start with the special first beat sound
		PlaySound();
}

void StopMetronome() {
	MAUtil::Environment::getEnvironment().removeTimer(&shotTimer);
	isRunning = false;

	MainScreen* mAppScreen = GetScreenHandle();
	mAppScreen->SetGreenLight(OFF);
	mAppScreen->SetRedLight(ON);
}

int isMetronomeRunning()  {
	return isRunning;
}

void SetPeriod(String match) {

	if(match == TXT_STD_PISTOL_10_SEC)
		tmrPeriod = (PERIOD_STD_PISTOL_10SEC);
	else if(match == TXT_STD_PISTOL_20_SEC)
		tmrPeriod = (PERIOD_STD_PISTOL_20SEC);
	else if(match == TXT_RAPID_FIRE_4_SEC)
		tmrPeriod = (PERIOD_RAPID_FIRE_4SEC);
	else if(match == TXT_RAPID_FIRE_6_SEC)
		tmrPeriod = (PERIOD_RAPID_FIRE_6SEC);
	else if(match == TXT_RAPID_FIRE_8_SEC)
		tmrPeriod = (PERIOD_RAPID_FIRE_8SEC);

	if(isMetronomeRunning())
		StartMetronome();

}
