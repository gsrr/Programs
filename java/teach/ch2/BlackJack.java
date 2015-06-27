import javax.swing.*;
import java.io.*;
import java.util.Random;

//Example 2 Using a Class

public class BlackJack
{
       //Globals
       public static final int NUMCARDS = 13;
       public static final int NUMFACES = 4;
       public static final int NUMCARDSINDECK = 52;
       public static final int MaxHandSize = 20;
       public static final int NumCardsToStartWith = 2;
       public static final int HouseLimit = 17;

       //The Card Values
       public static final int DEUCE = 2;
       public static final int THREE = 3;
       public static final int FOUR = 4;
       public static final int FIVE = 5;
       public static final int SIX = 6;
       public static final int SEVEN = 7;
       public static final int EIGHT = 8;
       public static final int NINE = 9;
       public static final int TEN = 10;
       public static final int JACK = 11;
       public static final int QUEEN = 12;
       public static final int KING = 13;
       public static final int ACE = 14;
       
       //The Faces
       public static final int SPADES = 0;
       public static final int HEARTS = 1;
       public static final int DIAMONDS = 2;
       public static final int CLUBS = 3;
       
       //Dealer and Player
       public static final int PLAYER = 1;
       public static final int DEALER = 2;

       public static int DealerTotal = 0;
       public static int PlayerTotal = 0;
       public static boolean DealerStay = false;
       public static boolean PlayerStay = false;

       //Count the Number of Deals for Indexing the Cards
       //Used to advance array forward to hold new cards in hand
       public static int PlayerDeal = 0;
       public static int DealerDeal = 0;
       
       public static CARD[] DeckOfCards = new CARD[NUMCARDSINDECK];
       public static CARD[] DealerHand = new CARD[MaxHandSize];
       public static CARD[] PlayerHand = new CARD[MaxHandSize];

       public static String PlayerName = "";
       public static boolean DisplayAllDealerCards = false;
       public static boolean CHEAT = false;
       
       public static int DealerWins = 0;
       public static int PlayerWins = 0;

//--------------------------------------------------------------------------------------

public static class CARD
{
       //Constructor
       public CARD()
       {
              TheCard = BlackJack.DEUCE;
              TheFace = BlackJack.HEARTS;
              Drawn = false;
       }

       //Overloaded Constructor
       public CARD(int card, int face)
       {
              TheCard = card;
              TheFace = face;
              Drawn = false;
              
              switch(TheCard)
              {
                  case BlackJack.DEUCE : PointValue = 2; break;
                  case BlackJack.THREE : PointValue = 3; break;
                  case BlackJack.FOUR : PointValue = 4; break;
                  case BlackJack.FIVE : PointValue = 5; break;
                  case BlackJack.SIX : PointValue = 6; break;
                  case BlackJack.SEVEN : PointValue = 7; break;
                  case BlackJack.EIGHT : PointValue = 8; break;
                  case BlackJack.NINE : PointValue = 9; break;
                  case BlackJack.TEN : PointValue = 10; break;
                  case BlackJack.JACK : PointValue = 10; break;
                  case BlackJack.QUEEN : PointValue = 10; break;
                  case BlackJack.KING : PointValue = 10; break;
                  case BlackJack.ACE : PointValue = 11; break;
                  default : break;
              }
       }

