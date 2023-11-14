// Include important C++ libraries here
#include <SFML/Graphics.hpp>											//these are the libraries we'll use
#include <SFML/Audio.hpp>
#include <cstdlib>														//some of them are exported from SFML website
#include <ctime>														//that let us use new features, some of them, being graphics uses

#include <sstream>
#include <string>
#include <iostream>

// Make code easier to type with "using namespace"
using namespace sf;														//this namespace is used to show the graphical utilities
// Function declaration

int nuvol;
int seed;																//This int is going to be used as a seed for the randomly generated numbers
int logSpeedX;															//This will be used to introduce the speed some parts will use
const int NumMaxClouds = 3;												//All this const will be used for diferents cases, in this one, for the clouds we'll show
const int distance = 150;												
const int MaxWidth = 1920;												//This Max values will be used to put the screen height and Width values
const int MaxHeight = 1080;
const int PosTimeBar = 980;												//And this one, to create a time bar
const int numBranches = 6;												//same as clouds, this is used to show a number of diferents sprites
String levelName = "DastardlyCave";										//This string is used to show the game name
String playerName = "John Carmack";										
String score1= "Score = 0";												//This will be used to show the total score
String message = "GAME OVER!!";											//And this will be used to create the game over message
bool logActive = false;													//This bool is one of the central gears of the program
float frames = 0;
int score = 0;															//we create an int that stores the score
bool mort = false;
float fps;

	// Where is the player/branch? 
	// Left or Right
	enum class side {LEFT, RIGHT, NONE};								//we create this variable to create 3 parametres, that'll be used in diferents points
	struct Cloud {														//With this, we'll be able to create the struct Cloud, that'll be formed by
		bool active;													//a bool, a sprite and an int called speed, everytime we use the word Cloud
		sf::Sprite sprite;
		int speed;
	};

