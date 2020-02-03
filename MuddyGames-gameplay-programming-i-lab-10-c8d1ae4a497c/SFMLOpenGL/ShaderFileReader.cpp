#include "ShaderFileReader.h"


// ------------------------------------------------------------------------------------- REWORD, ESPECIALLY COMMENTS


std::string ShaderFileReader::readFile(const std::string t_fileName)
{
	std::ifstream inputFile; // Create the file pointer
	inputFile.open("Shaders//" + t_fileName); // Open the file

	if (inputFile.is_open()) // Check that the file has opened successfully
	{
		std::string fileContents;
		std::string line; // Holds one line of data

		// Loop while getting lines add the contents string
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

	//----------------------------------------------------------------- remove
	else
	{
		throw(std::exception{ "can't open shader file." });
	}
}