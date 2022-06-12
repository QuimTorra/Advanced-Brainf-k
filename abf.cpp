#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

const string SYMBOLS = "<>+-.,[]:;";

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    cerr << "Usage:\n$ abf [file].abf/.bf [-opt]" << endl;
    return 0;
  }
  int memSize = 1000;
  if (argc >= 4)
  {
    if (argv[2] == string("-mem"))
    {
      memSize = strtol(argv[3], nullptr, 0);
    }
  }

  string fileName = argv[1];
  if (fileName.find(".abf") == string::npos && fileName.find(".bf") == string::npos)
  {
    cerr << "Input file not valid!" << endl;
    return 0;
  }

  ifstream file(argv[1]);

  if (file.is_open())
  {
    // Interpret the file, line by line and char by char
    string line;
    vector<pair<int, int>> loops;
    vector<uint8_t> arr = vector<uint8_t>(memSize);
    int pointer = 0;
    bool loopSkip = false;

    cout << arr.size() << endl;
    for (int lnum = 0; getline(file, line); lnum++)
    {
      for (int i = 0; i < line.size(); i++)
      {
        int p = SYMBOLS.find(line[i]);
        if (loopSkip && p != 7)
          continue;
        switch (p)
        {
        case 0:
          if (pointer == 0)
          {
            cout << "\033[1;31mError\033[0m\nOn line: " << lnum << " pos: " << i << ".\n\033[1;31mPointer can't be negative\033[0m" << endl;
            cerr << "---------------" << endl;
            cerr << "\033[34mEnding program\033[0m" << endl;
            return 0;
          }
          pointer--;
          break;
        case 1:
          if (pointer == arr.size() - 1)
          {
            cout << "\033[1;31mError\033[0m\nOn line: " << lnum << " pos: " << i << ".\n\033[1;31mExceeded memory size\033[0m" << endl;
            cerr << "---------------" << endl;
            cerr << "\033[34mEnding program\033[0m" << endl;
            return 0;
          }
          pointer++;
          break;
        case 2:
          arr[pointer]++;
          break;
        case 3:
          arr[pointer]--;
          break;
        case 4:
          cout << arr[pointer];
          break;
        case 5:
          cin >> arr[pointer];
        case 6:
          if (unsigned(arr[pointer]) == 0)
          {
            loopSkip = true;
          }
          else
          {
            loopSkip = false;
            loops.push_back(make_pair(lnum, i));
          }
          break;
        case 7:
          if (!loopSkip)
          {
            pair<int, int> r = loops.back();
            lnum = r.first;
            i = r.second - 1;
            file.seekg(ios::beg);
            for (int i = 0; i < lnum; ++i)
            {
              file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            file >> line;
            loops.pop_back();
          }
          loopSkip = false;
          break;
        case 8:
          cout << unsigned(arr[pointer]);
          break;
        case 9:
        {
          int a;
          cin >> a;
          arr[pointer] = a;
        }
        }
      }
    }
  }
  else
  {
    cerr << "Error opening file " << argv[1] << "!" << endl;
    return 0;
  }
}