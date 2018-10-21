// COMP710 GP 2D Framework 2018
#ifndef __LOGMANAGER_H__
#define __LOGMANAGER_H__

class LogManager
{
	//Member Methods:
public:
	static LogManager& GetInstance();
	~LogManager();

	void Log(const char* pcMessage);

	static void DestroyInstance();
protected:

private:
	LogManager();
	LogManager(const LogManager& logManager);
	LogManager& operator=(const LogManager& logManager);

	//Member Data:
public:

protected:
	static LogManager* sm_pInstance;

private:

};

#endif //__LOGMANAGER_H__
