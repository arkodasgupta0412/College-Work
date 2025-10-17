import javax.swing.*;
import java.awt.*;
import java.util.*;
import java.io.*;

public class a4p2 {
    public static int[] getHeights(int n) {
        try{
            Scanner s = new Scanner(new File("height.txt"));
            int[] h = new int[n];
            for (int i = 0; i < n; i++) h[i] = s.nextInt();
            return h;
        }
        catch (Exception e){
            int[] a=new int[1];
            return a;

        }
        
    }

    public static JPanel drawLines(int[] h, int a, int b) {
        return new JPanel() {
            protected void paintComponent(Graphics g) {
                super.paintComponent(g);
                int w = getWidth();
                int hgt = getHeight();
                int space = w / h.length;
                for (int i = 0; i < h.length; i++) {
                    int x = i * space + space / 2;
                    int y = hgt - h[i] * 10;
                    g.setColor((i == a || i == b) ? Color.RED : Color.BLACK);
                    g.drawLine(x, hgt, x, y);
                }
            }
        };
    }

    public static int getMaxArea(int[] h, int[] res) {
        int l = 0, r = h.length - 1, max = 0;
        while (l < r) {
            int area = (r - l) * Math.min(h[l], h[r]);
            if (area > max) {
                max = area;
                res[0] = l;
                res[1] = r;
            }
            if (h[l] < h[r]) l++; else r--;
        }
        return max;
    }

    public static double getSlantedArea(int[] h, double d, int[] res) {
        int l = 0, r = h.length - 1;
        double max = 0;
        while (l < r) {
            double hl = h[l] * Math.sin(Math.toRadians(d));
            double hr = h[r] * Math.sin(Math.toRadians(d));
            double area = (r - l) * Math.min(hl, hr);
            if (area > max) {
                max = area;
                res[0] = l;
                res[1] = r;
            }
            if (hl < hr) l++; else r--;
        }
        return max;
    }

    public static void main(String[] args) {
        JFrame f = new JFrame("Water View");
        f.setSize(800, 600);
        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel top = new JPanel();
        JTextField t1 = new JTextField(5);
        JTextField t2 = new JTextField(5);
        JButton btn = new JButton("Go");

        top.add(new JLabel("Lines:"));
        top.add(t1);
        top.add(new JLabel("Degree:"));
        top.add(t2);
        top.add(btn);

        JPanel drawPanel = new JPanel();
        f.setLayout(new BorderLayout());
        f.add(top, BorderLayout.NORTH);
        f.add(drawPanel, BorderLayout.CENTER);

        btn.addActionListener(e -> {
            int n = Integer.parseInt(t1.getText());
            double d = Double.parseDouble(t2.getText());
            int[] h = getHeights(n);
            int[] pair1 = new int[2];
            int normal = getMaxArea(h, pair1);
            int[] pair2 = new int[2];
            double tilt = getSlantedArea(h, d, pair2);

            JPanel newPanel = drawLines(h, pair1[0], pair1[1]);
            newPanel.setPreferredSize(drawPanel.getSize());

            drawPanel.removeAll();
            drawPanel.setLayout(new BorderLayout());
            drawPanel.add(newPanel, BorderLayout.CENTER);
            drawPanel.revalidate();
            drawPanel.repaint();

            JOptionPane.showMessageDialog(f, "Max: " + normal + "\nSlanted: " + String.format("%.2f", tilt));
        });

        f.setVisible(true);
    }
}
