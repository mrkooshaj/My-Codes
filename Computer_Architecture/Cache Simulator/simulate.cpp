#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;

#define memorySize 10000
#define cacheSize 100

int cacheArch = 0; // 0 one-way ; 1 two-way ; 2 four-way
int ReplacementPolicy = 0; // 0 FIFO ; 1 LRU ; 2 MRU ; 3 RANDOM ; 4 LIP
int WritePolicy = 0; // 0 Write Through ; 1 Write Back

int mainMemory[memorySize];

int stepcnt = 0;

int hit_cnt = 0;

int miss_cnt = 0;

struct cacheCell
{
    int data;
    int tag;
    int last_usage;
    int first_insert;
    bool valid;
    bool dirty;
};

struct cacheCell cacheMemory [cacheSize];


int string_to_num (string s)
{
	int result = 0;
	int tenpower = 1;
	int strsize = s.size();
	for (int j = s.size() - 1; j > -1; j--)
	{
		result = result + tenpower * (s[j] - '0');
		tenpower = tenpower * 10;
	}
	
	return result;
}

int DMA_read(int address)
{
	return mainMemory[address];
}

void DMA_write(int address, int data)
{
	mainMemory[address] = data;
}

int random1to1000()
{
	srand(time(NULL));

	int result = rand() * 79;
	
	result = result * 97;
	
	result = result % 1000;
	
	result = result * 23;
	
	result = result % 1000;
	
	result = result * 101;
	
	result = result % 1000;
	
	result = result * 997;
	
	result = result % 1000;
	
	result = result * 333;
	
	result = result % 1000;
	
	result = result * 993;
	
	result = result % 1000;
	
	result = result * 721;
	
	result = result % 1000;
	
	result = result * 399;
	
	result = result % 1000;
	
	result = result * 441;
	
	result = result % 1000;
	
	result = result * 697;
	
	result = result % 1000;
	
	result++;
	
	return result;
}

vector<int> cacheAddressMap(int address)
{
	vector<int> result;
	
	if (cacheArch == 0)
	{
		result.push_back(address % cacheSize);
	}
	
	else if (cacheArch == 1)
	{
		result.push_back(address % (cacheSize / 2));
		result.push_back(address % (cacheSize / 2) + (cacheSize / 2));
	}
	else if (cacheArch == 2)
	{
		result.push_back(address % (cacheSize / 4));
		result.push_back(address % (cacheSize / 4) + (cacheSize / 4));
		result.push_back(address % (cacheSize / 4) + (cacheSize * 2 / 4));
		result.push_back(address % (cacheSize / 4) + (cacheSize * 3 / 4));
	}
	
	return result;
}

int isInCache(int address)
{
	vector <int> mapping = cacheAddressMap(address);
	for (int i = 0; i < mapping.size(); i++)
	{
		struct cacheCell test = cacheMemory[mapping[i]];
		if (test.valid == true && test.tag == address)
		{
 			return mapping[i];
		}
	}
	
	return -1;
}

int evictionLRU(vector <int> array)
{
	int min = cacheMemory[array[0]].last_usage;
	int result = 0;
	for (int i = 0; i < array.size(); i++)
	{
		if(cacheMemory[array[i]].last_usage < min)
		{
			min = cacheMemory[array[i]].last_usage;
			result = i;
		}
	}
	
	return array[result];
}

int evictionMRU(vector <int> array)
{
	int max = cacheMemory[array[0]].last_usage;
	int result = 0;
	for (int i = 0; i < array.size(); i++)
	{
		if(cacheMemory[array[i]].last_usage > max)
		{
			max = cacheMemory[array[i]].last_usage;
			result = i;
		}
	}
	
	return array[result];
}

int evictionFIFO(vector <int> array)
{
	int min = cacheMemory[array[0]].first_insert;
	int result = 0;
	for (int i = 0; i < array.size(); i++)
	{
		if(cacheMemory[array[i]].first_insert < min)
		{
			min = cacheMemory[array[i]].first_insert;
			result = i;
		}
	}
	
	return array[result];
}

int evictionRandom(vector <int> array)
{
	return array[random1to1000() % array.size()];
}

