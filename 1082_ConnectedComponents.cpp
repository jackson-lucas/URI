/*
3
3 1
a c
10 10
a b
a c
a g
b c
c g
e d
d f
h i
i j
j h
6 4
a b
b c
c a
e f

Case #1:
a,c,
b,
2 connected components

Case #2:
a,b,c,g,
d,e,f,
h,i,j,
3 connected components

Case #3:
a,b,c,
d,
e,f,
3 connected components
*/

#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <vector>
#include <array>
#include <queue>
#include <assert.h>

using namespace std;

const int NOT_VISITED = 0;
const int VISITED = 1;
const int FINISHED = 2;

typedef struct vertex {
  char key;
  int status;
  int group;
  vector<int> neighborhood;
} Vertex;

typedef struct graph  {
  vector<Vertex> vertices;
} Graph;

char indexToKey(int index) {
  char key;

  // Ladies and Gentlemen I present to you: Ternaryssaur
  // Made for fun but it actually it seems pretty legible.
  key = index == 0 ? 'a' :
    index == 1 ? 'b' :
    index == 2 ? 'c' :
    index == 3 ? 'd' :
    index == 4 ? 'e' :
    index == 5 ? 'f' :
    index == 6 ? 'g' :
    index == 7 ? 'h' :
    index == 8 ? 'i' :
    index == 9 ? 'j' :
    index == 10 ? 'k' :
    index == 11 ? 'l' :
    index == 12 ? 'm' :
    index == 13 ? 'n' :
    index == 14 ? 'o' :
    index == 15 ? 'p' :
    index == 16 ? 'q' :
    index == 17 ? 'r' :
    index == 18 ? 's' :
    index == 19 ? 't' :
    index == 20 ? 'u' :
    index == 21 ? 'v' :
    index == 22 ? 'w' :
    index == 23 ? 'x' :
    index == 24 ? 'y' : 'z';

  return key;
}

int keyToIndex(char key) {
  int index = 0;

  switch (key) {
    case 'z':
      index++;
    case 'y':
      index++;
    case 'x':
      index++;
    case 'w':
      index++;
    case 'v':
      index++;
    case 'u':
      index++;
    case 't':
      index++;
    case 's':
      index++;
    case 'r':
      index++;
    case 'q':
      index++;
    case 'p':
      index++;
    case 'o':
      index++;
    case 'n':
      index++;
    case 'm':
      index++;
    case 'l':
      index++;
    case 'k':
      index++;
    case 'j':
      index++;
    case 'i':
      index++;
    case 'h':
      index++;
    case 'g':
      index++;
    case 'f':
      index++;
    case 'e':
      index++;
    case 'd':
      index++;
    case 'c':
      index++;
    case 'b':
      index++;
    case 'a':
      break;
  }

  return index;
}


Graph connectNodes(char key1, char key2, Graph graph) {
  int vertex1 = keyToIndex(key1);
  int vertex2 = keyToIndex(key2);

  graph.vertices[vertex1].neighborhood.push_back(vertex2);
  graph.vertices[vertex2].neighborhood.push_back(vertex1);

  return graph;
}


Graph depthFirstBreadth(char key, Graph graph, int group) {
  int vertexIndex = keyToIndex(key);

  graph.vertices[vertexIndex].status = VISITED;
  graph.vertices[vertexIndex].group = group;

  //cout << vertexIndex << " " << group << " " << graph.vertices[vertexIndex].neighborhood.size() << endl;
  for(int index=0; index<graph.vertices[vertexIndex].neighborhood.size();
   index++) {
    int adjacentVertexIndex = graph.vertices[vertexIndex].neighborhood[index];
    Vertex adjacentVertex = graph.vertices[adjacentVertexIndex];

    if(adjacentVertex.status == NOT_VISITED) {
      graph = depthFirstBreadth(adjacentVertex.key, graph, group);
    }
  }


  graph.vertices[vertexIndex].status = FINISHED;
  return graph;
}

Graph createGraph(int size) {
  Graph graph;
  Vertex temp;
  for(int index = 0; index < size; index++) {
    temp.key = indexToKey(index);
    temp.group = 0;
    temp.status = NOT_VISITED;
    graph.vertices.push_back(temp);
  }

  return graph;
}

