package  {
	
	import flash.display.MovieClip;
	import flash.text.*;
	import flash.geom.Point;

	//import flash.geom.Point;
	
	
	public class Points extends MovieClip {
		
		//public var textLabel:TextField;
		//public var scoreValue:int = 10;
		//public var Points:TextField;
		
		public function Points() {
			// constructor code
			//Points = new TextField();
			//addChild(Points);
			//Points.text = String(scoreValue);
			
			//trace(Points.text);
			
			//ScoreValue(10);
			
			if(score != null)
			{
				score.wordWrap = true;
				//align = TextWithStyle.LEFT;
				score.text = "1234";
			}
		}
		
		public function set setScore($s:int):void
		{
			//scoreValue = $score;
			score.text = String($s);
			
			//trace("call me: Points.length: " + score.length + " " + score.text);
			
		}
	}
	
}
