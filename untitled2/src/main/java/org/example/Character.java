package org.example;

public abstract class Character {
    protected String name;
    protected String gender;
    protected String characterClass;

    public Character(String name, String gender, String characterClass) {
        this.name = name;
        this.gender = gender;
        this.characterClass = characterClass;
    }

    public String getName() {
        return name;
    }

    public String getGender() {
        return gender;
    }

    public String getCharacterClass() {
        return characterClass;
    }

    public abstract String attack();
}
