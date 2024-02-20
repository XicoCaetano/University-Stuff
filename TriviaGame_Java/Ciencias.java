/**
 * @authors: Francisco Caetano, Miguel Gomes
 * @version 1
 */

import java.awt.BorderLayout;
import java.util.ArrayList;

import javax.swing.JButton;
import javax.swing.JPanel;

/**
 * subclasse de Perguntas
 */
public class Ciencias extends Perguntas{
    private ArrayList<String> easyOpcoes;
    private ArrayList<String> hardOpcoes;

    /**
     * construtor para perguntas do tipo Ciencias
     */
    public Ciencias(String texto, ArrayList<String> easyOpcoes, ArrayList<String> hardOpcoes, String solucao) {
        super(texto,null, solucao);
        this.easyOpcoes = easyOpcoes;
        this.hardOpcoes = hardOpcoes;
        setArea("Ciencias");
    }

    /**
     * override para o metodo que cria o painel com os botoes que contém as opçoes de resposta
     */
    public JPanel criarPainelDeOpcoes(int i,ArrayList<Perguntas> respostasCertas,ArrayList<Perguntas> respostasErradas) {
        JPanel optionsPanel = new JPanel();
        JPanel easyOptionsPanel = new JPanel();
        JPanel hardOptionsPanel = new JPanel();

        for(String opcao : easyOpcoes){
             JButton button = new JButton(opcao);
                easyOptionsPanel.add(button);
                setUpButtonListeners(button,respostasCertas,respostasErradas,optionsPanel);
        }

        for(String opcao : hardOpcoes){
            JButton button = new JButton(opcao);
                hardOptionsPanel.add(button);
                setUpButtonListeners(button,respostasCertas,respostasErradas,optionsPanel);
        }

        if(i<2){
            optionsPanel.add(easyOptionsPanel, BorderLayout.WEST);
        }
        else{
            optionsPanel.add(hardOptionsPanel, BorderLayout.EAST);
        }
        
        return optionsPanel;
    }
    /**
     * override para o metodo que calcula a pontuaçao (majoraçao) de cada pergunta
     */
    public int majoracao(){
        return super.majoracao() + 5;
    }
    /**
     * getter que retorna o array com as opçoes de resposta faceis
     */
    public ArrayList<String> getEasyOpcoes(){
        return easyOpcoes;
    }
    /**
     * getter que retorna o array com as opçoes de resposta dificeis
     */
    public ArrayList<String> getHardOpcoes(){
        return hardOpcoes;
    }

}