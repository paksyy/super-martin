#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <Windows.h> // se utilizara para acceder a la resolucion de la pantalla 
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <string>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include <time.h>

#define ANCHO 800
#define ALTO 600


using namespace std;

ALLEGRO_DISPLAY* ventana;
ALLEGRO_EVENT_QUEUE* queue;

//Fisica de colision
bool Collision(float x, float y, float ex, float ey, int ancho, int alto)
{
	if (x + ancho <ex || x > ex + ancho || y + alto <ey || y> ey + alto)
	{
		//Sin colicion
		return false;
	}
	return true;
}

//Funcion para la camara centrada
void actualCamara(float* cameraPosition, float x, float y, int ancho, int alto)
{
	cameraPosition[0] = -(ANCHO / 2) + (x + ancho / 2);
	cameraPosition[1] = -(ALTO / 2) + (y + alto / 2);

	if (cameraPosition[0] < 0)
	{
		cameraPosition[0] = 0;
	}
	else if (cameraPosition[0] > 800)
	{
		cameraPosition[0] = 800;
	}
	if (cameraPosition[1] < 0)
	{
		cameraPosition[1] = 0;
	}
}
//Funcion para sacar los examenes
int escoger(int x, int num1, int num2, int resultado, int operacion)
{
	int num = 0;
	int control = 0;
	if (!al_init()) //En caso de qu no se pueda inicializar allegro
	{
		al_show_native_message_box(NULL, "Error", "Error", "No se pudo iniciar allegro!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	al_init_primitives_addon();
	al_install_keyboard(); //instala el teclado
	al_init_primitives_addon();//permite incluir imagenes
	al_init_image_addon();
	al_install_audio();
	al_init_acodec_addon(); //Implementacion de sonido y musica
	al_reserve_samples(2);
	ALLEGRO_FONT* MermaidB = al_load_font("assets/fonts/Mermaid Babies.ttf", 50, 0);
	ALLEGRO_BITMAP* examen = al_load_bitmap("assets/images/examen.png");
	ALLEGRO_BITMAP* examenF1 = al_load_bitmap("assets/images/examenF1.png");
	ALLEGRO_BITMAP* examenF2 = al_load_bitmap("assets/images/examenF2.png");
	ALLEGRO_BITMAP* examenF3 = al_load_bitmap("assets/images/examenF3.png");
	ALLEGRO_SAMPLE* seleccion = al_load_sample("assets/sounds/seleccion.wav");
	ALLEGRO_EVENT_QUEUE* cola = al_create_event_queue(); //Creacion de la cola de eventos
	al_register_event_source(cola, al_get_keyboard_event_source()); //Registra el teclado en la cola de eventos
	al_register_event_source(cola, al_get_display_event_source(ventana)); //Registra la pantalla en la cola de eventos

	int botones[] = { 0 };
	int opcion = (rand() % 3) + 1;
	cout << opcion;
	while (1)
	{
		ALLEGRO_EVENT eventoE;//Se crea un evento
		al_wait_for_event(cola, &eventoE);//Se espera el evento
		//Se muestran las imagenes de los problemas matematicos
		if (botones[0] == 0)
		{
			al_draw_bitmap(examen, x - 180, 20, 0);
		}
		else if (botones[0] == 1)
		{
			al_draw_bitmap(examenF1, x - 180, 20, 0);
		}
		else if (botones[0] == 2)
		{
			al_draw_bitmap(examenF2, x - 180, 20, 0);
		}
		else if (botones[0] == 3)
		{
			al_draw_bitmap(examenF3, x - 180, 20, 0);
		}
		al_draw_text(MermaidB, al_map_rgb(0, 0, 0), x - 120, 250, NULL, (to_string(num1)).c_str());
		al_draw_text(MermaidB, al_map_rgb(0, 0, 0), x + 50, 250, NULL, (to_string(num2)).c_str());
		if (operacion == 1)
		{
			al_draw_text(MermaidB, al_map_rgb(0, 0, 0), x, 250, NULL, "+");
		}
		else if (operacion == 2)
		{
			al_draw_text(MermaidB, al_map_rgb(0, 0, 0), x, 250, NULL, "-");
		}
		else if (operacion == 3)
		{
			al_draw_text(MermaidB, al_map_rgb(0, 0, 0), x, 250, NULL, "x");
		}
		al_draw_text(MermaidB, al_map_rgb(0, 0, 0), x + 180, 250, NULL, "=");

		if (opcion == 1)
		{
			al_draw_text(MermaidB, al_map_rgb(0, 0, 0), x - 120, 340, NULL, ("a) " + to_string(resultado)).c_str());
			al_draw_text(MermaidB, al_map_rgb(0, 0, 0), x - 120, 440, NULL, ("b) " + to_string(resultado + 3)).c_str());
			al_draw_text(MermaidB, al_map_rgb(0, 0, 0), x - 120, 540, NULL, ("c) " + to_string(resultado + 4)).c_str());
		}
		else if (opcion == 2)
		{
			al_draw_text(MermaidB, al_map_rgb(0, 0, 0), x - 120, 340, NULL, ("a) " + to_string(resultado + 3)).c_str());
			al_draw_text(MermaidB, al_map_rgb(0, 0, 0), x - 120, 440, NULL, ("b) " + to_string(resultado)).c_str());
			al_draw_text(MermaidB, al_map_rgb(0, 0, 0), x - 120, 540, NULL, ("c) " + to_string(resultado + 2)).c_str());
		}
		else
		{
			al_draw_text(MermaidB, al_map_rgb(0, 0, 0), x - 120, 340, NULL, ("a)" + to_string(resultado + 1)).c_str());
			al_draw_text(MermaidB, al_map_rgb(0, 0, 0), x - 120, 440, NULL, ("b)" + to_string(resultado + 4)).c_str());
			al_draw_text(MermaidB, al_map_rgb(0, 0, 0), x - 120, 540, NULL, ("c)" + to_string(resultado)).c_str());
		}

		if (eventoE.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (eventoE.keyboard.keycode)
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
				//Dependiendo el boton se va regresar cierto resultado
			case ALLEGRO_KEY_ENTER:
			{
				if (botones[0] == 1)
				{
					al_destroy_bitmap(examen);
					al_destroy_bitmap(examenF1);
					al_destroy_bitmap(examenF2);
					al_destroy_bitmap(examenF3);
					if (opcion == 1)
					{
						return resultado;
					}
					else if (opcion == 2)
					{
						return resultado + 3;
					}
					else
					{
						return resultado + 1;
					}
				}
				else if (botones[0] == 2)
				{
					al_destroy_bitmap(examen);
					al_destroy_bitmap(examenF1);
					al_destroy_bitmap(examenF2);
					al_destroy_bitmap(examenF3);
					if (opcion == 1)
					{
						return resultado + 3;
					}
					else if (opcion == 2)
					{
						return resultado;
					}
					else
					{
						return resultado + 4;
					}
				}
				else if (botones[0] == 3)
				{
					al_destroy_bitmap(examen);
					al_destroy_bitmap(examenF1);
					al_destroy_bitmap(examenF2);
					al_destroy_bitmap(examenF3);
					if (opcion == 1)
					{
						return resultado + 4;
					}
					else if (opcion == 2)
					{
						return resultado + 2;
					}
					else
					{
						return resultado;
					}
				}
				break;
			}
			}

		}
		al_flip_display();//Mostrar en la pantalla
	}
}



int events(int dificultad)
{
	const float FPS = 60;
	int frame = 0;
	int banderaOp = 0;

	int no1, no2, no3, no4;
	int examenes[3] = { 0,0,0 };
	//crea numeros randoms para las operaciones 
	srand(time(NULL));
	int resultadoSumaDificil;
	int resultadoRestaDificil;
	int resultadoMultiplicacionDificil;

	//Operacion en dificultad : NORMAL
	int resultadoSumaNormal;
	int resultadoRestaNormal;
	int resultadoMultiplicacionNormal;

	//Operacion en dificultad : FACIL
	int resultadoSumaFacil;
	int resultadoRestaFacil;
	int resultadoMultiplicacionFacil;
	int operacionX;//Varia entre suma,resta y multiplicacion
	int resultadoX; //Varia entre resultado de sumas,restas y multiplicaciones
	//int operacionX;


	if (!al_init()) //En caso de qu no se pueda inicializar allegro
	{
		al_show_native_message_box(NULL, "Error", "Error", "No se pudo iniciar allegro!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	al_set_new_display_flags(ALLEGRO_WINDOWED);
	ALLEGRO_FONT* MermaidB = al_load_font("assets/fonts/Mermaid Babies.ttf", 20, 0);

	if (!ventana)
	{
		al_show_native_message_box(NULL, "Error", "Error", "No se pudo abrir la pantalla!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	float cameraPosition[2] = { 0,0 };
	ALLEGRO_TRANSFORM camera;


	al_init_primitives_addon();
	al_install_keyboard(); //instala el teclado
	al_init_primitives_addon();//permite incluir imagenes
	al_init_image_addon();
	al_install_audio();
	al_init_acodec_addon(); //Implementacion de sonido y musica
	al_reserve_samples(8);
	//Se declaran las variables
	ALLEGRO_SAMPLE* efectoSonido = al_load_sample("assets/sounds/salto.wav");
	ALLEGRO_SAMPLE* song = al_load_sample("assets/music/musicaJuego.mp3");
	ALLEGRO_SAMPLE* triste = al_load_sample("assets/music/triste.mp3");
	ALLEGRO_SAMPLE* feliz = al_load_sample("assets/music/feliz.mp3");
	ALLEGRO_SAMPLE* dolor = al_load_sample("assets/sounds/dolor.wav");
	ALLEGRO_BITMAP* fondo = al_load_bitmap("assets/images/fondo.png");
	ALLEGRO_BITMAP* fondoA = al_load_bitmap("assets/images/fondoB.png");
	ALLEGRO_BITMAP* fondoB = al_load_bitmap("assets/images/fondoB.png");
	ALLEGRO_BITMAP* pasto = al_load_bitmap("assets/images/pasto.png");
	ALLEGRO_BITMAP* meta = al_load_bitmap("assets/images/Meta.png");
	ALLEGRO_BITMAP* vida = al_load_bitmap("assets/images/corazon.png");
	ALLEGRO_BITMAP* examen0 = al_load_bitmap("assets/images/examen0.png");
	ALLEGRO_BITMAP* examen6 = al_load_bitmap("assets/images/examen6.png");
	ALLEGRO_BITMAP* examen8 = al_load_bitmap("assets/images/examen8.png");
	ALLEGRO_BITMAP* examen10 = al_load_bitmap("assets/images/examen10.png");
	ALLEGRO_BITMAP* picos = al_load_bitmap("assets/images/picos.png");
	ALLEGRO_BITMAP* enter = al_load_bitmap("assets/images/enter.png");

	ALLEGRO_SAMPLE_INSTANCE* songInstance = al_create_sample_instance(song);
	ALLEGRO_SAMPLE_INSTANCE* songInstanceD = al_create_sample_instance(dolor);
	al_set_sample_instance_playmode(songInstance, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(songInstance, al_get_default_mixer());


	ALLEGRO_BITMAP* jugador = al_load_bitmap("assets/images/caminar1.png");
	ALLEGRO_BITMAP* estructura = al_load_bitmap("assets/images/punto.png");
	ALLEGRO_KEYBOARD_STATE keyState;
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS); //Creacion de temporizador
	ALLEGRO_COLOR azul = al_map_rgb(44, 117, 255); //Configuracion de color
	ALLEGRO_COLOR amarillo = al_map_rgb(255, 255, 0);
	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue(); //Creacion de la cola de eventos

	al_register_event_source(event_queue, al_get_keyboard_event_source()); //Registra el teclado en la cola de evetos
	al_register_event_source(event_queue, al_get_timer_event_source(timer)); //Registra el timer en la cola de eventos
	al_play_sample_instance(songInstance);
	al_register_event_source(event_queue, al_get_display_event_source(ventana)); //Registra la pantalla en la cola de eventos
	al_hide_mouse_cursor(ventana);
	al_start_timer(timer); //Inicia el temporizador

	bool done = false, dibujar = true, activo = false;
	float x = 10, y = 10;//Ubicacion inicial del jugador
	float velocidad = 4; //Velocidad de movimiento del jugador
	float velx = 0, vely = 0;//velocidad inicial del jugador
	int sourceX = 32; //Direccion inicial del jugador
	const float gravedad = 1; //Definiendo la gravedad
	bool jump = false; //Variable para salto
	float jumpspeed = 20;//Velocida de salto
	int vidas = 3;//Vidas iniciales
	int control = 1;//Variable para controlar otras funciones
	while (!done)//Direccionamiento del personaje
	{
		ALLEGRO_EVENT ev; //Creacion de evento

		al_wait_for_event(event_queue, &ev);
		al_get_keyboard_state(&keyState);
		al_clear_to_color(al_map_rgb(0, 0, 0)); //Limpia la pantalla
		al_draw_bitmap(fondo, 0, 0, 0);
		al_draw_bitmap(fondo, 800, 0, 0);
		al_draw_bitmap(fondoA, 0, 600, 0);
		al_draw_bitmap(fondoA, 800, 600, 0);
		al_draw_bitmap(fondoB, 0, -600, 0);
		al_draw_bitmap(fondoB, 800, -600, 0);
		al_draw_bitmap(pasto, 0, 208, 0);
		al_draw_bitmap(pasto, 800, 208, 0);
		al_draw_bitmap(meta, 1400, 540, 0);
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		//El juego trabaja con un timer para los frames y que este pueda correr sin problema
		else if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			if (banderaOp != 1) {
				//Animacion para ir a la derecha
				if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT))
				{
					jugador = al_load_bitmap("assets/images/caminar1.png");
					velx = velocidad;
					activo = true;
					if (frame == 1)
					{
						jugador = al_load_bitmap("assets/images/caminar2.png");
						frame = 2;

					}
					else if (frame == 3)
					{
						jugador = al_load_bitmap("assets/images/caminar1.png");
						frame = 1;
					}
					else
					{
						jugador = al_load_bitmap("assets/images/caminar3.png");
						frame = 3;
					}

				}
				//Animacion para ir a la izquierda
				else if (al_key_down(&keyState, ALLEGRO_KEY_LEFT))
				{
					jugador = al_load_bitmap("assets/images/caminarI1.png");
					velx = -velocidad;
					activo = true;
					if (frame == 1)
					{
						jugador = al_load_bitmap("assets/images/caminarI2.png");
						frame = 2;

					}
					else if (frame == 3)
					{
						jugador = al_load_bitmap("assets/images/caminarI1.png");
						frame = 1;
					}
					else
					{
						jugador = al_load_bitmap("assets/images/caminarI3.png");
						frame = 3;
					}
				}
				else
				{
					velx = 0;
					activo = false;
				}
			}
			else
			{
				velx = 0;
				activo = false;
			}
			if (banderaOp != 1)
			{
				if (al_key_down(&keyState, ALLEGRO_KEY_SPACE) && jump)
				{
					al_play_sample(efectoSonido, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					vely -= jumpspeed;
					jump = false;
				}
			}
			//Fisicas basicas para el juego
			if (!jump)
			{
				vely += gravedad;
			}
			else
			{
				vely = 0;
			}

			if (x >= 0 && x <= 1560)
			{
				x += velx;
			}
			else
			{
				if (x < 0)
				{
					x = x + .5;
				}
				else
				{
					x = x - .5;
				}
			}

			y += vely;

			jump = (y >= 560);
			if (jump == true)
			{
				y = 560;
			}
			else
			{
				velx = 0;
				activo = false;
			}

			actualCamara(cameraPosition, x, 350, 64, 64);
			al_identity_transform(&camera);
			al_translate_transform(&camera, -cameraPosition[0], -cameraPosition[1]);
			al_use_transform(&camera);

			//Salirse del juego
			if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE))
			{
				al_destroy_event_queue(event_queue); //Destruye la cola de eventos
				al_destroy_timer(timer); //Destruye el temporizador
				al_destroy_bitmap(jugador);
				al_destroy_sample(efectoSonido);
				al_destroy_sample(song);
				al_destroy_sample_instance(songInstance);;
				actualCamara(cameraPosition, 0, -100, 32, 32);
				al_identity_transform(&camera);
				al_translate_transform(&camera, -cameraPosition[0], -cameraPosition[1]);
				al_use_transform(&camera);
				return -1;
			}
		}
		if (banderaOp == 1 || banderaOp == 2 || banderaOp == 3)
		{
			//Todo dentro del if de arriba es para la parte de generar y comprobar las operaciones
			no1 = (rand() % 10) + 1;
			no2 = (rand() % 100) + 1;
			no3 = (rand() % 300) + 1;
			no4 = (rand() % 20) + 10;
			//Operacion en dificultad : DIFICIL
			resultadoSumaDificil = no3 + no2;
			resultadoRestaDificil = no3 - no2;
			resultadoMultiplicacionDificil = no2 * no3;

			//Operacion en dificultad : NORMAL
			resultadoSumaNormal = no2 + no1;
			resultadoRestaNormal = no3 - no1;
			resultadoMultiplicacionNormal = no1 * no2;

			//Operacion en dificultad : FACIL
			resultadoSumaFacil = no1 + no1;
			resultadoRestaFacil = no4 - no1;
			resultadoMultiplicacionFacil = no1 * no1;
			operacionX = (rand() % 3) + 1;
			//Operaciones 
			 //Dificultad:DIFICIL
			 //Suma
			if (operacionX == 1 && dificultad == 3)
			{
				resultadoX = escoger(x, no3, no2, resultadoSumaDificil, operacionX);
				if (resultadoX == resultadoSumaDificil)
				{
					if (banderaOp == 1)
					{
						examenes[0] = 1;
					}
					else if (banderaOp == 2)
					{
						examenes[1] = 1;
					}
					else if (banderaOp == 3)
					{
						examenes[2] = 1;
					}
					banderaOp = 0;

				}
				else
				{
					x = 80;
					y = 400;
					banderaOp = 0;
					vidas--;
				}
			}
			//Resta
			else if (operacionX == 2 && dificultad == 3)
			{
				resultadoX = escoger(x, no3, no2, resultadoRestaDificil, operacionX);
				if (resultadoX == resultadoRestaDificil)
				{
					if (banderaOp == 1)
					{
						examenes[0] = 1;
					}
					else if (banderaOp == 2)
					{
						examenes[1] = 1;
					}
					else if (banderaOp == 3)
					{
						examenes[2] = 1;
					}
					banderaOp = 0;
				}
				else
				{
					x = 80;
					y = 400;
					banderaOp = 0;
					vidas--;
				}
			}
			//Multipliacacion
			else if (operacionX == 3 && dificultad == 3)
			{
				resultadoX = escoger(x, no2, no3, resultadoMultiplicacionDificil, operacionX);
				if (resultadoX == resultadoMultiplicacionDificil)
				{
					if (banderaOp == 1)
					{
						examenes[0] = 1;
					}
					else if (banderaOp == 2)
					{
						examenes[1] = 1;
					}
					else if (banderaOp == 3)
					{
						examenes[2] = 1;
					}
					banderaOp = 0;
				}
				else
				{
					x = 80;
					y = 400;
					banderaOp = 0;
					vidas--;
				}
			}
			//Dificultad:Normal
			//Suma
			else if (operacionX == 1 && dificultad == 2)
			{
				resultadoX = escoger(x, no2, no1, resultadoSumaNormal, operacionX);
				if (resultadoX == resultadoSumaNormal)
				{
					if (banderaOp == 1)
					{
						examenes[0] = 1;
					}
					else if (banderaOp == 2)
					{
						examenes[1] = 1;
					}
					else if (banderaOp == 3)
					{
						examenes[2] = 1;
					}
					banderaOp = 0;
				}
				else
				{
					x = 80;
					y = 400;
					banderaOp = 0;
					vidas--;
				}
			}
			//Resta
			else if (operacionX == 2 && dificultad == 2)
			{
				resultadoX = escoger(x, no3, no1, resultadoRestaNormal, operacionX);
				if (resultadoX == resultadoRestaNormal)
				{
					if (banderaOp == 1)
					{
						examenes[0] = 1;
					}
					else if (banderaOp == 2)
					{
						examenes[1] = 1;
					}
					else if (banderaOp == 3)
					{
						examenes[2] = 1;
					}
					banderaOp = 0;
				}
				else
				{
					x = 80;
					y = 400;
					banderaOp = 0;
					vidas--;
				}
			}
			//Multipliacacion
			else if (operacionX == 3 && dificultad == 2)
			{
				resultadoX = escoger(x, no1, no2, resultadoMultiplicacionNormal, operacionX);
				if (resultadoX == resultadoMultiplicacionNormal)
				{
					if (banderaOp == 1)
					{
						examenes[0] = 1;
					}
					else if (banderaOp == 2)
					{
						examenes[1] = 1;
					}
					else if (banderaOp == 3)
					{
						examenes[2] = 1;
					}
					banderaOp = 0;
				}
				else
				{
					x = 80;
					y = 400;
					banderaOp = 0;
					vidas--;
				}
			}
			//Dificultad:Facil
			//Suma
			else if (operacionX == 1 && dificultad == 1)
			{
				resultadoX = escoger(x, no1, no1, resultadoSumaFacil, operacionX);
				if (resultadoX == resultadoSumaFacil)
				{
					if (banderaOp == 1)
					{
						examenes[0] = 1;
					}
					else if (banderaOp == 2)
					{
						examenes[1] = 1;
					}
					else if (banderaOp == 3)
					{
						examenes[2] = 1;
					}
					banderaOp = 0;
				}
				else
				{
					x = 80;
					y = 400;
					banderaOp = 0;
					vidas--;
				}
			}
			//Resta
			else if (operacionX == 2 && dificultad == 1)
			{
				resultadoX = escoger(x, no4, no1, resultadoRestaFacil, operacionX);
				if (resultadoX == resultadoRestaFacil)
				{
					if (banderaOp == 1)
					{
						examenes[0] = 1;
					}
					else if (banderaOp == 2)
					{
						examenes[1] = 1;
					}
					else if (banderaOp == 3)
					{
						examenes[2] = 1;
					}
					banderaOp = 0;
				}
				else
				{
					x = 80;
					y = 400;
					banderaOp = 0;
					vidas--;
				}
			}
			//Multipliacacion
			else if (operacionX == 3 && dificultad == 1)
			{
				resultadoX = escoger(x, no1, no1, resultadoMultiplicacionFacil, operacionX);
				if (resultadoX == resultadoMultiplicacionFacil)
				{
					if (banderaOp == 1)
					{
						examenes[0] = 1;
					}
					else if (banderaOp == 2)
					{
						examenes[1] = 1;
					}
					else if (banderaOp == 3)
					{
						examenes[2] = 1;
					}
					banderaOp = 0;
				}
				else
				{
					x = 80;
					y = 400;
					banderaOp = 0;
					vidas--;
				}
			}
		}

		//Dependiendo cuantas vidas te muestra mas o menos imagenes
		if (vidas == 3)
		{

			if (x < 365)
			{
				al_draw_bitmap(vida, 25, 110, NULL);
			}
			else if (x > 1170)
			{
				al_draw_bitmap(vida, 825, 110, NULL);
			}
			else
			{
				al_draw_bitmap(vida, x - 343, 110, NULL);
			}
			if (x < 365)
			{
				al_draw_bitmap(vida, 95, 110, NULL);
			}
			else if (x > 1170)
			{
				al_draw_bitmap(vida, 895, 110, NULL);
			}
			else
			{
				al_draw_bitmap(vida, x - 273, 110, NULL);
			}

			if (x < 365)
			{
				al_draw_bitmap(vida, 165, 110, NULL);
			}
			else if (x > 1170)
			{
				al_draw_bitmap(vida, 965, 110, NULL);
			}
			else
			{
				al_draw_bitmap(vida, x - 203, 110, NULL);
			}

		}
		else if (vidas == 2)
		{
			if (x < 365)
			{
				al_draw_bitmap(vida, 25, 110, NULL);
			}
			else if (x > 1170)
			{
				al_draw_bitmap(vida, 815, 110, NULL);
			}
			else
			{
				al_draw_bitmap(vida, x - 343, 110, NULL);
			}

			if (x < 365)
			{
				al_draw_bitmap(vida, 95, 110, NULL);
			}
			else if (x > 1170)
			{
				al_draw_bitmap(vida, 885, 110, NULL);
			}
			else
			{
				al_draw_bitmap(vida, x - 273, 110, NULL);
			}
		}
		else if (vidas == 1)
		{
			if (x < 365)
			{
				al_draw_bitmap(vida, 25, 110, NULL);
			}
			else if (x > 1170)
			{
				al_draw_bitmap(vida, 815, 110, NULL);
			}
			else
			{
				al_draw_bitmap(vida, x - 343, 110, NULL);
			}
		}
		//Si no tienes vidas Te muestra una imagen que perdiste
		else
		{
			al_destroy_sample(song);
			al_play_sample(triste, 8.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, 0);
			do
			{
				al_get_keyboard_state(&keyState);
				if (x < 365)
				{
					al_draw_bitmap(examen0, 180, 20, NULL);
				}
				else if (x > 1170)
				{
					al_draw_bitmap(examen0, 1000, 20, NULL);
				}
				else
				{
					al_draw_bitmap(examen0, x - 180, 20, NULL);
				}

				if (al_key_down(&keyState, ALLEGRO_KEY_SPACE))
				{
					al_destroy_event_queue(event_queue); //Destruye la cola de eventos
					al_destroy_timer(timer); //Destruye el temporizador
					al_destroy_bitmap(jugador);
					al_destroy_sample(efectoSonido);
					al_destroy_sample(triste);
					actualCamara(cameraPosition, 0, -100, 32, 32);
					al_identity_transform(&camera);
					al_translate_transform(&camera, -cameraPosition[0], -cameraPosition[1]);
					al_use_transform(&camera);
					return 0;

				}
				al_flip_display(); //Actualiza la pantalla

			} while (1);
		}
		//Dependiendo si pasaste un examen te muestra una imagen
		if (examenes[0] == 1)
		{
			if (x < 365)
			{
				al_draw_bitmap(estructura, 10, 170, NULL);
			}
			else if (x > 1170)
			{
				al_draw_bitmap(estructura, 811, 170, NULL);
			}
			else
			{
				al_draw_bitmap(estructura, x - 357, 170, NULL);
			}
		}
		else
		{
			al_draw_bitmap_region(estructura, 0, 0, 64, 64, 400, 540, NULL);
			if (Collision(x, y, 400, 540, 32, 32)) //Activacion de operaciones
			{
				banderaOp = 1;
			}
		}
		//Dependiendo si pasaste un examen te muestra una imagen
		if (examenes[1] == 1)
		{

			if (x < 365)
			{
				al_draw_bitmap(estructura, 80, 170, NULL);
			}
			else if (x > 1170)
			{
				al_draw_bitmap(estructura, 881, 170, NULL);
			}
			else
			{
				al_draw_bitmap(estructura, x - 287, 170, NULL);
			}
		}
		else
		{
			al_draw_bitmap_region(estructura, 0, 0, 64, 64, 750, 540, NULL);
			if (Collision(x, y, 750, 540, 32, 32))
			{
				banderaOp = 2;
			}
		}
		//Dependiendo si pasaste un examen te muestra una imagen
		if (examenes[2] == 1)
		{

			if (x < 365)
			{
				al_draw_bitmap(estructura, 150, 170, NULL);
			}
			else if (x > 1170)
			{
				al_draw_bitmap(estructura, 951, 170, NULL);
			}
			else
			{
				al_draw_bitmap(estructura, x - 217, 170, NULL);
			}

		}
		else
		{
			al_draw_bitmap_region(estructura, 0, 0, 64, 64, 1000, 540, NULL);
			if (Collision(x, y, 1000, 540, 32, 32))
			{
				banderaOp = 3;
			}
		}
		//Si llegas a la meta, te muestra una imagen dependiendo cuantos examenes tuvieron
		if (Collision(x, y, 1400, 540, 32, 32))
		{
			al_destroy_sample(song);
			if (examenes[0] + examenes[1] + examenes[2] >= 1)
			{
				al_play_sample(feliz, 5.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, 0);
			}
			else
			{
				al_play_sample(triste, 8.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, 0);
			}
			do
			{
				al_get_keyboard_state(&keyState);
				if (examenes[0] + examenes[1] + examenes[2] == 3)
				{
					al_draw_bitmap(examen10, 970, 20, NULL);
				}
				else if (examenes[0] + examenes[1] + examenes[2] == 2)
				{
					al_draw_bitmap(examen8, 970, 20, NULL);
				}
				else if (examenes[0] + examenes[1] + examenes[2] == 1)
				{
					al_draw_bitmap(examen6, 970, 20, NULL);
				}
				else
				{
					al_draw_bitmap(examen0, 970, 20, NULL);
				}
				if (al_key_down(&keyState, ALLEGRO_KEY_SPACE))
				{
					al_destroy_event_queue(event_queue); //Destruye la cola de eventos
					al_destroy_timer(timer); //Destruye el temporizador
					al_destroy_bitmap(jugador);
					al_destroy_sample(efectoSonido);
					if (examenes[0] + examenes[1] + examenes[2] >= 1)
					{
						al_destroy_sample(feliz);
					}
					else
					{
						al_destroy_sample(triste);
					}
					actualCamara(cameraPosition, 0, -100, 32, 32);
					al_identity_transform(&camera);
					al_translate_transform(&camera, -cameraPosition[0], -cameraPosition[1]);
					al_use_transform(&camera);
					if (examenes[0] + examenes[1] + examenes[2] == 3)
					{
						return 3;
					}
					else if (examenes[0] + examenes[1] + examenes[2] == 2)
					{
						return 2;
					}
					else if (examenes[0] + examenes[1] + examenes[2] == 1)
					{
						return 1;
					}
					else
					{
						return 0;
					}


				}
				al_flip_display(); //Actualiza la pantalla

			} while (1);
		}
		al_set_sample_instance_playmode(songInstanceD, ALLEGRO_PLAYMODE_LOOP_ONCE);
		al_attach_sample_instance_to_mixer(songInstanceD, al_get_default_mixer());
		//Si colisionas con unos picos te regresas al inicio y pierdes una vida
		if (Collision(x, y, 295, 565, 48, 32) || Collision(x, y, 595, 565, 32, 32) || Collision(x, y, 895, 565, 32, 32) || Collision(x, y, 1125, 565, 32, 32))
		{
			al_play_sample_instance(songInstanceD);
			x = 80;
			y = 400;
			vidas--;
		}
		al_draw_bitmap(picos, 270, 560, 0);
		al_draw_bitmap(picos, 570, 560, 0);
		al_draw_bitmap(picos, 860, 560, 0);
		al_draw_bitmap(picos, 1100, 560, 0);
		al_draw_bitmap(jugador, x, y, NULL);
		al_flip_display(); //Actualiza la pantalla
	}
	al_destroy_event_queue(event_queue); //Destruye la cola de eventos
	al_destroy_timer(timer); //Destruye el temporizador
	al_destroy_bitmap(jugador);
	al_destroy_sample(efectoSonido);
	al_destroy_sample(song);
	al_destroy_sample_instance(songInstance);

	return 0;
}

