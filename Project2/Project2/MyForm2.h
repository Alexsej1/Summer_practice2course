#pragma once

#include "Character.h"
#include "Obstacle.h"
#include "Enemy.h"
#include "Fight.h" // Включаем заголовок для формы Fight

namespace Project2 {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class MyForm2 : public System::Windows::Forms::Form
    {
    public:
        MyForm2(Character^ character)
        {
            InitializeComponent();

            this->character = character; // Сохраняем переданный персонаж

            labelName->Text = "Имя: " + character->Name;
            labelGender->Text = "Пол: " + character->Gender;
            labelClass->Text = "Класс: " + character->CharacterClass; 

            this->KeyPreview = true;
            this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm2::OnKeyDown);

            obstacles = gcnew array<Obstacle^>(5);
            obstacles[0] = gcnew Obstacle(150, 100, 50, 50);
            obstacles[1] = gcnew Obstacle(300, 200, 50, 50);
            obstacles[2] = gcnew Obstacle(450, 150, 50, 50);
            obstacles[3] = gcnew Obstacle(100, 300, 50, 50);
            obstacles[4] = gcnew Obstacle(500, 50, 50, 50);

            for each (Obstacle ^ obstacle in obstacles)
            {
                this->Controls->Add(obstacle);
            }

            // Создание врагов
            enemies = gcnew array<Enemy^>(2);
            enemies[0] = gcnew Enemy(200, 150, 30, 30);
            enemies[1] = gcnew Enemy(400, 250, 30, 30);

            for each (Enemy ^ enemy in enemies)
            {
                this->Controls->Add(enemy);
            }
        }

    protected:
        ~MyForm2()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        Character^ character;
        System::ComponentModel::Container^ components;

        System::Windows::Forms::Label^ labelName;
        System::Windows::Forms::Label^ labelGender;
        System::Windows::Forms::Label^ labelClass;
        System::Windows::Forms::PictureBox^ characterPictureBox;
        System::Windows::Forms::Panel^ topBorder;
        System::Windows::Forms::Panel^ bottomBorder;
        System::Windows::Forms::Panel^ leftBorder;
        System::Windows::Forms::Panel^ rightBorder;
        array<Obstacle^>^ obstacles;
        array<Enemy^>^ enemies; 

        const int moveStep = 10;

