package example.Move_method;


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
        double overdraftCharge() 
        {
                if (_type.isPremium()) 
                {
                        double result = 10;
                        if (_daysOverdrawn > 7) 
                        {
                                result += (_daysOverdrawn - 7) * 0.85;
                        }
                        return result;
                }
                else 
                {
                        return _daysOverdrawn * 1.75;
                }
        }
        double bankCharge() 
        {
                double result = 4.5;
                if (_daysOverdrawn > 0) 
                {
                       result += overdraftCharge();
                }
                return result;
        }
}
public class Move_method
{
        public static void main(String args[])
        {
                Account test = new Account(new AccountType("VIP"), 5);
                System.out.println(test.bankCharge());
        }

}
