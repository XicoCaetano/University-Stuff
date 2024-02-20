/**
 * @authors: Francisco Caetano, Miguel Gomes
 * @version 1
 */

import java.util.ArrayList;
/**
 * Subclasse de Desporto
 */
public class Natacao extends Desporto {

    /**
     * construtor da classe Natacao
     */
    public Natacao(String texto, ArrayList<String> opcoes, String solucao) {
        super(texto, opcoes, solucao);
        setArea("Natacao");
    }
    /**
     * override para o metodo que calcula a pontuaçao (majoraçao) de cada pergunta
     */
    public int majoracao(){
        return super.majoracao() + 10;
    }

}
