/*
 * MainScreen.h
 *
 *  Created on: 22/06/2013
 *      Author: N9334122
 */

#ifndef MAINSCREEN_H_
#define MAINSCREEN_H_

#include <MAUI/Screen.h>
#include <MAUI/Label.h>
#include <MAUI/Layout.h>
#include <MAUI/EditBox.h>
#include <MAUI/Font.h>
#include <MAUI/image.h>
#include <MAUI/ListBox.h>
#include <MAP/DateTime.h>
#include <MAStdlib.h>
#include "MainScreen.h"
#include "MAHeaders.h"
#include "Metronome.h"
#include <conprint.h>


#define DEFAULT_HEIGHT  1230		// All images positions are based on an screen of this size
#define DEFAULT_WIDTH   720

using namespace MAUI;


enum LIGHTSTATE { ON,OFF };

/**
 * This class defines the screen of our application. We inherit
 * the Screen base class in the MAUI library. We'll only be
 * using one screen instance in this application, but you could
 * have multiple instances in your application, perhaps inheriting
 * their characteristics from other screen classes in a structured
 * hierarchy.
 *
 * We also implement the TextBoxListener interface to be able to
 * process events sent from the maTextBox syscall. This syscall
 * displays a virtual keyboard and an input text field, and is
 * very useful on devices that don't have a physical keypad.
 */
