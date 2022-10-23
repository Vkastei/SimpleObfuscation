#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#define LIMITER "


std::vector<std::string> newLines;
std::vector<std::string> functions;
std::vector<std::string> obfFunctions;
std::vector<std::string> functionTypes;
std::vector<std::string> variables;
std::string result;
std::string endResult;
std::string encrypt(std::string str){
    std::string newstr;
    for(char c : str){
 
        if(c != ';' && c != '<' && c != '>' && c != ' ' && c != '=' && c != '\'' && c!= '\"'){
            c += 5;
            newstr += c;
        
        }
    }


    return newstr;
    
}
void obfuscate(std::string fileName){
    
    std::ifstream startFile(fileName);
    
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
            std::string::size_type endpos2 = line.find("\" ");
            if(end_position != std::string::npos){
                found_text = line.substr(start_position, end_position - start_position);
                variables.push_back(found_text);
                std::cout << found_text << std::endl;
                std::string newstr = encrypt(found_text);
                line.replace(line.find(found_text), found_text.length(), newstr);
                
                found_text = "";
            }else if(endpos2 != std::string::npos){
                found_text = line.substr(start_position, endpos2 - start_position);
                std::cout << found_text << std::endl;
                variables.push_back(found_text);
                std::string newstr = encrypt(found_text);
                    
          
                line.replace(line.find(found_text), found_text.length(), newstr);
                
                found_text = "";
            }
        //find functions
        
        }else{

            newLines.push_back(line);
        } 
        for(std::string type : functionTypes){
            
            if(line.find(type) != std::string::npos && line.find("main") == std::string::npos){
                std::string::size_type startPos = line.find(type) + type.length() + 1;
                std::string::size_type endPos = line.find("(");
                std::string::size_type endPos2 = line.find(" ");
                std::string newVoid;
                if(endPos != std::string::npos){
                    newVoid = line.substr(startPos, endPos - startPos);
                    functions.push_back(newVoid);
                }else if(endPos2 != std::string::npos){
                    newVoid = line.substr(startPos, endPos2 -startPos);
                    functions.push_back(newVoid);
                }
            }
        }
            
        //obfuscate every function
        for(std::string s : functions){

            if(line.find(s) != std::string::npos){
                std::string newStr = encrypt(s);
            
                line.replace(line.find(s), newStr.length(), newStr);
                newLines.push_back(line);
                obfFunctions.push_back(newStr);
            }
        }
        //obfuscate every variable
        for(std::string s : variables){
            if(line.find(s) != std::string::npos){
                std::string newStr = encrypt(s);
                line.replace(line.find(s), newStr.length(), newStr);
                newLines.push_back(line);
                
            }
        }
        //remove spaces, \n's
        std::string space = "";
        
        int pos;
        if((pos = line.find('\n')) != std::string::npos) {
            line.erase(pos);
        }
        if(line.find("#") != std::string::npos){
            std::cout << "aaaaaaaaaa" << std::endl;
            line += "\n";
        }
        int pos2;
        while((pos2 = line.find("  ")) != std::string::npos){
            line.replace(pos2, 2, "");
        }

        //encrypt commands
        int pos3;
        if((pos3 = line.find("//")) != std::string::npos){
            std::string nStr = line.erase(0, 2);
            line = "/*" + encrypt(nStr) + "*/";
        }
        result += line;
    }
    
        
    std::cout << result;


}

void addTypes(){
    functionTypes.push_back("std::string");
    functionTypes.push_back("int");
    functionTypes.push_back("void");

    

}
void write_to_new_file(std::string filename){
    std::ofstream file("obf_" +filename);
    file.clear();
    file << result;
}
int main(){
    
    std::string fileName;
    std::cout << "File to obfuscate: " << std::endl;
    std::cin >> fileName;

    addTypes();
    obfuscate(fileName);
    write_to_new_file(fileName);

}
