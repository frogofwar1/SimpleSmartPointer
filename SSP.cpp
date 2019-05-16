#include <iostream>
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>


using namespace std;



class Monster
{
private:
	char* m_name;
	int m_hp;
	int m_atk;
	

public:
	Monster() : m_name(0), m_hp(0), m_atk(0)
	{
	}
	Monster(char* t_name, int t_hp, int t_atk) : m_name(t_name), m_hp(t_hp), m_atk(t_atk)
	{
	}
	~Monster()
	{
	}

	void setName(char* t_name) {
		m_name = t_name;
		cout << "Name has been changed to " << m_name << endl;
	}

	void setHp(int t_hp) {
		m_hp = t_hp;
		cout << "Hp has been changed to " << m_hp << endl;
	}

	void setAtk(int t_atk) {
		m_atk = t_atk;
		cout << "Atk has been changed to " << m_atk << endl;
	}

	void Display()
	{
		cout << "Name = " << m_name << ", Hp = " << m_hp << ", Atk = " << m_atk << endl;
	}
};

class Hero
{
private:
	char* m_name;
	int m_hp;
	int m_atk;


public:
	Hero() : m_name(0), m_hp(0), m_atk(0)
	{
	}
	Hero(char* t_name, int t_hp, int t_atk) : m_name(t_name), m_hp(t_hp), m_atk(t_atk)
	{
	}
	~Hero()
	{
	}

	void setName(char* t_name) {
		m_name = t_name;
		cout << "Name has been changed to " << m_name << endl;
	}

	void setHp(int t_hp) {
		m_hp = t_hp;
		cout << "Hp has been changed to " << m_hp << endl;
	}

	void setAtk(int t_atk) {
		m_atk = t_atk;
		cout << "Atk has been changed to " << m_atk << endl;
	}

	void Display()
	{
		cout << "Name = " << m_name << ", Hp = " << m_hp << ", Atk = " << m_atk << endl;
	}
};



class ReferenceCount
{
private:
	int count;

public:
	void AddRef()
	{
		count++;
		cout << "Increased reference count.." << endl;
		cout << "Reference count = " << count << endl;
	}

	int Release()
	{
		--count;
		cout << "Decreased reference count.." << endl;
		cout << "Reference count = " << count << endl;
		return count;
	}
};



template < typename T > class SmartPointer
{
private:
	T*    pointerData;
	ReferenceCount* reference;

public:
	SmartPointer() : pointerData(0), reference(0)
	{
		reference = new ReferenceCount();
		reference->AddRef();
	}

	SmartPointer(T* t_pointerData) : pointerData(t_pointerData), reference(0)
	{
		reference = new ReferenceCount();
		reference->AddRef();
	}

	SmartPointer(const SmartPointer<T>& t_sp) : pointerData(t_sp.pointerData), reference(t_sp.reference)
	{
		reference->AddRef();
	}

	~SmartPointer()
	{
		if (reference->Release() == 0)
		{
			delete pointerData;
			delete reference;
			cout << "Released memory!" << endl;
		}
	}

	T& operator* ()
	{
		return *pointerData;
	}

	T* operator-> ()
	{
		return pointerData;
	}

	SmartPointer<T>& operator = (const SmartPointer<T>& t_sp)
	{
		if (this != &t_sp)
		{
			if (reference->Release() == 0)
			{
				delete pointerData;
				delete reference;
				cout << "Released memory!" << endl;
			}

			pointerData = t_sp.pointerData;
			reference = t_sp.reference;
			reference->AddRef();
		}
		return *this;
	}
};


void main()
{

	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	{
		SmartPointer<Monster> p1_slime(new Monster((char*)"Slime", 50, 10));
		cout << "P1_slime : ";
		p1_slime->Display();
		{
			SmartPointer<Monster> p2_slime = p1_slime;
			p2_slime->setAtk(30);
			cout << "P2_slime : ";
			p2_slime->Display();

			SmartPointer<Monster> p3_slime = p1_slime;
			p3_slime->setHp(100);
			cout << "P3_slime : ";
			p3_slime->Display();
		}
		p1_slime->setName((char*)"GSlime");
		cout << "P1_slime : ";
		p1_slime->Display();
	}

	{
		SmartPointer<Hero> p1_Hero = (new Hero((char*)"John", 300, 50));
		p1_Hero->Display();
	}

	getchar();
}