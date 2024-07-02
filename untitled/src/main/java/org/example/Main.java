package org.example;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Main {
    public static void main(String[] args) {
        JFrame frame = new JFrame("Пример приложения на Java Swing");
        frame.setSize(400, 300);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        // Создаем панель
        JPanel panel = new JPanel();
        frame.add(panel);
        placeComponents(panel);

        // Делаем окно видимым
        frame.setVisible(true);
    }

    private static void placeComponents(JPanel panel) {
        panel.setLayout(null);

        // Создаем метку
        JLabel userLabel = new JLabel("Сообщение:");
        userLabel.setBounds(10, 20, 80, 25);
        panel.add(userLabel);

        // Создаем текстовое поле
        JTextField userText = new JTextField(20);
        userText.setBounds(100, 20, 165, 25);
        panel.add(userText);

        // Создаем кнопку
        JButton button = new JButton("Нажми меня");
        button.setBounds(10, 80, 150, 25);
        panel.add(button);

        // Добавляем действие для кнопки
        button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                userText.setText("Привет, мир!");
            }
        });
    }
}
