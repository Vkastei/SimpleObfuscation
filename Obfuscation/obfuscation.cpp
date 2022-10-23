#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#define LIMITER "


std::vector<std::string> newLines;
std::vector<std::string> functions;
std::vector<std::string> obfFunctions;
std::string encrypt(std::string str){
    std::string newstr;
    for(char c : str){
        c++;
        newstr += c;
    }

    return newstr;
    
}
void obfuscate(std::string fileName){
    
    std::ifstream startFile(fileName);
    std::ofstream obfFile("obf_file.cpp");
    
    //loop through lines
    std::string result;
    for(std::string line; std::getline(startFile, line);){
        int i = 0;
        
        std::string::size_type start_position = 0;
        std::string::size_type end_position = 0;
        std::string found_text;
        start_position = line.find("\"");
        //string obfuscation
        if(start_position != std::string::npos){
            ++start_position;

            end_position = line.find("\";");
            if(end_position != std::string::npos){
                found_text = line.substr(start_position, end_position - start_position);
                std::cout << found_text << std::endl;
                std::string newstr;
                for(char c : found_text){
                    c++;
                    newstr+=c;    
                    
                }
                newLines.push_back(newstr);
                found_text = "";
            }
        //function obfuscation
        }else if(line.find("void") != std::string::npos){
            std::string::size_type startPos = line.find("void") + 5;

            std::string::size_type endPos = line.find("(");
            std::string newVoid;
            if(endPos != std::string::npos){
                newVoid = line.substr(startPos, endPos - startPos);
                
                if(std::find(functions.begin(), functions.end(), newVoid) != functions.end()){
                    
                }
                functions.push_back(newVoid);

                std::string obfString;
                for(char c : newVoid){
                    c++;
                    obfString += c;
                }
                newLines.push_back(obfString);
                obfFunctions.push_back(obfString);

            }
            
            
        }
        result += line + "\n";
    }
    std::cout << result;


}
int main(){
    
    std::string fileName;
    std::cout << "File to obfuscate: " << std::endl;
    std::cin >> fileName;

    
    obfuscate(fileName);


}
