#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

const int ROWS = 6;
const int COLS = 2;


void printCircuit(int edge[], int totalvertix);
bool Check(int vertix, int graph[ROWS][2], int edge_exists[], int loc, int costA, int costB, int costC, int Time_Limit);
bool Process_Circuit(int graph[ROWS][2], int path[], int pos, int costA, int costB, int costC, int Time_Limit);
bool final_Circuit(int graph[ROWS][2], int tA, int tB, int tC, int T, int totalvertix);


//this function will check for repeated vertices and adjecency
//will also add a vertix in a certain location.
bool Check(int vertix, int graph[ROWS][2], int edge_exists[], int loc, int costA, int costB, int costC, int Time_Limit)
{
    int sum = 0;
    sum = costA + costB;
    if (sum < Time_Limit)
    {
        if (graph[edge_exists[loc - 1]][vertix] == 0)   //adj
            return false;
        for (int i = 0; i < loc; i++)           //avoid repetition
        {
            if (edge_exists[i] == vertix)
                return false;
        }
    }
    return true;
}

bool Process_Circuit(int graph[ROWS][2], int edge[], int loc,int tA, int tB,int tC, int T)
{
    int costA = 0, costB = 0, costC = 0, Time_Limit = 0;
    costA = tA;
    costB = tB;
    costC = tC;
    Time_Limit = T;
    bool flag = true;
     //cout << "t(A) = " << costA << endl;
     //cout << "t(B) = " << costB << endl;
     //cout << "t(C) = " << costC << endl;
     //cout << "T= " << Time_Limit << endl;

    if (loc == ROWS)   //At the end of circiut 1.first node=lastnode   2.Vertices=V and Edge = E
    {
        if (graph[edge[loc - 1]][edge[0]] == 1)
            return flag;
        else
            return (flag = false);
    }

    int sum = 0;
    //sum1 = costA + costB+ costC;
    //sum2 = costA + costB;



    for (int i = 1; i < ROWS; i++)     //next vertix move on
    {
        if (costA < Time_Limit)
        {
            if (Check(i, graph, edge, loc, costA, costB, costC, Time_Limit))
            {
                edge[loc] = i;
                if (Process_Circuit(graph, edge, loc + 1, costA, costB, costC, Time_Limit) == true && (costA + costB + costC) < Time_Limit)
                {
                    return flag;
                }

                edge[loc] = -1;
            }
        }
    }

    return (flag = false);
}

bool final_Circuit(int graph[ROWS][2],int tA, int tB,int tC, int T, int totalvertix)
{
    int var1 = 0, var2 =0 , var3 = 0,var4 = 0;
    var1 =tA;
    var2 =tB;
    var3 = tC;
    var4 = T;

    int* edge_exists;
    edge_exists = new int[ROWS];
    bool flag = false;

    for (int i = 0; i < ROWS; i++)
    {
        edge_exists[i] = -1;
    }
    edge_exists[0] = 0;     //home = h
    if (Process_Circuit(graph, edge_exists, 1, var1, var2, var3, var4) == false)
    {
        cout << "NOT FEASIBLE FOR HAMATONIAN GRAPH!" << endl;
        return false;
    }
    else
    {
       /* cout << "t(A) = " << var1 << endl;
        cout << "t(B) = " << var2 << endl;
        cout << "t(C) = " << var3 << endl;
        cout << "T= " << T << endl;*/
        printCircuit(edge_exists, totalvertix);
    }
    return true;
}


void printCircuit(int edge[], int totalvertix)
{
    cout << "FEASIBLE FOR HAAMITONIAN CIRCUIT" << endl;
    cout << "OUTPUT: " << endl;
    for (int i = 0; i < totalvertix; i++)     //last edge to first edge
        cout << edge[i] << " ";
    cout << edge[0] << " ";
    cout << endl;
}



int get_index(char* arr, char val)
{
    int get = -9999;
    for (int i = 0; arr[i] != '\0'; i++)
    {
        if (arr[i] == val)
            get = i;
    }
    return get;
}