        void InitializeComponent(void)
        {
            this->labelName = (gcnew System::Windows::Forms::Label());
            this->labelGender = (gcnew System::Windows::Forms::Label());
            this->labelClass = (gcnew System::Windows::Forms::Label());
            this->characterPictureBox = (gcnew System::Windows::Forms::PictureBox());
            this->topBorder = (gcnew System::Windows::Forms::Panel());
            this->bottomBorder = (gcnew System::Windows::Forms::Panel());
            this->leftBorder = (gcnew System::Windows::Forms::Panel());
            this->rightBorder = (gcnew System::Windows::Forms::Panel());
            this->SuspendLayout();

            // 
            // labelName
            // 
            this->labelName->AutoSize = true;
            this->labelName->Location = System::Drawing::Point(10, 10);
            this->labelName->Name = L"labelName";
            this->labelName->Size = System::Drawing::Size(35, 13);
            this->labelName->TabIndex = 0;

            // 
            // labelGender
            // 
            this->labelGender->AutoSize = true;
            this->labelGender->Location = System::Drawing::Point(10, 30);
            this->labelGender->Name = L"labelGender";
            this->labelGender->Size = System::Drawing::Size(35, 13);
            this->labelGender->TabIndex = 1;

            // 
            // labelClass
            // 
            this->labelClass->AutoSize = true;
            this->labelClass->Location = System::Drawing::Point(10, 50);
            this->labelClass->Name = L"labelClass";
            this->labelClass->Size = System::Drawing::Size(35, 13);
            this->labelClass->TabIndex = 2;

            // 
            // characterPictureBox
            // 
            this->characterPictureBox->Location = System::Drawing::Point(100, 150);
            this->characterPictureBox->Name = L"characterPictureBox";
            this->characterPictureBox->Size = System::Drawing::Size(30, 30);
            this->characterPictureBox->SizeMode = PictureBoxSizeMode::Zoom;
            this->characterPictureBox->Image = Image::FromFile("unnamed.jpg"); 
            this->Controls->Add(this->characterPictureBox);

            // 
            // topBorder
            // 
            this->topBorder->BackColor = System::Drawing::Color::Black;
            this->topBorder->Location = System::Drawing::Point(0, 0);
            this->topBorder->Name = L"topBorder";
            this->topBorder->Size = System::Drawing::Size(672, 10);
            this->Controls->Add(this->topBorder);

            // 
            // bottomBorder
            // 
            this->bottomBorder->BackColor = System::Drawing::Color::Black;
            this->bottomBorder->Location = System::Drawing::Point(0, 349);
            this->bottomBorder->Name = L"bottomBorder";
            this->bottomBorder->Size = System::Drawing::Size(672, 10);
            this->Controls->Add(this->bottomBorder);

            // 
            // leftBorder
            // 
            this->leftBorder->BackColor = System::Drawing::Color::Black;
            this->leftBorder->Location = System::Drawing::Point(0, 0);
            this->leftBorder->Name = L"leftBorder";
            this->leftBorder->Size = System::Drawing::Size(10, 359);
            this->Controls->Add(this->leftBorder);

            // 
            // rightBorder
            // 
            this->rightBorder->BackColor = System::Drawing::Color::Black;
            this->rightBorder->Location = System::Drawing::Point(662, 0);
            this->rightBorder->Name = L"rightBorder";
            this->rightBorder->Size = System::Drawing::Size(10, 359);
            this->Controls->Add(this->rightBorder);

            // 
            // MyForm2
            // 
            this->BackColor = System::Drawing::Color::Green;
            this->ClientSize = System::Drawing::Size(672, 359);
            this->Name = L"MyForm2";
            this->Text = L"MyForm2";

            // Добавляем фоновое изображение
            this->BackgroundImage = Image::FromFile("bg4.png");
            this->BackgroundImageLayout = ImageLayout::Stretch; 

            this->ResumeLayout(false);
            this->PerformLayout();
        }


        void OnKeyDown(Object^ sender, KeyEventArgs^ e)
        {
            int x = characterPictureBox->Location.X;
            int y = characterPictureBox->Location.Y;

            int newX = x;
            int newY = y;

            if (e->KeyCode == Keys::W)
            {
                newY -= moveStep;
            }
            else if (e->KeyCode == Keys::S)
            {
                newY += moveStep;
            }
            else if (e->KeyCode == Keys::A)
            {
                newX -= moveStep;
            }
            else if (e->KeyCode == Keys::D)
            {
                newX += moveStep;
            }

            if (newX < 10) newX = 10;
            if (newX + characterPictureBox->Width > 662) newX = 662 - characterPictureBox->Width;
            if (newY < 10) newY = 10;
            if (newY + characterPictureBox->Height > 349) newY = 349 - characterPictureBox->Height;

            if (CheckCollision(newX, newY))
            {
                return;
            }

            characterPictureBox->Location = System::Drawing::Point(newX, newY);
        }

        bool CheckCollision(int newX, int newY)
        {
            System::Drawing::Rectangle characterRect = characterPictureBox->Bounds;

            for each (Obstacle ^ obstacle in obstacles)
            {
                System::Drawing::Rectangle obstacleRect = obstacle->Bounds;

                if (newX < obstacleRect.Right && newX + characterRect.Width > obstacleRect.Left &&
                    newY < obstacleRect.Bottom && newY + characterRect.Height > obstacleRect.Top)
                {
                    return true; 
                }
            }

            for each (Enemy ^ enemy in enemies)
            {
                System::Drawing::Rectangle enemyRect = enemy->Bounds;

                if (newX < enemyRect.Right && newX + characterRect.Width > enemyRect.Left &&
                    newY < enemyRect.Bottom && newY + characterRect.Height > enemyRect.Top)
                {
                    OpenFightForm(character, enemy); 
                    return true;
                }
            }

            return false; 
        }

        void OpenFightForm(Character^ character, Enemy^ enemy)
        {
            Fight^ fightForm = gcnew Fight(character, enemy);

            fightForm->ShowDialog();
        }

    };
}