void printGraph(Graph graph) {
  for(int index = 0; index < graph.vertices.size(); index++) {
    cout << endl;
    cout << "Vertex " << index << endl;
    cout << "Key: " << graph.vertices[index].key << endl;
    cout << "Group: " << graph.vertices[index].group << endl;
  }
  cout << endl;
}

vector<char> getGroup(int index, Graph graph) {
  vector<char> group;

  for(int vertexIndex = 0; vertexIndex < graph.vertices.size(); vertexIndex++) {
    if (graph.vertices[vertexIndex].group == index) {
      group.push_back(graph.vertices[vertexIndex].key);
    }
  }

  return group;
}

void printComponents(Graph graph, int groupSize) {
  int groupIndex = 1;
  vector<char> group;

  //printGraph(graph);

  for(int groupIndex = 1; groupIndex < groupSize; groupIndex++) {
    group = getGroup(groupIndex, graph);
    for(int index = 0; index < group.size(); index++) {
      cout << group[index] << ",";
    }

    cout << endl;
  }

  cout << (groupSize - 1) << " connected components" << endl;
}

void searchConnectedComponents (Graph graph) {
  int groupSize = 1;

  for(int index = 0; index < graph.vertices.size(); index++) {
    if(graph.vertices[index].status == NOT_VISITED) {
      graph = depthFirstBreadth(indexToKey(index), graph, groupSize);
      groupSize++;
    }
  }

  printComponents(graph, groupSize);
}

// TEST AREA

void testMethodKeyToIndex() {
  assert(keyToIndex('a')==0);
  assert(keyToIndex('z')==25);
}

void testMethodIndexToKey() {
  assert(indexToKey(0)=='a');
  assert(indexToKey(25)=='z');
}

void testMethodConnectNodes() {
  Graph graph;
  Vertex temp;
  temp.key = 'a';
  graph.vertices.push_back(temp);

  temp.key = 'b';
  graph.vertices.push_back(temp);

  graph = connectNodes('a', 'b', graph);

  assert(graph.vertices[keyToIndex('a')].neighborhood.size() == 1);
  assert(graph.vertices[keyToIndex('b')].neighborhood.size() == 1);
}

void testGraphInsertion() {
  Graph graph;
  Vertex temp;
  temp.key = 'a';
  graph.vertices.push_back(temp);

  temp.key = 'b';
  graph.vertices.push_back(temp);

  assert(graph.vertices[keyToIndex('a')].key == 'a');
  assert(graph.vertices[keyToIndex('b')].key == 'b');
}

void testMethodCreateGraph() {
  Graph graph = createGraph(5);
  assert(graph.vertices[0].key == 'a');
  assert(graph.vertices[4].key == 'e');
}

void testGeneralCase() {
  Graph graph;

  graph = createGraph(10);
  graph = connectNodes('a', 'b', graph);
  graph = connectNodes('a', 'c', graph);
  graph = connectNodes('a', 'g', graph);
  graph = connectNodes('b', 'c', graph);
  graph = connectNodes('c', 'g', graph);
  graph = connectNodes('e', 'd', graph);
  graph = connectNodes('d', 'f', graph);
  graph = connectNodes('h', 'i', graph);
  graph = connectNodes('j', 'h', graph);

  searchConnectedComponents(graph);
}

void test() {
  testMethodKeyToIndex();
  testMethodIndexToKey();
  testMethodConnectNodes();
  testGraphInsertion();
  testMethodCreateGraph();
  testGeneralCase();
}

// END OF THE TEST AREA

// From C++ Documentation
int stringToInt (string input) {
  int number = 0;

  stringstream myStream(input);

  if (myStream >> number) {
    return number;
  } else {
    return -1;
  }
};

int main () {
  Graph graph;
  int testsQuantity, graphSize, connectionsQuantity;
  string input = "";
  char key1, key2;

  cin >> input;

  testsQuantity = stringToInt(input);

  for(int index = 0; index < testsQuantity; index++) {
    Graph graph;

    cin >> input;
    graphSize = stringToInt(input);

    cin >> input;
    connectionsQuantity = stringToInt(input);

    graph = createGraph(graphSize);

    for(int index2 = 0; index2 < connectionsQuantity; index2++) {
      cin >> input;
      key1 = input.at(0);

      cin >> input;
      key2 = input.at(0);

      graph = connectNodes(key1, key2, graph);
    }

    cout << "Case #" << (index + 1) << ":" << endl;
    searchConnectedComponents(graph);
    cout << endl;

  }

  return 0;
}
