#include "Utility.h"

#include <iostream>
#include <algorithm>

namespace Library
{
	std::string Utility::mDirectory = "";

	void Utility::SetWorkingDirectory(const std::string & dir)
	{
		if (dir[dir.length() -1] == '\\' || dir[dir.length() -1] == '/')
			mDirectory = dir;
		else
			mDirectory = dir + '\\';
        std::replace(mDirectory.begin(), mDirectory.end(), '\\', '/');
	}

	void Utility::SetWorkingDirectoryFromArgs(char ** args)
	{
		std::string path(args[0]);
		int l = path.find_last_of('\\');
		// Linux
		if(l == -1)
            l = path.find_last_of('/');

		SetWorkingDirectory(path.substr(0, l).c_str());
	}

	std::string Utility::GetWorkingDirectory()
	{
		return mDirectory;
	}

	std::string Utility::GetPath(const std::string & fileName)
	{
        std::string str = mDirectory + fileName;
        //std::replace(str.begin(), str.end(), '\\', '/');
		return str;
	}


}
