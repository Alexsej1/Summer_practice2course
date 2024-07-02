package org.example;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class CreateCharacter extends JFrame {

    private JTextField nameField;
    private JRadioButton maleRadioButton;
    private JRadioButton femaleRadioButton;
    private JComboBox<String> classComboBox;

    public CreateCharacter() {
        setTitle("Create Character");
        setSize(999, 545);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JLabel label1 = new JLabel("СОЗДАЙ СВОЕГО", SwingConstants.CENTER);
        label1.setFont(new Font("Microsoft Sans Serif", Font.BOLD, 40));
        JLabel label2 = new JLabel("ПЕРСОНАЖА", SwingConstants.CENTER);
        label2.setFont(new Font("Microsoft Sans Serif", Font.BOLD, 40));

        JLabel nameLabel = new JLabel("Имя:");
        nameField = new JTextField();

        JLabel genderLabel = new JLabel("Пол:");
        maleRadioButton = new JRadioButton("Мужской");
        femaleRadioButton = new JRadioButton("Женский");

        ButtonGroup genderGroup = new ButtonGroup();
        genderGroup.add(maleRadioButton);
        genderGroup.add(femaleRadioButton);

        JLabel classLabel = new JLabel("Класс:");
        classComboBox = new JComboBox<>(new String[]{"Маг", "Лучник", "Воин"});

        JButton continueButton = new JButton("Продолжить");
        continueButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String name = nameField.getText();
                String gender = maleRadioButton.isSelected() ? "Мужской" : "Женский";
                String classType = (String) classComboBox.getSelectedItem();

                Character character;
                switch (classType) {
                    case "Маг":
                        character = new Mage(name, gender);
                        break;
                    case "Лучник":
                        character = new Archer(name, gender);
                        break;
                    case "Воин":
                        character = new Warrior(name, gender);
                        break;
                    default:
                        character = null;
                        break;
                }

                if (character != null) {
                    JOptionPane.showMessageDialog(null, "Персонаж создан: " + character.getName() + ", " + character.getGender() + ", " + character.getCharacterClass() + "\nАтака: " + character.attack());
                    // Переход на игровое поле
                    MyForm2 gameField = new MyForm2(character);
                    gameField.setVisible(true);
                    setVisible(false);
                }
            }
        });

        setLayout(new GridLayout(10, 1));
        add(label1);
        add(label2);
        add(nameLabel);
        add(nameField);
        add(genderLabel);
        add(maleRadioButton);
        add(femaleRadioButton);
        add(classLabel);
        add(classComboBox);
        add(continueButton);

        setVisible(true);
    }
}
