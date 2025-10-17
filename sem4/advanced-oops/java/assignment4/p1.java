import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.Arrays;

public class p1 extends JFrame{
    private JTextField txtbox;
    private JButton runButton;
    private JPanel bulbsPanel;
    private boolean bulbs[];
    private int n;
    public p1(){
        setTitle("Assignment 4 Question 1");
        setSize(565, 200);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        JPanel panel1=new JPanel();
        BoxLayout b=new BoxLayout(panel1, BoxLayout.Y_AXIS);
        panel1.setLayout(b);
        add(panel1);
        JPanel panel2=new JPanel();
        JLabel inptxt=new JLabel("Number of bulbs (1-9):");
        panel2.add(inptxt);
        txtbox=new JTextField(1);
        panel2.add(txtbox);
        runButton=new JButton("Run");
        panel2.add(runButton);
        panel1.add(panel2);
        bulbsPanel=new JPanel(){
            @Override
            protected void paintComponent(Graphics g){
                super.paintComponent(g);
                if (bulbs==null) return;
                int bulbSize=Math.min(getWidth()/n, 50);
                for (int i=0;i<n;i++){
                    g.setColor(bulbs[i]?Color.YELLOW:Color.WHITE);
                    g.fillOval(20+i*(bulbSize+10),getHeight()/2-bulbSize/2,bulbSize,bulbSize);
                    g.setColor(Color.BLACK);
                    g.drawOval(20+i*(bulbSize+10),getHeight()/2-bulbSize/2,bulbSize, bulbSize);
                }
            }
        };
        bulbsPanel.setPreferredSize(new Dimension(400, 100));
        bulbsPanel.setBackground(new Color(240, 240, 240));
        panel1.add(bulbsPanel);
        runButton.addActionListener(e->startSimulation());
    }

    private void startSimulation(){
        n=Integer.parseInt(txtbox.getText());
        bulbs=new boolean[n];
        new Thread(this::runSimulation).start();
    }
    private void runSimulation(){
        for (int i=0;i<n;i++) bulbs[i]=false;
        for (int round=1;round<=n;round++){
            if (round==1){
                for (int i=0;i<n;i++) bulbs[i]=true;
            } 
            else{
                for (int i=round-1;i<n;i+=round){
                    bulbs[i]=!bulbs[i];
                }
            }
            SwingUtilities.invokeLater(()->bulbsPanel.repaint());
            try{
                Thread.sleep(1000);
            }
            catch(Exception e){
            
            }
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(()->new p1().setVisible(true));
    }
}
