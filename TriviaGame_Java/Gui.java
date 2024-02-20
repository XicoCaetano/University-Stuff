/**
 * @authors: Francisco Caetano, Miguel Gomes
 * @version 1
 */

import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

/**
 * classe da interface do programa
 */
public class Gui  {
    private JFrame frame;
    private Jogo jogo = new Jogo();
    /**
     * metodo responsavel pela criacao da frame
     */
    public void janela(ArrayList<Perguntas> cincoPerguntas, int i,ArrayList<Perguntas> respostasCertas,ArrayList<Perguntas> respostasErradas) {
        frame = new JFrame();
        frame.setTitle("Trivia Game");
        frame.setSize(400, 400);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        createPanel(cincoPerguntas, i,respostasCertas,respostasErradas);
        frame.setVisible(true);
        frame.setLocationRelativeTo(null);

    }
    /**
     * metodo responsavel pela criacao de paineis apresentados dentro da frame
     */
    public void createPanel(ArrayList<Perguntas> cincoPerguntas, int i,ArrayList<Perguntas> respostasCertas,ArrayList<Perguntas> respostasErradas) {
        JPanel panel = new JPanel();
        panel.setLayout(new BorderLayout());

        JLabel label = new JLabel(cincoPerguntas.get(i).getTexto());
        JPanel questionPanel = new JPanel();
        questionPanel.add(label);

        panel.add(cincoPerguntas.get(i).criarPainelDeOpcoes(i,respostasCertas,respostasErradas), BorderLayout.CENTER);
        panel.add(questionPanel, BorderLayout.NORTH);

        JButton proximaPerguntaButton = new JButton("Próxima Pergunta");
        
        panel.add(proximaPerguntaButton,BorderLayout.SOUTH);
        frame.add(panel);
        
        ActionListener perguntaRespondida = new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                apresentarPerguntas(cincoPerguntas,i,respostasCertas,respostasErradas);
            }
        };
    
        proximaPerguntaButton.addActionListener(perguntaRespondida);

        frame.setContentPane(panel);
        frame.revalidate();
        frame.repaint();
        
    }

    private void apresentarPerguntas(ArrayList<Perguntas> cincoPerguntas, int i, ArrayList<Perguntas> respostasCertas, ArrayList<Perguntas> respostasErradas) {
        if (i < cincoPerguntas.size() - 1) {
            i++;
            createPanel(cincoPerguntas, i,respostasCertas,respostasErradas);
        } 
        else {
            String nome = JOptionPane.showInputDialog(null, "Introduza o seu nome", "Input", JOptionPane.QUESTION_MESSAGE);
            System.out.println("Nome: " + nome);

            JOptionPane.showMessageDialog(null, "Pontuacao final: " + jogo.calculaPontuacaoJogo(respostasCertas) + " PONTOS","", JOptionPane.PLAIN_MESSAGE);
            System.out.println("Resultados finais: " + respostasCertas.size() + " respostas certas e " + respostasErradas.size() + " respostas erradas ---> " + jogo.calculaPontuacaoJogo(respostasCertas) + " pontos");

            String data = jogo.getData();
            System.out.println("Data: " + data);

            Jogado guardar = new Jogado(nome, data, respostasCertas, respostasErradas);

            jogo.writeObjectFile(guardar);
            jogo.terminarJogo(frame);;
        }
    }
}

