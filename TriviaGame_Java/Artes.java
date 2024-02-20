/**
 * @authors: Francisco Caetano, Miguel Gomes
 * @version 1
 */


import java.util.ArrayList;

import javax.swing.JButton;
import javax.swing.JPanel;

/**
 * subclasse de PErguntas
 */
public class Artes extends Perguntas{

    /**
     * construtor para perguntas do tipo Artes
     */
    public Artes(String texto, ArrayList<String> opcoes, String solucao) {
        super(texto, opcoes, solucao);
        setArea("Artes");

    }
    /**
     * override para o metodo que cria o painel com os botoes que contém as opçoes de resposta
     */
    public JPanel criarPainelDeOpcoes(int i,ArrayList<Perguntas> respostasCertas,ArrayList<Perguntas> respostasErradas) {
        JPanel optionsPanel = new JPanel();

        if(i<2){
            int j=0;
            JButton button = new JButton(getSolucao());
            optionsPanel.add(button);
            setUpButtonListeners(button,respostasCertas,respostasErradas,optionsPanel);
            for(String opcao : getOpcoes()){
                if(j<2 && !opcao.equals(getSolucao())){
                    JButton button1 = new JButton(opcao);
                    optionsPanel.add(button1);
                    setUpButtonListeners(button1,respostasCertas,respostasErradas,optionsPanel);
                    ++j;
                }
            } 
        }
        else{
            for(String opcao : getOpcoes()){
                JButton button = new JButton(opcao);
                optionsPanel.add(button);
                setUpButtonListeners(button,respostasCertas,respostasErradas,optionsPanel);
            } 
        }  
        return optionsPanel;
    }
    /**
     * override para o metodo que calcula a pontuaçao (majoraçao) de cada pergunta
     */
    public int majoracao(){
        return super.majoracao() * 10;
    }
    
}
