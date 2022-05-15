#define _CRT_SECURE_NO_WARNINGS 1
// C program for the above approach
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>


//#include <graphics.h>
#define FILE1PATH "C:\\Users\\adi\\Desktop\\bus project\\bus2.csv"
#define FILE2PATH "bus4.csv"
#define CITY_COLUMN 26
#define STATION_COLUMN 15
#define BUS_COLUMN 9
#define SIZE1 2815
#define NOT_FOUND -1
#define SIZE 12532
#define STATIONNUMBER_COLUMN 14
#define ARRANGE_COLUMN 13
#define DISTANCE_COLUMN 18

#define NOT_FOUND -1
#define MAX 12530
FILE* fp;
struct stationNumber
{
	char id[50];
};

struct flow
{
	int dest;
	struct flow* next;
};

struct vertex {
	char v[50];
	char arrangmentnum[50];
	char distance[50];
};

struct vertex vertexArry[MAX];
int numofsatation = 0;
int numofsatation1 = 0;
int numofarrangment = 0;
struct stationNumber s[SIZE1];


struct node {
	int data;
	int distance;
	char stationName[50];
	char value[50];
	struct node* next = NULL;
};


node* arr[SIZE];

typedef struct bus {
	char nameLine[100];
} Bus;

typedef struct station {
	char name[100];
	Bus  busses[50];//
	int  actualBussNum;//כמות האוטובסים
	stationNumber id1[50];
	int actstationNum;
} Station;

typedef struct city {
	char name[1024];
	Station stations[1024];
	int actualStationsNum;
}City;

typedef struct Edge {
	int src, dest, weight;
}Edge;

struct AllEdges {
	Edge edge;
	struct AllEdges* next;
};

struct Graph {
	int V, E;
	struct AllEdges* edge;
};

City* cities = NULL; // List of City
struct AllEdges* allEdges = NULL;
struct flow* flow = NULL;

int actualCityNum = 0;
int actualBusNum = 0;
int actualStationNum = 0;
int actualEdgesNum = 0;
void red() {
	printf("\033[1;31m");
}
void yellow() {
	printf("\033[1;33m"); // the color yellow for a printing code in stidio  ( קלט )
}
void green() {
	printf("\033[0;32m"); // the color yellow for a printing code in stidio  ( קלט )
}
void white() {
	printf("\033[0;37m"); // the color yellow for a printing code in stidio  ( קלט )
}
void black() {
	printf("\033[0;30m"); // the color yellow for a printing code in stidio  ( קלט )
}

void clearstring(char name[50]) {
	//clear the \n in the end of string after the fgets functions
	int len = strlen(name);
	if (len > 0 && name[len - 1] == '\n')
		name[len - 1] = '\0';
}


// return index of city if it's Exist,otherwise return NOT_FOUND -1
int isExistCity(char* cityName, int actualSize) {

	for (int index = 0; index < actualSize; index++)
	{
		if (strcmp(cities[index].name, cityName) == 0)
			return index;
	}
	return NOT_FOUND;
}

// return index of city if it's Exist,otherwise return NOT_FOUND -1
int isExistStation(int cityIndex, char* stationsName)
{
	int stationNums = cities[cityIndex].actualStationsNum;
	for (int index = 0; index < stationNums; index++)
	{
		if (strcmp(cities[cityIndex].stations[index].name, stationsName) == 0)
			return index;
	}
	return NOT_FOUND;
}


int isExistBus(int cityIndex, int stationIndex, char* bussName)
{

	int bussNums = cities[cityIndex].stations[stationIndex].actualBussNum;
	for (int index = 0; index < bussNums; index++)
	{
		if (strcmp(cities[cityIndex].stations[stationIndex].busses[index].nameLine, bussName) == 0)
			return index;
	}
	return NOT_FOUND;
}


int isExistStationnum(int cityIndex, int stationIndex, char* stationnum)
{

	int stationnum1 = cities[cityIndex].stations[stationIndex].actstationNum;
	for (int index = 0; index < stationnum1; index++)
	{
		if (strcmp(cities[cityIndex].stations[stationIndex].id1[index].id, stationnum) == 0)
			return index;
	}
	return NOT_FOUND;
}



