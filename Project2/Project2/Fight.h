// Fight.h
#pragma once
#include <string>
#include <ctime>
#include <cstdlib>
#include "Character.h"
#include "Enemy.h"
#include <Windows.h>

namespace Project2 {

    using namespace System;
    using namespace System::Windows::Forms;

    public ref class Fight : public System::Windows::Forms::Form
    {
    public:
        Fight(Character^ character, Enemy^ enemy)
            : character(character), enemy(enemy), rnd(gcnew Random())
        {
            InitializeComponent();

            String^ specialAbility = GetSpecialAbility(character);

            // ������������� ���������� � ��������� �����
            labelCharacterInfo->Text = String::Format("��������: {0}\n�����: {1}\n�����������: {2}", character->Name, character->CharacterClass, specialAbility);

            // ������������� ���������� � ����� ������
            labelEnemyInfo->Text = String::Format("����: {0}", enemy->Name);
            labelCharacterHealth->Text = String::Format("��������: {0}", characterHealth);
            labelEnemyHealth->Text = String::Format("��������: {0}", enemyHealth);
            labelCharacterAttack->Text = String::Format("�����: {0}", characterAttack);
            labelEnemyAttack->Text = String::Format("�����: {0}", enemyAttack);
        }

    protected:
        ~Fight()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::ComponentModel::Container^ components;
        Character^ character;
        Enemy^ enemy;
        Random^ rnd;
        int characterHealth = 100;
        int enemyHealth = 100;
        int characterAttack = 15;
        int enemyAttack = 15;

        System::Windows::Forms::Label^ labelCharacterInfo;
        System::Windows::Forms::Label^ labelEnemyInfo;
        System::Windows::Forms::Label^ labelCharacterHealth;
        System::Windows::Forms::Label^ labelEnemyHealth;
        System::Windows::Forms::Label^ labelCharacterAttack;
        System::Windows::Forms::Label^ labelEnemyAttack;
        System::Windows::Forms::Button^ buttonAttack;

        void InitializeComponent()
        {
            this->components = gcnew System::ComponentModel::Container();
            this->labelCharacterInfo = gcnew System::Windows::Forms::Label();
            this->labelEnemyInfo = gcnew System::Windows::Forms::Label();
            this->labelCharacterHealth = gcnew System::Windows::Forms::Label();
            this->labelEnemyHealth = gcnew System::Windows::Forms::Label();
            this->labelCharacterAttack = gcnew System::Windows::Forms::Label();
            this->labelEnemyAttack = gcnew System::Windows::Forms::Label();
            this->buttonAttack = gcnew System::Windows::Forms::Button();
            this->SuspendLayout();

            // 
            // labelCharacterInfo
            // 
            this->labelCharacterInfo->AutoSize = true;
            this->labelCharacterInfo->Location = System::Drawing::Point(10, 10);
            this->labelCharacterInfo->Name = L"labelCharacterInfo";
            this->labelCharacterInfo->Size = System::Drawing::Size(35, 13);
            this->labelCharacterInfo->TabIndex = 0;

            // 
            // labelEnemyInfo
            // 
            this->labelEnemyInfo->AutoSize = true;
            this->labelEnemyInfo->Location = System::Drawing::Point(160, 10);
            this->labelEnemyInfo->Name = L"labelEnemyInfo";
            this->labelEnemyInfo->Size = System::Drawing::Size(35, 13);
            this->labelEnemyInfo->TabIndex = 1;

            // 
            // labelCharacterHealth
            // 
            this->labelCharacterHealth->AutoSize = true;
            this->labelCharacterHealth->Location = System::Drawing::Point(10, 50);
            this->labelCharacterHealth->Name = L"labelCharacterHealth";
            this->labelCharacterHealth->Size = System::Drawing::Size(35, 13);
            this->labelCharacterHealth->TabIndex = 2;

            // 
            // labelEnemyHealth
            // 
            this->labelEnemyHealth->AutoSize = true;
            this->labelEnemyHealth->Location = System::Drawing::Point(160, 50);
            this->labelEnemyHealth->Name = L"labelEnemyHealth";
            this->labelEnemyHealth->Size = System::Drawing::Size(35, 13);
            this->labelEnemyHealth->TabIndex = 3;

            // 
            // labelCharacterAttack
            // 
            this->labelCharacterAttack->AutoSize = true;
            this->labelCharacterAttack->Location = System::Drawing::Point(10, 70);
            this->labelCharacterAttack->Name = L"labelCharacterAttack";
            this->labelCharacterAttack->Size = System::Drawing::Size(35, 13);
            this->labelCharacterAttack->TabIndex = 4;

            // 
            // labelEnemyAttack
            // 
            this->labelEnemyAttack->AutoSize = true;
            this->labelEnemyAttack->Location = System::Drawing::Point(160, 70);
            this->labelEnemyAttack->Name = L"labelEnemyAttack";
            this->labelEnemyAttack->Size = System::Drawing::Size(35, 13);
            this->labelEnemyAttack->TabIndex = 5;

            // 
            // buttonAttack
            // 
            this->buttonAttack->Location = System::Drawing::Point(10, 120);
            this->buttonAttack->Name = L"buttonAttack";
            this->buttonAttack->Size = System::Drawing::Size(75, 23);
            this->buttonAttack->TabIndex = 6;
            this->buttonAttack->Text = L"����";
            this->buttonAttack->UseVisualStyleBackColor = true;
            this->buttonAttack->Click += gcnew System::EventHandler(this, &Fight::buttonAttack_Click);

            // 
            // Fight
            // 
            this->ClientSize = System::Drawing::Size(400, 200);
            this->Controls->Add(this->labelCharacterInfo);
            this->Controls->Add(this->labelEnemyInfo);
            this->Controls->Add(this->labelCharacterHealth);
            this->Controls->Add(this->labelEnemyHealth);
            this->Controls->Add(this->labelCharacterAttack);
            this->Controls->Add(this->labelEnemyAttack);
            this->Controls->Add(this->buttonAttack);
            this->Name = L"Fight";
            this->Text = L"Fight";
            this->ResumeLayout(false);
            this->PerformLayout();

        }

        String^ GetSpecialAbility(Character^ character)
        {
            if (character->CharacterClass == "���")
            {
                return "�������� ���";
            }
            else if (character->CharacterClass == "������")
            {
                return "�������� ������";
            }
            else if (character->CharacterClass == "����")
            {
                return "���� �����";
            }
            else
            {
                return "��� �����������";
            }
        }

        void buttonAttack_Click(System::Object^ sender, System::EventArgs^ e)
        {
            // ��� ���������
            if (rnd->Next(100) >= 85) // 15% ���� ���������
            {
                MessageBox::Show("���� ���������");
            }
            else
            {
                int damage = characterAttack;
                enemyHealth -= damage;
                MessageBox::Show(String::Format("�������� ����� {0} �����", damage));
            }

            // �������� �� ����� ����
            if (enemyHealth <= 0)
            {
                MessageBox::Show("������!");
                this->Close(); // �������� �����
                return;
            }

            // ��� �����
            if (rnd->Next(100) >= 85) // 15% ���� ���������
            {
                MessageBox::Show("�������� ���������");
            }
            else
            {
                int damage = enemyAttack;
                characterHealth -= damage;
                MessageBox::Show(String::Format("���� ����� {0} �����", damage));
            }

            // ���������� ���������� � ��������
            labelCharacterHealth->Text = String::Format("��������: {0}", characterHealth);
            labelEnemyHealth->Text = String::Format("��������: {0}", enemyHealth);

            // �������� �� ����� ����
            if (characterHealth <= 0)
            {
                MessageBox::Show("���� ���������. ���������!");
                this->Close(); // �������� �����
                return;
            }
        }
    };
}
