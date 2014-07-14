package example.Split_Temporary_Variable;

import java.lang.Math;


class Split_Temporary_Variable_refactor
{

        int _primaryForce = 10;
        int _secondaryForce = 10;
        int _mass;
        int _delay;

        public Split_Temporary_Variable_refactor(int mass , int delay)
        {
                this._mass = mass;
                this._delay = delay;
        }
        public double getDistanceTravelled (int time) 
        {
                double result;
                final double primaryAcc = _primaryForce / _mass;
                int primaryTime = Math.min(time, _delay);
                result = 0.5 * primaryAcc * primaryTime * primaryTime;
                int secondaryTime = time - _delay;
                if (secondaryTime > 0) {
                        double primaryVel = primaryAcc * _delay;
                        final double secondaryAcc = (_primaryForce + _secondaryForce) / _mass;
                        result += primaryVel * secondaryTime + 0.5 * secondaryAcc *
                                secondaryTime * secondaryTime;
                }
                return result;
        }

        public static void main(String args[])
        {
               Split_Temporary_Variable_refactor test = new  Split_Temporary_Variable_refactor(2, 10);
               System.out.println(test.getDistanceTravelled(20));

        }
}