void printAllCities()
{
	for (int i = 0; i < actualCityNum; i++)
	{
		yellow();

		printf("City: %s\n", cities[i].name);

	}
	printf("There are [%d] cities\n", actualCityNum);
	printf("\n");
}

void printAllstations(char cityName[50])//Afula
{

	int cityPos = isExistCity(cityName, actualCityNum);//index of city==8
	if (cityPos != NOT_FOUND)//8!=-1
	{
		int size = cities[cityPos].actualStationsNum;//  מספר התחנות נמצא בעפולה
		printf("Stations: { \n");

		for (int j = 0; j < size; j++)
		{
			yellow();
			printf("staion %s:\n", cities[cityPos].stations[j].name);

		}
		printf("}\n");
		printf("There are [%d] stations in %s.\n", size, cityName);

	}
	else
	{
		printf("city is not found\n");
	}
}

void printStationdetails(char city[50], char stationName[50])//מקבלת את שם של שיער ושם של תחנה ומדפיסה את האוטובסים שעוברים דרך התחנה
{
	int cityPos = isExistCity(city, actualCityNum);//מחזירה את ה המיקום של העיר
	int StaionPos = isExistStation(cityPos, stationName);//מחזירה את המיקום של התחנה שנמצות בתוך העיר המסוימת


	if (cityPos != NOT_FOUND && StaionPos != NOT_FOUND) {//בודקת אם כן מצאנו את המיקום של העיר ואת המיקום של התחנה 


		int size = cities[cityPos].stations[StaionPos].actualBussNum;//כמות האטובוסית שנמצאת בתוך בתחנה שנמאת בתוך העיר המסוימת

	/*	printf("staion id:[%s] \n", cities[cityPos].stations[StaionPos].id1->id);*/
		printf("Lines on this staion:\n");
		for (int b = 0; b < cities[cityPos].stations[StaionPos].actualBussNum; b++)//עוברת מאפס עד מספר האטובוסים הנמצא בתוך תחנה הנמצאת בתוך עיר מסוימת
		{
			yellow();
			printf("%d:[%s], ", b, cities[cityPos].stations[StaionPos].busses[b].nameLine);//מדפיסה את האוטובוסים הנמצאים בתוך תחנה הנמצאת בתוך עיר מסוימת
			printf("\n");

		}

		printf("Found [%d] Lines\n", size);

	}
	else {

		printf(" not found\n");
	}
}


void printStationNumber(char city[50], char stationName[50])//מקבלת את שם של שיער ושם של תחנה ומדפיסה את האוטובסים שעוברים דרך התחנה
{
	int cityPos = isExistCity(city, actualCityNum);//מחזירה את ה המיקום של העיר
	int StaionPos = isExistStation(cityPos, stationName);//מחזירה את המיקום של התחנה שנמצות בתוך העיר המסוימת


	if (cityPos != NOT_FOUND && StaionPos != NOT_FOUND) {//בודקת אם כן מצאנו את המיקום של העיר ואת המיקום של התחנה 


		int size = cities[cityPos].stations[StaionPos].actualBussNum;//כמות האטובוסית שנמצאת בתוך בתחנה שנמאת בתוך העיר המסוימת
		yellow();

		printf("staion id:[%s] \n", cities[cityPos].stations[StaionPos].id1->id);
		printf("\n");
	}
	else {

		printf(" not found\n");
	}
}
void  FixCsvFile(char buffer[1024], char temp[1024]) {
	int j = 0;
	bool isStrangeChar = false;
	for (int i = 0; i < strlen(buffer); i++)
	{
		if (buffer[i] == '"' && buffer[i + 1] != ',')
			isStrangeChar = true;
		if (buffer[i] == ',' && buffer[i + 1] == ',')
		{
			temp[j] = buffer[i];
			j++;
			temp[j] = 'w';
			j++;
		}
		else if (buffer[i] == ',' && buffer[i + 1] == ' ' && isStrangeChar)
		{
			temp[j] = ';';
			j++;
			isStrangeChar = false;
		}
		else
		{
			temp[j] = buffer[i];
			j++;
		}
	}
	temp[j] = '\0';
}



