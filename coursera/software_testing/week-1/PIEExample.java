import java.io.*;
import java.util.*;

public class PIEExample
{
        boolean isStringPerm(String str1, String str2)
        {
                Hashtable ht = new Hashtable();
                for(int i = 1 ; i < str1.length() ; i++)
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
                for(int i = 1 ; i < str2.length() ; i++)
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
                System.out.println("No Error: Is str2 is permutation of str1:" + isStringPerm("abbb", "abbb"));
                System.out.println("Error but no failure: Is str2 is permutation of str1:" + isStringPerm("abbbc", "abbccc"));
                System.out.println("Failure: Is str2 is permutation of str1:" + isStringPerm("abbb", "cbbb"));
        }
        public static void main(String args[])
        {
                PIEExample pe = new PIEExample();
                pe.test();
        }         
}
