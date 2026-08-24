//-------------------------------------------------------
//
//  MyScene.h
//
//  Derived from MyThing.h by Jerry Tessendorf (2017)
//  Project: Assignment01
//
//  Description:
//  A place for scene generation.
//
//--------------------------------------------------------
#pragma once
#include <array>
#include "Vector.h"
#include "Color.h"
#include "PbaThing.h"

namespace pba
{
    class MyScene : public PbaThingyDingy
    {
    public:
        MyScene(const std::string nam = "Sphere");
        ~MyScene();

        void Init(const std::vector<std::string> &args);
        void Display();
        void Reset();

        void SetData(const std::vector<pba::Vector> &v, const std::vector<std::array<int, 3>> &f)
        {
            vertices = v;
            faces = f;
        }

    private:
        Vector border;
        std::vector<Vector> vertices;
        std::vector<std::array<int, 3>> faces;
    };

    pba::PbaThing CreateMyScene();
}
