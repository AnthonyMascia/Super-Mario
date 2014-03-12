// Programmer: Anthony Mascia
// Course: Video Game Design
// Due Date: May 2, 2013
//
// Final Game
//
// This will attempt to recreate the classic game "Super Mario Bros".
// The user will be able to control a character named Mario with
// the arrow keys and his objective is to get to the end of the map
// without dying while collecting as many coins as he can. Mario
// will face enemies called Goombas that can be killed by Mario
// jumping on top of them. Mario must also avoid the fire, as
// it will cost Mario a life. If Mario loses all lives, he will lose.


// Includes, namespace and prototypes
#include "template.h"
#include <vector>
using namespace AGK;
app App;

void generateStartScreen();
void generateInstructions();
void generateGameoverScreen();
void wipeAllSprites();
void generateWorld();
void setupSprites();
void updateMario();
void updateWorld();
void checkObstacleCollision();
bool collideLeft(int, int);
bool collideRight(int, int);
bool collideTop(int, int);
bool collideBottom(int, int);
void checkLeftBoundary();
void checkRightBoundary();
void checkJump();
void moveGoombas();
void checkGoombaCollision();
void checkFireCollision();
void checkCoinBoxCollision();
void moveBlock(int, float, const float);
void updateCoins();
void updateLives();
void checkMusic();
void checkGameover();

// Height and width of the screen
const int SCREEN_WIDTH      = 640;
const int SCREEN_HEIGHT	    = 480;

// Image Indexes
const int MARIO				= 1;
const int BG				= 2;
const int FLOOR				= 3;
const int COINBLOCK			= 4;
const int PIPE              = 5;
const int BLOCK             = 6;
const int PINKBLOCK         = 7;
const int BLUEBLOCK         = 8;
const int BLANKBLOCK        = 9;
const int GOOMBA            = 10;
const int FIRE				= 11;
const int CASTLE		    = 12;
const int COIN		        = 13;
const int STARTSCREEN       = 14;
const int INSTRUCTIONSCREEN = 15;
const int GAMEOVERSCREEN    = 16;
const int MARIOLIVES        = 17;

// Text IDs
const int DISPLAY_LIVES = 1;
const int DISPLAY_COINS = 2;
const int GAMEOVER_TEXT = 3;

/********************/
/** SPRITE INDEXES **/
/********************/
const int BG_INDEX    = 1;
const int MARIO_INDEX = 2;
/** Obstacle Sprites **/
const int FLOOR_INDEX = 3;
// Coin Blocks Sprite Indexes
const int COINBLOCK1_ROWONE_INDEX  = 4, COINBLOCK2_ROWONE_INDEX  = 5, 
	      COINBLOCK3_ROWONE_INDEX  = 6, COINBLOCK4_ROWONE_INDEX  = 7, 
		  COINBLOCK5_ROWONE_INDEX  = 8, COINBLOCK6_ROWONE_INDEX  = 9,
		  COINBLOCK7_ROWONE_INDEX  = 10, COINBLOCK8_ROWONE_INDEX = 11;
const int COINBLOCK1_ROWTWO_INDEX  = 12, COINBLOCK2_ROWTWO_INDEX = 13, 
		  COINBLOCK3_ROWTWO_INDEX  = 14, COINBLOCK4_ROWTWO_INDEX = 15,
		  COINBLOCK5_ROWTWO_INDEX  = 16, COINBLOCK6_ROWTWO_INDEX = 17;
// Obstacle Block Sprite Indexes
const int BLOCK1_INDEX  = 18, BLOCK2_INDEX  = 19, BLOCK3_INDEX  = 20,
		  BLOCK4_INDEX  = 21, BLOCK5_INDEX  = 22, BLOCK6_INDEX  = 23,
		  BLOCK7_INDEX  = 24, BLOCK8_INDEX  = 25, BLOCK9_INDEX  = 26,
		  BLOCK10_INDEX = 27, BLOCK11_INDEX = 28, BLOCK12_INDEX = 29,
		  BLOCK13_INDEX = 30, BLOCK14_INDEX = 31, BLOCK15_INDEX = 32,
		  BLOCK16_INDEX = 33, BLOCK17_INDEX = 34, BLOCK18_INDEX = 35,
		  BLOCK19_INDEX = 36, BLOCK20_INDEX = 37, BLOCK21_INDEX = 38,
		  BLOCK22_INDEX = 39;
// Pink Block Sprite Indexes
const int PINKBLOCK1_INDEX = 40, PINKBLOCK2_INDEX  = 41, 
	      PINKBLOCK3_INDEX = 42, PINKBLOCK4_INDEX  = 43, 
		  PINKBLOCK5_INDEX = 44, PINKBLOCK6_INDEX  = 45, 
		  PINKBLOCK7_INDEX = 46, PINKBLOCK8_INDEX  = 47, 
		  PINKBLOCK9_INDEX = 48, PINKBLOCK10_INDEX = 49;
// Blue Block Sprite Indexes
const int BLUEBLOCK1_INDEX = 50, BLUEBLOCK2_INDEX = 51;
// Pipe Sprite Indexes
const int PIPE1_INDEX = 52, PIPE2_INDEX = 53,
          PIPE3_INDEX = 54, PIPE4_INDEX = 55;
// Fire Sprite Indexes
const int FIRE1_INDEX = 56, FIRE2_INDEX = 57, FIRE3_INDEX = 58,
		  FIRE4_INDEX = 59, FIRE5_INDEX = 60, FIRE6_INDEX = 61;
// Castle Sprite Index
const int CASTLE_INDEX = 62;

/** Goomba Sprite Indexes **/
const int GOOMBA1_INDEX = 63, GOOMBA2_INDEX = 64, GOOMBA3_INDEX = 65,
		  GOOMBA4_INDEX = 66, GOOMBA5_INDEX = 67, GOOMBA6_INDEX = 68;

/** Beginning and Ending screens sprite indexes **/
const int STARTSCREEN_INDEX    = 72;
const int INSTRUCTIONS_INDEX   = 73;
const int GAMEOVERSCREEN_INDEX = 74;

/** Misc Sprite Indexes **/
const int GAME_COIN_INDEX    = 69,  // Coin shown when coin block hit
		  DISPLAY_COIN_INDEX = 70,  // Coins user has gotten
		  MARIOLIVES_INDEX   = 71;  // Mario's lives

/** Constants for All Sprites **/
const int SPRITES_START           = 1,
		  SPRITES_END			  = 71;
/** Constants for Obstacles **/
const int OBSTACLES_TOTAL         = 60,
		  OBSTACLES_START         = 3,  // Index obstacles start at
          OBSTACLES_END           = 62; // Index obstacles end at
// Coin blocks
const int COINBLOCKS_TOTAL        = 14,
		  COINBLOCKS_START        = 4,
		  COINBLOCKS_END          = 17;
const int COINBLOCKS_ROWONE_TOTAL = 8,  // Amount of blocks in first row
		  COINBLOCKS_ROWONE_START = 4,
		  COINBLOCKS_ROWONE_END   = 11;
const int COINBLOCKS_ROWTWO_TOTAL = 6,  // Amount of blocks in second row
		  COINBLOCKS_ROWTWO_START = 12,
		  COINBLOCKS_ROWTWO_END   = 17;