int evict(vector<int> array)
{
	for (int i = 0; i < array.size(); i++)
	{
		if(cacheMemory[array[i]].valid == false)
		{
			cacheMemory[array[i]].valid = true;
			return array[i];
		}
	}
	struct cacheCell tester;
	
	if (ReplacementPolicy == 0)
	{
		tester = cacheMemory[evictionFIFO(array)];
		if (tester.valid == true && tester.dirty == true && WritePolicy == 1)
		{
			DMA_write(tester.tag,tester.data);
			tester.dirty = false;
			tester.valid = false;
		}
		return evictionFIFO(array);
	}
	
	if (ReplacementPolicy == 1)
	{
		tester = cacheMemory[evictionLRU(array)];
		if (tester.valid == true && tester.dirty == true && WritePolicy == 1)
		{
			DMA_write(tester.tag,tester.data);
			tester.dirty = false;
			tester.valid = false;
		}
		return evictionLRU(array);
	}
	
	if (ReplacementPolicy == 2)
	{
		tester = cacheMemory[evictionMRU(array)];
		if (tester.valid == true && tester.dirty == true && WritePolicy == 1)
		{
			DMA_write(tester.tag,tester.data);
			tester.dirty = false;
			tester.valid = false;
		}
		return evictionMRU(array);
	}
	
	if (ReplacementPolicy == 3)
	{
		tester = cacheMemory[evictionRandom(array)];
		if (tester.valid == true && tester.dirty == true && WritePolicy == 1)
		{
			DMA_write(tester.tag,tester.data);
			tester.dirty = false;
			tester.valid = false;
		}
		return evictionRandom(array);
	}
}


int read(int address)
{
	struct cacheCell changer;
	stepcnt++;
	if (isInCache(address) == -1)
	{
		miss_cnt++;
		changer = cacheMemory[evict(cacheAddressMap(address))];
		changer.data = DMA_read(address);
		changer.last_usage = stepcnt;
		changer.first_insert = stepcnt;
		changer.tag = address;
		changer.valid = true;
		return changer.data;
	}
	else
	{
		hit_cnt++;
		changer = cacheMemory[isInCache(address)];
		changer.last_usage = stepcnt;
		return cacheMemory[isInCache(address)].data;
	}
}


void write(int address, int data)
{
	struct cacheCell changer;
	stepcnt++;
	if (WritePolicy == 0) //Write Through
	{
		if (isInCache(address) != -1)
		{
			changer = cacheMemory[isInCache(address)];
			changer.data = data;
			changer.last_usage = stepcnt;
			changer.dirty = true;
		}
		DMA_write(address,data);
	}
	
	else
	{
		if (isInCache(address) == -1)
		{
			changer = cacheMemory[evict(cacheAddressMap(address))];
			changer.data = data;
			changer.last_usage = stepcnt;
			changer.first_insert = stepcnt;
			changer.tag = address;
			changer.valid = true;
		}
		else
		{
			changer = cacheMemory[isInCache(address)];
			changer.data = data;
			changer.last_usage = stepcnt;
			changer.dirty = true;
		}
	}
}

void swap (int i, int j)
{
	int temp = read(i);
	write(i,read(j));
	write(j,temp);
}

void bubblesort()
{
	for (int i = 0; i < memorySize; i++)
	{
		cout<<i<<endl;
		cout<<"Hits = "<<hit_cnt<<endl<<"Misses = "<<miss_cnt<<endl;
		for (int j = 0; j < memorySize - 1; j++)
		{
			if (read(j) > read(j+1))
			{
				swap(j,j+1);
			}
		}
	}
}

void insertionsort()
{
	for (int i = 0; i < memorySize; i++)
	{
		for (int j = i-1; j > -1; j--)
		{
			if (read(j) > read(j+1))
			{
				swap(j,j+1);
			}
			else
			{
				break;
			}
		}
	}
}

void quicksort(int l_index, int h_index)
{
	int low = l_index;
	int high = h_index;
	int pivot = read(low); // as said in cw
	
	while (low <= high)
	{
		while (read(low) < pivot)
		{
			low++;
		}
		while (read(high) > pivot)
		{
			high--;
		}
		if (low <= high)
		{
			swap(low,high);
			low++;
			high--;
		}
	}
	
	if (l_index < high)
	{
		quicksort(l_index, high);
	}
	if (h_index > low)
	{
		quicksort(low, h_index);
	}
}

void merge(int start, int end, int middle)
{
	int iterator = start;
	
	while (iterator <= middle)
	{
		if (read(iterator) > read(middle + 1))
		{
			swap(iterator, middle + 1);
			for (int j = middle + 1; j < end; j++)
			{
				if (read(j) > read(j+1))
				{
					swap(j,j+1);
				}
			}
		}
	}
}

void mergesort(int start, int end)
{
	if (end - start == 1)
	{
		if (read(start) > read(end))
		{
			swap(start,end);
		}
	}
	else if (end != start)
	{
		int middle = (start + end) / 2;
		mergesort(start,middle);
		mergesort(middle+1,end);
		merge(start,end,middle);
	}
}

int main() 
{
    
    int i = 0; 
    
    ifstream datafile("data.txt");
    
    char str[255];
    
    while (datafile)
    {
    	datafile.getline(str,255);
    	if (datafile)
    	{
    		mainMemory[i] = string_to_num(str);
    		i++;
    	}
    }
    
    bubblesort();
}
