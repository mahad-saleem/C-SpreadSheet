
/*
                                                SIGMACELL - SPREADSHEET CREATOR/EDITOR
                                        

*/
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<windows.h>
#include<string.h>
#include<time.h>
#include<conio.h>
#include<iostream>
#include<cmath>
#define MAXSTRL 256


double RowDataMul=0;


//int RowTeller;
//double RowDataSub=0;
//char doubletostring[MAXSTRL];
/////////////////////////////////////////////Class SHEET START\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\/
class SHEET
{
private:
    class ROW;
    struct RNODE
    {
        ROW* Rows;
        RNODE* NextRow;
    };
    RNODE* Head_Row;
    int nofrows;
    int nofcells;
    int Stringchecker;
    char filename[MAXSTRL];
    int Trigger;
    double RowDataSum;
    int RowTeller;
    double RowDataSub;
    char doubletostring[MAXSTRL];
    double RowDataMul;
public:
    SHEET(void);
    ~SHEET(void);
    bool MainMenu(void);
    void CreateSheet(int,int);
    void AppendRow(ROW*);
    void CellMenu(void);
    bool EditCellData(void);
    void Data_Setter(int,int,char*);
    double Data_Getter(int,int);
    void PrintSheet(void);
    void OperationsMenu(void);
    void Add(void);
    void Subtract(void);
	void Multiply(void);
	void Divide(void);
	void Average(void);
	void SqRoot(void);
    void PrintCellData(void);
    void AddSpecific(void);
    bool AddRowRange(int,int);
    char* DoubleToString(double);
    double CheckDataType(char*);
    void InsertRow(int);
    bool DestroyRow(int);
    bool DestroyColumn(int);

    void DataSaveRow(void);
    void SaveAllData(void);
    void OpenSaved(void);
    void SubtractSpecific(void);
    bool SubRowRange(int,int,int);
    void DataSaveRow_S(void);
    void MultiplySpecific(void);
    bool MulRowRange(int,int,int);
    void DataSaveRow_M(void);
    void DivideSpecific(void);
    bool AveRowRange(int,int,int);
    void DataSaveRow_Ave(double);
    void SquareRoot(void);
    bool AddColRange(int,int,int);
	void DataSaveCol(void);
	bool SubColRange(int,int,int);
	void DataSaveCol_S(void);
	bool MulColRange(int,int,int);
	void DataSaveCol_M(void);
	bool AveColRange(int,int,int);
    void DataSaveCol_Ave(double);




//    double RowDataSum;
//    int Trigger;
//    int RowTeller;
//    char doubletostring[MAXSTRL];

};
/////////////////////////////////////////////Class ROW START\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\/
class SHEET::ROW
{
    private:
        class CELL;
        struct CNODE
        {
            CELL* Data;
            CNODE* NextCell;
        };
        CNODE* Head_Cell;
    public:
        ROW(int);
        ~ROW(void);
        void AddCell(int);
        void AppendCell(CELL*);
        void Cell_Setter(int,char*);
        double Cell_Getter(int,int*);//^^^^CHANGES^^^^^//
        void Print_Celldata(void);
        void InsertCell(int,int*);//^^^^CHANGES^^^^^//
        void Cell_Printer(int);
        char* Cell_Range(int);
        void CellDestroyer(int);
        void ColumnWiseDestroy(int);

        void Save_R(FILE*);
};
/////////////////////////////////////////////Class Cell START\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\/
class SHEET::ROW::CELL
{
    private:

        char STRING[MAXSTRL];

    public:
        CELL(void);
        //~CELL(void);
        void CELL_SET(char*);
        void CELL_DATAPRINT(void);
        double CheckDataType(int*);
        void Cprinter(void);
        char* CellRequired(void);
        void DataDestroyer(CELL*);

        void Save_C(FILE*);


};
/////////////////////////////////////////////Class Cell Functions START\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\/


SHEET::ROW::CELL::CELL(void)
{
    strcpy(STRING,"-     ");
}

void SHEET::ROW::CELL::CELL_SET(char* s)
{
    strcpy(STRING,s);
}

double SHEET::ROW::CELL::CheckDataType(int* Stringchecker)
{
    int LENGTHER=strlen(STRING);
    int ASCIIER=0;
    for (int i=0;i<(LENGTHER);i++)
    {

        ASCIIER=STRING[i];
        if ((ASCIIER!=46&&ASCIIER!=45)&&(ASCIIER>57||ASCIIER<48))
        {
            printf("\n\nError: Invalid Data Type for Mathematical Operation\n\tPRESS ANY KEY TO REVERT\n");
            getch();
            fflush(stdin);
            *Stringchecker=0;
            break;
        }
        else
        {
            double resulter=0;
            *Stringchecker=1;
            return resulter=atof(STRING);

        }
    }
}

char* SHEET::ROW::CELL::CellRequired(void)
{
	return STRING;
}

void SHEET::ROW::CELL::Cprinter(void)
{
	printf("\nCell Data: %s\n\n\tPRESS ANY KEY TO REVERT\n",STRING);
	getch();

}

void SHEET::ROW::CELL::Save_C(FILE* fp_1)
{
    int length,spaces;
	length=strlen(STRING);
	spaces=MAXSTRL-length;
	for (int i=0;i<length;i++)
			{
			    fprintf(fp_1,"%c",STRING[i]);
			}
	fprintf(fp_1,"\n");
}

void SHEET::ROW::CELL::CELL_DATAPRINT(void)
{
	printf(" %c  %10.10s  %c ",204,STRING,185);
}

void SHEET::ROW::CELL::DataDestroyer(CELL*x)
{
	
    delete x;   
}

//SHEET::ROW::CELL::~CELL(void)
//{
//    delete STRING;
//}



/////////////////////////////////////////////Class Cell Functions END\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\/

/////////////////////////////////////////////Class Cell END\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\/

/////////////////////////////////////////////Class ROW Functions START\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\/
SHEET::ROW::ROW(int n)
{
    Head_Cell=NULL;
    AddCell(n);
}

void SHEET::ROW::AddCell(int n)
{
	for (int i=0;i<n;i++)
    {

		CELL* temp_3 = new CELL();
		AppendCell(temp_3);
    }

}
void SHEET::ROW::AppendCell(CELL* c)
{

    if (Head_Cell==NULL)
    {
        Head_Cell=(CNODE*)malloc(sizeof(CNODE));
        Head_Cell->Data=c;
        Head_Cell->NextCell=NULL;
    }
    else
    {
        CNODE* temp_1=Head_Cell;
        while(temp_1->NextCell!=NULL)
        {

            temp_1=temp_1->NextCell;
        }
        temp_1->NextCell=(CNODE*)malloc(sizeof(CNODE));
        temp_1->NextCell->Data=c;
        temp_1->NextCell->NextCell=NULL;
    }
}

void SHEET::ROW::Cell_Setter(int n,char* data)//^^^^CHANGES^^^^^//
{
	CNODE * temp_1= Head_Cell;
	int count_1 = 0;
    while(temp_1!=NULL)
    {
       if(count_1==n)
       {
	    	temp_1->Data->CELL_SET(data);

       }
       count_1++;
       temp_1 = temp_1->NextCell;
    }
}

double SHEET::ROW::Cell_Getter(int n, int* Stringchecker)
{
	CNODE * temp_1= Head_Cell;
	int count_1 = 0;
    while(temp_1!=NULL)
    {
       if(count_1==n)
       {
       		double returndata;
	    	return returndata =temp_1->Data->CheckDataType(Stringchecker);

       }
       count_1++;
       temp_1 = temp_1->NextCell;
    }
}

char* SHEET::ROW::Cell_Range(int n)
{
	CNODE * temp_1= Head_Cell;
	int count_1 = 0;
    while(temp_1!=NULL)
    {
       if(count_1==n)
       {
       		char* retdata;
	    	return retdata=temp_1->Data->CellRequired();

       }
       count_1++;
       temp_1 = temp_1->NextCell;
    }
}

void SHEET::ROW::Cell_Printer(int n)
{
	CNODE * temp_1= Head_Cell;
	int count_1 = 0;
    while(temp_1!=NULL)
    {
       if(count_1==n)
       {
       		temp_1->Data->Cprinter();

       }
       count_1++;
       temp_1 = temp_1->NextCell;
    }
}


void SHEET::ROW::Print_Celldata(void)
{
	CNODE * temp_1  = Head_Cell;
     while(temp_1 != NULL)
     {

     	 temp_1->Data->CELL_DATAPRINT();
         temp_1 = temp_1->NextCell;
     }
}
void SHEET::ROW::InsertCell(int index,int* nofcells)//^^^^CHANGES^^^^^//
{
    CNODE* temp3=Head_Cell;
    if (index==0)
    {
        Head_Cell=new CNODE;
        Head_Cell->Data=new CELL;
        Head_Cell->NextCell=temp3;
    }
    else if(index==*nofcells)//^^^^CHANGES^^^^^//
    {
        while(temp3->NextCell!=NULL)
        {
            temp3=temp3->NextCell;
        }
        temp3->NextCell=new CNODE;
        temp3->NextCell->Data=new CELL;
        temp3->NextCell->NextCell=NULL;
    }
    else
    {
        CNODE* temp4=temp3->NextCell;
        for (int j=0;j<(index-1);j++)
        {
            temp3=temp4;
            temp4=temp3->NextCell;
        }
        temp3->NextCell=new CNODE;
        temp3->NextCell->Data=new CELL;
        temp3->NextCell->NextCell=temp4;

    }
}
void SHEET::ROW::CellDestroyer(int index)
{
    for (int i=0;i<(index);i++)
    {
    	CNODE* temp=Head_Cell;
        Head_Cell=Head_Cell->NextCell;
        temp->Data->DataDestroyer(temp->Data);
        delete temp;
    }
    delete Head_Cell;
}

void SHEET::ROW::ColumnWiseDestroy(int index)
{
    CNODE* temp=Head_Cell;
    if (index==0)
    {
        Head_Cell=Head_Cell->NextCell;
        temp->Data->DataDestroyer(temp->Data);
        delete temp;
    }
    else
    {
        CNODE* temp2=temp->NextCell;
        int counter=0;
        while(temp2!=NULL)
        {
            if(counter==(index-1))
            {
                temp->NextCell=temp2->NextCell;
                temp2->Data->DataDestroyer(temp2->Data);
                delete temp2;
            }
            counter++;
            temp=temp->NextCell;
            temp2=temp2->NextCell;
        }

    }
}

