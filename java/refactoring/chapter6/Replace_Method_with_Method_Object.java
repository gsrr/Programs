package example.replace_Method_with_Method_Object;


class Accout
{
	static int delta()
	{
		return 3;
	}
	int gamma (int inputVal, int quantity, int yearToDate) 
	{
		int importantValue1 = (inputVal * quantity) + delta();
		int importantValue2 = (inputVal * yearToDate) + 100;
		if ((yearToDate - importantValue1) > 100)
			importantValue2 -= 20;
		int importantValue3 = importantValue2 * 7;
		return importantValue3 - 2 * importantValue1;
	}
}

class replace_Method_with_Method_Object
{
	public static void main(String args)
	{
		Account test = new Account()
		System.out.println(test.gamma(10, 10, 2));
	}
}


