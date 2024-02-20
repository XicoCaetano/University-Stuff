/**
 * @authors: Francisco Caetano, Miguel Gomes
 * @version 1
 */

import java.util.ArrayList;

/**
 * Subclasse de Desporto 
 */
public class Ski extends Desporto{

    /**
     * construtor da classe Ski
     */
    public Ski(String texto, ArrayList<String> opcoes, String solucao) {
        super(texto, opcoes, solucao);
        setArea("Ski");
    }
    /**
     * override para o metodo que calcula a pontuaçao (majoraçao) de cada pergunta
     */
    public int majoracao(){
        return super.majoracao() * 2;
    }

}

