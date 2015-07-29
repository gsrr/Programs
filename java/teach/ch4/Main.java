public class Main
{
        public static void showColor(LightInterface li)
        {
                System.out.println(li.getColor());
        }
        public static void main(String args[])
        {
                Light red_light = new Light("Red");
                Light green_light = new Light("Green");
                Light yellow_light = new Light("Yellow");
                Light dark_light = new Light("Dark");
                showColor(red_light);
                showColor(green_light);
                showColor(yellow_light);
                showColor(dark_light);
        }
}
