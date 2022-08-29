#pragma once
#define SCREEN_WIDTH 1600				
#define SCREEN_HEIGHT 900

#define MENU_BACKGROUND_FILE_PATH "Ressources/image/batailleSpatial.jpg"
#define GAME_BACKGROUND_FILE_PATH "Ressources/image/gameBackground.jpg"
#define SPLASH_STATE_BACKGROUND_FILEPATH "Ressources/image/batailleSpatial.jpg"

#define GAME_FONTS "Ressources/font/Wallpoet-Regular.ttf"

#define FICHIER_SCORE "partiesGagnees.txt"

#define NOMBRE_LIGNE_JEU 5
#define NOMBRE_COLONNE_JEU 5
#define DISTANCE_ENTRE_PLANETE 80
#define LOGO_STATE_SHOW_TIME 5.0

#define COULEUR_DE_COMMENCEMENT Color::Cyan
#define COULEUR_PLANETE_INHABITABLE Color::Red
#define COULEUR_PLANETE_HABITABLE Color::Yellow
#define COULEUR_PLANETE_PARADISIAQUE Color::Green

#define SOUND_IMPERIAL_MARCH_FILEPATH "Ressources/sound/Star Wars - The Imperial March.wav"
#define SOUND_FUTURE_MANKIND_FILEPATH "Ressources/sound/The Future of Mankind.wav"
#define SOUND_HOPE_LOUNGE_FILEPATH "Ressources/sound/The Hope Lounge.wav"
#define SOUND_EXPLOSION_FILEPATH "Ressources/sound/explosion.wav"
#define SOUND_DEES_FILEPATH "Ressources/sound/dees.wav"


enum gameStates {
	ready,
	playing,
	gameOver
};