       public void DisplayCard()
       {        
              String OUT = "\n     A ";

              switch(TheCard)
              {
                  case BlackJack.DEUCE : OUT = OUT + "DEUCE"; break;
                  case BlackJack.THREE : OUT = OUT + "THREE"; break;
                  case BlackJack.FOUR : OUT = OUT + "FOUR"; break;
                  case BlackJack.FIVE : OUT = OUT + "FIVE"; break;
                  case BlackJack.SIX : OUT = OUT + "SIX"; break;
                  case BlackJack.SEVEN : OUT = OUT + "SEVEN"; break;
                  case BlackJack.EIGHT : OUT = OUT + "EIGHT"; break;
                  case BlackJack.NINE : OUT = OUT + "NINE"; break;
                  case BlackJack.TEN : OUT = OUT + "TEN"; break;
                  case BlackJack.JACK : OUT = OUT + "JACK"; break;
                  case BlackJack.QUEEN : OUT = OUT + "QUEEN"; break;
                  case BlackJack.KING : OUT = OUT + "KING"; break;
                  case BlackJack.ACE : OUT = OUT + "ACE"; break;
                  default : break;
              }

              OUT = OUT + " of ";

              switch(TheFace)
              {
                 case BlackJack.SPADES : OUT = OUT + "SPADES"; break;
                 case BlackJack.HEARTS : OUT = OUT + "HEARTS"; break;
                 case BlackJack.DIAMONDS : OUT = OUT + "DIAMONDS"; break;
                 case BlackJack.CLUBS : OUT = OUT + "CLUBS"; break;
                 default : break;
              }

              OUT = OUT + ". Points = " + PointValue + ".";

              System.out.print(OUT);
       }

       //Public Accessors
       public int GetFace() { return TheFace; }
       public int GetCard() { return TheCard; }
       public int GetPointValue() { return PointValue; }
       public boolean GetDrawn() { return Drawn; }

       public void SetFace(int x) { TheFace = x; }
       public void SetCard(int x) { TheCard = x; }
       public void SetPointValue(int x) { PointValue = x; }
       public void SetDrawn(boolean x) { Drawn = x; }

       //Private Data Members
       private int TheFace;
       private int TheCard;
       private int PointValue = 0;
       private boolean Drawn = false;

}//close CARD class

//--------------------------------------------------------------------------------------

       public static void Game()
       {
              //Initialize Values for a Round
              DealerTotal = 0;
              PlayerTotal = 0;
              PlayerDeal = 0;
              DealerDeal = 0;
              DealerStay = false;
              PlayerStay = false;
              DisplayAllDealerCards = false;

              //Start populating deck with DEUCES
              int CardType = DEUCE;

              //Populate the Deck Array With Card Values
              CLEAR(10);
              System.out.print("\n     -------------- Creating a 52 CARD Deck Now --------------\n");

              try { Thread.sleep(1500); }
              catch(Exception e) {  }

              for(int CardInDeck = 0; CardInDeck < NUMCARDSINDECK; )
              {
                  //For each card value give it 4 faces
                  for(int CardFace = 0; CardFace < NUMFACES; CardFace++)
                  {
                       DeckOfCards[CardInDeck] = new CARD(CardType,CardFace);
                       DeckOfCards[CardInDeck].DisplayCard();
                       CardInDeck++;
                  }
                  CardType++;
              }

              try { Thread.sleep(600); }
              catch(Exception e) {  }

              System.out.print("\n\n     ---------------------- DONE ---------------------------\n");

              System.out.println("\n     The Dealer shuffles the DECK and deals out the CARDs...\n");

              //Dealer and Player Start Hand By Drawing 2 Cards Each
              for(int x = 0; x < NumCardsToStartWith; x++)
              {
                  DRAW(PLAYER);
                  DRAW(DEALER);
              }

              DisplayHand(PLAYER);
              DisplayHand(DEALER);

              Deal();

              //Stop hiding Dealer's CARDs and POINTs
              DisplayAllDealerCards = true;
              
              System.out.print("\n     Closing HANDs:\n");
              DisplayHand(PLAYER);
              DisplayHand(DEALER);

              //If someone WINS or BUSTS
              if(PlayerTotal == 21)
              { 
                 System.out.print("     " + PlayerName + " nails it and wins! A perfect 21!");
                 PlayerWins++;
              }

              else if(DealerTotal == 21)
              { 
                 System.out.print("     Dealer nails it and wins! A perfect 21!");  
                 DealerWins++;
              }

              else if(PlayerTotal > 21)
              {
                    System.out.print("\n     " 
                    + PlayerName + ", you BUSTED! Sorry, you lost this round.");
                    DealerWins++;
              }

              else if(DealerTotal > 21)
              {
                    System.out.print("\n     Dealer BUSTED. Woo-hoo! " 
                    + PlayerName + " wins this round.");
                    PlayerWins++;
              }

              //Player STAYs, see whose hand is better
              if(PlayerStay)
              {
                  if(PlayerTotal == DealerTotal)
                  { 
                    System.out.print("\n     Unbelieveable! " 
                    + PlayerName + "  and the Dealer tie!");
                    PlayerWins++;
                    DealerWins++;
                  }
                  else if(PlayerTotal > DealerTotal)
                  { 
                    System.out.print("\n     " + PlayerName + "  wins this round!"); 
                    PlayerWins++;
                  }
                  else if(DealerTotal > PlayerTotal)
                  { 
                    System.out.print("\n     The Dealer wins this round!");
                    DealerWins++;
                  }
              }

              System.out.print("\n\n     This round of BlackJack is now complete!\n");

              for(int x = 0; x < MaxHandSize; x++)
              {
                  DealerHand[x] = null;
                  PlayerHand[x] = null;
              }
       }

//----------------------------------------------------------------------

