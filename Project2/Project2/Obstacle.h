#pragma once

namespace Project2 {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class Obstacle : public PictureBox
    {
    public:
        Obstacle(int x, int y, int width, int height)
        {
            this->Location = System::Drawing::Point(x, y);
            this->Size = System::Drawing::Size(width, height);
            this->SizeMode = PictureBoxSizeMode::StretchImage; // Масштабируем изображение для заполнения PictureBox
            this->Image = System::Drawing::Image::FromFile("Home.png"); // Путь к файлу с изображением препятствия
        }
    };
}
