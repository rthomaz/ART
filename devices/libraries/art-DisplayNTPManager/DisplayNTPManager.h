#ifndef DisplayNTPManager_h
#define DisplayNTPManager_h

#include "Arduino.h"
#include "DebugManager.h"
#include "DisplayManager.h"
#include "NTPManager.h"

class DisplayNTPManager
{
public:
	DisplayNTPManager(DisplayManager& displayManager, NTPManager& ntpManager, DebugManager& debugManager);
	~DisplayNTPManager();	
	
	//Também será private quando resolver o problema dos handlers
	void					updateCallback(bool update, bool forceUpdate);	
	
private:

	DisplayManager*       	_displayManager;	
	NTPManager*          	_ntpManager;
	DebugManager*         	_debugManager;

	void					printTime();
	void					printUpdate(bool on);
	
};

#endif