       public static void DRAW(int Hand)
       {
              Random PEACH = new Random();

              //Offset for fencepost
              int ACard = (PEACH.nextInt(NUMCARDSINDECK) + 1) - 1;

              //Find a Card the was not already Drawn
              while(DeckOfCards[ACard].GetDrawn())
              { ACard = (PEACH.nextInt(NUMCARDSINDECK) + 1) - 1; }

              //Mark Card as Drawn so it's no longer available
              DeckOfCards[ACard].SetDrawn(true);

              if(Hand == PLAYER)
              {
                  PlayerHand[PlayerDeal] = DeckOfCards[ACard];
                  PlayerTotal = PlayerTotal + PlayerHand[PlayerDeal].GetPointValue();
                  PlayerDeal++;
              }

              else
              {
                  DealerHand[DealerDeal] = DeckOfCards[ACard];
                  DealerTotal = DealerTotal + DealerHand[DealerDeal].GetPointValue();
                  DealerDeal++;
              }
       }

//--------------------------------------------------------------------------------------

       public static void DisplayHand(int Hand)
       {
              if(Hand == PLAYER)
              {
                  System.out.print("\n     " + PlayerName + "'s  Hand:");

                  for(int x = 0; x < MaxHandSize; x++)
                  {
                      if(PlayerHand[x]!= null)
                      {
                          PlayerHand[x].DisplayCard();
                      }
                      else { break; }
                  }

                  System.out.print("\n     Total " 
                  + PlayerName + " points = " + PlayerTotal + ".\n\n");
              }

              else
              {
                  System.out.print("\n     Dealer's Hand:");

                  if(DisplayAllDealerCards || CHEAT)
                  {
                      //Display all the Dealer's CARDs
                      for(int x = 0; x < MaxHandSize; x++)
                      {
                          if(DealerHand[x]!= null)
                          {
                             DealerHand[x].DisplayCard();
                          }
                          else
                          { break; }
                      }

                      System.out.print("\n     Total Dealer points = " + DealerTotal + ".\n\n");

                  }

                  else
                  {
                      //Hide 1st CARD (Element 0)
                      System.out.print("\n     A Hidden CARD! What could it be?");

                      for(int x = 1; x < MaxHandSize; x++)
                      {
                          if(DealerHand[x]!= null)
                          {
                             DealerHand[x].DisplayCard();
                          }
                          else
                          { break; }
                      }

                      System.out.print("\n     Total Dealer points = ??? (HIDDEN).\n\n");
                  }

              }
       }

//--------------------------------------------------------------------------------------

       public static String INPUT()
       {
              LineNumberReader BANANA = new LineNumberReader(new InputStreamReader(System.in));
              String input = "";
              try { input = BANANA.readLine(); }
              catch(IOException APPLE) { System.err.println("Error taking input..."); }
              return input;
       }

//--------------------------------------------------------------------------------------

