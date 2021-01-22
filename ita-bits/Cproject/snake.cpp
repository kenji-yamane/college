#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>


bool occupied[200][200], food[200][200];

void writech(int ch, int i, int j)
{
	move(i, j);
	addch(ch);
}

struct part
{
	int x;
	int y;
};

class Snake
{
public:
	part body[500];
	int life = 1;
	int movementState = 'w';
	void updateMovement()
	{
		int ch;
		
		if ((ch = getch()) != ERR && (ch == 'w' || ch == 'a' || ch == 's' || ch == 'd'))
			movementState = ch;
	}
	bool selfCollision()
	{
	    if (movementState == 'w' && occupied[body[0].x - 1][body[0].y] == true)
	        return true;
        else if (movementState == 'a' && occupied[body[0].x][body[0].y - 1] == true)
            return true;
        else if (movementState == 's' && occupied[body[0].x + 1][body[0].y] == true)
            return true;
        else if (movementState == 'd' && occupied[body[0].x][body[0].y + 1] == true)
            return true;
        
        return false;
	}
	void walk()
	{
		for (int i = life; i > 0; i--)
			body[i] = body[i - 1];
		
		if (movementState == 'w')
			body[0].x--;
		else if (movementState == 'a')
			body[0].y--;
		else if (movementState == 's')
			body[0].x++;
		else if (movementState == 'd')
			body[0].y++;
	}
	void showYourself()
	{
		for (int i = 0; i < life; i++)
			writech('o', body[i].x, body[i].y), occupied[body[i].x][body[i].y] = true;
	}
	void disappear()
	{
		for (int i = 0; i < life; i++)
			writech(' ', body[i].x, body[i].y), occupied[body[i].x][body[i].y] = false;
	}
};

int main()
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	srand(time(NULL));
	
	int h, w;
	bool game = true;
	getmaxyx(stdscr, h, w);

	//Creating the game's borders
	writech('*', 0, 0);
	writech('*', 0, w - 1);
	writech('*', h - 1, 0);
	writech('*', h - 1, w - 1);
	for (int i = 1; i < h - 1; i++)
		writech('|', i, 0), writech('|', i, w - 1);
	for (int i = 1; i < w - 1; i++)
		writech('-', 0, i), writech('-', h - 1, i);

	Snake s;
	s.body[0].x = h/2;
	s.body[0].y = w/2;
	while (game)
	{
		s.showYourself();
		refresh();
		usleep(200000/s.life);// - 1000*s.life);
		
		if (s.selfCollision())
		    game = false;
		s.disappear();	
		s.updateMovement();
		s.walk();

		if (food[s.body[0].x][s.body[0].y] == true)
			s.life++, food[s.body[0].x][s.body[0].y] = false;
		if (s.body[0].x == h || s.body[0].x == 0 || s.body[0].y == w || s.body[0].y == 0)
			game = false;
		
		int foodx = rand()%((h - 2) + 1);
		int foody = rand()%((w - 2) + 1);
		food[foodx][foody] = true;
		writech('+', foodx, foody);
	}

	endwin();

	return 0;
}
