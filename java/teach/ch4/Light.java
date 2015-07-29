public class Light implements LightInterface
{
        String color_;
        Light(String color)
        {
                color_ = color;
        }
        public String getColor()
        {
                return color_;
        }

}