void readfromfile() {
	fp = fopen(FILE1PATH, "r");//פתחנו את הקובץ לקריאה
	if (!fp)//אם הקובץ לא נפתח מדפיסים הודעה
	{
		printf("Can't open file\n");
	}
}

int isExiststationNumber(char* idname, int actualSize) {

	for (int index = 0; index < actualSize; index++)
	{

		if (strcmp(s[index].id, idname) == 0)
			return index;
	}
	return NOT_FOUND;
}
//אנחנו בודקים שלושה מקרים אם העיר לא נמצאת אז אנחנו מכניסים אותה וגם מכניסים את התחנות שקשורים לה עם האוטובוסים שעוברים ממנה
//אם העיר נמצאת אבל התחנה לא נמצאת אז אני מכניסה אותה ומגם את האוטובסים שעוברים ממנה
//אם מספר הקו לא נמצא אז מכניסים אותו
void openfile(char* col, int size)
{
	char buffer[1024] = { '\0' }; // data from csv file
	char temp[1024] = { '\0' };  // data after replace space charcter with w  
	// Substitute the full file path
	// for the string file_path


		// Here we have taken size of
		// array 1024 you can modify it
	int numOfCol = 0;
	int row = 0;
	while (fgets(buffer, 1024, fp))//מכניס את מה שנמצא בקובץ לתוך ה buffer
	{
		FixCsvFile(buffer, temp);//קראנו לפונקציה שמכניס אות  במקומות הריקיםה  
		// Splitting the data
		char* value = strtok(temp, ",");//value<-temp
		char stationName[100];//שם תחנה
		char busLine[100];//שם הקו
		char StaionNum1[50];

		while (value) {//

			if (row != 0 && numOfCol == STATIONNUMBER_COLUMN) {
				strcpy_s(StaionNum1, value);//value->busline
			}
			if (row != 0 && numOfCol == BUS_COLUMN)//אם שורה שונה מאפס וגם מספר עמודה שווה למספר העמודה של האטובוסים 
			{
				strcpy_s(busLine, value);//value->busline
			}

			//taking values of Station Coulmn from csv file
			if (row != 0 && numOfCol == STATION_COLUMN) {//אם מספר העמודה שווה למספר עמודה של התחנות
				strcpy_s(stationName, value);//value->stationname 
			}

			//taking values of City Coulmn from csv file
			if (row != 0 && numOfCol == CITY_COLUMN)//אם מספר העמודה שווה למספר עמודה של הערים
			{
				int posCity = isExistCity(value, actualCityNum);//מחזירה את המיקום של העיר 
				if (posCity == NOT_FOUND)
				{
					//init city by taking his name also by adding station
					if (stationName && busLine)
					{
						strcpy_s(cities[actualCityNum].name, value);//value->cities[actualCityNum].name
						cities[actualCityNum].actualStationsNum = 0;//התחלנו את מספר התחנות =0
						cities[actualCityNum].stations[0].actualBussNum = 0;//מאתחל את מספר האוטובוסים באפס
						strcpy_s(cities[actualCityNum].stations[0].busses[0].nameLine, busLine);//התעקת את busline->cities[actualCityNum].stations[0].busses[0].nameLine
						cities[actualCityNum].stations[0].actualBussNum++;//מקדם את מספר האוטובסים
						strcpy_s(cities[actualCityNum].stations[0].name, stationName);//מעתיק stationName->cities[actualCityNum].stations[0].name
						cities[actualCityNum].actualStationsNum++;//מקדם את מספר התחנות
						actualCityNum++;//מקדמים את מספר הערים
					}
				}
				else
				{

					if (stationName && busLine)
					{
						int posOfStationsName = isExistStation(posCity, stationName);//מחזיר את המיקום של התחנה 

						//City is Exist but the station is not exist
						if (posOfStationsName == NOT_FOUND)
						{

							int stationPos = cities[posCity].actualStationsNum;//מספר התחנות
							strcpy_s(cities[posCity].stations[stationPos].name, stationName);//מעתיק את השם של התחנה stationName->cities[posCity].stations[stationPos].name
							int bussPos = 0;//מספר האוטובוס 
							strcpy_s(cities[posCity].stations[stationPos].id1->id, StaionNum1);
							cities[posCity].stations[stationPos].actualBussNum = 0;//מעדכנת את מספר האוטובסים לאפס
							strcpy_s(cities[posCity].stations[stationPos].busses[bussPos].nameLine, busLine);//busLine->cities[posCity].stations[stationPos].busses[bussPos].nameLine
							bussPos++;//  מיקום האוטובוס מתקדם
							stationPos++;//מיקום התחנות מתקדם

							cities[posCity].actualStationsNum = stationPos;//
							cities[posCity].stations[stationPos].actualBussNum++;//מספר האוטובוסים מתקדם

						}
						else
						{
							int posOfBuss = isExistBus(posCity, posOfStationsName, busLine);//מחזירה את המיקום של האטובוס
							if (posOfBuss == NOT_FOUND)
							{
								int bussPos = cities[posCity].stations[posOfStationsName].actualBussNum;//bussPos<-cities[posCity].stations[posOfStationsName].actualBussNum
								strcpy_s(cities[posCity].stations[posOfStationsName].busses[bussPos].nameLine, busLine);//busLine->cities[posCity].stations[posOfStationsName].busses[bussPos].nameLine
								bussPos++;
								cities[posCity].stations[posOfStationsName].actualBussNum++;//מקדמים את מספר האוטובוסים
							}

						}

					}


				}
			}



			value = strtok(NULL, ",");
			numOfCol++;//מקדמים את מספר העמודה
		}
		numOfCol = 0;
		row++;//מקדמים את מספר השורה 
	}

	// Close the file
	fclose(fp);
}

