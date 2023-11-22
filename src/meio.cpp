#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <cmath>

#include "../include/meio.h"
#include "../include/receptor.h"

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