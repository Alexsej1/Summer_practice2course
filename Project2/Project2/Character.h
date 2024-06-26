



// Character.h
#pragma once
#include <string>

public ref class Character
{
protected:
    System::String^ name;
    System::String^ gender;
    System::String^ characterClass;

public:
    Character(System::String^ name, System::String^ gender, System::String^ characterClass)
        : name(name), gender(gender), characterClass(characterClass)
    {
    }

    property System::String^ Name {
        System::String^ get() { return name; }
    }

    property System::String^ Gender {
        System::String^ get() { return gender; }
    }

    property System::String^ CharacterClass {
        System::String^ get() { return characterClass; }
    }

    // Виртуальная функция для атаки
    virtual System::String^ Attack()
    {
        return "Нет способности";
    }
};

// Mage.h
#pragma once
#include "Character.h"

public ref class Mage : public Character
{
public:
    Mage(System::String^ name, System::String^ gender)
        : Character(name, gender, "Маг")
    {
    }

    virtual System::String^ Attack() override
    {
        return "Огненный шар";
    }
};

// Warrior.h
#pragma once
#include "Character.h"

public ref class Warrior : public Character
{
public:
    Warrior(System::String^ name, System::String^ gender)
        : Character(name, gender, "Воин")
    {
    }

    virtual System::String^ Attack() override
    {
        return "Удар мечом";
    }
};

// Archer.h
#pragma once
#include "Character.h"

public ref class Archer : public Character
{
public:
    Archer(System::String^ name, System::String^ gender)
        : Character(name, gender, "Лучник")
    {
    }

    virtual System::String^ Attack() override
    {
        return "Ядовитая стрела";
    }
};












