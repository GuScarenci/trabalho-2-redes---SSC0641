#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <cmath>

#include "../include/receptor.h"

void CamadaFisicaReceptora(std::vector<int> quadro)
{
    CamadaEnlaceDadosReceptora(quadro);
}

void CamadaEnlaceDadosReceptora(std::vector<int> quadro)
{
    //TODO:
    std::vector<int> quadroEnquadrado = CamadaEnlaceDadosReceptoraEnquadramento(quadro);
    std::vector<int> quadroCorrigido = CamadaEnlaceDadosReceptoraControleDeErro(quadroEnquadrado); //PRECISA MESMO?
    
    CamadaDeAplicacaoReceptora(quadroEnquadrado);
}
//TODO: REPETIR TUDO O QUE FOI FEITO PARA A APLICAÇÃO TRANSMISSORA NA APLICAÇÃO RECEPTORA!

std::vector<int> CamadaEnlaceDadosReceptoraEnquadramento(std::vector<int> quadro){
    return quadro;
}

std::vector<int> CamadaEnlaceDadosReceptoraControleDeErro(std::vector<int> quadro){
    int tipoDeControleDeErro = 0;

    std::vector<int> controleErro;

    switch (tipoDeControleDeErro)
    {
    case 0: // bit de paridade par
        controleErro = CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(quadro);
        break;
    case 1: // bit de paridade impar
        controleErro = CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar(quadro);
        break;
    case 2: // CRC
        controleErro = CamadaEnlaceDadosReceptoraControleDeErroCRC(quadro);
        break;
    } // fim do switch/case

    return controleErro;   
}

//TODO:
std::vector<int> CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(std::vector<int> quadro)
{
    // implementacao do algoritimo
} // fim do metodo camadaEnlaceDadosTransmissoraControleDeErroBitParidadePar

//TODO:
std::vector<int> CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar(std::vector<int> quadro)
{
    // implementacao do algoritimo
} // fim do metodo CamadaEnlaceDadosTranmissoraControleErroBitParidadeImpar

//TODO:
std::vector<int> CamadaEnlaceDadosReceptoraControleDeErroCRC(std::vector<int> quadro)
{
    // implementacao do algoritmo
    // usar polinomio CRC-32(IEEE 802)
} // fim do metodo CamadaEnlaceDAdosTransmissoraControleDeErroCRC

void CamadaDeAplicacaoReceptora(std::vector<int> quadro)
{
    std::string mensagem = DecodeToString(quadro); // estava trabalhando com bits
    // chama proxima camada
    AplicacaoReceptora(mensagem);
} // fim do metodo camadaDeAplicacaoReceptora

std::string DecodeToString(std::vector<int> quadro)
{
    int i = 0, y = 0, j = 0;
    std::string mensagem;
    int letra = 0;
    // Pega grupo de 8 bits
    for (i = 0; i < quadro.size(); i += 8)
    {
        letra = 0;
        y = 0;
        // Ler os 8 bits e converte de binario para decimal utilizando base 2
        // e o expoente da potencia sendo o indice do bit
        for (j = i; j < (8 + i); j++)
        {
            if (quadro[j] == 1)
                letra = letra + pow(2, 7 - y);

            y++;
        }
        // Converte o valor inteiro em um caracter e concatena com a string que sera retornada
        mensagem.push_back((char)letra);
    }

    return mensagem;
}

void AplicacaoReceptora(std::string mensagem)
{
    std::cout << "A mensagem recebida foi:" << mensagem << std::endl;
} // fim do metodo aplicacaoReceptora