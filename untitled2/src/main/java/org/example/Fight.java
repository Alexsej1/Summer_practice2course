package org.example;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Random;

public class Fight extends JFrame {

    private Character character;
    private Enemy enemy;
    private Random rnd;
    private int characterHealth = 100;
    private int enemyHealth = 100;
    private int characterAttack = 15;
    private int enemyAttack = 15;

    private JLabel labelCharacterInfo;
    private JLabel labelEnemyInfo;
    private JLabel labelCharacterHealth;
    private JLabel labelEnemyHealth;
    private JLabel labelCharacterAttack;
    private JLabel labelEnemyAttack;
    private JButton buttonAttack;

    public Fight(Character character, Enemy enemy) {
        this.character = character;
        this.enemy = enemy;
        rnd = new Random();

        setTitle("Бой: " + character.getName() + " vs " + "Гоблин");
        setSize(400, 350);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setLocationRelativeTo(null);
        setLayout(new BorderLayout());

        JPanel topPanel = new JPanel(new GridLayout(2, 1));
        topPanel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));
        topPanel.setBackground(Color.WHITE);

        labelCharacterInfo = new JLabel();
        labelCharacterInfo.setText(String.format("<html><b>Персонаж:</b> %s<br><b>Класс:</b> %s<br><b>Способность:</b> %s</html>",
                character.getName(), character.getCharacterClass(), getSpecialAbility(character)));
        topPanel.add(labelCharacterInfo);

        labelEnemyInfo = new JLabel();
        labelEnemyInfo.setText(String.format("<html><b>Враг:</b> %s</html>", "Гоблин"));
        topPanel.add(labelEnemyInfo);

        add(topPanel, BorderLayout.NORTH);

        JPanel centerPanel = new JPanel(new GridLayout(3, 2));
        centerPanel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));
        centerPanel.setBackground(Color.WHITE);

        labelCharacterHealth = new JLabel();
        labelCharacterHealth.setText(String.format("<html><b>Здоровье:</b> %d</html>", characterHealth));
        centerPanel.add(labelCharacterHealth);

        labelEnemyHealth = new JLabel();
        labelEnemyHealth.setText(String.format("<html><b>Здоровье:</b> %d</html>", enemyHealth));
        centerPanel.add(labelEnemyHealth);

        labelCharacterAttack = new JLabel();
        labelCharacterAttack.setText(String.format("<html><b>Атака:</b> %d</html>", characterAttack));
        centerPanel.add(labelCharacterAttack);

        labelEnemyAttack = new JLabel();
        labelEnemyAttack.setText(String.format("<html><b>Атака:</b> %d</html>", enemyAttack));
        centerPanel.add(labelEnemyAttack);

        add(centerPanel, BorderLayout.CENTER);

        JPanel buttonPanel = new JPanel(new FlowLayout(FlowLayout.CENTER));
        buttonPanel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));
        buttonPanel.setBackground(Color.WHITE);

        buttonAttack = new JButton("Удар");
        buttonAttack.setFont(new Font("Arial", Font.BOLD, 14));
        buttonAttack.setPreferredSize(new Dimension(120, 40));
        buttonAttack.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                performAttack();
            }
        });
        buttonPanel.add(buttonAttack);

        add(buttonPanel, BorderLayout.SOUTH);

        setVisible(true);
    }

    private String getSpecialAbility(Character character) {
        switch (character.getCharacterClass()) {
            case "Маг":
                return "Огненный шар";
            case "Лучник":
                return "Ядовитая стрела";
            case "Воин":
                return "Удар мечом";
            default:
                return "Нет способности";
        }
    }

    private void performAttack() {
        if (rnd.nextInt(100) >= 85) {
            JOptionPane.showMessageDialog(this, "Враг уклонился");
        } else {
            int damage = characterAttack;
            enemyHealth -= damage;
            JOptionPane.showMessageDialog(this, String.format("Персонаж нанес %d урона", damage));
        }

        if (enemyHealth <= 0) {
            JOptionPane.showMessageDialog(this, "ПОБЕДА!");
            dispose();
            return;
        }

        if (rnd.nextInt(100) >= 85) {
            JOptionPane.showMessageDialog(this, "Персонаж уклонился");
        } else {
            int damage = enemyAttack;
            characterHealth -= damage;
            JOptionPane.showMessageDialog(this, String.format("Враг нанес %d урона", damage));
        }

        labelCharacterHealth.setText(String.format("<html><b>Здоровье:</b> %d</html>", characterHealth));
        labelEnemyHealth.setText(String.format("<html><b>Здоровье:</b> %d</html>", enemyHealth));

        if (characterHealth <= 0) {
            JOptionPane.showMessageDialog(this, "Игра закончена. Поражение!");
            dispose();
        }
    }
}
