#include <iostream> //TODO: ME REMOVA
#include <string> //TODO: ME REMOVA
#include <vector> //TODO: ME REMOVA

#include "../include/camadaEnlace.h"

//TODO: ME REMOVA!
void teste(){
    std::string mensagem;
    std::cout << "Digite uma mensagem:" << std::endl;
    getline(std::cin, mensagem);

    std::vector<int> quadro = ConvertToBits(mensagem);

    for (int i = 0; i < quadro.size(); ++i)
    {
        std::cout << quadro[i] << " ";
    }

    std::string mensagem2 = DecodeToString(quadro);
    std::cout << "A mensagem recebida foi:" << mensagem2 << std::endl;
}


int main(void)
{   
    teste();

    //TODO:AplicacaoTransmissora();
} // fim do metodo main