// Solid blocks
const int BLOCKS_TOTAL            = 22;
const int BLOCKS_START            = 18;
const int BLOCKS_END	          = 39;
// Pink blocks
const int PINKBLOCKS_TOTAL        = 9;
const int PINKBLOCKS_START        = 40;
const int PINKBLOCKS_END          = 49;
// Blue blocks
const int BLUEBLOCKS_TOTAL        = 2;
const int BLUEBLOCKS_START        = 50;
const int BLUEBLOCKS_END          = 51;
// Big pipes
const int PIPES_TOTAL		  = 4;
const int PIPES_START		  = 52;
const int PIPES_END			  = 55;
// Fire
const int FIRE_TOTAL			  = 3;
const int FIRE_START			  = 56;
const int FIRE_END				  = 61;

/** Constants for Goombas **/
const int GOOMBAS_TOTAL = 6,  // Total number of Goomba enemies
		  GOOMBAS_START = 63,
		  GOOMBAS_END   = 68;


/**********************/
/** SPRITE ANIMATION **/
/**********************/
// Mario
const int MARIO_WIDTH	     = 21,  // Width of each frame
		  MARIO_HEIGHT		 = 38,  // Height of each frame
		  MARIO_FRAMES_START = 1,   // First frame in sprite sheet
		  MARIO_FRAMES_END   = 8;   // Last frame in sprite sheet
const float MARIO_FPS	     = 10;  // Frames per second
// Goomba
const int GOOMBA_WIDTH		 = 30,
		  GOOMBA_HEIGHT		 = 26,
		  GOOMBA_COUNT		 = 6;
// Fire
const int FIRE_WIDTH		 = 125,
	      FIRE_HEIGHT		 = 59,
		  FIRE_COUNT		 = 16;
// Misc
const int LOOP				 = 1;  // Loop sprite animation


/************************************/
/** STARTING POSITIONS FOR SPRITES **/
/************************************/
// Sprite next to number of lives
const float MARIOLIVES_X  = 18,
			MARIOLIVES_Y  = 60;
// Sprite next to number of coins
const float DISPLAYCOIN_X = 20,
			DISPLAYCOIN_Y = 30;
// User controlled Mario
const float MARIO_X = 200,
			MARIO_Y = 445;
// Floor
const float FLOOR_X = 0,
			FLOOR_Y = 465;
// Fires
const float FIRE1_X  = 1000, FIRE2_X  = 1860, FIRE3_X  = 1930,
			FIRE4_X  = 1980, FIRE5_X  = 2030, FIRE6_X  = 2900,
			FIRE_Y  = FLOOR_Y - 50;
// Y positions for each row of blocks
const float BLOCK_ROWONE_Y = 350,
			BLOCK_ROWTWO_Y = 230;
// Pink block row 1/col 1
const float PINKBLOCK_COLONE_X = 3800,
		    PINKBLOCK_ROWONE_Y = FLOOR_Y - 48;
// Pink block row 2/col 2
const float PINKBLOCK_COLTWO_X = PINKBLOCK_COLONE_X + 48,
		    PINKBLOCK_ROWTWO_Y = PINKBLOCK_ROWONE_Y - 48;
// Pink block row 3/col 3
const float PINKBLOCK_COLTHREE_X = PINKBLOCK_COLTWO_X + 48,
			PINKBLOCK_ROWTHREE_Y = PINKBLOCK_ROWTWO_Y - 48;
// Pink block row 4/col 4
const float PINKBLOCK_COLFOUR_X = PINKBLOCK_COLTHREE_X + 48,
			PINKBLOCK_ROWFOUR_Y = PINKBLOCK_ROWTHREE_Y - 48;

/** Coin Blocks **/
// Row one
const float COINBLOCK1_ROWONE_X = 250,
			COINBLOCK2_ROWONE_X = 410,
			COINBLOCK3_ROWONE_X = 450,
			COINBLOCK4_ROWONE_X = 1450,
			COINBLOCK5_ROWONE_X = 1820,
			COINBLOCK6_ROWONE_X = 2160,
			COINBLOCK7_ROWONE_X = 2320,
			COINBLOCK8_ROWONE_X = 2520;
// Row two
const float COINBLOCK1_ROWTWO_X = 430,
			COINBLOCK2_ROWTWO_X = 1450,
			COINBLOCK3_ROWTWO_X = 2160,
			COINBLOCK4_ROWTWO_X = 2520,
			COINBLOCK5_ROWTWO_X = 3400,
			COINBLOCK6_ROWTWO_X = 3460;

/** Obstacle Blocks **/
const float BLOCK1_X  = 390,   BLOCK2_X = 430,   BLOCK3_X = 470, 
		    BLOCK4_X  = 1800,  BLOCK5_X = 1840,  BLOCK6_X = 1900,
			BLOCK7_X  = 1920,  BLOCK8_X = 1940,  BLOCK9_X = 1960,
			BLOCK10_X = 1980, BLOCK11_X = 2000, BLOCK12_X = 2020,
			BLOCK13_X = 2100, BLOCK14_X = 2120, BLOCK15_X = 2140,
			BLOCK16_X = 2300, BLOCK17_X = 2460, BLOCK18_X = 2580,
			BLOCK19_X = 3400, BLOCK20_X = 3420, BLOCK21_X = 3440,
			BLOCK22_X = 3460;
/** Pipes **/
const float PIPE1_X = 600, PIPE2_X = 800,
			PIPE3_X = 980, PIPE4_X = 1300,
			PIPE_Y = FLOOR_Y - 80;          // Y position of all pipes
/** Blue Blocks **/
const float BLUEBLOCK1_X = 2800,
			BLUEBLOCK2_X = 3000,
			BLUEBLOCK_Y  = FLOOR_Y - 94;
/** Goombas **/
const float GOOMBA1_X = 700, GOOMBA2_X  = 900, GOOMBA3_X  = 1200,
			GOOMBA4_X = 1440, GOOMBA5_X = 2200, GOOMBA6_X = 3050,
		    GOOMBA_Y  = FLOOR_Y - GOOMBA_HEIGHT;
/** Castle **/
const float CASTLE_X = 4350,
			CASTLE_Y = FLOOR_Y - 479;


/*************************/
/** CONSTANTS FOR TEXTS **/
/*************************/
const float COINS_TEXT_X        = 40,
			COINS_TEXT_Y        = 30,
			COINS_TEXT_SIZE     = 20,
			COINS_TEXT_END_X    = 460,
			COINS_TEXT_END_Y    = 420,
			COINS_TEXT_END_SIZE = 30;
const float LIVES_TEXT_X        = 41,
			LIVES_TEXT_Y        = 61,
			LIVES_TEXT_SIZE	    = 20;
const float GAMEOVERTEXT_X      = 0,
			GAMEOVERTEXT_Y      = 420,
			GAMEOVERTEXT_SIZE   = 30;
const int   BLACK			    = 0,
            SOLID	            = 255;


/****************/
/** VELOCITIES **/
/****************/
const float MARIO_VY     = -520;
const float GOOMBA_VX    = 100;
const float COINBLOCK_VY = 800;
const float COIN_VY      = 1000;
const float NO_VEL       = 0;


