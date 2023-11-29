#ifndef MEIO_H
#define MEIO_H

#include <vector>

/*Simula o meio de comunicação entre a aplicação transmissora e a receptora. Alterando bits aleatóriamente baseado na porcentagem de erros.*/
void MeioDeComunicacao(std::vector<int> fluxoBrutoDeBits);

#endif //MEIO_H
