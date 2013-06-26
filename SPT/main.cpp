/*
Copyright (C) 2011 MoSync AB

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License,
version 2, as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
MA 02110-1301, USA.
*/

/**
 * @file hellomaui.cpp
 * @author Chris Hughes
 *
 * This application provides a very basic example of how to work
 * with MAUI to position and and manipulate graphical user interface
 * elements. The code is very well commented so that you can see
 * what's happening at each step. The application uses one screen
 * and a some widgets to provide a password entry box and some
 * control buttons. For more advanced use of MAUI, see our MAUIEx
 * example application.
 *
 * NOTE: "MA" is short for MoSync API. "MAUI" stands for the MoSync
 * user interface API. This is a completely cross platform API that
 * works on a wide range of devices. There is also a native widget
 * API, also cross platform, but targeted for high-end devices,
 * currently Android and iPhone.
 *
 * This example application has the same functionality as our example
 * application "HelloNativeUI". Compare the two examples to see how we
 * do similar things in MAUI and in Native UI.
 */

// Include the header files for MoSync Moblets and MAUI widgets
// so that we can use them in our code.
#include <MAUtil/Moblet.h>
#include <MAUI/Screen.h>
#include <MAUI/Label.h>
#include <MAUI/Layout.h>
#include <MAUI/EditBox.h>
#include <MAUI/Font.h>
#include "Main.h"
#include "Metronome.h"
#include <conprint.h>

MainScreen* screenHandle;

void saveScreenHandle(MainScreen* screen)  {
	screenHandle = screen;
}

MainScreen* GetScreenHandle() {
	return screenHandle;
}

/**
 * A Moblet is the main object of MoSync application. In the Moblet
 * we manage the application and handle events. Our Moblet inherits
 * the Moblet base class in the MAUtil library.
 */
class SPTMoblet : public MAUtil::Moblet
{
public:
	/**
	 * The user interface is created in the constructor method.
	 * (Note that constructors and destructors have the same
	 * name as the class.)
	 */

	SPTMoblet()
	{

		// Create the main (and only) screen used in the application.
		mAppScreen = new MainScreen();
		saveScreenHandle(mAppScreen);

		// Display the screen.
		mAppScreen->show();


	}

	/**
	 * The destructor deletes the screen object.
	 */
	virtual ~SPTMoblet()
	{
		delete mAppScreen;
	}

	void SetMainScreen(MainScreen* screen)  {
		mAppScreen = screen;
	}

private:
	/**
	 * The screen of our application.
	 */

	MainScreen* mAppScreen;
};

// Here is the real start of our program.
extern "C" int MAMain()
{
	// Create and run the Moblet to start the application.


	//MainScreen* mAppScreen = new MainScreen();
	//mAppScreen->show();
	//SPTMoblet* myMoblet = new SPTMoblet();
	//myMoblet->SetMainScreen(mAppScreen);
	MAUtil::Moblet::run(new SPTMoblet());


	// The Moblet will run until it is closed by the user.
	// When it is closed we end our program in a well-behaved
	// way, returning zero.
	return 0;
}
