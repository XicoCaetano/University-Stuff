/**
 * @authors: Francisco Caetano, Miguel Gomes
 * @version 1
 */

import java.util.ArrayList;

import javax.swing.JButton;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

/**
 * subclasse de Desporto 
 */
public class Futebol extends Desporto {
    ArrayList<String> opcoesNumero;
    ArrayList<String> opcoesNome;
    String solucaoNome;
    String SolucaoCamisola;

    public Futebol(String texto, ArrayList<String> opcoesNome, ArrayList<String> opcoesNumero, String solucaoNome, String SolucaoCamisola) {
        super(texto, null, null);
        this.opcoesNome = opcoesNome;
        this.opcoesNumero = opcoesNumero;
        this.solucaoNome = solucaoNome;
        this.SolucaoCamisola = SolucaoCamisola;
        setArea("Futebol");
    }
    /**
     * override para o metodo que cria o painel com os botoes que contém as opçoes de resposta
     */
    public JPanel criarPainelDeOpcoes(int i,ArrayList<Perguntas> respostasCertas,ArrayList<Perguntas> respostasErradas) {
        JPanel optionsPanel = new JPanel();

        if(i<2){
            for(String opcao : opcoesNome){
                JButton button = new JButton(opcao);
                optionsPanel.add(button);
                setUpButtonListeners(button,respostasCertas,respostasErradas,optionsPanel);
            } 
        }
        else{
            for(String opcao : opcoesNumero){
                JButton button = new JButton(opcao);
                optionsPanel.add(button);
                setUpButtonListeners(button,respostasCertas,respostasErradas,optionsPanel);
            } 
        }  
        return optionsPanel;
    }
    /**
     * override para o metodo que verifica se o utilizador respondeu corretamente ou nao
     */
    public void verifyResposta(ArrayList<Perguntas> respostasCertas,ArrayList<Perguntas> respostasErradas){
        if (getResposta().equals(solucaoNome) || getResposta().equals(SolucaoCamisola)){
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
     * override para o metodo que calcula a pontuaçao (majoraçao) de cada pergunta
     */
    public int majoracao(){
        return super.majoracao() + 1;
    }

}
