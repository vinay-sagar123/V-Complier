#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

enum SyntexKind
{
	EndoffileToken,
	Numbertoken,
	whitespaceToken,
	PlusToken,
	minusToken,
	MultiplyToken,
	divisionToken,
	badToken,
	openparenthasisToken,
	closeparenthasisToken,
};

class SyntaxToken
{
public:
	SyntexKind Kind;
	int Position;
	string Text;
	int Value;


	SyntaxToken(SyntexKind kind, int position, string text, int value)
	{
		Kind = kind;
		Position = position;
		Text = text;
		Value = value;
	}
};

inline const char* ToString(SyntexKind color) {
	if (color == 0)
	{
		return "EndoffileToken";
	}
	if (color == 1)
	{
		return "Numbertoken";
	}
	if (color == 2)
	{
		return "whitespaceToken";
	}
	if (color == 3)
	{
		return "PlusToken";
	}
	if (color == 4)
	{
		return "minusToken";
	}
	if (color == 5)
	{
		return "MultiplyToken";
	}
	if (color == 6)
	{
		return "divisionToken";
	}
	if (color == 7)
	{
		return "BadToken";
	}
	if (color == 8)
	{
		return "openparenthasisToken";
	}
	if (color == 9)
	{
		return "closeparenthasisToken";
	}
}

class lexar
{

public:
	string string_text;
	int _position = 0;
	lexar(string text)
	{
		string_text = text;
	}
	char current()
	{
		return string_text[_position];
	}

	void Next()
	{
		_position++;
	}

	SyntaxToken NextToken()
	{
		// <number> 
		// + - * / ( ) 
		// whitespaces
		if (_position >= string_text.length())
		{
			SyntexKind kk = EndoffileToken;
			SyntaxToken object(kk, _position, "", NULL);
			return object;
		}


		if (isdigit(current()))
		{
			int start = _position;
			while (isdigit(current()))
				Next();

			int lenght = _position - start;
			string text = string_text.substr(start, lenght);
			int value = stoi(text);
			SyntaxToken object(SyntexKind::Numbertoken, start, text, value);
			return object;
		}

		if (isspace(current()))
		{
			int start = _position;

			while (isspace(current()))
				Next();

			int length = _position - start;
			string text = string_text.substr(start, length);
			SyntexKind kk = whitespaceToken;
			SyntaxToken object(kk, _position, text, NULL);
			return object;
		}

		if (current() == '+')
		{
			SyntexKind kk = PlusToken;
			SyntaxToken object(kk, _position++, "+", NULL);
			return object;
		}

		else if (current() == '-')
		{
			SyntexKind kk = minusToken;
			SyntaxToken object(kk, _position++, "-", NULL);
			return object;
		}
		else if (current() == '*')
		{
			SyntexKind kk = MultiplyToken;
			SyntaxToken object(kk, _position++, "*", NULL);
			return object;
		}
		else if (current() == '/')
		{
			SyntexKind kk = divisionToken;
			SyntaxToken object(kk, _position++, "/", NULL);
			return object;
		}

		else if(current() == '(')
		{
			SyntexKind kk = openparenthasisToken;
			SyntaxToken object(kk, _position++, "(", NULL);
			return object;
		}
		else if (current() == ')')
		{
			SyntexKind kk = closeparenthasisToken;
			SyntaxToken object(kk, _position++, ")", NULL);
			return object;
		}
		else
		{
			SyntexKind kk = badToken;
			SyntaxToken object(kk, _position++, "", NULL);
			return object;
		}
	}
};

class Parsor
{
public:
	vector<SyntaxToken> tokens;
	Parsor(string text)
	{
		lexar Lexar(text);
		SyntaxToken token = Lexar.NextToken();
		do
		{
			SyntaxToken token = Lexar.NextToken();
			if (token.Kind != 2 && token.Kind != 7)
			{
				tokens.push_back(token);
			}
		} while (token.Kind != 0);
	}
};

void main()
{
	while (true)
	{
		cout << "> ";
		string line;
		getline(cin, line);

		
		if (line.empty())
			return;
		
		lexar lexa(line);
		while(true)
		{
			SyntaxToken token = lexa.NextToken();
			//cout << token.Text << endl;
			SyntexKind kin = token.Kind;
			if (kin == 0)
				break;
			//cout<< endl;
			cout << ToString(kin) << ":" <<"'"<< token.Text <<"'"<< " " << token.Value << endl;
		}

	}
	return;
}

