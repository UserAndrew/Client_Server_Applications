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
	return my_string;//gag
}