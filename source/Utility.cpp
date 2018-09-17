# include "Utility.h"
#include "Keywords.h"

bool Utility::isValidVariableName(string s) {
	return regex_match(s, regex("^[a-zA-Z][a-zA-Z0-9]*?$"));
}

bool Utility::isInteger(string s)
{
	return s.find_first_not_of("0123456789") == std::string::npos;
	/*std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();*/
}

vector<string> Utility::splitByDelimiter(string s, string delimiter)
{
	size_t pos = 0;
	string token;
	vector<string> vector = {};
	while ((pos = s.find(delimiter)) != string::npos) {
		token = s.substr(0, pos);
		vector.push_back(trim_copy(token));
		s.erase(0, pos + delimiter.length());
	}
	vector.push_back(trim_copy(s));
	return vector;
}

vector<string> Utility::splitByRegex(string s, regex delimiters)
{
	vector<string> vector = {};
	auto words_begin = sregex_iterator(s.begin(), s.end(), delimiters);
	auto words_end = sregex_iterator();
	for (std::sregex_iterator i = words_begin; i != words_end; ++i)
		vector.push_back((*i).str());
	return vector;
}

string Utility::convertInfixToPostfix(string infix)
{
	stack<char> operator_stack;
	stringstream output;

	for (unsigned i = 0; i < infix.length(); i++) {
		if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '^') {
			while (!operator_stack.empty() && priority(operator_stack.top()) <= priority(infix[i])) {
				output << operator_stack.top();
				operator_stack.pop();
			}
			operator_stack.push(infix[i]);
		}
		else if (infix[i] == '(') {
			operator_stack.push(infix[i]);
		}
		else if (infix[i] == ')') {
			while (operator_stack.top() != '(') {
				output << operator_stack.top();
				operator_stack.pop();
			}
			operator_stack.pop();
		}
		else {
			output << infix[i];
		}
	}

	while (!operator_stack.empty()) {
		output << operator_stack.top();
		operator_stack.pop();
	}

	return output.str();
}

int Utility::priority(char a) {
	int temp;
	if (a == '^')
		temp = 1;
	else  if (a == '*' || a == '/')
		temp = 2;
	else  if (a == '+' || a == '-')
		temp = 3;
	return temp;
}

bool Utility::validateInfixExpression(string expression)
{
	int previous = 0;
	int previous1 = 0;
	string expEvaluated = "";
	int operatorOperand = 1;

	for (int i = 0; i < expression.length(); i++)
	{
		char c = expression[i];
		if (c != ')') {
			if (c == '(')
			{
				int j = expression.find(')', i);
				if (j == -1)
					return false;

				string substring = expression.substr(i + 1, j - i - 1);

				while (count(substring.begin(), substring.end(), '(') != count(substring.begin(), substring.end(), ')'))
				{
					if (j < expression.length() - 1)
						j = expression.find(')', j + 1);
					else
						break;

					substring = expression.substr(i + 1, j - i - 1);
				}

				i = j - 1; //Changing the counter i to point to the next character
				//validating the sub expression
				if (validateInfixExpression(substring) == true)
				{
					if (previous != 0 && previous1 != 0 && previous > previous1)
					{
						previous1 = operatorOperand;
						operatorOperand++;
						previous = 0;
					}
					else if (previous != 0 && previous1 != 0 && previous <= previous1)
					{
						return false;
					}
					else if (previous1 != 0)
					{
						return false;
					}
					else
					{
						previous1 = operatorOperand;
						operatorOperand++;
					}
				}
				else
				{
					return false;
				}
			}
			else
				if (c == '+'
					|| c == '-'
					|| c == '*'
					|| c == '/'
					|| c == '%')
				{
					if (previous != 0)
					{
						return false;
					}
					previous = operatorOperand;
					operatorOperand++;
				}
				else
				{
					if (previous != 0 && previous1 != 0 && previous > previous1)
					{
						previous1 = operatorOperand;
						operatorOperand++;
						previous = 0;
					}
					else if (previous != 0 && previous1 != 0 && previous <= previous1)
					{
						return false;
					}
					else if (previous1 != 0)
					{
						return false;
					}
					else
					{
						previous1 = operatorOperand;
						operatorOperand++;
					}
				}
		}
	}
	if (previous != 0)
		return false;
	return true;
}

// trim from start (in place)
void Utility::ltrim(string &s) {
	s.erase(s.begin(), find_if(s.begin(), s.end(), [](int ch) {
		return !isspace(ch);
	}));
}

// trim from end (in place)
void Utility::rtrim(string &s) {
	s.erase(find_if(s.rbegin(), s.rend(), [](int ch) {
		return !isspace(ch);
	}).base(), s.end());
}

// trim from both ends (copying)
string Utility::trim_copy(string s) {
	ltrim(s);
	rtrim(s);
	return s;
}