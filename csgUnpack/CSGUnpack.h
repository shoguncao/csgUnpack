#ifndef __csgUnpack__CSGUnpack__
#define __csgUnpack__CSGUnpack__

#include <iostream>

static const unsigned long long MEMORY_SIZE = 512*1024*1024;

using namespace std;

struct FILE_INFO
{
	fpos_t m_cur_pos;
	fpos_t m_len;
};

struct MEMORY_DATA
{
	char *m_begin;
	unsigned long long m_len;
};

class CSGUnpack
{
public:
    CSGUnpack(string in_file_path, string out_file_path);
    ~CSGUnpack();
    
    int unpack();
    
private:
    string m_in_file_path;
    string m_out_file_path;
    FILE *m_in_fp;
    FILE *m_out_fp;
    FILE_INFO m_in_file_info;
	FILE_INFO m_out_file_info;
    MEMORY_DATA m_memory_data;
    
    int cast_rar_file();
    int prepare_data();
    void sync_bitwise_not();
    int store_data();
};

#endif
