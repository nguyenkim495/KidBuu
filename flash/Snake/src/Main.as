package  {
	
	import flash.display.MovieClip;
	import flash.display.Sprite;
	import flash.events.Event;
	
	public class Main extends Sprite{

		public var head:Snake;
		public var snake:Array;
		public var food:Food;
		public var _points:points;
		
		///
		//public var init = function();
		///
		
		public function Main() {
			// constructor code
			
			if(!stage)
				_iniṭ();
			
			
			head = new Snake();
			_points = new points;
			food = new Food();
			
			//this.addChild();
			
			//addChild(food);
			
			_points.ScoreValue = 192138;
			
			
			this.addEventListener(Event.ENTER_FRAME, thisOnEnterFrame);
		}
		
		public function _init():void
		{
			trace("call init");
		}
		
		public function thisOnEnterFrame($event:Event):void
		{
			//trace("this");
			
		}

	}
	
}
