#include <stdio.h>
#include <conio.h>
#include <Windows.h>

struct Slup
{
	int x = 0;
	int y = 0;
	int szerokosc = 0;
	int gap_size = 0;
	int move_x = 0;
	int gap_pos_y = 0;
};

struct Bird
{
	int x = 0;
	int y = 0;
	int jump_height = 0;
	int gravity = 0;
	int radius = 0;
};


void hidecursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}
	
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void arena(const int arena_x, const int arena_y)
{
	
	for (int i = 1; i < arena_y; i++)
	{
		for (int j = 1; j < arena_x; j++)
		{
			gotoxy(j, i);
			if (((j == 1) or (j == arena_x - 1)) or ((i == 1) or (i == arena_y - 1)))
			{
				printf("=");
				
			}
		}
		printf("\n");
	}
	
}

void set_slup(struct Slup *slup, const int arena_y)
{
	slup->x = 44;
	slup->y = 2;
	slup->szerokosc = 2;
	slup->gap_size = 5;
	slup->gap_pos_y = rand() % ((arena_y - 15) +6);

	
}

void set_bird(struct Bird *bird, const int arena_x, const int arena_y)
{
	bird->x = arena_x / 3;
	bird->y = arena_y / 2;
	bird->radius = 2;
	bird->gravity = -1;
	bird->jump_height = 2;

}
void czysc(const int arena_y, const int arena_x)
{
	for (int i = 2; i < arena_y-1; i++)
	{
		for(int j = 2; j < arena_x-1; j++)
		{
		gotoxy(j, i);
		printf(" ");
	
		}
	}
}

void generowanie_slupa(struct Slup slup, const int arena_y, const int arena_x)
{
	gotoxy(slup.x, slup.y);

	for (int y = slup.y ; y < arena_y-1; y++)
	{
		for (int x = slup.x; x < (slup.x + slup.szerokosc); x++)
		{
			gotoxy(x , y);
			if (y >= slup.gap_pos_y and y <= slup.gap_pos_y + slup.gap_size)
			{
				
				printf(" ");
			} else
			printf("*");

		}
		printf("\n");
	}
}

void generowanie_ptaka(struct Bird bird, const int arena_x, const int arena_y)
{
	gotoxy(bird.x, bird.y);
	
	
	for (int y = bird.y - bird.radius; y < bird.y + bird.radius; y++)
	{
		for (int x = bird.x - bird.radius ; x < bird.x + bird.radius+1; x++)  //dodaje 1, aby był kwadrat(rozna wysokosc komorek x i y)
		{
			gotoxy(x, y);
			printf("#");
		}
		printf("\n");
	}

}

void pokaz_punkty(int punkt)
{
	gotoxy(55, 2);
	printf("Punkty: %i", punkt);
		
}

void game_over(const int arena_x, const int arena_y, int punkt)
{
	gotoxy(arena_x / 2.5, arena_y / 2);
	printf("GAME OVER");
	gotoxy((arena_x / 2.5) -3, (arena_y / 2) + 2);
	printf("Twoje Punkty: %i", punkt);
	gotoxy(arena_x, arena_y);
	arena(arena_x, arena_y);
	gotoxy((arena_x / 2.5) - 3, (arena_y - 6));
	printf("1. GRAJ PONOWNIE\n");
	gotoxy((arena_x / 2.5)- 3, (arena_y - 5));
	printf("2. WYJSCIE \n");
	gotoxy(arena_x, arena_y);
	
}

void logo(const int arena_x, const int arena_y, int czas = 50)
{
	//======================LOGO=============================================
	arena(arena_x, arena_y);
	gotoxy(2, (arena_y/ 2) - 4);
	printf("               AA \n"); Sleep(czas);
	printf(" =             .'  `. \n"); Sleep(czas);
	printf(" =           .'      `. \n"); Sleep(czas);
	printf(" =          <          > \n"); Sleep(czas);
	printf(" =           `.      .' \n"); Sleep(czas);
	printf(" =             `.  .' \n"); Sleep(czas);
	printf(" =               VV \n"); Sleep(czas);
	gotoxy(27, (arena_y / 2));
	printf("JUMPING");
	gotoxy(27, (arena_y / 2) + 1);
	printf("BOX");
}
void menu(const int arena_x, const int arena_y)
{
	arena(arena_x, arena_y);
	gotoxy((arena_x / 2)-3, arena_y / 2);
	printf("MENU");
	gotoxy((arena_x / 2.5) -2, (arena_y / 2) + 2);
	printf("1. GRAJ \n");
	gotoxy((arena_x / 2.5) - 2, (arena_y / 2) + 4);
	printf("2. WYJSCIE \n");
	gotoxy(arena_x, arena_y);
}

int main()
{
	
	char choice;
	char klawa;
	const int arena_x = 50;
	const int arena_y = 25;
	struct Slup slup;
	struct Bird bird;
	int punkt = 0;
	
	hidecursor();

	logo(arena_x, arena_y);
	Sleep(1000);
	czysc(arena_y, arena_x);
	
	set_slup(&slup, arena_y);
	set_bird(&bird, arena_x, arena_y);

	menu(arena_x, arena_y);
	
	choice = _getch();
		
		while (choice != '1' && choice != '2')
		{
			menu(arena_x, arena_y);
			choice = _getch();
		}
			
			while (choice == '2')
			{
				return 0;
			}

	while (choice == '1')
	{
		arena(arena_x, arena_y);
		czysc(arena_y, arena_x);
		generowanie_slupa(slup, arena_y, arena_x);
		generowanie_ptaka(bird, arena_x, arena_y);
		pokaz_punkty(punkt);
		
		if (slup.x < 2)			//generowanie słupa na początku, gdy dojdzie do końca
		{
			czysc(arena_y, arena_x);
			arena(arena_x, arena_y);
			set_slup(&slup, arena_y);
			generowanie_slupa(slup, arena_y, arena_x);
			generowanie_ptaka(bird, arena_x, arena_y);
		}
		else             //jeżeli mieści się w granicach areny to pętla idzie dalej
		{
			slup.x -= 1;             //przesuwanie słupa
			bird.y -= bird.gravity; //opadanie ptaka

			Sleep(1);

				if (_kbhit())  //skakanie ptaka
				{
					klawa = _getch();
					if (klawa == ' ')
					{
						bird.y -= bird.jump_height;
					}
				}

				if ((bird.y == arena_y - 2) or (bird.y < 4) or (bird.x == slup.x-bird.radius
					and ((bird.y > slup.gap_pos_y+slup.gap_size) or (bird.y < slup.gap_pos_y+bird.radius)))) //kolizje
				{
					system("cls");					
					game_over(arena_x, arena_y, punkt);
					set_bird(&bird, arena_x, arena_y);
					set_slup(&slup, arena_y);
					punkt = 0;
					choice = _getch();
					

					while (choice != '1' && choice != '2')    //wybor game_over, czy grac dalej
					{
						game_over(arena_x, arena_y, punkt);
						choice = _getch();
					}
					if (choice == '2')			//wyjście
					{
						return 0;
					}
					

				}

				if (bird.x - bird.radius * 2 == slup.x + slup.szerokosc)  //jeżeli ptak przejdzie przez słup to dodaj punkt
				{
					punkt += 1;
				}
		}				
	}	
}
