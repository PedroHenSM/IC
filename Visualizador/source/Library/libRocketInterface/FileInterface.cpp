#include <FileInterface.h>
#include <stdio.h>

#include "Utility.h"
using namespace Library;

RendererFileInterface::RendererFileInterface()
{
}

RendererFileInterface::~RendererFileInterface()
{
}

// Opens a file.
Rocket::Core::FileHandle RendererFileInterface::Open(const Rocket::Core::String& path)
{
	// Attempt to open the file relative to the application's root.
	std::string fullPath = Utility::GetPath(path.CString());
	FILE* fp = fopen(fullPath.c_str(), "rb");
	if (fp != NULL)
		return (Rocket::Core::FileHandle) fp;

	// Attempt to open the file relative to the current working directory.
	fp = fopen(path.CString(), "rb");
	return (Rocket::Core::FileHandle) fp;
}

// Closes a previously opened file.
void RendererFileInterface::Close(Rocket::Core::FileHandle file)
{
	fclose((FILE*) file);
}

// Reads data from a previously opened file.
size_t RendererFileInterface::Read(void* buffer, size_t size, Rocket::Core::FileHandle file)
{
	return fread(buffer, 1, size, (FILE*) file);
}

// Seeks to a point in a previously opened file.
bool RendererFileInterface::Seek(Rocket::Core::FileHandle file, long offset, int origin)
{
	return fseek((FILE*) file, offset, origin) == 0;
}

// Returns the current position of the file pointer.
size_t RendererFileInterface::Tell(Rocket::Core::FileHandle file)
{
	return ftell((FILE*) file);
}
