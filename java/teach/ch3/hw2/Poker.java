import java.util.Scanner;

public class Poker
{


        public static void compare(Player[] p)
        {
                int lcnt = 0 , wcnt = 0;
                System.out.println();       
                int dealer_value = p[0].cal_hand_value();
                System.out.println("The dealer's value is " + dealer_value);
                for(int pi = 1 ; pi < p.length ; pi++)
                {
                        int player_value = p[pi].cal_hand_value();
                        if(player_value > dealer_value)
                        {
                                System.out.println("Player:" + pi + " value: " + player_value + ": Win");   
                                wcnt++;
                        }       
                        else
                        {
                                System.out.println("Player:" + pi + " value: " + player_value + ": Lost");   
                                lcnt++;
                        }       
                }
                System.out.println("Summary Win:" + wcnt + " Lost:" + lcnt);       
        }

        public static void main(String args[])
        {
                Scanner kb = new Scanner(System.in);
                Deck d = new Deck();
                System.out.print("\nPlease enter the number of players:");       
                int players = kb.nextInt();
                Player[] p = new Player[players];
                for(int pi = 0 ; pi < players ; pi++)
                {
                        p[pi] = new Player();
                        p[pi].receive_card(d);
                        p[pi].receive_card(d);
                }
                compare(p);
        }
}
