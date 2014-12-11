#include <utility>
#include <string>

int main(int argc, char ** argv)
{
	//Wcinaj tabami.

	//Używaj angielskich, CamelCase'owych nazw.
	struct Person
	{
	private:
		const char * firstName;
		const char * surname;

	public:
		Person(const char * firstName, const char * surname)
			: firstName(firstName)
			, surname(surname)
		{}

		const char * getFirstName() const
		{
			return firstName;
		}

		const char * getSurname() const
		{
			return surname;
		}
	};

	//Umieszczaj klamry w osobnych liniach.
	if (true)
	{
		// ...
	}
	else
	{
		// ...
	}

	while (false)
	{

	}

	for (;;)
	{

	}

	auto l = [](int x) -> int
	{
		return x;
	};

	//Wyjątkiem są puste lub krótkie, jednolinijkowe funkcje,
	//które możesz formatować następująco...
	struct A
	{
		void doNothing() {}

		static int getTheUltimateAnswer()
		{ return 42; }
	};

	//...jak i również listy inicjujące...
	std::pair<double, double> position {
		34.0, 85.0
	};

	//...oraz namespace.
	//namespace Foo {
	//...
	//}

	//Nie ma ustalonego limitu na długość linii, lecz staraj się,
	//aby kod dał radę się zmieścić na połowie ekranu.

	//Rozbijaj długie deklaracje/wywołania funkcji.
	struct B
	{
		static std::string concatenate(
			const std::string & a,
			const std::string & b,
			const std::string & c
		)
		{
			return a + " " + b + " " + c;
		}
	};

	auto text = B::concatenate(
		"Ala ma kota.",
		"Kot ma pchły.",
		"Kot ma jedną, Ala trzy."
	);

	return 0;
}

//W namespace nie rób dodatkowych wcięć.
namespace Foo {
static const unsigned int THE_ULTIMATE_ANSWER = 42;
}

//W razie wątpliwości - użyj Zdrowego Rozsądku™ i bądź konsekwentny.
//(ewentualnie pytaj podczas game jamu)