/*------------------------------------------------------------------------------------------------------------------*/
void initStartList()
{
	for (int i = 0; i < SIZE1; i++)
	{
		arr[i] = NULL;
	}
}
/*------------------------------------------------------------------------------------------------------------------*/
void beginsert(int num, int i) {
	struct node* ptr1 = (struct node*)malloc(sizeof(struct node));
	if (ptr1 == NULL) {
		printf("");
	}

	ptr1->data = num;
	ptr1->next = arr[i];
	arr[i] = ptr1;

}

void printLinkedList() {
	node* temp;
	for (int i = 0; i < SIZE1; i++)
	{
		temp = arr[i];
		while (temp) {
			yellow();
			printf("%d->", temp->data);
			temp = temp->next;
		}
		printf("||\n");
	}

}
void printnodearr() {
	for (int i = 0; i < SIZE1; i++) {
		printf("%d\n", arr[i]->data);
	}

}



void printarragmentnumber()
{
	for (int i = 0; i < MAX; i++)
	{
		printf("%d.arrrNumber: %s-%s\n", i, vertexArry[i].arrangmentnum, vertexArry[i].v);
	}
	printf("\n");
}


void printAllstationNumber()
{
	for (int i = 0; i < MAX; i++)
	{
		printf("%d.stationNumber: %s\n", i, vertexArry[i].v);
	}
	printf("\n");
}



int findstaionnum(int staionnum) {

	for (int k = 0; k < SIZE1; k++)
	{
		if (staionnum == arr[k]->data)
			return k;
	}

	return -1;

}


void lastinsert(int item, int index, int distance)//,char *stationName)
{
	struct node* ptr = (struct node*)malloc(sizeof(struct node));
	struct node* temp;
	if (ptr == NULL)
	{
		printf("\nOVERFLOW");
	}
	else
	{
		ptr->data = item;
		ptr->distance = distance;
		//strcpy_s(ptr->stationName, stationName);

		if (arr[index] == NULL)
		{

			ptr->next = NULL;
			arr[index] = ptr;
			// printf("\nNode inserted");
		}
		else
		{
			temp = arr[index];
			while (temp->next != NULL)
			{
				if (temp->next->data == item) {
					return;
				}
				temp = temp->next;
			}
			temp->next = ptr;
			ptr->next = NULL;
			//printf("\nNode inserted");
			temp = arr[index];
			/* while (temp) {
				 printf("%d->", temp->data);
				 temp = temp->next;
			 }*/
		}
	}
}


