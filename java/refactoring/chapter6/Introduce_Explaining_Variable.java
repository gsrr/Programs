package example.Introduce_Explaining_Variable;




class Introduce_Explaining_Variable
{
        private String _platform;
        private String _browser;
        boolean _init;
        private int _resize;

        public Introduce_Explaining_Variable(String platform, String browser, boolean init, int resize)
        {
                this._platform = platform;
                this._browser = browser;
                this._init = init;
                this._resize = resize;
        }
        public void do_action()
        {
                if ( (_platform.toUpperCase().indexOf("MAC") > -1) &&
                                (_browser.toUpperCase().indexOf("IE") > -1) &&
                                wasInitialized() && _resize > 0 )
                {
                        System.out.println("Start to do something\n");
                }

        }
        public boolean wasInitialized()
        {
                return _init;
        }
        public static void main(String args[])
        {
                Introduce_Explaining_Variable test = new Introduce_Explaining_Variable("MAC", "IE", true, 10);
                test.do_action();
        }
}