void SHEET::ROW::Save_R(FILE* fp)
{
    CNODE * temp_1  = Head_Cell;
     while(temp_1 != NULL)
     {
     	 temp_1->Data->Save_C(fp);
         temp_1 = temp_1->NextCell;
     }
}
SHEET::ROW::~ROW(void)
{
    CNODE* temp_0=Head_Cell;
    Head_Cell=NULL;
    while (temp_0!=NULL)
    {
        CNODE* temp_9=temp_0;
        temp_0->Data->~CELL();
        temp_0=temp_0->NextCell;
        delete(temp_9);
    }
}
/////////////////////////////////////////////Class ROW Functions END\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\/

/////////////////////////////////////////////Class ROW END\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\/

/////////////////////////////////////////////Class SHEET Functions START\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\/
SHEET::SHEET(void)
{
    Head_Row=NULL;

	nofrows=0;
	nofcells=0;
	Trigger=0;
	RowDataSum=0;
	RowTeller=0;
	RowDataSum=0.0;
	RowDataMul=0;

    MainMenu();
}

bool SHEET::MainMenu()
{
    system("cls");
    int mainoption;
    int namelength=0;
    FILE* spreadsheet;
    FILE* test;
    printf("\n\tSIGMACELL\n");
    printf("\nPlease choose an option\n");
    printf("1. CREATE NEW SPREADSHEET\n");
    printf("2. OPEN EXISTING SPREADSHEET\n");
    printf("0. EXIT\n");
    printf("Option: ");
    scanf("%d",&mainoption);
    fflush(stdin);
    switch(mainoption)
    {
        case 1:
            while(true)
            {

            printf("\nPlease enter File Name for the new sheet\n");
            scanf("%[^\n]s",filename);
            fflush(stdin);
            if ((strlen(filename)<=0))
            {
                printf("Error. Invalid FILE NAME.\n");
                continue;
            }
            strcat(filename,".txt");

            test=fopen(filename,"r");
            if(test==NULL)
                {
                    spreadsheet=fopen(filename,"w");
                    fclose(spreadsheet);
                    break;
                }
            else
                {
                    printf("\nFile with entered name already exists! Press any key to enter another name!\n");
                    getch();
                    continue;
                }
            }

            while(true)
            {
                printf("Please enter Number of Rows for the sheet\n");
                printf("Rows= ");
                scanf("%d",&nofrows);
                fflush(stdin);
                if (nofrows<=0)
                {
                    printf("Error: Row Value Cannot be Less Than or Equal to Zero\n");
                    continue;
                }
                else
                    break;
            }
            while(true)
            {
                printf("Please enter Number of Columns for the sheet\n");
                printf("Columns= ");
                scanf("%d",&nofcells);
                fflush(stdin);
                if (nofcells<=0)
                {
                    printf("Error: Column Value Cannot be Less Than or Equal to Zero\n");
                    continue;
                }
                else
                    break;
            }
            printf("\nCreating Spreadsheet\n");

            CreateSheet(nofrows,nofcells);
            CellMenu();
            break;

        case 2:
            OpenSaved();
            break;

        case 0:
            return true;
    }
}
void SHEET::CreateSheet(int m,int n)
{

    for (int i=0; i<m;i++)
    {
        ROW* temp=new ROW(n);

        AppendRow(temp);
    }

}
void SHEET::AppendRow(ROW* c)
{

    if(Head_Row==NULL)
    {
        Head_Row=(RNODE*)malloc(sizeof(RNODE));
        Head_Row->Rows=c;
        Head_Row->NextRow=NULL;
    }
    else
    {
        RNODE* temp=Head_Row;
        while(temp->NextRow!=NULL)
        {
            temp=temp->NextRow;
        }
        temp->NextRow=(RNODE*)malloc(sizeof(RNODE));
        temp->NextRow->Rows=c;
        temp->NextRow->NextRow=NULL;
    }
}

double SHEET::CheckDataType(char * str)
{
    int LENGTHER=strlen(str);
    int ASCIIER=0;
    for (int i=0;i<(LENGTHER);i++)
    {

        ASCIIER=str[i];
        if ((ASCIIER!=46)&&(ASCIIER>57||ASCIIER<48))
        {
            printf("\n\nError: Invalid Data Type for Mathematical Operation\n\tPRESS ANY KEY TO REVERT\n");
            getch();
            fflush(stdin);
            Stringchecker=0;
            if(Trigger==1)
            	DataSaveRow();
            //OperationsMenu();
        }
        else
        {
        	Stringchecker=1;
            double resulter=0;
            return resulter=atof(str);

        }

    }
}

void SHEET::CellMenu(void)
{
	while(true)
	{
        int celloption;
        system("cls");
        PrintSheet();
        printf("\n\n\tCELL OPERATIONS MENU");
        printf("\n\nPlease choose an option\n");
        printf("1. EDIT CELL DATA\n2. INSERT CELL\n3. DELETE CELL\n4. PRINT CELL DATA\n-------------------------\n5. DATA OPERATIONS\n-------------------------\n0. SAVE AND EXIT\n");
        printf("Option: ");
        scanf("%d",&celloption);
        fflush(stdin);
        if (celloption==1)
        {
            EditCellData();
        }
        else if (celloption==2)
        {
            printf("\nPlease choose an option\n");
            printf("1. Insert Row\n");
            printf("2. Insert Column\n");
            printf("Option: ");
            int addoption=0;
            scanf("%d",&addoption);
            fflush(stdin);
            if (addoption==1)
            {
                int rowindex;
                while(true)
                {
                    printf("Please enter the index where you would like to add the ROW:\nROW INDEX: ");
                    scanf("%d",&rowindex);
                    fflush(stdin);
                    if ((rowindex<0)||(rowindex>(nofrows)))
                    {
                        printf("Error. Row index OUT OF RANGE.\n");
                        continue;
                    }
                    break;
                }
                InsertRow(rowindex);
            }
            else if(addoption==2)
            {
                int colindex;
                while(true)
                {
                    printf("Please enter the index where you would like to add the COLUMN:\nCOLUMN INDEX: ");
                    scanf("%d",&colindex);
                    fflush(stdin);
                    if ((colindex<0)||(colindex>(nofcells)))
                    {
                        printf("Error. Column index OUT OF RANGE.\n");
                        continue;
                    }
                    break;
                }
                RNODE* temp=Head_Row;
                for (int i=0;i<nofrows;i++)
                {
                    temp->Rows->InsertCell(colindex,&nofcells);//^^^^CHANGES^^^^^//
                    temp=temp->NextRow;
                }
                nofcells=nofcells+1;
            }
            else
            {
                printf("Error. Invalid Option\n");
            }
        }

        else if (celloption==3)
        {
            int destroyoption;
            printf("Please choose an option\n");
            printf("\n1. Destroy Row\n");
            printf("2. Destroy Column\n");
            printf("Option: ");
            scanf("%d",&destroyoption);
            fflush(stdin);
            if (destroyoption==1)
            {
                int rowindex=0;
                if (nofrows>1)
                {
                    while(true)
                    {
                        printf("Please enter the ROW index you would like to destroy:\nROW INDEX: ");
                        scanf("%d",&rowindex);
                        fflush(stdin);
                        if ((rowindex<0)||(rowindex>(nofrows-1)))
                        {
                            printf("Error. Row index OUT OF RANGE.\n");
                            continue;
                        }
                        break;
                    }
                    DestroyRow(rowindex);
                    nofrows=nofrows-1;
                }
                else
                {
                    printf("\nOption not available.File must contain at least one row and one column\n\tPRESS ANY KEY TO CONTINUE\n");
                    getch();
                }
            }
            else
            {
                int colindex=0;
                if(nofcells>1)
                {
                    while(true)
                    {

                        printf("Please enter the COLUMN index you would like to destroy:\nCOLUMN INDEX: ");
                        scanf("%d",&colindex);
                        fflush(stdin);
                        if ((colindex<0)||(colindex>(nofcells-1)))
                        {
                            printf("Error. Column index OUT OF RANGE.\n");
                            continue;
                        }
                        break;
                    }
                    DestroyColumn(colindex);
                    nofcells=nofcells-1;
                }
                else
                {
                    printf("\nOption not available.File must contain at least one row and one column\n\tPRESS ANY KEY TO CONTINUE\n");
                    getch();
                }
            }
        }
        else if (celloption==4)
        {
            PrintCellData();
        }
        else if (celloption==5)
        {
            OperationsMenu();
        }
        else if (celloption==0)
        {
            RNODE* temp=Head_Row;
            Head_Row=NULL;
            while(temp->NextRow!=NULL)
            {
                RNODE* temp2=temp;
                temp=temp->NextRow;
                temp->Rows->CellDestroyer(nofcells);
                delete(temp2);
            }
            break;//
            //return true;
        }
        else
        {
            printf("Error. Invalid Option\n");
        }
        continue;
	}
}

void SHEET::OperationsMenu(void)
{
	while(true)
	{

	system("cls");
    PrintSheet();
    printf("\n\n\t\t<<<<<OPERATIONS MENU>>>>>\n");
	printf("\nPlease select an option :");
	printf("\n1. Add.");
	printf("\n2. Subtract.");
	printf("\n3. Multiply.");
	printf("\n4. Divide.                         0. Go back to Cell Menu.");
	printf("\n5. Average.");
	printf("\n6. Square Root.");
	printf("\nOption: ");
	char userchoice3;
	scanf("%c",&userchoice3);
	fflush(stdin);
	switch(userchoice3)
	{
		case '0':
			//SHEET::CellMenu();
			return;
			break;
		case '1':
			SHEET::Add();
			break;
		case '2':
			SHEET::Subtract();
			break;
		case '3':
			SHEET::Multiply();
			break;
		case '4':
			SHEET::Divide();
			break;
		case '5':
			SHEET::Average();
			break;
		case '6':
			SHEET::SqRoot();
			break;
        default:
            printf("Error. Invalid Entry\n");
            break;
	}
	continue;
	}
}