/*********************/
/** MUSIC AND SOUND **/
/*********************/
// Music Indexes
const int INTRO_MUSIC = 1,
		  GAME_MUSIC  = 2,
		  END_MUSIC    = 3;
// Sound Indexes
const int JUMP        = 1,
		  DIED        = 2,
		  STOMP       = 3,
		  GETCOIN     = 4;
// Sound Volume
const int VOL         = 40,
		  MAX		  = 100;


/*****************/
/** GAME STATES **/
/*****************/
const int START_SCREEN = 1,
		  INSTRUCTIONS = 2,
		  PLAY_GAME    = 3,
		  GAME_OVER    = 4;


/********************/
/** MISC CONSTANTS **/
/********************/
// World direction movement
const int WORLD_LEFT      = 1,
		  WORLD_RIGHT	  = 2;
// World speed
const int WORLD_INCREMENT = 2;
// Gravity of the game
const float GRAVITY_X     = 0,
		    GRAVITY_Y	  = 1000;
// Sprite Depth
const int BACKGROUND      = 1000;
// Visibility
const int SHOW		      = 1,
		  HIDE            = 0;
// How far the coin block
// and coins can go
const float BLOCK_LIMIT   = 10,
			COIN_LIMIT    = 70;
// For sprite flip
const int LEFT            = 1,
		  RIGHT           = 0,
		  VERT            = 0;
// Time constants for
// Goomba movement
const int LEFT_TIME       = 1,
		  RIGHT_TIME      = 2;
// Physics
const int STATIC		  = 1,
		  DYNAMIC         = 2,
		  KINETIC		  = 3;
const int NO_ROTATE       = 0;


/**********************/
/** GLOBAL VARIABLES **/
/**********************/
int g_gameState       = START_SCREEN;
int g_worldMove       = WORLD_LEFT;
bool g_updateRight    = true;
bool g_updateLeft     = true;
bool g_leftScreenHit  = true;
bool g_rightScreenHit = false;
bool g_coinBoxRowOne  = false;
bool g_coinBoxRowTwo  = true;
int g_coins           = 0;
int g_lives           = 3;


/*************/
/** VECTORS **/
/*************/
std::vector<int> g_obstacles;
std::vector<int> g_goombas;

// Begin app, called once at the start
void app::Begin( void )
{
	agk::SetWindowTitle("Super Mario by Anthony Mascia");
	agk::SetVirtualResolution(SCREEN_WIDTH, SCREEN_HEIGHT);

	/** Load Images **/
	agk::LoadImage(STARTSCREEN,       "resources/mariostartscreen.jpg");
	agk::LoadImage(INSTRUCTIONSCREEN, "resources/intructionscreen.jpg");
	agk::LoadImage(GAMEOVERSCREEN,    "resources/gameoverscreen.jpg");
	agk::LoadImage(MARIOLIVES,        "resources/mariolives.png");
	agk::LoadImage(MARIO,             "resources/mario.png");
	agk::LoadImage(BG,                "resources/background.jpg");
	agk::LoadImage(COINBLOCK,         "resources/randblock.png");
	agk::LoadImage(PIPE,              "resources/largepipe.png");
	agk::LoadImage(BLOCK,             "resources/block.png");
	agk::LoadImage(FLOOR,             "resources/floor.png");
	agk::LoadImage(PINKBLOCK,         "resources/pinkblock.png");
	agk::LoadImage(BLUEBLOCK,         "resources/blueblock.png");
	agk::LoadImage(BLANKBLOCK,        "resources/blankbox.png");
	agk::LoadImage(FIRE,              "resources/fire.png");
	agk::LoadImage(GOOMBA,            "resources/goomba.png");
	agk::LoadImage(CASTLE,            "resources/castle.png");
	agk::LoadImage(COIN,              "resources/coin.png");

	/** Load Sound and Music **/
	agk::LoadMusic(INTRO_MUSIC, "resources/intromusic.mp3");
	agk::LoadMusic(GAME_MUSIC,  "resources/gamemusic.mp3");
	agk::LoadMusic(END_MUSIC,   "resources/endmusic.mp3");
	agk::LoadSound(JUMP,	    "resources/jump.wav");
	agk::LoadSound(DIED,        "resources/killed.wav");
	agk::LoadSound(STOMP,       "resources/stomp.wav");
	agk::LoadSound(GETCOIN,     "resources/coin.wav");

	agk::CreateSprite(STARTSCREEN_INDEX, STARTSCREEN);
	agk::CreateSprite(INSTRUCTIONS_INDEX, INSTRUCTIONSCREEN);
	agk::CreateSprite(GAMEOVERSCREEN_INDEX, GAMEOVERSCREEN);
	agk::SetSpriteVisible(STARTSCREEN_INDEX, HIDE);
	agk::SetSpriteVisible(INSTRUCTIONS_INDEX, HIDE);
	agk::SetSpriteVisible(GAMEOVERSCREEN_INDEX, HIDE);

	agk::PlayMusic(INTRO_MUSIC);

}

// Main loop, called every frame
void app::Loop ( void )
{
	switch(g_gameState)
	{
		case START_SCREEN:
			generateStartScreen();
			break;
		case INSTRUCTIONS:
			generateInstructions();
			break;
		case PLAY_GAME:
			checkMusic();
			moveGoombas();
			checkObstacleCollision();
			checkGoombaCollision();
			updateMario();
			checkLeftBoundary();
			checkJump();
			checkCoinBoxCollision();
			checkFireCollision();
			checkGameover();
			break;
		case GAME_OVER:
			generateGameoverScreen();
			break;
		default:
			break;
	}


	agk::Sync();
}

// Called when the app ends
void app::End ( void )
{
}

// First function called tht displays the startscreen image
// to the user
void generateStartScreen()
{
	agk::SetSpriteVisible(STARTSCREEN_INDEX, SHOW);
	// When space pressed, show instruction screen
	if(agk::GetRawKeyPressed(AGK_KEY_SPACE))
	{
		agk::DeleteSprite(STARTSCREEN_INDEX);
		g_gameState = INSTRUCTIONS;
	}
}

// Function that displays the instructions screen
// to the user
void generateInstructions()
{
	agk::SetSpriteVisible(INSTRUCTIONS_INDEX, SHOW);
	// If space pressed, start game
	if(agk::GetRawKeyPressed(AGK_KEY_SPACE))
	{
		agk::DeleteSprite(INSTRUCTIONS_INDEX);
		generateWorld();
		g_gameState = PLAY_GAME;
	}
}

// Screen that is displayed after the game is over
// Displays how many coins the user got
void generateGameoverScreen()
{
	agk::SetSpriteVisible(GAMEOVERSCREEN_INDEX, SHOW);

	// Game over text
	agk::SetTextSize(GAMEOVER_TEXT, GAMEOVERTEXT_SIZE);
	agk::SetTextColor(GAMEOVER_TEXT, BLACK, BLACK, BLACK, SOLID);
	agk::SetTextPosition(GAMEOVER_TEXT,
						 GAMEOVERTEXT_X,
						 GAMEOVERTEXT_Y);
	agk::CreateText(GAMEOVER_TEXT, "You got this many coins: ");

	// Text that displays amount of coins
	agk::SetTextSize(DISPLAY_COINS, COINS_TEXT_END_SIZE);
	agk::SetTextColor(DISPLAY_COINS, BLACK, BLACK, BLACK, SOLID);
	agk::SetTextPosition(DISPLAY_COINS,
		                 COINS_TEXT_END_X,
						 COINS_TEXT_END_Y);
	agk::CreateText(DISPLAY_COINS, agk::Str(g_coins));
}

