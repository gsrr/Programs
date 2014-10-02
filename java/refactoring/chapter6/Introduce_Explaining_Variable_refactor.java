package example.Introduce_Explaining_Variable;




class Introduce_Explaining_Variable_refactor
{
        private String _platform;
        private String _browser;
        boolean _init;
        private int _resize;

        public Introduce_Explaining_Variable_refactor(String platform, String browser, boolean init, int resize)
        {
                this._platform = platform;
                this._browser = browser;
                this._init = init;
                this._resize = resize;
        }
        public void do_action()
        {
                final boolean isMacOs = _platform.toUpperCase().indexOf("MAC") > -1;
                final boolean isIEBrowser = _browser.toUpperCase().indexOf("IE") > -1;
                final boolean wasResized = _resize > 0;
                if ( isMacOs && isIEBrowser && wasInitialized() &&  wasResized )
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
                Introduce_Explaining_Variable_refactor test = new Introduce_Explaining_Variable_refactor("MAC", "IE", true, 10);
                test.do_action();
        }
}
