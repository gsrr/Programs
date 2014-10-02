package example.Split_Temporary_Variable;

import java.lang.Math;


class Split_Temporary_Variable
{

        int _primaryForce = 10;
        int _secondaryForce = 10;
        int _mass;
        int _delay;

        public Split_Temporary_Variable(int mass , int delay)
        {
                this._mass = mass;
                this._delay = delay;
        }
        public double getDistanceTravelled (int time) 
        {
                double result;
                double acc = _primaryForce / _mass;
                int primaryTime = Math.min(time, _delay);
                result = 0.5 * acc * primaryTime * primaryTime;
                int secondaryTime = time - _delay;
                if (secondaryTime > 0) {
                        double primaryVel = acc * _delay;
                        acc = (_primaryForce + _secondaryForce) / _mass;
                        result += primaryVel * secondaryTime + 0.5 * acc *
                                secondaryTime * secondaryTime;
                }
                return result;
        }

        public static void main(String args[])
        {
               Split_Temporary_Variable test = new  Split_Temporary_Variable(2, 10);
               System.out.println(test.getDistanceTravelled(20));

        }
}

