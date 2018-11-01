#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <math.h>
#include <stack>
#include <queue>

using namespace std;

typedef vector<vector<int>> Graph;

stack<int> dfs(Graph &g, int s, int t)
{ 
  vector<bool> flag(g.size(), false);
  stack<int> st;
  flag[s] = true;
  st.push(s);
  while(!st.empty())
  {
    int current = st.top();
    if(current == t)
    {
      return st;
    }else{
      bool nv = false;
      for(int i = 0; i < g[current].size(); i++)
      {
        int next = g[current][i];
        if(!flag[next])
        {
          nv = true;
          flag[next] = true;
          st.push(next);
          break;
        }
      }
      if(!nv)
      {
        st.pop();
      }
    }
  }
  return st;
}

void draw_non_path(Graph &g, vector<int> &draw, vector<int> mem, int s, int color)
{
  vector<bool> flag(g.size(), false);
  queue<int> q;
  flag[s] = true;
  q.push(s);
  while(!q.empty())
  {
    int current = q.front();
    q.pop();
    for(int i = 0; i < g[current].size(); i++)
    {
      int next = g[current][i];
      if(mem[next] != 0) continue;
      if(flag[next]) continue;
      flag[next] = true;
      q.push(next);
      draw[next] = color;
    }
  }
}

void draw_in_path(Graph &g, vector<int> &draw, int s, int color)
{
  vector<bool> flag(g.size(), false);
  queue<int> q;
  flag[s] = true;
  q.push(s);
  while(!q.empty())
  {
    int current = q.front();
    q.pop();
    for(int i = 0; i < g[current].size(); i++){
      int next = g[current][i];
      if(flag[next]) continue;
      if(draw[next] != color && draw[next] != 0) continue;
      flag[next] = true;
      draw[next] = color;
      q.push(next);
    }
  }
}

int main()
{
  int n;
  cin >> n;
  Graph tree(n);
  for(int i = 0; i < n - 1; i++)
  {
    int a, b;
    cin >> a >> b;
    tree[a - 1].push_back(b - 1);
    tree[b - 1].push_back(a - 1);
  }
  stack<int> result = dfs(tree, 0, n - 1);
  //パス内の点を登録し色塗り
  vector<int> draw(n, 0);
  vector<int> path;
  draw[0] = 1;  //黒
  draw[n - 1] = -1; //白
  int count = 0;
  vector<int> in_path(n, 0);
  while(!result.empty())
  {
    int temp = result.top();
    result.pop();
    in_path[temp] = 1;
    path.push_back(temp);
    count++;
  }
  reverse(path.begin(), path.end());
  for(int i = 0; i < path.size(); i++)
  {
    if(i < ceil(path.size() * 0.5))
    {
      draw[path[i]] = 1;
    }else{
      draw[path[i]] = -1;
    }
  } 
  //パス外の点を塗る
  draw_non_path(tree, draw, in_path, 0, 1);
  draw_non_path(tree, draw, in_path, n - 1, -1);
  //パス内の点を塗る
  draw_in_path(tree, draw, 0, 1);
  draw_in_path(tree, draw, n - 1, -1);
  /*for(auto e : draw)
  {
    cout << e << endl;
  }*/
  //判定
  int count_b = 0;
  int count_w = 0;
  for(int i = 0; i < n; i++)
  {
    if(draw[i] == 1)
    {
      count_b++;
    }else{
      count_w++;
    }
  }
  if(count_b > count_w)
  {
    cout << "Fennec" << endl;
  }else{
    cout << "Snuke" << endl;
  }
	return 0;
}