// Function that creates and clones all the sprites for the game 
void generateWorld()
{
	agk::StopMusic();                // Stop the intro music
	agk::SetMusicSystemVolume(MAX);
	agk::PlayMusic(GAME_MUSIC);      // Begin the game music


	/******************************/
	/** CREATE AND CLONE SPRITES **/
	/******************************/
	// Single Sprites with no clones
	agk::CreateSprite(MARIO_INDEX, MARIO);
	agk::CreateSprite(BG_INDEX, BG);
	agk::CreateSprite(FLOOR_INDEX, FLOOR);
	agk::CreateSprite(CASTLE_INDEX, CASTLE);
	agk::CreateSprite(GAME_COIN_INDEX, COIN);
	agk::CreateSprite(DISPLAY_COIN_INDEX, COIN);
	agk::CreateSprite(MARIOLIVES_INDEX, MARIOLIVES);

	// Create and clone coin blocks
	agk::CreateSprite(COINBLOCK1_ROWONE_INDEX, COINBLOCK);
	for(int i = COINBLOCK2_ROWONE_INDEX; i <= COINBLOCKS_END; i++)
	{
		agk::CloneSprite(i, COINBLOCK1_ROWONE_INDEX);
	}
	// Create and clone solid blocks
	agk::CreateSprite(BLOCK1_INDEX, BLOCK);
	for(int i = BLOCK2_INDEX; i <= BLOCKS_END; i++)
	{
		agk::CloneSprite(i, BLOCK1_INDEX);
	}
	// Create  and clone pipes
	agk::CreateSprite(PIPE1_INDEX, PIPE);
	for(int i = PIPE2_INDEX; i <= PIPES_END; i++)
	{
		agk::CloneSprite(i, PIPE1_INDEX);
	}
	// Create and clone pink blocks
	agk::CreateSprite(PINKBLOCK1_INDEX, PINKBLOCK);
	for(int i = PINKBLOCK2_INDEX; i <= PINKBLOCKS_END; i++)
	{
		agk::CloneSprite(i, PINKBLOCK1_INDEX);
	}
	// Create and clone blue blocks
	agk::CreateSprite(BLUEBLOCK1_INDEX, BLUEBLOCK);
	for(int i = BLUEBLOCK2_INDEX; i <= BLUEBLOCKS_END; i++)
	{
		agk::CloneSprite(i, BLUEBLOCK1_INDEX);
	}
	// Create and clone fire
	agk::CreateSprite(FIRE1_INDEX, FIRE);
	for(int i = FIRE2_INDEX; i <= FIRE_END; i++)
	{
		agk::CloneSprite(i, FIRE1_INDEX);
	}
	// Create and clone Goombas
	agk::CreateSprite(GOOMBA1_INDEX, GOOMBA);
	for(int i = GOOMBA2_INDEX; i <= GOOMBAS_END; i++)
	{
		agk::CloneSprite(i, GOOMBA1_INDEX);
	}

	/** Create Texts **/
	agk::CreateText(DISPLAY_COINS, agk::Str(g_coins));
	agk::CreateText(DISPLAY_LIVES, agk::Str(g_lives));
	
	/** Call function to set up sprites **/
	setupSprites();


	/*********************************/
	/** PHYSICS SETUP FOR THE WORLD **/
	/*********************************/
	agk::SetPhysicsGravity(GRAVITY_X, GRAVITY_Y);

	/**Set Physics On and Rotations **/
	// Mario
	agk::SetSpritePhysicsOn(MARIO_INDEX, DYNAMIC);
	agk::SetSpritePhysicsCanRotate(MARIO_INDEX, NO_ROTATE);
	// Game Coin
	agk::SetSpritePhysicsOn(GAME_COIN_INDEX, KINETIC);
	// Obstacles
	for(int i = 0; i < OBSTACLES_TOTAL; i++)
	{
		agk::SetSpritePhysicsOn(g_obstacles.at(i), KINETIC);
	}
	// Goombas
	for(int i = 0; i < GOOMBAS_TOTAL; i++)
	{
		agk::SetSpritePhysicsOn(g_goombas.at(i), DYNAMIC);
		agk::SetSpritePhysicsCanRotate(MARIO_INDEX, NO_ROTATE);
	}

}

