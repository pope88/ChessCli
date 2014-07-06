#ifndef SYSTEM_ERR_H
#define SYSTEM_ERR_H

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Config.h>
#include <ostream>


namespace System
{
////////////////////////////////////////////////////////////
/// \brief Standard stream used by library to output warnings and errors
///
////////////////////////////////////////////////////////////
	std::ostream& Err();

} // namespace System


#endif // SYSTEM_ERR_H


////////////////////////////////////////////////////////////
/// \fn System::Err
/// \ingroup system
///
/// By default, System::Err() outputs to the same location as std::cerr,
/// (-> the stderr descriptor) which is the console if there's
/// one available.
///
/// It is a standard std::ostream instance, so it supports all the
/// insertion operations defined by the STL
/// (operator <<, manipulators, etc.).
///
/// System::Err() can be redirected to write to another output, independantly
/// of std::cerr, by using the rdbuf() function provided by the
/// std::ostream class.
///
/// Example:
/// \code
/// // Redirect to a file
/// std::ofstream file("system-log.txt");
/// std::streambuf* previous = System::Err().rdbuf(file.rdbuf());
///
/// // Redirect to nothing
/// System::Err().rdbuf(NULL);
///
/// // Restore the original output
/// System::Err().rdbuf(previous);
/// \endcode
///
////////////////////////////////////////////////////////////
