package org.example;

import javax.swing.*;
import java.awt.*;

public class Obstacle extends JLabel {

    public Obstacle(int x, int y, int width, int height) {
        setLocation(x, y);
        setSize(width, height);
        setBackground(new Color(139, 69, 19));
        setOpaque(true);
        setHorizontalAlignment(SwingConstants.CENTER);
        setVerticalAlignment(SwingConstants.CENTER);
    }
}
