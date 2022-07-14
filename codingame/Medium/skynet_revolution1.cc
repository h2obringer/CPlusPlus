/*Author: Randal Obringer
*
* Date Last Modified: 30 October 2016
*
* Difficulty: Medium
*
* NOTE: This program is not meant to be run anywhere else but the codingame IDE at www.codingame.com
*	as the input is given through the IDE.
*
* Description: Stop an agent from reaching the gateways in a graph/network using djikstras single source shortest path algorithm.
* 	Run the algorithm for each gateway that is present in the graph and sever links to the closest gateway. Choose to sever the link
*	along the optimal path to the closest gateway between the agent and the next hop in its path to produce the optimal solution.
*
* Problem Statement: Your virus has caused a backdoor to open on the Skynet 
*	network enabling you to send new instructions in real time. You decide 
*	to take action by stopping Skynet from communicating on its own 
*	internal network. Skynet's network is divided into several smaller 
*	networks, in each sub-network is a Skynet agent tasked with transferring 
*	information by moving from node to node along links and accessing gateways
*	leading to other sub-networks. Your mission is to reprogram the virus 
*	so it will sever links in such a way that the Skynet Agent is unable to 
*	access another sub-network thus preventing information concerning the 
*	presence of our virus to reach Skynet's central hub.
*
* Rules: 
*	For each test you are given:
*		A map of the network.
*		The position of the exit gateways.
*		The starting position of the Skynet agent.
*	>>> Nodes can only be connected to up to a single gateway. <<<
*
*	Each game turn:
*	First off, you sever one of the given links in the network.
*	Then the Skynet agent moves from one Node to another accessible Node.
*
* Victory Conditions: The Skynet agent cannot reach an exit gateway.
*
* Lost Conditions: They Skynet agent has reached a gateway.
*
* Game Input:
*	The program must first read the initialization data from standard 
*	input. Then, within an infinite loop, read the data from the standard 
*	input related to the current state of the Skynet agent and provide to 
*	the standard output the next instruction.
*
*	Initialization input:
*		Line 1: 3 integers N L E
*			- N, the total number of nodes in the level, including the gateways.
*			- L, the number of links in the level.
*			- E, the number of exit gateways in the level.
*		Next L lines: 2 integers per line (N1, N2), indicating a link between 
*			the nodes indexed N1 and N2 in the network.
*		Next E lines: 1 integer EI representing the index of a gateway node.
*
*	Input for one game turn:
*		Line 1: 1 integer SI, which is the index of the node on which the 
*			Skynet agent is positioned this turn.
*
* Output for one game turn:
*	A single line comprised of two integers C1 and C2 separated by a space. C1 and C2 are the indices of the nodes you wish to sever the link 
*
* Constraints:
*	2 ≤ N ≤ 500
*	1 ≤ L ≤ 1000
*	1 ≤ E ≤ 20
*	0 ≤ N1, N2 < N
*	0 ≤ SI < N
*	0 ≤ C1, C2 < N
*	Response time per turn ≤ 150ms
*
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <climits>
#include <cstdlib>
#include <set>
#include <vector>
#include <sstream>
#include <queue>
//credit goes to DevSolar on StackOverflow for this code. Another solution could have been used but I like the simplified usage.
#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

using namespace std;

//Description: hold the list of vertices that are adjacent to a vertex. Provide functions to add, 
//remove, and test existing adjacencies. The current vertex is referenced by the index value of the vector/array
//in the Graph object
class AdjListVertex {
    public:
    	AdjListVertex();
    	bool containsEdge(int destination); //test if an edge exists between this vertex and the destination vertex
    	list<int> getAdjacencyList(); //return the list of adjacencies
    	void addAdjacency(int destination); //add adjacency between this vertex and the destination vertex
    	void removeAdjacency(int destination); //remove adjacency between this vertex and the destination vertex
    private:
    	list<int> adjacency_list;
};

AdjListVertex::AdjListVertex() {
}

list<int> AdjListVertex::getAdjacencyList() {
	return adjacency_list;
}

bool AdjListVertex::containsEdge(int destination) {
	for (list<int>::iterator it = adjacency_list.begin(); it != adjacency_list.end(); ++it) {
		if (*it == destination) {
			return true;
		} else {
			return false;
		}
	}
}

void AdjListVertex::addAdjacency(int destination) {
	if (containsEdge(destination) == false) {
		adjacency_list.push_back(destination);
	}
}

void AdjListVertex::removeAdjacency(int destination) {
	adjacency_list.remove(destination);
}

//Description: Adjacency List Graph representation. Holds a set known amount of nodes labeled from 0 to N-1.
//Allows you to build the graph representation and provides a way to determine shortest paths from a source to destination.
class Graph {
	public:
		Graph(int N);
		void addEdge(int source, int destination); //adds an edge to the graph between the two specified vertices
		void removeEdge(int source, int destination); //removes an edge in the graph between the two specified vertices
		string djikstrasSSSP(int source, int destination); //returns the distance and previous vertex to the destination vertex from the source
		string BFS(int source,int destination); //returns the distance and previous vertex to all vertices in the graph in a breadth first manner. NOT USED.
		void printGraph(); //for debugging purposes
		AdjListVertex getVertex(int index);
	private:
		int getSmallestVertex(vector<int>& dist, set<int>& visited); //helper function, return smallext vertex from vertex/distance log not already visited
		vector<AdjListVertex> vertices; //can use this implementation because we know how many nodes the graph will have and they will all be in order. This will be an array.
		int num_nodes; //will hold N from problem statement
};

Graph::Graph(int N) {
	num_nodes = N;
	AdjListVertex temp;
	for(int i=0;i<N;i++){
	    vertices.push_back(temp);
	}
}

void Graph::printGraph(){
    for(int i=0;i<num_nodes;i++){
        cerr << "Vertex " << i <<": ";
        list<int> temp = vertices[i].getAdjacencyList();
        for(list<int>::iterator it = temp.begin(); it!=temp.end();++it){
            cerr << *it << ", ";
        }
        cerr << endl;
    }
}


AdjListVertex Graph::getVertex(int index){
    return vertices[index];
}

void Graph::addEdge(int source, int destination) {
	//our nodes are static so if source or desination are out of range then return
	if (source<0 || source>num_nodes - 1 || destination<0 || destination>num_nodes - 1) {
	    cerr << "Failed to add the edge! Source or destination is out of range" << endl;
		return;
	}
	
	//add links going both ways (undirected graph)
	vertices[source].addAdjacency(destination); //unweighted graph so use 1 weight for all
	vertices[destination].addAdjacency(source);
}

void Graph::removeEdge(int source, int destination) {
	//our nodes are static so if source or desination are out of range then return
	if (source<0 || source>num_nodes - 1 || destination<0 || destination>num_nodes - 1) {
	    cerr << "Failed to remove the edge! Source or destination is out of range" << endl;
		return;
	}
	//remove links going both ways to sever the link completely (undirected graph)
	vertices[source].removeAdjacency(destination);
	vertices[destination].removeAdjacency(source);
}

//return smallest value from vector that already wasn't visited
//returns INT_MAX when there is no path from node to destination so each for this value in djikstras and handle it.
int Graph::getSmallestVertex(vector<int>& dist, set<int>& visited) {
	int smallest = INT_MAX;
	int answer = INT_MAX;

	for (int i = 0; i<num_nodes; i++) {
		if ((visited.count(i) == 0) && (dist[i]) <= smallest) {
			smallest = dist[i];
			answer = i;
		}
	}

	return answer;
}

/*
Function: djikstrasSSSP (the optimal solution)
Description: Computes the distance (smallest number of hops, unweighted graph) from source to the destination vertex. 
    Returns the distance in the shortest path as well as the next vertex in the agent's path to the destination as a pair inside a string
Parameters: 
    source - source vertex #
    destination - destination vertex #
*/
string Graph::djikstrasSSSP(int source, int destination) {
	list<int> Q;
	vector<int> dist;
	vector<int> prev;
	set<int> visited;

	for (int i = 0; i<num_nodes; i++) { //initialize Q, distance and previous arrays
		Q.push_back(i);
		dist.push_back(INT_MAX);
		prev.push_back(-1); //using -1 to represent undefined
	}
	dist[source] = 0; //already at source so distance is 0

    int u=0;
	while (!Q.empty()) {
		int u = getSmallestVertex(dist, visited); //returns smallest distance value from distance array
		if(u==INT_MAX){ //bug fix - adresses the case when there is no more edges between the gateway and the agent
		    break;
		}
		Q.remove(u);
		visited.insert(u);

        list<int> temp = vertices[u].getAdjacencyList(); //helper
		//relax(u,v,w)
		for (list<int>::iterator it = temp.begin(); it != temp.end(); ++it) {
			int v = *it; 
			int w = 1; //weights are all the same so use 1

			if (dist[v] > dist[u] + w) { //actual relax part
				dist[v] = dist[u] + w;
				prev[v] = u;
			}
		}
	}
	
	//**********ALGORITHM END************************************************************************************************************
	//Finish by finding the next vertex from the agent (source) to the gateway (destination) that was computed
	//***********************************************************************************************************************************
	
    //build the distance/previousVertex pair to return - returns the closest vertex on the optimal path to the destination from the agent
    int nextToAgent = destination;
    while(prev[nextToAgent]!=source){
        nextToAgent=prev[nextToAgent];
    }
    
	string distance = "";
	if(u == INT_MAX){ //bug fix - adresses the case when there is no more edges between the gateway and the agent
	    distance = SSTR(u); //guarantee that the output from this iteration of djikstras is not selected in main()
	}else{
	    distance = SSTR(dist[destination]);
	}
	string next = SSTR(nextToAgent); //next vertex in agent's optimal path from agent to this gateway
	
	//return min distance from agent to this gateway and the previous vertex to the gateway so we 
	//can cut this link if it is the shortest distance out of all the gateways
	string answer = distance + " " + next;
	
	return answer;
}


