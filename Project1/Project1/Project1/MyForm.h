#pragma once

#include <cmath>
#include <vector>

namespace Project1 {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Collections::Generic;

    public ref class Vector2D {
    public:
        float x, y;

        Vector2D(float x, float y) : x(x), y(y) {}

        void Normalize() {
            float length = Math::Sqrt(x * x + y * y);
            if (length > 0) {
                x /= length;
                y /= length;
            }
        }

        static Vector2D^ FromPoints(float x1, float y1, float x2, float y2) {
            return gcnew Vector2D(x2 - x1, y2 - y1);
        }
    };

    public ref class Ball {
    public:
        float x, y;
        float vx, vy;
        float radius;

        Ball(float x, float y, float radius, float vx, float vy)
            : x(x), y(y), radius(radius), vx(vx), vy(vy) {}

        void Move() {
            x += vx;
            y += vy;
        }

        void Draw(Graphics^ g) {
            g->FillEllipse(Brushes::Blue, x - radius, y - radius, radius * 2, radius * 2);
        }

        void CheckCollision(int panelWidth, int panelHeight) {
            
            if (x - radius < 0 || x + radius > panelWidth) {
                vx = -vx;
            }
            // Столкновение с верхним и нижним краем панели
            if (y - radius < 0 || y + radius > panelHeight) {
                vy = -vy;
            }
        }

        bool CheckCollisionWithRectObstacle(float ox, float oy, float oWidth, float oHeight) {
           
            return x + radius > ox && x - radius < ox + oWidth && y + radius > oy && y - radius < oy + oHeight;
        }

        bool CheckCollisionWithCircleObstacle(float cx, float cy, float radius) {
       
            float dx = x - cx;
            float dy = y - cy;
            float distance = Math::Sqrt(dx * dx + dy * dy);
            return distance <= this->radius + radius;
        }

        void ReflectFromRectObstacle(float ox, float oy, float oWidth, float oHeight) {
          
            float closestX = Math::Max(ox, Math::Min(ox + oWidth, x));
            float closestY = Math::Max(oy, Math::Min(oy + oHeight, y));

           
            float dx = x - closestX;
            float dy = y - closestY;

            
            float normalX, normalY;
            if (dx == 0 && dy == 0) {
                
                normalX = 1.0f;
                normalY = 0.0f;
            }
            else {
               
                float length = Math::Sqrt(dx * dx + dy * dy);
                normalX = dx / length;
                normalY = dy / length;
            }

            
            float dotProduct = vx * normalX + vy * normalY;

            
            vx -= 2 * dotProduct * normalX;
            vy -= 2 * dotProduct * normalY;

          
            x += vx;
            y += vy;
        }

        void ReflectFromCircleObstacle(float cx, float cy, float radius) {
           
            float dx = x - cx;
            float dy = y - cy;
            float dist = Math::Sqrt(dx * dx + dy * dy);

            if (dist != 0) {
                dx /= dist;
                dy /= dist;
            }

            float dotProduct = vx * dx + vy * dy;
            vx -= 2 * dotProduct * dx;
            vy -= 2 * dotProduct * dy;
        }
    };



    public ref class Obstacle {
    public:
        float x, y;
        float width, height;
        bool isCircle;

        Obstacle(float x, float y, float width, float height, bool isCircle)
            : x(x), y(y), width(width), height(height), isCircle(isCircle) {}

        void Draw(Graphics^ g) {
            if (isCircle) {
                g->FillEllipse(Brushes::Red, x, y, width, height);
            }
            else {
                g->FillRectangle(Brushes::Red, x, y, width, height);
            }
        }

        Vector2D^ GetNormal(float px, float py, Ball^ ball) {
            if (isCircle) {
                // Вычисление нормали для круглого препятствия
                float cx = x + width / 2; // Центр круга по X
                float cy = y + height / 2; // Центр круга по Y
                float dx = px - cx; // Разница по X
                float dy = py - cy; // Разница по Y
                Vector2D^ normal = gcnew Vector2D(dx, dy);
                normal->Normalize(); // Нормализация вектора
                return normal;
            }
            else {
                // Вычисление нормали для прямоугольного препятствия
                float ballCenterX = ball->x;
                float ballCenterY = ball->y;

                float dx = ballCenterX - (x + width / 2);
                float dy = ballCenterY - (y + height / 2);

                // Нормализуем вектор
                float length = Math::Sqrt(dx * dx + dy * dy);
                dx /= length;
                dy /= length;

                // Вектор нормали к поверхности препятствия
                return gcnew Vector2D(dx, dy);
            }
        }
    };


