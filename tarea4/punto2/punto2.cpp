#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <iomanip>
#include <ctime>
using namespace std;

const double gr = 1.0 / 5.0;
const double gp = 1.0 / 30.0;
const double kr = 1.0;
const double kp = gp * 10000.0 / 5.0;

float genRand()
{
  return ((double)rand() / (RAND_MAX));
}

float tau(double rand, float sumEvents)
{
  return log(1 / rand) / sumEvents;
}

float pcr(float r, float p)
{
  return kr;
}
float pdr(float r, float p)
{
  return gr * r;
}
float pcp(float r, float p)
{
  return kp * r;
}
float pdp(float r, float p)
{
  return gp * p;
}

float sumOfVector(vector<double> daVector)
{
  float ans = 0;
  for (int i = 0; i < daVector.size(); i++)
  {
    ans += daVector[i];
  }
  return ans;
}

vector<double> events(float r, float p)
{
  vector<double> ans;

  ans.push_back(pcr(r, p));
  ans.push_back(pdr(r, p));
  ans.push_back(pcp(r, p));
  ans.push_back(pdp(r, p));

  return ans;
}

vector<double> normalizedEvents(float r, float p)
{
  vector<double> ans;

  ans.push_back(pcr(r, p));
  ans.push_back(pdr(r, p));
  ans.push_back(pcp(r, p));
  ans.push_back(pdp(r, p));

  float sumVector = sumOfVector(ans);

  for (int i = 0; i < ans.size(); i++)
  {
    ans[i] /= sumVector;
  }

  return ans;
}

void doAction(int index, vector<double> &r, vector<double> &p)
{

  switch (index)
  {
  case 0:
  {

    r.push_back(r.back() + 1);
    p.push_back(p.back());
    break;
  }
  case 1:
  {
    r.push_back(r.back() - 1);
    p.push_back(p.back());
    break;
  }
  case 2:
  {
    r.push_back(r.back());
    p.push_back(p.back() + 1);
    break;
  }
  case 3:
  {
    r.push_back(r.back());
    p.push_back(p.back() - 1);
    break;
  }
  default:
    cout << "switch defaulted";
    break;
  }
}

void writeToFile(vector<double> vec, string filename)
{
  ofstream myfile;
  // if (filename == "t")
  // {
  //   cout << "T!!!" << endl;
  // }
  myfile.open(filename + ".dat", ios_base::app);

  for (int i = 0; i < vec.size(); i++)
  {
    if (i != vec.size() - 1)
    {
      myfile << vec[i] << " ";
    }
    else
    {
      myfile << vec[i];
    }
  }
  myfile << endl;

  // myfile << "Writing this to a file.\n";
  myfile.close();
}

void printVector(vector<double> vec)
{
  for (auto i = vec.begin(); i != vec.end(); ++i)
    cout << *i << ' ';
}

void simSingleCell(double cellsStatus)
{
  vector<double> t;
  vector<double> p;
  vector<double> r;

  t.push_back(0.0);
  p.push_back(0.0);
  r.push_back(0.0);

  while (t.back() < 10.0 / gp)
  {

    // cout << "\r"
    //      << "Cells status: " << cellsStatus << " Current cell status:" << t.back() * 100 * gp / 10.0;
    t.push_back(t.back() + tau(genRand(), sumOfVector(events(r.back(), p.back()))));

    // normalized vector
    vector<double> normedEvents = normalizedEvents(r.back(), p.back());

    //cumulative version to figure out which event took place
    for (int i = 1; i < normedEvents.size(); i++)
    {
      normedEvents[i] = normedEvents[i - 1] + normedEvents[i];
    }

    // cout << endl;
    // cout << "normedVect" << endl;
    // printVector(normedEvents);

    // random num to determine what happens
    float randNum = genRand();

    // lets determine what happens

    int decideIndex;
    for (int i = 0; i < normedEvents.size(); i++)
    {
      if (randNum < normedEvents[i])
      {
        decideIndex = i;
        break;
      }
    }

    doAction(decideIndex, r, p);
  }

  writeToFile(t, "t");
  writeToFile(r, "r");
  writeToFile(p, "p");

  // cout << endl;
}

main(int argc, char const *argv[])
{
  cout<<"Starting program..."<<endl;
  time_t start = time(NULL);

	
  const int totCells = 1000;
  int currentCell = 1;
  cout<<"Entering cycle..."<<endl;
  for (int i = 0; i < totCells; i++)
  {
    cout << "Cells status: " << currentCell * 100.0 / totCells<<endl;
    simSingleCell(currentCell * 100.0 / totCells);
    currentCell++;
  }
  cout<<endl;

  time_t end = time(NULL);

  cout<< "Time taken to run simulations: "<<endl;
  cout<< end-start<< " seconds"<<endl;

  return 0;
}
