/*
 * metronome.h
 *
 *  Created on: 20/06/2013
 *      Author: N9334122
 */

#ifndef METRONOME_H_
#define METRONOME_H_

#define PERIOD_SEREIS_PAUSE		2000

#define PERIOD_STD_PISTOL_10SEC 1666
#define PERIOD_STD_PISTOL_20SEC 3333
#define PERIOD_RAPID_FIRE_4SEC 666
#define PERIOD_RAPID_FIRE_6SEC 1000
#define PERIOD_RAPID_FIRE_8SEC 1333

#define TXT_STD_PISTOL_10_SEC "Standard Pistol: 10 Sec"
#define TXT_STD_PISTOL_20_SEC "Standard Pistol: 20 Sec"
#define TXT_RAPID_FIRE_8_SEC  "Rapid Fire: 8 Sec"
#define TXT_RAPID_FIRE_6_SEC  "Rapid Fire: 6 Sec"
#define TXT_RAPID_FIRE_4_SEC  "Rapid Fire: 4 Sec"

#define beats	6

using namespace MAUtil;

void StartMetronome();
void StopMetronome();
void PlaySound();

int isMetronomeRunning();
void SetPeriod(String);



#endif /* METRONOME_H_ */
