/***
    File IO

        - fileIO.cpp

    Author: Fillipe Meireles
    Organization: Luspew

    https://github.com/fillipehmeireles/server-modules

***/
#include <iostream>
#include <string>
#include <fstream>


#define MAXLINES 100

std::string *readf(std::string);
void writef(std::string, std::string*);
void imagecopy(std::string, std::string);
void writebinf(std::string, std::string);
std::string readbinf(std::string);

int main(int argc, char *argv[])
{
	if(argc < 2) 
	{
		std::cerr << "Please provide a filename." << std::endl;
		return 1;
	}

	std::string filename = argv[1];

	//Writing to file
	std::string* fileinfo;
	fileinfo = new std::string;

	*fileinfo = argv[2];

	writef(filename,fileinfo);

	//Reading File
	std::string *file_lines = readf(filename);

	for(size_t i = 0; i < sizeof(file_lines); i++)
	{
		if(!(file_lines[i] == "")){
			std::cout << file_lines[i] << std::endl;
		}
	} 

	// Copying a image
	imagecopy("image.jpg","copyimage.jpg");

	// Writing binary file
	writebinf(filename,"Hello World, Luspew");
	
	// Reading binary file
	readbinf(filename);

	delete fileinfo;
	return 0;
}

void writef(std::string filename, std::string *fileinfo)
{
	std::ofstream FileWriter;

	FileWriter.open(filename);

	if(!FileWriter.is_open())
	{
		perror("Could not open file");
	}

	FileWriter << *fileinfo;
	

	FileWriter.close();
}


std::string *readf(std::string filename) 
{
	std::ifstream FileReader (filename);
	std::string file_line_reader;

	if(!FileReader.is_open())
	{
		perror("Could not open file");
	}

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

void imagecopy(std::string filename, std::string copyimage)
{
	std::ofstream(copyimage, std::ios::binary) << std::ifstream(filename, std::ios::binary).rdbuf();
}

void writebinf(std::string filename, std::string fileinfo)
{
	std::ofstream OutFile;
	OutFile.open(filename, std::ios::out | std::ios::binary);
	OutFile.write(fileinfo.c_str(), fileinfo.length());
	OutFile.close();
}

std::string readbinf(std::string filename)
{
	std::ifstream File(filename);
	std::string lines;

	getline(File, lines);

	return lines;
}