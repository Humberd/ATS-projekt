#include "QueryParser.h"



QueryParser::QueryParser()
{
}


QueryParser::~QueryParser()
{
}

vector<vector<string>> QueryParser::ReadFile(string path)
{
	ifstream inputFile(path);
	string line;
	vector<vector<string>> vectorResult;
	while (getline(inputFile, line))
	{
		vector<string> splitedLine;
		istringstream iss(line);
		for (string s; iss >> s; )
			splitedLine.push_back(s);
		vectorResult.push_back(splitedLine);
	}
	//SplitQuery(vectorResult[0]);
	return vectorResult;
};

QueryParts QueryParser::SplitQuery(vector<string> query)
{
	string helpString;
	QueryParts qp;
	int paramNumber = 0;
	int wordNumber = 0;
	if (query.empty())
	{
		throw invalid_argument("Empty line");
	}
	helpString = query[0];
	transform(helpString.begin(), helpString.end(), helpString.begin(), tolower);

	if ((find(parameters.begin(), parameters.end(), helpString) != parameters.end()))
	{
		if (query[1].back() != ';')
		{
			throw invalid_argument("Expected ';'");
		}
		else
		{
			vector<string> parameter;
			parameter.push_back(query[0]);
			parameter.push_back(query[1].substr(0, query[1].size() - 1));
			qp.parameters.push_back(parameter);
			wordNumber = 2;
		}
	}
	else
	{
		throw invalid_argument("Bad parameter type");
	}
	helpString = query[wordNumber];
	transform(helpString.begin(), helpString.end(), helpString.begin(), tolower);


	if ((find(parameters.begin(), parameters.end(), helpString) != parameters.end()))
	{

		if (query[wordNumber + 1].back() != ';')
		{
			throw invalid_argument("Expected ';'");
		}
		else
		{
			vector<string> parameter;
			parameter.push_back(query[wordNumber]);
			parameter.push_back(query[wordNumber + 1].substr(0, query[wordNumber + 1].size() - 1));
			qp.parameters.push_back(parameter);
			wordNumber = wordNumber + 2;
		}
	}

	helpString = query[wordNumber];
	transform(helpString.begin(), helpString.end(), helpString.begin(), tolower);

	if (helpString != "select")
	{
		throw invalid_argument("Expected word 'select'");
	}
	wordNumber++;

	helpString = query[wordNumber];
	transform(helpString.begin(), helpString.end(), helpString.begin(), tolower);

	qp.selectingItem = helpString;
	wordNumber++;

	helpString = query[wordNumber];
	transform(helpString.begin(), helpString.end(), helpString.begin(), tolower);

	if (helpString != "such")
	{
		throw invalid_argument("Expected 'such'");
	}
	wordNumber++;
	helpString = query[wordNumber];
	transform(helpString.begin(), helpString.end(), helpString.begin(), tolower);
	if (helpString != "that")
	{
		throw invalid_argument("Expected word 'that'");
	}

	wordNumber++;
	helpString = query[wordNumber] + query[wordNumber + 1];
	transform(helpString.begin(), helpString.end(), helpString.begin(), tolower);
	string tag = "";
	int bracketStart = 0;
	for each (char var in helpString)
	{
		if (var == '(')
		{
			qp.tag = tag;
			break;
		}
		else
		{
			tag += var;
		}
		bracketStart++;
	}

	if (bracketStart == 0)
		throw invalid_argument("Expected '('");
	else
	{
		string firstParam = "";
		string secondParam = "";
		bool wasComma = false;
		bool wasEndBracket = false;
		for (int i = bracketStart + 2; i < helpString.size(); i++)
		{
			if (helpString[i] == ')')
			{
				wasEndBracket = true;
				if (firstParam != "")
					qp.parameteresInBracket.push_back(firstParam);
				if (secondParam != "")
					qp.parameteresInBracket.push_back(secondParam);
				break;
			}
			if (helpString[i] == ',')
			{
				wasComma = true;
				continue;
			}
			if (!wasComma)
			{
				firstParam += helpString[i];
			}
			else
			{
				secondParam += helpString[i];
			}
		}
	}


	if (!(find(allowedWords.begin(), allowedWords.end(), qp.tag) != allowedWords.end()))
	{
		string errorMessage = "Tag must be one of them: ";
		for each (string var in allowedWords)
		{
			errorMessage += var + " ";
		}
		throw invalid_argument(errorMessage);
	}

	return qp;
};