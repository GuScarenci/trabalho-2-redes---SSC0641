#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <cmath>

#include "../include/camadaEnlace.h"

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

// TODO:
void CamadaEnlaceDadosTransmissora(std::vector<int> quadro)
{
    std::vector<int> quadroCorrigido = CamadaEnlaceDadosTransmissoraControleDeErro(quadro);
    //TODO: CamadaEnlaceEnquadramento(???)
    
    // chama proxima camada
    CamadaFisicaTransmissora(quadroCorrigido);

} // fim do metodo camadaEnlaceDadosTransmissora

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

//TODO:
void MeioDeComunicacao(std::vector<int> fluxoBrutoDeBits)
{
    // OBS: trabalhar com BITS e não com BYTES!!!
    //TODO:
    int erro;
    std::vector<int> fluxoBrutoDeBitsPontoA, fluxoBrutoDeBitsPontoB;

    fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;

    int porcentagemDeErros = 0; // 10%, 20%,30%,40%,...,100%
    int i = 0;
    while (i < fluxoBrutoDeBits.size())
    {

        if ((rand() % 100) >= porcentagemDeErros / fluxoBrutoDeBits.size())
        {                                                                // fazer a probabilidade do erro
            fluxoBrutoDeBitsPontoB.push_back(fluxoBrutoDeBitsPontoA[i]); // BITS!!!
        }
        else
        { // ERRO! INVERTER (usa condição ternária)
            fluxoBrutoDeBitsPontoA[i] == 0 ? fluxoBrutoDeBitsPontoB.push_back(fluxoBrutoDeBitsPontoA[i] + 1) : fluxoBrutoDeBitsPontoB.push_back(fluxoBrutoDeBitsPontoA[i] - 1);
        } // fim do if
        i++;
    } // fim do while
    CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB);
    
} // fim do metodo meioDeComunicacao

void CamadaFisicaReceptora(std::vector<int> quadro)
{
    CamadaEnlaceDadosReceptora(quadro);
}

void CamadaEnlaceDadosReceptora(std::vector<int> quadro)
{
    //TODO:
    // quadro = CamadaEnlaceDadosReceptoraControleDeErro(quadro); //PRECISA MESMO?
    // quadro = CamadaEnlaceDadosReceptoraEnquadramento(quadro); //PRECISA MESMO?
    CamadaDeAplicacaoReceptora(quadro);
}

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