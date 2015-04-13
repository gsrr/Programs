import java.io.*;
import java.util.*;

public class FaultExample
{
        boolean isStringPerm(String str1, String str2)
        {
                Hashtable ht = new Hashtable();
                for(int i = 0 ; i < str1.length()-1 ; i++) //Fault 1, the variable i should smaller than str1.length() 
                {
                        char key = str1.charAt(i);
                        if(ht.containsKey(key) == false)
                        {
                                ht.put(key, 1);
                        }
                        else
                        {
                                int cnt = (int)ht.get(key);
                                cnt++;
                                ht.put(key, cnt);

                        }
                }
                for(int i = 1 ; i < str2.length() ; i++) //Fault 2 , the variable i should start from 0
                {
                        char key = str2.charAt(i);
                        if(ht.containsKey(key) == false)
                        {
                                return false;
                        }
                        else
                        {
                                int cnt = (int)ht.get(key);
                                cnt--;
                                ht.put(key, cnt);
                        }
                }
                
                Enumeration<Character> keys = ht.keys();
                while(keys.hasMoreElements())
                {
                        Character key = keys.nextElement();
                        int val = (int)ht.get(key);
                        if(val != 0) 
                        {
                                return false;
                        }
                }
                return true;
        }

        void test()
        {
                System.out.println("Result:" + isStringPerm("bbbbaaaa", "bbbbaaa"));
                System.out.println("Result:" + isStringPerm("abba", "cabba"));
        }
        public static void main(String args[])
        {
                FaultExample pe = new FaultExample();
                pe.test();
        }         
}
