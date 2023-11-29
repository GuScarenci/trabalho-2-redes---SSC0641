#ifndef TRANSMISSOR_H
#define TRANSMISSOR_H

#include <string>
#include <vector>

/*Aplicação transmissora. Faz o input da mensagem em string a ser transmitida.*/
void AplicacaoTransmissora(void);

/*Trata a string (mensagem) a ser transmitida.*/
void CamadaDeAplicacaoTransmissora(std::string mensagem);

/*Converte uma string passada (mensagem) em um vector de int's binários.*/
std::vector<int> ConvertToBits(std::string mensagem);

/*Enquadra e insere detecção de erros*/
void CamadaEnlaceDadosTransmissora(std::vector<int> quadro);

/*Enquadra o fluxo de bits passado*/
std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramento(std::vector<int> quadro);

/*Enquadra o fluxo de bits por contagem de caracteres*/
std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(std::vector<int> quadro);

/*Enquadra o fluxo de bits por inserção de bytes*/
std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(std::vector<int> quadro);

/*Insere a detecção de erros no fluxo de bits passado*/
std::vector<int> CamadaEnlaceDadosTransmissoraControleDeErro(std::vector<int> quadro);

/*Insere detecção de erros por bit de paridade par*/
std::vector<int> CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(std::vector<int> quadro);

/*Insere detecção de erros por bit de paridade impar*/
std::vector<int> CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(std::vector<int> quadro);

/*Insere detecção de erros por CRC IEEE-802*/
std::vector<int> CamadaEnlaceDadosTransmissoraControleDeErroCRC(std::vector<int> quadro);

/*Ultima camada da aplicação transmissora, envia o fluxo de bits para o meio de comunicação*/
void CamadaFisicaTransmissora(std::vector<int> quadro);

#endif //TRANSMISSOR_H
