package org.example;

public class Mage extends Character {
    public Mage(String name, String gender) {
        super(name, gender, "Маг");
    }

    @Override
    public String attack() {
        return "Огненный шар";
    }
}