void nigbhoors() {
	int i = 0;
	int v1 = 0;
	for (; i < MAX; i++) {
		if ((atoi)(vertexArry[i].arrangmentnum) != 1) {
			int index = findstaionnum(v1);
			lastinsert((atoi)(vertexArry[i].v), index, (atoi)(vertexArry[i].distance));//vertexArry[i].nameOfDestinationStation);
			v1 = (atoi)(vertexArry[i].v);
		}
		v1 = (atoi)(vertexArry[i].v);
	}
}


void insertinto() {
	for (int i = 0; i < SIZE1; i++) {
		beginsert(((atoi)(s[i].id)), i);
		arr[0]->data = 53436;

		if (i == 1) {
			arr[1]->data = 59589;
		}

		if (i == 2) {
			arr[2]->data = 53500;
		}
	}
}


void insertdataintostructs(char* col, int size)
{


	char buffer[1024] = { '\0' }; // data from csv file
	char temp[1024] = { '\0' };  // data after replace space charcter with w  
	// Substitute the full file path
	// for the string file_path

		// Here we have taken size of
		// array 1024 you can modify it
	int numOfCol = 0;
	int row = 0;
	while (fgets(buffer, 1024, fp))//מכניס את מה שנמצא בקובץ לתוך ה buffer
	{
		FixCsvFile(buffer, temp);//קראנו לפונקציה שמכניס אות  במקומות הריקיםה  
		// Splitting the data
		char* value = strtok(temp, ",");//value<-temp
		char stationName[100];//שם תחנה
		char busLine[100];//שם הקו

		while (value) {//


			//taking values of City Coulmn from csv file
			if (row != 0 && numOfCol == STATIONNUMBER_COLUMN)//אם מספר העמודה שווה למספר עמודה של הערים
			{
				int posCity = isExiststationNumber(value, numofsatation);//מחזירה את המיקום של העיר 
				if (posCity == NOT_FOUND)
				{
					//init city by taking his name also by adding station
					if (stationName && busLine)
					{
						strcpy_s(s[numofsatation].id, value);//value->cities[actualCityNum].name
						numofsatation++;
					}
				}
			}

			//taking values of City Coulmn from csv file
			if (row != 0 && numOfCol == STATIONNUMBER_COLUMN)//אם מספר העמודה שווה למספר עמודה של מספר התחנה
			{

				//init city by taking his name also by adding station
				if (stationName && busLine)
				{
					strcpy_s(vertexArry[numofsatation1].v, value);//value->cities[actualCityNum].name

					//numofsatation1++;//מקדמים את מספר התחנות
				}
			}



			////taking values of City Coulmn from csv file
			if (row != 0 && numOfCol == ARRANGE_COLUMN)//אם מספר העמודה שווה למספר עמודה של הערים
			{

				//init city by taking his name also by adding station
				if (stationName && busLine)
				{
					strcpy_s(vertexArry[numofarrangment].arrangmentnum, value);//value->cities[actualCityNum].name

					numofarrangment++;//מקדמים את מספר הערים
				}
			}


			//if (row != 0 && numOfCol == STATION_COLUMN)//אם מספר העמודה שווה למספר עמודה של הערים
			//{

			//	//init city by taking his name also by adding station
			//	//if (stationName && busLine)
			//	{
			//		strcpy_s(s[numofsatation].name, value);//value->cities[actualCityNum].name

			//		numofsatation++;//מקדמים את מספר הערים
			//	}
			//}

			if (row != 0 && numOfCol == DISTANCE_COLUMN)//אם מספר העמודה שווה למספר עמודה של הערים
			{

				//init city by taking his name also by adding station
				//if (stationName && busLine)
				{
					if (!strcmp(value, "w"))
						strcpy_s(vertexArry[numofsatation1].distance, "0");//value->cities[actualCityNum].name
					else
						strcpy_s(vertexArry[numofsatation1].distance, value);//value->cities[actualCityNum].name

					numofsatation1++;//מקדמים את מספר הערים
				}
			}

			value = strtok(NULL, ",");
			numOfCol++;//מקדמים את מספר העמודה
		}
		numOfCol = 0;
		row++;//מקדמים את מספר השורה 
	}
	printf("Going to print city list with size[%d]\n", numofsatation);

	// Close the file
	fclose(fp);
}


