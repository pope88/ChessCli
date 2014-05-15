#ifndef _ZOCFG_H_
#define _ZOCFG_H_

namespace System
{
	class IniFileA;
}

class ZoCfg
{
public:
	ZoCfg();
	~ZoCfg();
	void load(const std::string& filename = "conf/zoCfg.ini");
	void loadString(const char *cfg);
	void unload();
private:
	void processIniFile(System::IniFileA &iniFile);
public:
	std::vector<UInt32> serverNo;
	std::set<UInt32> serverNoSet;
	std::vector<std::string> serverName;
	std::string tcpHost;
	UInt32 tcpPort;

	std::string dataPath;
	std::string logPath;
	std::string sqlPath;
	std::string scriptPath;
	
	std::string redisHost;
	UInt16 redisPort;
	std::string redisPrefix;

	std::string mongoHost;
	UInt16 mongoPort;
	std::string mongoDatabase;

	bool backendEnable;
	std::string backendHost;
	UInt16 backendPort;
	std::string backendDatabase;
	UInt32 onlineLogInterval;

	UInt32 openDay;
	std::string serverKey;

	bool debugMode;
	bool enableGM;	
	bool postReg;
	bool useOldData;

	bool useIdPool;
	std::string idPoolHost;
	UInt16 idPoolPort;
};

extern ZoCfg zocfg;
#endif
#endif
#endif