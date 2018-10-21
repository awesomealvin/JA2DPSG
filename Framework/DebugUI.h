#ifndef __DEBUGUI_H__
#define __DEBUGUI_H__

#include <string>

class BackBuffer;

class DebugUI
{
public:
	static DebugUI& GetInstance();
	static void DestroyInstance();
	~DebugUI();

	void Draw(BackBuffer& backBuffer);
	void SetLine(int index, std::string string);

protected:
	void ConstructConstChar();
	
private:
	DebugUI();
	DebugUI(const DebugUI& debugUI);
	DebugUI& operator=(const DebugUI& debugUI);

public:
	bool m_drawHitBoxes = false;

protected:
	static DebugUI* sm_pInstance;

	std::string* m_lines;
	const int NUM_LINES;

	std::string m_output;


};

#endif

