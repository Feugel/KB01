#ifndef RENDERER_H
#define RENDERER_H

class Window;

class Renderer
{
public:
	Renderer(void);
	virtual ~Renderer(void);
	virtual void* GetDevice() = 0;
	virtual void RenderStart() = 0;
	virtual void Render() = 0;
	virtual void RenderEnd() = 0;
	virtual void Present() = 0;
	virtual void Init(Window* window) = 0;
};

#endif //RENDERER_H

