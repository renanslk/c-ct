#include <iostream>
#include <time.h>

using namespace std;

int **storage;
int *object;

enum ObjDetails {
    ID,
    CATEGORY,
    SIZE,
    PRICE,
    N_FIELDS
};

enum DtOptions {
    YEAR,
    MONTH,
    DAY,
    HOUR,
    MIN,
    SEC
};

int getTime(int mode){
    time_t t = time(NULL);
    struct tm now = *localtime(&t);

    int res = 0;
    switch(mode){
    case YEAR:
        res = now.tm_year + 1900;
        break;
    case MONTH:
        res = now.tm_mon + 1;
        break;
    case DAY:
        res = now.tm_mday;
        break;
    case HOUR:
        res = now.tm_hour;
        break;
    case MIN:
        res = now.tm_min;
        break;
    case SEC:
        res = now.tm_sec;
        break;
    default:
        res = 0;
    }
    return res;
}

int main()
{
    cout << "========================================" << "\n"
    << "   STORAGE DATABASE" << "\n"
    << "========================================" << endl;
    cout << "   System time: " << getTime(YEAR) << "-" << getTime(MONTH) <<
    "-" << getTime(DAY) << " " << getTime(HOUR) << ":" << getTime(MIN) << ":" <<
    getTime(SEC) << "\n----------------------------------------" << endl;

    int objCount;
    int cols = N_FIELDS;

    cout << " Please insert quantity of objects to add:" << endl;
    cin >> objCount;

    /* Allocate object holder */
    object = (int*)malloc(cols * sizeof(int));

    /* Allocate storage matrix */
    storage = (int**)malloc(objCount * sizeof(int*));
    for (int i = 0; i < objCount; i++){
        storage[i] = (int*)malloc(cols * sizeof(int));
    }

    /* Adding data to object array */
    for (int i = 0; i < objCount; i++){
        object[ID] = i;
        cout << " Registering object - ID [" << i << "]:" << endl;
        cout << "   > Insert object category number: ";
        cin >> object[CATEGORY];
        cout << "   > Insert object size: ";
        cin >> object[SIZE];
        cout << "   > Insert object price value: ";
        cin >> object[PRICE];
        cout << "   Object " << "[" << i << "]" << " added successfully." << endl << endl;

        /* Realloc for datetime field */
        cols = 6; // adding more 2 columns
        storage[i] = (int*)realloc(storage[i], cols * sizeof(int));

        storage[i][ID] = object[ID];
        storage[i][CATEGORY] = object[CATEGORY];
        storage[i][SIZE] = object[SIZE];
        storage[i][PRICE] = object[PRICE];
        storage[i][4] = getTime(YEAR);
        storage[i][5] = getTime(MONTH);
    }

    /* Show database */
    cout << endl;
    cout << "ID\tCAT\tSIZE\tPRICE\tYEAR\tMON\n" <<
    "--------------------------------------------" << endl;
    for (int i = 0; i < objCount; i++){
        for (int j = 0; j < cols; j++){
            cout << storage[i][j] << "\t";
        }
        cout << endl;
    }

    /* Release memory */
    free(object);
    for (int i = 0; i < objCount; i++)
        free(storage[i]);
    free(storage);

    return 0;
}
