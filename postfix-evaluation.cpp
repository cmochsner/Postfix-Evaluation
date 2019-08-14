#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool isBalanced(string exp);
double operand(char op, double num1, double num2);

template<class T>
struct node
{
	T item;
	struct node<T> *next;
};
template<class T>
class stack
{
	private:
		struct node<T> *top;
	public:
		stack()
		{
			top = NULL;
		}
		T getTop();
		T pop();
		void push(T el);
		bool isEmpty();
		void print();
};
template<class T>
T stack<T>::getTop()
{
	T item = {};
	if (top != NULL)
	{
		item=top->item;
	}
	return item;
}
template<class T>
T stack<T>::pop()
{
	T item = {};
	if (top == NULL)
	{
		cout << "Stack is empty. Cannot delete." << endl;
		return item;
	}
	else
	{
		item = top->item;

		struct node<T>* temp = top;
		top = top->next;

		free(temp);
	}

	return item;
}
template<class T>
void stack<T>::push(T el)
{
	if (top == NULL)
	{
		top = new node<T>;
		top->item = el;
		top->next = NULL;
		return;
	}
	struct node<T> * newnode = new node<T>;

	newnode->item = el;
	newnode->next = top;
	top = newnode;
}
template<class T>
bool stack<T>::isEmpty()
{
	if (top == NULL)
	{
		return true;
	}
	return false;
}
template<class T>
void stack<T>::print()
{
	struct node<T>* current = top;
	while (current != NULL)
	{
		cout << current->item << " ";
		current = current->next;
	}
	cout << endl;
}

int isOperand(char ch)
{
	int number = ch - '0';
	return (number >= 0 && number <= 9);
}

int Prec(char ch)
{
	switch (ch)
	{
		case '*':
			return 2;
		case '/':
			return 2;
		case '+':
		case '-':
			return 1;
	}
	return -1;
}

string infixToPostfix(string exp)
{
	stack <char> s;
	int length = exp.length();
	string postfix;
	for (int i = 0; i < length; i++)
	{
		if (isOperand(exp[i]))
		{
			postfix = postfix + exp[i];
		}
		else if (exp[i] == '(' || exp[i] == '[' || exp[i] == '{')
		{
			s.push(exp[i]);
		}
		else if (!s.isEmpty() && (exp[i] == ')' || exp[i] == ']' || exp[i] == '}'))
		{
			while (!s.isEmpty() && (s.getTop() != '('&&s.getTop() != '['&&s.getTop() != '{'))
			{
				postfix = postfix + s.pop();
			}
			s.pop();
		}
		else if (exp[i] == '+' || exp[i] == '-' || exp[i]=='/' || exp[i]=='*')
		{
			if (i == 0 && exp[i] == '+')
			{
				i++;
			}
			while ((!s.isEmpty() && Prec(s.getTop()) >= Prec(exp[i]) && s.getTop() != '('&& s.getTop() != '['&& s.getTop() != '{'))
			{
				postfix = postfix + s.pop();
			}
			s.push(exp[i]);
		}
	}
	while (!s.isEmpty())
	{
		postfix = postfix + s.pop();
	}
	return postfix;
}

double postfixEval(string exp)
{
	stack<double> s;

	int i = 0;
	int length = exp.length();

	double ans = 0.0;

	while (i < length)
	{
		if (exp[i] != '+' && exp[i] != '-' && exp[i] != '/' && exp[i] != '*')
		{
			double num = exp[i] - '0';
			if (isOperand(exp[i]))
			{
				s.push(num);
			}
		}
		else
		{
			double num1, num2;
			if (!s.isEmpty())
			{
				num1 = s.pop();
			}
			if (!s.isEmpty())
			{
				num2 = s.pop();
			}
			s.push(operand(exp[i], num1, num2));
		}
		i++;
	}

	if (!s.isEmpty())
	{
		ans=s.pop();
	}
	
	return ans;
}
double operand(char op, double num1, double num2)
{
	double sol;
	switch (op)
	{
		case '-':
			sol = num2 - num1;
			break;
		case '+':
			sol = num2 + num1;
			break;
		case '/':
			sol = num2 / num1;
			break;
		case '*':
			sol = num2 * num1;
			break;
		default:
			cout << "Invalid operand" << endl;
			break;
	}

	return sol;
}
int main()
{
	bool equal = true;
	string exp = "";

	cout << "Welcome to the postfix evaluation program! Enter -1 to exit." << endl;

	while (exp != "-1")
	{
		cout << "\nEnter the expression you'd like to evaluate." << endl;
		cin >> exp;

		if (exp == "-1")
		{
			break;
		}

		bool error = false;

		if (exp.length() < 1)
		{
			continue;
		}
		if (!isBalanced(exp))
		{
			cout << "Expression is not balanced. Cannot be evaluated." << endl;
			error = true;
		}

		if (!error)
		{
			string postfix;
			double ans;

			postfix = infixToPostfix(exp);
			cout << "Postfix Expression: " << postfix << endl;
			ans = postfixEval(postfix);
			cout << "Evaluated Expression: " << ans << endl;
		}
	}
	//system("pause");
	return 0;
}

bool isBalanced(string exp)
{
	stack<char> s;
	int i = 0;
	int length = exp.length();
	while (i < length)
	{
		switch (exp[i])
		{
			case '(':
			case '{':
			case '[':
				s.push(exp[i]);
				break;
			case ')':
				if ('(' == s.getTop())
				{
					s.pop();
				}
				else
				{
					return false;
				}
				break;
			case '}':
				if ('{' == s.getTop())
				{
					s.pop();
				}
				else
				{
					return false;
				}
				break;
			case ']':
				if ('[' == s.getTop())
				{
					s.pop();
				}
				else
				{
					return false;
				}
				break;
			default:
				break;
		}
		i++;
	}
	if (s.isEmpty())
	{
		return true;
	}
	return false;
}