    /// <summary>
    /// Summary for MyForm
    /// </summary>
    public ref class MyForm : public System::Windows::Forms::Form
    {
    public:
        MyForm(void)
        {
            InitializeComponent();
            //
            //TODO: Add the constructor code here
            //

            ball = gcnew Ball(100, 100, 10, 5, 5);
            obstacles = gcnew List<Obstacle^>();
            // Добавление препятствий
            obstacles->Add(gcnew Obstacle(280, 150, 50, 30, false)); // Прямоугольное препятствие
            obstacles->Add(gcnew Obstacle(20, 150, 50, 30, false)); // Прямоугольное препятствие
            obstacles->Add(gcnew Obstacle(150, 100, 40, 40, true)); // Круглое препятствие
            obstacles->Add(gcnew Obstacle(50, 50, 40, 40, true)); // Круглое препятствие
            obstacles->Add(gcnew Obstacle(250, 50, 40, 40, true)); // Круглое препятствие
            // Исправленные параметры для нижнего препятствия (нижний прямоугольник)
            obstacles->Add(gcnew Obstacle(120, panel1->Height - 10, 80, 10, false)); // Черный прямоугольник внизу игрового поля

            // Инициализация рычага
            leverLength = 40; // Длина рычага
            leverAngle = 45;   // Начальный угол поворота рычага
            leverBaseX = panel1->Width / 2; // Базовая точка рычага (середина панели)
            leverBaseY = panel1->Height - 20; // Нижняя граница панели (крепление рычага)

            timer1->Interval = 30; // Интервал таймера для обновления анимации
            timer1->Start();
            this->KeyDown += gcnew KeyEventHandler(this, &MyForm::MyForm_KeyDown); // Подписываемся на событие нажатия клавиш
            this->KeyUp += gcnew KeyEventHandler(this, &MyForm::MyForm_KeyUp);     // Подписываемся на событие отпускания клавиш
        }

    protected:
        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        ~MyForm()
        {
            if (components)
            {
                delete components;
            }
        }
    private: int score = 0;
    private: System::Windows::Forms::Label^ label1;
    private: System::Windows::Forms::Panel^ panel1;
    private: System::Windows::Forms::Timer^ timer1;

    private: System::ComponentModel::IContainer^ components;
    private: Ball^ ball; // Объявление переменной ball
    private: List<Obstacle^>^ obstacles; // Коллекция препятствий

           // Переменные для рычага
    private:
        float leverLength;
        float leverAngle;
        float leverBaseX;
        float leverBaseY;
        bool leverIsDown;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->components = (gcnew System::ComponentModel::Container());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->panel1 = (gcnew System::Windows::Forms::Panel());
            this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
            this->SuspendLayout();
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Location = System::Drawing::Point(151, 64);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(0, 16);
            this->label1->TabIndex = 0;
            // 
            // panel1
            // 
            this->panel1->Location = System::Drawing::Point(184, 41);
            this->panel1->Name = L"panel1";
            this->panel1->Size = System::Drawing::Size(448, 418);
            this->panel1->TabIndex = 1;
            this->panel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::panel1_Paint);
            // 
            // timer1
            // 
            this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
            // 
            // MyForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(800, 450);
            this->Controls->Add(this->panel1);
            this->Controls->Add(this->label1);
            this->Name = L"MyForm";
            this->Text = L"MyForm";
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion

    private: System::Void panel1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
        e->Graphics->DrawRectangle(Pens::Black, 0, 0, panel1->Width - 1, panel1->Height - 1);

        DrawLever(e->Graphics);

        ball->Draw(e->Graphics);
        for each (Obstacle ^ obstacle in obstacles) {
            obstacle->Draw(e->Graphics);
        }
        e->Graphics->FillRectangle(Brushes::Black, 120, panel1->Height - 10, 80, 10);

        DrawScore(e->Graphics);
    }

private: void DrawScore(Graphics^ g) {
    String^ scoreText = "Score: " + score;
    g->DrawString(scoreText, SystemFonts::DefaultFont, Brushes::Black, 10, 10);
}


    private: void DrawLever(Graphics^ g) {
        float leverEndX = leverBaseX + leverLength * (float)Math::Sin(leverAngle);
        float leverEndY = leverBaseY - leverLength * (float)Math::Cos(leverAngle);

        g->DrawLine(Pens::Green, leverBaseX, leverBaseY, leverEndX, leverEndY);
    }

    private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
        ball->Move();
        ball->CheckCollision(panel1->Width, panel1->Height);
        if (CheckCollisionsWithObstacles()) {
            timer1->Stop(); 
            score -= 10; 
            MessageBox::Show("Game Over! Your score: " + score);
        }
        panel1->Invalidate(); 
    }


    private: bool CheckCollisionsWithObstacles() {
        for each (Obstacle ^ obstacle in obstacles) {
            if (obstacle->isCircle) {
                if (ball->CheckCollisionWithCircleObstacle(obstacle->x + obstacle->width / 2, obstacle->y + obstacle->height / 2, obstacle->width / 2)) {
                    ball->ReflectFromCircleObstacle(obstacle->x + obstacle->width / 2, obstacle->y + obstacle->height / 2, obstacle->width / 2);
                    score += 10;
                }
            }
            else {
                if (ball->CheckCollisionWithRectObstacle(obstacle->x, obstacle->y, obstacle->width, obstacle->height)) {
                    Vector2D^ normal = obstacle->GetNormal(ball->x, ball->y, ball);
                    float dotProduct = ball->vx * normal->x + ball->vy * normal->y;
                    ball->vx -= 2 * dotProduct * normal->x;
                    ball->vy -= 2 * dotProduct * normal->y;
                    score += 10;
                }
            }
        }

        for each (Obstacle ^ obstacle in obstacles) {
            if (!obstacle->isCircle && obstacle->y + obstacle->height == panel1->Height) {
                if (ball->CheckCollisionWithRectObstacle(120, panel1->Height - 10, 80, 10)) {
                    return true; 
                }
            }
        }

        return false;
    }



    private: System::Void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
        if (e->KeyCode == Keys::Space && !leverIsDown) {
            leverIsDown = true;
            leverAngle = -Math::PI / 4; 
            ApplyLeverForce();
            panel1->Invalidate();
        }
    }

    private: System::Void MyForm_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
        if (e->KeyCode == Keys::Space && leverIsDown) {
            leverIsDown = false;
            leverAngle = 45; 
            panel1->Invalidate();
        }
    }

    private: void ApplyLeverForce() {
        float forceAngle = leverAngle - Math::PI / 2; 
        float forceMagnitude = 8.0f; 

        float forceX = forceMagnitude * (float)Math::Cos(forceAngle);
        float forceY = forceMagnitude * (float)Math::Sin(forceAngle);

        ball->vx += forceX;
        ball->vy += forceY;
    }
    };
}

