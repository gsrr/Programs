
package example.Extract_class_refactor;


class TelephoneNumber 
{
        private String _areaCode;
        private String _number;
        
        public TelephoneNumber(String areaCode, String number)
        {
                _areaCode = areaCode;
                _number = number;
        }        
        String getAreaCode() 
        {
                return _areaCode;
        }

        String getNumber() 
        {
                return _number;
        }
}
class Person
{
        private String _name;
        private TelephoneNumber _telNumber;

        public Person(String name)
        {
                _name = name;
        }

        public String getName()
        {
                return _name;
        }

        public String getTelephoneNumber()
        {
                return ("(" + _telNumber.getAreaCode() + ") " + _telNumber.getNumber());
        }

        public void setTelephone(TelephoneNumber telNumber)
        {
                _telNumber = telNumber;
        }

}


public class Extract_class_refactor
{
        public static void main(String args[])
        {
                TelephoneNumber tel = new TelephoneNumber("02", "3783783");
                Person test = new Person("Jerry Cheng");
                test.setTelephone(tel);
                System.out.println(test.getTelephoneNumber());
        }

}
