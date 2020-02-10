#include "ShaderFileReader.h"





std::string ShaderFileReader::readFile(const std::string t_fileName)
{
	std::ifstream inputFile;
	inputFile.open("Shaders//" + t_fileName);

	if (inputFile.is_open())
	{
		std::string fileContents;
		std::string line;


		while (std::getline(inputFile, line))
		{
			for (int character = 0; character < line.length(); character++)
			{
				if (line.at(character) == '\\' && character + 1 < line.size())
				{
					if (line.at(character + 1) == 'n')
					{
						fileContents += '\n';
					}
					else if (line.at(character + 1) == 'r')
					{
						fileContents += '\r';
					}

					character += 1;
				}
				else
				{
					fileContents += line.at(character);
				}
			}
		}

		inputFile.close();


		return fileContents;
	}

}