#ifndef _SSCFG_H_
#define _SSCFG_H_

#include "System/IniFile.h"

namespace System
{
	class IniFileA;
}

class SsCfg
{
public:
	SsCfg();
	~SsCfg();
	void load(const std::string& filename = "conf/sSCfg.ini");
	void loadString(const char *scfg);
	void unload();
private:
	void processIniFile(System::IniFileA &iniFile);
public:

	std::string tcpHost;
	UInt32 tcpPort;

	std::string dataPath;
	std::string logPath;

	bool debugMode;
};

extern SsCfg sSCfg;
#endif

