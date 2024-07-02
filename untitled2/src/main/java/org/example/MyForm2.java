package org.example;

import javax.swing.*;
import java.awt.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

public class MyForm2 extends JFrame {

    private JLabel labelName;
    private JLabel labelGender;
    private JLabel labelClass;
    private JLabel characterLabel;
    private JPanel topBorder;
    private JPanel bottomBorder;
    private JPanel leftBorder;
    private JPanel rightBorder;
    private Character character;
    private Obstacle[] obstacles;
    private Enemy[] enemies;

    private final int moveStep = 10;

    public MyForm2(Character character) {
        this.character = character;

        setTitle("Game Field");
        setSize(672, 359);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        getContentPane().setBackground(Color.GREEN);

        setLayout(null);

        labelName = new JLabel("Имя: " + character.getName());
        labelName.setBounds(10, 10, 200, 20);
        add(labelName);

        labelGender = new JLabel("Пол: " + character.getGender());
        labelGender.setBounds(10, 30, 200, 20);
        add(labelGender);

        labelClass = new JLabel("Класс: " + character.getCharacterClass());
        labelClass.setBounds(10, 50, 200, 20);
        add(labelClass);

        characterLabel = new JLabel();
        characterLabel.setBounds(100, 150, 30, 30);
        characterLabel.setOpaque(true);
        characterLabel.setBackground(Color.WHITE);
        add(characterLabel);

        topBorder = new JPanel();
        topBorder.setBackground(Color.BLACK);
        topBorder.setBounds(0, 0, 672, 10);
        add(topBorder);

        bottomBorder = new JPanel();
        bottomBorder.setBackground(Color.BLACK);
        bottomBorder.setBounds(0, 349, 672, 10);
        add(bottomBorder);

        leftBorder = new JPanel();
        leftBorder.setBackground(Color.BLACK);
        leftBorder.setBounds(0, 0, 10, 359);
        add(leftBorder);

        rightBorder = new JPanel();
        rightBorder.setBackground(Color.BLACK);
        rightBorder.setBounds(662, 0, 10, 359);
        add(rightBorder);

        obstacles = new Obstacle[5];
        obstacles[0] = new Obstacle(150, 100, 50, 50);
        obstacles[1] = new Obstacle(300, 200, 50, 50);
        obstacles[2] = new Obstacle(450, 150, 50, 50);
        obstacles[3] = new Obstacle(100, 300, 50, 50);
        obstacles[4] = new Obstacle(500, 50, 50, 50);

        for (Obstacle obstacle : obstacles) {
            add(obstacle);
        }

        enemies = new Enemy[2];
        enemies[0] = new Enemy(200, 150, 30, 30);
        enemies[1] = new Enemy(400, 250, 30, 30);

        for (Enemy enemy : enemies) {
            add(enemy);
        }

        addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e) {
                int x = characterLabel.getLocation().x;
                int y = characterLabel.getLocation().y;

                int newX = x;
                int newY = y;

                switch (e.getKeyCode()) {
                    case KeyEvent.VK_W:
                        newY -= moveStep;
                        break;
                    case KeyEvent.VK_S:
                        newY += moveStep;
                        break;
                    case KeyEvent.VK_A:
                        newX -= moveStep;
                        break;
                    case KeyEvent.VK_D:
                        newX += moveStep;
                        break;
                }

                if (newX < 10) newX = 10;
                if (newX + characterLabel.getWidth() > 662) newX = 662 - characterLabel.getWidth();
                if (newY < 10) newY = 10;
                if (newY + characterLabel.getHeight() > 349) newY = 349 - characterLabel.getHeight();

                // Check collisions
                if (checkCollision(newX, newY)) {
                    return;
                }

                characterLabel.setLocation(newX, newY);
            }
        });

        setFocusable(true);
        requestFocusInWindow();
        setVisible(true);
    }

    private boolean checkCollision(int newX, int newY) {
        Rectangle characterRect = new Rectangle(newX, newY, characterLabel.getWidth(), characterLabel.getHeight());

        for (Obstacle obstacle : obstacles) {
            Rectangle obstacleRect = obstacle.getBounds();

            if (characterRect.intersects(obstacleRect)) {
                return true;
            }
        }

        for (Enemy enemy : enemies) {
            Rectangle enemyRect = enemy.getBounds();

            if (characterRect.intersects(enemyRect)) {
                openFightForm(character, enemy);
                return true;
            }
        }

        return false;
    }

    private Fight openFightForm(Character character, Enemy enemy) {
        Fight fightForm = new Fight(character, enemy);
        fightForm.setVisible(true);
        return fightForm;
    }


    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            Character character = new Mage("Имя персонажа", "Мужской");
            new MyForm2(character);
        });
    }
}
