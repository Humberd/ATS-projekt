#include "QueryParser.h"
/*
QueryParser::QueryParser()
{
}


QueryParser::~QueryParser()
{
}
*/
vector<vector<string>> QueryParser::ReadFile(string path)
{
	ifstream inputFile(path);
	string line;
	vector<vector<string>> vectorResult;
	while (getline(inputFile, line))
	{
		for (int i = 0; i < line.size(); i++)
		{
			char ch = line[i];
			if (ch == '(')
			{
				line.insert(i, 1, ' ');
				i++;
			}
		}
		vector<string> splitedLine;
		istringstream iss(line);
		for (string s; iss >> s; )
			splitedLine.push_back(s);
		vectorResult.push_back(splitedLine);
	}
	QueryParts parts = SplitQuery(vectorResult[0]);
	FollowsTag tag(parts, 0);
	tag.DoQuery();
	return vectorResult;
};

QueryParts QueryParser::SplitQuery(vector<string> query)
{

	vector<Parameter> parametersVector;
	vector<Parameter> parametersWithVector;
	QueryParts qp;
	bool newParam = false;
	bool pattern = false;
	int increment = 0;
	//vector<QueryParts> queryPartsVector;
	Part partGen;
	Part patternPartGen;
	vector<Part> partsVector;

	vector<vector<string>> examples;
	for (increment = 0; increment < query.size(); increment++)
	{
		string help = query[increment];
		transform(help.begin(), help.end(), help.begin(), tolower);
		if (help == "select")
			break;
		if ((find(parameters.begin(), parameters.end(), help) != parameters.end()))
		{
			Parameter param;
			param.Type = help;
			parametersVector.push_back(param);
			newParam = true;
			continue;
		}
		else
		{
			if (newParam == true)
			{
				string paramHelp = query[increment];
				if ((paramHelp[paramHelp.size() - 1] == ';') || (paramHelp[paramHelp.size() - 1] == ','))
				{

					parametersVector[parametersVector.size() - 1].Name = paramHelp.substr(0, paramHelp.size() - 1);
				}
				else
				{
					parametersVector[parametersVector.size() - 1].Name = paramHelp;
				}
				newParam = false;
			}

			else
			{
				Parameter paramNew;
				paramNew.Type = parametersVector[parametersVector.size() - 1].Type;
				string paramHelp = query[increment];
				if ((paramHelp[paramHelp.size() - 1] == ';') || (paramHelp[paramHelp.size() - 1] == ','))
				{

					paramNew.Name = paramHelp.substr(0, paramHelp.size() - 1);
				}
				else
				{
					paramNew.Name = paramHelp;
				}
				parametersVector.push_back(paramNew);
			}

		}

	}

	for (increment; increment < query.size(); increment++)
	{
		string helpString = query[increment];
		transform(helpString.begin(), helpString.end(), helpString.begin(), tolower);
		if (helpString == "select")
		{
			if (query[increment + 1][0] == '<')
			{
				string selectingHelp = "";
				for (int z = increment+1; z < query.size(); z++)
				{
					if (query[z][query[z].size() - 1] == '>')
					{
						selectingHelp += query[z];
						increment = z;
						break;
					}
					else
						selectingHelp += query[z];
				}
				qp.selectingItem = selectingHelp;
			}
			else
			{
				qp.selectingItem = query[increment + 1];
				increment++;
			}
			continue;
		}
		if (helpString == "and")
		{
			string helpStringNew = query[increment + 1];
			transform(helpStringNew.begin(), helpStringNew.end(), helpStringNew.begin(), tolower);
			if (!(find(allowedWords.begin(), allowedWords.end(), helpStringNew) != allowedWords.end()))
			{
				continue;
			}

			partsVector.push_back(partGen);
			partGen.parameteresInBracket.clear();
			partGen.tag = "";
			continue;
		}
		if ((find(allowedWords.begin(), allowedWords.end(), helpString) != allowedWords.end()))
		{
			//qp.tag = helpString;
			partGen.tag = helpString;
		}

		if (helpString == "pattern")
		{
			patternPartGen.tag = "";
			patternPartGen.tag.clear();
			patternPartGen.tag = helpString;
			pattern = true;
		}


		if (helpString == "example")
		{
			vector<string> exampleHelp;
			string exampleStr;
			for (int k = increment + 1; k < query.size(); k++)
			{
				if (query[k] == "Example")
				{
					increment = k + 1;
					examples.push_back(exampleHelp);
					break;
				}
				if (query[k][query[k].size() - 1] == ',')
				{
					exampleHelp.push_back(query[k].substr(0, query[k].size() - 1));
				}
				else
				{
					exampleHelp.push_back(query[k]);
				}
			}
		}

		if (helpString == "with")
		{
			Parameter p;
			for (int k = increment + 1; k < query.size(); k++)
			{
				if (query[k] == "and")
					continue;
				if (query[k] == "=")
				{
					p.Name = query[k + 1];
					parametersWithVector.push_back(p);
					p.Name = "";
					p.Type = "";
				}
				else
				{
					p.Type = query[k];
				}
			}
		}

		if (query[increment][0] == '(')
		{
			string inBracket = "";
			for (int j = increment; j < query.size(); j++)
			{
				if (query[j][query[j].size() - 1] == ')')
				{
					increment = j;
					inBracket += query[j];
					for (int l = increment; l < query.size(); l++)
					{
						if (query[l][query[l].size() - 1] != ')')
							inBracket += query[l];
					}

					string paramInBracket = "";
					bool first = true;
					for (int k = 1; k < inBracket.size(); k++)
					{
						if (first)
						{
							if (inBracket[k] != ',')
							{
								paramInBracket += inBracket[k];
							}
							else
							{
								first = false;
								if (patternPartGen.tag == "")
									partGen.parameteresInBracket.push_back(paramInBracket);
								else
									patternPartGen.parameteresInBracket.push_back(paramInBracket);
								paramInBracket = "";
								continue;
							}
						}
						else
						{
							if (inBracket[k] != ')')
							{
								paramInBracket += inBracket[k];
							}
							else
							{
								if (patternPartGen.tag == "")
									partGen.parameteresInBracket.push_back(paramInBracket);
								else
								{
									patternPartGen.parameteresInBracket.push_back(paramInBracket);
									qp.parts.push_back(patternPartGen);
									//patternPartGen.tag = "";
									//patternPartGen.tag.clear();
									pattern = false;
								}
								break;
							}
						}
					}
					break;
				}
				else
				{
					inBracket += query[j];
				}
			}
		}


	}
	partsVector.push_back(partGen);
	qp.parts = partsVector;
	qp.parametersWithVector = parametersWithVector;
	qp.examples = examples;
	qp.ParametersList = parametersVector;

	for (int h = 0; h < qp.parametersWithVector.size(); h++)
	{
		string sentence = qp.parametersWithVector[h].Type;
		istringstream iss(sentence);
		std::vector<std::string> tokens;
		std::string token;
		while (std::getline(iss, token, '.')) {
			if (!token.empty())
				tokens.push_back(token);
		}
		for (int z = 0; z < qp.parts.size(); z++)
		{
			for (int l = 0; l < qp.parts[z].parameteresInBracket.size(); l++)
			{
				if (qp.parts[z].parameteresInBracket[l] == tokens[0])
				{
					qp.parts[z].parameteresInBracket[l] = qp.parametersWithVector[h].Name;
				}
			}
		}
	}

	return qp;
};





/*
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
//transform(helpString.begin(), helpString.end(), helpString.begin(), tolower);
string tag = "";
int bracketStart = 0;
for each (char var in helpString)
{
if (var == '(')
{
transform(tag.begin(), tag.end(), tag.begin(), tolower);
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
for (int i = bracketStart + 1; i < helpString.size(); i++)
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
*/