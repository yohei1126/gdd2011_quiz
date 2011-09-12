#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

struct data_set {
  vector<unsigned int> data;
  int count;
  void show(const string &str);
};

void data_set::show(const string& str) {
  cout << str << ":";
  for (int i = 0; i < data.size(); i++) {
    cout << data[i] << " ";
  }
  cout << endl << "count=" << count << endl;
}

int solve(data_set& d) {
  queue<data_set> q;
  int min_count = 0;
  q.push(d);

  while(q.size()){
    data_set ds = q.front();
    q.pop();

    //ds.show("process data:");
    if ((min_count != 0) && (min_count < ds.count)) {
      continue;
    }

    if (ds.data.size() == 0) {
      if ((min_count == 0) ||
	  (min_count > ds.count)) {
	  min_count = ds.count;
      }
      continue;
      //cout << "min count = " << min_count << endl;
    }

    data_set ds1 = ds;
    //cout << "ds1:";
    for(int i = 0; i< ds1.data.size(); i++) {
      ds1.data[i] = ds1.data[i]/2;
    }
    ds1.count ++;
    //ds1.show("ds1:");
    q.push(ds1);

    data_set ds2 = ds;
    for (int i = 0; i < ds.data.size(); i++) {
      if (ds2.data[i] % 5 == 0) {
	ds2.data[i] = 0;
      }
    }
    vector<unsigned int>::iterator it = remove(ds2.data.begin(), ds2.data.end(), 0);
    ds2.data.erase(it, ds2.data.end());
    ds2.count++;
    //ds2.show("ds2:");
    q.push(ds2);
  }

  return min_count;
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    return 1;
  }
  ifstream ifs(argv[1]);
  if(!ifs) {
    return 1;
  }

  string buf;
  getline(ifs,buf);
  int T;
  sscanf(buf.c_str(),"%d", &T);
  //cout << "T =" << T << endl;

  for(int i = 0; i < T; i++) {
    getline(ifs,buf);
    int N;
    sscanf(buf.c_str(),"%d", &N);
    //cout << "N=" << N << endl;
    getline(ifs,buf);

    data_set ds;
    for (int j = 0; j < N; j++) {
      unsigned int d;
      sscanf(buf.c_str(),"%d", &d);
      int end = buf.find_first_of(" ", end + 1);
      buf = buf.erase(0, end);
      ds.data.push_back(d);
    }
    //ds.show("data_set:");
    ds.count = 0;
    cout << solve(ds) << endl;
  }

  return 0;
}