void printstationnihboors(int stationnum) {
	int index = 0;
	for (int i = 0; i < SIZE1; i++) {
		if (arr[i]->data == stationnum)
			index = i;

	}
	node* temp;
	temp = arr[index];
	while (temp) {
		yellow();

		printf("%d->", temp->data);
		temp = temp->next;
	}
	printf("||\n");
}

void insertEdge(int src, int dest, int distance)
{
	struct AllEdges* temp;
	if (!allEdges)
	{
		allEdges = (struct AllEdges*)malloc(sizeof(struct AllEdges));
		if (!allEdges)
		{
			return;
		}
		allEdges->edge.src = src;
		allEdges->edge.dest = dest;
		allEdges->edge.weight = distance;
		allEdges->next = NULL;
	}
	else
	{
		struct AllEdges* ptr = (struct AllEdges*)malloc(sizeof(struct AllEdges));
		if (ptr == NULL)
		{
			printf("\nOVERFLOW");
			return;
		}
		else
		{
			//add edge to last
			ptr->edge.src = src;
			ptr->edge.dest = dest;
			ptr->edge.weight = distance;

			ptr->next = NULL;

			temp = allEdges;
			while (temp->next != NULL)
			{
				temp = temp->next;
			}
			temp->next = ptr;
		}
	}
	actualEdgesNum++;
}

void createEdgeList() {

	for (int index = 0; index < SIZE1; index++)
	{
		node* temp;
		temp = arr[index];
		temp = temp->next;
		while (temp)
		{
			int src = index;
			int dest = findstaionnum(temp->data);
			//temp->
			insertEdge(src, dest, temp->distance);
			temp = temp->next;
		}
	}
}



void printEdges()
{
	struct AllEdges* temp = allEdges;
	while (temp != NULL)
	{
		yellow();

		printf("src:%d, dest:%d, distance:%d\n", temp->edge.src, temp->edge.dest, temp->edge.weight);

		temp = temp->next;
	}
}

struct Graph* createGraph() {
	struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
	graph->V = SIZE1;
	graph->E = actualEdgesNum;
	graph->edge = allEdges;
	return graph;
}

void BellmanFord(struct Graph* graph, int sourceStationNumber, int destStationNumber) {

	int src = findstaionnum(sourceStationNumber);
	int dest = findstaionnum(destStationNumber);
	int V = graph->V;
	int E = graph->E;
	int dist[SIZE1];
	int nighpors[SIZE1];

	struct AllEdges* temp = graph->edge;
	// Step 1: Initialize distances from src to all other
  // vertices as INFINITE
	for (int i = 0; i < SIZE1; i++)
		dist[i] = INT_MAX;
	dist[src] = 0;
	// Step 2: Relax all edges |V| - 1 times. A simple
	// shortest path from src to any other vertex can have
	// at-most |V| - 1 edges
	for (int i = 1; i <= V - 1; i++) {
		temp = graph->edge;
		for (int j = 0; j < E; j++) {
			int u = temp->edge.src;
			int v = temp->edge.dest;
			int weight = temp->edge.weight;
			if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
			{
				dist[v] = dist[u] + weight;
				nighpors[v] = u;
			}
			temp = temp->next;
		}
	}
	// Step 3: check for negative-weight cycles.  The above
	// step guarantees shortest distances if graph doesn't
	// contain negative weight cycle.  If we get a shorter
	// path, then there is a cycle.
	temp = graph->edge;
	for (int i = 0; i < E; i++) {
		int u = temp->edge.src;
		int v = temp->edge.dest;
		int weight = temp->edge.weight;
		if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
			printf("Graph contains negative weight cycle");
			return;
		}
		temp = temp->next;
	}

	//printf("Vertex :\t\t\t ");
	//for (int i = 0; i < V; ++i)
	//	printf("%d \t", i);
	//printf("\nDistance From Source : ");
	//for (int i = 0; i < V; ++i)
	//	printf("%d \t", dist[i]);


	//int mn = findstaionnum(53502);
	if (!flow)
	{
		flow = (struct flow*)malloc(sizeof(struct flow));
		flow->dest = arr[dest]->data;
		flow->next = NULL;
	}
	//else

	struct flow* tempflow = flow;
	struct flow* temp1 = NULL;
	int currIndex = nighpors[dest];
	while (currIndex != src)
	{
		temp1 = (struct flow*)malloc(sizeof(struct flow));
		temp1->dest = arr[currIndex]->data;
		temp1->next = tempflow;
		tempflow = temp1;
		currIndex = nighpors[currIndex];
	}

	if (currIndex == src)
	{
		temp1 = (struct flow*)malloc(sizeof(struct flow));
		temp1->dest = arr[src]->data;
		//arr[src]->data
		temp1->next = tempflow;
		tempflow = temp1;
		flow = tempflow;
	}

	tempflow = flow;
	printf("The Flow is:\n");
	while (tempflow)
	{
		yellow();
		if (tempflow->next)
			printf("%ld --> ", tempflow->dest);
		else
			printf("%ld\n", tempflow->dest);
		tempflow = tempflow->next;
	}

	printf("The Distance is:%ld\n", dist[dest]);
	return;

}
void setFontSize(int a, int b)

