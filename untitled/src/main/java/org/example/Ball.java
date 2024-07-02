package org.example;

import java.awt.*;

public class Ball {
    public float x, y;
    public float vx, vy;
    public float radius;

    public Ball(float x, float y, float radius, float vx, float vy) {
        this.x = x;
        this.y = y;
        this.radius = radius;
        this.vx = vx;
        this.vy = vy;
    }

    public void move() {
        x += vx;
        y += vy;
    }

    public void draw(Graphics g) {
        g.setColor(Color.BLUE);
        g.fillOval((int) (x - radius), (int) (y - radius), (int) (radius * 2), (int) (radius * 2));
    }

    public void checkCollision(int panelWidth, int panelHeight) {
        if (x - radius < 0 || x + radius > panelWidth) {
            vx = -vx;
        }
        if (y - radius < 0 || y + radius > panelHeight) {
            vy = -vy;
        }
    }

    public boolean checkCollisionWithRectObstacle(float ox, float oy, float oWidth, float oHeight) {
        return x + radius > ox && x - radius < ox + oWidth && y + radius > oy && y - radius < oy + oHeight;
    }

    public boolean checkCollisionWithCircleObstacle(float cx, float cy, float radius) {
        float dx = x - cx;
        float dy = y - cy;
        float distance = (float) Math.sqrt(dx * dx + dy * dy);
        return distance <= this.radius + radius;
    }

    public void reflectFromRectObstacle(float ox, float oy, float oWidth, float oHeight) {
        float closestX = Math.max(ox, Math.min(ox + oWidth, x));
        float closestY = Math.max(oy, Math.min(oy + oHeight, y));

        float dx = x - closestX;
        float dy = y - closestY;

        float normalX, normalY;
        if (dx == 0 && dy == 0) {
            normalX = 1.0f;
            normalY = 0.0f;
        } else {
            float length = (float) Math.sqrt(dx * dx + dy * dy);
            normalX = dx / length;
            normalY = dy / length;
        }

        float dotProduct = vx * normalX + vy * normalY;
        vx -= 2 * dotProduct * normalX;
        vy -= 2 * dotProduct * normalY;

        x += vx;
        y += vy;
    }

    public void reflectFromCircleObstacle(float cx, float cy, float radius) {
        float dx = x - cx;
        float dy = y - cy;
        float dist = (float) Math.sqrt(dx * dx + dy * dy);

        if (dist != 0) {
            dx /= dist;
            dy /= dist;
        }

        float dotProduct = vx * dx + vy * dy;
        vx -= 2 * dotProduct * dx;
        vy -= 2 * dotProduct * dy;
    }
}
