#ifndef RECEPTOR_H
#define RECEPTOR_H

#include <string>
#include <vector>

/*Primeira camada da aplicação receptora que recebe o fluxo de bits*/
void CamadaFisicaReceptora(std::vector<int> quadro);

/*Desenquadra e faz detecção de erros*/
void CamadaEnlaceDadosReceptora(std::vector<int> quadro);

/*Desenquadra o fluxo de bits passado*/
std::vector<int> CamadaEnlaceDadosReceptoraEnquadramento(std::vector<int> quadro);

/*Desenquadra o fluxo de bits por contagem de caracteres*/
std::vector<int> CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(std::vector<int> quadro);

/*Desenquadra o fluxo de bits por inserção de bytes*/
std::vector<int> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(std::vector<int> quadro);

/*Detecção de erros no fluxo de bits passado*/
std::vector<int> CamadaEnlaceDadosReceptoraControleDeErro(std::vector<int> quadro);

/*Detecção de erros por bit de paridade par*/
std::vector<int> CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(std::vector<int> quadro);

/*Detecção de erros por bit de paridade impar*/
std::vector<int> CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar(std::vector<int> quadro);

/*Detecção de erros por CRC IEEE-802*/
std::vector<int> CamadaEnlaceDadosReceptoraControleDeErroCRC(std::vector<int> quadro);

/*Trata o fluxo de bits recebido.*/
void CamadaDeAplicacaoReceptora(std::vector<int> quadro);

/*Converte um vector de int's binários passado em uma string.*/
std::string DecodeToString(std::vector<int> quadro);

/*Recebe a mensagem tratada da camada de aplicação receptora e a imprime no console.*/
void AplicacaoReceptora(std::string mensagem);

#endif //RECEPTOR_H
