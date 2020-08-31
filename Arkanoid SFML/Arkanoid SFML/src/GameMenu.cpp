#include "Engine.h"

/*static bool EscapeButton(RenderWindow& window, Menu& menu, bool& creditsPage)
{
	if (creditsPage == false)
	{
		window.close();
		return false;
	}
	else
	{
		creditsPage = false;
		menu.changeArrowPosition(creditsPage);
	}
	return true;
}

static int EnterButton(Menu& menu, bool& creditsPage)
{
	if (creditsPage == true)
	{
		creditsPage = false;
		menu.changeArrowPosition(creditsPage);
	}
	else
	{
		switch (menu.readState())
		{
		case 1:
			return 1;

		case 2:
			creditsPage = true;
			menu.changeArrowPosition(creditsPage);
			return 2;

		case 3:
			return 3;
		}
	}
	return 0;
}
*/
bool GameMenu(RenderWindow& window)
{
	Menu menu;
	menu.Run(window);

	return false;
}