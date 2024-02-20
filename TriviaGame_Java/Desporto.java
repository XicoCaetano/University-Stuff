/**
 * @authors: Francisco Caetano, Miguel Gomes
 * @version 1
 */

import java.util.ArrayList;

/**
 * subclasse de Perguntas
 */
public class Desporto extends Perguntas {

    /**
     * construtor para perguntas do tipo Desporto
     */
    public Desporto(String texto, ArrayList<String> opcoes, String solucao) {
        super(texto, opcoes, solucao);
        setArea("Desporto");

    }
    /**
     * override para o metodo que calcula a pontuaçao (majoraçao) de cada pergunta
     */
    public int majoracao(){
        return super.majoracao() + 3;
    }

}
