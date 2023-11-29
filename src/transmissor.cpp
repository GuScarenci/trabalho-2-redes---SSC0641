#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <cmath>

#include "../include/transmissor.h"
#include "../include/meio.h"
#include "../include/helper.h"

/*Aplicação transmissora. Faz o input da mensagem em string a ser transmitida.*/
void AplicacaoTransmissora(void)
{
    printTag("Aplicação Transmissora: \n\n");

    std::string mensagem;
    std::cout << "Digite uma mensagem: ";
    getline(std::cin, mensagem);
    std::cout<<std::endl;

    CamadaDeAplicacaoTransmissora(mensagem); //Em um exemplo mais realistico, aqui seria dado um SEND

} // fim do metodo AplicacaoTransmissora

/*Trata a string (mensagem) a ser transmitida.*/
void CamadaDeAplicacaoTransmissora(std::string mensagem)
{
    printTag("Camada de Aplicação Transmissora: \n\n");

    std::vector<int> quadro = ConvertToBits(mensagem);

    printQuadro(quadro);

    CamadaEnlaceDadosTransmissora(quadro);
}// fim do metodo CamadaAplicacaoTransmissora

/*Converte uma string passada (mensagem) em um vector de int's binários.*/
std::vector<int> ConvertToBits(std::string mensagem)
{
    int i = 0, j = 0;
    std::vector<int> quadro;

    for (i = 0; i < mensagem.size(); i++)
    {
        std::bitset<8> set(mensagem[i]);
        if (mensagem[i] == ' ')
        {
            //Espaço é um caso especial
            set.reset();   //Todos são zero
            set.set(5, 1); //32 == espaço
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
}//fim do metodo ConvertToBits

/*Enquadra e insere detecção de erros*/
void CamadaEnlaceDadosTransmissora(std::vector<int> quadro)
{   
    printTag("Camada de Enlace Transmissora: \n\n");
    std::cout<<"Enquadra e insere correção de erros!"<<std::endl<<std::endl;

    std::vector<int> quadroEnquadrado = CamadaEnlaceDadosTransmissoraEnquadramento(quadro);
    printQuadro(quadroEnquadrado);
    std::vector<int> quadroCorrigido = CamadaEnlaceDadosTransmissoraControleDeErro(quadroEnquadrado);
    printQuadro(quadroCorrigido);

    CamadaFisicaTransmissora(quadroCorrigido);

} // fim do metodo CamadaEnlaceDadosTransmissora

/*Enquadra o fluxo de bits passado*/
std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramento(std::vector<int> quadro){
    printTag("Enquadramento ");
    // Escolhe o tipo de enquadramento, 0 = Contagem de Caracters, 1 = inserção de bytes
	std::vector<int> quadroEnquadrado;

	switch (enquadramento){
		case 0:

			quadroEnquadrado = CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(quadro);

			break;

		case 1:

			quadroEnquadrado = CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(quadro);

			break;
	}

	return quadroEnquadrado;
}

/*Enquadra o fluxo de bits por contagem de caracteres*/
std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(std::vector<int> quadro){
    printTag("por Contagem de Caracteres: \n\n");
    std::cout<<"Enquadrando..."<<std::endl<<std::endl;

    uint8_t qtd_bytes = ceil(quadro.size() / 8);
    std::vector<int> quadroEnquadrado = quadro;
    std::vector<int> binario;

    std::bitset<8> bits(qtd_bytes);
    for (int i = 0; i < 8; i++){
        if (int(bits[i]) == 1)
            quadroEnquadrado.insert(quadroEnquadrado.begin(), int(bits[i]));
        else
            quadroEnquadrado.insert(quadroEnquadrado.begin(), int(0));
    }
	return quadroEnquadrado;
}

/*Enquadra o fluxo de bits por inserção de bytes*/
std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(std::vector<int> quadro){
    printTag("por Inserção de bytes: \n\n");
    std::cout<<"Enquadrando..."<<std::endl<<std::endl;

	std::string flag = "00001111";
	std::string esc = "11110000";
	std::string flag_bit = "01111110";
	std::string byte_str = "", quadro_str = flag;

    std::vector<int> quadroEnquadrado;
    int counter = 1;

    for (int i = 0; i < quadro.size(); i++){
        byte_str += std::to_string(quadro[i]);

        if (counter == (8)){
            if ((byte_str == flag) || (byte_str == esc))
                quadro_str += esc;

            quadro_str += byte_str;

            counter = 0;
            byte_str = "";
        }
        counter++;
    }

    quadro_str += flag;

    for (auto &i : quadro_str){
        quadroEnquadrado.push_back(i - '0');
	}
    return quadroEnquadrado;
}

/*Insere a detecção de erros no fluxo de bits passado*/
std::vector<int> CamadaEnlaceDadosTransmissoraControleDeErro(std::vector<int> quadro)
{   
    printTag("Correção de Erros ");

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

/*Insere detecção de erros por bit de paridade par*/
std::vector<int> CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(std::vector<int> quadro)
{
    printTag("por bit de paridade par:\n\n");
    std::cout<<"Inserindo correção..."<<std::endl<<std::endl;

    //Implementacao do algoritmo
	std::vector<int> controleParidadePar;
	bool paridade = true;

	for (int i = 0; i < quadro.size(); i++)
		controleParidadePar.push_back(quadro.at(i));

	for (int i = 0; i < quadro.size(); i++)
		if (quadro.at(i) == 1)
			paridade = !paridade;

	controleParidadePar.push_back(paridade);

	return controleParidadePar;
} // fim do metodo camadaEnlaceDadosTransmissoraControleDeErroBitParidadePar

/*Insere detecção de erros por bit de paridade impar*/
std::vector<int> CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(std::vector<int> quadro)
{
    printTag("por bit de paridade impar:\n\n");
    std::cout<<"Inserindo correção..."<<std::endl<<std::endl;

    // Implementação do algoritmo para bit de paridade ímpar
    std::vector<int> controleParidadeImpar;
    bool paridade = true;

    // Copia o quadro original para o novo quadro com paridade
    for (int i = 0; i < quadro.size(); i++)
        controleParidadeImpar.push_back(quadro.at(i));

    // Calcula a paridade ímpar
    for (int i = 0; i < quadro.size(); i++)
        if (quadro.at(i) == 1)
            paridade = !paridade;

    // Adiciona o bit de paridade
    controleParidadeImpar.push_back(!paridade);

    return controleParidadeImpar;
} // fim do metodo CamadaEnlaceDadosTranmissoraControleErroBitParidadeImpar

/*Insere detecção de erros por CRC IEEE-802*/
std::vector<int> CamadaEnlaceDadosTransmissoraControleDeErroCRC(std::vector<int> quadro)
{
    printTag("por CRC: \n\n");
    std::cout<<"Inserindo correção..."<<std::endl<<std::endl;
    //Implementacao do algoritmo usando polinômio CRC-32(IEEE 802)

    std::vector<int> novo_quadro = quadro;
    int polinomio_crc_32[27] = {1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1};

    for (int i = 0; i < /*polinomio_crc_32.length()*/ 31; i++)
        novo_quadro.push_back(0);

    for (int i = 0; i < quadro.size(); i++){
        if (novo_quadro[i] == 1){
            for (int j = 0; j < 27; j++)
                novo_quadro[i + j] ^= (polinomio_crc_32[j]);
            // XOR entre o elemento i+j do novo quadro e o polinômio CRC 32bits; Armazena no próprio elemento i+j do novo quadro
        }
    }

    for (int i = 0; i < quadro.size(); i++)
        novo_quadro[i] = quadro[i];

    return novo_quadro;

} // fim do metodo CamadaEnlaceDAdosTransmissoraControleDeErroCRC

/*Ultima camada da aplicação transmissora, envia o fluxo de bits para o meio de comunicação*/
void CamadaFisicaTransmissora(std::vector<int> quadro)
{   
    printTag("Camada Física Transmissora: \n\n");

    std::cout<<"Transmitindo..."<<std::endl<<std::endl;

    MeioDeComunicacao(quadro);
}