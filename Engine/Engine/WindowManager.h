#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <windows.h>
#include <map>		 // std::map
#include <algorithm> // find()

class Scene;
class Kernel; // Forward Declaration to access the Kernel from the Manager;
class Window; // Forward Declaration to access the Manager from the Window;

class WindowManager
{
public:
	//Destructor.
	//Calls Cleanup and then destroys all local variables.
	virtual ~WindowManager(void);
	//Cleans up the mess this WindowManager created.
	//Keeps variables in memory to enable a reset.
	void Cleanup();
	//Get the instance
	static WindowManager* Instance();
	//Pushes the window at the back of the vector.
	bool RegisterWindow(Window* window);
	//Simply removes a window from the vector and cleans up afterwards.
	bool ReleaseWindow(Window* window);
	//Remove a window by it's handle
	bool ReleaseWindow(HWND hwnd);
	//Registers a scene to a window
	void RegisterScene(Window* window, Scene* scene);
	//Get the scene registered with this Window or NULL if not found
	Scene* GetSceneByWindow(Window* window);
	//Get the scene registered with this Window or NULL if not found
	Scene* GetSceneByWindow(HWND window);
			//Returns the vector containing the windows.
			std::map<HWND, Window*> GetWindows();
			//Render on all windows
			void Render();
			//Get the kernel
			Kernel* GetKernel();
			//Set the kernel
			void SetKernel(Kernel* kernel);
	//Window Procedure used by all Windows. Uses WindowProc if this manager can be decoded from lParam.
	static LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	//The actual Window Procedure. Keeps the vector up to date.
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	//Default constructor.
	WindowManager();
	//Adds a window to the vector if it does not yet exist.
	void PushWindow(Window* wnd);
	//Removes a window from the vector
	void PopWindow(Window* window);
	//Get a window by its handle
	Window* GetWindowByHandle(HWND hwnd);
	//The instance
	static WindowManager* instance;
	//Local Vector to keep track of all instatiated windows.
	std::map<HWND, Window*> windows;
	//Kernel reference
	Kernel* kernel;
	// Keep track of Scenes in Windows
	std::map<Window*, Scene*> sceneMap;
};

#endif