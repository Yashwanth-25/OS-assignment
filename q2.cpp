#include <bits/stdc++.h>
using namespace std;

struct p_data
{
	int numer;
	int process_id;
	int arr_time;
	int burst_time;
	int prior;
	int finish_time;
	int remain_time;
	int wait_time;
	int start_time;
	int response_time;

};

struct p_data curr;
typedef struct p_data P_d ;

bool sort_id(const P_d& x , const P_d& y)
{
	return x.process_id < y.process_id;
}
bool sort_arr( const P_d& x ,const P_d& y)
{
	if(x.arr_time < y.arr_time)
		return true;
	else if(x.arr_time > y.arr_time)
		return false;
	if(x.prior < y.prior)
		return true;
	else if(x.prior > y.prior)
		return false;
	if(x.process_id < y.process_id)
		return true;

	return false;
}


bool sort_num( const P_d& x ,const P_d& y)
{
	return x.numer < y.numer;
}
struct comp
{
	bool operator()(const P_d& x ,const P_d& y)
	{
		if( x.prior > y.prior )
			return true;
		else if( x.prior < y.prior )
			return false;
		if( x.process_id > y.process_id )
			return true;

		return false;
	}
};

void my_check(vector<P_d> mv)
{
	for(unsigned int i= 0; i < mv.size() ;i++)
	{
		cout<<" process_id :"<<mv[i].process_id<<" _time : "<<mv[i].arr_time<<" burst_time : "<<mv[i].burst_time<<" prior : "<<mv[i].prior<<endl;
	}

}

int main()
{
	int i;
	vector< P_d > input;
	vector<P_d> input_copy;
	P_d temp;
	int pq_process = 0;
	int rq_process = 0;
	int arr_time;
	int burst_time;
	int process_id;
	int prior;
	int n;
	int clock;
	int total_exection_time = 0;
	cout<<"Enter the number of processes  : ";
	cin>>n;
	for( i= 0; i< n; i++ )
	{
	    cout<<"Enter process_id , Arrival_time , Burst_time , prior for process "<<i+1<<" : ";
		cin>>process_id>>arr_time>>burst_time>>prior;
		temp.numer = i+1;
		temp.arr_time = arr_time;
		temp.burst_time = burst_time;
		temp.remain_time = burst_time;
		temp.process_id = process_id;
		temp.prior = prior;
		input.push_back(temp);
	}
	input_copy = input;
	sort( input.begin(), input.end(), sort_arr );
    total_exection_time = total_exection_time + input[0].arr_time;
    for( i= 0 ;i< n; i++ )
    {
    	if( total_exection_time >= input[i].arr_time )
    	{
    		total_exection_time = total_exection_time +input[i].burst_time;
    	}
    	else
    	{
    		int diff = (input[i].arr_time - total_exection_time);
    		total_exection_time = total_exection_time + diff + burst_time;

    	}
    }

	int Ghant[total_exection_time]={0};
	for( i= 0; i< total_exection_time; i++ )
	{
		Ghant[i]=-1;
	}

	priority_queue < P_d ,vector<p_data> ,comp> pq;

	queue< P_d > rq;
	int cpu_state = 0;
	int quantum = 4 ;
	curr.process_id = -2;
	curr.prior = 999999;

	for ( clock = 0; clock< total_exection_time; clock++ )
	{
		for( int j = 0; j< n ; j++ )
		{
			if(clock == input[j].arr_time)
			{
				pq.push(input[j]);
			}
		}

		if(cpu_state == 0)
		{
			if(!pq.empty())
			{
				curr = pq.top();
				cpu_state = 1;
				pq_process = 1;
				pq.pop();
				quantum = 4;
			}
			else if(!rq.empty())
			{
				curr = rq.front();
				cpu_state = 1;
				rq_process = 1;
				rq.pop();
				quantum = 4;
			}
		}
		else if(cpu_state == 1)
		{
			if(pq_process == 1 && (!pq.empty()))
			{
				if(pq.top().prior < curr.prior )
				{
					rq.push(curr);
					curr = pq.top();
					pq.pop();
					quantum = 4;
				}
			}
			else if(rq_process == 1 && (!pq.empty()))
			{
				rq.push(curr);
				curr = pq.top();
				pq.pop();
				rq_process = 0;
				pq_process = 1;
				quantum = 4 ;
			}
		}

		if(curr.process_id != -2)
		{
			curr.remain_time--;
			quantum--;
			Ghant[clock] = curr.process_id;
			if(curr.remain_time == 0)
			{
				cpu_state = 0 ;
				quantum = 4 ;
				curr.process_id = -2;
				curr.prior = 999999;
				rq_process = 0;
				pq_process = 0;
			}
			else if(quantum == 0 )
			{
				rq.push(curr);
				curr.process_id = -2;
				curr.prior = 999999;
				rq_process = 0;
				pq_process = 0;
				cpu_state=0;
			}
		}
	}

	sort( input.begin(), input.end(), sort_id );
	for(int i=0;i<n;i++)
	{
		for(int k=total_exection_time;k>=0;k--)
		{
			if(Ghant[k]==i+1)
			{
				input[i].finish_time=k+1;
				break;
			}
		}
	}
	for(int i=0;i<n;i++)
	{
		for(int k=0;k<total_exection_time;k++)
		{
			if(Ghant[k]==i+1)
			{
				input[i].start_time=k;
				break;
			}
		}
	}

	sort( input.begin(), input.end(), sort_num );

	for(int i=0;i<n;i++)
	{
		input[i].response_time=input[i].start_time-input[i].arr_time;
		input[i].wait_time=(input[i].finish_time-input[i].arr_time)-input[i].burst_time;
	}

    cout<<endl<<"**********************************************************"<<endl<<endl;
	cout<<"process_id\tRes_time F_time\tW_time"<<endl;
	for(int i=0;i<n;i++)
	{
		cout<<input[i].process_id<<"\t"<<input[i].response_time<<"\t"<<input[i].finish_time<<"\t"<<input[i].wait_time
		<<endl;
	}
	return 0;
}
