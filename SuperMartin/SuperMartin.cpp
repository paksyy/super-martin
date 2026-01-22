#include "eventosJuego.h"
#pragma warning(disable : 4996)

using namespace std;

int menu();
void controles();
int dificultad(int trofeos[], int dificultadNivel);

ALLEGRO_FONT* pix_elfy;
ALLEGRO_TIMER* segundosTimer;

int main()
{
	if (!al_init())//Sirve para correr allegro y en caso de no tenerlo, regresar el error
	{
		al_show_native_message_box(NULL, "Error critico", "Error 0", "No se pudo cargar la libreria allegro", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	//Se inizializan e instalan los necesarios para allegro
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_init_primitives_addon();
    al_install_keyboard();
    al_install_mouse();
    al_install_audio();
    al_init_acodec_addon();
	ventana = al_create_display(800, 600);//Crear la pantalla de cierto tamaño donde se jugara
	al_hide_mouse_cursor(ventana);
	pix_elfy = al_load_font("assets/fonts/Pixelfy.ttf", 20, 0);//Cargar la fuete a utilizar

	int ancho = GetSystemMetrics(SM_CXSCREEN);//Sacar el ancho de la pantalla
	int alto = GetSystemMetrics(SM_CYSCREEN);//Sacar el alto de la pantalla
	al_set_window_title(ventana, "Super Martin");//Nombrar la pantalla dejuego
	al_set_window_position(ventana, ancho / 2 - 800 / 2, alto / 2 - 600 / 2);//Posicionar la pantalla en medio

	segundosTimer = al_create_timer(1.0);//se crea un temporizador

	queue = al_create_event_queue();//Se crea una cola de eventos

	al_register_event_source(queue, al_get_timer_event_source(segundosTimer));//Se inicia un registro de temporizador
	al_register_event_source(queue, al_get_mouse_event_source());//Se inicia un registro de eventos
	al_register_event_source(queue, al_get_keyboard_event_source());//Se inicia un registro de eventos
	al_start_timer(segundosTimer);//se inicia el timer

	menu();

	return 0;
}

int menu()
{
	int segundo = 0;//variable para segundos
	int dificultadNivel = 1;
	al_reserve_samples(2);
	//Se inizializan los visuales y sonoros del juego
	ALLEGRO_COLOR negro = al_map_rgb(0, 0, 0);
	ALLEGRO_COLOR blanco = al_map_rgb(255, 255, 255);
	ALLEGRO_BITMAP* menu_null = al_load_bitmap("assets/images/menu_null.png");
	ALLEGRO_BITMAP* menu_jugar = al_load_bitmap("assets/images/menu_jugar.png");
	ALLEGRO_BITMAP* menu_dificultad = al_load_bitmap("assets/images/menu_dificultad.png");
	ALLEGRO_BITMAP* menu_salir = al_load_bitmap("assets/images/menu_salir.png");
	ALLEGRO_BITMAP* esc = al_load_bitmap("assets/images/esc.png");
	ALLEGRO_SAMPLE* seleccion = al_load_sample("assets/sounds/seleccion.wav");
	ALLEGRO_SAMPLE* cancion_menu = al_load_sample("assets/music/musicaMenu.mp3");
	ALLEGRO_BITMAP* comic1 = al_load_bitmap("assets/images/comic1.png");
	ALLEGRO_BITMAP* comic2 = al_load_bitmap("assets/images/comic2.png");
	ALLEGRO_BITMAP* comic3 = al_load_bitmap("assets/images/comic3.png");
	ALLEGRO_BITMAP* comic4 = al_load_bitmap("assets/images/comic4.png");
	ALLEGRO_BITMAP* comic5 = al_load_bitmap("assets/images/comic5.png");
	ALLEGRO_SAMPLE_INSTANCE* cancionMenuIns = al_create_sample_instance(cancion_menu);
	al_set_sample_instance_playmode(cancionMenuIns, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(cancionMenuIns, al_get_default_mixer());
	FILE* aptr;

	int control = 0;
	int botones[] = { 0 };
	int resultado;
	int trofeos[3];
	int i = 0;
	int controlImg = 0;
	//se lee los trofeos del usuario
	aptr = fopen("assets/data/trofeos.dat", "r+b");
	while (!feof(aptr))
	{
		fread(&trofeos[i], sizeof(trofeos), 1, aptr);
		i = i + 1;
	}
	fclose(aptr);


	al_play_sample_instance(cancionMenuIns);
	al_set_mixer_gain(al_get_default_mixer(), 0.08);
	while (true)
	{
		ALLEGRO_EVENT evento;//Se crea un evento
		al_register_event_source(queue, al_get_keyboard_event_source());
		al_wait_for_event(queue, &evento);//Se espera el evento
		al_clear_to_color(al_map_rgb(0, 0, 0));//Borrar la panntalla
		while (controlImg == 0)
		{
			al_draw_bitmap(comic1, 0, 0, 0);
			al_wait_for_event(queue, &evento);//Se espera el evento
			if (evento.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				switch (evento.keyboard.keycode)
				{
				case ALLEGRO_KEY_SPACE:

					controlImg = 1;
					break;
				}

			}
			al_flip_display();//Mostrar en la pantalla
		}
		//Siempre que se hable de controlImg, es para ver el comic
		if (controlImg > 0)
		{
			controlImg = 0;
		}
		al_clear_to_color(al_map_rgb(0, 0, 0));//Borrar la panntalla
		while (controlImg == 0)
		{
			al_draw_bitmap(comic2, 0, 0, 0);
			al_wait_for_event(queue, &evento);//Se espera el evento
			if (evento.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				switch (evento.keyboard.keycode)
				{
				case ALLEGRO_KEY_SPACE:

					controlImg = 1;
					break;
				}

			}
			al_flip_display();//Mostrar en la pantalla
		}
		if (controlImg > 0)
		{
			controlImg = 0;
		}
		al_clear_to_color(al_map_rgb(0, 0, 0));//Borrar la panntalla
		while (controlImg == 0)
		{
			al_draw_bitmap(comic3, 0, 0, 0);
			al_wait_for_event(queue, &evento);//Se espera el evento
			if (evento.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				switch (evento.keyboard.keycode)
				{
				case ALLEGRO_KEY_SPACE:

					controlImg = 1;
					break;
				}

			}
			al_flip_display();//Mostrar en la pantalla
		}
		if (controlImg > 0)
		{
			controlImg = 0;
		}
		al_clear_to_color(al_map_rgb(0, 0, 0));//Borrar la panntalla
		while (controlImg == 0)
		{
			al_draw_bitmap(comic4, 0, 0, 0);
			al_wait_for_event(queue, &evento);//Se espera el evento
			if (evento.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				switch (evento.keyboard.keycode)
				{
				case ALLEGRO_KEY_SPACE:

					controlImg = 1;
					break;
				}

			}
			al_flip_display();//Mostrar en la pantalla
		}
		if (controlImg > 0)
		{
			controlImg = 0;
		}
		al_clear_to_color(al_map_rgb(0, 0, 0));//Borrar la panntalla
		while (controlImg == 0)
		{
			al_draw_bitmap(comic5, 0, 0, 0);
			al_wait_for_event(queue, &evento);//Se espera el evento
			if (evento.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				switch (evento.keyboard.keycode)
				{
				case ALLEGRO_KEY_SPACE:

					controlImg = 1;
					break;
				}

			}
			al_flip_display();//Mostrar en la pantalla
		}
		controlImg = -1;
		//Se termina el comic
		//Se empieza a mostrar el mmenu y sus opciones
		if (botones[0] == 0)
		{
			al_draw_bitmap(menu_null, 0, 0, 0);
		}
		else if (botones[0] == 1)
		{
			al_draw_bitmap(menu_jugar, 0, 0, 0);
		}
		else if (botones[0] == 2)
		{
			al_draw_bitmap(menu_dificultad, 0, 0, 0);
		}
		else if (botones[0] == 3)
		{
			al_draw_bitmap(menu_salir, 0, 0, 0);
		}
		al_draw_bitmap(esc, 680, 10, 0);
		//Dependiendo las teclas, se cambiara de imagen para mostrar en el menu
		if (evento.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (evento.keyboard.keycode)
			{
			case ALLEGRO_KEY_DOWN:
				if (botones[0] < 3)
				{
					botones[0] += 1;
					control = 1;
					al_play_sample(seleccion, 5.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
				}
				break;
			case ALLEGRO_KEY_UP:
				if (control == 0)
				{
					botones[0] += 1;
					control = 1;
					al_play_sample(seleccion, 5.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
				}
				else if (control == 1)
				{
					if (botones[0] > 1)
					{
						botones[0] -= 1;
						al_play_sample(seleccion, 5.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
					}
				}
				break;
				//Se selecciona una opcion y dependiendo se haran ciertas cosas
			case ALLEGRO_KEY_ENTER:
			{
				//se redirige a jugar
				if (botones[0] == 1)
				{
					al_stop_sample_instance(cancionMenuIns);
					do
					{
						resultado = events(dificultadNivel);
						al_destroy_event_queue(queue); //Destruye la cola de eventos
						queue = al_create_event_queue(); //Creacion de la cola de eventos
						botones[0] = 0;
					} while (resultado == 0);
					trofeos[dificultadNivel - 1] = resultado;
					al_draw_bitmap(menu_null, 0, 0, 0);
					al_play_sample_instance(cancionMenuIns);
				}
				//se redirige a dificultad
				else if (botones[0] == 2)
				{
					al_stop_sample_instance(cancionMenuIns);
					dificultadNivel = dificultad(trofeos, dificultadNivel);
					al_destroy_event_queue(queue); //Destruye la cola de eventos
					queue = al_create_event_queue(); //Creacion de la cola de eventos
					botones[0] = 0;
					al_play_sample_instance(cancionMenuIns);
				}
				//Te sales del juego
				else if (botones[0] == 3)
				{
					i = 0;
					al_stop_sample_instance(cancionMenuIns);
					aptr = fopen("assets/data/trofeos.dat", "w+b");
					while (i < 3)
					{
						fwrite(&trofeos[i], sizeof(trofeos), 1, aptr);
						i = i + 1;
					}
					fclose(aptr);
					return 1;
				}
				break;
			}
			//ves los controles
			case ALLEGRO_KEY_C:
			{
				al_stop_sample_instance(cancionMenuIns);
				controles();
				al_draw_bitmap(menu_null, 0, 0, 0);
				al_play_sample_instance(cancionMenuIns);
				break;
			}
			default:
				break;
			}
		}
		al_flip_display();//Mostrar en la pantalla
	}
	al_destroy_sample_instance(cancionMenuIns);
}

void controles()
{
	al_reserve_samples(1);

	ALLEGRO_BITMAP* controles = al_load_bitmap("assets/images/controles.png");
	ALLEGRO_SAMPLE* cancion_dificultad = al_load_sample("assets/music/musicaDificultad.mp3");
	ALLEGRO_SAMPLE_INSTANCE* cancionDificultadIns = al_create_sample_instance(cancion_dificultad);
	al_set_sample_instance_playmode(cancionDificultadIns, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(cancionDificultadIns, al_get_default_mixer());
	al_set_mixer_gain(al_get_default_mixer(), 0.08);

	//se muestra una imagen de los controles
	al_play_sample_instance(cancionDificultadIns);
	while (true)
	{
		ALLEGRO_EVENT evento;//Se crea un evento
		al_wait_for_event(queue, &evento);//Se espera el evento
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_bitmap(controles, 0, 0, 0);
		if (evento.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (evento.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				al_destroy_sample_instance(cancionDificultadIns);
				return;
				break;

			default:
				break;
			}
		}
		al_flip_display();
	}
	al_destroy_sample_instance(cancionDificultadIns);
}

int dificultad(int trofeos[], int dificultadNivel)
{
	ALLEGRO_COLOR negro = al_map_rgb(0, 0, 0);
	ALLEGRO_COLOR blanco = al_map_rgb(255, 255, 255);

	al_reserve_samples(2);
	//Se inicializan las variables
	ALLEGRO_BITMAP* menu_dificultad_null = al_load_bitmap("assets/images/menu_dificultad_null.png");
	ALLEGRO_BITMAP* menu_dificultad_facil = al_load_bitmap("assets/images/menu_dificultad_facil.png");
	ALLEGRO_BITMAP* menu_dificultad_medio = al_load_bitmap("assets/images/menu_dificultad_medio.png");
	ALLEGRO_BITMAP* menu_dificultad_dificil = al_load_bitmap("assets/images/menu_dificultad_dificil.png");
	ALLEGRO_SAMPLE* seleccionD = al_load_sample("assets/sounds/dibujo_circulo.mp3");
	ALLEGRO_SAMPLE* cancion_dificultad = al_load_sample("assets/music/musicaDificultad.mp3");
	ALLEGRO_BITMAP* azul1 = al_load_bitmap("assets/images/azul1.png");
	ALLEGRO_BITMAP* azul2 = al_load_bitmap("assets/images/azul2.png");
	ALLEGRO_BITMAP* azul3 = al_load_bitmap("assets/images/azul3.png");
	ALLEGRO_BITMAP* verde1 = al_load_bitmap("assets/images/verde1.png");
	ALLEGRO_BITMAP* verde2 = al_load_bitmap("assets/images/verde2.png");
	ALLEGRO_BITMAP* verde3 = al_load_bitmap("assets/images/verde3.png");
	ALLEGRO_BITMAP* rojo1 = al_load_bitmap("assets/images/rojo1.png");
	ALLEGRO_BITMAP* rojo2 = al_load_bitmap("assets/images/rojo2.png");
	ALLEGRO_BITMAP* rojo3 = al_load_bitmap("assets/images/rojo3.png");


	ALLEGRO_SAMPLE_INSTANCE* cancionDificultadIns = al_create_sample_instance(cancion_dificultad);
	al_set_sample_instance_playmode(cancionDificultadIns, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(cancionDificultadIns, al_get_default_mixer());
	al_set_mixer_gain(al_get_default_mixer(), 0.08);

	int botonesDificultad[] = { 0 };
	int control = 0;
	al_play_sample_instance(cancionDificultadIns);
	while (true)
	{
		ALLEGRO_EVENT evento;//Se crea un evento
		al_wait_for_event(queue, &evento);//Se espera el evento
		al_clear_to_color(al_map_rgb(0, 0, 0));
		//Dependiendo la dificultad se muestran las imagenes
		if (botonesDificultad[0] == 0)
		{
			al_draw_bitmap(menu_dificultad_null, 0, 0, 0);
		}
		else if (botonesDificultad[0] == 1)
		{
			al_draw_bitmap(menu_dificultad_facil, 0, 0, 0);
		}
		else if (botonesDificultad[0] == 2)
		{
			al_draw_bitmap(menu_dificultad_medio, 0, 0, 0);
		}
		else if (botonesDificultad[0] == 3)
		{
			al_draw_bitmap(menu_dificultad_dificil, 0, 0, 0);
		}
		if (trofeos[0] == 1)
		{
			al_draw_bitmap(azul3, 200, 280, 0);
		}
		if (trofeos[0] == 2)
		{
			al_draw_bitmap(azul2, 200, 280, 0);
		}
		if (trofeos[0] == 3)
		{
			al_draw_bitmap(azul1, 200, 280, 0);
		}
		if (trofeos[1] == 1)
		{
			al_draw_bitmap(verde3, 400, 300, 0);
		}
		if (trofeos[1] == 2)
		{
			al_draw_bitmap(verde2, 400, 300, 0);
		}
		if (trofeos[1] == 3)
		{
			al_draw_bitmap(verde1, 400, 300, 0);
		}
		if (trofeos[2] == 1)
		{
			al_draw_bitmap(rojo3, 550, 300, 0);
		}
		if (trofeos[2] == 2)
		{
			al_draw_bitmap(rojo2, 550, 300, 0);
		}
		if (trofeos[2] == 3)
		{
			al_draw_bitmap(rojo1, 550, 300, 0);
		}
		//Dependiendo las teclas se muentran diferentes imagenes, y si ya habias completado un nivel se guarda tu progreso
		if (evento.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (evento.keyboard.keycode)
			{
			case ALLEGRO_KEY_RIGHT:
				if (botonesDificultad[0] < 3)
				{
					botonesDificultad[0] += 1;
					control = 1;
					al_play_sample(seleccionD, 6.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
				}
				break;
			case ALLEGRO_KEY_LEFT:
				if (control == 0)
				{
					botonesDificultad[0] += 1;
					control = 1;
					al_play_sample(seleccionD, 6.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
				}
				else if (control == 1)
				{
					if (botonesDificultad[0] > 1)
					{
						botonesDificultad[0] -= 1;
						al_play_sample(seleccionD, 6.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
					}
				}
				break;
			case ALLEGRO_KEY_ENTER:
			{
				if (botonesDificultad[0] == 1)
				{
					al_stop_sample_instance(cancionDificultadIns);
					return 1;
				}
				else if (botonesDificultad[0] == 2)
				{
					al_stop_sample_instance(cancionDificultadIns);
					return 2;
				}
				else if (botonesDificultad[0] == 3)
				{
					al_stop_sample_instance(cancionDificultadIns);
					return 3;
				}
				break;
			}
			//Te sales directamente del nivel
			case ALLEGRO_KEY_ESCAPE:
			{
				al_stop_sample_instance(cancionDificultadIns);
				return dificultadNivel;
				break;
			}
			default:
				break;
			}
		}
		al_flip_display();
	}
	al_destroy_sample_instance(cancionDificultadIns);
}