// Function that puts sprites in their respective vectors,
// assigns sprites to their starting positions, and sets
// up sprite animations
void setupSprites()
{
	/*******************************/
	/** ASSIGN SPRITES TO VECTORS **/
	/*******************************/
	// Obstacle Vector
	for(int spriteNum = OBSTACLES_START;
		spriteNum <= OBSTACLES_END; spriteNum++)
	{
		g_obstacles.push_back(spriteNum);
	}
	// Goomba (enemy) Vector
	for(int spriteNum = GOOMBAS_START;
		spriteNum <= GOOMBAS_END; spriteNum++)
	{
		g_goombas.push_back(spriteNum);
	}


	/*************************/
	/** SET UP COIN DISPLAY **/
	/*************************/
	agk::SetSpritePosition(DISPLAY_COIN_INDEX,
						   DISPLAYCOIN_X,
						   DISPLAYCOIN_Y);
	agk::SetTextSize(DISPLAY_COINS, COINS_TEXT_SIZE);
	agk::SetTextColor(DISPLAY_COINS, BLACK, BLACK, BLACK, SOLID);
	agk::SetTextPosition(DISPLAY_COINS, COINS_TEXT_X, COINS_TEXT_Y);


	/*************************/
	/** SET UP LIFE DISPLAY **/
	/*************************/
	agk::SetSpritePosition(MARIOLIVES_INDEX,
		                   MARIOLIVES_X,
						   MARIOLIVES_Y);
	agk::SetTextSize(DISPLAY_LIVES, LIVES_TEXT_SIZE);
	agk::SetTextColor(DISPLAY_LIVES, BLACK, BLACK, BLACK, SOLID);
	agk::SetTextPosition(DISPLAY_LIVES, LIVES_TEXT_X, LIVES_TEXT_Y);


	/********************************************/
	/** SET BEGINNING POSITIONS OF ALL SPRITES **/
	/********************************************/
	/** Mario and Floor **/
	agk::SetSpritePosition(MARIO_INDEX, MARIO_X, MARIO_Y);
	agk::SetSpritePosition(FLOOR_INDEX, FLOOR_X, FLOOR_Y);
	
	/** Coin Blocks **/
	// First row
	agk::SetSpritePosition(COINBLOCK1_ROWONE_INDEX,
					       COINBLOCK1_ROWONE_X,
						   BLOCK_ROWONE_Y);
	agk::SetSpritePosition(COINBLOCK2_ROWONE_INDEX,
		                   COINBLOCK2_ROWONE_X,
		                   BLOCK_ROWONE_Y);
	agk::SetSpritePosition(COINBLOCK3_ROWONE_INDEX,
		                   COINBLOCK3_ROWONE_X,
		                   BLOCK_ROWONE_Y);
	agk::SetSpritePosition(COINBLOCK4_ROWONE_INDEX,
		                   COINBLOCK4_ROWONE_X,
		                   BLOCK_ROWONE_Y);
	agk::SetSpritePosition(COINBLOCK5_ROWONE_INDEX,
						   COINBLOCK5_ROWONE_X,
						   BLOCK_ROWONE_Y);
	agk::SetSpritePosition(COINBLOCK6_ROWONE_INDEX,
						   COINBLOCK6_ROWONE_X,
						   BLOCK_ROWONE_Y);
	agk::SetSpritePosition(COINBLOCK7_ROWONE_INDEX,
		                   COINBLOCK7_ROWONE_X,
						   BLOCK_ROWONE_Y);
	agk::SetSpritePosition(COINBLOCK8_ROWONE_INDEX,
		                   COINBLOCK8_ROWONE_X,
						   BLOCK_ROWONE_Y);
	// Second row
	agk::SetSpritePosition(COINBLOCK1_ROWTWO_INDEX,
					       COINBLOCK1_ROWTWO_X,
						   BLOCK_ROWTWO_Y);
	agk::SetSpritePosition(COINBLOCK2_ROWTWO_INDEX,
					       COINBLOCK2_ROWTWO_X,
						   BLOCK_ROWTWO_Y);
	agk::SetSpritePosition(COINBLOCK3_ROWTWO_INDEX,
					       COINBLOCK3_ROWTWO_X,
						   BLOCK_ROWTWO_Y);
	agk::SetSpritePosition(COINBLOCK4_ROWTWO_INDEX,
					       COINBLOCK4_ROWTWO_X,
						   BLOCK_ROWTWO_Y);
	agk::SetSpritePosition(COINBLOCK5_ROWTWO_INDEX,
					       COINBLOCK5_ROWTWO_X,
						   BLOCK_ROWTWO_Y);
	agk::SetSpritePosition(COINBLOCK6_ROWTWO_INDEX,
					       COINBLOCK6_ROWTWO_X,
						   BLOCK_ROWTWO_Y);

	/** Obstacle Blocks **/
	agk::SetSpritePosition(BLOCK1_INDEX, BLOCK1_X, BLOCK_ROWONE_Y);
	agk::SetSpritePosition(BLOCK2_INDEX, BLOCK2_X, BLOCK_ROWONE_Y);
	agk::SetSpritePosition(BLOCK3_INDEX, BLOCK3_X, BLOCK_ROWONE_Y);
	agk::SetSpritePosition(BLOCK4_INDEX, BLOCK4_X, BLOCK_ROWONE_Y);
	agk::SetSpritePosition(BLOCK5_INDEX, BLOCK5_X, BLOCK_ROWONE_Y);
	agk::SetSpritePosition(BLOCK6_INDEX, BLOCK6_X, BLOCK_ROWTWO_Y);
	agk::SetSpritePosition(BLOCK7_INDEX, BLOCK7_X, BLOCK_ROWTWO_Y);
	agk::SetSpritePosition(BLOCK8_INDEX, BLOCK8_X, BLOCK_ROWTWO_Y);
	agk::SetSpritePosition(BLOCK9_INDEX, BLOCK9_X, BLOCK_ROWTWO_Y);
	agk::SetSpritePosition(BLOCK10_INDEX, BLOCK10_X, BLOCK_ROWTWO_Y);
	agk::SetSpritePosition(BLOCK11_INDEX, BLOCK11_X, BLOCK_ROWTWO_Y);
	agk::SetSpritePosition(BLOCK12_INDEX, BLOCK12_X, BLOCK_ROWTWO_Y);
	agk::SetSpritePosition(BLOCK13_INDEX, BLOCK13_X, BLOCK_ROWTWO_Y);
	agk::SetSpritePosition(BLOCK14_INDEX, BLOCK14_X, BLOCK_ROWTWO_Y);
	agk::SetSpritePosition(BLOCK15_INDEX, BLOCK15_X, BLOCK_ROWTWO_Y);
	agk::SetSpritePosition(BLOCK16_INDEX, BLOCK16_X, BLOCK_ROWONE_Y);
	agk::SetSpritePosition(BLOCK17_INDEX, BLOCK17_X, BLOCK_ROWONE_Y);
	agk::SetSpritePosition(BLOCK18_INDEX, BLOCK18_X, BLOCK_ROWONE_Y);
	agk::SetSpritePosition(BLOCK19_INDEX, BLOCK19_X, BLOCK_ROWONE_Y);
	agk::SetSpritePosition(BLOCK20_INDEX, BLOCK20_X, BLOCK_ROWONE_Y);
	agk::SetSpritePosition(BLOCK21_INDEX, BLOCK21_X, BLOCK_ROWONE_Y);
	agk::SetSpritePosition(BLOCK22_INDEX, BLOCK22_X, BLOCK_ROWONE_Y);

	/** Pipes **/
	agk::SetSpritePosition(PIPE1_INDEX, PIPE1_X, PIPE_Y);
	agk::SetSpritePosition(PIPE2_INDEX, PIPE2_X, PIPE_Y);
	agk::SetSpritePosition(PIPE3_INDEX, PIPE3_X, PIPE_Y);
	agk::SetSpritePosition(PIPE4_INDEX, PIPE4_X, PIPE_Y);

	/** Fire **/
	agk::SetSpritePosition(FIRE1_INDEX, FIRE1_X, FIRE_Y);
	agk::SetSpritePosition(FIRE2_INDEX, FIRE2_X, FIRE_Y);
	agk::SetSpritePosition(FIRE3_INDEX, FIRE3_X, FIRE_Y);
	agk::SetSpritePosition(FIRE4_INDEX, FIRE4_X, FIRE_Y);
	agk::SetSpritePosition(FIRE5_INDEX, FIRE5_X, FIRE_Y);
	agk::SetSpritePosition(FIRE6_INDEX, FIRE6_X, FIRE_Y);

	/** Pink Blocks **/
	agk::SetSpritePosition(PINKBLOCK1_INDEX, PINKBLOCK_COLONE_X,
					       PINKBLOCK_ROWONE_Y);
	agk::SetSpritePosition(PINKBLOCK2_INDEX, PINKBLOCK_COLTWO_X,
		                   PINKBLOCK_ROWONE_Y);
	agk::SetSpritePosition(PINKBLOCK3_INDEX, PINKBLOCK_COLTHREE_X,
		                   PINKBLOCK_ROWONE_Y);
	agk::SetSpritePosition(PINKBLOCK4_INDEX, PINKBLOCK_COLFOUR_X,
		                   PINKBLOCK_ROWONE_Y);
	agk::SetSpritePosition(PINKBLOCK5_INDEX, PINKBLOCK_COLTWO_X,
		                   PINKBLOCK_ROWTWO_Y);
	agk::SetSpritePosition(PINKBLOCK6_INDEX, PINKBLOCK_COLTHREE_X,
		                   PINKBLOCK_ROWTWO_Y);
	agk::SetSpritePosition(PINKBLOCK7_INDEX, PINKBLOCK_COLFOUR_X,
		                   PINKBLOCK_ROWTWO_Y);
	agk::SetSpritePosition(PINKBLOCK8_INDEX, PINKBLOCK_COLTHREE_X,
		                   PINKBLOCK_ROWTHREE_Y);
	agk::SetSpritePosition(PINKBLOCK9_INDEX, PINKBLOCK_COLFOUR_X,
		                   PINKBLOCK_ROWTHREE_Y);
	agk::SetSpritePosition(PINKBLOCK10_INDEX, PINKBLOCK_COLFOUR_X,
		                   PINKBLOCK_ROWFOUR_Y);

	/** Blue Blocks **/
	agk::SetSpritePosition(BLUEBLOCK1_INDEX, BLUEBLOCK1_X, BLUEBLOCK_Y);
	agk::SetSpritePosition(BLUEBLOCK2_INDEX, BLUEBLOCK2_X, BLUEBLOCK_Y);

	/** Goombas **/
	agk::SetSpritePosition(GOOMBA1_INDEX, GOOMBA1_X, GOOMBA_Y);
	agk::SetSpritePosition(GOOMBA2_INDEX, GOOMBA2_X, GOOMBA_Y);
	agk::SetSpritePosition(GOOMBA3_INDEX, GOOMBA3_X, GOOMBA_Y);
	agk::SetSpritePosition(GOOMBA4_INDEX, GOOMBA4_X, GOOMBA_Y);
	agk::SetSpritePosition(GOOMBA5_INDEX, GOOMBA5_X, GOOMBA_Y);
	agk::SetSpritePosition(GOOMBA6_INDEX, GOOMBA6_X, GOOMBA_Y);

	/** Castle **/
	agk::SetSpritePosition(CASTLE_INDEX, CASTLE_X, CASTLE_Y);


	/***************************/
	/** SET SPRITE VISIBILITY **/
	/***************************/
	agk::SetSpriteVisible(GAME_COIN_INDEX, HIDE);

	
	/***********************/
	/** Set sprite depths **/
	/***********************/
	agk::SetSpriteDepth(BG_INDEX, BACKGROUND);


	/******************************/
	/** SET UP SPRITE ANIMATIONS **/
	/******************************/
	// Mario
	agk::SetSpriteAnimation(MARIO_INDEX, MARIO_WIDTH,
							MARIO_HEIGHT, MARIO_FRAMES_END);
	//agk::PlaySprite(MARIO_INDEX);
	// Goombas
	for(int i = GOOMBAS_START; i <= GOOMBAS_END; i++)
	{
		agk::SetSpriteAnimation(i, GOOMBA_WIDTH,
								GOOMBA_HEIGHT, GOOMBA_COUNT);
		agk::PlaySprite(i);
	}
	// Fire
	for(int i = FIRE_START; i <= FIRE_END; i++)
	{
		agk::SetSpriteAnimation(i, FIRE_WIDTH,
								FIRE_HEIGHT, FIRE_COUNT);
		agk::PlaySprite(i);
	}
}

