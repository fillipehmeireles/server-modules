#include <iostream>
#include <string>
#include <fstream>


#define MAXLINES 100

std::string *readf(std::string filename);

int main(int argc, char *argv[])
{
	if(argc < 2) 
	{
		std::cerr << "Please provide a filename." << std::endl;
		return 1;
	}

	std::string filename = argv[1];

	std::string *file_lines = readf(filename);

	for(int i = 0; i < sizeof(file_lines); i++)
	{
		if(!(file_lines[i] == "")){
			std::cout << file_lines[i] << std::endl;
		}
	} 

	return 0;
}

std::string *readf(std::string filename) 
{
	std::ifstream FileReader (filename);
	std::string file_line_reader;

	std::string *file_descr = new std::string[MAXLINES];
	int i = 0;

	while(getline(FileReader, file_line_reader))
	{
		std::cout << file_line_reader << std::endl;
		file_descr[i] = file_line_reader;
		i++;
	}
	
	FileReader.close();
	return file_descr;
}