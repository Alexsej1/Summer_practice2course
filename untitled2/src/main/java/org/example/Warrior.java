package org.example;

public class Warrior extends Character {
    public Warrior(String name, String gender) {
        super(name, gender, "Воин");
    }

    @Override
    public String attack() {
        return "Удар мечом";
    }
}
