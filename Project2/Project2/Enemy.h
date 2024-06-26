#pragma once

#include <Windows.h>
#include <iostream>

namespace Project2 {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class Enemy : public System::Windows::Forms::Panel
    {
    public:
        Enemy(int x, int y, int width, int height)
        {
            this->Location = System::Drawing::Point(x, y);
            this->Size = System::Drawing::Size(width, height);
            this->BackColor = Color::Red; 
        }
    };
}
