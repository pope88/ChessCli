#ifndef _SYSTEM_FILE_H_
#define _SYSTEM_FILE_H_

namespace System {

	namespace priv
	{
		class FileImpl;
	}

	class Path;

	class File
		/// The File class provides methods for working with a file.
	{
	public:
		typedef UInt64 FileSize;

		File();
		/// Creates the file.

		File(const std::string& path);
		/// Creates the file.

		File(const char* path);
		/// Creates the file.

		File(const Path& path);
		/// Creates the file.

		File(const File& file);
		/// Copy constructor.

		virtual ~File();
		/// Destroys the file.

		File& operator = (const File& file);
		/// Assignment operator.

		File& operator = (const std::string& path);
		/// Assignment operator.

		File& operator = (const char* path);
		/// Assignment operator.

		File& operator = (const Path& path);
		/// Assignment operator.

		void swap(File& file);
		/// Swaps the file with another one.

		const std::string& path() const;
		/// Returns the path.

		bool exists() const;
		/// Returns true iff the file exists.

		bool canRead() const;
		/// Returns true iff the file is readable.

		bool canWrite() const;
		/// Returns true iff the file is writeable.

		bool isFile() const;
		/// Returns true iff the file is a regular file.

		bool isLink() const;
		/// Returns true iff the file is a symbolic link.

		bool isDirectory() const;
		/// Returns true iff the file is a directory.

		bool isDevice() const;
		/// Returns true iff the file is a device.

		bool isHidden() const;
		/// Returns true if the file is hidden.
		///
		/// On Windows platforms, the file's hidden
		/// attribute is set for this to be true.
		///
		/// On Unix platforms, the file name must
		/// begin with a period for this to be true.

		UInt64 created() const;
		/// Returns the creation date of the file.
		///
		/// Not all platforms or filesystems (e.g. Linux and most Unix
		/// platforms with the exception of FreeBSD and Mac OS X)
		/// maintain the creation date of a file.
		/// On such platforms, created() returns
		/// the time of the last inode modification.

		UInt64 getLastModified() const;
		/// Returns the modification date of the file.

		void setLastModified(UInt64 ts);
		/// Sets the modification date of the file.

		FileSize getSize() const;
		/// Returns the size of the file in bytes.

		void setSize(FileSize size);
		/// Sets the size of the file in bytes. Can be used
		/// to truncate a file.

		void setWriteable(bool flag = true);
		/// Makes the file writeable (if flag is true), or
		/// non-writeable (if flag is false) by setting the
		/// file's flags in the filesystem accordingly.

		void setReadOnly(bool flag = true);
		/// Makes the file non-writeable (if flag is true), or
		/// writeable (if flag is false) by setting the
		/// file's flags in the filesystem accordingly.

		void setExecutable(bool flag = true);
		/// Makes the file executable (if flag is true), or
		/// non-executable (if flag is false) by setting
		/// the file's permission bits accordingly.
		///
		/// Does nothing on Windows and OpenVMS.	

		void copyTo(const std::string& path) const;
		/// Copies the file (or directory) to the given path. 
		/// The target path can be a directory.
		///
		/// A directory is copied recursively.

		void moveTo(const std::string& path);
		/// Copies the file (or directory) to the given path and 
		/// removes the original file. The target path can be a directory.

		void renameTo(const std::string& path);
		/// Renames the file to the new name.

		void remove(bool recursive = false);
		/// Deletes the file. If recursive is true and the
		/// file is a directory, recursively deletes all
		/// files in the directory.

		bool createFile();
		/// Creates a new, empty file in an atomic operation.
		/// Returns true if the file has been created and false
		/// if the file already exists. Throws an exception if
		/// an error occurs.

		bool createDirectory();
		/// Creates a directory. Returns true if the directory
		/// has been created and false if it already exists.
		/// Throws an exception if an error occurs.

		void createDirectories();
		/// Creates a directory (and all parent directories
		/// if necessary).

		void list(std::vector<std::string>& files) const;
		/// Fills the vector with the names of all
		/// files in the directory.

		void list(std::vector<File>& files) const;
		/// Fills the vector with the names of all
		/// files in the directory.

		bool operator == (const File& file) const;
		bool operator != (const File& file) const;
		bool operator <  (const File& file) const;
		bool operator <= (const File& file) const;
		bool operator >  (const File& file) const;
		bool operator >= (const File& file) const;

		static void handleLastError(const std::string& path);
		/// For internal use only. Throws an appropriate
		/// exception for the last file-related error.

	protected:
		void copyDirectory(const std::string& path) const;
		/// Copies a directory. Used internally by copyTo().

	private:
		priv::FileImpl * impl;
	};

} // namespace System

#endif // _SYSTEM_FILE_H_
