#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <cmath>

#include "../include/transmissor.h"
#include "../include/meio.h"


void AplicacaoTransmissora(void)
{
    std::string mensagem;
    std::cout << "Digite uma mensagem:" << std::endl;
    getline(std::cin, mensagem);

    // Chama a proxima camada
    CamadaDeAplicacaoTransmissora(mensagem); // em um exemplo mais realistico, aqui seria dado um SEND do SO(?)

} // fim do metodo aplicacaoTransmissora

void CamadaDeAplicacaoTransmissora(std::string mensagem)
{
    std::vector<int> quadro = ConvertToBits(mensagem); // trabalhar com bits!!!

    //printa o quadro
    for (int i = 0; i < quadro.size(); ++i)
    {
        std::cout << quadro[i] << " ";
    }

    // chama a proxima camada
    CamadaEnlaceDadosTransmissora(quadro);
}

//TODO: entender um pouco mais  e implementar sem cópia
std::vector<int> ConvertToBits(std::string mensagem)
{
    int i = 0, j = 0;
    std::vector<int> quadro;

    for (i = 0; i < mensagem.size(); i++)
    {
        std::bitset<8> set(mensagem[i]);
        if (mensagem[i] == ' ')
        {
            // um espaço vazio teve que virar um caso especial
            set.reset();   // todos são zero
            set.set(5, 1); // 32 == espaço
        }

        for (j = 7; j >= 0; j--)
        {
            if (set.test(j))
            {
                quadro.push_back(1);
            }
            else
            {
                quadro.push_back(0);
            }
        }
    }
    return quadro;
}

//TODO:
void CamadaEnlaceDadosTransmissora(std::vector<int> quadro)
{   
    std::vector<int> quadroEnquadrado = CamadaEnlaceDadosTransmissoraEnquadramento(quadro);
    std::vector<int> quadroCorrigido = CamadaEnlaceDadosTransmissoraControleDeErro(quadroEnquadrado);

    // chama proxima camada
    CamadaFisicaTransmissora(quadroCorrigido);

} // fim do metodo camadaEnlaceDadosTransmissora

//TODO: implementar enquadramento
std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramento(std::vector<int> quadro){
    return quadro;
}

//TODO: implementar correção de erros
std::vector<int> CamadaEnlaceDadosTransmissoraControleDeErro(std::vector<int> quadro)
{
    int tipoDeControleDeErro = 0; // alterar de acordo com o teste

    std::vector<int> controleErro;

    switch (tipoDeControleDeErro)
    {
    case 0: // bit de paridade par
        controleErro = CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(quadro);
        break;
    case 1: // bit de paridade impar
        controleErro = CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(quadro);
        break;
    case 2: // CRC
        controleErro = CamadaEnlaceDadosTransmissoraControleDeErroCRC(quadro);
        break;
    } // fim do switch/case

    return controleErro;
} // fim dp metodo camadaEnlaceDadosTransmissoraControleDeErro

//TODO:
std::vector<int> CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(std::vector<int> quadro)
{
    // implementacao do algoritimo
} // fim do metodo camadaEnlaceDadosTransmissoraControleDeErroBitParidadePar

//TODO:
std::vector<int> CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(std::vector<int> quadro)
{
    // implementacao do algoritimo
} // fim do metodo CamadaEnlaceDadosTranmissoraControleErroBitParidadeImpar

//TODO:
std::vector<int> CamadaEnlaceDadosTransmissoraControleDeErroCRC(std::vector<int> quadro)
{
    // implementacao do algoritmo
    // usar polinomio CRC-32(IEEE 802)
} // fim do metodo CamadaEnlaceDAdosTransmissoraControleDeErroCRC

void CamadaFisicaTransmissora(std::vector<int> quadro)
{
    MeioDeComunicacao(quadro);
}