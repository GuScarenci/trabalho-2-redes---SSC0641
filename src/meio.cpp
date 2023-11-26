#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <cmath>

#include "../include/meio.h"
#include "../include/receptor.h"
#include "../include/helper.h"

void MeioDeComunicacao(std::vector<int> fluxoBrutoDeBits)
{
    printTag("Meio de Comunicação: \n\n");

    std::cout<<"Possíveis erros aparecem aqui!"<<std::endl<<std::endl;

    int porcentagemDeErros = 1; // 10%, 20%,30%,40%,...,100%
    std::vector<int> fluxoBrutoDeBitsPontoA, fluxoBrutoDeBitsPontoB;

    fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;

    int i = 0;
    while (i < fluxoBrutoDeBits.size())
    {

        /*MENINA
        if ((rand() % 100) >= porcentagemDeErros / fluxoBrutoDeBits.size())
        {                                                                // fazer a probabilidade do erro
            fluxoBrutoDeBitsPontoB.push_back(fluxoBrutoDeBitsPontoA[i]); // BITS!!!
        }
        else
        { // ERRO! INVERTER (usa condição ternária)
            fluxoBrutoDeBitsPontoA[i] == 0 ? fluxoBrutoDeBitsPontoB.push_back(fluxoBrutoDeBitsPontoA[i] + 1) : fluxoBrutoDeBitsPontoB.push_back(fluxoBrutoDeBitsPontoA[i] - 1);
        } // fim do if
        */

       if ((rand() % 100 + 1) >= porcentagemDeErros){
            fluxoBrutoDeBitsPontoB.push_back(fluxoBrutoDeBitsPontoA[i]);
        } else{
            fluxoBrutoDeBitsPontoA[i] == 0 ? fluxoBrutoDeBitsPontoB.push_back(1) : fluxoBrutoDeBitsPontoB.push_back(0);
        }

        i++;
    } // fim do while
    CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB);   
} // fim do metodo meioDeComunicacao