#include "Observer.h"

void Observer::Update(const char* message_from_subject)
{
	ULONG size_data_original = 1024;
	ULONG size_data_uncompressed = size_data_original;
	BYTE* data_uncompressed = (BYTE*)malloc(size_data_uncompressed);
	BYTE* data_read_in_compressed = (BYTE*)malloc(size_data_uncompressed);
	fillDataCompressed(message_from_subject, data_read_in_compressed);
	int z_result = uncompress(data_uncompressed, &size_data_uncompressed, 
		data_read_in_compressed, strlen((char*)data_read_in_compressed));
	printResultUncompressing(z_result);
	std::string final_string((char*)data_uncompressed);
	m_message_from_subject = final_string;
}

void Observer::printResultUncompressing(int result)
{
	switch (result)
	{
	case Z_OK:
		printf("***** SUCCESS! *****\n");
		break;

	case Z_MEM_ERROR:
		printf("out of memory\n");
		exit(1);
		break;

	case Z_BUF_ERROR:
		printf("output buffer wasn't large enough!\n");
		exit(1);
		break;
	}
}

void Observer::RemoveMeFromTheList()
{
	m_subject.Detach(this);
}

void Observer::fillDataCompressed(const char* ch, BYTE* data)
{
	char* this_data = (char*)data;
	for (int i = 0; i < strlen(ch), i++;)
	{
		this_data[i] = ch[i];
	}
}