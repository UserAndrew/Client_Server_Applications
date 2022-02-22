#include "Observer.h"

std::string Observer::Update(std::string message_from_subject)
{
	/*ULONG size_data_original = 1024;
	ULONG size_data_uncompressed = size_data_original;
	BYTE* data_uncompressed = (BYTE*)malloc(size_data_uncompressed);
	BYTE* data_read_in_compressed = (BYTE*)malloc(size_data_uncompressed);
	fillDataCompressed(message_from_subject, data_read_in_compressed);
	int z_result = uncompress(data_uncompressed, &size_data_uncompressed, 
		data_read_in_compressed, strlen((char*)data_read_in_compressed));
	printResultUncompressing(z_result);
	std::string final_string((char*)data_uncompressed);
	m_message_from_subject = final_string;
	free(data_uncompressed);
	free(data_read_in_compressed);*/
	std::string umcompress_data = Gzip::decompress(message_from_subject);
	std::cout << umcompress_data;
	return umcompress_data;
}

/*std::string Observer::Update(std::string message_from_subject)
{
	char arr_in[128];
	char arr_out[128];

	strcpy(arr_in, message_from_subject.c_str());

	z_stream infstream;
	infstream.zalloc = Z_NULL;
	infstream.zfree = Z_NULL;
	infstream.opaque = Z_NULL;

	infstream.avail_out = (uInt)sizeof(arr_out);
	infstream.next_out = (Bytef*)arr_out;
	infstream.avail_in = (uInt)((char*)infstream.next_out - arr_in); // size of input
	infstream.next_in = (Bytef*)arr_in; // input char array
	//infstream.avail_out = (uInt)sizeof(arr_out); // size of output
	//infstream.next_out = (Bytef*)arr_out; // output char array

	// the actual DE-compression work.
	inflateInit(&infstream);
	inflate(&infstream, Z_NO_FLUSH);
	inflateEnd(&infstream);

	std::string result(arr_out);
	std::cout << result << std::endl;
	return result;
}*/

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

void Observer::fillDataCompressed(std::string str, BYTE* data)
{
	char* this_data = (char*)data;
	for (int i = 0; i < str.size(), i++;)
	{
		this_data[i] = str[i];
	}
}