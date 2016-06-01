package  {
	
	import flash.display.MovieClip;
	import flash.text.*;
	//import flash.geom.Point;
	
	
	public class points extends MovieClip {
		
		//public var textLabel:TextField;
		public var scoreValue:int = 10;
		//public var Points:TextField;
		
		public function points() {
			// constructor code
			//Points = new TextField();
			addChild(Points);
			Points.text = String(scoreValue);
			
			//trace(Points.text);
			
			ScoreValue(10);
		}
		
		public function set ScoreValue($score:int):void
		{
			scoreValue = $score;
			Points.text = String(scoreValue);
			
			trace("call me: Points.length: " + Points.length + " " + Points.text);
			
		}
	}
	
}
