#include <iostream>
#include <string>

using namespace std;

class Animal
{
protected:
	string sound;

public:
	Animal()
	{
		sound = "Unknown sound";
		cout << "Animal()\n";
	}

	virtual ~Animal()
	{
		cout << "~Animal()\n";
	}

	virtual string Sound()
	{
		return sound;
	}

	virtual string Class_name()
	{
		return "Animal";
	}
	
	virtual bool isA(string name)
	{
		return (name == "Animal");
	}
};

class Cat : public Animal
{
public:
	Cat()
	{
		sound = "Mew";
		cout << "Cat()\n";
	}

	~Cat()
	{
		cout << "~Cat()\n";
	}

	string Sound()
	{
		return sound;
	}

	string Class_name()
	{
		return "Cat";
	}

	void Catch()
	{
		cout << "Catch()\n";
	}

	bool isA(string name)
	{
		return (name == "Cat" || Animal::isA(name));
	}
};

class Dog : public Animal
{
public:
	Dog()
	{
		sound = "Woof";
		cout << "Dog()\n";
	}

	~Dog()
	{
		cout << "~Dog\n";
	}

	string Sound()
	{
		return sound;
	}

	string Class_name()
	{
		return "Dog";
	}

	void Chase()
	{
		cout << "Chase()\n";
	}

	bool isA(string name)
	{
		return (name == "Dog" || Animal::isA(name));
	}
};

class WildDog : public Dog
{
public:
	WildDog()
	{
		sound = "GRRR";
		cout << "WildDog()\n";
	}

	~WildDog()
	{
		cout << "~WildDog\n";
	}

	string Sound()
	{
		return sound;
	}

	string Class_name()
	{
		return "WildDog";
	}

	bool isA(string name)
	{
		return (name == "WildDog" || Dog::isA(name));
	}
};

class Base
{
public:
	int x, y;
	Base()
	{
		cout << "Base()\n";
		x = 0;
		y = 0;
	}
	Base(Base* obj)
	{
		cout << "Base(Base* obj)\n";
		x = obj->x;
		y = obj->y;
	}
	Base(Base& obj)
	{
		cout << "Base(Base& obj)\n";
		x = obj.x;
		y = obj.y;
	}
	virtual ~Base() 
	{
		cout << "~Base(" << x << ", " << y << ")\n";
	}
};

class Desc : public Base
{
public:
	int z;
	Desc() : Base()
	{
		cout << "Desc()\n";
		z = 0;
	}
	Desc(Desc* obj) : Base(obj)
	{
		cout << "Desc(Desc* obj)\n";
		z = obj->z;
	}
	Desc(Desc& obj)	: Base(obj)
	{
		cout << "Desc(Desc& obj)\n";
		z = obj.z;
	}
	~Desc()
	{
		cout << "~Desc()\n";
	}
};

int Func1(Base b)
{
	return (b.x + b.y);
}

int Func2(Base* b)
{
	return (b->x * b->y);
}

int Func3(Base& b)
{
	return (b.x / b.y);
}

int main()
{
	//	calling constructors and virtual methods
	const int n = 10;
	Animal *a[n];

	//	checking if object belongs to class
	for (int i = 0; i < n; ++i)
	{
		cout << i << '\n';
		int r = rand() % 4;
		if (!r)
			a[i] = new Animal();
		else if (r == 1)
			a[i] = new Cat();
		else if (r == 2)
			a[i] = new Dog();
		else
			a[i] = new WildDog();
	}
	cout << "\n\n";

	//	unsafe cast
	for (int i = 0; i < n; ++i)
	{
		((Cat*)a[i])->Catch();
	}
	cout << "\n\n";

	//	safe cast
	for (int i = 0; i < n; ++i)
	{
		if (a[i]->Class_name() == "Cat")
			((Cat*)a[i])->Catch();
		else if (a[i]->Class_name() == "Dog" || a[i]->Class_name() ==
			"WildDog")
			((Dog*)a[i])->Chase();
		else
			cout << "...\n";
	}
	getchar();
	system("cls");

	//	isA
	for (int i = 0; i < n; ++i)
	{
		cout << i << ' ';
		if (a[i]->isA("Dog"))
			((Dog*)a[i])->Chase();
		else if (a[i]->isA("Cat"))
			((Cat*)a[i])->Catch();
		else
			cout << "...\n";
	}
	cout << "\n\n";

	//	dynamic cast
	for (int i = 0; i < n; ++i)
	{
		cout << i << ' ';
		if (dynamic_cast<Dog*>(a[i]) != NULL)
			((Dog*)a[i])->Chase();
		else if (dynamic_cast<Cat*>(a[i]) != NULL)
			((Cat*)a[i])->Catch();
		else
			cout << "...\n";
		delete a[i];
	}
	getchar();
	system("cls");

	//	passing objects as parameters to functions
	{
		Base b1;
		Base* b2 = new Base(&b1);
		Base* b3 = new Base(*b2);
		b1.x = 1;
		b1.y = 2;
		b2->x = 3;
		b2->y = 4;
		b3->x = 5;
		b3->y = 6;
		//	Func1(Base obj) works with object's copy 
		cout << Func1(b1) << '\n';
		cout << Func2(b2) << '\n';
		cout << Func3(*b3) << '\n';
		delete b2;
		delete b3;
	}
	getchar();
	system("cls");

	Desc d1;
	Desc* d2 = new Desc(&d1);
	Desc* d3 = new Desc(*d2);
	d1.x = 1;
	d1.y = 2;
	d2->x = 3;
	d2->y = 4;
	d3->x = 5;
	d3->y = 6;

	cout << Func1(d1) << '\n';
	cout << Func2(d2) << '\n';
	cout << Func3(*d3) << '\n';
	delete d2;
	delete d3;
}
