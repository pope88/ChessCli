#ifndef __INIFILE_H_
#define __INIFILE_H_

namespace System
{

#define INI_TOKEN_A_ANSI "\a"	// I.E. Item1;Item2;Item3 - '\a' used in place of ';'
#define INI_TOKEN_B_ANSI "\b"	// I.E. Item1,Item1b;Item2,Item2b;Item3,Item3b - '\b' used in place of ','
#define INI_EMPTY_ANSI "*"		// Used to indicate empty value in token string. I.E. *;Item2;*;Item3;

struct ci_less_a
{
	bool operator() (const std::string & s1, const std::string & s2) const
	{
#ifndef _WIN32
		return strcasecmp(s1.c_str(), s2.c_str()) < 0;
#else
		return _stricmp(s1.c_str(), s2.c_str()) < 0;
#endif
	}
};

class IniFileA
{
public:
	static const char* const LF;
public:
	IniFileA();
	~IniFileA();

	// Used to save the data back to the file or your choice
	bool Save( const std::string& fileName );

	// Save data to an output stream
	void Save( std::ostream& output );

	// Loads the Reads the data in the ini file into the IniFile object
	bool Load( const std::string& fileName , bool bMerge = false );

	// Load data from an input stream
	void Load( std::istream& input , bool bMerge = false );

public:
	class IniMergeA
	{
	public:
		explicit IniMergeA(IniFileA& ini):_INI(ini){}
		std::istream &operator()(std::istream& input) const
		{
			_INI.Load( input , true );
			return input;
		}
	private:
		IniFileA& _INI;
	};
public:
	class IniSectionA
	{
		friend class IniFileA; // Allow IniFileA to create sections
	public:
		class IniKeyA
		{
			friend class IniSectionA; // Allow IniSectionA to create keys
		private: // IniFileA acts as a class factory for IniSectionA Objects
			IniKeyA( IniSectionA* pSection , std::string sKeyName );
			IniKeyA( const IniKeyA& ); // No Copy
			IniKeyA& operator=(const IniKeyA&); // No Copy
			~IniKeyA( );
		public:
			// Sets the value of the key
			void SetValue( std::string sValue );
			// Returns the value of the Key
			std::string GetValue() const;
			// Sets the key name, returns true on success, fails if the section
			// name sKeyName already exists
			bool SetKeyName( std::string sKeyName );
			// Returns the name of the Key
			std::string GetKeyName() const;
		private:
			// Name of the Key
			std::string m_sKeyName;
			// Value associated
			std::string m_sValue;
			// Pointer to the parent IniSectionA
			IniSectionA* m_pSection;
		}; // End of IniKeyA
		typedef std::map<std::string,IniKeyA*,ci_less_a> KeyMapA;
#ifdef _WIN32
		// Added for VC6 Support
#if defined(_MSC_VER) && (_MSC_VER >= 1200) && (_MSC_VER < 1300)
		friend class IniKeyA;
#endif
#endif
	private: // IniSectionA acts as a class factory for IniKeyA Objects
		IniSectionA( IniFileA* pIniFile , std::string sSectionName );
		IniSectionA( const IniSectionA& ); // No Copy
		IniSectionA& operator=(const IniSectionA&); // No Copy
		~IniSectionA( );
	public:
		// Adds a key to the IniSectionA object, returns a IniKeyA pointer to the new or existing object
		IniKeyA* AddKey( std::string sKeyName );
		// Removes a single key by pointer
		void RemoveKey( IniKeyA* pKey );
		// Removes a single key by string
		void RemoveKey( std::string sKey );
		// Removes all the keys in the section
		void RemoveAllKeys( );
		// Returns a IniKeyA pointer to the key by name, NULL if it was not found
		IniKeyA* GetKey( std::string sKeyName ) const;
		// Returns all keys in the section by KeyList ref
		const KeyMapA& GetKeys() const;
		// Returns a KeyValue at a certain section
		std::string GetKeyValue( std::string sKey ) const;
		// Sets a KeyValuePair at a certain section
		void SetKeyValue( std::string sKey, std::string sValue );
		// Sets the section name, returns true on success, fails if the section
		// name sSectionName already exists
		bool SetSectionName( std::string sSectionName );
		// Returns the section name
		std::string GetSectionName() const;