// Function that moves mario according to which key user presses
void updateMario()
{
	// If user is holding down the right arrow key, is allowed
	// to move right, and is not at the right edge of the map,
	// then move map to the left
	if(agk::GetRawKeyState(AGK_KEY_RIGHT) && g_updateRight == true &&
	   g_rightScreenHit == false)
	{
		g_worldMove = WORLD_LEFT;
		agk::SetSpriteFlip(MARIO_INDEX, RIGHT, VERT);
		// Used to loop sprite when key held down
		if(!agk::GetSpritePlaying(MARIO_INDEX))
		{
			agk::PlaySprite (MARIO_INDEX, MARIO_FPS, LOOP,
							 MARIO_FRAMES_START, MARIO_FRAMES_END);
		}
		updateWorld();
	}
	// If user is holding down the left arrow key and is allowed
	// to move left, and is not at the left edge of the map,
	// then move map to the right
	else if(agk::GetRawKeyState(AGK_KEY_LEFT) && g_updateLeft == true &&
	        g_leftScreenHit == false)
	{
		g_worldMove = WORLD_RIGHT;
		agk::SetSpriteFlip(MARIO_INDEX, LEFT, VERT);
		// Used to loop sprite animation when key held down
		if(!agk::GetSpritePlaying(MARIO_INDEX))
		{
			agk::PlaySprite (MARIO_INDEX, MARIO_FPS, LOOP,
							 MARIO_FRAMES_START, MARIO_FRAMES_END);
		}
		updateWorld();
	}
	else
	{
		// Reset sprite to starting position and stop it from playing
		agk::SetSpriteFrame(MARIO_INDEX, MARIO_FRAMES_START);
		agk::StopSprite(MARIO_INDEX);
	}
}

// Function that moves all sprites left or right to simulate movement
// when user holds down the left or the right arrow key
void updateWorld()
{
	for(int i = 0; i < OBSTACLES_TOTAL; i++)
	{
		// If user is holding down the right key, move sprites left
		if(g_worldMove == WORLD_LEFT)
		{
			agk::SetSpriteX(g_obstacles.at(i),
				            agk::GetSpriteX(g_obstacles.at(i)) 
							- WORLD_INCREMENT);
		}
		// If user is holding down the left key, move sprites right
		else if(g_worldMove == WORLD_RIGHT)
		{
			agk::SetSpriteX(g_obstacles.at(i), 
				            agk::GetSpriteX(g_obstacles.at(i)) 
							+ WORLD_INCREMENT);
		}
	}

	for(int i = 0; i < GOOMBAS_TOTAL; i++)
	{
		// If user is holding down the right key, move sprites left
		if(g_worldMove == WORLD_LEFT)
		{
			agk::SetSpriteX(g_goombas.at(i), 
							agk::GetSpriteX(g_goombas.at(i))
							- WORLD_INCREMENT);
		}
		// If user is holding down the left key, move sprites right
		else if(g_worldMove == WORLD_RIGHT)
		{
			agk::SetSpriteX(g_goombas.at(i), 
				            agk::GetSpriteX(g_goombas.at(i)) 
							+ WORLD_INCREMENT);
		}
	}
	// Update background
	if(g_worldMove == WORLD_LEFT)
	{
		agk::SetSpriteX(BG_INDEX, 
					    agk::GetSpriteX(BG_INDEX) - WORLD_INCREMENT);
	}
	else if(g_worldMove == WORLD_RIGHT)
	{
		agk::SetSpriteX(BG_INDEX, 
					    agk::GetSpriteX(BG_INDEX) + WORLD_INCREMENT);
	}
}

// Function that checks if user wants Mario to jump by
// pressing the up arrow key
void checkJump()
{
	// Constantly check if Mario is on a jumpable sprite
	for(int i = 0; i < OBSTACLES_TOTAL; i++)
	{
		// If he is and user presses up, make him jump
		// by setting his y velocity in a negative direction
		if(agk::GetRawKeyPressed(AGK_KEY_UP) &&
		   agk::GetPhysicsCollision(MARIO_INDEX, g_obstacles.at(i)))
		{
			agk::SetPhysicsGravity(GRAVITY_X, GRAVITY_Y);
			agk::SetSpritePhysicsVelocity(MARIO_INDEX, NO_VEL, MARIO_VY);
			agk::PlaySound(JUMP, VOL);
		}
	}
}

