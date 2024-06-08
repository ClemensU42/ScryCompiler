#include <iostream>
#include <sstream>
#include <getopt.h>
#include <fstream>

#include "lexer.h"
#include "consoleColors.h"

int main(int argc, char** argv) {

	std::string inputFilePath, outputFilePath;

	int c;
	while((c = getopt(argc, argv, "i:o:")) != -1){
		switch (c) {
			case 'i':
				inputFilePath = optarg;
				break;
			case 'o':
				outputFilePath = optarg;
				break;
			case '?':
				switch (optopt) {
					case 'i':
					case 'o':
						std::cerr << RED << "Option -" << static_cast<char>(optopt) << " requires an argument." << RESET << std::endl;
						break;
					default:
						if (isprint(optopt))
							std::cerr << RED << "unknown option '-" << static_cast<char>(optopt) << "'." << RESET << std::endl;
						else
							std::cerr << RED << "Unknown option character " << static_cast<char>(optopt) << RESET << std::endl;
						break;
					return 1;
				}
			default:
				abort();
		}
	}

	if(inputFilePath.empty()){
		std::cerr << "\033[1;31m" << "Missing input file!" << RESET << std::endl;
		return 0;
	}

	if(outputFilePath.empty()){
		std::cerr << "\033[1;31m" << "Missing output file!" << RESET << std::endl;
		// return 0;
	}

	std::ifstream inputFileStream(inputFilePath);
	if(!inputFileStream.is_open()){
		std::cerr << "\033[1;31m" << "Error opening file '" << inputFilePath << "'." << RESET << std::endl;
		return 0;
	}

	std::stringstream inputBuffer;
	inputBuffer << inputFileStream.rdbuf();
	std::cout << inputBuffer.str() << std::endl;

	std::vector<lexer::Token> tokens = lexer::ParseStringToTokens(inputBuffer.str());
	std::cout << std::flush;
	std::cout << "token amount: " << tokens.size() << std::endl;
	for(const lexer::Token& token : tokens)
		std::cout << token.tokenContent << '\n';
	std::cout << std::flush;

    return 0;
}
