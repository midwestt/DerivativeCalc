#include <iostream>
#include <string>
#include <cctype>
#include <unordered_map>
#include <set>

// 2*x^100+100*x^2
// x^2+x
// 2*x^100+100*x^2

struct CoeffAndPower
{
	std::string coefficent;
	std::string power;
	std::string op;
};

using polynomial_t = std::vector<CoeffAndPower>;
//using polynomial_t = std::unordered_map<std::string, std::string>;

const std::set<char> OPERATORS = { '+', '-', '*', '/' };

bool findOperator(const char op)
{
	return OPERATORS.find(op) != OPERATORS.end();
}

polynomial_t parsePolynom(std::string polynomial)
{
	std::string coefficent;
	std::string power;
	bool isDigit = true;
	bool isPower = false;
	polynomial_t res;
	for (int i = 0; i < polynomial.size(); ++i)
	{
		if ((std::isdigit(polynomial[i]) || polynomial[i] == 'x') && isDigit)
		{
			coefficent += polynomial[i];
		}
		else if (polynomial[i] == '^')
		{
			isDigit = false;
			isPower = true;
			continue;
		}

		if (std::isdigit(polynomial[i]) && isPower)
		{
			power += polynomial[i];
		}

		if (polynomial[i] == '*' && polynomial[i + 1] == 'x')
		{
			continue;
		}

		if (OPERATORS.find(polynomial[i]) != OPERATORS.end() || i == polynomial.size() - 1)
		{
			if (coefficent.find('x') == std::string::npos)
				continue;

			isPower = false;
			isDigit = true;
			std::string op;
			if (i == polynomial.size() - 1)
				op = "";
			else
				op = polynomial[i];

			if (power == "")
				power = "1";

			CoeffAndPower cap{ coefficent, power, op };
			res.push_back(cap);

			coefficent = "";
			power = "";
		}
	}

	return res;
}

std::string derivative(std::string polynomial)
{
	polynomial_t polynom = parsePolynom(polynomial);

	int sum = 0;
	bool isFind = false;

	std::string res = "";

	for (int i = 0; i < polynom.size(); ++i)
	{
		std::string op = polynom[i].op;
		if (i == polynom.size() - 1)
		{
			op = "";
		}

        if (polynom[i].coefficent == "x" && polynom[i].power == "")
		{
			res += "1" + op;
			continue;
		}
		else if (polynom[i].coefficent == "x" && polynom[i].power != "")
		{
			if (polynom[i].power == "1")
			{
				res += polynom[i].power + op;
				continue;
			}

			std::string newPower = std::to_string(std::stoi(polynom[i].power) - 1);

			if (newPower != "1")
				res += polynom[i].power + "*x^" + newPower + op;
			else
				res += polynom[i].power + "*x" + op;

			continue;
		}

		int exp = std::stoi(polynom[i].coefficent) * std::stoi(polynom[i].power);

		std::string newPower = std::to_string(std::stoi(polynom[i].power) - 1);

		if (newPower != "1")
			res += std::to_string(exp) + "*x^" + newPower + op;
		else
			res += std::to_string(exp) + "*x" + op;
	}

	std::cout << res << std::endl;

	return res;
}

int main()
{
	derivative("x^2+x");
	derivative("2*x^100+100*x^2");
	derivative("x^10000+x+1");
	derivative("x+x+x+x+x+x+x+x+x+x");

	system("pause");
}