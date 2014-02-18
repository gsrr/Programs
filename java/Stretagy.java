package com.design.Stretage;

interface IShape
{
        public void draw();
}

class Square implements IShape
{
        public void draw()
        {
                System.out.println("This is a Square!!");
        }
}

class Triangle implements IShape
{
        public void draw()
        {
                System.out.println("This is a Triangle!!");
        }
}

class Circle implements IShape
{
        public void draw()
        {
                System.out.println("This is a Circle!!");
        }
}

public class Stretagy
{
        public static void main(String args[])
        {
                IShape shape = new Square();
                shape.draw();
        }
}