bool SHEET::EditCellData(void)
{
	int rowlocation,columnlocation;
    char DATA[MAXSTRL];
    while(true)
    {
        printf("\nPlease enter Row Number\n");
        printf("ROW: ");
        scanf("%d",&rowlocation);
        fflush(stdin);
        if ((rowlocation+1)<=0||(rowlocation+1)>nofrows)
        {
            printf("Error: Row Value Out of Range\n");
        }
        else
            break;
    }
    while(true)
    {
        printf("Please enter Column Number\n");
        printf("COLUMN: ");
        scanf("%d",&columnlocation);
        fflush(stdin);
        if ((columnlocation+1)<=0||(columnlocation+1)>nofcells)
        {
            printf("Error: Column Value Out of Range\n");
        }
        else
            break;
    }

    printf("Please enter the Data\n");
    printf("DATA: ");
    scanf("%[^\n]s",DATA);
    fflush(stdin);
    Data_Setter(rowlocation,columnlocation,DATA);
    while(true)
    {
        system("cls");
        PrintSheet();
        int nextdata;
        if (nofrows>1&&nofcells>1)
        {
            if (rowlocation==0&&columnlocation==0)
            {
                printf("\n1. Next Row\n");
                printf("2. Next Column\n");
                printf("0. Return to previous Menu\n");
                printf("Option: ");
                scanf("%d",&nextdata);
                fflush(stdin);
                switch(nextdata)
                {
                case 1:
                    rowlocation=rowlocation+1;
                    printf("Please enter the Data\n");
                    printf("DATA: ");
                    scanf("%[^\n]s",DATA);
                    fflush(stdin);
                    Data_Setter(rowlocation,columnlocation,DATA);
                    break;
                case 2:
                    columnlocation=columnlocation+1;
                    printf("Please enter the Data\n");
                    printf("DATA: ");
                    scanf("%[^\n]s",DATA);
                    fflush(stdin);
                    Data_Setter(rowlocation,columnlocation,DATA);
                    break;
                case 0:
                    return true;
                    break;
                default:
                    printf("Error: Invalid Option\n");
                    break;
                }
            }
            else if (rowlocation==0&&columnlocation<(nofcells-1)&&columnlocation>0)
            {
                printf("\n1. Next Row\n");
                printf("2. Next Column\n");
                printf("3. Previous Column\n");
                printf("0. Return to previous Menu\n");
                printf("Option: ");
                scanf("%d",&nextdata);
                fflush(stdin);
                switch(nextdata)
                {
                case 1:
                    rowlocation=rowlocation+1;
                    printf("Please enter the Data\n");
                    printf("DATA: ");
                    scanf("%[^\n]s",DATA);
                    fflush(stdin);
                    Data_Setter(rowlocation,columnlocation,DATA);
                    break;
                case 2:
                    columnlocation=columnlocation+1;
                    printf("Please enter the Data\n");
                    printf("DATA: ");
                    scanf("%[^\n]s",DATA);
                    fflush(stdin);
                    Data_Setter(rowlocation,columnlocation,DATA);
                    break;
                case 3:
                    columnlocation=columnlocation-1;
                    printf("Please enter the Data\n");
                    printf("DATA: ");
                    scanf("%[^\n]s",DATA);
                    fflush(stdin);
                    Data_Setter(rowlocation,columnlocation,DATA);
                    break;
                case 0:
                    return true;
                    break;
                default:
                    printf("Error: Invalid Option\n");
                    break;
                }
            }
            else if (rowlocation>0&&rowlocation<(nofrows-1)&&columnlocation==0)
            {
                printf("\n1. Next Row\n");
                printf("2. Previous Row\n");
                printf("3. Next Column\n");
                printf("0. Return to previous Menu\n");
                printf("Option: ");
                scanf("%d",&nextdata);
                fflush(stdin);
                switch(nextdata)
                {
                case 1:
                    rowlocation=rowlocation+1;
                    printf("Please enter the Data\n");
                    printf("DATA: ");
                    scanf("%[^\n]s",DATA);
                    fflush(stdin);
                    Data_Setter(rowlocation,columnlocation,DATA);
                    break;
                case 2:
                    rowlocation=rowlocation-1;
                    printf("Please enter the Data\n");
                    printf("DATA: ");
                    scanf("%[^\n]s",DATA);
                    fflush(stdin);
                    Data_Setter(rowlocation,columnlocation,DATA);
                    break;
                case 3:
                    columnlocation=columnlocation+1;
                    printf("Please enter the Data\n");
                    printf("DATA: ");
                    scanf("%[^\n]s",DATA);
                    fflush(stdin);
                    Data_Setter(rowlocation,columnlocation,DATA);
                    break;
                case 0:
                    return true;
                    break;
                default:
                    printf("Error: Invalid Option\n");
                    break;
                }
            }
            else if (rowlocation>0&&rowlocation<(nofrows-1)&&columnlocation>0&&columnlocation<(nofcells-1))
            {
                printf("\n1. Next Row\n");
                printf("2. Previous Row\n");
                printf("3. Next Column\n");
                printf("4. Previous Column\n");
                printf("0. Return to previous Menu\n");
                printf("Option: ");
                scanf("%d",&nextdata);
                fflush(stdin);
                switch(nextdata)
                {
                case 1:
                    rowlocation=rowlocation+1;
                    printf("Please enter the Data\n");
                    printf("DATA: ");
                    scanf("%[^\n]s",DATA);
                    fflush(stdin);
                    Data_Setter(rowlocation,columnlocation,DATA);
                    break;
                case 2:
                    rowlocation=rowlocation-1;
                    printf("Please enter the Data\n");
                    printf("DATA: ");
                    scanf("%[^\n]s",DATA);
                    fflush(stdin);
                    Data_Setter(rowlocation,columnlocation,DATA);
                    break;
                case 3:
                    columnlocation=columnlocation+1;
                    printf("Please enter the Data\n");
                    printf("DATA: ");
                    scanf("%[^\n]s",DATA);
                    fflush(stdin);
                    Data_Setter(rowlocation,columnlocation,DATA);
                    break;
                case 4:
                    columnlocation=columnlocation-1;
                    printf("Please enter the Data\n");
                    printf("DATA: ");
                    scanf("%[^\n]s",DATA);
                    fflush(stdin);
                    Data_Setter(rowlocation,columnlocation,DATA);
                    break;
                case 0:
                    return true;
                    break;
                default:
                    printf("Error: Invalid Option\n");
                    break;
                }
            }
            else if (rowlocation==(nofrows-1)&&columnlocation==(nofcells-1))
            {
                printf("\n1. Previous Row\n");
                printf("2. Previous Column\n");
                printf("0. Return to previous Menu\n");
                printf("Option: ");
                scanf("%d",&nextdata);
                fflush(stdin);
                switch(nextdata)
                {
                case 1:
                    rowlocation=rowlocation-1;
                    printf("Please enter the Data\n");
                    printf("DATA: ");
                    scanf("%[^\n]s",DATA);
                    fflush(stdin);
                    Data_Setter(rowlocation,columnlocation,DATA);
                    break;
                case 2:
                    columnlocation=columnlocation-1;
                    printf("Please enter the Data\n");
                    printf("DATA: ");
                    scanf("%[^\n]s",DATA);
                    fflush(stdin);
                    Data_Setter(rowlocation,columnlocation,DATA);
                    break;
                case 0:
                    return true;
                    break;
                default:
                    printf("Error: Invalid Option\n");
                    break;
                }
            }
            else if (rowlocation==(nofrows-1)&&columnlocation>0&&columnlocation<(nofcells-1))
            {
                printf("\n1. Previous Row\n");
                printf("2. Next Column\n");
                printf("3. Previous Column\n");
                printf("0. Return to previous Menu\n");
                printf("Option: ");
                scanf("%d",&nextdata);
                fflush(stdin);
                switch(nextdata)
                {
                case 1:
                    rowlocation=rowlocation-1;
                    printf("Please enter the Data\n");
                    printf("DATA: ");
                    scanf("%[^\n]s",DATA);
                    fflush(stdin);
                    Data_Setter(rowlocation,columnlocation,DATA);
                    break;
                case 2:
                    columnlocation=columnlocation+1;
                    printf("Please enter the Data\n");
                    printf("DATA: ");
                    scanf("%[^\n]s",DATA);
                    fflush(stdin);
                    Data_Setter(rowlocation,columnlocation,DATA);
                    break;
                case 3:
                    columnlocation=columnlocation-1;
                    printf("Please enter the Data\n");
                    printf("DATA: ");
                    scanf("%[^\n]s",DATA);
                    fflush(stdin);
                    Data_Setter(rowlocation,columnlocation,DATA);
                    break;
                case 0:
                    return true;
                    break;
                default:
                    printf("Error: Invalid Option\n");
                    break;
                }
            }
            else if (rowlocation>0&&rowlocation<(nofrows-1)&&columnlocation==(nofcells-1))
            {
                printf("\n1. Next Row\n");
                printf("2. Previous Row\n");
                printf("3. Previous Column\n");
                printf("0. Return to previous Menu\n");
                printf("Option: ");
                scanf("%d",&nextdata);
                fflush(stdin);
                switch(nextdata)
                {
                case 1:
                    rowlocation=rowlocation+1;
                    printf("Please enter the Data\n");
                    printf("DATA: ");
                    scanf("%[^\n]s",DATA);
                    fflush(stdin);
                    Data_Setter(rowlocation,columnlocation,DATA);
                    break;
                case 2:
                    rowlocation=rowlocation-1;
                    printf("Please enter the Data\n");
                    printf("DATA: ");
                    scanf("%[^\n]s",DATA);
                    fflush(stdin);
                    Data_Setter(rowlocation,columnlocation,DATA);
                    break;
                case 3:
                    columnlocation=columnlocation-1;
                    printf("Please enter the Data\n");
                    printf("DATA: ");
                    scanf("%[^\n]s",DATA);
                    fflush(stdin);
                    Data_Setter(rowlocation,columnlocation,DATA);
                    break;
                case 0:
                    return true;
                    break;
                default:
                    printf("Error: Invalid Option\n");
                    break;
                }
            }
            else if(rowlocation==0&&columnlocation==(nofcells-1))
            {
                printf("\n1. Next Row\n");
                printf("2. Previous Column\n");
                printf("0. Return to previous Menu\n");
                printf("Option: ");
                scanf("%d",&nextdata);
                fflush(stdin);
                switch(nextdata)
                {
                case 1:
                    rowlocation=rowlocation+1;
                    printf("Please enter the Data\n");
                    printf("DATA: ");
                    scanf("%[^\n]s",DATA);
                    fflush(stdin);
                    Data_Setter(rowlocation,columnlocation,DATA);
                    break;

                case 2:
                    columnlocation=columnlocation-1;
                    printf("Please enter the Data\n");
                    printf("DATA: ");
                    scanf("%[^\n]s",DATA);
                    fflush(stdin);
                    Data_Setter(rowlocation,columnlocation,DATA);
                    break;
                case 0:
                    return true;
                    break;
                default:
                    printf("Error: Invalid Option\n");
                    break;
                }
            }
            else if(rowlocation==(nofrows-1)&&columnlocation>0&&columnlocation<(nofcells-1))
            {
                printf("\n1. Previous Row\n");
                printf("2. Next Column\n");
                printf("3. Previous Column\n");
                printf("0. Return to previous Menu\n");
                printf("Option: ");
                scanf("%d",&nextdata);
                fflush(stdin);
                switch(nextdata)
                {
                case 1:
                    rowlocation=rowlocation-1;
                    printf("Please enter the Data\n");
                    printf("DATA: ");
                    scanf("%[^\n]s",DATA);
                    fflush(stdin);
                    Data_Setter(rowlocation,columnlocation,DATA);
                    break;
                case 2:
                    columnlocation=columnlocation+1;
                    printf("Please enter the Data\n");
                    printf("DATA: ");
                    scanf("%[^\n]s",DATA);
                    fflush(stdin);
                    Data_Setter(rowlocation,columnlocation,DATA);
                    break;
                case 3:
                    columnlocation=columnlocation-1;
                    printf("Please enter the Data\n");
                    printf("DATA: ");
                    scanf("%[^\n]s",DATA);
                    fflush(stdin);
                    Data_Setter(rowlocation,columnlocation,DATA);
                    break;
                case 0:
                    return true;
                    break;
                default:
                    printf("Error: Invalid Option\n");
                    break;
                }
            }
            else if(rowlocation==(nofrows-1)&&columnlocation==0)
            {
                printf("\n1. Previous Row\n");
                printf("2. Next Column\n");
                printf("0. Return to previous Menu\n");
                printf("Option: ");
                scanf("%d",&nextdata);
                fflush(stdin);
                switch(nextdata)
                {
                case 1:
                    rowlocation=rowlocation-1;
                    printf("Please enter the Data\n");
                    printf("DATA: ");
                    scanf("%[^\n]s",DATA);
                    fflush(stdin);
                    Data_Setter(rowlocation,columnlocation,DATA);
                    break;

                case 2:
                    columnlocation=columnlocation+1;
                    printf("Please enter the Data\n");
                    printf("DATA: ");
                    scanf("%[^\n]s",DATA);
                    fflush(stdin);
                    Data_Setter(rowlocation,columnlocation,DATA);
                    break;
                case 0:
                    return true;
                    break;
                default:
                    printf("Error: Invalid Option\n");
                    break;
                }
            }
        }
        else
        {
            if (nofrows==1)
            {
                if (columnlocation==0)
                {
                    printf("\n1. Next Column\n");
                    printf("0. Return to Previous Menu\n");
                    printf("Option: ");
                    scanf("%d",&nextdata);
                    fflush(stdin);
                    switch(nextdata)
                    {
                    case 1:
                        columnlocation=columnlocation+1;
                        printf("Please enter the Data\n");
                        printf("DATA: ");
                        scanf("%[^\n]s",DATA);
                        fflush(stdin);
                        Data_Setter(rowlocation,columnlocation,DATA);
                        break;

                    case 0:
                        return true;
                        break;
                    default:
                        printf("Error: Invalid Option\n");
                        break;
                    }

                }
                else
                {
                    if (columnlocation<(nofcells-1))
                    {
                        printf("\n1. Next Column\n");
                        printf("2. Previous Column\n");
                        printf("0. Return to Previous Menu\n");
                        printf("Option: ");
                        scanf("%d",&nextdata);
                        fflush(stdin);
                        switch(nextdata)
                        {
                        case 1:
                            columnlocation=columnlocation+1;
                            printf("Please enter the Data\n");
                            printf("DATA: ");
                            scanf("%[^\n]s",DATA);
                            fflush(stdin);
                            Data_Setter(rowlocation,columnlocation,DATA);
                            break;
                        case 2:
                            columnlocation=columnlocation-1;
                            printf("Please enter the Data\n");
                            printf("DATA: ");
                            scanf("%[^\n]s",DATA);
                            fflush(stdin);
                            Data_Setter(rowlocation,columnlocation,DATA);
                            break;

                        case 0:
                            return true;
                            break;
                        default:
                            printf("Error: Invalid Option\n");
                            break;
                        }
                    }
                    else
                    {
                        printf("\n1. Previous Column\n");
                        printf("0. Return to Previous Menu\n");
                        printf("Option: ");
                        scanf("%d",&nextdata);
                        fflush(stdin);
                        switch(nextdata)
                        {
                        case 1:
                            columnlocation=columnlocation-1;
                            printf("Please enter the Data\n");
                            printf("DATA: ");
                            scanf("%[^\n]s",DATA);
                            fflush(stdin);
                            Data_Setter(rowlocation,columnlocation,DATA);
                            break;

                        case 0:
                            return true;
                            break;
                        default:
                            printf("Error: Invalid Option\n");
                            break;
                        }
                    }
                }
            }
            else
            {
                if (rowlocation==0)
                {
                    printf("\n1. Next Row\n");
                    printf("0. Return to Previous Menu\n");
                    printf("Option: ");
                    scanf("%d",&nextdata);
                    fflush(stdin);
                    switch(nextdata)
                    {
                    case 1:
                        rowlocation=rowlocation+1;
                        printf("Please enter the Data\n");
                        printf("DATA: ");
                        scanf("%[^\n]s",DATA);
                        fflush(stdin);
                        Data_Setter(rowlocation,columnlocation,DATA);
                        break;

                    case 0:
                        return true;
                        break;
                    default:
                        printf("Error: Invalid Option\n");
                        break;
                    }
                }
                else
                {
                    if (rowlocation<(nofrows-1))
                    {
                        printf("\n1. Next ROW\n");
                        printf("2. Previous ROW\n");
                        printf("0. Return to Previous Menu\n");
                        printf("Option: ");
                        scanf("%d",&nextdata);
                        fflush(stdin);
                        switch(nextdata)
                        {
                        case 1:
                            rowlocation=rowlocation+1;
                            printf("Please enter the Data\n");
                            printf("DATA: ");
                            scanf("%[^\n]s",DATA);
                            fflush(stdin);
                            Data_Setter(rowlocation,columnlocation,DATA);
                            break;
                        case 2:
                            rowlocation=rowlocation-1;
                            printf("Please enter the Data\n");
                            printf("DATA: ");
                            scanf("%[^\n]s",DATA);
                            fflush(stdin);
                            Data_Setter(rowlocation,columnlocation,DATA);
                            break;

                        case 0:
                            return true;
                            break;
                        default:
                            printf("Error: Invalid Option\n");
                            break;
                        }
                    }
                    else
                    {
                        printf("\n1. Previous ROW\n");
                        printf("0. Return to Previous Menu\n");
                        printf("Option: ");
                        scanf("%d",&nextdata);
                        fflush(stdin);
                        switch(nextdata)
                        {
                        case 1:
                            rowlocation=rowlocation-1;
                            printf("Please enter the Data\n");
                            printf("DATA: ");
                            scanf("%[^\n]s",DATA);
                            fflush(stdin);
                            Data_Setter(rowlocation,columnlocation,DATA);
                            break;

                        case 0:
                            return true;
                            break;
                        default:
                            printf("Error: Invalid Option\n");
                            break;
                        }
                    }
                }
            }
        }

    }
}

