package org.example;

import javax.swing.*;
import java.awt.*;

public class Enemy extends JPanel {

    public Enemy(int x, int y, int width, int height) {
        setLocation(x, y);
        setSize(width, height);
        setBackground(Color.RED);
    }
}
