import io;
import files;
import string;
@dispatch=WORKER
(int x) worm(int i) "wormsegmenter" "0.0"
["set <<x>> [wormSegmenter_wormSegmenterF <<i>>]"];
//file outputFile <"out.txt">;
string A[];
foreach i in [0:1000-1]{
	//output=blob_from_string(string_from_blob(output)+"File Number\t:"+i+"Data\t"+worm(i)+"\n");
	A[i]="File \t"+i+"data\t:"+worm(i)+"\n";
	//printf("Swift output is \t: %s",A[i]);
}
file outputFile <"output.txt">;
string a = string_join(A,"");
outputFile=write(a);