void SHEET::Data_Setter(int m,int n,char* data)
{
	RNODE * temp = Head_Row;
    int count_count = 0;
    while(temp!=NULL)
    {
       if(count_count==m)
       {

		temp->Rows->Cell_Setter(n,data);//^^^^CHANGES^^^^^//

       }
       count_count++;
       temp = temp->NextRow;
    }

}

double SHEET::Data_Getter(int m,int n)
{
	RNODE * temp = Head_Row;
    int count_count = 0;
    while(temp!=NULL)
    {
       if(count_count==m)
       {
	   	double returndata_2;
		return returndata_2=temp->Rows->Cell_Getter(n,&Stringchecker);

       }
       count_count++;
       temp = temp->NextRow;
    }
}
void SHEET::SaveAllData(void)
{
    FILE* fp;
	fp=fopen(filename,"w");
	fprintf(fp,"%d\n",nofrows);
	fprintf(fp,"%d\n",nofcells);

	RNODE * temp  = Head_Row;

     while(temp != NULL)
     {
         temp->Rows->Save_R(fp);
         temp = temp->NextRow;
         fprintf(fp,"*_*\n");
     }
	 fclose(fp);
}

void SHEET::OpenSaved(void)
{
	FILE* fp;
	int namelength;
	printf("\n\tOPEN MENU\n");
	printf("\nPlease enter File Name of the file name\n");
    scanf("%[^\n]s",filename);
    fflush(stdin);
    strcat(filename,".txt");
    fp=fopen(filename,"r");
    if(fp==NULL)
		{
			printf("\nNo File found!!!\n\n");
			printf("Press any key to go to Main Menu.\n");
			getch();
			MainMenu();
		}
	else
		{
			int val=0;
			fscanf(fp,"%d",&nofrows);
			fscanf(fp,"%d",&nofcells);
			CreateSheet(nofrows,nofcells);
			fseek(fp,2,SEEK_CUR);
			for(int i=0;i<nofrows;i++)
				{
				for(int j=0;j<nofcells;j++)
					{

						char dataloading[MAXSTRL+1];
						fscanf(fp,"%s",dataloading);
						fflush(stdin);
						Data_Setter(i,j,dataloading);
					}
					char aiwien[50];
					fscanf(fp,"%s",aiwien);

				}

			fclose(fp);
			CellMenu();

		}
}

