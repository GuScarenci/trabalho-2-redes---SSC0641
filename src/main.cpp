    #include <iostream>
    #include <string>
    #include <vector>
    #include <bitset>

    void aplicacaoTransmissora(void);
    void camadaDeAplicacaoTransmissora (std::string mensagem);
    std::vector<int> ConvertToBits(std::string mensagem); //EDITAR

    void camadaEnlaceDadosTransmissora (std::vector<int> quadro);
    std::vector<int> camadaEnlaceDadosTransmissoraControleDeErro (std::vector<int> quadro);
    std::vector<int> camadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(std::vector<int> quadro); //PRECISA IMPLEMENTAR
    std::vector<int> camadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(std::vector<int> quadro); //PRECISA IMPLEMENTAR
    std::vector<int> camadaEnlaceDadosTransmissoraControleDeErroCRC (std::vector<int> quadro); //PRECISA IMPLEMENTAR

    void camadaFisicaTransmissora(std::vector<int> quadro);

    void camadaDeAplicacaoReceptora (int quadro[]);
    void aplicacaoReceptora (std::string mensagem);
    void meioDeComunicacao (int fluxoBrutoDeBits[]);


    int main (void) {
        aplicacaoTransmissora();
    } // fim do metodo main

    void aplicacaoTransmissora(void) {
        std::string mensagem;
        std::cout << "Digite uma mensagem:" << std::endl;
        getline(std::cin, mensagem);

        //Chama a proxima camada

        camadaDeAplicacaoTransmissora(mensagem);    //em um exemplo mais realistico, aqui seria dado um SEND do SO(?)

    }//fim do metodo aplicacaoTransmissora

    void camadaDeAplicacaoTransmissora (std::string mensagem) {
        std::vector<int> quadro = ConvertToBits(mensagem); // trabalhar com bits!!!
        
        //std::cout<<quadro<<std::endl;
        for(int i = 0; i < quadro.size(); ++i) {
            std::cout << quadro[i] << " ";
        }
        // chama a proxima camada
        camadaEnlaceDadosTransmissora(quadro);
    }

    std::vector<int> ConvertToBits(std::string mensagem){
        int i=0, j=0;
        std::vector<int> quadro;

        for(i=0; i < mensagem.size(); i++){
            std::bitset<8> set (mensagem[i]);
            if (mensagem[i] == ' '){
                //um espaço vazio teve que virar um caso especial
                set.reset();   // todos são zero
                set.set(5, 1); // 32 == espaço
            }

            for(j=7; j>= 0; j--){
                if(set.test(j)){
                    quadro.push_back(1);
                }
                else{
                    quadro.push_back(0);
                }
            }
        }
        return quadro;
    }

    void camadaEnlaceDadosTransmissora (std::vector<int> quadro) {
        std::vector<int> quadroCorrigido = camadaEnlaceDadosTransmissoraControleDeErro(quadro);
        //chama proxima camada
        camadaFisicaTransmissora(quadroCorrigido);
    }//fim do metodo camadaEnlaceDadosTransmissora

    std::vector<int> camadaEnlaceDadosTransmissoraControleDeErro (std::vector<int> quadro[]){
        int tipoDeControleDeErro = 0;//alterar de acordo com o teste

        std::vector<int> controleErro;

        switch (tipoDeControleDeErro){
            case 0://bit de paridade par
                controleErro = camadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(quadro);
                break;
            case 1://bit de paridade impar
                controleErro = camadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(quadro);
                break;
            case 2://CRC
                controleErro = camadaEnlaceDadosTransmissoraControleDeErroCRC(quadro);
                break;
        }//fim do switch/case

        return controleErro;
    }//fim dp metodo camadaEnlaceDadosTransmissoraControleDeErro

    std::vector<int> camadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(int quadro[]){
        //implementacao do algoritimo
    }//fim do metodo camadaEnlaceDadosTransmissoraControleDeErroBitParidadePar

    std::vector<int> camadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(int quadro[]){
        //implementacao do algoritimo
    }//fim do metodo CamadaEnlaceDadosTranmissoraControleErroBitParidadeImpar

    std::vector<int> camadaEnlaceDadosTransmissoraControleDeErroCRC (int quadro[]){
        //implementacao do algoritmo
        //usar polinomio CRC-32(IEEE 802)
    }//fim do metodo CamadaEnlaceDAdosTransmissoraControleDeErroCRC

    void camadaFisicaTransmissora(std::vector<int> quadro){
        meioDeComunicacao();
    }

    void meioDeComunicacao (int fluxoBrutoDeBits[]) {
        //OBS: trabalhar com BITS e não com BYTES!!!
        int erro, porcentagemDeErros;
        int fluxoBrutoDeBitsPontoA[], fluxoBrutoDeBitsPontoB[];

        porcentagemDeErros = 0; //10%, 20%,30%,40%,...,100%
        fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;

        while(fluxoBrutoDeBitsPontoB.lenght != fluxoBrutoDeBitsPontoA){

            if((rand()%100) == ...){//fazer a probabilidade do erro
                fluxoBrutoDeBitsPontoB += fluxoBrutoDeBitsPontoA; //BITS!!!
            }else{ //ERRO! INVERTER (usa condição ternária)
                fluxoBrutoDeBitsPontoB == 0 ?
                fluxoBrutoDeBitsPontoA = fluxoBrutoDeBitsPontoB++ :
                fluxoBrutoDeBitsPontoA=fluxoBrutoDeBitsPontoB--;
            }//fim do if

        }//fim do while
    }//fim do metodo meioDeComunicacao

    
    /*
    void camadaDeAplicacaoReceptora (int quadro[]){
        std::string mensagem = quadro[]; // estava trabalhando com bits
        //chama proxima camada
        aplicacaoReceptora(mensagem);
    }//fim do metodo camadaDeAplicacaoReceptora

    void aplicacaoReceptora (std::string mensagem){
        std::cout << "A mensagem recebida foi:" << mensagem << std::endl;
    }//fim do metodo aplicacaoReceptora
*/