	private:
		// IniFileA pointer back to the object that instanciated the section
		IniFileA* m_pIniFile;
		// Name of the section
		std::string m_sSectionName;
		// List of IniKeyA pointers ( Keys in the section )
		KeyMapA m_keys;
	}; // End of IniSectionA
	// Typedef of a List of IniSectionA pointers
	typedef std::map<std::string,IniSectionA*,ci_less_a> SecMapA;
#ifdef _WIN32
	// Added for VC6 Support
#if defined(_MSC_VER) && (_MSC_VER >= 1200) && (_MSC_VER < 1300)
	friend class IniSectionA;
#endif
#endif
public:
	// Adds a section to the IniFileA object, returns a IniFileA pointer to the new or existing object
	IniSectionA* AddSection( std::string sSection );
	// Removes section by pointer
	void RemoveSection( IniSectionA* pSection );
	// Removes a section by its name sSection
	void RemoveSection( std::string sSection );
	// Removes all existing sections
	void RemoveAllSections( );
	// Returns a IniSectionA* to the section by name, NULL if it was not found
	IniSectionA* GetSection( std::string sSection ) const;
	// Gets all the section in the ini file
	const SecMapA& GetSections() const;
	// Returns a KeyValue at a certain section
	std::string GetKeyValue( std::string sSection, std::string sKey ) const;
	// Sets a KeyValuePair at a certain section
	void SetKeyValue( std::string sSection, std::string sKey, std::string sValue );
	// Renames an existing section returns true on success, false if the section didn't exist or there was another section with the same sNewSectionName
	bool RenameSection( std::string sSectionName  , std::string sNewSectionName );
	// Renames an existing key returns true on success, false if the key didn't exist or there was another section with the same sNewSectionName
	bool RenameKey( std::string sSectionName  , std::string sKeyName , std::string sNewKeyName);
private:
	IniFileA( const IniFileA&); // No Copy
	IniFileA& operator=(const IniFileA&); // No Copy
	// List of IniSectionA pointers ( List of sections in the class )
	SecMapA m_sections;
}; // End of IniFileA

// Basic typedefs for ease of use
typedef IniFileA::IniMergeA IniMergeA;
typedef IniFileA::IniSectionA IniSectionA;
typedef IniSectionA::IniKeyA IniKeyA;

// Pointers
typedef IniFileA* PIniA;
typedef IniKeyA* PIniKEYA;
typedef IniSectionA* PIniSECA;

// Map Types
typedef IniSectionA::KeyMapA KeyMapA;
typedef IniFileA::SecMapA SecMapA;


std::ostream& operator<<(std::ostream& output, IniFileA& obj);
std::istream& operator>>(std::istream& input, IniFileA& obj);
std::istream& operator>>(std::istream& input, IniMergeA merger);

// Unicode Class Definition

#define INI_TOKEN_A_UNICODE L"\a"	// I.E. Item1;Item2;Item3 - '\a' used in place of ';'
#define INI_TOKEN_B_UNICODE L"\b"	    // I.E. Item1,Item1b;Item2,Item2b;Item3,Item3b - '\b' used in place of ','
#define INI_EMPTY_UNICODE L"*"		// Used to indicate empty value in token string. I.E. *;Item2;*;Item3;

#define INI_TOKEN_A INI_TOKEN_ANSI
#define INI_TOKEN_B INI_TOKEN_ANSI
#define INI_EMPTY INI_EMPTY_ANSI
typedef IniMergeA IniMerge;
typedef IniFileA IniFile;
typedef IniSectionA IniSection;
typedef IniKeyA IniKey;
typedef PIniA PIni;
typedef PIniKEYA PIniKEY;
typedef PIniSECA PIniSEC;
typedef KeyMapA KeyMap;
typedef SecMapA SecMap;

}

#endif

