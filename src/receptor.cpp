#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <cmath>

#include "../include/receptor.h"
#include "../include/helper.h"

/*Primeira camada da aplicação receptora que recebe o fluxo de bits*/
void CamadaFisicaReceptora(std::vector<int> quadro)
{
    printTag("Camada Física Receptora: \n\n");

    std::cout<<"Recebendo..."<<std::endl<<std::endl;

    CamadaEnlaceDadosReceptora(quadro);
}

/*Desenquadra e faz detecção de erros*/
void CamadaEnlaceDadosReceptora(std::vector<int> quadro)
{
    printTag("Camada de Enlace Receptora: \n\n");

    std::cout<<"Desenquadra e corrige erros!"<<std::endl<<std::endl;

    std::vector<int> quadroCorrigido = CamadaEnlaceDadosReceptoraControleDeErro(quadro);
    std::vector<int> quadroDesenquadrado = CamadaEnlaceDadosReceptoraEnquadramento(quadroCorrigido);
    CamadaDeAplicacaoReceptora(quadroCorrigido);
}

/*Desenquadra o fluxo de bits passado*/
std::vector<int> CamadaEnlaceDadosReceptoraEnquadramento(std::vector<int> quadro){

    printTag("Desenquadramento ");

	std::vector<int> quadro_desenquadrado;

	//Escolhe o tipo de enquadramento, 0 = Contagem de Caracters, 1 = inserção de bytes

	switch (enquadramento)
	{
	case 0: //contagem de caracteres
		quadro_desenquadrado = CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(quadro);
		break;
	case 1: //insercao de bytes
		quadro_desenquadrado = CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(quadro);
		break;
	default:
		exit(1);
		break;
	}
	return quadro_desenquadrado;
}

/*Desenquadra o fluxo de bits por contagem de caracteres*/
std::vector<int> CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(std::vector<int> quadro)
{
    printTag("por Contagem de Caracteres: \n\n");
    std::cout<<"Enquadrando..."<<std::endl<<std::endl;


	std::vector<int> quadro_desenquadrado;

	for (int i = 8; i < quadro.size(); i++)
		quadro_desenquadrado.push_back(quadro[i]);

	return quadro_desenquadrado;
}

/*Desenquadra o fluxo de bits por inserção de bytes*/
std::vector<int> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(std::vector<int> quadro)
{
    printTag("por Inserção de bytes: \n\n");
    std::cout<<"Desenquadrando..."<<std::endl<<std::endl;


	std::string byte_str = "";
	std::string quadro_str = "";
	std::string flag = "00001111";
	std::string esc = "11110000";

	std::vector<int> novo_quadro;
	int counter = 1;
	bool ignore = false;

	for (int i = 0; i < quadro.size(); i++)
	{
		byte_str += std::to_string(quadro[i]);

		if (counter == 8)
		{
			if (((byte_str == flag) || (byte_str == esc)) && !ignore)
				ignore = true;
			else
			{
				quadro_str += byte_str;
				ignore = false;
			}

			counter = 0;
			byte_str = "";
		}
		counter++;
    }
    for (auto &i : quadro_str){
		novo_quadro.push_back(i - '0');
	}

	return novo_quadro;
}

/*Detecção de erros no fluxo de bits passado*/
std::vector<int> CamadaEnlaceDadosReceptoraControleDeErro(std::vector<int> quadro){
    printTag("Correção de Erros ");

    std::vector<int> controleErro;

    switch (tipoDeControleDeErro)
    {
    case 0: // bit de paridade par
        controleErro = CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(quadro);
        break;
    case 1: // bit de paridade impar
        controleErro = CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar(quadro);
        break;
    case 2: // CRC
        controleErro = CamadaEnlaceDadosReceptoraControleDeErroCRC(quadro);
        break;
    } // fim do switch/case

    return controleErro;   
}

/*Detecção de erros por bit de paridade par*/
std::vector<int> CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(std::vector<int> quadro)
{   
    printTag("por bit de paridade par:\n\n");
    std::cout<<"Corrigindo..."<<std::endl<<std::endl;

    // implementacao do algoritimo
	std::vector<int> recebimento_paridade_par;
	bool paridade = true;

	for (int i = 0; i < quadro.size() - 1; i++)
		recebimento_paridade_par.push_back(quadro.at(i));

	for (int i = 0; i < recebimento_paridade_par.size(); i++)
		if (recebimento_paridade_par.at(i) == 1)
			paridade = !paridade;

	if (quadro.back() == paridade){
		std::cout<<"\nRecebeu com sucesso!\n"<<std::endl;
    }else{
        std::cout<<"\nProblema na comunicação detectado!\n"<<std::endl;
    }


	return recebimento_paridade_par;

} // fim do metodo camadaEnlaceDadosReceptoraControleDeErroBitParidadePar

