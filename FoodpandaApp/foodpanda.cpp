#include<iostream>
#include<fstream>
#include "foodpanda.h"

using namespace std;

/////////////////// Start of Main ///////////////////////////
int main(){
  Foodpanda app;
  struct winsize window;

  app.getdata();
  app.getdetail();

  cout << "\x1B[32m";   // change text color to green

  bool exit = false;
  while (not exit)
  {
    // display welcome window
    app.welcome(window);

    int input = cin.get();

    if (input == 27)
      exit = true;

    else if (input == 10)
      app.displayboard(window);

    else
      cout << '\a';
  }

  cout << "\x1B[0m";    // set default text color

  // clears the console
  system("clear");
  return 0;
}
/////////////////// End of Main ///////////////////////////

/* This method receives data from file
   and sets data to pointed array(s)
   note: file 'data.csv' is required */
bool Foodpanda :: getdata()
{
  string file = "data.csv", line;
  // initializing datasize
  datasize = 0;

  // open file and count number of lines
  ifstream fin(file.c_str());
  if (fin.is_open())
  {
    while(not fin.eof())
    {
      getline(fin, line);
      datasize++;   // this counts number of lines
    }
    // close the file
    fin.close();
  }

  else
  {
    cout << "File '" << file << "' not found!\n";
    return false;
  }

  /*
  Re-open the file to get data and
  create a dynamic array(s) with respect
  to name, contact, address, city.
  */
  fin.open(file.c_str());

  // dynamic memory allocation
  hotel_name = new string[datasize];
  hotel_contact = new string[datasize];
  hotel_location = new string[datasize];
  hotel_city = new string[datasize];

  for(int i = 0; i < datasize; i++)
  {
    getline(fin, hotel_name[i], ',');
    getline(fin, hotel_contact[i], ',');
    getline(fin, hotel_location[i], ',');
    getline(fin, hotel_city[i], '\n');
  }

  fin.close();
  return true;
}

bool Foodpanda :: getdetail()
{
  ifstream file("fooditems.csv");
  detailsize = 0;
  // string temp;
  // while(not file.eof())
  // {
  //   getline(file, temp);
  //   detailsize++;
  // }
  // file.close();
  //
  // file.open("fooditems.csv");
  // int list = 0;
  // string name;
  // char comma;
  // hotel_items = new string*[detailsize];
  // item_price = new int*[detailsize];
  // for(int i = 0; i < detailsize; i++)
  // {
  //   getline(file, name, ',');
  //   file >> list;
  //   getchar();
  //   // file.ignore(',', 0);
  //   hotel_items[i] = new string[list + 1];
  //   item_price[i] = new int[list + 1];
  //   hotel_items[i][0] = name;
  //   item_price[i][0] = list;
  //
  //   for (int j = 1; j < list; j++) {
  //     getline(file, hotel_items[i][j], ',');
  //     file >> item_price[i][j];
  //     file.ignore(',');
  //     cout << item_price[i][j] << ' ';
  //   }
  //   cout << endl;
  // }
  // return true;
}

// this method CAPITALIZES a given string
string Foodpanda :: upper(string str)
{
	string upperStr;

	for (int i = 0; i < str.length(); i++)
  {
    // if alphabet is lower case than convert to upper
    if (str[i] >= char(97) && str[i] <= char(122))
      upperStr += char(str[i] - 32);

    // else no change
    else
      upperStr += str[i];
  }

	return upperStr;
}

/* This method outputs welcome screen
   as designed in 'display.txt' file */
void Foodpanda :: welcome(winsize window)
{
  // checks the current console window size
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);

  system("clear");
  string design;
  ifstream file("display.txt");

  while(not file.eof())
  {
    getline(file, design);
    cout << design << endl;
    window.ws_row--;
  }
  file.close();

  for (int col = 0; col < ((window.ws_row - 1) * window.ws_col); col++)
    cout << ' ';

  return;
}


void fillspace(int width)
{
  for (int i = 0; i < width; i++)
    cout << ' ';

  return;
}