// Checks to see is user collides with either the right or left sides
// of an obstacle which will stop the user from moving
void checkObstacleCollision()
{	
	// Go through all obstacles to check if Mario comes
	// in contact with any obstacles
	for(int i = 0; i < OBSTACLES_TOTAL; i++)
	{
		// If Mario collides with an obstacle
		if(agk::GetSpriteCollision(MARIO_INDEX, g_obstacles.at(i)))
		{
			// Collision detection to see if Mario collides with left
			// side of the obstacle
			if(collideRight(MARIO_INDEX, g_obstacles.at(i)))
			{
				// If true, make it so Mario cannot move right until
				// he gets passed the obstacle
				g_updateRight = false;
			}
			// Collision detection to see if Mario collides with right
			// side of the obstacle
			else if(collideLeft(MARIO_INDEX, g_obstacles.at(i)))
			{
				// If true, make it so Mario cannot move left until
				// he gets passed the obstacle
				g_updateLeft = false;
			}
			// If Mario does no collide with either the left or right
			// side of the obstacle, allow user to move him left or right
			else
			{
				g_updateRight = true;
				g_updateLeft  = true;
			}
		}
	}
}

// Function that constantly checks if Mario has collided
// with a Goomba
void checkGoombaCollision()
{
	for(int i = 0; i < GOOMBAS_TOTAL; i++)
	{
		// If Mario jumps on top of a Goomba, delete the
		// Goomba sprite, play a sound, and set his velocity
		// in the negative y direction to simulate him bouncing
		// off the Goomba
		if(collideTop(MARIO_INDEX, g_goombas.at(i)))
		{
			agk::PlaySound(STOMP, VOL);
			agk::DeleteSprite(g_goombas.at(i));
			agk::SetSpritePhysicsVelocity(MARIO_INDEX, NO_VEL, MARIO_VY);
		}
		// If Mario collides with the right or left side of the
		// Goomba: lose a life, play the death sound, and start
		// Mario back at the beginning of the map
		else if(collideRight(MARIO_INDEX, g_goombas.at(i)) ||
			    collideLeft(MARIO_INDEX, g_goombas.at(i)))
		{
			g_lives--;
			updateLives();
			agk::PlaySound(DIED, VOL);
			setupSprites();  // Function that resets the map
		}
	}
}

// Function that checks whether to see if the music is playing
// or not. If it is not playing, then resume it.
// Instances where the music will not be playing is when the
// "death" sound is played, and the music will resume when
// that sound is over
void checkMusic()
{
	if(agk::GetSoundsPlaying(DIED))
		agk::PauseMusic();
	else
	{
		if(!agk::GetSoundsPlaying(DIED))
			agk::ResumeMusic();
	}
}

// Checks whether user is at the left edge of the screen
// so he does not walk off the floor sprite
void checkLeftBoundary()
{
	float floorX = agk::GetSpriteX(FLOOR_INDEX);

	if(floorX >= FLOOR_X)
		g_leftScreenHit = true;
	else
		g_leftScreenHit = false;
}

// Function that constantly moves Goombas left and right
// using the timer. This will move the Goomba left for a
// second then move the Goomba right for a second.
// This will keep repeating until Goomba has died, or user
// has won or died
void moveGoombas()
{
	for(int i = 0; i < GOOMBAS_TOTAL; i++)
	{
		// If the timer is less than one, set Goomba's
		// x velocity in negative direction so he moves left
		if(agk::GetSeconds() <= LEFT_TIME)
		{
			agk::SetSpriteFlip(g_goombas.at(i), LEFT, VERT);
			agk::SetSpritePhysicsVelocity(g_goombas.at(i),
									      -GOOMBA_VX,
										  NO_VEL);
		}
		// If the timer is greater than 1, but less than 2,
		// set Goombas x direction in the positive direction
		// to simulate right movement
		else if(agk::GetSeconds() > LEFT_TIME &&
			    agk::GetSeconds() <= RIGHT_TIME)
		{
			agk::SetSpriteFlip(g_goombas.at(i), RIGHT, VERT);
			agk::SetSpritePhysicsVelocity(g_goombas.at(i),
				                          GOOMBA_VX,
										  NO_VEL);
		}
		// After Goomba has moved left then right, reset timer
		// so it continually does so
		else
			agk::ResetTimer();
	}
}

// Function that checks if the user has collided
// with a fire sprite
void checkFireCollision()
{
	for(int i = FIRE_START; i <= FIRE_END; i++)
	{
		// If Mario collides with a fire sprite,
		// kill him, and reset him to the start position
		if(agk::GetSpriteCollision(MARIO_INDEX, i))
		{
			agk::PlaySound(DIED, VOL);
			g_lives--;
			updateLives();
			setupSprites();
		}
	}
}

// Checks whether to see Mario has hit a coin box with his head
void checkCoinBoxCollision()
{
	/** Collision detection for all coin blocks in the first row **/
	for(int coinBlockRowOne = COINBLOCKS_ROWONE_START;
		coinBlockRowOne <= COINBLOCKS_ROWONE_END; coinBlockRowOne++)
	{
		float coinBlockRowOneY = agk::GetSpriteY(coinBlockRowOne);
		float coinBlockRowOneX = agk::GetSpriteX(coinBlockRowOne);

		// If Mario collides with the bottom of the coin block
		// and the coin block has not already been hit before
		if(collideBottom(MARIO_INDEX, coinBlockRowOne) &&
		   agk::GetSpriteImageID(coinBlockRowOne) != BLANKBLOCK)
		{
			agk::PlaySound(GETCOIN, VOL);
			// Increment coins by 1
			g_coins++;
			// Update coins gotten on the screen
			updateCoins();
			// Show the coin that comes out of the block
			agk::SetSpriteVisible(GAME_COIN_INDEX, SHOW);
			// Make sure the coin is positioned right above the block
			agk::SetSpritePosition(GAME_COIN_INDEX, coinBlockRowOneX,
							      coinBlockRowOneY -
								  agk::GetSpriteHeight(GAME_COIN_INDEX));
			// Set the velocity of the coin in the negative
			// y direction to simulate it shooting up
			agk::SetSpritePhysicsVelocity(GAME_COIN_INDEX, 
										  NO_VEL,
										  -COIN_VY);
			// Set the velocity of the block in the negative
			// y direction to simulate it shooting up
			agk::SetSpritePhysicsVelocity(coinBlockRowOne,
										  NO_VEL,
										  -COINBLOCK_VY);
			// Change the image of the coin block to a blank block
			// so user already know he got the coin from that block
			agk::SetSpriteImage(coinBlockRowOne, BLANKBLOCK);
		}
		// Function to return coin block and hide coin
		moveBlock(coinBlockRowOne, coinBlockRowOneY, BLOCK_ROWONE_Y);
	}

	/** Collision detection for all coin blocks in the second row **/
	// Same as the previous for loop for the first row
	for(int coinBlockRowTwo = COINBLOCKS_ROWTWO_START; 
		coinBlockRowTwo <= COINBLOCKS_ROWTWO_END; coinBlockRowTwo++)
	{
		float coinBlockRowTwoY = agk::GetSpriteY(coinBlockRowTwo);
		float coinBlockRowTwoX = agk::GetSpriteX(coinBlockRowTwo);

		if(collideBottom(MARIO_INDEX, coinBlockRowTwo) 
		   && agk::GetSpriteImageID(coinBlockRowTwo) != BLANKBLOCK)
		{
			agk::PlaySound(GETCOIN, VOL);
			g_coins++;
			updateCoins();
			agk::SetSpriteVisible(GAME_COIN_INDEX, SHOW);
			agk::SetSpritePosition(GAME_COIN_INDEX, coinBlockRowTwoX,
								  coinBlockRowTwoY -
								  agk::GetSpriteHeight(GAME_COIN_INDEX));
			agk::SetSpritePhysicsVelocity(GAME_COIN_INDEX, 
				                          NO_VEL,
										  -COIN_VY);
			agk::SetSpritePhysicsVelocity(coinBlockRowTwo,
				                          NO_VEL,
										  -COINBLOCK_VY);
			agk::SetSpriteImage(coinBlockRowTwo, BLANKBLOCK);
		}
		moveBlock(coinBlockRowTwo, coinBlockRowTwoY, BLOCK_ROWTWO_Y);
	}	
}

