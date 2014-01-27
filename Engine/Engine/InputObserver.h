#include <vector>
#include "InputMouse.h"

class InputManager;
//-----------------------------------------------------
// Observer Class			
//-----------------------------------------------------
class InputObserver
{
public:
	virtual ~InputObserver();		// Destructor
	virtual void Notify(MouseStruct mouseStruct, char* keyBuffer) = 0;
protected:
//constructor is protected because this class is abstract, it’s only meant to be inherited!
	InputObserver();
};

