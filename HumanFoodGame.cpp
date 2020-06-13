#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

class GameObject {
protected:
	int distance;
	int x, y;
public:
	GameObject(int startX, int startY, int distance) {
		this->x = startX;
		this->y = startY;
		this->distance = distance;

	}

	virtual ~GameObject() {};

	virtual void move() = 0;
	virtual char getShape() = 0;

	int getX() { return x; }
	int getY() { return y; }
	bool collide(GameObject *p) {
		if (this->x == p->getX() && this->y == p->getY())
			return true;
		else
			return false;

	}
};
class Game :public GameObject {
public:
	Game(int a, int b, int c) :GameObject(a, b, c) {}
	//GameObject는 추상클래스라서 객체를 만들지 못한다.
	//따라서 생성자를 명시적으로 만들어 파생클래스의 객체를 정상적으로 만들 수 있도록 했다.
	int who = 0;//getShape() 안에서 객체를 식별하기 위해 필요한 정수형 변수이다.
	
	static int random; //Monster와 Food의 이동방향을 랜덤으로 설정하기 위해 필요함.
	static int forfood;//Food는 5번 중 2번만 움직이는데, 이를 표현하기 위해 필요함.
	static char user;//user가 입력하는 asdf를 받아내기 위해 필요함.
	
	char getShape() {
		if (this->who == 1)
			return 'H';
		else if (this->who == 2)
			return 'M';
		else if (this->who == 3)
			return '@';
	}
	void move() {
		if (this->getShape() == 'H') {
			switch (user) {
			case 'a':
				if (this->x <= 0) { cout << "불가능합니다." << endl; }
				else { this->x--; }
				break;

			case 's':
				if (this->y >= 19) { cout << "불가능합니다." << endl; }
				else { this->y++; }
				break;

			case 'd':
				if (this->y == 0) { cout << "불가능합니다." << endl; }
				else { this->y--; }
				break;

			case 'f':
				if (this->x == 9) { cout << "불가능합니다." << endl; }
				else { this->x++; }
				break;

			default:
				cout << "잘못된 문자를 입력하셨습니다~ㅠㅠ" << endl;
				cout << endl;
				break;
			}
		}
		else if (this->getShape() == 'M') {
			switch (random) {
			case 0:
				if (this->x == 0 || this->x == 1)
					this->x += 2;
				else
					this->x -= 2;
				break;

			case 1:
				if (this->x == 8 || this->x == 9)
					this->x -= 2;
				else
					this->x += 2;
				break;

			case 2:
				if (this->y == 0 || this->y == 1)
					this->y += 2;
				else
					this->y -= 2;
				break;

			case 3:
				if (this->y == 18 || this->y == 19)
					this->y -= 2;
				else
					this->y += 2;
				break;
			}
		}

		else if (this->getShape() == '@') {
			if (forfood % 2 == 1) {
				forfood++;
			}
			else if (forfood % 2 == 0) {
				switch (random) {
				case 0:
					if (this->x == 0)
					{
						this->x++;
						forfood++;
					}
					else
					{
						this->x--;
						forfood++;
					}
						
					break;

				case 1:
					if (this->x == 9)
					{
						this->x--;
						forfood++;
					}
					else
					{
						this->x++;
						forfood++;
					}
					break;

				case 2:
					if (this->y == 0)
					{
						this->y++;
						forfood++;
					}
					else
					{
						this->y--;
						forfood++;
					}
					break;

				case 3:
					if (this->y == 19)
					{
						this->y--;
						forfood++;
					}
					else
					{
						this->y++;
						forfood++;
					}
					break;
				}
			}
		}
	}


};

int Game::random = 0;
int Game::forfood = 1;
char Game::user = ' ';

int main() {
	srand(time(NULL));
	char c[10][20];
	Game Human(rand()%20,rand()%10, 1);
	Game Mon(rand() % 20, rand() % 10, 2);
	Game Food(rand() % 20, rand() % 10, 1);
	Human.who = 1;
	Mon.who = 2;
	Food.who = 3; //getshape()함수 안에서 각 객체 식별에 필요한 who 변수를 각각 할당
	int hx = Human.getX();
	int hy = Human.getY();
	int mx = Mon.getX();
	int my = Mon.getY();
	int fx = Food.getX();
	int fy = Food.getY();
	int rf = 1;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 20; j++) {
			c[i][j] = '-';
		}
	}
	c[hy][hx] = 'H';
	c[my][mx] = 'M';
	c[fy][fx] = '@';
	cout << "** Human의 Food 먹기 게임을 시작합니다. **" << endl;
	while (rf == 1) {
		if (Human.collide(&Mon) == true || Food.collide(&Mon) == true)
		{
			cout << "졌습니다~ㅠㅠ" << endl;
			rf = 2;
		}
		else if (Human.collide(&Food) == true)
		{
			cout << "Human is winner!!" << endl;
			rf = 2;
		}
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 20; j++) {
				cout << c[i][j];
			}
			cout << endl;
		}
		cout << "왼쪽(a), 아래(s), 위(d), 오른쪽(f) >>";
		cin >> Game::user;
		Human.move();

		if (Human.collide(&Mon) == true || Food.collide(&Mon) == true)
		{
			cout << "졌습니다~ㅠㅠ" << endl;
			rf = 2;
		}
		else if (Human.collide(&Food) == true)
		{
			cout << "Human is winner!!" << endl;
			rf = 2;
		}

		Game::random = rand()%4;
		Mon.move();
		Game::random = rand()%4;
		Food.move();
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 20; j++) {
				c[i][j] = '-';
			}
		}
		int hx = Human.getX();
		int hy = Human.getY();
		int mx = Mon.getX();
		int my = Mon.getY();
		int fx = Food.getX();
		int fy = Food.getY();
		c[hy][hx] = 'H';
		c[my][mx] = 'M';
		c[fy][fx] = '@';
		
	}
	
}//메인함수 닫는 괄호