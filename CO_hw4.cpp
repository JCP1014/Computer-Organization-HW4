#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<vector>
#include<fstream>
#include<string>
#include<cstring>
#include<queue>
using namespace std;

int main(int argc, char *argv[])
{
	
	vector<unsigned long> instruc;
	string input;
	ifstream in(argv[2]);
	ofstream out(argv[4]);
	int cache_size, block_size;
	int asso;  // associativity
	int rp;  // replace algorithm
	int block_amount;
	unsigned long block_addr;
	vector<unsigned long> block_used;
	//int index_amount;
	unsigned long hit = 0;
	bool isHit = false;
	queue<unsigned long> priority;
	vector<unsigned long> hitInstruc;
	vector<unsigned long> missInstruc;
	unsigned long instruc_amount;
	double missRate;

	// read file
	for(int i=0; i<4; i++)
	{
		getline(in, input);
		instruc.push_back(atoi(input.c_str()));
	}

	while(getline(in, input))
	{
		instruc.push_back(strtoul(input.c_str(),NULL,16));
	}
	in.close();

	cache_size = instruc[0];
	block_size = instruc[1];
	asso = instruc[2];
	rp = instruc[3];

	cache_size *= 1000;  // convert KB to Byte	
	switch(asso)
	{
		case 0:
			
			break;
		case 1:

			break;
		case 2:  // fully associative
			block_amount = cache_size / block_size;
			block_used.assign(block_amount,0);
			for(int i=4; i<instruc.size(); i++)
			{
				cout << instruc[i] << endl;
				cout << block_size << endl;
				block_addr = instruc[i] / block_size;
				//cout << block_addr << endl;
				isHit = false;
				for(int j=0; j<block_used.size(); j++)
				{
					if(block_addr == block_used[j])
					{
						isHit = true;
						hit++;
						hitInstruc.push_back(i-3);
						break;
					}
				}
				if(isHit == false)  // miss
				{
					missInstruc.push_back(i-3);
					if(block_used.size() < block_amount)
					{
						block_used.push_back(block_addr);
						//priority.push(block_addr);	
					}					
					else
					{
						if(rp == 0)  // FIFO
						{
							block_used.erase(block_used.begin());
							block_used.push_back(block_addr);
						}
						else  // LRU
						{
							
						}
					}
				}
			}
	}

	instruc_amount = instruc.size()-4;
	//cout << hit << endl;
	//cout << instruc_amount << endl;
	missRate = 1 - ((double)hit / instruc_amount);
	//cout << missRate << endl;

	// write file
	out << "Hits instructions: ";
	for(int i=0; i<hitInstruc.size(); i++)
	{
		out << hitInstruc[i];
		if(i!=hitInstruc.size()-1)
			out << ",";
	}
	out << endl;
	out << "Misses instructions: ";
	for(int i=0; i<missInstruc.size(); i++)
	{
		out << missInstruc[i];
		if(i!=missInstruc.size()-1)
			out << ",";
	}
	out << endl;
	out << "Miss rate: " << missRate;
	out.close();


	return 0;
}
