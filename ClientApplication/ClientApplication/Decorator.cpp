#include "Decorator.h"
#include "getSymbol.h"

std::string Decorator::messageProcessing(std::string my_string)
{
	return m_iclient->messageProcessing(my_string);
}

std::string HashSumDecorator::messageProcessing(std::string my_string)
{
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

	std::string result_string = Decorator::messageProcessing(my_string) + hash_string + separator;
	delete myWrapper;
	myWrapper = NULL;
	return result_string;
}

std::string CompressDecorator::messageProcessing(std::string my_string)
{
	int size_data_original = my_string.size();
	BYTE* data_original = (BYTE*)malloc(size_data_original);
	fillDataOriginal(data_original, my_string);
	ULONG size_data_compressed = (size_data_original * 1.1) + 12;
	BYTE* data_compressed = (BYTE*)malloc(size_data_compressed);
	int z_result = compress(data_compressed, &size_data_compressed, data_original, \
		size_data_original);
	printResultCompressing(z_result);
	std::string str_result((char*)data_original);
	return str_result;
}

void CompressDecorator::fillDataOriginal(BYTE* data, std::string my_string)
{
	char* this_data = (char*)data;
	for (int i = 0; i < my_string.size(), i++;)
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