void SHEET::PrintSheet(void)
{

	RNODE * temp  = Head_Row;
	int counter=0;
	printf("    ");
	for (int i=0;i<nofcells;i++)
    {
        printf(" %c    %05d  %4c ",211,i,189);
    }
    printf("\n");
    for (int i=0;i<nofcells;i++)
    {
        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
    }
     while(temp != NULL)
     {
     	 printf("\n%03d|",counter);
     	 counter++;
         temp->Rows->Print_Celldata();
         temp = temp->NextRow;
     }
    SaveAllData();

}
void SHEET::InsertRow(int index)
{
    RNODE* temp=Head_Row;
    if (index==0)
    {
        Head_Row=new RNODE;
        Head_Row->Rows=new ROW(nofcells);
        Head_Row->NextRow=temp;
        nofrows=nofrows+1;
    }
    else if (index==nofrows)
    {
        while(temp->NextRow!=NULL)
        {
            temp=temp->NextRow;
        }
        temp->NextRow=new RNODE;
        temp->NextRow->Rows=new ROW(nofcells);
        temp->NextRow->NextRow=NULL;
        nofrows=nofrows+1;
    }
    else
    {
        RNODE* temp=Head_Row;
        RNODE* temp2=temp->NextRow;
        for (int i=0;i<(index-1);i++)
        {
            temp=temp->NextRow;
            temp2=temp->NextRow;
        }
        temp->NextRow=new RNODE;
        temp->NextRow->Rows=new ROW(nofcells);
        temp->NextRow->NextRow=temp2;
        nofrows=nofrows+1;
    }
}

void SHEET::PrintCellData(void)
{
	int m,n;
    while(true)
    {
        printf("\nPlease enter Row Number\n");
        printf("ROW: ");
        scanf("%d",&m);
        fflush(stdin);
        if ((m+1)<=0||(m+1)>nofrows)
        {
            printf("Error: Row Value Out of Range\n");
        }
        else
            break;
    }
    while(true)
    {
        printf("Please enter Column Number\n");
        printf("COLUMN: ");
        scanf("%d",&n);
        fflush(stdin);
        if ((n+1)<=0||(n+1)>nofcells)
        {
            printf("Error: Column Value Out of Range\n");
        }
        else
            break;
    }

	RNODE * temp = Head_Row;
    int count_count = 0;
    while(temp!=NULL)
    {
       if(count_count==m)
       {
	   	temp->Rows->Cell_Printer(n);

       }
       count_count++;
       temp = temp->NextRow;
    }
}
//========================Opertaions detail functions====================
char* SHEET::DoubleToString(double dd)
{
    snprintf(doubletostring,MAXSTRL,"%f",dd);
    return (doubletostring);
}

bool SHEET::AddRowRange(int m1,int m2)
{
	Trigger=1;/*new*/
	RNODE * temp = Head_Row;
    int count_count = 0;
    while(temp!=NULL)
    {
       if(count_count==m1)
       {
            char* retdata_2;
            retdata_2=temp->Rows->Cell_Range(m2);
            temp = temp->NextRow;
            double retdata_3;
            retdata_3=CheckDataType(retdata_2);
			system("cls");
    		PrintSheet();
            RowDataSum=RowDataSum+retdata_3;
            printf("\nPrevious Data Added: %f",retdata_3);
            printf("\nSum: %f\n",RowDataSum);
            return true;
       }
       count_count++;
       temp = temp->NextRow;
    }
    return true;
}

void SHEET::DataSaveRow(void)
{
	Trigger=0;
	int selection;
	while(true)
	{
	
	printf("\nPlease enter a Choice:\n");
	printf("1. To save Sum in an existing Column.\n2. To save Sum in a New Column\nCHOICE:\n");/////////////////////////////////////
	scanf("%d",&selection);
	fflush(stdin);
	if(selection==1 || selection==2)
		break;
	else
		continue;
	}
	if(selection==1)
	{
		int rowlocation,columnlocation;
	    while(true)
	    {
	        printf("\nPlease enter Row Number\n");
	        printf("ROW: ");
	        scanf("%d",&rowlocation);
	        fflush(stdin);
	        if ((rowlocation+1)<=0||(rowlocation+1)>nofrows)
	        {
	            printf("Error: Row Value Out of Range\n");
	        }
	        else
	            break;
	    }
	    while(true)
	    {
	        printf("Please enter Column Number\n");
	        printf("COLUMN: ");
	        scanf("%d",&columnlocation);
	        fflush(stdin);
	        if ((columnlocation+1)<=0||(columnlocation+1)>nofcells)
	        {
	            printf("Error: Column Value Out of Range\n");
	        }
	        else
	            break;
	    }
	    Data_Setter(rowlocation,columnlocation,DoubleToString(RowDataSum));
	}
	else if(selection==2)
	{
		RNODE* temp=Head_Row;
        for (int i=0;i<nofrows;i++)
            {
                temp->Rows->InsertCell(nofcells,&nofcells);
                temp=temp->NextRow;
            }
        nofcells=nofcells+1;
        Data_Setter(RowTeller,(nofcells-1),DoubleToString(RowDataSum));
	}
	//OperationsMenu();
	
}
//========================================>> new add <<==================================================

//******************************************column ka kaam **************************************************

bool SHEET::AddColRange(int m1,int m2,int count_temp)
{
	Trigger=1;/*new*/
	RNODE * temp = Head_Row;
    int count_count = 0;
    while(temp!=NULL)
    {
       if(count_count==m1)
       {
            char* retdata_2;
            retdata_2=temp->Rows->Cell_Range(m2);
            temp = temp->NextRow;
            double retdata_3;
            retdata_3=CheckDataType(retdata_2);
			system("cls");
    		PrintSheet();
			if(count_temp==1)
			{
				RowDataSum=retdata_3;
				printf("\nSum: %f",retdata_3);
				return true;
			}
            RowDataSum=RowDataSum+retdata_3;
            printf("\nPrevious Data Added: %f",retdata_3);
            printf("\nSum: %f\n",RowDataSum);
            return true;
       }
       count_count++;
       temp = temp->NextRow;
    }
    return true;
}

void SHEET::DataSaveCol(void)
{
	Trigger=0;
	int selection;
	while(true)
	{
	
	printf("\nPlease enter a Choice:\n");
	printf("1. To save Sum in an existing Row.\n2. To save Sum in a New Row\nCHOICE:\n");/////////////////////////////////////
	scanf("%d",&selection);
	fflush(stdin);
	if(selection==1 || selection==2)
		break;
	else
		continue;
	}
	if(selection==1)
	{
		int rowlocation,columnlocation;
	    while(true)
	    {
	        printf("\nPlease enter Row Number\n");
	        printf("ROW: ");
	        scanf("%d",&rowlocation);
	        fflush(stdin);
	        if ((rowlocation+1)<=0||(rowlocation+1)>nofrows)
	        {
	            printf("Error: Row Value Out of Range\n");
	        }
	        else
	            break;
	    }
	    while(true)
	    {
	        printf("Please enter Column Number\n");
	        printf("COLUMN: ");
	        scanf("%d",&columnlocation);
	        fflush(stdin);
	        if ((columnlocation+1)<=0||(columnlocation+1)>nofcells)
	        {
	            printf("Error: Column Value Out of Range\n");
	        }
	        else
	            break;
	    }
	    Data_Setter(rowlocation,columnlocation,DoubleToString(RowDataSum));
	}
	else if(selection==2)
	{
		InsertRow(nofrows);
		Data_Setter((nofrows-1),RowTeller,DoubleToString(RowDataSum));
	}
	//OperationsMenu();
	
}

bool SHEET::SubColRange(int m1,int m2,int count_temp)
{
	Trigger=1;/*new*/
	RNODE * temp = Head_Row;
    int count_count = 0;
    while(temp!=NULL)
    {
       if(count_count==m1)
       {
            char* retdata_2;
            retdata_2=temp->Rows->Cell_Range(m2);
            temp = temp->NextRow;
            double retdata_3;
            retdata_3=CheckDataType(retdata_2);
			system("cls");
   		 	PrintSheet();
			if(count_temp==1)
			{
				RowDataSub=retdata_3;
				printf("\nDifference: %f",retdata_3);
				return true;
			}
            RowDataSub=RowDataSub-retdata_3;
            printf("\nPrevious Data Subtracted: %f",retdata_3);
            printf("\nDifference: %f\n",RowDataSub);
            return true;
       }
       count_count++;
       temp = temp->NextRow;
    }
    return true;
}

void SHEET::DataSaveCol_S(void)
{
	Trigger=0;
	int selection;
	while(true)
	{
	
	printf("\nPlease enter a Choice:\n");
	printf("1. To save Difference in an existing Row.\n2. To save Difference in a New Row\nCHOICE:\n");/////////////////////////////////////
	scanf("%d",&selection);
	fflush(stdin);
	if(selection==1 || selection==2)
		break;
	else
		continue;
	}
	if(selection==1)
	{
		int rowlocation,columnlocation;
	    while(true)
	    {
	        printf("\nPlease enter Row Number\n");
	        printf("ROW: ");
	        scanf("%d",&rowlocation);
	        fflush(stdin);
	        if ((rowlocation+1)<=0||(rowlocation+1)>nofrows)
	        {
	            printf("Error: Row Value Out of Range\n");
	        }
	        else
	            break;
	    }
	    while(true)
	    {
	        printf("Please enter Column Number\n");
	        printf("COLUMN: ");
	        scanf("%d",&columnlocation);
	        fflush(stdin);
	        if ((columnlocation+1)<=0||(columnlocation+1)>nofcells)
	        {
	            printf("Error: Column Value Out of Range\n");
	        }
	        else
	            break;
	    }
	    Data_Setter(rowlocation,columnlocation,DoubleToString(RowDataSub));
	}
	else if(selection==2)
	{
		InsertRow(nofrows);
		Data_Setter((nofrows-1),RowTeller,DoubleToString(RowDataSub));
	}
	//OperationsMenu();
	
}

bool SHEET::MulColRange(int m1,int m2,int count_temp)
{
	Trigger=1;/*new*/
	RNODE * temp = Head_Row;
    int count_count = 0;
    while(temp!=NULL)
    {
       if(count_count==m1)
       {
            char* retdata_2;
            retdata_2=temp->Rows->Cell_Range(m2);
            temp = temp->NextRow;
            double retdata_3;
            retdata_3=CheckDataType(retdata_2);
			system("cls");
    		PrintSheet();
			if(count_temp==1)
			{
				RowDataMul=retdata_3;
				printf("\nProduct: %f",retdata_3);
				return true;
			}
            RowDataMul=RowDataMul*retdata_3;
            printf("\nPrevious Data Multiplied: %f",retdata_3);
            printf("\nProduct: %f\n",RowDataMul);
            return true;
       }
       count_count++;
       temp = temp->NextRow;
    }
    return true;
}

