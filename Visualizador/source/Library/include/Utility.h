#pragma once

#include "Common.h"

namespace Library
{
	class Utility
	{
	public:
		static void SetWorkingDirectory(const std::string& dir);
		static void SetWorkingDirectoryFromArgs(char** args);
		static std::string GetWorkingDirectory();
		static std::string GetPath(const std::string& fileName);

	protected:
		static std::string mDirectory;

	private:
		Utility();
		Utility(const Utility& rhs);
		Utility& operator=(const Utility& rhs);

	};
}