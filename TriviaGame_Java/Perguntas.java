/**
 * @authors: Francisco Caetano, Miguel Gomes
 * @version 1
 */

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import javax.swing.JButton;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import java.io.Serializable;

/**
 * classe pai (super classe) para as perguntas do jogo
 */
public class Perguntas implements Serializable{
    private String texto;
    private ArrayList<String> opcoes;
    private String solucao;
    private String area;
    public String respostaDada;
    private static int pontuacao = 5;

    /**
     * Construtor geral das perguntas
     */
    public Perguntas(String texto, ArrayList<String> opcoes, String solucao){
        this.texto = texto;
        this.opcoes = opcoes;
        this.solucao = solucao;
        this.area = null;
        this.respostaDada = null;
    }
    /**
     * metodo que cria o painel com os botoes que contém as opçoes de resposta
     */
    public JPanel criarPainelDeOpcoes(int i,ArrayList<Perguntas> respostasCertas,ArrayList<Perguntas> respostasErradas) {
        JPanel optionsPanel = new JPanel();

        for(String opcao : opcoes){
            JButton button = new JButton(opcao);
            optionsPanel.add(button);
            setUpButtonListeners(button,respostasCertas,respostasErradas,optionsPanel);
        }
        return optionsPanel;
    }
    /**
     * metodo que atribui os listeners aos botoes e vê qual opçao que o utilizador escolheu
     */
    public void setUpButtonListeners(JButton button,ArrayList<Perguntas> respostasCertas,ArrayList<Perguntas> respostasErradas, JPanel optionsPanel){
        ActionListener buttonListener = new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent ae){
                setRespostaDada(button.getText());
                verifyResposta(respostasCertas,respostasErradas);
                optionsPanel.removeAll();
            }
        };

        button.addActionListener(buttonListener);
    }
    /**
     * metodo que verifica se a resposta dada pelo utilizador é a correta ou nao, e informa o utilizador se respondeu corretamente ou nao
     */
    public void verifyResposta(ArrayList<Perguntas> respostasCertas,ArrayList<Perguntas> respostasErradas){
        if (respostaDada.equals(getSolucao())){
            System.out.println("RESPOSTA CORRETA");
            JOptionPane.showMessageDialog(null, "RESPOSTA CORRETA!\n+" + this.majoracao() + " PONTOS","", JOptionPane.PLAIN_MESSAGE);
            respostasCertas.add(this);
        }        
        else {
            JOptionPane.showMessageDialog(null, "RESPOSTA ERRADA!","", JOptionPane.PLAIN_MESSAGE);
            System.out.println("RESPOSTA ERRADA");
            respostasErradas.add(this);
        }
    }
    /**
     * metodo que calcula a pontuaçao (majoraçao) de cada pergunta
     */
    public int majoracao(){
        return pontuacao;
    }
    /**
     * getter que retorna o valor do atributo texto
     */
    public String getTexto() {
        return texto;
    }
    /**
     * getter que retorna o valor do atributo opcoes
     */
    public ArrayList<String> getOpcoes() {
        return opcoes;
    }
    /**
     * getter que retorna o valor do atributo solucao
     */
    public String getSolucao() {
        return solucao;
    }
    /**
     * setter que define o valor do atributo area
     */
    public void setArea(String area){
        this.area = area;
    }
    /**
     * getter que retorna o valor do atributo area
     */
    public String getArea() {
        return area;
    }
    /**
     * getter que retorna o valor do atributo respostaDada
     */
    public String getResposta(){
        return respostaDada;
    }
    /**
     * setter que atribui o valor do atributo respostaDada
     */
    public void setRespostaDada(String respostaDada){
        this.respostaDada = respostaDada;
    }

}