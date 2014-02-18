package com.design.template;

abstract class HouseTemplate
{
        public final void buildHouse()
        {
                buildFundation();
                buildPillars();
                buildWalls();
                buildWindows();
                System.out.println("House is built!!");
        }          

        private void buildWindows()
        {
                System.out.println("Building Galss Windows");              
        }

        public abstract void buildWalls();
        public abstract void buildPillars();
        private void buildFundation()
        {
                System.out.println("Building Fundations");
        }
}

class WoodenHouse extends HouseTemplate
{
        public void buildWalls()
        {
                System.out.println("Building Wooden walls!!");
        }

        public void buildPillars()
        {
                System.out.println("Building Wooden Pillars!!");
        }
}

class GlassHouse extends HouseTemplate
{
        public void buildWalls()
        {
                System.out.println("Building Glass walls!!");
        }

        public void buildPillars()
        {
                System.out.println("Building Glass Pillars!!");
        }
}


public class template
{
        public static void main(String args[])
        {
                HouseTemplate house = new WoodenHouse();
                house.buildHouse();
                
                System.out.println();

                house = new GlassHouse();
                house.buildHouse();
                        
        }
}

