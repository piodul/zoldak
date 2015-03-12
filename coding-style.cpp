#include <utility>
#include <string>

//Put spaces around pointers and references
int main(int argc, char ** argv)
{
	//Use tabs for indentation

	//Use english names typed in CamelCase (for types)
	//or camelCase (for functions and variables)
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

	//When default ctors and dtors suffice and you want
	//to be explicit about it, use the C++11 "default" notation
	struct SimpleClass
	{
		SimpleClass() = default;
		~SimpleClass() = default;
	}

	//Put braces in separate lines
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

	//The exceptions are empty or simple one-liner functions,
	//which can be formatted in the following way
	struct A
	{
		void doNothing() {}

		static int getTheUltimateAnswer()
		{ return 42; }
	};


	//...as well as initializer lists
	std::pair<double, double> position {
		34.0, 85.0
	};

	//..and namespaces
	//namespace Foo {
	//...
	//}

	//There's no preset limit on line length,
	//but try to be reasonable about it

	//Split long declarations and function calls
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
		"Lorem ipsum ",
		"dolor sit amet, ",
		"consectetur adipiscing elit"
	);

	return 0;
}

//Don't indent the first level of namespace content
namespace Foo {
static const unsigned int THE_ULTIMATE_ANSWER = 42;
}

//When in doubt - use Common Sense™ and stay consistent.
//Don't hesitate to ask or propose extensions to this guideline.