/*
Function: BFS (the suboptimal solution)
Description: Computes the distance (smallest number of hops, unweighted graph) from source to each reachable vertex. 
    It also produces a "breadth-first tree" with root as the source. Works on both directed and undirected graphs.
Parameters: 
    source - source vertex #
    destination - not used in algorithm just to produce the answer we want at end
*/
string Graph::BFS(int source, int destination){
	vector<int> dist; //u.d
	vector<int> prev; //u.pi
	vector<int> disc; //u.color - undiscovered (-1), discovered (0), finished (1)
        
    for(vector<AdjListVertex>::iterator it=vertices.begin();it!=vertices.end();++it){ //for all vertices in graph
        disc.push_back(-1);               //all vertices start out undiscovered
        dist.push_back(INT_MAX); //dist[u]=infinity
        prev.push_back(-1); //prev[u]=undefined
    }
        
    disc[source]=0; //the source is already discovered
    dist[source]=0; //distance from source to source is 0
    queue<int> Q;
    Q.push(source);
        
    while(Q.size()!=0){ //while queue is not empty
        int u = Q.front();
        Q.pop();
        
        list<int> temp = vertices[u].getAdjacencyList(); //helper
        for(list<int>::iterator it = temp.begin();it!=temp.end();++it){ //for each vertex v adjacent to u
            int v = *it; //vertex v
            if(disc[v]==-1){ //if the adjacent vertex is undiscovered
                disc[v]=0; //log the vertex is discovered
                dist[v]=dist[u]+1; //v is 1 away from u
                prev[v]=u;
                Q.push(v); //add u's adjacent vertices to v
            }
        }
        disc[u]=1; //log the vertex as finished.
    }
    
	string distance = SSTR(dist[destination]);
	string previous = SSTR(prev[destination]);
	string answer = distance + " " + previous;
	return answer;
}