void SHEET::DataSaveCol_M(void)
{
	Trigger=0;
	int selection;
	while(true)
	{
	
	printf("\nPlease enter a Choice:\n");
	printf("1. To save Product in an existing Row.\n2. To save Product in a New Row\nCHOICE:\n");/////////////////////////////////////
	scanf("%d",&selection);
	fflush(stdin);
	if(selection==1 || selection==2)
		break;
	else
		continue;
	}
	if(selection==1)
	{
		int rowlocation,columnlocation;
	    while(true)
	    {
	        printf("\nPlease enter Row Number\n");
	        printf("ROW: ");
	        scanf("%d",&rowlocation);
	        fflush(stdin);
	        if ((rowlocation+1)<=0||(rowlocation+1)>nofrows)
	        {
	            printf("Error: Row Value Out of Range\n");
	        }
	        else
	            break;
	    }
	    while(true)
	    {
	        printf("Please enter Column Number\n");
	        printf("COLUMN: ");
	        scanf("%d",&columnlocation);
	        fflush(stdin);
	        if ((columnlocation+1)<=0||(columnlocation+1)>nofcells)
	        {
	            printf("Error: Column Value Out of Range\n");
	        }
	        else
	            break;
	    }
	    Data_Setter(rowlocation,columnlocation,DoubleToString(RowDataMul));
	}
	else if(selection==2)
	{
		InsertRow(nofrows);
		Data_Setter((nofrows-1),RowTeller,DoubleToString(RowDataMul));
	}
	//OperationsMenu();
	
}

bool SHEET::AveColRange(int m1,int m2,int count_temp)
{
	Trigger=1;/*new*/
	RNODE * temp = Head_Row;
    int count_count = 0;
    while(temp!=NULL)
    {
       if(count_count==m1)
       {
            char* retdata_2;
            retdata_2=temp->Rows->Cell_Range(m2);
            temp = temp->NextRow;
            double retdata_3;
            retdata_3=CheckDataType(retdata_2);
			system("cls");
    		PrintSheet();
			if(count_temp==1)
			{
				RowDataSum=retdata_3;
				printf("\nPrevious value chosen: %f",retdata_3);
				return true;
			}
            RowDataSum=RowDataSum+retdata_3;
            printf("\nPrevious value chosen: %f",retdata_3);
            return true;
       }
       count_count++;
       temp = temp->NextRow;
    }
    return true;
}

void SHEET::DataSaveCol_Ave(double average)
{
	Trigger=0;
	int selection;
	while(true)
	{
	
	printf("\nPlease enter a Choice:\n");
	printf("1. To save Product in an existing Row.\n2. To save Product in a New Row\nCHOICE:\n");/////////////////////////////////////
	scanf("%d",&selection);
	fflush(stdin);
	if(selection==1 || selection==2)
		break;
	else
		continue;
	}
	if(selection==1)
	{
		int rowlocation,columnlocation;
	    while(true)
	    {
	        printf("\nPlease enter Row Number\n");
	        printf("ROW: ");
	        scanf("%d",&rowlocation);
	        fflush(stdin);
	        if ((rowlocation+1)<=0||(rowlocation+1)>nofrows)
	        {
	            printf("Error: Row Value Out of Range\n");
	        }
	        else
	            break;
	    }
	    while(true)
	    {
	        printf("Please enter Column Number\n");
	        printf("COLUMN: ");
	        scanf("%d",&columnlocation);
	        fflush(stdin);
	        if ((columnlocation+1)<=0||(columnlocation+1)>nofcells)
	        {
	            printf("Error: Column Value Out of Range\n");
	        }
	        else
	            break;
	    }
	    Data_Setter(rowlocation,columnlocation,DoubleToString(average));
	}
	else if(selection==2)
	{
		InsertRow(nofrows);
		Data_Setter((nofrows-1),RowTeller,DoubleToString(average));
	}
	//OperationsMenu();
	
}

//***********************************************************************************************************
bool SHEET::MulRowRange(int m1,int m2,int count_temp)
{
	Trigger=1;/*new*/
	RNODE * temp = Head_Row;
    int count_count = 0;
    while(temp!=NULL)
    {
       if(count_count==m1)
       {
            char* retdata_2;
            retdata_2=temp->Rows->Cell_Range(m2);
            temp = temp->NextRow;
            double retdata_3;
            retdata_3=CheckDataType(retdata_2);
			system("cls");
    		PrintSheet();
			if(count_temp==1)
			{
				RowDataMul=retdata_3;
				printf("\nProduct: %f",retdata_3);
				return true;
			}
            RowDataMul=RowDataMul*retdata_3;
            printf("\nPrevious Data Multiplied: %f",retdata_3);
            printf("\nProduct: %f\n",RowDataMul);
            return true;
       }
       count_count++;
       temp = temp->NextRow;
    }
    return true;
}

void SHEET::DataSaveRow_M(void)
{
	Trigger=0;
	int selection;
	while(true)
	{
	
	printf("\nPlease enter a Choice:\n");
	printf("1. To save Product in an existing Column.\n2. To save Product in a New Column\nCHOICE:\n");/////////////////////////////////////
	scanf("%d",&selection);
	fflush(stdin);
	if(selection==1 || selection==2)
		break;
	else
		continue;
	}
	if(selection==1)
	{
		int rowlocation,columnlocation;
	    while(true)
	    {
	        printf("\nPlease enter Row Number\n");
	        printf("ROW: ");
	        scanf("%d",&rowlocation);
	        fflush(stdin);
	        if ((rowlocation+1)<=0||(rowlocation+1)>nofrows)
	        {
	            printf("Error: Row Value Out of Range\n");
	        }
	        else
	            break;
	    }
	    while(true)
	    {
	        printf("Please enter Column Number\n");
	        printf("COLUMN: ");
	        scanf("%d",&columnlocation);
	        fflush(stdin);
	        if ((columnlocation+1)<=0||(columnlocation+1)>nofcells)
	        {
	            printf("Error: Column Value Out of Range\n");
	        }
	        else
	            break;
	    }
	    Data_Setter(rowlocation,columnlocation,DoubleToString(RowDataMul));
	}
	else if(selection==2)
	{
		RNODE* temp=Head_Row;
        for (int i=0;i<nofrows;i++)
            {
                temp->Rows->InsertCell(nofcells,&nofcells);
                temp=temp->NextRow;
            }
        nofcells=nofcells+1;
        Data_Setter(RowTeller,(nofcells-1),DoubleToString(RowDataMul));
	}
	//OperationsMenu();
	
}

bool SHEET::SubRowRange(int m1,int m2,int count_temp)
{
	Trigger=1;/*new*/
	RNODE * temp = Head_Row;
    int count_count = 0;
    while(temp!=NULL)
    {
       if(count_count==m1)
       {
            char* retdata_2;
            retdata_2=temp->Rows->Cell_Range(m2);
            temp = temp->NextRow;
            double retdata_3;
            retdata_3=CheckDataType(retdata_2);
			system("cls");
    		PrintSheet();
			if(count_temp==1)
			{
				RowDataSub=retdata_3;
				printf("\nDifference: %f",retdata_3);
				return true;
			}
            RowDataSub=RowDataSub-retdata_3;
            printf("\nPrevious Data Subtracted: %f",retdata_3);
            printf("\nDifference: %f\n",RowDataSub);
            return true;
       }
       count_count++;
       temp = temp->NextRow;
    }
    return true;
}

void SHEET::DataSaveRow_S(void)
{
	Trigger=0;
	int selection;
	while(true)
	{
	
	printf("\nPlease enter a Choice:\n");
	printf("1. To save Difference in an existing Column.\n2. To save Difference in a New Column\nCHOICE:\n");/////////////////////////////////////
	scanf("%d",&selection);
	fflush(stdin);
	if(selection==1 || selection==2)
		break;
	else
		continue;
	}
	if(selection==1)
	{
		int rowlocation,columnlocation;
	    while(true)
	    {
	        printf("\nPlease enter Row Number\n");
	        printf("ROW: ");
	        scanf("%d",&rowlocation);
	        fflush(stdin);
	        if ((rowlocation+1)<=0||(rowlocation+1)>nofrows)
	        {
	            printf("Error: Row Value Out of Range\n");
	        }
	        else
	            break;
	    }
	    while(true)
	    {
	        printf("Please enter Column Number\n");
	        printf("COLUMN: ");
	        scanf("%d",&columnlocation);
	        fflush(stdin);
	        if ((columnlocation+1)<=0||(columnlocation+1)>nofcells)
	        {
	            printf("Error: Column Value Out of Range\n");
	        }
	        else
	            break;
	    }
	    Data_Setter(rowlocation,columnlocation,DoubleToString(RowDataSub));
	}
	else if(selection==2)
	{
		RNODE* temp=Head_Row;
        for (int i=0;i<nofrows;i++)
            {
                temp->Rows->InsertCell(nofcells,&nofcells);
                temp=temp->NextRow;
            }
        nofcells=nofcells+1;
        Data_Setter(RowTeller,(nofcells-1),DoubleToString(RowDataSub));
	}
	//OperationsMenu();
	
}

bool SHEET::AveRowRange(int m1,int m2,int count_temp)
{
	Trigger=1;/*new*/
	RNODE * temp = Head_Row;
    int count_count = 0;
    while(temp!=NULL)
    {
       if(count_count==m1)
       {
            char* retdata_2;
            retdata_2=temp->Rows->Cell_Range(m2);
            temp = temp->NextRow;
            double retdata_3;
            retdata_3=CheckDataType(retdata_2);
			system("cls");
    		PrintSheet();
			if(count_temp==1)
			{
				RowDataSum=retdata_3;
				printf("\nPrevious value chosen: %f",retdata_3);
				return true;
			}
            RowDataSum=RowDataSum+retdata_3;
            printf("\nPrevious value chosen: %f",retdata_3);
            return true;
       }
       count_count++;
       temp = temp->NextRow;
    }
    
    return true;
}

