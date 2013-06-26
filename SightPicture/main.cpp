#include <ma.h>
#include <mavsprintf.h>
#include <MAUtil/Moblet.h>
#include <MAUtil/Environment.h>
#include <NativeUI/Widgets.h>
#include <NativeUI/WidgetUtil.h>
#include <NativeUI/Image.h>
#include <NativeUI/Label.h>
#include <MAAPI.h>
#include "MAHeaders.h"
#include <conprint.h>


using namespace MAUtil;
using namespace NativeUI;

/**
 * Moblet to be used as a template for a Native UI application.
 */
class NativeUIMoblet : public Moblet, public NativeUI::ScreenListener, public NativeUI::ButtonListener
{
public:
	/**
	 * The constructor creates the user interface.
	 */
	NativeUIMoblet()
	{
		// Set the orientation mode to dynamic, so that it is possible to switch
		// between portrait and landscape orientations. You can also use these
		// syscalls to lock the screen in PORTRAIT or LANDSCAPE mode.
		maScreenSetSupportedOrientations(MA_SCREEN_ORIENTATION_DYNAMIC);


		createUI();
	}

	/**
	 * Destructor.
	 */
	virtual ~NativeUIMoblet()
	{

		// All the children will be deleted.
		delete mScreen;
	}

	/**
	 * Create the user interface.
	 */
	void createUI()
	{
		// Create a NativeUI screen that will hold layout and widgets.
		mScreen = new Screen();
		mScreen->setTitle("Sight Picture");
		mScreen->addScreenListener(this);
		mTargetImage = new Image();
		mTargetImage->setImage(R_PRECISION_TARGET_720x1280);
		mTargetImage->setScaleMode(IMAGE_SCALE_PRESERVE_ASPECT);



		// Target Button has no image. It takes up the full screen size
		mTargetButton = new ImageButton();
		mTargetButton->addButtonListener(this);
		mScreen->addChild(mTargetButton);

		mScreen->addChild(mTargetImage);
		DrawScreen();
	}

	void DrawScreen()  {
		displayWidth = EXTENT_X(maGetScrSize());
		displayHeight = EXTENT_Y(maGetScrSize());


		// Target is Square so use the width only
		mTargetImage->setSize(displayWidth, displayWidth);

		// Draw Image in the middle of the screen
		if( maScreenGetCurrentOrientation() & MA_SCREEN_ORIENTATION_PORTRAIT) {  // Portait Mode
			mTargetButton->setSize(EXTENT_X(maGetScrSize()),EXTENT_Y(maGetScrSize()));
			mTargetImage->setPosition(0,(displayHeight/2)-(mTargetImage->getHeight()/2));
		}
		else  {
			mTargetButton->setSize(EXTENT_Y(maGetScrSize()),EXTENT_X(maGetScrSize()));
			mTargetImage->setPosition((displayHeight/2)-(mTargetImage->getHeight()/2),0);

		}
		mScreen->show();
		maUpdateScreen();
	}

	/**
	 * Called when a key is pressed.
	 */
	void keyPressEvent(int keyCode, int nativeCode)
	{
		if (MAK_BACK == keyCode || MAK_0 == keyCode)
		{
			// Call close to exit the application.
			close();
		}
	}


	virtual void buttonClicked(Widget* widget) {

		if(mTargetImage->getImage() == R_PRECISION_TARGET_720x1280)
			mTargetImage->setImage(R_DUELING_TARGET_720x1200);
		else
			mTargetImage->setImage(R_PRECISION_TARGET_720x1280);

		maUpdateScreen();
	}

	virtual void orientationChanged(Screen* screen, int screenOrientation)  {
		DrawScreen();
	}




private:
	int displayWidth;
	int displayHeight;

    Screen* mScreen;			//A Native UI screen
    VerticalLayout* mLayout;	//A Native UI layout
    ImageButton* mTargetButton;
    Image* mTargetImage;		//A Native UI button
    Label* mLabel;
    int	scrOrientation;
};

/**
 * Main function that is called when the program starts.
 */
extern "C" int MAMain()
{
	Moblet::run(new NativeUIMoblet());
	return 0;
}
