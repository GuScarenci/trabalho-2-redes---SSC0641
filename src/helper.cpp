#include <vector>
#include <iostream>
#include <string>

#include "../include/helper.h"

void printQuadro(std::vector<int>quadro){
    for (int i = 0; i < quadro.size(); ++i)
    {
        std::cout << quadro[i] << " ";
    }
    std::cout<<std::endl<<std::endl;
}

void printTag(std::string str){
    std::cout << GREEN << BOLD << str << RESETC << RESETS;
}