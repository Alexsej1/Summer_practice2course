package org.example;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class MainMenu extends JFrame {

    public MainMenu() {
        setTitle("Main Menu");
        setSize(935, 575);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JLabel label1 = new JLabel("MEHMAT", SwingConstants.CENTER);
        label1.setFont(new Font("Microsoft Sans Serif", Font.BOLD, 72));
        JLabel label2 = new JLabel("RPG", SwingConstants.CENTER);
        label2.setFont(new Font("Microsoft Sans Serif", Font.BOLD, 60));

        JButton startButton = new JButton("СТАРТ");
        startButton.setFont(new Font("Microsoft Sans Serif", Font.BOLD, 40));
        startButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                setVisible(false);
                new CreateCharacter();
            }
        });

        JButton exitButton = new JButton("ВЫХОД");
        exitButton.setFont(new Font("Microsoft Sans Serif", Font.BOLD, 40));
        exitButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                System.exit(0);
            }
        });

        setLayout(new GridLayout(4, 1));
        add(label1);
        add(label2);
        add(startButton);
        add(exitButton);

        setVisible(true);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new MainMenu());
    }
}
