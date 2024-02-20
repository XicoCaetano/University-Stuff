/**
 * @authors: Francisco Caetano, Miguel Gomes
 * @version 1
 */

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.time.Instant;
import java.util.ArrayList;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.FlowLayout;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;


/**
 * Classe principal para realizar o Programa, contém todos os métodos necessários
 */
public class Jogo{
    private ArrayList<Perguntas> perguntas = new ArrayList<>();
    private ArrayList<Perguntas> cincoPerguntas = new ArrayList<>();
    private ArrayList<Integer> indices = new ArrayList<>();
    private ArrayList<Perguntas> respostasCertas = new ArrayList<>();
    private ArrayList<Perguntas> respostasErradas = new ArrayList<>();

    private void lerFicheiro() {
        File f = new File("perguntas.txt");
        if (f.exists() && f.isFile()) {
            try {
                FileReader fr = new FileReader(f);
                BufferedReader br = new BufferedReader(fr);

                String linha;
                while ((linha = br.readLine()) != null) {
                    String[] partes = linha.split("\\|\\|");

                    if(partes[0].equals("Ciencias")){
                        Ciencias pergunta = new Ciencias(partes[1],converteArrayList(partes[2]),converteArrayList(partes[3]),partes[4]);
                        perguntas.add(pergunta);
                    }

                    if(partes[0].equals("Artes")){
                        Artes pergunta = new Artes(partes[1],converteArrayList(partes[2]),partes[3]);
                        perguntas.add(pergunta);
                    }

                    if(partes[0].equals("Futebol")){
                        Futebol pergunta = new Futebol(partes[1],converteArrayList(partes[2]),converteArrayList(partes[3]),partes[4],partes[5]);
                        perguntas.add(pergunta);
                    }

                    if(partes[0].equals("Ski")){
                        Ski pergunta = new Ski(partes[1],converteArrayList(partes[2]),partes[3]);
                        perguntas.add(pergunta);
                    }

                    if(partes[0].equals("Natacao")){
                        Natacao pergunta = new Natacao(partes[1],converteArrayList(partes[2]),partes[3]);
                        perguntas.add(pergunta);
                    }
                }
                br.close();
            } 
            catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    private ArrayList<String> converteArrayList(String str){
        ArrayList<String> opcoes = new ArrayList<>();
        String[] partes = str.split(",");

        for(String parte : partes){
            opcoes.add(parte);
        }

        return opcoes;
    }

    private int getRandomQuestion(ArrayList<Perguntas> perguntas){
        int max = perguntas.size();
        return (int)(Math.random()*max);
    }

    private ArrayList<Perguntas> createGame(ArrayList<Perguntas> perguntas){
        int cont_desporto = 0;
        int cont_ciencias = 0;
        int cont_artes = 0;

        while(indices.size() < 5 && !perguntas.isEmpty()){
            int index = getRandomQuestion(perguntas);

            if(!indices.contains(index)){
                if(perguntas.get(index).getArea().equals("Artes")){
                    if (cont_artes <= 3) {
                        indices.add(index);
                        cincoPerguntas.add(perguntas.get(index));
                        cont_artes++;
                    }
                    else{
                        break;
                    }
                }
                else if(perguntas.get(index).getArea().equals("Ciencias")){
                    if (cont_ciencias <= 3) {
                        indices.add(index);
                        cincoPerguntas.add(perguntas.get(index));
                        cont_ciencias++;
                    }
                    else{
                        break;
                    }
                }
                else if(perguntas.get(index).getArea().equals("Ski") || perguntas.get(index).getArea().equals("Futebol") || perguntas.get(index).getArea().equals("Natacao")){
                    if (cont_desporto <= 3) {
                        indices.add(index);
                        cincoPerguntas.add(perguntas.get(index));
                        cont_desporto++;
                    }
                    else{
                        break;
                    }
                }
            }
        }

        return cincoPerguntas;
    }

    private Jogado readFileObject(File ficheiro){
        
        File f = ficheiro;

        try {
            FileInputStream fis = new FileInputStream(f);
            ObjectInputStream ois = new ObjectInputStream(fis);
            Jogado jogo = (Jogado) ois.readObject();

            ois.close();

            return jogo;
        } 
        
        catch (FileNotFoundException ex) {
            System.out.println("Erro a abrir ficheiro.");
            return null;
        } 
        
        catch (IOException ex) {
            ex.printStackTrace();
            System.out.println("Erro a ler ficheiro.");
            return null;
        } 
        
        catch (ClassNotFoundException ex) {
            System.out.println("Erro a converter objeto.");
            return null;
        }
    }
    /**
     * metodo responsavel por escrever e guardar a informaçao de cada jogo num ficheiro de objetos
     */
    public void writeObjectFile(Jogado guardar){
        String nameFile = "pootrivia_jogo_" + guardar.data + "_" + getInicials(guardar.nome) + ".dat";

        File f = new File("Jogos" + File.separator + nameFile);

        File diretoria = new File("Jogos");

        if (!diretoria.exists()) {
            if(diretoria.mkdirs()){
                System.out.println("Pasta Criada");
            }

            else {
                System.out.println("Erro a criar pasta");
                return;
            }
        }
        else{
            System.out.println("Pasta ja existe");
        }

        try {
            FileOutputStream fos = new FileOutputStream(f);
            ObjectOutputStream oos = new ObjectOutputStream(fos);
            oos.writeObject(guardar);
            oos.close();
            System.out.println("Ficheiro criado com sucesso");
        } catch (FileNotFoundException ex) {
            ex.printStackTrace();
            System.out.println("Erro a criar ficheiro.");
        } catch (IOException ex) {
            System.out.println("Erro a escrever para o ficheiro.");
        }
    }

    private String getInicials(String nome){
        String [] iniciais = nome.split(" ");
        String ini = "";
        for (int i = 0; i < iniciais.length ; i++){
           ini += iniciais[i].charAt(0); 
        }

        return ini.toUpperCase();
    }
    /**
     * metodo responsavel por retornar a data em que o jogo foi jogado
     */
    public String getData(){
        Instant instant = Instant.now();
        String output = instant.toString();
        String[] divisao = output.split("-");
        String data = "";  
        //ano +  mes + dia +  hora
        data += divisao[0] + divisao[1] + divisao[2].charAt(0) + divisao[2].charAt(1) + divisao[2].charAt(3) + divisao[2].charAt(4)  + divisao[2].charAt(6) + divisao[2].charAt(7);

        return data;
    }

    private JPanel createTopPlayersPanel() {
        JPanel topPlayersPanel = new JPanel();
        topPlayersPanel.setLayout(new GridLayout(3, 1)); // Layout para mostrar os 3 jogadores
        JPanel centerPanel = new JPanel(new FlowLayout(FlowLayout.CENTER));


        File diretoria = new File("Jogos");
        File[] ficheiros = diretoria.listFiles();
        File[] topFicheiros;

        if (diretoria.isDirectory()) {
            if(ficheiros.length < 3){
                System.out.println("NOT ENOUGH FILES");
                JLabel emptyLabel = new JLabel("Ainda não existe top 3");
                topPlayersPanel.add(emptyLabel);
            }

            else{
                topFicheiros = bubbleSort(ficheiros.length, ficheiros);

                for (int i = 0; i < 3; ++i) {
                    Jogado jogo = readFileObject(topFicheiros[i]);
                    ArrayList<Perguntas> certas = jogo.getRespostasCertas();
                    int pontuacao = calculaPontuacaoJogo(certas);
                    String jogador = jogo.nome;

                    JLabel playerLabel = new JLabel(jogador + ": " + pontuacao + " pontos");
                    topPlayersPanel.add(playerLabel);
                }
            }
        }
        centerPanel.add(topPlayersPanel);

        return centerPanel;
    }
    /**
     * metodo responsavel por lidar com a parte final do jogo
     */
    public void terminarJogo(JFrame frame) {
        frame.getContentPane().removeAll();
    
        JPanel topPlayersPanel = createTopPlayersPanel();
    
        frame.add(topPlayersPanel, BorderLayout.CENTER);
    
        JButton novoJogoButton = new JButton("Novo Jogo");
        JButton sairButton = new JButton("Sair");
    
        JPanel bottomPanel = new JPanel();
        bottomPanel.add(novoJogoButton);
        bottomPanel.add(sairButton);
    
        frame.add(bottomPanel, BorderLayout.SOUTH);
    
        novoJogoButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                frame.dispose();
                inicio();
            }
        });
    
        sairButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                System.exit(0);
            }
        });
    
        frame.revalidate();
        frame.repaint();
    }
    /**
     * metodo responsavel por calcular a pontuacao do jogo
     */
    public int calculaPontuacaoJogo(ArrayList<Perguntas> certas){
        int pontuacaoFinal = 0;
        for (Perguntas pergunta : certas){
            pontuacaoFinal += pergunta.majoracao();
        }
        return pontuacaoFinal;
    }

    private File[] bubbleSort(int tamanho, File[] ficheiros){

        for (int j = 0; j < tamanho - 1 ;j++){
            for (int i = 0; i < tamanho - 1 - j; i++){

                Jogado jogo1 = readFileObject(ficheiros[i]);
                Jogado jogo2 = readFileObject(ficheiros[i+1]);

                ArrayList<Perguntas> certas1 = jogo1.getRespostasCertas();
                ArrayList<Perguntas> certas2 = jogo2.getRespostasCertas();

                int pont1 = calculaPontuacaoJogo(certas1);
                int pont2 = calculaPontuacaoJogo(certas2);

                if(pont1 < pont2){
                    File aux = ficheiros[i];
                    ficheiros[i] = ficheiros[i+1];
                    ficheiros[i+1] = aux;
                }
            }
        }

        return ficheiros;
    }

    /**
     * metodo responsavel por inicializar o jogo
     */
    public void inicio(){
        int i=0;

        lerFicheiro();
        Gui gui = new Gui();
        gui.janela(createGame(perguntas),i,respostasCertas,respostasErradas);            
    }

    /**
     * getter do ArrayList de respostas certas
     */
    public ArrayList<Perguntas> getRespostasCertas(){
        return respostasCertas;
    }

    /**
     * getter do ArrayList de respostas erradas
     */
    public ArrayList<Perguntas> getRespostasErradas(){
        return respostasErradas;
    }

}
