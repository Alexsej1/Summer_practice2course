package org.example;

public class Archer extends Character {
    public Archer(String name, String gender) {
        super(name, gender, "Лучник");
    }

    @Override
    public String attack() {
        return "Ядовитая стрела";
    }
}
