#include "DebugUI.h"

#include "backbuffer.h"
#include "logmanager.h"

DebugUI* DebugUI::sm_pInstance = 0;

DebugUI::DebugUI() 
	: NUM_LINES(8)
{
	m_lines = new std::string[NUM_LINES];
	for (int i = 0; i < NUM_LINES; ++i)
	{
		m_lines[i] = "";
	}
	ConstructConstChar();
}


DebugUI & DebugUI::GetInstance()
{
	if (sm_pInstance == 0)
	{
		sm_pInstance = new DebugUI();
	}

	return (*sm_pInstance);
}

void DebugUI::DestroyInstance()
{
	delete sm_pInstance;
	sm_pInstance = 0;
}

DebugUI::~DebugUI()
{
	delete[] m_lines;
	m_lines = 0;
}

void DebugUI::Draw(BackBuffer & backBuffer)
{
	backBuffer.DrawMenuText(100, 100, m_output.c_str(), false);
}

void DebugUI::SetLine(int index, std::string string)
{
	int i = (index > NUM_LINES - 1) ? 0 : index;
	m_lines[i] = string;

	ConstructConstChar();
}

void DebugUI::ConstructConstChar()
{
	std::string finalOutput = "";
	for (int i = 0; i < NUM_LINES; ++i)
	{
		finalOutput.append(m_lines[i]);
		finalOutput.append("\n");
	}

	m_output = finalOutput;
	//LogManager::GetInstance().Log(m_output);
}
