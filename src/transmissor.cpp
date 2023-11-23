#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <cmath>

#include "../include/transmissor.h"
#include "../include/meio.h"


void AplicacaoTransmissora(void)
{
    std::string mensagem;
    std::cout << "Digite uma mensagem:" << std::endl;
    getline(std::cin, mensagem);

    // Chama a proxima camada
    CamadaDeAplicacaoTransmissora(mensagem); // em um exemplo mais realistico, aqui seria dado um SEND do SO(?)

} // fim do metodo aplicacaoTransmissora

void CamadaDeAplicacaoTransmissora(std::string mensagem)
{
    std::vector<int> quadro = ConvertToBits(mensagem); // trabalhar com bits!!!

    //printa o quadro
    for (int i = 0; i < quadro.size(); ++i)
    {
        std::cout << quadro[i] << " ";
    }

    // chama a proxima camada
    CamadaEnlaceDadosTransmissora(quadro);
}

//TODO: entender um pouco mais  e implementar sem cópia
std::vector<int> ConvertToBits(std::string mensagem)
{
    int i = 0, j = 0;
    std::vector<int> quadro;

    for (i = 0; i < mensagem.size(); i++)
    {
        std::bitset<8> set(mensagem[i]);
        if (mensagem[i] == ' ')
        {
            // um espaço vazio teve que virar um caso especial
            set.reset();   // todos são zero
            set.set(5, 1); // 32 == espaço
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
}

//TODO:
void CamadaEnlaceDadosTransmissora(std::vector<int> quadro)
{   
    std::vector<int> quadroEnquadrado = CamadaEnlaceDadosTransmissoraEnquadramento(quadro);
    std::vector<int> quadroCorrigido = CamadaEnlaceDadosTransmissoraControleDeErro(quadroEnquadrado);

    // chama proxima camada
    CamadaFisicaTransmissora(quadroCorrigido);

} // fim do metodo camadaEnlaceDadosTransmissora

//TODO: implementar enquadramento
std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramento(std::vector<int> quadro){
    // escolhe o tipo de enquadramento
	// 0 = Contagem de Caracters
	// 1 = inserção de bytes
	int enquadramento = 0;
	std::vector<int> quadroEnquadrado;
	// enquadra o fluxo de bits passado
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

std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(std::vector<int> quadro){

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

std::vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(std::vector<int> quadro){	
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

//TODO: implementar correção de erros
std::vector<int> CamadaEnlaceDadosTransmissoraControleDeErro(std::vector<int> quadro)
{
    int tipoDeControleDeErro = 0; // alterar de acordo com o teste

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

//TODO:
std::vector<int> CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(std::vector<int> quadro)
{
    // implementacao do algoritmo
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

//TODO: IMPLEMENTAR!!!!
std::vector<int> CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(std::vector<int> quadro)
{
    // implementacao do algoritimo
} // fim do metodo CamadaEnlaceDadosTranmissoraControleErroBitParidadeImpar

//TODO:  FIXME: NÃO FUNCIONA
std::vector<int> CamadaEnlaceDadosTransmissoraControleDeErroCRC(std::vector<int> quadro)
{
    // implementacao do algoritmo
    // usar polinomio CRC-32(IEEE 802)

    std::vector<int> novo_quadro = quadro;
	std::string polinomio_crc_32 = "100000100110000010001110110110111";

    if (quadro.size() <= polinomio_crc_32.length()){
		std::cout<<"\n\nErro, o quadro possui menos bits que o polinomio\n\n"<<std::endl;
        exit(1);
    }

    for (int i = 0; i < polinomio_crc_32.length(); i++)
        novo_quadro.push_back(0);

    for (int i = 0; i < quadro.size(); i++){
        if (novo_quadro[i] == 1){
            for (int j = 0; j < polinomio_crc_32.length(); j++)
                novo_quadro[i + j] ^= (polinomio_crc_32[j] - '0');
            // XOR entre o elemento i+j do novo quadro e o polinômio CRC 32bits; Armazena no próprio elemento i+j do novo quadro
        }
    }

    for (int i = 0; i < quadro.size(); i++)
        novo_quadro[i] = quadro[i];

    return novo_quadro;

} // fim do metodo CamadaEnlaceDAdosTransmissoraControleDeErroCRC

void CamadaFisicaTransmissora(std::vector<int> quadro)
{
    MeioDeComunicacao(quadro);
}