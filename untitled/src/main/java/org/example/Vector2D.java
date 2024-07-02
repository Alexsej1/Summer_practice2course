package org.example;

public class Vector2D {
    public float x, y;

    public Vector2D(float x, float y) {
        this.x = x;
        this.y = y;
    }

    public void normalize() {
        float length = (float) Math.sqrt(x * x + y * y);
        if (length > 0) {
            x /= length;
            y /= length;
        }
    }

    public static Vector2D fromPoints(float x1, float y1, float x2, float y2) {
        return new Vector2D(x2 - x1, y2 - y1);
    }
}
