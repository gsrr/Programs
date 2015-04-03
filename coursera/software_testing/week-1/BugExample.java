import java.io.*;
import java.util.*;

public class BugExample
{
        boolean isStringPerm_bug(String str1, String str2)
        {
                if(str1.length() != str2.length())
                {
                        return false;
                }
                if(str1.length() == 0)
                {
                        System.out.println("Warning:First string is empty");
                }
                if(str2.length() == 0)
                {
                        System.out.println("Warning:Second string is empty");
                }

                int[] buf = new int[128];
                char[] cArray1 = str1.toCharArray();
                char[] cArray2 = str2.toCharArray();
                for(int i = 0 ; i < cArray1.length ; i++)
                {
                        int val = (int)cArray1[i];
                        buf[val] += 1;
                }
                for(int i = 0 ; i < cArray2.length ; i++)
                {
                        int val = (int)cArray2[i];
                        buf[val] -= 1;
                        if(buf[val] == -1)
                        {
                                return false;
                        }
                }
                return true;
        }
        boolean isStringPerm_fixed(String str1, String str2)
        {
                if(str1.length() != str2.length())
                {
                        return false;
                }
                Hashtable ht = new Hashtable();
                for(int i = 0 ; i < str1.length() ; i++)
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
                for(int i = 0 ; i < str2.length() ; i++)
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
                                if(cnt == -1)
                                {
                                        return false;
                                }
                                ht.put(key, cnt);
                        }
                }
                return true;
        }

        void test()
        {
                System.out.println("Is str2 is permutation of str1:" + isStringPerm_bug("abbb", "bbba"));
                System.out.println("Is str2 is permutation of str1:" + isStringPerm_bug("abbb", "cbba"));
                System.out.println("Is str2 is permutation of str1:" + isStringPerm_bug("!@#$%^", "^%$#!@"));
                System.out.println("Is str2 is permutation of str1:" + isStringPerm_bug("", "^%$#!@"));
                System.out.println("Is str2 is permutation of str1:" + isStringPerm_bug("", ""));
                System.out.println("Is str2 is permutation of str1:" + isStringPerm_bug("a   bb", "bb   a"));
                //System.out.println("Is str2 is permutation of str1:" + isStringPerm_bug("者管理", "管理者"));
                System.out.println("Is str2 is permutation of str1:" + isStringPerm_fixed("者管理", "管理者"));
                System.out.println("Is str2 is permutation of str1:" + isStringPerm_fixed("者者管理", "管理者"));
        }
        public static void main(String args[])
        {
                BugExample be = new BugExample();
                be.test();
        }         
}
