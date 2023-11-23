#ifndef TRANSMISSOR_H
#define TRANSMISSOR_H

#include <string>
#include <vector>

void AplicacaoTransmissora(void);

void CamadaDeAplicacaoTransmissora(std::string mensagem);

std::vector<int> ConvertToBits(std::string mensagem);

void CamadaEnlaceDadosTransmissora(std::vector<int> quadro);

std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramento(std::vector<int> quadro);

std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(std::vector<int> quadro);

std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(std::vector<int> quadro);

std::vector<int> CamadaEnlaceDadosTransmissoraControleDeErro(std::vector<int> quadro);

std::vector<int> CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(std::vector<int> quadro);

std::vector<int> CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(std::vector<int> quadro);

std::vector<int> CamadaEnlaceDadosTransmissoraControleDeErroCRC(std::vector<int> quadro);

void CamadaFisicaTransmissora(std::vector<int> quadro);

#endif //TRANSMISSOR_H
