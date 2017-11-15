#include "control.hpp"

static void initLocalMediaControl();
static void analyseMediaControl(media_control_t *);

// Lokaler Datenhalter
static media_control_t local_media_control;



void *control (void* val){
	control_daten_intern *control_daten=(control_daten_intern *) val;
  
	bool my_new; //true, wenn sich daten geändert haben. Wird wieder auf falsegesetzt, wenn die neue Daten an die View übermittelt wurden.
	int kmh = control_daten->kmh; //Zwischenspeicherung, der zuletzt an View gesendeten Daten
	int rpm = control_daten->rpm; //Zwischenspeicherung, der zuletzt an View gesendeten Daten
	int gear = control_daten->gear; //Zwischenspeicherung, der zuletzt an View gesendeten Daten
	unsigned int tank = control_daten->tank; //Zwischenspeicherung, der zuletzt an View gesendeten Daten
	int temp = control_daten->temp; //Zwischenspeicherung, der zuletzt an View gesendeten Daten
	
	initLocalMediaControl();
	while(1){
    
    
		if(control_daten->my_new == true){ //Überprüfung, ob es im Model neue Daten gibt
      
		if(kmh != control_daten->kmh){ //Prüfen, ob sich die Geschwindigkeit geändet hat.
		std::cout << "? 0 " << control_daten->kmh*3 << std::endl; //Geschwindigkeitswert wird mit 3 multipliziert, da die Werte aus der Motorsimulation als Hexwerte für das Originaldisplay berechnet werden.
		kmh = control_daten->kmh;
	
		}
		if( rpm != control_daten->rpm){ //Prüfen, ob sich die Drehzahl geändet hat.
		std::cout << "? 1 " << control_daten->rpm*60 << std::endl; //Drehzahlswert wird mit 60 multipliziert, da die Werte aus der Motorsimulation als Hexwerte für das Originaldisplay berechnet werden.
		rpm = control_daten->rpm;
	
		}
		if(control_daten->x == true){ //Prüfen, ob Button "x" (Blinker linbks) betätig wurde.
			std::cout << "? 2 " << control_daten->x << std::endl;
			control_daten->x = false; //Button zuzücksetzen
		}
		if(control_daten->b == true){ //Prüfen, ob Button "b" (Blinker rechts) betätig wurde.
			std::cout << "? 3 " << control_daten->b << std::endl;
			control_daten->b = false; //Button zuzücksetzen
		}
		if(control_daten->up == true){ //Prüfen, ob Button "up" (Menu up) betätig wurde.
			std::cout << "? 4 " << control_daten->up << std::endl;
			control_daten->up = false; //Button zuzücksetzen
	
		}
		if(control_daten->down == true){ //Prüfen, ob Button "down" (Menu down) betätig wurde.
			std::cout << "? 5 " << control_daten->down << std::endl;
			control_daten->down = false; //Button zuzücksetzen
	
		}
		if(control_daten->right == true){ //Prüfen, ob Button "right" (left side up / Phonemenu) betätig wurde.
			std::cout << "? 6 " << control_daten->right << std::endl;
			control_daten->right  = false; //Button zuzücksetzen
		}
      
		if(control_daten->left == true){ //Prüfen, ob Button "left" (left side down  / Phonemenu) betätig wurde.
			std::cout << "? 7 " << control_daten->left << std::endl;
			control_daten->left = false; //Button zuzücksetzen	
		}
		if(gear != control_daten->gear){ //Prüfen, ob sich der Gang bzw. Fahrmodus geändet hat.
			std::cout << "? 8 " << control_daten->gear << std::endl;
			gear = control_daten->gear; //Button zuzücksetzen
		}
      
		if(temp != control_daten->temp)
		{ //Prüfen, ob sich die Temperatur geändet hat.
			std::cout << "? 9 " << control_daten->temp << std::endl;
			temp = control_daten->temp;
		}
		if(control_daten->xbox == true)
		{ //Prüfen, ob Button "xbox" (Fehlermeldungen) betätig wurde.
			std::cout << "? 10 " << control_daten->xbox << std::endl;
			control_daten->xbox = false;
		}

		if(control_daten->rsb_top == true)
		{ //Prüfen, ob Button "rsb_top" (Warnblinker) betätig wurde.
			std::cout << "? 11 " << control_daten->rsb_top << std::endl;
			control_daten->rsb_top = false;
		}  
		if(tank != control_daten->tank){ //Prüfen, ob sich der Tankwert geändet hat.
			std::cout << "? 12 " << control_daten->tank << std::endl;
			tank = control_daten->tank;
		}
		if(control_daten->a == true)
		{ //Prüfen, ob Button "a" (Volume Down) Button betätig wurde.
			std::cout << "? 13 " << control_daten->a << std::endl;
			control_daten->a = false; //Button zuzücksetzen
		}
		if(control_daten->y == true){ //Prüfen, ob Button "y" (Volume Up) betätig wurde.
			std::cout << "? 14 " << control_daten->b << std::endl;
			control_daten->y = false; //Button zuzücksetzen
		} 
		
		control_daten->my_new = false;
	
		} // endif my_new
    
	}
	analyseMediaControl(control_daten->media_control);
}

static void initLocalMediaControl()
{
	local_media_control.wheel_direction = NEUTRAL;
	local_media_control.wheel_turns = 0;
	local_media_control.wheel_pressed = false;
	local_media_control.menu_pressed = false;
	local_media_control.back_pressed = false;
	local_media_control.btn_right_pressed = false;
	local_media_control.btn_left_pressed = false;
}

static void analyseMediaControl(media_control_t *control_daten)
{
	if(control_daten->wheel_turns != 0)
	{
		std::cout << "? 20 " << control_daten->wheel_turns << std::endl;
		control_daten->wheel_turns = 0;
	}
	if(control_daten->wheel_direction != local_media_control.wheel_direction)
	{
		std::cout << "? 21 " << control_daten->wheel_direction << std::endl;
		local_media_control.wheel_direction = control_daten->wheel_direction;
	}
	if(control_daten->wheel_pressed != local_media_control.wheel_pressed)
	{
		std::cout << "? 22 " << control_daten->wheel_pressed << std::endl;
		local_media_control.wheel_pressed = control_daten->wheel_pressed;
	}
	if(control_daten->menu_pressed != local_media_control.menu_pressed)
	{
		std::cout << "? 23 " << control_daten->menu_pressed << std::endl;
		local_media_control.menu_pressed = control_daten->menu_pressed;
	}
	if(control_daten->back_pressed != local_media_control.back_pressed)
	{
		std::cout << "? 24 " << control_daten->back_pressed << std::endl;
		local_media_control.back_pressed = control_daten->back_pressed;
	}
	if(control_daten->btn_left_pressed != local_media_control.btn_left_pressed)
	{
		std::cout << "? 25 " << control_daten->btn_left_pressed << std::endl;
		local_media_control.btn_left_pressed = control_daten->btn_left_pressed;
	}
	if(control_daten->btn_right_pressed != local_media_control.btn_right_pressed)
	{
		std::cout << "? 26 " << control_daten->btn_right_pressed << std::endl;
		local_media_control.btn_right_pressed = control_daten->btn_right_pressed;
	}
}
