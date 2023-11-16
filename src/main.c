#include <stdio.h>

void main (void) {
    aplicacaoTransmissora();
} // fim do metodo main

void aplicacaoTransmissora(void) {
    char mensagem[100];
    printf("Digite uma mensagem");
    fgets(mensagem, 100, stdin);

    //Chama a proxima camada

    camadaDeAplicacaoTransmissora(mensagem);    //em um exemplo mais realistico, aqui seria dado um SEND do SO(?)

}//fim do metodo aplicacaoTransmissora

void camadaDeAplicacaoTransmissora (char mensagem[]) {
    //int quadro [] = mensagem // trabalhar com bits!!!
    // chama a proxima camada (???)
}

void camadaDeAplicacaoReceptora (int quadro[]){
    //string mensagem = quadro[]; // estava trabalhando com bits
    //chama proxima camada
    aplicacaoReceptora(mensagem);

}//fim do metodo camadaDeAplicacaoReceptora

void aplicacaoReceptora (char mensagem[]){
    printf("A mensagem recebida foi: %s",mensagem);
}//fim do metodo aplicacaoReceptora

void meioDeComunicacao (int fluxoBrutoDeBits[]) {
    //OBS: trabalhar com BITS e não com BYTES!!!
    int erro, porcentagemDeErros;
    int fluxoBrutoDeBitsPontoA[], fluxoBrutoDeBitsPontoB[];

    porcentagemDeErros = 0; //10%, 20%,30%,40%,...,100%
    fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;

    while(fluxoBrutoDeBitsPontoB.lenght != fluxoBrutoDeBitsPontoA){
        if((rand()%100) == ...){//fazer a probabilidade do erro
        fluxoBrutoBitsPontoB += fluxoBrutoBitsPontoA; //BITS!!!
        }else{
            fluxoBrutoBitsPontoB == 0) ?
            fluxoBrutoBitsPonntoA = fluxoBrutoBitsPonto++ :
            fluxoBrutoBitsPontoA=fluxoBrutoBitsPontoB--;
        }//fim do if
    }//fim do while
}//fim do metodo meioDeComunicacao

void camadaEnlaceDadosTransmissora (int quadro[]) {
    camadaEnlaceDadosTransmissoraControleDeErro(quadro);

    //chama proxima camada
}//fim do metodo camadaEnlaceDadosTransmissora

void camadaEnlaceDadosTransmissoraControleDeErro (int quadro[]){
 int tipoDeControleDeErro = 0;//alterar de acordo com o teste
 switch (tipoDeControleDeErro){
    case 0://bit de paridade par
        //codigo
        break;
    case 1://bit de paridade impar
        //codigo
        break;
    case 2://CRC
        //codigo
        break;
 }//fim do switch/case
}//fim dp metodo camadaEnlaceDadosTransmissoraControleDeErro

void camadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(int quadro[]){
    //implementacao do algoritimo
}//fim do metodo camadaEnlaceDadosTransmissoraControleDeErroBitParidadePar

void camadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(int quadro[]){
    //implementacao do algoritimo
}//fim do metodo CamadaEnlaceDadosTranmissoraControleErroBitParidadeImpar

