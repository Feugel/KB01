#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H


class WindowManager
{
public:
	WindowManager(void);
	virtual ~WindowManager(void);
	void Cleanup();
	bool CreateWindow();
	bool ReleaseWindow();
};

#endif