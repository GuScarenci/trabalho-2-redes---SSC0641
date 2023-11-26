#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <cmath>

#include "../include/receptor.h"
#include "../include/helper.h"

void CamadaFisicaReceptora(std::vector<int> quadro)
{
    CamadaEnlaceDadosReceptora(quadro);
}

void CamadaEnlaceDadosReceptora(std::vector<int> quadro)
{
    std::vector<int> quadroEnquadrado = CamadaEnlaceDadosReceptoraEnquadramento(quadro);
    std::vector<int> quadroCorrigido = CamadaEnlaceDadosReceptoraControleDeErro(quadroEnquadrado);
    CamadaDeAplicacaoReceptora(quadroEnquadrado);
}

std::vector<int> CamadaEnlaceDadosReceptoraEnquadramento(std::vector<int> quadro){
	std::vector<int> quadro_desenquadrado;

	// escolhe o tipo de enquadramento
	// 0 = Contagem de Caracters
	// 1 = inserção de bytes
	int enquadramento = 0;

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

std::vector<int> CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(std::vector<int> quadro)
{

	std::vector<int> quadro_desenquadrado;

	for (int i = 8; i < quadro.size(); i++)
		quadro_desenquadrado.push_back(quadro[i]);

	return quadro_desenquadrado;
}

std::vector<int> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(std::vector<int> quadro)
{
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

std::vector<int> CamadaEnlaceDadosReceptoraControleDeErro(std::vector<int> quadro){
    int tipoDeControleDeErro = 2; //mudar de acordo com o teste

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

std::vector<int> CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(std::vector<int> quadro)
{
    // implementacao do algoritimo
	std::vector<int> recebimento_paridade_par;
	bool paridade = true;

	for (int i = 0; i < quadro.size() - 1; i++)
		recebimento_paridade_par.push_back(quadro.at(i));

	for (int i = 0; i < recebimento_paridade_par.size(); i++)
		if (recebimento_paridade_par.at(i) == 1)
			paridade = !paridade;

	if (quadro.back() == paridade)
		std::cout<<"\nRecebeu com sucesso\n"<<std::endl;

	return recebimento_paridade_par;

} // fim do metodo camadaEnlaceDadosReceptoraControleDeErroBitParidadePar

std::vector<int> CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar(std::vector<int> quadro)
{
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
        std::cout << "\nErro de paridade detectado\n" << std::endl;
    else
        std::cout << "\nRecebeu com sucesso\n" << std::endl;

    return recebimentoParidadeImpar;
} // fim do metodo CamadaEnlaceDadosTranmissoraControleErroBitParidadeImpar

std::vector<int> CamadaEnlaceDadosReceptoraControleDeErroCRC(std::vector<int> quadro)
{
    // implementacao do algoritmo
    // usar polinomio CRC-32(IEEE 802)
    std::cout<<"\n\nRealizando o controle de erro CRC receptor...\n\n"<<std::endl;
	std::string polinomio_crc_32 = "100110000010001110110110111";
    std::vector<int> mensagem, novo_quadro;
    bool valido = true;

    /*if (quadro.size() <= polinomio_crc_32.length())
    {
        std::cout<<"\n\nErro, o quadro possui menos bits que o polinômio\n\n"<<std::endl;
        exit(1);
    }*/

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
        std::cout << "\n Erro! \n" << std::endl;
    }else{
        std::cout << "\nRecebeu com sucesso\n" << std::endl;
    }
    return mensagem;

    //O QUE ESTAVA ANTES
    /*if (valido){
		for (int k : mensagem)
			std::cout<<k<<std::endl;
		std::cout<<"\n\n"<<std::endl;
        return mensagem;
	}*/

} // fim do metodo CamadaEnlaceDadosReceptoraControleDeErroCRC

void CamadaDeAplicacaoReceptora(std::vector<int> quadro)
{
    std::string mensagem = DecodeToString(quadro); // estava trabalhando com bits
    // chama proxima camada
    AplicacaoReceptora(mensagem);
} // fim do metodo camadaDeAplicacaoReceptora

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
}

void AplicacaoReceptora(std::string mensagem)
{
    std::cout << "A mensagem recebida foi:" << mensagem << std::endl;
} // fim do metodo aplicacaoReceptora