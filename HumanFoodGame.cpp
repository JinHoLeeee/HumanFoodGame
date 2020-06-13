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
	//GameObject�� �߻�Ŭ������ ��ü�� ������ ���Ѵ�.
	//���� �����ڸ� ��������� ����� �Ļ�Ŭ������ ��ü�� ���������� ���� �� �ֵ��� �ߴ�.
	int who = 0;//getShape() �ȿ��� ��ü�� �ĺ��ϱ� ���� �ʿ��� ������ �����̴�.
	
	static int random; //Monster�� Food�� �̵������� �������� �����ϱ� ���� �ʿ���.
	static int forfood;//Food�� 5�� �� 2���� �����̴µ�, �̸� ǥ���ϱ� ���� �ʿ���.
	static char user;//user�� �Է��ϴ� asdf�� �޾Ƴ��� ���� �ʿ���.
	
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
				if (this->x <= 0) { cout << "�Ұ����մϴ�." << endl; }
				else { this->x--; }
				break;

			case 's':
				if (this->y >= 19) { cout << "�Ұ����մϴ�." << endl; }
				else { this->y++; }
				break;

			case 'd':
				if (this->y == 0) { cout << "�Ұ����մϴ�." << endl; }
				else { this->y--; }
				break;

			case 'f':
				if (this->x == 9) { cout << "�Ұ����մϴ�." << endl; }
				else { this->x++; }
				break;

			default:
				cout << "�߸��� ���ڸ� �Է��ϼ̽��ϴ�~�Ф�" << endl;
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
	Food.who = 3; //getshape()�Լ� �ȿ��� �� ��ü �ĺ��� �ʿ��� who ������ ���� �Ҵ�
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
	cout << "** Human�� Food �Ա� ������ �����մϴ�. **" << endl;
	while (rf == 1) {
		if (Human.collide(&Mon) == true || Food.collide(&Mon) == true)
		{
			cout << "�����ϴ�~�Ф�" << endl;
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
		cout << "����(a), �Ʒ�(s), ��(d), ������(f) >>";
		cin >> Game::user;
		Human.move();

		if (Human.collide(&Mon) == true || Food.collide(&Mon) == true)
		{
			cout << "�����ϴ�~�Ф�" << endl;
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
	
}//�����Լ� �ݴ� ��ȣ