{

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX();

	lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);

	GetCurrentConsoleFontEx(hStdOut, 0, lpConsoleCurrentFontEx);

	lpConsoleCurrentFontEx->dwFontSize.X = a;

	lpConsoleCurrentFontEx->dwFontSize.Y = b;

	SetCurrentConsoleFontEx(hStdOut, 0, lpConsoleCurrentFontEx);

}
void walkingPepole()
{
	system("color F0");
	setFontSize(10, 30);

	int w = 20;
	int z = 200000000;
	int a = 20;// 
	int m;
	//creates walking 

	while (a != -1) {
		printf("\n\n\n\n\t\t\t\t\tLoading...");
		printf("\n\n\n\n\n\n\n\n\n\n\n");
		if (a != 0) {
			printf(" o");//1
			for (m = 0; m <= a; m++) { printf(" "); }// the distance
			if (a % 2 == 0)
				printf("   o");
			else
				printf("  o");

			printf("\n/|\\");//1
			for (m = 0; m <= a; m++) { printf(" "); }// the distance 
			if (a % 2 == 0)
				printf("o/|\\");
			else
				printf("/|\\");

			printf("\n/\\");//1
			for (m = 0; m <= a; m++) { printf(" "); }
			if (a % 2 == 0)
				printf("  /\\");
			else
				printf(" o/\\");

		}// end creating walking people
		else
		{
			printf(" o"); printf("    o");
			printf("\n/|\\"); printf("<3/|\\");
			printf("\n/\\"); printf("   /\\");

			while (z != 0) { z--; }// wasting time
			z = 2000000000;
		}


		while (z != 0) { z--; }// wasting time
		z = 200000000;
		system("cls");
		a--;
	}
	//system("pause");
}
void welcome()
{
	system("color F0");
	setFontSize(10, 30);
	int x; double y;
	char alphabet1[] = "\n\n\n\n \t\t\t\t\t Welcome To Our Project  ";
	char alphabet2[] = "\n\n \t\t\t\t\t\t\t\t\t By ";
	char alphabet3[] = "\n\n \t\t\t\t\t\t\t\t\t\t\t Hala Adi Ayube ";
	printf("\n\n");
	for (x = 0; alphabet1[x] != NULL; x++)
	{
		printf("%c", alphabet1[x]);
		for (y = 0; y <= 8888888; y++)
		{
		}
	}
	printf("\n\n");
	for (x = 0; alphabet2[x] != NULL; x++)
	{
		printf("%c", alphabet2[x]);
		for (y = 0; y <= 7777777; y++)
		{
		}
	}
	printf("\n\n");
	for (x = 0; alphabet3[x] != NULL; x++)
	{
		printf("%c", alphabet3[x]);
		for (y = 0; y <= 7777777; y++)
		{
		}
	}
	getchar();

}

