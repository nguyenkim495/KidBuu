package  {
	
	import flash.display.SimpleButton;
	import flash.text.TextField;
	import flash.text.*;
	
	
	public class ButtonSimpleBase extends SimpleButton {
		public var label_text:TextField;
		
		public function ButtonSimpleBase() {
			// constructor code
			trace("create me");
			label_text.text = "Me";
		}
	}
	
}
