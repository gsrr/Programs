
class Library
{
        private Number num;
        public Library(Number num)
        {
                this.num = num;
        }
        public int addition()
        {
                return this.num.x + this.num.y;
        }

        public int sub(int x, int y)
        {
                return x - y;
        }
}