int getdata() {
	char a[50] = "City";

	openfile(a, 50);


	for (;;) {

		white();


		char c;

		printf("\nplease choose an option\n");
		printf("\n1.Print all cities\n");
		printf("\n2.Print Staions per city\n");
		printf("\n3.Print buses per staion\n");
		printf("\n4.Print stationnumber per staion\n");
		printf("\n5.Exit\n");
		int option1;
		scanf_s("%d", &option1);
		c = getchar();
		switch (option1)
		{

		case 1: {
			system("cls");
			printAllCities();
			break; }
		case 2: {

			system("cls");
			char cityName[100];
			char c;
			printf("\nplease enter a city\n");
			fgets(cityName, 33, stdin);
			clearstring(cityName);
			//c = getchar();
			//strcpy_s(cityName, "Tiberias");
			printAllstations(cityName);
			break;
		}
		case 3: {
			system("cls");
			char StaionName[100];
			char cityName1[100];
			printf("\nPlease enter a City name\n");
			fgets(cityName1, 33, stdin);
			clearstring(cityName1);
			//c2 = getchar();
			printf("\nPlease enter a Staion name\n");
			fgets(StaionName, 33, stdin);
			clearstring(StaionName);

			//c1 = getchar();
		//	strcpy_s(cityName1, "Afula");
			//strcpy_s(StaionName, "Harod / Cyrus");
			printStationdetails(cityName1, StaionName);
			break;
		}

		case 4: {
			system("cls");
			char StaionName1[100];
			char cityName2[100];
			printf("\nPlease enter a City name\n");
			fgets(cityName2, 33, stdin);
			clearstring(cityName2);
			//	char c2 = getchar();
			printf("\nPlease enter a Staion name\n");
			fgets(StaionName1, 33, stdin);

			clearstring(StaionName1);

			printStationNumber(cityName2, StaionName1);
			break;
		}
		case 5: {return -1;
			break;
			//}
		}
		default: {

		}
			   break;

		}
	}
	return 0;
}


int graphdata() {
	system("cls");
	char b[50] = "Station number";
	insertdataintostructs(b, 50);
	insertinto();
	nigbhoors();

	for (;;) {
		white();
		printf("\n1.print nighoors\n");
		printf("\n2.Print flow\n");
		printf("\n3.Print the index of the station Number\n");
		printf("\n4.print all edges\n");
		printf("\n5.print linked list\n");
		printf("\n6.exit\n");
		int option2;
		scanf_s("%d", &option2);
		switch (option2)
		{


		case 1: {
			system("cls");

			char vertexfromlist[50];
			int c = (atoi)(vertexfromlist);
			scanf_s("%d", &c);
			printstationnihboors(c);
			break;
		}
			  //printEdges();
		case 2: {
			system("cls");

			createEdgeList();
			struct Graph* graph = createGraph();
			char sourceNumber[50];
			char destNumber[50];
			//printEdges();
			printf("\nPlease enter Source Station number\n");
			int a = (atoi)(sourceNumber);
			scanf_s("%d", &a);
			printf("\nPlease enter Dest Station number\n");
			int b = (atoi)(destNumber);
			scanf_s("%d", &b);
			BellmanFord(graph, a, b);
			break;

		}

		case 3: {
			system("cls");

			printf("please enter a station Number");
			char num[50];
			int numstation = (atoi)(num);
			scanf_s("%d", &numstation);
			yellow();
			printf("%d the index of station Num", findstaionnum(numstation));
			break;
		}

		case 4: {
			system("cls");

			createEdgeList();
			printEdges(); break;
		}

		case 5: {
			system("cls");

			printLinkedList();
			break;
		}
		case 6: {

			return -1;
			break;
		}
		default: {

		}
			   break;



		}
	}
	return 0;
}

// Driver Code
int main()
{
	setFontSize(10, 30);
	welcome();
	cities = (struct city*)malloc(2000 * sizeof(struct city));

	if (!cities)
	{
		return -1;
	}
	for (;;) {
		//black();
		walkingPepole();
		system("color F0");
		int option3;

		//printf("Hello Welcome To Our Project\n");
		system("cls");
		printf(" Press [1] to get data  \n Press [2] to get graph  \n");
		scanf_s("%d", &option3);
		{
			switch (option3)
			{
			case 1: {
				readfromfile();
				int a;
				getdata();
				break; }
			case 2: {
				readfromfile();

				graphdata();
				break;
			}
			default: {}
				   break;
			}
		}
	}
	return 0;
}