int main() {

	int N; // the total number of nodes in the level, including the gateways
	int L; // the number of links
	int E; // the number of exit gateways

	cin >> N >> L >> E; cin.ignore();
	Graph skySubnet(N);

	for (int i = 0; i < L; i++) {
		int N1; // N1 and N2 defines a link between these nodes
		int N2;
		cin >> N1 >> N2; cin.ignore();
		skySubnet.addEdge(N1, N2);
	}
	
	//DEBUG
	//skySubnet.printGraph();

	int *gateways = new int[E]; //hold values of all gateways
	for (int i = 0; i < E; i++) {
		int EI; // the index of a gateway node
		cin >> EI; cin.ignore();
		gateways[i] = EI;
		
		//DEBUG
		cerr << "Gateway " << EI << " logged" << endl;
	}

	// game loop
	while (1) {
		int SI; // The index of the node on which the Skynet agent is positioned this turn
		cin >> SI; cin.ignore();
		string answer=""; //
		int currentDistance=-1; //hold current distance to current gateway given by djikstrasSSSP
		int hopsToGate=INT_MAX; //hold shortest distance value considering all gateways.
		int shortestPrevVertex=-1; //hold previous vertex to shortest gateway
		int currentPrevVertex=-1; //hold current previous vertex data to current gateway
		int gatewayForShortest=-1; //hold vertex of shortest gateway to sever link for
		
		for(int i=0;i<E;i++){
		    if(skySubnet.getVertex(gateways[i]).getAdjacencyList().size()!=0){
		        answer = skySubnet.djikstrasSSSP(SI, gateways[i]); //compute shortest path from agent to current gateway
    		    
    		    //DEBUG
    		    //cerr << "The distance to gateway " << gateways[i] << " and its previous vertex are: " << answer << endl;
    		    
    		    //read answer from computation
    		    istringstream is(answer); //use like cin >> x;
    		    is >> currentDistance; //Grab current distance from agent to this gateway
    		    is >> currentPrevVertex; //Grab current previous vertex to this gateway
    		    
    		    if(hopsToGate>currentDistance){ //if there are less hops to this gateway then update data for the shortest path to sever
    		        hopsToGate=currentDistance;
    		        shortestPrevVertex=currentPrevVertex; //a vertex in edge to sever
    		        gatewayForShortest=gateways[i]; //hold this gateway in edge to sever
    		    }
		    }
		}
		
		answer = SSTR(SI)+ " " + SSTR(shortestPrevVertex); //repurpose the answer, sever this link
		//remove the chosen edge so we can continue to choose optimal edges to sever and prevent the agent from reaching the gateway
		skySubnet.removeEdge(SI,shortestPrevVertex); 
		
		//DEBUG
		skySubnet.printGraph();

		cout << answer << endl; //the indices of the nodes you wish to sever the link between
	}
}