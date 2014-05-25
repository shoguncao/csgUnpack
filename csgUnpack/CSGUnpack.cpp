#include "CSGUnpack.h"

CSGUnpack::CSGUnpack(string in_file_path, string out_file_path)
{
    m_in_fp = NULL;
    m_out_fp = NULL;
    
    if (in_file_path == out_file_path) {
        return;
    }
    
    m_in_fp = fopen(in_file_path.c_str(), "rb");
    m_out_fp = fopen(out_file_path.c_str(), "wb");
    
    if (NULL != m_in_fp)
	{
		m_in_file_info.m_cur_pos = 0;
		fseek(m_in_fp, 0, SEEK_END);
		fgetpos(m_in_fp, &(m_in_file_info.m_len));
		fseek(m_in_fp, 0, SEEK_SET);
	}
    
	if (NULL != m_out_fp)
	{
		m_out_file_info.m_cur_pos = 0;
		m_out_file_info.m_len = 0;
		fseek(m_out_fp, 0, SEEK_SET);
	}
    
	m_memory_data.m_begin = new char[MEMORY_SIZE];
	m_memory_data.m_len = 0;
}

CSGUnpack::~CSGUnpack()
{
	if (NULL != m_in_fp)
	{
		fclose(m_in_fp);
		m_in_fp = NULL;
	}
	if (NULL != m_out_fp)
	{
		fclose(m_out_fp);
		m_out_fp = NULL;
	}
	if (NULL != m_memory_data.m_begin)
	{
		delete m_memory_data.m_begin;
	}
}

int CSGUnpack::unpack()
{
	if ((NULL == m_in_fp) || (NULL == m_out_fp))
	{
		return -1;
	}
	if (0 != cast_rar_file())
	{
		return -1;
	}
	while (0 == prepare_data())
	{
		sync_bitwise_not();
		store_data();
	}
	return 0;
}

int CSGUnpack::cast_rar_file()
{
	unsigned long long offset = 10268114;
	fseek(m_in_fp, 0, SEEK_SET);
	fseek(m_in_fp, (int)offset, SEEK_SET);
	m_in_file_info.m_cur_pos = offset;
	return 0;
}

int CSGUnpack::prepare_data()
{
	fpos_t cur_pos = m_in_file_info.m_cur_pos;
	fpos_t total_len = m_in_file_info.m_len;
	if (cur_pos >= total_len)
	{
		return -1;
	}
    
	fpos_t len = (MEMORY_SIZE < total_len-cur_pos) ? (MEMORY_SIZE) : (total_len-cur_pos);
	fread(m_memory_data.m_begin, sizeof(char), (size_t)len, m_in_fp);
	cur_pos = cur_pos+len;
	m_in_file_info.m_cur_pos = cur_pos;
	m_memory_data.m_len = len;
	return 0;
}

int CSGUnpack::store_data()
{
	fwrite(m_memory_data.m_begin, sizeof(char), (size_t)(m_memory_data.m_len), m_out_fp);
	return 0;
}

void CSGUnpack::sync_bitwise_not()
{
    char *end = m_memory_data.m_begin + m_memory_data.m_len - 1;
    for (char *p = m_memory_data.m_begin; p <= end; ++p)
    {
        *p = ~(*p);
    }
}
