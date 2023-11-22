#ifndef CAMADAENLACE_H
#define CAMADAENLACE_H

#include <string>
#include <vector>

void AplicacaoTransmissora(void);
void CamadaDeAplicacaoTransmissora(std::string mensagem);
std::vector<int> ConvertToBits(std::string mensagem); // EDITAR

void CamadaEnlaceDadosTransmissora(std::vector<int> quadro);
std::vector<int> CamadaEnlaceDadosTransmissoraControleDeErro(std::vector<int> quadro);
std::vector<int> CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(std::vector<int> quadro);   // PRECISA IMPLEMENTAR
std::vector<int> CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(std::vector<int> quadro); // PRECISA IMPLEMENTAR
std::vector<int> CamadaEnlaceDadosTransmissoraControleDeErroCRC(std::vector<int> quadro);              // PRECISA IMPLEMENTAR

void CamadaFisicaTransmissora(std::vector<int> quadro);

void MeioDeComunicacao(std::vector<int> fluxoBrutoDeBits);

void CamadaFisicaReceptora(std::vector<int> quadro);

void CamadaEnlaceDadosReceptora(std::vector<int> quadro);

void CamadaDeAplicacaoReceptora(std::vector<int> quadro);

std::string DecodeToString(std::vector<int> quadro);
void AplicacaoReceptora(std::string mensagem);

#endif // CAMADAENLACE_H