class MainScreen :
	public MAUI::Screen
{
public:

		/**
		 * In the constructor, we create the user interface.
		 */
		MainScreen()
		{
			// Create user interface widgets.
			createUI();

		}

		/**
		 * In the destructor, we destroy the widgets to release memory.
		 * Destroying a widget automatically destroys all child widgets.
		 */
		 virtual ~MainScreen()
		{
			delete mBackgroundImage;
		}




			/**
			 * Here we create the user interface widgets.
			 */
			void createUI()
			{


				// Get the height of the display. We use this
				// to size our font.
				displayHeight = EXTENT_Y(maGetScrSize());

				yScale = (float)((float)displayHeight / (float)DEFAULT_HEIGHT);
				printf("Y:%d-%f",displayHeight,yScale);

				// Get the width of the display. We use this
				// to size our widgets.
				displayWidth = EXTENT_X(maGetScrSize());
				xScale = (float)((float)displayWidth / (float)DEFAULT_WIDTH);
				printf("X:%d-%f",displayWidth,xScale);

				// Create a font object. The font resource and other
				// resources are defined in the file "resources.lst".
				MAUI::Font* font;
				if (600 < displayHeight) {
					font = new MAUI::Font(RES_FONT_BIG);
				} else {
					font = new MAUI::Font(RES_FONT);
				}


				MAHandle backgroundImage;
				if(displayHeight >= 1200 && displayWidth >= 720)
					backgroundImage = R_BACKGROUND_720x1280;
				else if(displayHeight >= 480 && displayWidth >= 320)
					backgroundImage = R_BACKGROUND_320x480;
				else
					backgroundImage = R_BACKGROUND_320x480;

				mBackgroundImage = new MAUI::Image(
						0,
						0,
						0,
						0,
						NULL,
						true,
						true,
						backgroundImage);

				// Add the layout as the root of the screen's widget tree.
				setMain(mBackgroundImage);


				mGreenLight = new MAUI::Image(
						(int)(337*xScale),
						(int)(32*yScale),
						0,
						0,
						mBackgroundImage,
						true,
						true,
						R_LIGHT_OFF);

				mRedLight = new MAUI::Image(
						(int)(337*xScale),
						(int)(472*yScale),
						0,
						0,
						mBackgroundImage,
						true,
						true,
						R_LIGHT_OFF);



				// The third widget is the Clear button. We use a label
				// for as a button widget.
				mStopButton = new MAUI::Image(
					(int)(70*xScale), // Left.
					(int)(950*yScale), // Top (will be set by the layout).
					0, // Width.
					0, // Height.
					mBackgroundImage, // Parent widget.
					true, // Button text.
					true,     // Background color (we will use the skin).
					R_BUTTON_STOP); // Font.



				// The fourth widget is the Submit button.
				mStartButton = new MAUI::Image(
					(int)(70*xScale), // Left.
					(int)(850*yScale), // Top (will be set by the layout).
					0, // Width.
					0, // Height.
					mBackgroundImage, // Parent widget.
					true, // Button text.
					true,     // Background color (we will use the skin).
					R_BUTTON_START); // Font.


				mTrainingButton = new MAUI::Image(
					(int)(400*xScale), // Left.
					(int)(850*yScale), // Top (will be set by the layout).
					0, // Width.
					0, // Height.
					mBackgroundImage, // Parent widget.
					true, // Button text.
					true,     // Background color (we will use the skin).
					R_BUTTON_TRAINING_ON); // Font.




				// Now the user interface widgets are created.
			}


		    // We need to define two methods to make the buttons work
			// with touch events. To do this we overload (i.e. create
			// our own implementation of) the pointer event methods
			// in the Screen base class.

			/**
			 * This method is called on touch down events. Here we provide
			 * visual feedback that show the buttons in selected state.
			 */
			void pointerPressEvent(MAPoint2d point)
			{

				// If the Clear button is clicked...
				if (mStopButton->contains(point.x, point.y))
				{
					// ...set the button's state to "selected". This
					// automatically changes the button's skin.
					mStopButton->setSelected(true);
				}
				else
				if (mStartButton->contains(point.x, point.y))
				{
					// Do the same for the Submit button.
					mStartButton->setSelected(true);
				}


			}

			/**
			 * This method is called on touch up events. Here we restore
			 * the buttons to the unselected state, and perform button actions.
			 */
			void pointerReleaseEvent(MAPoint2d point)
			{
				// Deselect the buttons so that the "unselected" skins
				// are redisplayed, and also reselect the edit box.
				mStopButton->setSelected(false);
				mStartButton->setSelected(false);

				// If the pointer is inside the Clear button we call the
				// action method for the button.
				if (mStopButton->contains(point.x, point.y))
				{
					stopButtonAction();
				}

				// If the pointer is inside the Submit button we call the
				// action method for the button.
				if (mStartButton->contains(point.x, point.y))
				{
					startButtonAction();
				}

}

			/**
			 * This method is called when a key is pressed.
			 */
			void keyPressEvent(int keyCode, int nativeCode)
			{
				switch (keyCode)
				{
					// Close the application if the back key, key 0,
					// or the left "softkey" is pressed (the left
					// softkey is usually located at the top left of
					// the keypad of phones that have a keypad, and
					// is often used as a back navigation key).
					case MAK_BACK:
					case MAK_0:
					case MAK_SOFTLEFT:
						// Exit the application.
						maExit(0);
						break;
					case MAK_UP:

						break;
					case MAK_DOWN:
						break;
					case MAK_FIRE:
						// When the "fire" (centre) key on the keypad
						// is pressed, we run the action associated
						// with the selected widget.
						runWidgetAction();
						break;
				}
			}


			/**
			 * Execute the action of the selected widget.
			 */
			void runWidgetAction()
			{
				if (mStopButton->isSelected())
				{
					stopButtonAction();
				}
				else
				if (mStartButton->isSelected())
				{
					startButtonAction();
				}

				// Deselect the buttons so that the "unselected" skins
				// are redisplayed, and make the edit box selected.
				mStopButton->setSelected(false);
				mStartButton->setSelected(false);

			}

			/**
			 * This method is called when the Clear button is activated.
			 */
			void stopButtonAction()
			{
				StopMetronome();
			}

			/**
			 * This method is called when the Submit button is activated.
			 */
			void startButtonAction()
			{
				SetPeriod(TXT_RAPID_FIRE_6_SEC);
				StartMetronome();
			}


			void AddBulletHoles(int index)  {


				MAHandle R_BULLET_HOLE;
				if(displayHeight >= 1200 && displayWidth >= 720)
					R_BULLET_HOLE = R_BULLETHOLE_720x1280;
				else if(displayHeight >= 480 && displayWidth >= 320)
					R_BULLET_HOLE = R_BULLETHOLE_320x480;
				else
					R_BULLET_HOLE = R_BULLETHOLE_320x480;

				// Seed the Radmoniser
				MAPUtil::DateTime* tm = new MAPUtil::DateTime;
				srand(tm->now().getTicks());

				if(!mBulletHoles[index]) {
					mBulletHoles[index] = new MAUI::Image(
							0,
							0,
							0,
							0,
							mBackgroundImage,
							true,
							true,
							R_BULLET_HOLE
					);
				}

				mBulletHoles[index]->setPosition((int)(170*xScale)+(rand() % (int)(405*xScale)), (int)(105*yScale)+(rand() % (int)(365*yScale)) );
				mBulletHoles[index]->setEnabled(true);

			}

			void ClearBulletHoles()  {
				for(int i=0;i<5;i++)  {
					if(mBulletHoles[i]!=NULL) {
						mBulletHoles[i]->setEnabled(false);
					}

				}
			}

			void SetGreenLight(LIGHTSTATE state) {
				if(state == ON)
					mGreenLight->setResource(R_GREEN_LIGHT_ON);
				else
					mGreenLight->setResource(R_LIGHT_OFF);
			}

			void SetRedLight(LIGHTSTATE state) {
				if(state == ON)
					mRedLight->setResource(R_RED_LIGHT_ON);
				else
					mRedLight->setResource(R_LIGHT_OFF);
			}

private:
			int displayHeight;
			int displayWidth;
			float	xScale;					// Scale image positions by this amount
			float	yScale;					// Scale image positions by this amount
			/** The Clear button. */
			MAUI::Image* mStopButton;

			/** The Submit button. */
			MAUI::Image* mStartButton;

			/** The Training button. */
			MAUI::Image* mTrainingButton;

			MAUI::Image* mBackgroundImage;
			MAUI::Image* mBulletHole;
			MAUI::Image* mGreenLight;
			MAUI::Image* mRedLight;

			MAUI::Image* mBulletHoles[15];

			MAUI::ListBox* mList;

};


#endif /* MAINSCREEN_H_ */
