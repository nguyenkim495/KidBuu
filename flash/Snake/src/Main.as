package  {
	
	import flash.display.MovieClip;
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.events.KeyboardEvent;
	
	public class Main extends Sprite{

		public var head:Snake;
		public var snake:Array;
		public var food:Food;
		public var _points:points;
		public var direct:int; //-1 = reset,0 = up, 1 = right, 2 = down, 3 = left
		
		public var snakeDead:Boolean = false;
		public var countClick:int;
		
		///
		//public var init = function();
		///
		
		public function Main() {
			// constructor code
			
			//if(!stage)
			//iniṭ();
			
			
			
			head = new Snake();
			_points = new points;
			food = new Food();
			
			//this.addChild();
			
			this.addChild(food);
			food.visible = true;
			
			this.addChild(head);
			head.visible = true;
			
			this.addChild(_points);
			_points.ScoreValue = 192138;
			
			//for food
			food.addEventListener(MouseEvent.CLICK, hiddenFood);
			
			//for snake
			stage.addEventListener(KeyboardEvent.KEY_UP, onPressKeyUp);
			stage.addEventListener(KeyboardEvent.KEY_DOWN, onPressKeyDown);
			
			stage.addEventListener(Event.ENTER_FRAME, thisOnEnterFrame);
			
		}
		
		public function init():void
		{
			trace("call init()");
			
			head = new Snake();
			_points = new points;
			food = new Food();
			
			//this.addChild();
			
			this.addChild(food);
			food.visible = true;
			
			this.addChild(head);
			//head.visible = true;
			
			head.x = stage.x - head.width;
			
			this.addChild(_points);
			_points.ScoreValue = 192138;
			
			//for food
			food.addEventListener(MouseEvent.CLICK, hiddenFood);
			
			//for snake
			stage.addEventListener(KeyboardEvent.KEY_UP, onPressKeyUp);
			stage.addEventListener(KeyboardEvent.KEY_DOWN, onPressKeyDown);
			
			stage.addEventListener(Event.ENTER_FRAME, thisOnEnterFrame);
		}
		
		public function thisOnEnterFrame($event:Event):void
		{
			//this.addEventListener(KeyboardEvent.KEY_UP, onKeyUp);
			//this.addEventListener(KeyboardEvent.KEY_DOWN, onKeyDown);
			
			//trace("this");
			if(!food.visible)
				newFood();
			
			
			//updateNewDirect();//try this			
			//trace
			//moveHead();
			
			
		}
		
		public function hiddenFood($event:MouseEvent):void
		{
			//countClick++;
			trace("click " + countClick++ + " " + this.mouseX + " " + this.mouseY);
			
			//if((food.x <= this.mouseX) && (this.mouseX <= (food.x + food.width))
			//   &&(food.y <= this.mouseX) && (this.mouseY <= (food.y + food.height))
			//   && food.visible == true)
			{
				trace("set visible");
				food.visible = false;	
			}
			
		}
		
		public function newFood():void
		{
			trace("call newFood");
			food.x = Math.round(Math.random()*stage.width);
			food.y = Math.round(Math.random()*stage.height);
			
			//
			food.visible = true;
			
			trace(food.x + " " +food.y)
			
			
		}
		
		
		public function onPressKeyUp($event:KeyboardEvent):void
		{
			trace(" " + $event.keyCode);
			
			switch($event.keyCode)
			{
				case 37: //left arrow
					//direct = -1;
					//trace("press left arrow");
					break;
				case 38: //up arrow
					//direct = -1;
					//trace("press up arrow");
					break;
				case 39: //right arrow
					//direct = -1;
					//trace("press right arrow");
					break;
				case 40: //down arrow
					//direct = -1;
					//trace("press down arrow");
					break;
					
				default:
				break;
			}
		}
		
		public function onPressKeyDown($event:KeyboardEvent):void
		{
			trace("direct: " + direct);
			
			switch($event.keyCode)
			{
				
				
				case 37: //left arrow
					if(!(direct == 1 || direct == 3))
						direct = 3;
					trace("press left arrow");
					break;
				case 38: //up arrow
					if(!(direct == 2 || direct == 0))
						direct = 0;
					trace("press up arrow");
					break;
				case 39: //right arrow
					if(!(direct == 3 || direct == 1))
						direct = 1;
					trace("press right arrow");
					break;
				case 40: //down arrow
					if(!(direct == 0 || direct == 2))
						direct = 2;
					trace("press down arrow");
					break;
				
				
					
				default:
				break;
			}
			
			updateNewDirect();
		}
		
		public function moveHead():void
		{
			var bounceX:int = head.x + head.width;
			var bounceY:int = head.y + head.height;
			
			var invalidRoundX:int = stage.width - bounceX;
			var invalidRoundY:int = stage.height - bounceY;
			
			if(invalidRoundX >= 0)
				head.x = head.x + head.width;
		}
		
		public function updateNewDirect():void
		{
			switch(direct)
			{
				case -1: //do no thing
					break;
				case 0://up
					//head.x = head.x + head.width;
					head.y = (snakeDead)? head.y : head.y - head.height;
					break;
				case 1://right
					head.x = (snakeDead)? head.x : head.x + head.width;
					break;
				case 2://down
					head.y = (snakeDead)? head.y : head.y + head.height
					break;
				case 3://left
					head.x = (snakeDead)? head.x : head.x - head.width;
					break;
				
				default:
				break;
			}
		}

	}
	
}
