import io;
import files;
import string;
@dispatch=WORKER
(int x) worm(int i,int xA,int yA) "wormsegmenter" "0.0"
["set <<x>> [wormSegmenter_wormSegmenterF <<i>> <<xA>> <<yA>>]"];
//file outputFile <"out.txt">;
string A[];
string inputF[] =file_lines(input("input.txt"));
foreach i in [0:32000-1]{
	if (i ==0){
		A[i]="File \t"+i+"data\t:"+worm(i,-1,-1)+"\n";	
	}
	else
	{
		A[i]="File \t"+i+"data\t:"+worm(i,string2int(split(inputF[i-1],",")[1]),string2int(split(inputF[i-1],",")[2]))+"\n";
	}
	//printf("Swift output is \t: %s",A[i]);
}
file outputFile <"output.txt">;
string a = string_join(A,"");
outputFile=write(a);


