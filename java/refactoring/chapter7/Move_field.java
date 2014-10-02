package example.Move_field;


class AccountType
{
        String _type;
        public AccountType(String type)
        {
                this._type = type;
        }
}

class Account
{
        private AccountType _type;
        private double _interestRate;
        
        public Account(AccountType type)
        {
               this._type = type;
        }

        double interestForAmount_days(double amount, int days)
        {
                return this.getInterestRate() * amount * days / 365;
        }
        public void setInterestRate (double arg) 
        {
                this._interestRate = arg;
        }
        public double getInterestRate() 
        {
                return this._interestRate;
        }
}
public class Move_field
{
        public static void main(String args[])
        {
                Account test = new Account(new AccountType("VIP"));
                test.setInterestRate(1.0);
                System.out.println("Interest rate:" + test.getInterestRate());
                System.out.println("Result:" + test.interestForAmount_days(100, 10));
        }

}
