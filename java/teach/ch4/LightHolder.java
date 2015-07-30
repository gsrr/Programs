import java.lang.*;
import java.io.*;


public class LightHolder
{
        Light[] ls_;
        Light off_;

        LightHolder(Light[] ls, Light off)
        {
                ls_ = ls;
                off_ = off;              
        }
        public void display()
        {
                int current_state = 0;
                while(true)
                {
                        current_state = current_state % 3;
                        for(int i = 0 ; i < ls_.length ; i++)
                        {
                                if( i == current_state)
                                {
                                        System.out.print(ls_[i].getColor());
                                }
                                else
                                {
                                        System.out.print(off_.getColor());
                                }
                                System.out.print(" ");
                        }
                        System.out.println();
                        //System.out.println(System.getProperty("os.name"));
                        try
                        {

                                //Process p = Runtime.getRuntime().exec("clear");
                                //p.waitFor();
                                Thread.sleep(ls_[current_state].getTimeOut()*1000);
                                System.out.print("\033[H\033[2J");
                        }
                        catch(InterruptedException e)
                        {
                                e.printStackTrace();
                                ;
                        }
                        /*
                        catch(IOException e)
                        {

                                e.printStackTrace();
                                ;
                        }
                        */
                        current_state++;
                        
                }
        }
}
