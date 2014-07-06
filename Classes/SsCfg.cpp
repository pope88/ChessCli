#include "Config.h"
#include "SsCfg.h"


#include "System/IniFile.h"
#include "System/TimeUtil.h"
#include "System/StringTokenizer.h"
#include <sstream>

SsCfg sSCfg;

SsCfg::SsCfg():tcpPort(0)
{
}

SsCfg::~SsCfg()
{

}

void SsCfg::loadString(const char *cfg)
{
	System::IniFileA iniFile;

	std::istringstream s(cfg);
	iniFile.Load(s);
	processIniFile(iniFile);
}

void SsCfg::load(const std::string& filename)
{
	System::IniFileA iniFile;
	if (iniFile.Load(filename))
	{
		processIniFile(iniFile);
	}
}




void SsCfg::processIniFile(System::IniFileA &iniFile)
{
	System::IniSection *sec = iniFile.GetSection("network");
	if (sec != NULL)
	{
		tcpHost = sec->GetKeyValue("tcpHost");
		tcpPort = (UInt16)atoi(sec->GetKeyValue("tcpPort").c_str());
	}

	//tcpHost
	if (tcpHost.empty())
	{
		tcpHost = "0.0.0.0";
	}
	if (tcpPort == 0)
	{
		tcpPort = 8880;
	}

	if(dataPath.empty())
	{
		dataPath = "conf/data/";
	}
	if(logPath.empty())
	{
		logPath = "log/";
	}

}