void SHEET::DataSaveRow_Ave(double average)
{
	Trigger=0;
	int selection;
	while(true)
	{
	
	printf("\nPlease enter a Choice:\n");
	printf("1. To save Average in an existing Column.\n2. To save Average in a New Column\nCHOICE:\n");/////////////////////////////////////
	scanf("%d",&selection);
	fflush(stdin);
	if(selection==1 || selection==2)
		break;
	else
		continue;
	}
	if(selection==1)
	{
		int rowlocation,columnlocation;
	    while(true)
	    {
	        printf("\nPlease enter Row Number\n");
	        printf("ROW: ");
	        scanf("%d",&rowlocation);
	        fflush(stdin);
	        if ((rowlocation+1)<=0||(rowlocation+1)>nofrows)
	        {
	            printf("Error: Row Value Out of Range\n");
	        }
	        else
	            break;
	    }
	    while(true)
	    {
	        printf("Please enter Column Number\n");
	        printf("COLUMN: ");
	        scanf("%d",&columnlocation);
	        fflush(stdin);
	        if ((columnlocation+1)<=0||(columnlocation+1)>nofcells)
	        {
	            printf("Error: Column Value Out of Range\n");
	        }
	        else
	            break;
	    }
	    Data_Setter(rowlocation,columnlocation,DoubleToString(average));
	}
	else if(selection==2)
	{
		RNODE* temp=Head_Row;
        for (int i=0;i<nofrows;i++)
            {
                temp->Rows->InsertCell(nofcells,&nofcells);
                temp=temp->NextRow;
            }
        nofcells=nofcells+1;
        Data_Setter(RowTeller,(nofcells-1),DoubleToString(average));
	}
//	OperationsMenu();
	
}

//==========================================================================================================================================================
void SHEET::AddSpecific(void)
{
	int m,n;
	char DATA[MAXSTRL];
    while(true)
    {
        printf("\nPlease enter Row Number\n");
        printf("ROW: ");
        scanf("%d",&m);
        fflush(stdin);
        if ((m+1)<=0||(m+1)>nofrows)
        {
            printf("Error: Row Value Out of Range\n");
        }
        else
            break;
    }
    while(true)
    {
        printf("Please enter Column Number\n");
        printf("COLUMN: ");
        scanf("%d",&n);
        fflush(stdin);
        if ((n+1)<=0||(n+1)>nofcells)
        {
            printf("Error: Column Value Out of Range\n");
        }
        else
            break;
    }
    printf("Please enter the Data\n");
    printf("DATA: ");
    scanf("%[^\n]s",DATA);
    fflush(stdin);
    double data_2;
    data_2=CheckDataType(DATA);
    if(Stringchecker==0)
    {
    	return;
	}
	else if (Stringchecker==1)
	{
		double data;
		data=Data_Getter(m,n);
		if(Stringchecker==0)
		{
			return;
		}
		else if(Stringchecker==1)
		{
		double data_1;
		data_1=data+data_2;
		char* temp;
		temp=DoubleToString(data_1);
		Data_Setter(m,n,temp);
		}
	}
}

void SHEET::SubtractSpecific(void)
{
	int m,n;
	char DATA[MAXSTRL];
    while(true)
    {
        printf("\nPlease enter Row Number\n");
        printf("ROW: ");
        scanf("%d",&m);
        fflush(stdin);
        if ((m+1)<=0||(m+1)>nofrows)
        {
            printf("Error: Row Value Out of Range\n");
        }
        else
            break;
    }
    while(true)
    {
        printf("Please enter Column Number\n");
        printf("COLUMN: ");
        scanf("%d",&n);
        fflush(stdin);
        if ((n+1)<=0||(n+1)>nofcells)
        {
            printf("Error: Column Value Out of Range\n");
        }
        else
            break;
    }
    printf("Please enter the Data\n");
    printf("DATA: ");
    scanf("%[^\n]s",DATA);
    fflush(stdin);
    double data_2;
    data_2=CheckDataType(DATA);
    if(Stringchecker==0)
    {
    	return;
	}
	else if (Stringchecker==1)
	{
		double data;
		data=Data_Getter(m,n);
		if(Stringchecker==0)
		{
			return;
		}
		else if(Stringchecker==1)
		{
		double data_1;
		data_1=data-data_2;
		Data_Setter(m,n,DoubleToString(data_1));
		}
	}

}

void SHEET::MultiplySpecific(void)
{
	int m,n;
	char DATA[MAXSTRL];
    while(true)
    {
        printf("\nPlease enter Row Number\n");
        printf("ROW: ");
        scanf("%d",&m);
        fflush(stdin);
        if ((m+1)<=0||(m+1)>nofrows)
        {
            printf("Error: Row Value Out of Range\n");
        }
        else
            break;
    }
    while(true)
    {
        printf("Please enter Column Number\n");
        printf("COLUMN: ");
        scanf("%d",&n);
        fflush(stdin);
        if ((n+1)<=0||(n+1)>nofcells)
        {
            printf("Error: Column Value Out of Range\n");
        }
        else
            break;
    }
    printf("Please enter the Data\n");
    printf("DATA: ");
    scanf("%[^\n]s",DATA);
    fflush(stdin);
    double data_2;
    data_2=CheckDataType(DATA);
    if(Stringchecker==0)
    {
    	return;
	}
	else if (Stringchecker==1)
	{
		double data;
		data=Data_Getter(m,n);
		if(Stringchecker==0)
		{
			return;
		}
		else if(Stringchecker==1)
		{
		double data_1;
		data_1=data*data_2;
		Data_Setter(m,n,DoubleToString(data_1));
		}
	}

}

void SHEET::DivideSpecific(void)
{
	int m,n;
	char DATA[MAXSTRL];
    while(true)
    {
        printf("\nPlease enter Row Number\n");
        printf("ROW: ");
        scanf("%d",&m);
        fflush(stdin);
        if ((m+1)<=0||(m+1)>nofrows)
        {
            printf("Error: Row Value Out of Range\n");
        }
        else
            break;
    }
    while(true)
    {
        printf("Please enter Column Number\n");
        printf("COLUMN: ");
        scanf("%d",&n);
        fflush(stdin);
        if ((n+1)<=0||(n+1)>nofcells)
        {
            printf("Error: Column Value Out of Range\n");
        }
        else
            break;
    }
    printf("Please enter the Data\n");
    printf("DATA: ");
    scanf("%[^\n]s",DATA);
    fflush(stdin);
    double data_2;
    data_2=CheckDataType(DATA);
    if(Stringchecker==0)
    {
    	return;
	}
	else if (Stringchecker==1)
	{
		double data;
		data=Data_Getter(m,n);
		if(Stringchecker==0)
		{
			return;
		}
		else if(Stringchecker==1)
		{
		double data_1;
		data_1=data/data_2;
		Data_Setter(m,n,DoubleToString(data_1));
		}
	}

}

void SHEET::SquareRoot(void)
{
	int m,n;
	char DATA[MAXSTRL];
    while(true)
    {
        printf("\nPlease enter Row Number\n");
        printf("ROW: ");
        scanf("%d",&m);
        fflush(stdin);
        if ((m+1)<=0||(m+1)>nofrows)
        {
            printf("Error: Row Value Out of Range\n");
        }
        else
            break;
    }
    while(true)
    {
        printf("Please enter Column Number\n");
        printf("COLUMN: ");
        scanf("%d",&n);
        fflush(stdin);
        if ((n+1)<=0||(n+1)>nofcells)
        {
            printf("Error: Column Value Out of Range\n");
        }
        else
            break;
    }
    
		double data;
		data=Data_Getter(m,n);
		if(Stringchecker==0)
		{
			return;
		}
		else if(Stringchecker==1)
		{
		double data_1;
		data_1=pow(data,0.5);
		Data_Setter(m,n,DoubleToString(data_1));
		}

}
// ======================================================================

/*                                OPERATINS FUNCTIONS
*/

