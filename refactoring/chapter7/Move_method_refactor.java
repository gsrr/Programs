package example.Move_method_refactor;


class AccountType
{
        private String type = "";
        public AccountType(String _type)
        {
                type = _type;
        }
        public boolean isPremium()
        {
                if(type.equals("VIP"))
                {
                        return true;
                }
                else
                {
                        return false;
                }
        }
        
        public double overdraftCharge(Account account) 
        {
                if (isPremium()) 
                {
                        double result = 10;
                        if (account.daysOverdrawn() > 7) 
                        {
                                result += (account.daysOverdrawn() - 7) * 0.85;
                        }
                        return result;
                }
                else 
                {
                        return account.daysOverdrawn() * 1.75;
                }
        }
}

class Account
{
        private AccountType _type;
        private int _daysOverdrawn;
        public Account(AccountType type, int daysOverdrawn)
        {
                _type = type;
                _daysOverdrawn = daysOverdrawn;        
        }
        public int daysOverdrawn()
        {
                return _daysOverdrawn;
        }
        double bankCharge() 
        {
                double result = 4.5;
                if (_daysOverdrawn > 0) 
                {
                       result += _type.overdraftCharge(this);
                }
                return result;
        }
}
public class Move_method_refactor
{
        public static void main(String args[])
        {
                Account test = new Account(new AccountType("VIP"), 5);
                System.out.println(test.bankCharge());
        }

}
