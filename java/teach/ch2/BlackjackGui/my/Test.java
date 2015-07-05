import java.util.Scanner;

public class Test
{


        public static void winner(Hand[] h)
        {
                System.out.println();       
                int max = h[0].getHandValue();
                System.out.println("The dealer's value is " + max);
                for(int i = 1 ; i < h.length ; i++)
                {
                        int tmp = h[i].getHandValue();
                        if(tmp > max)
                        {
                                System.out.println("Player:" + i + " value: " + tmp + ": Win");       
                        }       
                        else
                        {
                                System.out.println("Player:" + i + " value: " + tmp + ": Lost");       
                        }       
                }
                System.out.println();       
        }

        public static void main(String args[])
        {
                Scanner kb = new Scanner(System.in);
                Deck d = new Deck();
                System.out.print("\nPlease enter the number of players:");       
                int players = kb.nextInt();
                Hand[] h = new Hand[players];
                for(int i = 0 ; i < players ; i++)
                {
                        h[i] = new Hand();
                        h[i].newCard(d);
                        h[i].newCard(d);
                }
                winner(h);

        }
}