       public static void Deal()
       {
              String choice = "#";

              //Player Goes First, play until Player or Dealer reaches 21,
              //Busts or both Player and Dealer decide to STAY
              while(choice.charAt(0) != 'q' &&
                    DealerTotal < 21 &&
                    PlayerTotal < 21 &&
                    PlayerStay == false
                    )
              {
                  System.out.print("\n     The Dealer asks:\n\n" +
                  "     " + PlayerName + ", do you want a HIT or will you STAY?\"\n\n");

                  System.out.print("     _______________ Options _____________ \n");
                  System.out.print("     |                                    |\n");
                  System.out.print("     |  (H)it       (S)tay      (Q)uit    |\n");
                  System.out.print("     |____________________________________|\n\n     ");

                  choice = INPUT().toLowerCase();

                  switch(choice.charAt(0))
                  {
                      case 'h' : System.out.print("\n     " + PlayerName + " requests a HIT.\n");
                                 Hit(PLAYER);
                                 break;
                      case 's' : System.out.print("\n     " + PlayerName + " decides to STAY.\n");
                                 PlayerStay = true;
                                 DisplayHand(PLAYER);
                                 break;
                      case 'q' : break;
                      default : System.out.print("\n     Invalid input!\n");
                                choice = "INVALID_INPUT";
                                break;
                  }
                  char X;
                  //If invalid input skip Dealer events and go back to player
                  if(!choice.equals("INVALID_INPUT"))
                  {
                       //Dealer Only Draws if Player Not Busted
                       if(PlayerTotal < 21)
                       {
                            if(DealerTotal < HouseLimit)
                            {
                                System.out.print("\n     The Dealer decides to take a card.\n");
                                Hit(DEALER);
                            }
                            else
                            {
                                System.out.print("\n     The Dealer decides to STAY.\n");
                                DealerStay = true;
                                DisplayHand(DEALER);
                            }

                       }//close if for Player Not Busted

                  }//close if for invalid choice

              }//close while true loop

       }//close function

//--------------------------------------------------------------------------------------

       public static void Hit(int WHOEVER)
       {
              DRAW(WHOEVER);

              if(WHOEVER == PLAYER)
              {
                 if(PlayerTotal > 21)
                 {
                    for(int x = 0; x < MaxHandSize; x++)
                    {
                       if(PlayerHand[x]!= null)
                       {
                           if(PlayerHand[x].GetCard() == ACE)
                           {
                                System.out.print("\n     " 
                                + PlayerName + 
                                ", your HAND is over 21 but an ACE was found.\n"
                                + "     We'll convert the ACE from 11 points to 1 point!\n");
                                PlayerHand[x].SetPointValue(1);
                                break; //Set points of only 1 ACE to 1
                           }

                       }
                       else
                       { break; }
                    }//close for loop

                    //Recount Point values of cards after converting ACE
                    //Alternatively, you could just subtract 10 from PlayerTotal
                    //ans set its point value to 1 without looping theough the arrays above/below
                    PlayerTotal = 0;

                    for(int x = 0; x < MaxHandSize; x++)
                    {
                         if(PlayerHand[x]!= null)
                         {
                             PlayerTotal = PlayerTotal + PlayerHand[x].GetPointValue();
                         }
                         else { break; }
                    }

                 }//close if PlayerTotal

              }//close if WHOEVER == PLAYER
              
              //Then must be Dealer
              else
              {
                 if(DealerTotal > 21)
                 {
                    for(int x = 0; x < MaxHandSize; x++)
                    {
                       if(DealerHand[x]!= null)
                       {
                           if(DealerHand[x].GetCard() == ACE)
                           {
                                System.out.print(
                                "\n     Dealer's HAND is over 21 but an ACE was found.\n"
                                + "     We'll convert the ACE from 11 points to 1 point!\n");
                                DealerHand[x].SetPointValue(1);
                                break; //Set points of only 1 ACE to 1
                           }

                       }
                       else
                       { break; }
                    }//close for loop

                    //Recount Point values of cards after converting ACE
                    //Alternatively, you could just subtract 10 from PlayerTotal
                    //ans set its point value to 1 without looping theough the arrays above/below
                    DealerTotal = 0;

                    for(int x = 0; x < MaxHandSize; x++)
                    {
                         if(DealerHand[x]!= null)
                         {
                             DealerTotal = DealerTotal + DealerHand[x].GetPointValue();
                         }
                         else { break; }
                    }
                 }

              }

              DisplayHand(WHOEVER);

      }//close Hit function

//--------------------------------------------------------------------------------------

