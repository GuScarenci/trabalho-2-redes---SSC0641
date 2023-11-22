#ifndef RECEPTOR_H
#define RECEPTOR_H

#include <string>
#include <vector>

void CamadaFisicaReceptora(std::vector<int> quadro);

void CamadaEnlaceDadosReceptora(std::vector<int> quadro);

std::vector<int> CamadaEnlaceDadosReceptoraEnquadramento(std::vector<int> quadro);

std::vector<int> CamadaEnlaceDadosReceptoraControleDeErro(std::vector<int> quadro);

std::vector<int> CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(std::vector<int> quadro);

std::vector<int> CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar(std::vector<int> quadro);

std::vector<int> CamadaEnlaceDadosReceptoraControleDeErroCRC(std::vector<int> quadro);

void CamadaDeAplicacaoReceptora(std::vector<int> quadro);

std::string DecodeToString(std::vector<int> quadro);

void AplicacaoReceptora(std::string mensagem);

#endif //RECEPTOR_H
