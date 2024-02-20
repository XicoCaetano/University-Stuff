/**
 * @authors: Francisco Caetano, Miguel Gomes
 * @version 1
 */
import java.io.Serializable;
import java.util.ArrayList;

/**
 * subclasse de Jogo usada para guardar os jogos em ficheiro
 */
public class Jogado extends Jogo implements Serializable{
    String nome;
    String data;

    ArrayList<Perguntas> respostasCertas;
    ArrayList<Perguntas> respostasErradas;
    /**
     * construtor para objetos do tipo jogago
     */
    public Jogado(String nome, String data, ArrayList<Perguntas> respostasCertas, ArrayList<Perguntas> respostasErradas) {
        this.nome = nome;
        this.data = data;
        this.respostasCertas = respostasCertas;
        this.respostasErradas = respostasErradas;
    }
    /**
     * metodo que retorna o arraylist com as respostas certas
     */
    public ArrayList<Perguntas> getRespostasCertas() {
        return respostasCertas;
    }
}