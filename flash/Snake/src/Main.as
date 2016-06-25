package  {
	
	import flash.display.MovieClip;
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.events.KeyboardEvent;
	import flash.display.DisplayObject;
	
	public class Main extends Sprite{

		public var head:Snake;
		public var snake:Array;
		public var food:Food;
		public var _points:Points;
		public var button:GameButton;
		
		public var direct:int; //-1 = reset,0 = up, 1 = right, 2 = down, 3 = left
		
		public var snakeDead:Boolean = false;
		public var countClick:int;
		public var countTick:int;
		public var speed:int = 5;
		public var score:int = 0;
		
		public static var LINE_WIDTH:int = 10;
		public static var screenWidth:int = 480;
		public static var screenHeight:int = 800;
		
		///
		//public var init = function();
		///
		//[SWF(width="800", height="200", backgroundColor="0x8B8B8B")]
		public function Main() {
			// constructor code
			//[SWF(width="800", height="200", backgroundColor="0x8B8B8B")];
			super();
			
			if(stage)
				init();
				//updateNewDirect();
				//newFood();
			else 
				addEventListener(Event.ADDED_TO_STAGE, init, false, 0, true);
				
				
				
			//trace("stage x: " + stage.width);
			
		}
		
		public function init($e:Event = null):void
		{
			trace("call init()");
			removeEventListener( Event.ADDED_TO_STAGE, init );
			
			
			button = new GameButton();
			button.x = Math.round(screenWidth/2);
			button.y = Math.round(screenHeight/2);
			//
			addChild(button);
			
			countTick = 0;
			head = new Snake();
			_points = new Points();
			food = new Food();
			
			//this.addChild();
			
			///
			head.x = screenWidth/2;
			head.y = screenHeight/2;
			
			
			//trace("x: " + head.x + "-y: " + head.y);
			//trace("stage x: " + stage.width + "-y: " + stage.height);
			
			this.addChild(food);
			food.visible = true;
			
			this.addChild(head);
			//head.visible = true;
			
			//head.x = stage.x - head.width;
			//hidden fisrt time
			
			food.visible = false;
			head.visible = false;
			
			//this.addChild(_points);
			score = 0;
			_points.setScore = 0;
			
			//for food
			food.addEventListener(MouseEvent.CLICK, hiddenFood);
			
			//for snake
			stage.addEventListener(KeyboardEvent.KEY_UP, onPressKeyUp);
			stage.addEventListener(KeyboardEvent.KEY_DOWN, onPressKeyDown);
			
			stage.addEventListener(Event.ENTER_FRAME, thisOnEnterFrame);
			button.addEventListener(MouseEvent.CLICK, pressButton);
			
		}
		
		public function thisOnEnterFrame($event:Event):void
		{
			//this.addEventListener(KeyboardEvent.KEY_UP, onKeyUp);
			//this.addEventListener(KeyboardEvent.KEY_DOWN, onKeyDown);
			
			
			/*if(countTick < 60)
				countTick++;
			else
			{
				countTick = 0;				
				if(!food.visible)
					newFood();
			}*/
			countTick++;
			
			playingGame(!button.visible);
				
			
			
			//updateNewDirect();//try this			
			//trace
			//moveHead();
			
			
		}
		
		public function playingGame($playing:Boolean):void
		{
			if($playing)
			{
				if (countTick == 30)
				{
					//newFood();
					//trace("");
				}
			
				else if (countTick == 60)
				{
					//hiddenFood(null);
					countTick = 0;
				}
			
			
				if (!checkGameOver(null, head))
				{
					if (Math.round(countTick %Math.round(10/speed)) == 0)
						updateNewDirect();
				}else
				{
					button.setText = "Replay";
					button.enabled = true;
					button.visible = true;
				}
				
				
				
				
				
				
				
				
				
				//trace("this");
				if (checkCollision(head, food))
				{
					//trace (":DDDDDDDDD");
					score += 10;
					_points.setScore = score;
					hiddenFood(null);
					newFood();
				}
				
			}else
			{
				return;
			}
		}
		
		public function pressButton($event:Event):void
		{
			button.enabled = false;
			button.visible = false;
			
			
			//if(button.labelTextButton.text == "Replay")
			{
				food.visible = true;
				head.visible = true;
			}
			
			//start new game
		}
		
		public function hiddenFood($event:MouseEvent):void
		{
			
			
			//countClick++;
			//trace("click " + countClick++ + " " + this.mouseX + " " + this.mouseY);
			
			//if((food.x <= this.mouseX) && (this.mouseX <= (food.x + food.width))
			//   &&(food.y <= this.mouseX) && (this.mouseY <= (food.y + food.height))
			//   && food.visible == true)
			{
				//trace("set visible");
				
				//if((head.x <= food.x + food.width) && (head.x <= food.x))
				
				var midFood:int = Math.round(food.width/2);
				var midHead:int = Math.round(head.width/2);
				var distance:int = midFood + midHead;
				
				if(distance <= (food.x + food.width))
					food.visible = false;	
			}
			
		}
		
		public function newFood():void
		{
			//trace("call newFood");
			
			
			
			//food.x = Math.round(Math.random()*stage.width);
			//food.y = Math.round(Math.random()*stage.height + _points.height*1.5);
			
			food.x = Math.round(Math.random()*screenWidth);
			food.y = Math.round(Math.random()*screenHeight + 54); //54 is magic number
			
			//
			
			//if ((food.x <= head.x) || head.width <=(food.x + food.width))
			//if(food.x + food.width )
				food.visible = true;
			
			//trace(food.x + " " +food.y)
			
			
			
		}
		
		
		public function onPressKeyUp($event:KeyboardEvent):void
		{
			//trace(" " + $event.keyCode);
			
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
			//trace("direct: " + direct);
			
			switch($event.keyCode)
			{
				
				
				case 37: //left arrow
					if(!(direct == 1 || direct == 3))
					{
							direct = 3;
						//trace("press left arrow");
					}
					
					break;
				case 38: //up arrow
					if(!(direct == 2 || direct == 0))
						direct = 0;
					//trace("press up arrow");
					break;
				case 39: //right arrow
					if(!(direct == 3 || direct == 1))
					{
						direct = 1;
					//trace("press right arrow");
						
					}
						
					break;
				case 40: //down arrow
					if(!(direct == 0 || direct == 2))
						direct = 2;
					//trace("press down arrow");
					break;
				
				
					
				default:
				break;
			}
			
			//updateNewDirect();
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
					//trace("head x: " + head.x + " -head y: " + head.y);
					break;
				case 1://right
					head.x = (snakeDead)? head.x : head.x + head.width;
					//trace("head x: " + head.x + " -head y: " + head.y);
					break;
				case 2://down
					head.y = (snakeDead)? head.y : head.y + head.height;
					//trace("head x: " + head.x + " -head y: " + head.y);
					break;
				case 3://left
					head.x = (snakeDead)? head.x : head.x - head.width;
					//trace("head x: " + head.x + " -head y: " + head.y);
					break;
				
				default:
				break;
			}
			
			//reset direct value
			//direct = -1;
		}
		
		
		public function checkCollision($objA:DisplayObject, $objB:DisplayObject):Boolean
		{
			//a = sprt(b^2+c^2)
			var disX:Number = Math.abs($objA.x - $objB.x);
			var disY:Number = Math.abs($objA.y - $objB.y);
			var distance:Number = Math.sqrt(Math.pow(disX, 2) + Math.pow(disY, 2));
			
			var staticDistance:Number = ($objA.width/2 + $objB.width/2); //width = height
			
			if(distance <= staticDistance/1.5)
				return true;
			else
				return false;
		}
		
		public function checkGameOver($snake:Array, $objHead:DisplayObject):Boolean
		{
			//check conllision to wall
			if($objHead.x <= 0 //left wall
			   || (($objHead.x + $objHead.width) >= screenWidth) //right wall
			   || ($objHead.y <= 54) //up wall..hard code = 54
			   || (($objHead.y + $objHead.height) >= screenHeight)) //bottom wall
			 {
				 //  trace("game over");
				 //
				   return true;
				   
			 }
			 else
			 {
				 return false;
			 }
			   
			   
			   
			 //return false
		}
	}
	
}
