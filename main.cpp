/****************************************************************************************************************************************************************************
Project by:
1. Lior Roife     , ID: 206257826
2. Ori Leibovich  , ID: 307837096
 ****************************************************************************************************************************************************************************/

#include "Header.h"

 //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Main ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
int main(int argc, char* argv[])
{
	if (argv[1] != nullptr && argv[2] != nullptr)           //In case input and output file arguments exist - we start working on them.
	{
		string FileLine;                                    //The data of a single line in the file (will be used through the reading process).
		vector<string> LineParams{};                        //String vector that will be used to keep the Elements of a single line in the file after parsing.
		
		int numOfVertices, numOfEdges;                      //Variables that will be used to keep the amount of elemnts in groups 'V' and 'E' (Vertices , Edges) of the Graph 'G'.
		int Ecount = 0;                                     //Edges counter

		int s, d, w;                                        //Variables that will be used to keep the values of the elemnts in a single line.
															//'s'- Source vertex , 'd' - destination vertex , 'w' - Weight of Edge (s,d).
		ifstream inFile;                                    //input file stream.
		ofstream outFile;                                   //output file stream.

		inFile.open(argv[1]);                               //Try to open the input file.
		if (!inFile)                                        //In case we can't open the file with the given name in argv[1].
		{//handle error
			cout << ERROR_MSG_IN_FILE << endl;
			exit(1);
		}
		outFile.open(argv[2]);                              //Try to open the output file.
		if (!outFile)                                       //In case we can't open the file with the given name in argv[2].
		{//handle error
			cout << ERROR_MSG_IN_FILE << endl;
			exit(1);
		}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Read From File and Test The Input Elements ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
		if (getline(inFile, FileLine, '\n'))                //Get n - input vertices.
		{
			if (check_number(FileLine))                     //Test input number of vertices.
			{
				numOfVertices = stoi(FileLine);             //Convert the string to number.
			}
			else
			{//handle error
				cout << ERROR_MSG_INVALID_INPUT << endl;    //In case the element used to represent the 'numOfVertices' is invalid.
				outFile << ERROR_MSG_INVALID_INPUT << endl;
				inFile.close();
				outFile.close();
				exit(1);
			}
		}
		else
		{//handle error
			cout << ERROR_MSG_INVALID_INPUT << endl;        //In case there is a problem with reading the file using 'getline()'
			outFile << ERROR_MSG_INVALID_INPUT << endl;
			inFile.close();                                 //We close the file and exit the program.
			outFile.close();
			exit(1);
		}

		UndirectedGraph G;                    		        //Build Graph - 
		G.MakeEmptyGraph(numOfVertices);                    //with 'numOfVertices'

		if (getline(inFile, FileLine, '\n'))                //Get m - input edges
		{
			if (check_number(FileLine))                     //Test input number of edges
			{
				numOfEdges = stoi(FileLine);                //Convert the string to number.
			}
			else
			{//handle error
				cout << ERROR_MSG_INVALID_INPUT << endl;    //In case the element used to represent the 'numOfEdges' is invalid.
				outFile << ERROR_MSG_INVALID_INPUT << endl;
				inFile.close();                             //We close the file and exit the program.
				outFile.close();
				exit(1);
			}
		}
		else
		{//handle error
			cout << ERROR_MSG_IN_FILE << endl;
			outFile << ERROR_MSG_IN_FILE << endl;
			inFile.close();
			exit(1);
		}

		while (!inFile.eof())                               //While it is not the end of the input file.
		{
			if (!inFile.good())                             //If the file is unreadable.
			{//handle error
				cout << ERROR_MSG_IN_FILE << endl;
				outFile << ERROR_MSG_IN_FILE << endl;
				inFile.close();
				outFile.close();
				exit(1);
			}
			else
			{
				if (getline(inFile, FileLine, '\n'))        //Get file line elemnts into 'string' variable.
				{
					LineParams = ParseStringLine(FileLine); //Parse the string and move the elements into string vector.
					if (Ecount < numOfEdges && check_line_params(LineParams, numOfVertices, s, d, w))//'check_line_params' tests single line - 'true' if valid
					{                                       // if num of eges in file is less then 'm'
						if (LineParams.size() == 3)         //In case there are 3 valid elements in the file line.
						{
							Ecount++;                       //Increase the valid Edges counter.
							if (!G.AddEdge(s, d, w))        //Build edge (s,d,w) and add it to the Graph if it valid.
							{//handle error
								cout << ERROR_MSG_INVALID_INPUT << endl;  //Else - the amount of elements in the file invalid, print "Invalid input" msg.
								outFile << ERROR_MSG_INVALID_INPUT << endl;
								inFile.close();
								outFile.close();
								exit(1);
							}
						}
						else
						{//handle error
							cout << ERROR_MSG_INVALID_INPUT << endl;      //Else - the amount of elements in the file invalid, print "Invalid input" msg.
							outFile << ERROR_MSG_INVALID_INPUT << endl;
							inFile.close();
							outFile.close();
							exit(1);
						}
					}
					else if (Ecount == numOfEdges && check_line_params(LineParams, numOfVertices, s, d, w))//In case we expect getting Edge (s,d) to remove. 
					{
						if (!G.isConnected())               //Check whether the graph is connected before activating Kruskal , Prim.
						{
							cout << "Kruskal " << ERROR_MSG_NO_MST << endl <<
								"Prim " << ERROR_MSG_NO_MST << endl <<
								"Kruskal2 " << ERROR_MSG_NO_MST << endl;
							outFile << "Kruskal " << ERROR_MSG_NO_MST << endl <<
								"Prim " << ERROR_MSG_NO_MST << endl <<
								"Kruskal2 " << ERROR_MSG_NO_MST << endl;
							outFile.close();
							inFile.close();
							exit(1);
						}

						if (LineParams.size() == 2)         //If we have parsed 2 elemnts from the line it means those elemnts are representing edge (s,d) to remove.
						{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Kruskal (First Attempt) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
							//~~~~~~~Kruskal <x> // Weight of G by kruskal
							vector<Edge> KruskalRes1 = Kruskal(&G);
							int KruskalWeight1 = CalculateKruskalWeight(KruskalRes1);
							cout << "Kruskal < " << KruskalWeight1 << " >" << endl;
							outFile << "Kruskal < " << KruskalWeight1 << " >" << endl;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Prim ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
							//Prim <x>           // Weight of G by Prim
							int* PrimResult = Prim(&G);
							int PrimWeight = CalculatePrimWeight(PrimResult, &G);
							cout << "Prim < " << PrimWeight << " >" << endl;
							outFile << "Prim < " << PrimWeight << " >" << endl;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Remove Edge ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
							if (!G.RemoveEdge(s, d))        //'s' or 'd' invalid or edge (s,d) doesn't exissts - 'invalid input'.
							{
								cout << ERROR_MSG_INVALID_INPUT << endl;
								outFile << ERROR_MSG_INVALID_INPUT << endl;
								inFile.close();
								outFile.close();
								exit(1);
							}
							if (!G.isConnected())           //Check whether the graph is still connected (after removing and edge) before activating Kruskal again.
							{
								cout << "Kruskal2 " << ERROR_MSG_NO_MST << endl;
								outFile << "Kruskal2 " << ERROR_MSG_NO_MST << endl;
								inFile.close();
								outFile.close();
								exit(1);
							}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Kruskal (Second Attempt) ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
							//Kruskal <x’>       // Weight of G by Kruskal after removing Edge
							vector<Edge> KruskalRes2 = Kruskal(&G);
							int KruskalWeight2 = CalculateKruskalWeight(KruskalRes2);
							cout << "Kruskal2 < " << KruskalWeight2 << " >" << endl;
							outFile << "Kruskal2 < " << KruskalWeight2 << " >" << endl;
						}
						else
						{//handle error
							cout << ERROR_MSG_INVALID_INPUT << endl;
							outFile << ERROR_MSG_INVALID_INPUT << endl;
							inFile.close();
							outFile.close();
							exit(1);
						}
					}
					else
					{//handle error (Ecount > numOfEdges)
						cout << ERROR_MSG_INVALID_INPUT << endl;
						outFile << ERROR_MSG_INVALID_INPUT << endl;
						inFile.close();
						outFile.close();
						exit(1);
					}
				}
				else
				{//handle error
					cout << ERROR_MSG_INVALID_INPUT << endl;
					outFile << ERROR_MSG_INVALID_INPUT << endl;
					inFile.close();
					outFile.close();
					exit(1);
				}
			}
		}
		inFile.close();
		outFile.close();
		//G.PrintGraph();   //for tests
	}
	else
	{//handle error
		cout << "Invalid arguments\n";
		exit(1);
	}
	return 0;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ End Of Main ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