/*Detecção de erros por bit de paridade impar*/
std::vector<int> CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar(std::vector<int> quadro)
{
    printTag("por bit de paridade impar:\n\n");
    std::cout<<"Corrigindo..."<<std::endl<<std::endl;

    // Implementação do algoritmo para recepção com paridade ímpar
    std::vector<int> recebimentoParidadeImpar;
    bool paridade = false;  // Começa com falso para paridade ímpar

    // Copia o quadro recebido, exceto o bit de paridade
    for (int i = 0; i < quadro.size() - 1; i++)
        recebimentoParidadeImpar.push_back(quadro.at(i));

    // Calcula a paridade ímpar
    for (int i = 0; i < recebimentoParidadeImpar.size(); i++)
        if (recebimentoParidadeImpar.at(i) == 1)
            paridade = !paridade;

    // Verifica se o bit de paridade é válido
    if (quadro.back() != paridade)  // Verifica se é diferente para paridade ímpar
        std::cout << "\nErro de paridade detectado!\n" << std::endl;
    else
        std::cout << "\nRecebeu com sucesso!\n" << std::endl;

    return recebimentoParidadeImpar;
} // fim do metodo CamadaEnlaceDadosTranmissoraControleErroBitParidadeImpar

/*Detecção de erros por CRC IEEE-802*/
std::vector<int> CamadaEnlaceDadosReceptoraControleDeErroCRC(std::vector<int> quadro)
{
    printTag("por CRC: \n\n");
    std::cout<<"Inserindo correção..."<<std::endl<<std::endl;

    // Implementacao do algoritmo usando polinomio CRC-32(IEEE 802)
	std::string polinomio_crc_32 = "100110000010001110110110111";
    std::vector<int> mensagem, novo_quadro;
    bool valido = true;

    novo_quadro = quadro;
    mensagem = quadro;
    mensagem.erase(mensagem.end() - 31, mensagem.end());

    for (int i = 0; i < mensagem.size(); i++)
    {
        if (novo_quadro[i] == 1)
        {
            for (int j = 0; j < polinomio_crc_32.length(); j++)
                novo_quadro[j + i] = novo_quadro[j + i] == polinomio_crc_32[j] ? 0 : 1;
            /*  Compara o item i+j do novo quadro com o polinômio CRC 32 bits e armazena, no mesmo elemento,
                    0 se forem iguais, e 1 caso sejam diferentes. */
        }
    }

    for (int i = 0; i < mensagem.size(); i++)
    {
        if (novo_quadro[i] != 0)
            valido = false;
    }

    if (!valido){
        std::cout << "\nErro! \n" << std::endl;
    }else{
        std::cout << "\nRecebeu com sucesso!\n" << std::endl;
    }
    return mensagem;

    //TODO:
    //O QUE ESTAVA ANTES
    /*if (valido){
		for (int k : mensagem)
			std::cout<<k<<std::endl;
		std::cout<<"\n\n"<<std::endl;
        return mensagem;
	}*/

} // fim do metodo CamadaEnlaceDadosReceptoraControleDeErroCRC

/*Trata o fluxo de bits recebido.*/
void CamadaDeAplicacaoReceptora(std::vector<int> quadro)
{
    printTag("Camada de Aplicação Receptora: \n\n");

    std::cout << "Transferindo fluxo de bits para mensagem legível...\n\n";

    std::string mensagem = DecodeToString(quadro); // estava trabalhando com bits
    // chama proxima camada
    AplicacaoReceptora(mensagem);
} // fim do metodo camadaDeAplicacaoReceptora

/*Converte um vector de int's binários passado em uma string.*/
std::string DecodeToString(std::vector<int> quadro)
{
    int i = 0, y = 0, j = 0;
    std::string mensagem;
    int letra = 0;
    // Pega grupo de 8 bits
    for (i = 0; i < quadro.size(); i += 8)
    {
        letra = 0;
        y = 0;
        // Ler os 8 bits e converte de binario para decimal utilizando base 2
        // e o expoente da potencia sendo o indice do bit
        for (j = i; j < (8 + i); j++)
        {
            if (quadro[j] == 1)
                letra = letra + pow(2, 7 - y);

            y++;
        }
        // Converte o valor inteiro em um caracter e concatena com a string que sera retornada
        mensagem.push_back((char)letra);
    }

    return mensagem;
}// fim do metodo DecodeToString

/*Recebe a mensagem tratada da camada de aplicação receptora e a imprime no console.*/
void AplicacaoReceptora(std::string mensagem)
{   
    printTag("Aplicação Receptora \n\n");

    std::cout << "A mensagem recebida foi:" << mensagem << std::endl;
} // fim do metodo aplicacaoReceptora