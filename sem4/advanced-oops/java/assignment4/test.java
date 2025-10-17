import javax.swing.JFrame;
import javax.swing.ImageIcon;
import java.awt.Color;
import javax.swing.JLabel;

class myFrame extends JFrame {
    myFrame() {
        // sets the x-dim and y-dim of the frame
        setSize(420, 420);
    
        // sets the title of the frame
        setTitle("TestFrame");

        // closes the entire frame completely on clicking X
        // by default, it hides the frame, keeping it running in the background even after closing
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); 

        ImageIcon image = new ImageIcon("C:\\Users\\Nabasree\\OneDrive\\Pictures\\Saved Pictures\\hacker.jpg");
        setIconImage(image.getImage());
        ImageIcon img = new ImageIcon("C:\\Users\\Nabasree\\OneDrive\\Pictures\\Saved Pictures\\art.png");

        getContentPane().setBackground(new Color(35,34, 123));

        JLabel label = new JLabel();
        label.setText("Bro, do you even code?");
        label.setBounds(200, 100, 300, 30);
        label.setForeground(Color.white);
        
        label.setIcon(img);
        add(label);

        // sets the visibility of the frame
        setVisible(true);
    }
}

public class test {
    public static void main(String[] args) {
        myFrame frame = new myFrame();
    }
}