public class Main
{
        public static void showColor(LightInterface li)
        {
                System.out.println(li.getColor());
        }
        public static void main(String args[])
        {
                Light red_light = new Light("Red", 10);
                Light green_light = new Light("Green", 20);
                Light yellow_light = new Light("Yellow", 3);
                Light dark_light = new Light("Dark", 0);
                showColor(red_light);
                showColor(green_light);
                showColor(yellow_light);
                showColor(dark_light);
                Light[] ls = new Light[3];
                ls[0] = red_light;
                ls[1] = yellow_light;
                ls[2] = green_light;
                LightHolder lh = new LightHolder(ls, dark_light);
                lh.display();
        }
}