void SHEET::Add(void)
{

	system("cls");
    PrintSheet();
	printf("\n\nPlease select an option:");
	printf("\n1. Add a specific No. to a cell.");
	printf("\n2. Add Row Range.");
	printf("\n3. Add Column Range.");
	printf("\n0. Go back to Operations Menu.");
	printf("\nOption: ");
	char userchoice4;
	scanf("%c",&userchoice4);
	fflush(stdin);
	switch(userchoice4)
	{
		case '0':
			return;
			break;
		case '1':
			AddSpecific();
			break;
		case '2':
			RowDataSum=0;
			int m1;
            while(true)
            {
                printf("\nPlease enter the Row Number\n");
                printf("ROW: ");
                scanf("%d",&m1);
                RowTeller=m1;
                fflush(stdin);
                if ((m1+1)<=0||(m1+1)>nofrows)
                {
                    printf("Error: Row Value Out of Range\n");
                }
                else
                    break;
            }
            
            while(true)
            {
                int m2;
                while(true)
                {
                    printf("Please enter COLUMN\n");
                    printf("COLUMN: ");
                    scanf("%d",&m2);
                    fflush(stdin);
                    if ((m2+1)<=0||(m2+1)>nofcells)
                    {
                        printf("Error: Row Value Out of Range\n");
                    }
                    else
                        break;
                }
                AddRowRange(m1,m2);
                printf("\nTo Add another Column, Press 1 or Press any other key to exit.\n");
                if(getch()=='1')
                    continue;
                else
                    {
					DataSaveRow();
					break;
					}

            }
			break;
		case '3':
			RowDataSum=0;
			int m3;
            while(true)
            {
                printf("\nPlease enter the Column Number\n");
                printf("Column: ");
                scanf("%d",&m3);
                RowTeller=m3;
                fflush(stdin);
                if ((m3+1)<=0||(m3+1)>nofcells)
                {
                    printf("Error: Row Value Out of Range\n");
                }
                else
                    break;
            }
            int count_temp=1;
            while(true)
            {
                int m4;
                while(true)
                {
                    printf("Please enter ROW\n");
                    printf("ROW: ");
                    scanf("%d",&m4);
                    fflush(stdin);
                    if ((m4+1)<=0||(m4+1)>nofrows)
                    {
                        printf("Error: Row Value Out of Range\n");
                    }
                    else
                        break;
                }
                AddColRange(m4,m3,count_temp);
                printf("\nTo Add another Row, Press 1 or Press any other key to exit.\n");
                if(getch()=='1')
                	{
                	count_temp++;
                    continue;
                	}    
                else
                    {
					DataSaveCol();
					break;
					}

            }
			break;


	}
	

}
// =====================================> new Add <=============================================================
void SHEET::Subtract(void)
{

	system("cls");
    PrintSheet();
	printf("\nPlease select an option:");
	printf("\n1. Subtract a specific No. from a cell.");
	printf("\n2. Subtract Row range.");
	printf("\n3. Subtract Column range.");
	printf("\n0. Go back.");
	printf("\nOption: ");
	char userchoice5;
	scanf("%c",&userchoice5);
	fflush(stdin);
	int count_temp=1;
	switch(userchoice5)
	{
		case '0':
			return;
			break;
		case '1':
			SubtractSpecific();
			break;
		case '2':
			RowDataSub=0;
			int m1;
			
            while(true)
            {
                printf("\nPlease enter the Row Number\n");
                printf("ROW: ");
                scanf("%d",&m1);
                RowTeller=m1;
                fflush(stdin);
                if ((m1+1)<=0||(m1+1)>nofrows)
                {
                    printf("Error: Row Value Out of Range\n");
                }
                else
                    break;
            }
            
            while(true)
            {
                int m2;
                while(true)
                {
                    printf("Please enter COLUMN\n");
                    printf("COLUMN: ");
                    scanf("%d",&m2);
                    fflush(stdin);
                    if ((m2+1)<=0||(m2+1)>nofcells)
                    {
                        printf("Error: Row Value Out of Range\n");
                    }
                    else
                        break;
                }
                SubRowRange(m1,m2,count_temp);
                printf("\nTo Subtract another Column, Press 1 or Press any other key to exit.\n");
                if(getch()=='1')
                {
					count_temp++;
                    continue;
            	}
                else
                {
				
                    DataSaveRow_S();
                    break;
                }

            }
			break;
		case '3':
			RowDataSub=0;
			int m3;
            while(true)
            {
                printf("\nPlease enter the Column Number\n");
                printf("Column: ");
                scanf("%d",&m3);
                RowTeller=m3;
                fflush(stdin);
                if ((m3+1)<=0||(m3+1)>nofcells)
                {
                    printf("Error: Row Value Out of Range\n");
                }
                else
                    break;
            }
            while(true)
            {
                int m4;
                while(true)
                {
                    printf("Please enter ROW\n");
                    printf("ROW: ");
                    scanf("%d",&m4);
                    fflush(stdin);
                    if ((m4+1)<=0||(m4+1)>nofrows)
                    {
                        printf("Error: Row Value Out of Range\n");
                    }
                    else
                        break;
                }
                SubColRange(m4,m3,count_temp);
                printf("\nTo Subtract another Row, Press 1 or Press any other key to exit.\n");
                if(getch()=='1')
                	{
                	count_temp++;
                    continue;
                	}    
                else
                    {
					DataSaveCol_S();
					break;
					}

            }
			break;

	}
	

}
// ======================================================================================================================================
void SHEET::Multiply(void)
{

	system("cls");
    PrintSheet();
	printf("\nPlease select an option:");
	printf("\n1. Multiply a specific No. with a cell.");
	printf("\n2. Multiply Row Range.");
	printf("\n3. Multiply Column Range.");
	printf("\n0. Go back.");
	printf("\nOption: ");
	char userchoice6;
	scanf("%c",&userchoice6);
	fflush(stdin);
	int count_temp=1;
	switch(userchoice6)
	{
		case '0':
			return;
			break;
		case '1':
			MultiplySpecific();
			break;
		case '2':
			RowDataMul=0;
			int m1;
            while(true)
            {
                printf("\nPlease enter the Row Number\n");
                printf("ROW: ");
                scanf("%d",&m1);
                RowTeller=m1;
                fflush(stdin);
                if ((m1+1)<=0||(m1+1)>nofrows)
                {
                    printf("Error: Row Value Out of Range\n");
                }
                else
                    break;
            }
            
            while(true)
            {
                int m2;
                while(true)
                {
                    printf("Please enter COLUMN\n");
                    printf("COLUMN: ");
                    scanf("%d",&m2);
                    fflush(stdin);
                    if ((m2+1)<=0||(m2+1)>nofcells)
                    {
                        printf("Error: Row Value Out of Range\n");
                    }
                    else
                        break;
                }
                MulRowRange(m1,m2,count_temp);
                printf("\nTo Multiply another Column, Press 1 or Press any other key to exit.\n");
                if(getch()=='1')
                {
					count_temp++;
                    continue;
            	}
                else
                {
                    DataSaveRow_M();
                    break;
                }

            }
			getch();
			break;
		case '3':
			RowDataMul=0;
			int m3;
            while(true)
            {
                printf("\nPlease enter the Column Number\n");
                printf("Column: ");
                scanf("%d",&m3);
                RowTeller=m3;
                fflush(stdin);
                if ((m3+1)<=0||(m3+1)>nofcells)
                {
                    printf("Error: Row Value Out of Range\n");
                }
                else
                    break;
            }
            while(true)
            {
                int m4;
                while(true)
                {
                    printf("Please enter ROW\n");
                    printf("ROW: ");
                    scanf("%d",&m4);
                    fflush(stdin);
                    if ((m4+1)<=0||(m4+1)>nofrows)
                    {
                        printf("Error: Row Value Out of Range\n");
                    }
                    else
                        break;
                }
                MulColRange(m4,m3,count_temp);
                printf("\nTo Multiply another Row, Press 1 or Press any other key to exit.\n");
                if(getch()=='1')
                	{
                	count_temp++;
                    continue;
                	}    
                else
                    {
					DataSaveCol_M();
					break;
					}

            }
			break;

			
	}

}

void SHEET::Divide(void)
{
	system("cls");
    PrintSheet();
	printf("\nPlease select an option:");
	printf("\n1. Divide the cell data with a specific number.");
	printf("\n0. Go back.");
	printf("\nOption: ");
	char userchoice7;
	scanf("%c",&userchoice7);
	fflush(stdin);
	switch(userchoice7)
	{
		case '0':
			return;
			break;
		case '1':
			DivideSpecific();
			break;

	}

}

void SHEET::Average(void)
{
	system("cls");
    PrintSheet();
 	printf("\nPlease select an option:");
	printf("\n1. Take Average of Row data.");
	printf("\n2. Take Average of Column data.");
	printf("\n0. Go back.");
	printf("\nOption: ");
	char userchoice8;
	scanf("%c",&userchoice8);
	fflush(stdin);
	int count_temp=1;
	switch(userchoice8)
	{
		case '0':
			return;
			break;
		case '1':
			RowDataSum=0;
			int m1;
            while(true)
            {
                printf("\nPlease enter the Row Number\n");
                printf("ROW: ");
                scanf("%d",&m1);
                RowTeller=m1;
                fflush(stdin);
                if ((m1+1)<=0||(m1+1)>nofrows)
                {
                    printf("Error: Row Value Out of Range\n");
                }
                else
                    break;
            }
            
            while(true)
            {
                int m2;
                while(true)
                {
                    printf("Please enter COLUMN\n");
                    printf("COLUMN: ");
                    scanf("%d",&m2);
                    fflush(stdin);
                    if ((m2+1)<=0||(m2+1)>nofcells)
                    {
                        printf("Error: Row Value Out of Range\n");
                    }
                    else
                        break;
                }
                AveRowRange(m1,m2,count_temp);
                printf("\nTo take Average of another Column, Press 1 or Press any other key to exit.\n");
                if(getch()=='1')
                {
					count_temp++;
                    continue;
            	}
                else
                	{double average;
                	average=(RowDataSum/count_temp);
                	printf("\nAverage: %f",average);
                    DataSaveRow_Ave(average);
                    break;
					}
            }
			break;
		case '2':
			RowDataSum=0;
			int m3;
            while(true)
            {
                printf("\nPlease enter the Column Number\n");
                printf("Column: ");
                scanf("%d",&m3);
                RowTeller=m3;
                fflush(stdin);
                if ((m3+1)<=0||(m3+1)>nofcells)
                {
                    printf("Error: Row Value Out of Range\n");
                }
                else
                    break;
            }
            while(true)
            {
                int m4;
                while(true)
                {
                    printf("Please enter ROW\n");
                    printf("ROW: ");
                    scanf("%d",&m4);
                    fflush(stdin);
                    if ((m4+1)<=0||(m4+1)>nofrows)
                    {
                        printf("Error: Row Value Out of Range\n");
                    }
                    else
                        break;
                }
                AveColRange(m4,m3,count_temp);
                printf("\nTo take Average of another Row, Press 1 or Press any other key to exit.\n");
                if(getch()=='1')
                {
					count_temp++;
                    continue;
            	}
                else
                	{double average;
                	average=(RowDataSum/count_temp);
                	printf("\nAverage: %f",average);
                    DataSaveCol_Ave(average);
                    break;
					}
            }
			break;
						
	}

}

void SHEET::SqRoot(void)
{
	system("cls");
    PrintSheet();
	printf("\nPlease select an option:");
	printf("\n1. Take Square Root of a specific cell data.");
	printf("\n0. Go back.");
	printf("\nOption: ");
	char userchoice9;
	scanf("%c",&userchoice9);
	fflush(stdin);
	switch(userchoice9)
	{
		case '0':
			return;
			break;
		case '1':
			SquareRoot();
			break;
	}

}


bool SHEET::DestroyRow(int index)
{
    RNODE* temp=Head_Row;
    if(index==0)
    {
        Head_Row=Head_Row->NextRow;
        temp->Rows->CellDestroyer(nofcells);
        delete temp;
        return true;
    }
    else
    {
        RNODE* temp2=Head_Row->NextRow;
        int counter=0;
        while(temp2!=NULL)
        {
            if (counter==(index-1))
            {
                temp->NextRow=temp2->NextRow;
                temp2->Rows->CellDestroyer(nofcells);
                delete temp2;
            }
            counter++;
            temp=temp->NextRow;
            temp2=temp2->NextRow;
        }
    }
}
bool SHEET::DestroyColumn(int index)
{
    RNODE* temp=Head_Row;
    while(temp!=NULL)
    {
        temp->Rows->ColumnWiseDestroy(index);
        temp=temp->NextRow;
    }
    return true;
}
SHEET::~SHEET(void)
{
    if (Head_Row!=NULL)
    {
        RNODE* temp=Head_Row;
        Head_Row=NULL;
        while(temp->NextRow!=NULL)
        {
            RNODE* temp2=temp;
            temp=temp->NextRow;
            temp->Rows->CellDestroyer(nofcells);
            delete(temp2);
        }
    }
    else
        delete(Head_Row);
        exit;

}

/////////////////////////////////////////////Class SHEET Functions END\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\/

/////////////////////////////////////////////Class SHEET END\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\/