       public static void main(String args[])
       {
              System.out.print("\n          Welcome to BlackJack 1.0!\n\n");

              System.out.print("          What's your name, player? ");
              PlayerName = INPUT();

              System.out.print(
              "\n\n\n\n               O.k. " + PlayerName + ", here's what you can do:\n\n");
              //Hint: Make a menu here, let computer draw, let player draw
              String choice = "#";
              while(choice.charAt(0) != 'q')
              {
                    System.out.print("\n                    ________ Main Menu _______\n");
                    System.out.print("                    |                        |\n");
                    System.out.print("                    |    (P)lay BlackJack    |\n");
                    System.out.print("                    |    (I)nstructions      |\n");
                    if(!DisplayAllDealerCards)
                    { System.out.print("                    |    (A)ctivate Cheat    |\n"); }
                    else
                    { System.out.print("                    |    (D)ectivate Cheat   |\n"); }
                    System.out.print("                    |    (Q)uit              |\n");
                    System.out.print("                    |________________________|\n\n\n");

                    System.out.print("                             Scores           \n\n");
                    System.out.print("                       Dealer Wins = " + DealerWins + "\n");
                    System.out.print("                       Player Wins = " + PlayerWins + "\n");
                    CLEAR(10);

                    choice = INPUT();

                    switch(choice.charAt(0))
                    {
                          case 'p' : Game(); break;
                          case 'i' : Instructions(); break;
                          case 'a' : CHEAT = true; break;
                          case 'd' : CHEAT = false; break;
                          case 'q' : break;
                          default : System.out.println("     Sorry, that was an invalid choice.\n");
                                    break;
                    }
              }

       }

//--------------------------------------------------------------------------------------

       public static void Instructions()
       {
              System.out.print(
              "\n\n          " 
              + PlayerName + ", this is a short, fast card game of luck and skill.\n");
              System.out.print(
              "          The dealer will start you with two cards from the deck.\n");
              System.out.print(
              "          Your goal is to draw cards to get as close to the number\n");
              System.out.print(
              "          21 as possible. If you go over 21, you are BUSTED. If you\n");
              System.out.print(
              "          get closer to 21 than the dealer but not over, you win.\n");
              System.out.print("          The card values are:\n");
              System.out.print("\n             DEUCES = 2          EIGHT = 8");
              System.out.print("\n             THREE =  3          NINE =  9");
              System.out.print("\n             FOUR =   4          TEN =   10 ");
              System.out.print("\n             FIVE =   5          JACK =  10");
              System.out.print("\n             SIX =    6          QUEEN = 10");
              System.out.print("\n             SEVEN =  7          KING =  10");
              System.out.print("\n                                 ACE =   11 or 1\n");
              System.out.print(
              "\n          ACEs are 1 or 11 depending on which value is advantageous.");
              
              System.out.print(
              "\n\n          Activating the CHEAT allows you to see all the dealer's cards,");
              System.out.print(
              "\n          giving you an unfair advantage. Normally, one of the Dealer's");
              System.out.print(
              "\n          cards is hidden, making the game more challenging.");

              PAUSE();
       }

//--------------------------------------------------------------------------------------

       public static void PAUSE()
       {
          //Since Java doesn't have a PAUSE command lie C++, make your own
          String CONTINUE = "";
          LineNumberReader cin = new LineNumberReader(new InputStreamReader(System.in));
          while(CONTINUE == "")
          {
                System.out.print("\n\n\n          Paused. Press ENTER to continue.\n     ");
                try { CONTINUE = cin.readLine(); }
                catch (IOException e) { System.err.println("Error."); }
          }
          System.out.print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
      }

//--------------------------------------------------------------------------------------

      public static void CLEAR(int x)
      {
             for(int z = 0; z < x; z++)
             {
                System.out.println();
             }
             System.out.print("                    ");
      }
//--------------------------------------------------------------------------------------

}//close class SPEC