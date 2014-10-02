
package example.Extract_class;


class Person
{
        private String _name;
        private String _officeAreaCode;
        private String _officeNumber;

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
                return ("(" + _officeAreaCode + ") " + _officeNumber);
        }

        String getOfficeAreaCode()
        {
                return _officeAreaCode;
        }

        void setOfficeAreaCode(String arg)
        {
                _officeAreaCode = arg;
        }

        String getOfficeNumber()
        {
                return _officeNumber;
        }

        void setOfficeNumber(String arg) 
        {
                _officeNumber = arg;
        }
}


public class Extract_class
{
        public static void main(String args[])
        {
                Person test = new Person("Jerry Cheng");
                test.setOfficeAreaCode("02");
                test.setOfficeNumber("3783783");
                System.out.println(test.getTelephoneNumber());
        }

}