// Function that updates the coins to the user
// on the screen by deleting and recreating the
// text
void updateCoins()
{
	agk::DeleteText(DISPLAY_COINS);
	agk::CreateText(DISPLAY_COINS, agk::Str(g_coins));
	agk::SetTextSize(DISPLAY_COINS, COINS_TEXT_SIZE);
	agk::SetTextColor(DISPLAY_COINS, BLACK, BLACK, BLACK, SOLID);
	agk::SetTextPosition(DISPLAY_COINS, COINS_TEXT_X, COINS_TEXT_Y);
}

// Function that updates the lives to the user
// on the screen by deleting and recreating the
// text
void updateLives()
{
	agk::DeleteText(DISPLAY_LIVES);
	agk::CreateText(DISPLAY_LIVES, agk::Str(g_lives));
	agk::SetTextSize(DISPLAY_LIVES, LIVES_TEXT_SIZE);
	agk::SetTextColor(DISPLAY_LIVES, BLACK, BLACK, BLACK, SOLID);
	agk::SetTextPosition(DISPLAY_LIVES, LIVES_TEXT_X, LIVES_TEXT_Y);
}

// Function that brings the coin blocks back down after
// being hit and having their velocity changed in a negative
// y direction
// Also hides coin that pops out after coin block is hit
void moveBlock(int index, float blockY, const float STARTPOSITION)
{
	float coinY = agk::GetSpriteY(GAME_COIN_INDEX);

	// If the y position of the coin block reaches
	// 10 pixels above its starting position, 
	// bring the box back down
	if(blockY <= STARTPOSITION - BLOCK_LIMIT)
		agk::SetSpritePhysicsVelocity(index, NO_VEL, COINBLOCK_VY);
	// When the block reaches one pixel above its starting position
	// kill the blocks velocity and reset the block back at its
	// starting position
	else if(blockY >= STARTPOSITION + 1)
	{
		agk::SetSpritePhysicsVelocity(index, NO_VEL, NO_VEL);
		agk::SetSpriteY(index, STARTPOSITION);
	}
	// Make the coin disappear after it has reached
	// 70 pixels above its starting position
	if(coinY <= STARTPOSITION - COIN_LIMIT)
		agk::SetSpriteVisible(GAME_COIN_INDEX, HIDE);
}

// Checks if the necessary conditions for the game to
// be over are met. If they are, this changes the
// gamestate to game over after deleting all the
// sprites in the map
void checkGameover()
{
	// Game is over when user reaches the castle
	// or has no more lives
	if(agk::GetSpriteCollision(MARIO_INDEX, CASTLE_INDEX) ||
	   g_lives <= 0)
	{
		g_gameState = GAME_OVER;
		wipeAllSprites();
		agk::StopMusic();
		agk::PlayMusic(END_MUSIC);
	}
}

// Function that deletes all sprites in world map
// Also deletes texts
void wipeAllSprites()
{
	for(int i = SPRITES_START; i <= SPRITES_END; i++)
	{
		agk::DeleteSprite(i);
	}
	agk::DeleteText(DISPLAY_LIVES);
	agk::DeleteText(DISPLAY_COINS);
}

// Collision detection to see if Mario collides with right
// side of the obstacle
bool collideRight(int collidingSprite, int collidedSprite)
{
	float collidingSpriteRightX  = agk::GetSpriteX(collidingSprite) +
								   agk::GetSpriteWidth(collidingSprite);
	float collidedSpriteLeftX   = agk::GetSpriteX(collidedSprite);

	if(agk::GetSpriteCollision(collidingSprite, collidedSprite))
	{

		// Collision detection to see if Mario collides with right
		// side of the obstacle
		if(collidingSpriteRightX + 1 >= collidedSpriteLeftX &&
		   collidingSpriteRightX <= collidedSpriteLeftX)
		{
			return true;
		}
	}
	
	return false;
}

// Collision detection to see if Mario collides with left
// side of the obstacle
bool collideLeft(int collidingSprite, int collidedSprite)
{
	float collidingSpriteLeftX  = agk::GetSpriteX(collidingSprite);
	float collidedSpriteLeftX   = agk::GetSpriteX(collidedSprite) +
								  agk::GetSpriteWidth(collidedSprite);

	if(agk::GetPhysicsCollision(collidingSprite, collidedSprite))
	{

		// Collision detection to see if Mario collides with right
		// side of the obstacle
		if(collidingSpriteLeftX - 1 <= collidedSpriteLeftX &&
		   collidingSpriteLeftX >= collidedSpriteLeftX)
		{
			return true;
		}
	}
	
	return false;
}

// Collision detection to see if Mario collides with bottom
// side of the obstacle
bool collideTop(int collidingSprite, int collidedSprite)
{
	float collidingSpriteBottomY  = agk::GetSpriteY(collidingSprite) +
								   agk::GetSpriteHeight(collidingSprite);
	float collidedSpriteTopY      = agk::GetSpriteY(collidedSprite);

	if(agk::GetPhysicsCollision(collidingSprite, collidedSprite))
	{
		// Collision detection to see if Mario collides with bottom
		// side of the obstacle
		if(collidingSpriteBottomY - 1 <= collidedSpriteTopY)
		{
			return true;
		}
	}
	
	return false;
}

// Collision detection to see if Mario collides with top
// side of the obstacle
bool collideBottom(int collidingSprite, int collidedSprite)
{
	float collidingSpriteTopY   = agk::GetSpriteY(collidingSprite);
	float collidedSpriteBottomY = agk::GetSpriteY(collidedSprite) +
								  agk::GetSpriteHeight(collidedSprite);

	if(agk::GetPhysicsCollision(collidingSprite, collidedSprite))
	{
		// Collision detection to see if Mario collides with top
		// side of the obstacle
		if(collidingSpriteTopY - 1 <= collidedSpriteBottomY &&
		   collidingSpriteTopY >= collidedSpriteBottomY)
		{
			return true;
		}
	}
	
	return false;
}
