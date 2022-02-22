#include "Decorator.h"

std::string Decorator::messageProcessing(std::string my_string, std::string& flag_string)
{
	std::cout << "Called Decorator" << std::endl;
	flag_string.append("");
	return this->m_iclient->messageProcessing(my_string, flag_string);
}

std::string HashSumDecorator::messageProcessing(std::string my_string, std::string& flag_string)
{
	std::cout << "Called HashSumDecorator" << std::endl;
	flag_string.append("h");
	hashwrapper* myWrapper = new md5wrapper();
	std::string hash_string;
	std::string separator;
	getSymbol(separator);
	try
	{
		hash_string = myWrapper->getHashFromString(my_string);
	}
	catch (hlException& e)
	{
		//your error handling here
		std::cerr << "Error("
			<< e.error_number()
			<< "): "
			<< e.error_message()
			<< std::endl;
	}


	std::string result_string = Decorator::messageProcessing(my_string, flag_string) + hash_string + separator;
	delete myWrapper;
	myWrapper = NULL;
	//std::string result = std::to_string(GetCurrentProcessId());
	//std::string result_string = Decorator::messageProcessing(my_string, flag_string) + result + separator;
	return result_string;
}

std::string CompressDecorator::messageProcessing(std::string my_string, std::string& flag_string)
{
	std::cout << "Called CompressDecorator" << std::endl;
	flag_string.append("z");
	/*int size_data_original = my_string.size();
	BYTE* data_original = (BYTE*)malloc(size_data_original);
	fillDataOriginal(data_original, my_string);
	ULONG size_data_compressed = (size_data_original * 1.1) + 12;
	BYTE* data_compressed = (BYTE*)malloc(size_data_compressed);
	int z_result = compress(data_compressed, &size_data_compressed, data_original, \
		size_data_original);
	printResultCompressing(z_result);
	std::string str_result((char*)data_compressed);
	free(data_original);
	free(data_compressed);
	return Decorator::messageProcessing(str_result, flag_string);*/
	std::string tmp = Decorator::messageProcessing(my_string, flag_string);
	std::string str_result = Gzip::compress(tmp);
	return str_result;
}

/*std::string CompressDecorator::messageProcessing(std::string my_string, std::string& flag_string)
{
	std::cout << "Called CompressDecorator" << std::endl;
	flag_string.append("z");
	/*char arr_in[128];
	char arr_out[128];

	strcpy(arr_in, my_string.c_str());

	z_stream defstream;
	defstream.zalloc = Z_NULL;
	defstream.zfree = Z_NULL;
	defstream.opaque = Z_NULL;

	defstream.avail_in = (uInt)strlen(arr_in) + 1; 
	defstream.next_in = (Bytef*)arr_in; 
	defstream.avail_out = (uInt)sizeof(arr_out); 
	defstream.next_out = (Bytef*)arr_out; 

	deflateInit(&defstream, Z_BEST_COMPRESSION);
	deflate(&defstream, Z_FINISH);
	deflateEnd(&defstream);

	std::string result(arr_out);
	std::string separator;
	getSymbol(separator);
	std::string result = std::to_string(GetCurrentProcessId()) + separator + Decorator::messageProcessing(my_string, flag_string);
	return result;
}*/

void CompressDecorator::fillDataOriginal(BYTE* data, std::string my_string)
{
	char* this_data = (char*)data;
	for (size_t i = 0; i < my_string.size(); i++)
	{
		this_data[i] = my_string[i];
	}
}

void CompressDecorator::printResultCompressing(int result)
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

std::string CommandMessageProcessingDecorator::messageProcessing(std::string _string, std::string& flag_string)
{
	return _string;
}



std::string SizeDataDecorator::messageProcessing(std::string _string, std::string& flag_string)
{
	return _string;
}