#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <cmath>

#include "../include/meio.h"
#include "../include/receptor.h"
#include "../include/helper.h"

/*Simula o meio de comunicação entre a aplicação transmissora e a receptora. Alterando bits aleatóriamente baseado na porcentagem de erros.*/
void MeioDeComunicacao(std::vector<int> fluxoBrutoDeBits)
{
    printTag("Meio de Comunicação: \n\n");

    printQuadro(fluxoBrutoDeBits);

    std::cout<<"Possíveis erros aparecem aqui!"<<std::endl<<std::endl;

    std::vector<int> fluxoBrutoDeBitsPontoA, fluxoBrutoDeBitsPontoB;

    fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;

    int i = 0;
    while (i < fluxoBrutoDeBits.size())
    {

       if ((rand() % 100 + 1) >= porcentagemDeErros){
            fluxoBrutoDeBitsPontoB.push_back(fluxoBrutoDeBitsPontoA[i]);
        } else{
            fluxoBrutoDeBitsPontoA[i] == 0 ? fluxoBrutoDeBitsPontoB.push_back(1) : fluxoBrutoDeBitsPontoB.push_back(0);
        }

        i++;
    } // fim do while

    printQuadro(fluxoBrutoDeBitsPontoB);

    CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB);   
} // fim do metodo meioDeComunicacao