void Foodpanda :: displayboard(winsize window)
{
  system("clear");
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);
  fillspace((window.ws_col * 4) + window.ws_col / 6);

  cout << "[Find or see your nearest hotels/restaurants";
  cout << " address/contact]\n\n";
  fillspace(window.ws_col / 6);
  cout << "[1] Find local restaurants/hotels\n";
  fillspace(window.ws_col / 6);
  cout << "[2] Show famous hotels/restaurants\n";
  fillspace(window.ws_col / 6);
  cout << "[3] Show all available\n\n";
  fillspace(window.ws_col / 6);
  cout << "[Esc to exit]\n";
  fillspace(window.ws_col / 6);
  cout << "Enter choice[1 - 3]: ";
  int choice = cin.get();
  if (choice == 49)
    search(window.ws_col);

  else if (choice == 50)
    display(window.ws_col, false);

  else if (choice == 51)
    display(window.ws_col, true);

  return;
}
void Foodpanda :: display(int window, bool all)
{
  system("clear");
  fillspace((window * 4) + window / 6);
  cout << "[:] Name(s) of hotels/restaurants\n\n";

  if (all)
  {
    fillspace(window / 12);
    for (int i = 0; i < datasize - 1; i++)
    {
      cout << '[' << i + 1 << ']' << ' ';
      cout << setw(20) << left << upper(hotel_name[i]);

      if ((i + 1) % 3 == 0 and i > 0)
      {
        cout << endl;
        fillspace(window / 12);
      }
    }
  }

  else if (not all)
  {
    fillspace(window / 6);
    for (int i = 0; i < 5; i++)
    {
      cout << '[' << i + 1 << ']' << ' ';
      cout << upper(hotel_name[i]) << endl;
      fillspace(window / 6);
    }
  }

  cout << endl;
  int index;
  fillspace(window / 6);
  cout << "[:] For detail: ";
  cin >> index;

  cout << endl;
  fillspace(window / 6);

  if (index > 0 and index <= datasize)
    if (all or index <= 5)
    {
      system("clear");
      displayinfo(index - 1, window);
    }

  else
    cout << "[Invalid entry!]" << endl;

  cout << endl;
  fillspace(window / 6);
  cout << "[Enter to retry] \t [Esc to exit]\n";
  cout << endl;

  index = cin.get();
  if (index == 27)
    return;

  cin.get();
  return display(window, all);
}


void Foodpanda :: search(int window)
{
  system("clear");
  fillspace((window * 4) + window / 6);

  cout << "[Go ahead and tell us what you know]\n\n";
  fillspace(window / 6);
  cout << "[1] Search by name\n";
  fillspace(window / 6);
  cout << "[2] Search by contact\n";
  fillspace(window / 6);
  cout << "[Esc to exit]\n";
  fillspace(window / 6);
  cout << "Enter choice[1 - 2]: ";
  string input;
  int index[datasize] = {0};

  cin >> input;
  cin.ignore();
  cout << endl;
  fillspace(window / 6);
  if (input == "1")
  {
    cout << "Enter name: ";
    getline(cin, input);
    locate(input, index, "hotel_name");
  }
  else if (input == "2")
  {
    cout << "Enter number: ";
    getline(cin, input);
    cout << input;
    locate(input, index, "hotel_contact");
  }

  // system("clear");
  for (int i = 0; i < datasize; i++)
  {
    if (index[i] == 1)
      displayinfo(i, window);
  }

  cin.get();
  return;
}

int Foodpanda :: locate(string desired, int index[], string on)
{
    if (on == "hotel_name")
      for (int i = 0; i < datasize; i++)
        if (upper(hotel_name[i]) == upper(desired))
          index[i] = 1;

    else if (on == "hotel_contact")
      for (int i = 0; i < datasize; i++)
        if (upper(hotel_contact[i]) == upper(desired))
          index[i] = 1;

  return *index;
}

void Foodpanda :: displayinfo(int index, int window)
{
  fillspace((window * 4) + window / 6);

  cout << "[Detail Info]\n\n";
  fillspace(window / 6);
  cout << "Name    :   " << upper(hotel_name[index]) << endl;
  fillspace(window / 6);
  cout << "Contact :  " << upper(hotel_contact[index]) << endl;
  fillspace(window / 6);
  cout << "Address :  " << upper(hotel_location[index]) << endl;
  fillspace(window / 6);
  cout << "City    :   " << upper(hotel_city[index]) << endl;
  cout << endl;
  fillspace(window / 6);
  cout << "[Press any key to exit]" << endl;

  cin.get();
  return;
}