void read_file()
{
    int totalvertix = 0;
    char delimiter = ',';
    bool bool_array[ROWS][COLS];
    int edgeCount = 0;
    string edgeString = "E={(h,A),(h,B),(h,C),(A,B),(A,C),(B,C)}";

    int i = 0;
    string token1;
    int tA = 0;
    int tB = 0;
    int tC = 0;
    int T = 0;

    int** edge = new int* [4];
    for (int i = 0; i < 4; i++)
        edge[i] = new int[4];

    char array[ROWS][COLS];
    int arr[ROWS][COLS];

    char* vertex = new char[20];

    istringstream ss(edgeString);
    string token;
    string filename = "P2_test1.txt";
    ifstream file(filename);

    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            istringstream ss(line);
            string token;
            while (getline(ss, token, '\n'))
            {
                if (line.find("V=") != string::npos)
                {
                    char* vertexArray = new char[line.size() + 1];
                    copy(line.begin() + 3, line.end() - 1, vertexArray);
                    vertexArray[line.size() - 4] = '\0'; // Null terminator
                    cout << "Vertex Array: " << vertexArray << endl;
                    int i = 0; int loop = 0;
                    for (; vertexArray[i] != '\0'; i++) {
                        if (vertexArray[i] != ',')
                            vertex[loop++] = vertexArray[i];
                    }
                    
                    vertex[loop] = '\0';
                    totalvertix = loop;
                    cout << "TOTAL VERTICES: " << loop << endl;
                    cout << vertex << endl;     //vertices extracted
                    delete[] vertexArray;
                }

                //read file in bool
                else if (line.find("E=") != string::npos)
                {
                    int loop = 0; int row = 0;
                    istringstream ss(line);
                    //string token;
                    cout << "edges : " << token << endl;
                    int k = 0;
                    while (token[k] != '\0')
                    {
                        while (token[k] != '{')
                            k++;

                        while (token[k] != '}') {

                            k += 2;
                            //cout << "**************** " << endl;
                            array[row][loop++] = token[k];//before comma
                            //cout << "**************** " << endl;
                            array[row][loop++] = token[k + 2];//after comma
                            row++;
                            loop = 0;
                            k += 4;
                        }
                        k++;
                    }
                }
                else if (line.find("Weights=") != string::npos)
                {
                    int h = 0;
                    int loop = 0; int row = 0;
                    cout << token << endl;
                    int l = 0;
                    while (token[h] != '\0') {
                        while (token[h] != '{')
                            h++;
                        while (token[h] != '}' && l !=6)
                        {
                            int var1, var2;
                            var1 = get_index(vertex, array[row][0]);
                            var2 = get_index(vertex, array[row][1]);
                            h++;
                            cout << "**************** " << endl;
                            cout << "SR. no: " << token[h] << endl;
                            edge[get_index(vertex, array[row][0])][get_index(vertex, array[row][1])] = (token[h] - 48);
                            edge[get_index(vertex, array[row][1])][get_index(vertex, array[row][0])] = (token[h] - 48);
                            //cout << "(" << get_index(vertex, array[row][0]) << " , " << get_index(vertex, array[row][1]) << ")" << endl;
                            cout << "(" << var1 << " , " << var2 << ")" << endl;
                            row++;
                            h++;
                            arr[l][0] = var1;
                            arr[l][1] = var2;
                            var1 = 0;
                            var2 = 0;
                            l++;
                        }
                        h++;
                    }
                }

                else if (line.find("t(A)=") != string::npos || line.find("t(B)=") != string::npos || line.find("t(C)=") != string::npos)
                {
                    stringstream sstream(token.substr(token.find('=') + 1));
                    string tempToken;
                    sstream >> tA;
                   
                    while (getline(sstream, tempToken, ','))
                    {
                        if (tempToken.find("t(B)=") != string::npos)
                        {
                            tB = stoi(tempToken.substr(tempToken.find('=') + 1));
                        }
                        else if (tempToken.find("t(C)=") != string::npos)
                        {
                            tC = stoi(tempToken.substr(tempToken.find('=') + 1));
                        }
                    }
                }

                else if (line.find("T=") != string::npos || line.find("t(B)=") != string::npos || line.find("t(C)=") != string::npos)
                {
                    stringstream sstream(token.substr(token.find('=') + 1));
                    string tempToken;
                    sstream >> T;
                    
                }

            }

        }
       /* cout << "t(A) = " << tA << endl;
        cout << "t(B) = " << tB << endl;
        cout << "t(C) = " << tC << endl;
        cout << "T= " << T << endl;*/

        /*for (int i = 0; i < ROWS; i++) {
     for (int j = 0; j < COLS; j++) {
         cout << array[i][j] << " , ";

     }
     cout << endl;
     }*/

        
       /*for (int i = 0; i < 4; i++) {
          for (int j = 0; j < 4; j++) {
              if (i == j)
                  edge[i][j] = 0;
              cout << edge[i][j] << " , ";

          }

          cout << endl;
      }*/


        //for (int i = 0; i < ROWS; i++)
        //{
        //        cout << arr[i][0] << "," << arr[i][1];
        //        cout << endl;
        //}

        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                cout << arr[i][j]<< " ";
            }
            cout << endl;
        }

        /*for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                bool_array[i][j] = arr[i][j];
            }
                cout << endl;       
        }*/


        //for (int i = 0; i < ROWS; i++)
        //{
        //    for (int j = 0; j < COLS; j++)
        //    {
        //      cout <<  bool_array[i][j] << " ";
        //    }
        //    cout << endl;
        //}

      //for (int i = 0; i < 6; i++)
      //{
      //    cout << edge[i][0] << ", " << edge[i][1] << endl;
      //}

        cout << "**************** " << totalvertix << endl;
        final_Circuit(arr, tA, tB, tC, T, totalvertix);
        file.close();
    }

    else
    {
        cout << "Unable to open file" << endl;
    }
}

int main()
{
    read_file();
}