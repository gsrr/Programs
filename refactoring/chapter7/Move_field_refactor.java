package example.Move_field_refactor;


class AccountType
{
        private String _type;
        private double _interestRate;

        public AccountType(String type)
        {
                this._type = type;
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

class Account
{
        private AccountType _type;
        
        public Account(AccountType type)
        {
               _type = type;
        }

        double interestForAmount_days(double amount, int days)
        {
                return getInterestRate() * amount * days / 365;
        }
        public void setInterestRate (double arg) 
        {
                _type.setInterestRate(arg);        
        }
        public double getInterestRate() 
        {
                return _type.getInterestRate();
        }
}


public class Move_field_refactor
{
        public static void main(String args[])
        {
                Account test = new Account(new AccountType("VIP"));
                test.setInterestRate(1.0);
                System.out.println("Interest rate:" + test.getInterestRate());
                System.out.println("Result:" + test.interestForAmount_days(100, 10));
        }

}
