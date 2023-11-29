#include <vector>
#include <iostream>
#include <string>

#include "../include/helper.h"

/*Variáveis globais da porcentagem de erros do meio de comunicação, do tipo de enquadramento e do tipo de controle de erro da aplicação transmissora e receptora*/
int porcentagemDeErros = 0;
int enquadramento = 0;
int tipoDeControleDeErro = 0;

/*Usado para imprimir os quadros da aplicação. Função que recebe um vector de inteiro e o imprime.*/
void printQuadro(std::vector<int>quadro){
    for (int i = 0; i < quadro.size(); ++i)
    {
        std::cout << quadro[i] << " ";
    }
    std::cout<<std::endl<<std::endl;
}

/*Usado para textos customizados, principalmente títulos, para melhor visualização no console.*/
void printTag(std::string str){
    std::cout << GREEN << BOLD << str << RESETC << RESETS;
}