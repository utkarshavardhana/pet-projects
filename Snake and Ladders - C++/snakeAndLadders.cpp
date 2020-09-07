// Snake and Ladders

#include<bits/stdc++.h>
using namespace std;

int main() {
	bool play = true;
	while(play) {
		int players;
		cout<<"How many players want to play : ";
		cin>>players;
		
		map<int, string> names;
		cout<<"Enter your names : "<<endl; 
		for(int i=0; i<players; i++) {
			string str;
			cout<<"Player "<<i<<": ";
			cin>>str;
			names[i] = str;
		}
		
		int numSnakes, numLadders;
		map<int, int> snake, ladder;
		cout<<"How many snakes ? ";
		cin>>numSnakes;
		cout<<"Enter the snakes' locations (head, tail) : ";
		while(snake.size() < numSnakes) {
			int u, v;
			cin>>u>>v;
			if(u <= v)	continue;
			snake[u] = v;
		}
		
		cout<<"How many ladders ? ";
		cin>>numLadders;
		cout<<"Enter the ladders' locations (start, end) : ";
		while(ladder.size() < numLadders) {
			int u, v;
			cin>>u>>v;
			if(u >= v or snake[u] or snake[v])	continue;
			ladder[u] = v;
		}
		
		vector<int> player(players, 0);
		
		bool won = false;
		int winner = -1;
		int turn = 0;
		while(!won) {
		    turn++;
			int dice = rand()%6 + 1;
			if(player[turn%players] == 0) {
				if(dice == 1)	player[turn%players] = 1;
				cout<<names[turn%players]<<" got "<<dice<<". The new position is : "<<player[turn%players]<<endl;
				continue;
			}
			if(player[turn%players] + dice > 100) {
				cout<<names[turn%players]<<" got "<<dice<<". The new position is : "<<player[turn%players]<<endl;
				continue;
			}
			player[turn%players] += dice;
			if(snake[player[turn%players]]) {
				cout<<"Cut by snake. "; 
				player[turn%players] = snake[player[turn%players]];
			}
			if(ladder[player[turn%players]]) {
				cout<<"Onto the ladder. "; 
				player[turn%players] = ladder[player[turn%players]];
			}
			cout<<names[turn%players]<<" got "<<dice<<". The new position is : "<<player[turn%players]<<endl;
			if(player[turn%players] == 100) {
				won = true;
				winner = turn%players;
			}
		}
		
		cout<<"Winner is "<<names[winner]<<endl;
		
		char playmore;
		cout<<"Press Y to play again ? ";
		cin>>playmore;
		
		if(playmore != 'Y' and playmore != 'y')    play = false;
	}
	return 0;
}
