#include "Config.h"
#include "IniFile.h"
#include <algorithm>
#include <iostream>
#include <fstream>

namespace System
{

// In the event you want to trace the calls can define _TRACE_INIFILE
#if defined(_TRACE_INIFILE)
#define _INIFILE_DEBUG
#endif

// _CRLF is used in the Save() function
// The class will read the correct data regardless of how the file linefeeds are defined <CRLF> or <CR>
// It is best to use the linefeed that is default to the system. This reduces issues if needing to modify
// the file with ie. notepad.exe which doesn't recognize unix linefeeds.
#ifdef _WIN32 // Windows default is \r\n
#ifdef _FORCE_UNIX_LINEFEED
#define _CRLFA "\n"
#define _CRLFU L"\n"
#else
#define _CRLFA "\r\n"
#define _CRLFU L"\r\n"
#endif
#else // Standard format is \n for unix
#ifdef _FORCE_WINDOWS_LINEFEED
#define _CRLFA "\r\n"
#define _CRLFU L"\r\n"
#else
#define _CRLFA "\n"
#define _CRLFU L"\n"
#endif
#endif

// Helper Functions
void RTrim(std::string &str, const std::string& chars = " \t")
{
#ifdef _INIFILE_DEBUG
	std::cout <<  "RTrim()" << std::endl;
#endif
	str.erase(str.find_last_not_of(chars)+1);
}

void LTrim(std::string &str, const std::string& chars = " \t" )
{
#ifdef _INIFILE_DEBUG
	std::cout <<  "LTrim()" << std::endl;
#endif
	str.erase(0, str.find_first_not_of(chars));
}

void Trim( std::string& str , const std::string& chars = " \t" )
{
#ifdef _INIFILE_DEBUG
	std::cout <<  "Trim()" << std::endl;
#endif
	str.erase(str.find_last_not_of(chars)+1);
	str.erase(0, str.find_first_not_of(chars));
}

// Stream Helpers

std::ostream& operator<<(std::ostream& output, IniFileA& obj)
{
	obj.Save( output );
	return output;
}

std::istream& operator>>(std::istream& input, IniFileA& obj)
{
	obj.Load( input );
	return input;
}

std::istream& operator>>(std::istream& input, IniMergeA merger)
{
	return merger(input);
}

// IniFileA class methods

IniFileA::IniFileA()
{
#ifdef _INIFILE_DEBUG
	std::cout <<  "IniFileA::IniFileA()" << std::endl;
#endif
}

IniFileA::~IniFileA()
{
#ifdef _INIFILE_DEBUG
	std::cout <<  "IniFileA::~IniFileA()" << std::endl;
#endif
	RemoveAllSections( );
}

const char* const IniFileA::LF = _CRLFA;

void IniFileA::Save( std::ostream& output )
{
	std::string sSection;

	for( SecMapA::iterator itr = m_sections.begin() ; itr != m_sections.end() ; itr++ )
	{
		sSection = "[" + itr->second->GetSectionName() + "]";

#ifdef _INIFILE_DEBUG
		std::cout <<  "Writing Section " << sSection << std::endl;
#endif

		output << sSection << _CRLFA;

		for( KeyMapA::iterator klitr = itr->second->m_keys.begin() ; klitr != itr->second->m_keys.end() ; klitr++ )
		{
			std::string sKey = klitr->second->GetKeyName() + "=" + klitr->second->GetValue();
#ifdef _INIFILE_DEBUG
			std::cout <<  "Writing Key [" << sKey << "]" << std::endl;
#endif
			output << sKey << _CRLFA;
		}
	}
}

bool IniFileA::Save( const std::string& fileName )
{
#ifdef _INIFILE_DEBUG
	std::cout <<  "IniFileA::Save() - " << fileName << std::endl;
#endif

	std::ofstream output;

	output.open( fileName.c_str() , std::ios::binary );

	if( !output.is_open() )
		return false;

	Save(output);

	output.close();
	return true;
}


void IniFileA::Load( std::istream& input , bool bMerge )
{
	if( !bMerge )
		RemoveAllSections();

	IniSectionA* pSection = NULL;
	std::string sRead;
	enum { KEY , SECTION , COMMENT , OTHER };

	while( std::getline( input , sRead ) )
	{

		// Trim all whitespace on the left
		LTrim( sRead );
		// Trim any returns
		RTrim( sRead , "\n\r");

		if( !sRead.empty() )
		{
			unsigned int nType = ( sRead.find_first_of("[") == 0 && ( sRead[sRead.find_last_not_of(" \t\r\n")] == ']' ) ) ? SECTION : OTHER ;
			nType = ( (nType == OTHER) && ( sRead.find_first_of("=") ) > 0 ) ? KEY : nType ;
			nType = ( (nType == OTHER) && ( sRead.find_first_of("#") == 0) ) ? COMMENT : nType ;

			switch( nType )
			{
			case SECTION:
#ifdef _INIFILE_DEBUG
				std::cout <<  "Parsing: Secton - " << sRead << std::endl;
#endif
				pSection = AddSection( sRead.substr( 1 , sRead.size() - 2 ) );
				break;

			case KEY:
				{
#ifdef _INIFILE_DEBUG
					std::cout <<  "Parsing: Key - " << sRead << std::endl;
#endif
					// Check to ensure valid section... or drop the keys listed
					if( pSection )
					{
						size_t iFind = sRead.find_first_of("=");
						std::string sKey = sRead.substr(0,iFind);
						std::string sValue = sRead.substr(iFind + 1);
						IniKeyA* pKey = pSection->AddKey( sKey );
						if( pKey )
						{
#ifdef _INIFILE_DEBUG
							std::cout <<  "Parsing: Key Value - " << sValue << std::endl;
#endif
							pKey->SetValue( sValue );
						}
					}
				}
				break;
			case COMMENT:
#ifdef _INIFILE_DEBUG
				std::cout <<  "Parsing: Comment - " << sRead << std::endl;
#endif
				break;
			case OTHER:
#ifdef _INIFILE_DEBUG
				std::cout <<  "Parsing: Other - " << sRead << std::endl;
#endif
				break;
			}
		}
	}
}

bool IniFileA::Load(const std::string& fileName , bool bMerge )
{
#ifdef _INIFILE_DEBUG
	std::cout <<  "IniFileA::Load() - " << fileName << std::endl;
#endif

	std::ifstream input;

	input.open( fileName.c_str() , std::ios::binary);

	if( !input.is_open() )
		return false;

	Load( input , bMerge );

	input.close();
	return true;
}

const SecMapA& IniFileA::GetSections() const
{
#ifdef _INIFILE_DEBUG
	std::cout <<  "IniFileA::GetSections()" << std::endl;
#endif
	return m_sections;
}


IniSectionA* IniFileA::GetSection( std::string sSection ) const
{
#ifdef _INIFILE_DEBUG
	std::cout << "IniFileA::GetSection()" << std::endl;
#endif
	Trim(sSection);
	SecMapA::const_iterator itr = m_sections.find( sSection );
	if( itr != m_sections.end() )
		return itr->second;
	return NULL;
}

IniSectionA* IniFileA::AddSection( std::string sSection )
{
#ifdef _INIFILE_DEBUG
	std::cout <<  "IniFileA::AddSection()" << std::endl;
#endif

	Trim(sSection);
	SecMapA::const_iterator itr = m_sections.find( sSection );
	if( itr == m_sections.end() )
	{
		// Note constuctor doesn't trim the string so it is trimmed above
		IniSectionA* pSection = new IniSectionA( this , sSection );
		m_sections[sSection] = pSection;
		return pSection;
	}
	else
		return itr->second;
}


std::string IniFileA::GetKeyValue( std::string sSection, std::string sKey ) const
{
#ifdef _INIFILE_DEBUG
	std::cout <<  "IniFileA::GetKeyValue()" << std::endl;
#endif
	std::string sValue;
	IniSectionA* pSec = GetSection( sSection );
	if( pSec )
	{
		IniKeyA* pKey = pSec->GetKey( sKey );
		if( pKey )
			sValue = pKey->GetValue();
	}
	return sValue;
}

void IniFileA::SetKeyValue( std::string sSection, std::string sKey, std::string sValue )
{
#ifdef _INIFILE_DEBUG
	std::cout <<  "IniFileA::SetKeyValue()" << std::endl;
#endif
	IniSectionA* pSec = AddSection( sSection );
	if( pSec )
	{
		IniKeyA* pKey = pSec->AddKey( sKey );
		if( pKey )
			pKey->SetValue( sValue );
	}
}


void IniFileA::RemoveSection( std::string sSection )
{
#ifdef _INIFILE_DEBUG
	std::cout <<  "IniFileA::RemoveSection()" << std::endl;
#endif
	Trim(sSection);
	SecMapA::iterator itr = m_sections.find( sSection );
	if( itr != m_sections.end() )
	{
		delete itr->second;
		m_sections.erase( itr );
	}
}

void IniFileA::RemoveSection( IniSectionA* pSection )
{
#ifdef _INIFILE_DEBUG
	std::cout <<  "IniFileA::RemoveSection()" << std::endl;
#endif
	// No trim since internal object not from user
	SecMapA::iterator itr = m_sections.find( pSection->m_sSectionName );
	if( itr != m_sections.end() )
	{
		delete itr->second;
		m_sections.erase( itr );
	}
}

void IniFileA::RemoveAllSections( )
{
#ifdef _INIFILE_DEBUG
	std::cout <<  "IniFileA::RemoveAllSections()" << std::endl;
#endif
	for( SecMapA::iterator itr = m_sections.begin() ; itr != m_sections.end() ; itr++ )
	{
#ifdef _INIFILE_DEBUG
		std::cout <<  "Deleting Section: MapKey[" << itr->first << "] IniSectionAName[" << itr->second->GetSectionName() << "]" << std::endl;
#endif
		delete itr->second;
	}
	m_sections.clear();
}


bool IniFileA::RenameSection( std::string sSectionName  , std::string sNewSectionName )
{
#ifdef _INIFILE_DEBUG
	std::cout <<  "IniFileA::RenameSection()" << std::endl;
#endif
	// Note string trims are done in lower calls.
	bool bRval = false;
	IniSectionA* pSec = GetSection( sSectionName );
	if( pSec )
	{
		bRval = pSec->SetSectionName( sNewSectionName );
	}
	return bRval;
}

bool IniFileA::RenameKey( std::string sSectionName  , std::string sKeyName , std::string sNewKeyName)
{
#ifdef _INIFILE_DEBUG
	std::cout <<  "IniFileA::RenameKey()" << std::endl;
#endif
	// Note string trims are done in lower calls.
	bool bRval = false;
	IniSectionA* pSec = GetSection( sSectionName );
	if( pSec != NULL)
	{
		IniKeyA* pKey = pSec->GetKey( sKeyName );
		if( pKey != NULL )
			bRval = pKey->SetKeyName( sNewKeyName );
	}
	return bRval;
}

// IniFileA functions end here

// IniSectionA functions start here

IniSectionA::IniSectionA( IniFileA* pIniFile , std::string sSectionName ) : m_pIniFile(pIniFile)
{
#ifdef _INIFILE_DEBUG
	std::cout <<  "IniSectionA::IniSectionA()" << std::endl;
#endif
	m_sSectionName = sSectionName;
}


IniSectionA::~IniSectionA()
{
#ifdef _INIFILE_DEBUG
	std::cout <<  "IniSectionA::~IniSectionA()" << std::endl;
#endif
	RemoveAllKeys();
}

IniKeyA* IniSectionA::GetKey( std::string sKeyName ) const
{
#ifdef _INIFILE_DEBUG
	std::cout <<  "IniSectionA::GetKey()" << std::endl;
#endif
	Trim(sKeyName);
	KeyMapA::const_iterator itr = m_keys.find( sKeyName );
	if( itr != m_keys.end() )
		return itr->second;
	return NULL;
}

void IniSectionA::RemoveAllKeys()
{
#ifdef _INIFILE_DEBUG
	std::cout <<  "IniSectionA::RemoveAllKeys()" << std::endl;
#endif
	for( KeyMapA::iterator itr = m_keys.begin() ; itr != m_keys.end() ; itr++ )
	{
#ifdef _INIFILE_DEBUG
		std::cout <<  "Deleting Key: " << itr->second->GetKeyName() << std::endl;
#endif
		delete itr->second;
	}
	m_keys.clear();
}

void IniSectionA::RemoveKey( std::string sKey )
{
#ifdef _INIFILE_DEBUG
	std::cout <<  "IniSectionA::RemoveKey()" << std::endl;
#endif
	Trim( sKey );
	KeyMapA::iterator itr = m_keys.find( sKey );
	if( itr != m_keys.end() )
	{
		delete itr->second;
		m_keys.erase( itr );
	}
}

void IniSectionA::RemoveKey( IniKeyA* pKey )
{
#ifdef _INIFILE_DEBUG
	std::cout <<  "IniSectionA::RemoveKey()" << std::endl;
#endif
	// No trim is done to improve efficiency since IniKeyA* should already be trimmed
	KeyMapA::iterator itr = m_keys.find( pKey->m_sKeyName );
	if( itr != m_keys.end() )
	{
		delete itr->second;
		m_keys.erase( itr );
	}
}

IniKeyA* IniSectionA::AddKey( std::string sKeyName )
{
#ifdef _INIFILE_DEBUG
	std::cout <<  "IniSectionA::AddKey()" << std::endl;
#endif
	Trim(sKeyName);
	KeyMapA::const_iterator itr = m_keys.find( sKeyName );
	if( itr == m_keys.end() )
	{
		// Note constuctor doesn't trim the string so it is trimmed above
		IniKeyA* pKey = new IniKeyA( this , sKeyName );
		m_keys[sKeyName] = pKey;
		return pKey;
	}
	else
		return itr->second;
}

bool IniSectionA::SetSectionName( std::string sSectionName )
{
#ifdef _INIFILE_DEBUG
	std::cout <<  "IniSectionA::SetSectionName()" << std::endl;
#endif
	Trim(sSectionName);
	// Does this already exist.
	if( m_pIniFile->m_sections.find( sSectionName ) == m_pIniFile->m_sections.end() )
	{
#ifdef _INIFILE_DEBUG
		std::cout <<  "Setting Section Name: [" << m_sSectionName <<  "] --> [" << sSectionName << "]" << std::endl;
#endif

		// Find the current section if one exists and remove it since we are renaming
		SecMapA::iterator itr = m_pIniFile->m_sections.find( m_sSectionName );

		// Just to be safe make sure the old section exists
		if( itr != m_pIniFile->m_sections.end() )
			m_pIniFile->m_sections.erase(itr);

		// Set the new map entry we know should not exist
		m_pIniFile->m_sections[sSectionName] = this;

		// Set the new internal section name..
		m_sSectionName = sSectionName;

		return true;
	}
	else
	{
#ifdef _INIFILE_DEBUG
		std::cout <<  "Section existed could not rename" << std::endl;
#endif
		return false;
	}
}

std::string IniSectionA::GetSectionName() const
{
#ifdef _INIFILE_DEBUG
	std::cout <<  "IniSectionA::GetSectionName()" << std::endl;
#endif
	return m_sSectionName;
}

const KeyMapA& IniSectionA::GetKeys() const
{
#ifdef _INIFILE_DEBUG
	std::cout <<  "IniSectionA::GetKeys()" << std::endl;
#endif
	return m_keys;
}

std::string IniSectionA::GetKeyValue( std::string sKey ) const
{
#ifdef _INIFILE_DEBUG
	std::cout <<  "IniSectionA::GetKeyValue()" << std::endl;
#endif
	std::string sValue;
	IniKeyA* pKey = GetKey( sKey );
	if( pKey )
	{
		sValue = pKey->GetValue();
	}
	return sValue;
}

void IniSectionA::SetKeyValue( std::string sKey, std::string sValue )
{
#ifdef _INIFILE_DEBUG
	std::cout <<  "IniSectionA::SetKeyValue()" << std::endl;
#endif
	IniKeyA* pKey = AddKey( sKey );
	if( pKey )
	{
		pKey->SetValue( sValue );
	}
}

// IniSectionA function end here

// IniKeyA Functions Start Here

IniKeyA::IniKeyA( IniSectionA* pSection , std::string sKeyName ) : m_pSection(pSection)
{
#ifdef _INIFILE_DEBUG
	std::cout <<  "IniKeyA::IniKeyA()" << std::endl;
#endif
	// Not trimmed since the parent trims for us
	m_sKeyName = sKeyName;
}


IniKeyA::~IniKeyA()
{
#ifdef _INIFILE_DEBUG
	std::cout <<  "IniKeyA::~IniKeyA()" << std::endl;
#endif
}

void IniKeyA::SetValue( std::string sValue )
{
#ifdef _INIFILE_DEBUG
	std::cout << "IniKeyA::SetValue()" << std::endl;
#endif
	m_sValue = sValue;
}

std::string IniKeyA::GetValue() const
{
#ifdef _INIFILE_DEBUG
	std::cout << "IniKeyA::GetValue()" << std::endl;
#endif
	return m_sValue;
}

bool IniKeyA::SetKeyName( std::string sKeyName )
{
#ifdef _INIFILE_DEBUG
	std::cout << "IniKeyA::SetKeyName()" << std::endl;
#endif
	Trim( sKeyName );
	// Check for key name conflict
	if( m_pSection->m_keys.find( sKeyName ) == m_pSection->m_keys.end() )
	{

		KeyMapA::iterator itr = m_pSection->m_keys.find( m_sKeyName );
		// Find the old map entry and remove it
		if( itr != m_pSection->m_keys.end() )
			m_pSection->m_keys.erase( itr );

		// Make the new map entry
		m_pSection->m_keys[sKeyName] = this;

		m_sKeyName = sKeyName;

		return true;
	}
	else
	{
#ifdef _INIFILE_DEBUG
		std::cout << "Could not set key name, key by that name already exists!" << std::endl;
#endif
		return false;
	}
}

std::string IniKeyA::GetKeyName() const
{
#ifdef _INIFILE_DEBUG
	std::cout << "IniKeyA::GetKeyName()" << std::endl;
#endif
	return m_sKeyName;
}

// End of IniKeyA Functions

}
