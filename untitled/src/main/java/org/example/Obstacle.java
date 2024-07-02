package org.example;

import java.awt.*;

public class Obstacle {
    public float x, y;
    public float width, height;
    public boolean isCircle;

    public Obstacle(float x, float y, float width, float height, boolean isCircle) {
        this.x = x;
        this.y = y;
        this.width = width;
        this.height = height;
        this.isCircle = isCircle;
    }

    public void draw(Graphics g) {
        g.setColor(Color.RED);
        if (isCircle) {
            g.fillOval((int) x, (int) y, (int) width, (int) height);
        } else {
            g.fillRect((int) x, (int) y, (int) width, (int) height);
        }
    }

    public Vector2D getNormal(float px, float py, Ball ball) {
        if (isCircle) {
            float cx = x + width / 2;
            float cy = y + height / 2;
            float dx = px - cx;
            float dy = py - cy;
            Vector2D normal = new Vector2D(dx, dy);
            normal.normalize();
            return normal;
        } else {
            float ballCenterX = ball.x;
            float ballCenterY = ball.y;

            float dx = ballCenterX - (x + width / 2);
            float dy = ballCenterY - (y + height / 2);

            float length = (float) Math.sqrt(dx * dx + dy * dy);
            dx /= length;
            dy /= length;

            return new Vector2D(dx, dy);
        }
    }
}