int main() {															//This is where the program starts
	
	
	Sprite branches[numBranches];										//We set up this for future uses
	side branchPositions[numBranches];									//And this one to make it flip when need it

	srand((int)time(0) * 10);											//this is going to create a random 


														
		// Create a video mode object
		VideoMode vm(1920, 1080);										//using this, we select the weight and height that the screen will generate

		// Create and open a window for the game
		RenderWindow window(vm, "Timber!!!");							//This will create a window with the selected name
		window.setFramerateLimit(60);
		// Create a texture to hold a graphic on the GPU
		Texture textureBackground;										//With this steps, we create the sprite we'll use as a backgroud

		// Load a graphic into the texture
		textureBackground.loadFromFile("graphics/bosc.jpg");			//To do it, we put the dir of the png we'll use

		// Create a sprite
		Sprite spriteBackground;										//We'll create a sprite

		// Attach the texture to the sprite
		spriteBackground.setTexture(textureBackground);					//And we'll put the texture into the sprite

		// Set the spriteBackground to cover the screen
		spriteBackground.setPosition(0, 0);								//After this, we select the position, and at the end of the code, we'll make the program show it
		spriteBackground.setScale(2.65, 2.65);
		// Make a tree sprite

		Texture textureTree;											//We follow the same steps as the background
		textureTree.loadFromFile("graphics/tree.png");					//Select the png for the texture
		Sprite spriteTree;												//Create an sprite
		spriteTree.setTexture(textureTree);								//Put it together
		spriteTree.setPosition(810, 0);									//and finally, choose the position

		Texture textureTree2;											//We follow the same steps as the background
		textureTree2.loadFromFile("graphics/crimson.png");					//Select the png for the texture
		Sprite spriteTree2;												//Create an sprite
		spriteTree2.setTexture(textureTree2);							//Put it together
		spriteTree2.setPosition(-500, 250);								//and finally, choose the position
		spriteTree2.setScale(3, 3);

		Texture textureTree3;											//We follow the same steps as the background
		textureTree3.loadFromFile("graphics/crimson.png");				//Select the png for the texture
		Sprite spriteTree3;												//Create an sprite
		spriteTree3.setTexture(textureTree3);							//Put it together
		spriteTree3.setPosition(0, 100);								//and finally, choose the position
		spriteTree3.setScale(2.5, 3.5);

		Texture textureTree4;											//We follow the same steps as the background
		textureTree4.loadFromFile("graphics/crimson.png");				//Select the png for the texture
		Sprite spriteTree4;												//Create an sprite
		spriteTree4.setTexture(textureTree4);							//Put it together
		spriteTree4.setPosition(1000, 600);								//and finally, choose the position
		spriteTree4.setScale(3, 3);

		Texture textureTree5;											//We follow the same steps as the background
		textureTree5.loadFromFile("graphics/crimson.png");				//Select the png for the texture
		Sprite spriteTree5;												//Create an sprite
		spriteTree5.setTexture(textureTree5);							//Put it together
		spriteTree5.setPosition(810, 140);								//and finally, choose the position
		spriteTree5.setScale(2.5, 3);

		// Prepare the bee

		Texture textureBee;												//same as the 2 lasts sprites
		textureBee.loadFromFile("graphics/bee.png");
		Sprite spriteBee;
		spriteBee.setTexture(textureBee);
		spriteBee.setPosition(100, 800);

		// Is the bee currently moving?
		bool BeeActive = false;											//and in this case we prepare a bool
		// How fast can the bee fly
		float beeSpeed = 0.0f;											//and a float that'll be used later as a flight speed, to create an animation

		Texture textureBee2;												//same as the 2 lasts sprites
		textureBee2.loadFromFile("graphics/bee2.png");
		Sprite spriteBee2;
		spriteBee2.setTexture(textureBee2);
		spriteBee2.setPosition(100, 800);
		spriteBee2.setScale(.5, .5);

		// Is the bee currently moving?
		bool BeeActive2 = false;											//and in this case we prepare a bool
		// How fast can the bee fly
		float beeSpeed2 = 0.0f;											//and a float that'll be used later as a flight speed, to create an animation
		
		
		// make 3 cloud sprites from 1 texture

		Texture textureCloud;											//after that, we create the Cloud texture
		textureCloud.loadFromFile("graphics/cloud.png");				//to introduce the cloud png
		
		const int numClouds = 4;										//after that, we create this const
		const int distance = 150;										//and this const that will help us later
		Cloud spriteCloud[numClouds];									//After this, we call the struct (array) we did at the begining of the program
		for (int i = 0; i < numClouds; i++) {							//and now, we create a void that'll help us to create the numerous clouds we want to use, that, as long as
			spriteCloud[i].active = false;								//i is not equal to the number we choosed as the maxium clouds, it'll work. In this void, every sprite is false
			spriteCloud[i].sprite.setTexture(textureCloud);				//and we set the texture into the sprite, to call it later
			spriteCloud[i].sprite.setPosition(0, 0 * distance);			//and after this, we choose the position of each cloud. The distance value will make us able to separate each cloud
			spriteCloud[i].speed = 2.0f;								//here, we'll put a speed value to each cloud, being the same at all, but'll change it later
			spriteCloud[i].sprite.setScale(.25, .25);					//this is used to set the scale of the clouds, to make it more visible
		}
		


		// Load 1 new texture

		// 3 New sprites withe the same texture

		// Position the clouds off screen

		// Are the clouds currently on screen?

		SoundBuffer chop;												//In this part, we'll be able to use sounds during the program
		chop.loadFromFile("sound/chop.WAV");							//this is very similar as the texture-sprite process, we call a sound buffer
		Sound chop1;													//we put the directory and finally we create a Sound variable
		chop1.setBuffer(chop);											//With this, we are able to fuse them into an unique variable that stores a sound in it

		SoundBuffer xof;												//We do all this for the same, the first one is used to reproduce a sound each time we
		xof.loadFromFile("sound/death.MP3");							//chop the tree, another one is used to create a sound displayed when we die
		Sound death;													//and the last one, used if we run out of time
		death.setBuffer(xof);

		SoundBuffer DK;
		DK.loadFromFile("sound/DK.MP3");
		Sound fi;
		fi.setBuffer(DK);

		// How fast is each cloud?

		

		// Variables to control time itself

		Clock clock;													//with this variable, we're able to use time based actions

		// Time bar

		RectangleShape timeBar;											//Here, we create a rectangle shape that'll be used as a Time Bar
		float timeBarStartWidth = 400;									//to make it able to work, we'll declare 2 variables, one for the width and 
		float timeBarHeight = 80;										//and the other for the height
		timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));	//Here, we set the size, by using the 2 variables created earlier, this'll be used to show the time left
		timeBar.setFillColor(Color::Red);								// We set a color for the rectangle
		timeBar.setPosition((MaxWidth / 2) - timeBarStartWidth / 2, PosTimeBar);	//In this part, we choose where the bar will be positionated
		Time gameTimeTotal;
		float timeRemaining = 6.0f;													//In this part, we're able to select the time we'll want the game to be active
		float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;			//And this will make the rect smaller when the time passes


		//We prepare up a rectangle behind the score to make it more visual
	
		RectangleShape shapeDani;							
		shapeDani.setSize(Vector2f(500.f, 100.f));
		shapeDani.setFillColor(Color::Magenta);
		shapeDani.setOutlineThickness(10);
		shapeDani.setOutlineColor(Color::Yellow);
		shapeDani.setPosition(10, 30);

		RectangleShape shapeMort;
		shapeMort.setSize(Vector2f(450.f, 100.f));
		shapeMort.setFillColor(Color::Blue);
		shapeMort.setOutlineThickness(10);
		shapeMort.setOutlineColor(Color::Black);
		shapeMort.setPosition(730, 490);

		

		// Track whether the game is running

		bool paused = true;												//this bool is used to declare that the game is working. This'll be used later

		// Draw some text

		Text scoreText;													//here we create some text, that'll display the score we get
		
		Text myText;

		// We need to choose a font

		Font font;														//with this function, we are able to create a variable that stores a text font
		font.loadFromFile("fonts/KOMIKAP_.ttf");						//with this variable, we call the file that stores a type of font

		// Set the font to our message

		myText.setFont(font);											//once the font is set, we put it to the text variable
		scoreText.setFont(font);										//we do the same for this part

		// Assign the actual message

		myText.setString("Press Enter to start!");						//we set the strings with the text in it
		scoreText.setString("Score = 0");								

		// Make it really big

		myText.setCharacterSize(75);									//here we set the size of the characters
		scoreText.setCharacterSize(100);

		// Choose a color

		myText.setFillColor(Color::White);								//and then, we finally set the color with setFillerColor
		scoreText.setFillColor(Color::White);

		// Position the text

		FloatRect textRect = myText.getLocalBounds();					//We set the variable textRect that let us construct a rectangle from position to size
		myText.setOrigin(textRect.left +								//with this text, we're able to recreate a rectangle that will put the text in the center
			textRect.width / 2.0f,
			textRect.top +
			textRect.height / 2.0f);
		myText.setPosition(1920 / 2.0f, 1080 / 2.0f);					//with this values, we can put the text in the middle
		scoreText.setPosition(20, 20);									//and with these, we set the position of the score value

		//Frames

		Text FPS;
		FPS.setString("FPS: ");
		FPS.setFillColor(Color::White);
		FloatRect frames = FPS.getLocalBounds();
		FPS.setPosition(1500, 40);
		FPS.setFont(font);
		FPS.setCharacterSize(75);


		// Prepare 6 branches

		Texture textureBranch;											//Here, we prepare the texture to put it various times
		textureBranch.loadFromFile("graphics/branch.png");				//To archieve this, we prepare it as always, calling the dir

		// Set the texture for each branch sprite

		for (int br = 0; br < numBranches; br++) {						//after that, we create a void to create how many branches we want to add

			branches[br].setTexture(textureBranch);						//after this, we put the texture into the sprite
			branches[br].setPosition(-2000, -2000);						//and we set each branch into a position
			//Set the sprite's origin to dead centre
			//We can then spin it round without changing its position
			branches[br].setOrigin(220, 20);							//and finally, an origin where it appears

		}
		//Move all the branches down one place
		for (int seed = 1; seed <= 5; seed++) {							//after all that, we create a void that moves each branch randomly

			//Spawn a new branch at position 0
			// LEFT, RIGHT or NONE

			srand((int)time(0) + seed);									//with this, we'll create a random seed that will make us able to create random nums
			int r = (rand() % 5);										//with this rand, we create a random seed that'll decide which case will be activated

			switch (r) {
			case 0:
				branchPositions[seed] = side::LEFT;						//in case the number generated us 0, a branch will be set at the left
				break;													//this is used to avoid the other cases be displayed

			case 1:
				branchPositions[seed] = side::RIGHT;					//if the randomly generated num is 1, it will set a branch in the right
				break;

			default:
				branchPositions[seed] = side::NONE;						//and if the number is any other than 0 or 1, it will not set any branch
				break;

			}
	}
		// Prepare the player

		Texture texturePlayer;											//same as the others, to create the player, we call it from this dir
		texturePlayer.loadFromFile("graphics/player.png");				//and then set it as a sprite
		Sprite spritePlayer;
		spritePlayer.setTexture(texturePlayer);
		spritePlayer.setPosition(590, 690);								//finally, we set it into the position we want to
		
		// The player starts on the left
		side playerSide = side::LEFT;									//with this, we set that the player is set into the left position
		branchPositions[3] = side::NONE;								//and avoid that a branch is able to appear at the same place as the player

		// Prepare the gravestone
		Texture textureGrave;											//we do the same to create a Grave
		textureGrave.loadFromFile("graphics/rip.png");
		Sprite spriteGrave;
		spriteGrave.setTexture(textureGrave);
		spriteGrave.setPosition(650, 875);

		// Prepare the axe
		Texture textureAxe;												//same goes to the Axe
		textureAxe.loadFromFile("graphics/axe.png");
		Sprite spriteAxe;
		spriteAxe.setTexture(textureAxe);
		spriteAxe.setPosition(700, 800);

		// Line the axe up with the tree
		const float AXE_POSITION_LEFT = 700;							//we prepare the positions that the axe will appear if the conditions Left or Right are created
		const float AXE_POSITION_RIGHT = 1075;
		
		// Prepare the flying log
		Texture textureLog;												//we create another sprite, and this one will be set in another part of the program
		textureLog.loadFromFile("graphics/log.png");
		Sprite spriteLog;
		spriteLog.setTexture(textureLog);

		// Some other useful log related variables

		// Control the player input

		bool acceptInput = false;										//we create a bool that will help us with the character actions

		// Prepare the sound

		// Out of time

		//game loop
		while (window.isOpen())											//here, we'll create a loop that will let us control everything we've created
		{
			
			/*
			****************************************
			Handle the players input
			****************************************
			*/
			sf::Event event;											//with this, we create a condition, that depends entirely form what event says
			while (window.pollEvent(event))
			{

				if (event.type == Event::Closed)						//in this case, we set that, in case we press the cross and close the program, it'll stop
					window.close();										//this makes the window to close

				else if (Keyboard::isKeyPressed(Keyboard::Escape))		//this sets that, in case the player presses ESC, the program will close
					window.close();

				else if (event.type == Event::KeyReleased && !paused) {	//This part, will set that, as long the game is not paused and the player is not pressing anything
					//Listen for key presses again						//the program will set the acceptInput into true to make the player able to move
					acceptInput = true;
					mort = false;
					//hide the Axe
					spriteAxe.setPosition(2000,							//this is used to hide the axe, and make it more appealing
						spriteAxe.getPosition().y);
				}
			}

			if (Keyboard::isKeyPressed(Keyboard::Return))				//if the player presses enter, the program will create this 
			{
				paused = false;											//the bool paused will be stated into false, stating that the game can start
				//Reset the time and score
				score = 0;												//this will make us able to reset the game, setting the score and the time as default
				timeRemaining = 6;

				//Make all the branches disappear
				//starting in the second position
				for (int i = 1; i < numBranches; i++) {					//this makes all the branches disapper when we press Enter

					branchPositions[i] = side::NONE;
				}
				//Make sure the Gravestone is hidden
				spriteGrave.setPosition(675, 2000);						//we hide the gravestone, that'll appear when the player dies

				//Move the player into position
				spritePlayer.setPosition(580, 720);						//We'll set the player at the left position of the tree
				acceptInput = true;										//and we'll set this boll into true to create the actions
			}

			// Wrap the player controls 

			if (acceptInput) {											//as we already said, this bool is now true, so it will activate this if state
				
				// Make sure we are accepting input
				if (Keyboard::isKeyPressed(Keyboard::Right)) {			//into the condition, we set a diferent condition, setting that everytime we hit the key right
					
					// First handle pressing the right cursor key
					playerSide = side::RIGHT;							//it will the the player to the right side
					score++;											//and will add 1 point to the score count
					
					// Add to the amount of time remaining
					timeRemaining += (2 / score) + .15;					//adding some time to the time bar
					spriteAxe.setPosition(AXE_POSITION_RIGHT,			//and displaying the axe at the stated place 
						spriteAxe.getPosition().y);
					spritePlayer.setPosition(1200, 720);

					// update the branches
					for (int j = numBranches - 1; j > 0; j--) {			//with this, we make one branch disappear and fall down
						branchPositions[j] = branchPositions[j - 1];

					}

					//Spawn a new branch at position 0
						//LEFT, RIGHT OR NONE
					int r = (rand() % 5);								//we'll need to create new branches too, doing the same rand and switch done earlier
					switch (r) {
					case 0:
						branchPositions[0] = side::LEFT;
						break;

					case 1:
						branchPositions[0] = side::RIGHT;
						break;

					default:
						branchPositions[0] = side::NONE;
						break;
					}
					
					//Set the log flying to the left
					chop1.play();										//with this, we'll make the chop sound play 
					spriteLog.setPosition(810, 720);					//and we'll create an animation of the log being ejected
					logSpeedX = -5000;									//this part makes us able to set the speed
					logActive = true;									
					acceptInput = false;								//and this one will set this bool being set into false to be able to start the void again

					std::stringstream ss;								//and with this, we set a string that count the total amount of score
					ss << "Score= " << score;
					scoreText.setString(ss.str());
				}

			// Handle the left cursor key
				if (Keyboard::isKeyPressed(Keyboard::Left)) {			//this condition is set in case the program detects the player presses left
					
					// First handle pressing the right cursor key
					playerSide = side::LEFT;							//It makes the playerSide stores a LEFT value
					score++;											//and adds a point
					
					// Add to the amount of time remaining
					timeRemaining += (2 / score) + .15;					//this adds a second each time the key is pressed
					spriteAxe.setPosition(AXE_POSITION_LEFT,			//and we have to set the axe being displayed at the side we hit 
						spriteAxe.getPosition().y);						
					spritePlayer.setPosition(580, 720);					//and finally, the player sprite in it

					// update the branches
					for (int j = numBranches - 1; j > 0; j--) {			//we create a void that deletes one branch and updates it
						branchPositions[j] = branchPositions[j - 1];	//making one disappear each time the key is pressed

					}

					//Spawn a new branch at position 0
						//LEFT, RIGHT OR NONE
					int r = (rand() % 5);								//after making one branch disappear, we create a new one
					switch (r) {										//by setting a random void with the switch function
					case 0:												//explained earlier in the code
						branchPositions[0] = side::LEFT;
						break;

					case 1:
						branchPositions[0] = side::RIGHT;
						break;

					default:
						branchPositions[0] = side::NONE;
						break;
					}
					//Set the log flying to the left

					chop1.play();										//like the last one, we play the sound 
					spriteLog.setPosition(810, 720);					//and make the log fly again
					logSpeedX = -5000;									//and we set the speed of it
					logActive = true;									//and set this value into 
					acceptInput = false;								//and we set this bool into to false to make it able to hit a tile again
				
					std::stringstream ss;								//with this part, we set the string and display it with the updated version of the score int
					ss << "Score= " << score;
					scoreText.setString(ss.str());
				}

			}
			
			if (score >= 10) {											//with this part, we set that the rectangle behind the score

				shapeDani.setSize(Vector2f(550.f, 100.f));				//has to get larger in case the score is superior to 10

			}
			if (score >= 100) {											//and here we do the same in case the score is superior to 100

				shapeDani.setSize(Vector2f(600.f, 100.f));

			}

			/*
			****************************************
			Update the scene
			****************************************
			*/

			if (!paused)												//this condition states that in case the state paused changes, it activates this code
			{
				// Measure time
				Time dt = clock.restart();								//here we create a time variable called dt work along the clock function we called at first
				Time predt = clock.getElapsedTime();

				//Update the fps

				fps = 1.f / (dt.asSeconds() - predt.asSeconds());

				predt = dt;

				std::stringstream sa;									//and with this, we set a string that count the total amount of frames
				sa << "FPS = " << fps;
				FPS.setString(sa.str());
				// Subtract from the amount of time remaining

				timeRemaining -= dt.asSeconds();						//With this, we convert the dt function to seconds, and apply it to the time remaining
																		//which has already been called earlier
				// size up the time bar

				timeBar.setSize(Vector2f(timeBarWidthPerSecond *		//with this, we are able to create a time bar that changes along the time
					timeRemaining, timeBarHeight));

				if (timeRemaining <= 0.0f) {							//this conditional activates in case the time reaches 0

					// Pause the game

					paused = true;										//stating that the bool paused becomes true, changing the program

					// Change the message shown to the player
					
					
					
					myText.setString("Out of time!!");					//and this message will display 
					
					//Reposition the text based on its new size

					FloatRect textRect = myText.getLocalBounds();				//to select the position, we write this part of the code
					myText.setOrigin(textRect.left + textRect.width / 2.0f,
						textRect.top + textRect.height / 2.0f);
					myText.setPosition(MaxWidth / 2.0f, MaxHeight / 2.0f);
					fi.play();

					

				}

				// Play the out of time sound


			// Setup the bee
				if (!BeeActive) {										//this conditional helps us to make the bee 
					//How fast is the bee
					beeSpeed = (rand() % 200) + 400;					//here we can select the speed we want it to have, by setting a rand and a limit, and the minium speed

					//How high is the bee
					float height = (rand() % 500) + 500;				//here we create a float that will decide how high will the bee fly
					spriteBee.setPosition(2000, height);				//and where it will appear. Here we use the height value to make it random and change it everytime
					BeeActive = true;									//then, the bool will be active

				}
				else													//and now, we create an else that will help us move it
					//Move the bee
				{
					spriteBee.setPosition(								//by setting it like this, we're able to make it move, by calling the position, and rest everysecond
						spriteBee.getPosition().x -						//a random speed value, created earlies
						(beeSpeed * dt.asSeconds()),
						spriteBee.getPosition().y);						//and in this part, the position y will always remain the same

					//Has the bee reached the left-hand edge of the screen?

					if (spriteBee.getPosition().x < -100)				//with this, we state that, if the bee reaches this position
					{
						//Set it up ready to be a whole new bee next frame
						BeeActive = false;								//it'll be set into a false state, making it appear again in a diferent position
					}



				}

				if (!BeeActive2) {										//this is the same as the last bee, the diference is that, we change the sprite

					//How fast is the bee
					beeSpeed2 = (rand() % -300) + -700;					//and by applying this diference, or we could make it into the else making it a +
																		//we're able to make it move to the right
					//How high is the bee
					float height2 = (rand() % 300) + 700;				//and by using this float, we can make it appear like the second moving item is 
					spriteBee2.setPosition(0, height2);					//running 
					BeeActive2 = true;

				}
				else
					//Move the bee
				{
					spriteBee2.setPosition(
						spriteBee2.getPosition().x -					//if we would've changed this part, making it a +, it could have work
						(beeSpeed2 * dt.asSeconds()),
						spriteBee2.getPosition().y);

					//Has the bee reached the left-hand edge of the screen?

					if (spriteBee2.getPosition().x >= 2000)				//same as the other, we state that if the sprite reaches a certain position, it resets into a new one
					{
						//Set it up ready to be a whole new bee next frame
						BeeActive2 = false;
					}



				}

			// Manage the clouds
				for (int i = 0; i < numClouds; i++) {						//this part is kinda tricky, we create a bool to make numerous clouds, using the variable numClouds, used earlies
					if (!spriteCloud[i].active) {							// the i int is used to call and control each cloud
						spriteCloud[i].speed = (rand() % 200) + 350;		//by making this, we give to every cloud a randomly generated speed
						float height = rand() % (distance * (i + 1));		//and we apply the same float as earlier, but using a distance const to separate them, and making it random
						spriteCloud[i].sprite.setPosition(-200, height);	//using the last float, we're abñe to set the position in each cloud faster
						spriteCloud[i].active = true;						//and each cloud will be set into true
					}
					else {
						spriteCloud[i].sprite.setPosition(														//once all aplied, we set the sprite to move
							spriteCloud[i].sprite.getPosition().x + (spriteCloud[i].speed * dt.asSeconds()),	//as we did with the last one, we set the first position
							spriteCloud[i].sprite.getPosition().y);												//and then we make it add more per second
						if (spriteCloud[i].sprite.getPosition().x > MaxWidth) {									//making it move, and if it reaches the limit of the screen
							spriteCloud[i].active = false;														//it will make it appear again as a false state, starting again the proces
						}

					}
				}


				// Handle a flying log		
				if (logActive) {											//this part is very similar to the last one, with the diference we make the element move
																			//in a perpendicular path
					float logSpeedY;										//this varible is called here because it wasn't called earlier, but it'll work too
				
					logSpeedX = 5000;										//we set a these 2 variables the speed we'll want to play
					logSpeedY = 3000;
					if (playerSide == side::LEFT) {							//with this, we make that if the player, is at the left side, it will display an animation 
						spriteLog.setPosition(												//that'll display the sprite as it flies away to the right
							spriteLog.getPosition().x - (-logSpeedX * dt.asSeconds()),		//to create this we follow the same order as lately, making them get the position an then rest it
							spriteLog.getPosition().y - (logSpeedY * dt.asSeconds())
						);
					}
					else if (playerSide == side::RIGHT) {									//and if the player is at the right side, the sprite will fly to the left
						spriteLog.setPosition(												//we also could do it like this, or we could it just make it a + state
							spriteLog.getPosition().x - (logSpeedX * dt.asSeconds()),
							spriteLog.getPosition().y - (logSpeedY * dt.asSeconds())
						);
					}

				}
				

				// has the player been squished by a branch?

				if (branchPositions[5] == playerSide)						//in this scenario, we'll create a Game over, so the player has to be careful with the branches
				{
					//death
					paused = true;											//to make this, if the fifth branch is at the player side, we set the game into pause with the bool
					acceptInput = false;									//and we stop the acceptInput condition into a false, so the player cannot keep playing
					//Draw the gravestone
					if (playerSide == side::LEFT) {							//with this part, we'll create a GraveStone, depending on the side
						spriteGrave.setPosition(525, 760);
					}
					else if (playerSide == side::RIGHT) {
						spriteGrave.setPosition(1200, 760);
					}
					//hide the playter
					spritePlayer.setPosition(2000, 660);					//and with this part, we make the player disapper by just putting him in an unseen part 
					//Change the text of the message
					myText.setString("SQUISHED!!");							//we display a message anouncing the game over
					//Center it on the screen
					FloatRect textRect = myText.getLocalBounds();			// and we set the position where the message would be displayed
					myText.setOrigin(textRect.left + textRect.width / 2.0f,
						textRect.top + textRect.height / 2.0f);
					myText.setPosition(1920 / 2.0f, 1080 / 2.0f);
					 mort = true;

					death.play();
				}
			}// End if(!paused)
				for (int br = 0; br < numBranches; br++) {							//with this part of the code, we are able to make the branches spawn
																					//the amount of times we call it at the const numBranches
									float height = br * 150;						//by setting this, we create a float that will be used to put the separation to each branch

									if (branchPositions[br] == side::LEFT) {		//thanks to a previous part of the code, each branch will be created in a diferent side of the tree

										//Move the sprite to the left side
										branches[br].setPosition(610, height);		//so here we're just saying where and how the branch should be created
										//Flip the sprite round the other way
										branches[br].setRotation(180);				//and with this part, we make it look to the left

									}
									else if (branchPositions[br] == side::RIGHT) { //in case the side of the branch is set as RIGHT, this part will be created

										//Move the sprite to the right side
										branches[br].setPosition(1330, height);		//setting the X position as 1330 and the height as the float we called earlier
										//Set the sprite rotation to normal
										branches[br].setRotation(0);				//in this case it's not necessary to rotate it because it's already looking to the right
	
									}
									else {											//and if the branch does not appear in any of these 2, we just have to hide it
																					//by just putting it at a far side of the screen
										//Hide the branch
										branches[br].setPosition(3000, height);
									}
				}
			 /*
			 ****************************************
			 Draw the scene
			 ****************************************
			 */

			 // Clear everything from the last frame
				window.clear();												//by using this, we make the program clear everything passed. If this is not done properly
																			//the program will always display everything at the same time
				// Draw our game scene here
				window.draw(spriteBackground);								//this is used to display the Background, created earlier
				window.draw(shapeDani);										//and this to display the square behind the score
				window.draw(FPS);

				// Draw the clouds
				for (int i = 0; i < numClouds; i++) {						//with this part, we're able to set each cloud being created one by one and not having to do many coding

					window.draw(spriteCloud[i].sprite);
				}
				window.draw(spriteTree2);									//we'll use this to create diferent trees, displayed in a diferent order
				window.draw(spriteTree3);
				
				window.draw(spriteTree5);
			// Draw the branches
				

				for (int br = 0; br < numBranches; br++) {					//same as the clouds, we make a void to create each branch with just 2 lines of code
					window.draw(branches[br]);
				}

				// Draw the tree
				window.draw(spriteTree);									//here, we display the central tree
				

				// Draw the player
				window.draw(spritePlayer);									//this part is used for the player
				// Draw the axe
				window.draw(spriteAxe);										//this for the axe
				// Draraw the flying log
				window.draw(spriteLog);										//this one for the piece of log we cut
				// Draw the gravestone
				window.draw(spriteGrave);									//here for the Grave

				// Drawraw the bee
				window.draw(spriteBee);										//and this will display the bee
				window.draw(spriteBee2);									//and this one, the Arale's running sprite

				window.draw(spriteTree4);									//we've drawn this tree here to make depth perspective, as we want the bee and the other sprite 
																			//to be pass throught behind the tree
				// Draw the score
				if (mort) {

					window.draw(shapeMort);

				}
				window.draw(scoreText);
				if (paused) {

					window.draw(myText);
				}
				
				// Draw the timebar

				window.draw(timeBar);										//here we display the time bar

				// Show everything we just drew
				window.display();											//and if we don't put this part here, nothing will be shown


			}

	return 0;
}

		
