//************************************************************
//
//  Hand.Java             Authors:  Lewis, Chase, Coleman
//  
//  Provides an implementation of a hand of cards using a 
//  set to represent the cards
//
//************************************************************

import java.util.*;

public class Hand
{
        protected ArrayList<Card> inHand;
        protected int handvalue;  

        /**********************************************************
          Constructs a hand of Cards.
         **********************************************************/
        public Hand()
        {
                inHand = new ArrayList<Card>(12);
                handvalue = 0;
        }

        /**********************************************************
          Adds a new card to the hand.
          @param currentdeck the Deck the game is playing with
         **********************************************************/
        public Card newCard(Deck currentdeck)
        {
                Card result;
                result = currentdeck.getCard();
                inHand.add(result);  

                return result;
        }


        /**********************************************************
          Returns the value of this hand.
         **********************************************************/
        public int getHandValue()
        {
                handvalue = 0;
                for(int i = 0 ; i < inHand.size(); i++)
                {
                        Card c = inHand.get(i);
                        handvalue += c.getvalue();
                }
                handvalue = handvalue % 10;
                return handvalue;
        }

        /**********************************************************
          Returns an iterator over this hand.
         **********************************************************/
        public Iterator<Card> iterator()
        {
                return inHand.iterator();
        }

        /**********************************************************
          Removes a card from this hand.
         **********************************************************/
        public Card remove(int index)
        {
                if(index >= inHand.size())
                {
                        System.out.println("No such card:Card " + index  + "!!\n");
                        return null;
                }

                return inHand.remove(index);
        }

        /**********************************************************
          Returns a string representation of this hand. 
         **********************************************************/
        public String toString()
        {
                String result="";

                Card cardstr = null;
                int i=0;
                Iterator<Card> scan = inHand.iterator();
                while (scan.hasNext())
                {
                        cardstr= scan.next();
                        result += "card"+i+": "+cardstr.getvalue()+"\n";
                        i++;
                }

                return result;
        }

}//end Hand
