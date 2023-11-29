#ifndef HELPER_H
#define HELPER_H

#include <vector>
#include <string>

/*Variáveis para customizar o output do console*/
const std::string GREEN = "\033[32m";
const std::string RESETC = "\033[0m";
const std::string BOLD = "\033[1m";
const std::string RESETS = "\033[0m";

/*Variáveis globais da porcentagem de erros do meio de comunicação, do tipo de enquadramento e do tipo de controle de erro da aplicação transmissora e receptora*/
extern int porcentagemDeErros;
extern int enquadramento;
extern int tipoDeControleDeErro;

/*Usado para imprimir os quadros da aplicação. Função que recebe um vector de inteiro e o imprime.*/
void printQuadro(std::vector<int>quadro);

/*Usado para textos customizados, principalmente títulos, para melhor visualização no console.*/
void printTag(std::string str);

#endif //HELPER_H