// BlackJackApp.java

// Import all the Java API classes needed by this program.
import java.lang.System;
import java.lang.Integer;
import java.lang.NumberFormatException;
import java.io.DataInputStream;
import java.io.IOException;
import java.util.Random;

class BlackJackApp {
        public static void main (String args[]) throws IOException {
                // Create a BlackJackGame object ...
                BlackJackGame game = new BlackJackGame();
                // and play it!
                game.play();
        }
}

class BlackJackGame {
        // Variable declarations
        int bet;
        int money;
        Deck deck;
        Hand playersHand;
        Hand dealersHand;
        DataInputStream keyboardInput;

        // Method declarations 
        public BlackJackGame() { // Constructor
                bet = 0;
                money = 1000;
                deck = new Deck();
                keyboardInput = new DataInputStream(System.in);
        }

        void play() throws IOException {
                System.out.println("Welcome to Blackjack!"); 
                System.out.println("You have $"+Integer.toString(money)+"."); 
                do {
                        placeBet();
                        if(bet>0) {
                                initialDeal();
                                if(playersHand.blackjack()) playerWins(); 
                                else{
                                        while(playersHand.under(22) && playerTakesAHit()) {
                                                playersHand.addCard(deck.deal()); 
                                                playersHand.show(false,false); 
                                        }
                                        while(dealersHand.mustHit())
                                                dealersHand.addCard(deck.deal()); 
                                        dealersHand.show(true,false);
                                        showResults();
                                }
                        }
                } while (bet>0);
        }

        void placeBet() throws IOException, NumberFormatException {
                do{
                        System.out.print("Enter bet: ");
                        System.out.flush();
                        bet = Integer.parseInt(keyboardInput.readLine()); 
                } while(bet<0 || bet>money);
        }

        void initialDeal() {
                System.out.println("New hand...");
                playersHand = new Hand();
                dealersHand = new Hand();
                for(int i = 0;i<2;++i) {
                        playersHand.addCard(deck.deal());
                        dealersHand.addCard(deck.deal());
                }
                dealersHand.show(true,true);
                playersHand.show(false,false);
        }

        void playerWins() {
                money += bet;
                System.out.println("Player wins $"+Integer.toString(bet)+"."); 
                System.out.println("Player has $"+Integer.toString(money)+"."); 
        }

        void dealerWins() {
                money -= bet;
                System.out.println("Player loses $"+Integer.toString(bet)+"."); 
                System.out.println("Player has $"+Integer.toString(money)+"."); 
        }

        void tie() {
                System.out.println("Tie.");
                System.out.println("Player has $"+Integer.toString(money)+"."); 
        }

        boolean playerTakesAHit() throws IOException {
                char ch = ' ';
                do{
                        System.out.print("Hit or Stay: "); 
                        System.out.flush();
                        String playersDecision = keyboardInput.readLine(); 
                        try 
                        {
                                ch = playersDecision.charAt(0);
                        }
                        catch (StringIndexOutOfBoundsException exception) 
                        {
                                ;
                        }
                        if(ch == 'H' || ch == 'h') return true;
                        if(ch == 'S' || ch == 's') return false;
                } while(true);
        }

        void showResults() {
                if(playersHand.busted() && dealersHand.busted()) tie();
                else if(playersHand.busted()) dealerWins();
                else if(dealersHand.busted()) playerWins();
                else if(playersHand.bestScore() > dealersHand.bestScore()) playerWins();
                else if(playersHand.bestScore() < dealersHand.bestScore()) dealerWins();
                else tie();
        }
} // End of BlackJackGame class

class Deck {
        // Variable declarations
        int cards[]; // Array of 52 cards
        int topCard; // 0-51 (index of card in deck)
        Random random;

        // Method declarations
        public Deck() { // Constructor
                cards = new int[52];
                for(int i = 0;i<52;++i) cards[i] = i;
                topCard = 0;
                random = new Random();
                shuffle();
        }

        public void shuffle() {
                // Repeat 52 times
                for(int i = 0;i<52;++i) {
                        // Randomly exchange two cards in the deck. 
                        int j = randomCard();
                        int k = randomCard();
                        int temp = cards[j];
                        cards[j] = cards[k];
                        cards[k] = temp;
                }
        }

        int randomCard() {
                int r = random.nextInt();
                if(r<0) r = 0-r;
                return r%52;
        }

        Card deal() {
                if(topCard>51) {
                        shuffle();
                        topCard = 0;
                }
                Card card = new Card(cards[topCard]);
                ++topCard;
                return card;
        }
} // End of Deck class

class Hand {
        // Variable declarations
        int numCards;
        Card cards[];
        static int MaxCards = 12;

        //Method declarations
        public Hand() { // Constructor
                numCards = 0;
                cards = new Card[MaxCards];
        }

        void addCard(Card c) {
                cards[numCards] = c;
                ++numCards;
        }

        void show(boolean isDealer,boolean hideFirstCard) {
                if(isDealer) System.out.println("Dealer:"); 
                else System.out.println("Player:");
                for(int i = 0;i<numCards;++i) {
                        if(i == 0 && hideFirstCard) System.out.println(" Hidden");
                        else System.out.println(" "+cards[i].value+" of "+cards[i].suit);
                }
        }

        boolean blackjack() {
                if(numCards == 2) {
                        if(cards[0].iValue == 1 && cards[1].iValue == 10) return true;
                        if(cards[1].iValue == 1 && cards[0].iValue == 10) return true;
                }
                return false;
        }

        boolean under(int n) {
                int points = 0;
                for(int i = 0;i<numCards;++i) points += cards[i].iValue; 
                if(points<n) return true;
                else return false;
        }

        int bestScore() {
                int points = 0;
                boolean haveAce = false;
                for(int i = 0;i<numCards;++i) {
                        points += cards[i].iValue;
                        if(cards[i].iValue == 1) haveAce = true;
                }
                if(haveAce) {
                        if(points+10 < 22) points += 10;
                }
                return points;
        }

        boolean mustHit() {
                if(bestScore()<17) return true;
                else return false;
        }

        boolean busted() {
                if(!under(22)) return true;
                else return false;
        }
} // End of Hand class 

class Card {
        // Variable declarations
        int iValue; // Numeric value corresponding to card.
        String value; // "A" "2" through "9" "T" "J" "Q" "K"
        String suit; // "S" "H" "C" "D"

        // Method declarations
        public Card(int n) { // Constructor
                int iSuit = n/13;
                iValue = n%13+1;
                switch(iSuit) {
                        case 0:
                                suit = "Spades";
                                break;
                        case 1:
                                suit = "Hearts";
                                break;
                        case 2:
                                suit = "Clubs";
                                break;
                        default:
                                suit = "Diamonds";
                }
                if(iValue == 1) value = "Ace";
                else if(iValue == 10) value = "Ten";
                else if(iValue == 11) value = "Jack";
                else if(iValue == 12) value = "Queen";
                else if(iValue == 13) value = "King";
                else value = Integer.toString(iValue);
                if(iValue>10) iValue = 10;
        }

        int getValue() {
                return iValue;
        }
} // End of Card class
