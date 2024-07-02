package org.example;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.util.ArrayList;
import java.util.List;

public class MyFrame extends JFrame {
    private int score = 0;
    private JLabel label;
    private JPanel panel;
    private Timer timer;
    private Ball ball;
    private List<Obstacle> obstacles;

    private float leverLength;
    private float leverAngle;
    private float leverBaseX;
    private float leverBaseY;
    private boolean leverIsDown;

    public MyFrame() {
        setTitle("Java Swing Example");
        setSize(800, 450);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        label = new JLabel();
        panel = new JPanel() {
            @Override
            protected void paintComponent(Graphics g) {
                super.paintComponent(g);
                drawPanel(g);
            }
        };

        panel.setPreferredSize(new Dimension(360, 418));
        panel.setBackground(Color.WHITE);
        add(label, BorderLayout.NORTH);
        add(panel, BorderLayout.CENTER);

        ball = new Ball(100, 100, 10, 5, 5);
        obstacles = new ArrayList<>();
        obstacles.add(new Obstacle(280, 150, 50, 30, false));
        obstacles.add(new Obstacle(20, 150, 50, 30, false));
        obstacles.add(new Obstacle(150, 100, 40, 40, true));
        obstacles.add(new Obstacle(50, 50, 40, 40, true));
        obstacles.add(new Obstacle(250, 50, 40, 40, true));
        obstacles.add(new Obstacle(120, 408, 80, 10, false));

        leverLength = 40;
        leverAngle = 45;
        leverBaseX = 180;
        leverBaseY = 398;

        timer = new Timer(30, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                ball.move();
                ball.checkCollision(panel.getWidth(), panel.getHeight());
                if (checkCollisionsWithObstacles()) {
                    timer.stop();
                    score -= 10;
                    JOptionPane.showMessageDialog(null, "Game Over! Your score: " + score);
                }
                panel.repaint();
            }
        });
        timer.start();

        addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e) {
                if (e.getKeyCode() == KeyEvent.VK_SPACE && !leverIsDown) {
                    leverIsDown = true;
                    leverAngle = -45;
                    applyLeverForce();
                    panel.repaint();
                }
            }

            @Override
            public void keyReleased(KeyEvent e) {
                if (e.getKeyCode() == KeyEvent.VK_SPACE && leverIsDown) {
                    leverIsDown = false;
                    leverAngle = 45;
                    panel.repaint();
                }
            }
        });
        setFocusable(true);
        setFocusTraversalKeysEnabled(false);
    }

    private void drawPanel(Graphics g) {
        g.drawRect(0, 0, panel.getWidth() - 1, panel.getHeight() - 1);

        drawLever(g);

        ball.draw(g);
        for (Obstacle obstacle : obstacles) {
            obstacle.draw(g);
        }
        g.fillRect(120, panel.getHeight() - 10, 80, 10);

        drawScore(g);
    }

    private void drawScore(Graphics g) {
        String scoreText = "Score: " + score;
        g.drawString(scoreText, 10, 10);
    }

    private void drawLever(Graphics g) {
        float leverEndX = leverBaseX + leverLength * (float) Math.sin(Math.toRadians(leverAngle));
        float leverEndY = leverBaseY - leverLength * (float) Math.cos(Math.toRadians(leverAngle));

        g.setColor(Color.GREEN);
        g.drawLine((int) leverBaseX, (int) leverBaseY, (int) leverEndX, (int) leverEndY);
    }

    private boolean checkCollisionsWithObstacles() {
        for (Obstacle obstacle : obstacles) {
            if (obstacle.isCircle) {
                if (ball.checkCollisionWithCircleObstacle(obstacle.x + obstacle.width / 2, obstacle.y + obstacle.height / 2, obstacle.width / 2)) {
                    ball.reflectFromCircleObstacle(obstacle.x + obstacle.width / 2, obstacle.y + obstacle.height / 2, obstacle.width / 2);
                    score += 10;
                }
            } else {
                if (ball.checkCollisionWithRectObstacle(obstacle.x, obstacle.y, obstacle.width, obstacle.height)) {
                    if (obstacle.y + obstacle.height == panel.getHeight()) {
                        return true;
                    }
                    Vector2D normal = obstacle.getNormal(ball.x, ball.y, ball);
                    float dotProduct = ball.vx * normal.x + ball.vy * normal.y;
                    ball.vx -= 2 * dotProduct * normal.x;
                    ball.vy -= 2 * dotProduct * normal.y;
                    score += 10;
                }
            }
        }
        return false;
    }

    private void applyLeverForce() {
        float forceAngle = (float) Math.toRadians(leverAngle - 90);
        float forceMagnitude = 8.0f;

        float forceX = forceMagnitude * (float) Math.cos(forceAngle);
        float forceY = forceMagnitude * (float) Math.sin(forceAngle);

        ball.vx += forceX;
        ball.vy += forceY;
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            MyFrame frame = new MyFrame();
            frame.pack();
            frame.setLocationRelativeTo(null);
            frame.setVisible(true);
        });
    }
}
