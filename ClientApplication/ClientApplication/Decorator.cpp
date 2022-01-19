#include "Decorator.h"

std::string Decorator::messageProcessing(std::string my_string)
{
	return this->m_iclient->messageProcessing(my_string);
}

std::string HashSumDecorator::messageProcessing(std::string my_string)
{
	hashwrapper* myWrapper = new md5wrapper();
	std::string hash_string;
	try
	{
		hash_string = myWrapper->getHashFromString(my_string);
	}
	catch (hlException& e)
	{
		//your error handling here
	}

	std::string result_string = Decorator::messageProcessing(my_string) + hash_string + ";";
	delete myWrapper;
	myWrapper = NULL;
	return result_string;
}

std::string CompressDecorator::messageProcessing(std::string my_string)
{

}