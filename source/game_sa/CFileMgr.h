/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"

#define FILESTREAM int

#define DIRNAMELENGTH 128

class  CFileMgr
{
public:
	// variables
	// length: 128
	static char *ms_dirName;
	// length: 128
	static char *ms_rootDirName;
	// functions
	static void Initialise();
	static int ChangeDir(const char *path);
	static int SetDir(const char *path);
	static int SetDirMyDocuments();
	static int LoadFile(const char *path, unsigned char *buf, int size, const char *mode);
	static FILESTREAM OpenFile(const char *path, const char *mode);
	static FILESTREAM OpenFileForWriting(const char *path);
	static FILESTREAM OpenFileForAppending(const char *path);
	static int Read(FILESTREAM file, char *buf, int size);
	static int Write(FILESTREAM file, char *buf, int size);
	static char Seek(FILESTREAM file, int offset, int origin);
	static char ReadLine(FILESTREAM file, char *str, int num);
	static int CloseFile(FILESTREAM file);
	static int GetFileLength(FILESTREAM file);
	static int Tell(FILESTREAM file);
	static bool GetErrorReadWrite(FILESTREAM file);
};