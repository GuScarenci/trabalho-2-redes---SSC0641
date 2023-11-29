#include <iostream>

#include "../include/helper.h"
#include "../include/transmissor.h"

/*Seta as variáveis globais da porcentagem de erros do meio de comunicação, do tipo de enquadramento e do tipo de controle de erros.*/
void config(){

    std::cout<<BOLD<<"Qual a porcentagem de erros do meio de comunicação?"<<RESETS<<std::endl<<"Número inteiro entre 0 e 100: 0 para 0\% de erro e 100 para 100\% de erro!"<<std::endl<<std::endl;
    std::cin>>porcentagemDeErros;
    std::cout<<std::endl;

    std::cout<<BOLD<<"Qual vai ser o modo de enquadramento?"<<RESETS<<std::endl<<"0 para contagem de caracteres e 1 para inserção de bytes"<<std::endl<<std::endl;
    std::cin>>enquadramento;
    std::cout<<std::endl;

    std::cout<<BOLD<<"Qual vai ser o modo de detecção de erros?"<<RESETS<<std::endl<<"0 para bit de paridade par, 1 para bit de paridade impar e 2 para CRC IEEE-802"<<std::endl<<std::endl;
    std::cin>>tipoDeControleDeErro;
    std::cout<<std::endl;

    std::cin.get();
}

int main(void)
{   
    printTag("\nInício:\n\n");

    config();

    AplicacaoTransmissora();
}

